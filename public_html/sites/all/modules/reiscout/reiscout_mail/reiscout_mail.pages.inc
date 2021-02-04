<?php

/**
 * @file
 * User page callback file for the Reiscout Mail module.
 */

/**
 * Form builder; Allows to pick up a template for a letter and send it.
 *
 * @see reiscout_mail_send_letter_form_submit()
 */
function reiscout_mail_send_letter_form($form, &$form_state, $node) {
  global $user;

  try {
    $templatesOptions = Letter::getTemplatesOptions($node);
  }
  catch (ReiscoutMailNoGlobalTemplatesDefined $e) {
    watchdog_exception('reiscout_mail', $e);

    // If the current user can manage templates
    if (user_access('edit any letter_template content')) {
      $t_args = array('!url' => url('node/add/letter-template'));
      $msg = t('No global letter templates defined. You can <a href="!url">create</a> one.', $t_args);
    }
    else {
      $msg = t("A letter to the property's owner cannot be sent. Please, try again later or contact technical support for assistance!");
    }

    drupal_set_message($msg, 'error');
    drupal_goto('node/' . $node->nid);
  }
  catch (ReiscoutPropertyValueIsUnknown $e) {
    watchdog_exception('reiscout_mail', $e);
    $msg = t('The property value is unknown. Please fill in either <em>Appraised Value</em> field or <em>Market Value</em> field to be able to send a letter!');
    drupal_set_message($msg, 'error');
    drupal_goto('node/' . $node->nid);
  }
  catch (ReiscoutPropertyGrossAreaIsUnknown $e) {
    watchdog_exception('reiscout_mail', $e);
    $msg = t('The gross area of the property is unknown. Please fill in <em>Gross Area</em> field to be able to send a letter!');
    drupal_set_message($msg, 'error');
    drupal_goto('node/' . $node->nid);
  }
  catch (ReiscoutPropertyUserAddressIsNotSet $e) {
    watchdog_exception('reiscout_mail', $e);
    $t_args = array('!url' => url('user/' . $user->uid . '/edit', array('query' => array('destination' => 'node/' . $node->nid))));
    $msg = t('Please fill in your postal address for <a href="!url">your profile</a> to be able to send a letter!', $t_args);
    drupal_set_message($msg, 'error');
    drupal_goto('node/' . $node->nid);
  }
  catch (ReiscoutPropertyUserPhoneNumberIsNotSet $e) {
    watchdog_exception('reiscout_mail', $e);
    $t_args = array('!url' => url('user/' . $user->uid . '/edit', array('query' => array('destination' => 'node/' . $node->nid))));
    $msg = t('Please fill in your phone number for <a href="!url">your profile</a> to be able to send a letter!', $t_args);
    drupal_set_message($msg, 'error');
    drupal_goto('node/' . $node->nid);
  }
  catch (Exception $e) {
    watchdog_exception('reiscout_mail', $e);
    $msg = t("A letter to the property's owner cannot be sent. Please, try again later or contact technical support for assistance!");
    drupal_set_message($msg, 'error');
    drupal_goto('node/' . $node->nid);
  }

  $form['info'] = array(
    '#prefix' => '<p>',
    '#markup' => t('Please, pick up a predefined template for your letter or create a custom one'),
    '#suffix' => '</p>',
  );

  $form['property_nid'] = array(
    '#type' => 'value',
    '#value' => $node->nid,
  );

  $form['template_nid'] = array(
    '#type' => 'radios',
    '#title' => t('Available templates'),
    '#options' => $templatesOptions,
    '#default_value' => Letter::getTemplateNidByUid($user->uid),
    '#required' => TRUE,
  );

  $form['use_call_center'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Reiscout Call Center ($50/mo)'),
    '#description' => t('The phone number of our call center will be placed on your letter as the contact number for incoming calls.<br/>You will receive a weekly report of each call, the results, and the contact information of the prospects that responded.<br/>Our agents utilize a custom script to be sure that each call provides you the information that will help you to make an investment decision.'),
    '#disabled' => TRUE,
  );

  $form['#attached']['css'][] = drupal_get_path('module', 'reiscout_mail') . '/reiscout_mail.css';

  return reiscout_points_product_decorate_form($form, $form_state, 'send_letter');
}

/**
 * Form submission handler for reiscout_mail_send_letter_form().
 *
 * @see reiscout_mail_send_letter_form()
 */
function reiscout_mail_send_letter_form_submit($form, &$form_state) {
  global $user;

  $property_nid = intval($form_state['values']['property_nid']);
  $template_nid = intval($form_state['values']['template_nid']);

  Letter::saveDefaultTemplateNidForUser($user->uid, $template_nid);

  if (!ReiscoutMail::canUserSendBySendLimitPeriod($property_nid)) {
    $t_args = array(
      '!period' => ReiscoutMail::getSendLimitPeriod(),
    );
    $message = t("You may send a mail to the same property's owner only once per !period days!", $t_args);
    drupal_set_message($message, 'warning');
    $form_state['redirect'] = 'node/' . $property_nid;
    return;
  }

  try {
    $letter = Letter::send($property_nid, $template_nid);

    reiscout_points_product_charge('send_letter');
    ReiscoutMail::log($property_nid, $template_nid, $letter['id'], $letter['expected_delivery_date'], ReiscoutMail::TYPE_LETTER);

    $t_args = array(
      '!url' => $letter['url'],
      '%carrier' => $letter['carrier'],
      '%date' => $letter['expected_delivery_date'],
    );
    $message = t('Your <a href="!url" target="_blank">letter</a> will be sent via %carrier. Expected delivery date is %date.', $t_args);
    drupal_set_message($message);
  }
  catch (LobApiException $e) {
    $msg = t("A letter to the property's owner cannot be sent. Please, try again later or contact technical support for assistance!");
    drupal_set_message($msg, 'error');
  }
  catch (Exception $e) {
    watchdog_exception('reiscout_mail', $e);
    $msg = t("A letter to the property's owner cannot be sent. Please, try again later or contact technical support for assistance!");
    drupal_set_message($msg, 'error');
  }

  $form_state['redirect'] = 'node/' . $property_nid;
}

/**
 * Form builder; Allows to pick up a template for a postcard and send it.
 *
 * @see reiscout_mail_send_postcard_form_submit()
 */
function reiscout_mail_send_postcard_form($form, &$form_state, $node) {
  global $user;

  try {
    $templatesOptions = Postcard::getTemplatesOptions($node);
  }
  catch (ReiscoutMailNoGlobalTemplatesDefined $e) {
    watchdog_exception('reiscout_mail', $e);

    // If the current user can manage templates
    if (user_access('edit any postcard_template content')) {
      $t_args = array('!url' => url('node/add/postcard-template'));
      $msg = t('No global postcard templates defined. You can <a href="!url">create</a> one.', $t_args);
    }
    else {
      $msg = t("A postcard to the property's owner cannot be sent. Please, try again later or contact technical support for assistance!");
    }

    drupal_set_message($msg, 'error');
    drupal_goto('node/' . $node->nid);
  }
  catch (ReiscoutPropertyUserPhoneNumberIsNotSet $e) {
    watchdog_exception('reiscout_mail', $e);
    $user_edit_link = url('user/' . $user->uid . '/edit', array('query' => array('destination' => 'node/' . $node->nid)));
    $t_args = array('!user_edit_link' => $user_edit_link);
    $msg = t("Please fill in your phone number to be able to send a postcard for <a href='!user_edit_link'>your profile</a>.", $t_args);
    drupal_set_message($msg, 'error');
    drupal_goto('node/' . $node->nid);
  }
  catch (Exception $e) {
    watchdog_exception('reiscout_mail', $e);
    $msg = t("A postcard to the property's owner cannot be sent. Please, try again later or contact technical support for assistance!");
    drupal_set_message($msg, 'error');
    drupal_goto('node/' . $node->nid);
  }

  $form['info'] = array(
    '#prefix' => '<p>',
    '#markup' => t('Please, pick up a predefined template for your postcard or create a custom one'),
    '#suffix' => '</p>',
  );

  $form['property_nid'] = array(
    '#type' => 'value',
    '#value' => $node->nid,
  );

  $form['template_nid'] = array(
    '#type' => 'radios',
    '#title' => t('Available templates'),
    '#options' => $templatesOptions,
    '#default_value' => Postcard::getTemplateNidByUid($user->uid),
    '#required' => TRUE,
  );

  $form['use_call_center'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Reiscout Call Center ($50/mo)'),
    '#description' => t('The phone number of our call center will be placed on your postcard as the contact number for incoming calls.<br/>You will receive a weekly report of each call, the results, and the contact information of the prospects that responded.<br/>Our agents utilize a custom script to be sure that each call provides you the information that will help you to make an investment decision.'),
    '#disabled' => TRUE,
  );

  $form['#attached']['css'][] = drupal_get_path('module', 'reiscout_mail') . '/reiscout_mail.css';

  return reiscout_points_product_decorate_form($form, $form_state, 'send_postcard');
}

/**
 * Form submission handler for reiscout_mail_send_postcard_form().
 *
 * @see reiscout_mail_send_postcard_form()
 */
function reiscout_mail_send_postcard_form_submit($form, &$form_state) {
  global $user;

  $property_nid = intval($form_state['values']['property_nid']);
  $template_nid = intval($form_state['values']['template_nid']);

  Postcard::saveDefaultTemplateNidForUser($user->uid, $template_nid);

  if (!ReiscoutMail::canUserSendBySendLimitPeriod($property_nid)) {
    $t_args = array(
      '!period' => ReiscoutMail::getSendLimitPeriod(),
    );
    $message = t("You may send a mail to the same property's owner only once per !period days!", $t_args);
    drupal_set_message($message, 'warning');
    $form_state['redirect'] = 'node/' . $property_nid;
    return;
  }

  try {
    $postcard = Postcard::send($property_nid, $template_nid);

    reiscout_points_product_charge('send_postcard');
    ReiscoutMail::log($property_nid, $template_nid, $postcard['id'], $postcard['expected_delivery_date'], ReiscoutMail::TYPE_POSTCARD);

    $t_args = array(
      '!url' => $postcard['url'],
      '%carrier' => $postcard['carrier'],
      '%date' => $postcard['expected_delivery_date'],
    );
    $message = t('Your <a href="!url" target="_blank">postcard</a> will be sent via %carrier. Expected delivery date is %date.', $t_args);
    drupal_set_message($message);
  }
  catch (ReiscoutPropertyUserAddressIsNotSet $e) {
    watchdog_exception('reiscout_mail', $e);
    $user_edit_link = url('user/' . $user->uid . '/edit', array('query' => array('destination' => 'node/' . $property_nid)));
    $t_args = array('!user_edit_link' => $user_edit_link);
    $msg = t('Please fill in your postal address to be able to sent a postcard for <a href="!user_edit_link">your profile</a>.', $t_args);
    drupal_set_message($msg, 'error');
  }
  catch (LobApiException $e) {
    $msg = t("A postcard to the property's owner cannot be sent. Please, try again later or contact technical support for assistance!");
    drupal_set_message($msg, 'error');
  }
  catch (Exception $e) {
    watchdog_exception('reiscout_mail', $e);
    $msg = t("A postcard to the property's owner cannot be sent. Please, try again later or contact technical support for assistance!");
    drupal_set_message($msg, 'error');
  }

  $form_state['redirect'] = 'node/' . $property_nid;
}

/**
 * Page callback: displays a letter preview.
 *
 * Given a property node and a template node, displays the letter preview.
 */
function reiscout_mail_preview_letter_page($property_node, $template_node) {
  print Letter::buildPreviewHtml($property_node->nid, $template_node->nid);
}

/**
 * Page callback: displays mail sent history.
 *
 * Displays mail sent history for the current Property node.
 */
function reiscout_mail_sent_history_page($node) {
  return ReiscoutMail::genSentHistoryPage($node);
}

/**
 * Page callback: webhook for Lob API.
 *
 * Processes a notification from Lob on tracking events for mail.
 */
function reiscout_mail_wh_page() {
  ReiscoutMail::processLobNotification();
}
