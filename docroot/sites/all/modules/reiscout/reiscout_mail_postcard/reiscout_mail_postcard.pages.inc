<?php

/**
 * @file
 * User page callback file for the Reiscout Mail Postcard module.
 */

/**
 * Form builder; Pick up an HTML template for a postcard and send one.
 *
 * @see reiscout_mail_postcard_send_form_submit()
 */
function reiscout_mail_postcard_send_form($form, &$form_state, $node) {
  global $user;

  $global_templates = _reiscout_mail_postcard_get_global_templates();
  $user_defined_templates = _reiscout_mail_postcard_get_user_defined_templates_by_uid($user->uid);

  if (!$global_templates && !$user_defined_templates) {
    if (node_access('create', 'postcard_template')) {
      $t_args = array('!url_add_template' => url('node/add/postcard-template'));
      $msg = t('No postcard templates found. You can <a href="!url_add_template">create</a> one.', $t_args);
    }
    else {
      $msg = t('You cannot send a postcard, because there are no any postcard templates available.');
    }

    drupal_set_message($msg, 'error');
    drupal_goto('node/' . $node->nid);
  }

  try {
    $templates_options = _reiscout_mail_postcard_combine_templates_options($global_templates, $user_defined_templates, $node);
  }
  catch (ReiscoutPropertyUserPhoneNumberIsNotSet $e) {
    watchdog_exception('reiscout_mail_postcard', $e);
    $user_edit_link = url('user/' . $user->uid . '/edit', array('query' => array('destination' => 'node/'. $node->nid)));
    $t_args = array('!user_edit_link' => $user_edit_link);
    $msg = t("Please fill in your phone number to be able to sent a postcard for <a href='!user_edit_link'>your profile</a>.", $t_args);
    drupal_set_message($msg, 'error');
    drupal_goto('node/' . $node->nid);
  }
  catch (Exception $e) {
    watchdog_exception('reiscout_mail_postcard', $e);
    $msg = t("Letter to the property's owner cannot be sent. Please, try again later or contact technical support for assistance!");
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
    '#options' => $templates_options,
    '#default_value' => _reiscout_mail_postcard_get_template_nid_by_uid($user->uid),
    '#required' => TRUE,
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send a postcard')
  );

  return $form;
}

/**
 * Form submission handler for reiscout_mail_postcard_send_form().
 *
 * @see reiscout_mail_postcard_send_form()
 */
function reiscout_mail_postcard_send_form_submit($form, &$form_state) {
  global $user;

  $property_nid = intval($form_state['values']['property_nid']);
  $template_nid = intval($form_state['values']['template_nid']);

  // Save selected template nid as default for the current user
  $uw = entity_metadata_wrapper('user', $user);
  $uw->field_default_template_nid = $template_nid;
  $uw->save();

  try {
    $postcard = _reiscout_mail_postcard_send($property_nid, $template_nid);

    _reiscout_mail_postcard_decrease_user_points();
    _reiscout_mail_postcard_log($property_nid, $template_nid, $postcard['id']);

    $t_args = array(
      '!url' => $postcard['url'],
      '%carrier' => $postcard['carrier'],
      '%date' => $postcard['expected_delivery_date'],
    );
    $message = t('Your <a href="!url" target="_blank">postcard</a> will be sent via %carrier. Expected delivery date is %date', $t_args);
    drupal_set_message($message);
  }
  catch (LobApiException $e) {
    $msg = t("Letter to the property's owner cannot be sent. Please, try again later or contact technical support for assistance!");
    drupal_set_message($msg, 'error');
  }
  catch (ReiscoutPropertyUserAddressIsNotSet $e) {
    watchdog_exception('reiscout_mail_postcard', $e);
    $user_edit_link = url('user/' . $user->uid . '/edit', array('query' => array('destination' => 'node/' . $property_nid)));
    $t_args = array('!user_edit_link' => $user_edit_link);
    $msg = t("Please fill in your postal address to be able to sent a postcard for <a href='!user_edit_link'>your profile</a>.", $t_args);
    drupal_set_message($msg, 'error');
  }
  catch (Exception $e) {
    watchdog_exception('reiscout_mail_postcard', $e);
    $msg = t("Letter to the property's owner cannot be sent. Please, try again later or contact technical support for assistance!");
    drupal_set_message($msg, 'error');
  }

  $form_state['redirect'] = 'node/' . $property_nid;
}

/**
 * Decreases the amount of user points.
 */
function _reiscout_mail_postcard_decrease_user_points() {
  global $user;

  $params = array(
    'uid' => $user->uid,
    'points' => -1,
    'tid' => REISCOUT_MAIL_POSTCARD_USERPOINTS_TID,
    'operation' => '1 point has been used to send a postcard.',
  );

  userpoints_userpointsapi($params);
}

/**
 * Saves information to DB about postcard sending.
 */
function _reiscout_mail_postcard_log($property_nid, $template_nid, $lob_api_postcard_id) {
  global $user;

  $record = new stdClass();
  $record->uid = $user->uid;
  $record->pnid = $property_nid;
  $record->tnid = $template_nid;
  $record->lob_api_postcard_id = $lob_api_postcard_id;
  $record->timestamp = time();

  drupal_write_record('reiscout_mail_postcard_history', $record);
}

/*
 * Sends a postcard to an owner of a property.
 */
function _reiscout_mail_postcard_send($property_nid, $template_nid) {
  // Check if a Property node exists
  $pnw = entity_metadata_wrapper('node', $property_nid);
  if (!$pnw->value() || 'property' != $pnw->type->value()) {
    $msg = t('Property node is invalid: !nid.', array('!nid' => $property_nid));
    throw new Exception($msg, REISCOUT_MAIL_POSTCARD_EXCEPTION_INVALID_PROPERTY_NODE);
  }

  // Check if a Postcard template node exists
  $tnw = entity_metadata_wrapper('node', $template_nid);
  if (!$tnw->value() || 'postcard_template' != $tnw->type->value()) {
    $msg = t('Postcard template node is invalid: !nid.', array('!nid' => $template_nid));
    throw new Exception($msg, REISCOUT_MAIL_POSTCARD_EXCEPTION_INVALID_TEMPLATE_NODE);
  }

  $property_owner_address = _reiscout_property_get_owner_address_by_nid($property_nid);
  $user_address = _reiscout_property_get_user_address();

  $front = _reiscout_mail_postcard_build_front_html($property_nid, $template_nid);
  $back = _reiscout_mail_postcard_build_back_html($property_nid, $template_nid);

  $data = array(
    'to' => array(
      'name'            => $property_owner_address->name_line->value(),
      'address_line1'   => $property_owner_address->thoroughfare->value(),
      'address_city'    => $property_owner_address->locality->value(),
      'address_state'   => $property_owner_address->administrative_area->value(),
      'address_zip'     => $property_owner_address->postal_code->value(),
      'address_country' => $property_owner_address->country->value(),
    ),

    'from' => array(
      'name'            => $user_address->name_line->value(),
      'address_line1'   => $user_address->thoroughfare->value(),
      'address_city'    => $user_address->locality->value(),
      'address_state'   => $user_address->administrative_area->value(),
      'address_zip'     => $user_address->postal_code->value(),
      'address_country' => $user_address->country->value(),
    ),

    'front'             => $front,
    'back'              => $back,
  );

  return lob_api_send_postcard($data);
}

/**
 * Builds content to use as the front of a postcard.
 *
 * Given a property node and a template node, builds
 * content to use as the front of a postcard.
 */
function _reiscout_mail_postcard_build_front_content($property_nid, $template_nid) {
  $tnw = entity_metadata_wrapper('node', $template_nid);

  if (_reiscout_property_is_owner_an_individual_by_nid($property_nid)) {
    $content = $tnw->field_postcard_template_front->value()['safe_value'];
  }
  else {
    $content = $tnw->field_postcard_template_front_co->value()['safe_value'];
  }

  return _reiscout_mail_postcard_replace_tokens($content, $property_nid);
}

/**
 * Builds content to use as the back of a postcard.
 *
 * Given a property node and a template node, builds
 * content to use as the back of a postcard.
 */
function _reiscout_mail_postcard_build_back_content($property_nid, $template_nid) {
  $tnw = entity_metadata_wrapper('node', $template_nid);
  $content = $tnw->field_postcard_template_back->value()['safe_value'];

  return _reiscout_mail_postcard_replace_tokens($content, $property_nid);
}

/**
 * Builds HTML content to use as the front of a postcard.
 *
 * Given a property node and a template node, builds HTML
 * content to use as the front of a postcard.
 */
function _reiscout_mail_postcard_build_front_html($property_nid, $template_nid) {
  $content = _reiscout_mail_postcard_build_front_content($property_nid, $template_nid);

  $template_file_path = drupal_get_path('module', 'reiscout_mail_postcard') . '/html/front.html';
  if (!$template_file_content = @file_get_contents($template_file_path)) {
    $msg = t('front.html file, that is used as a template for front of a postcard, cannot be read.');
    throw new Exception($msg, REISCOUT_MAIL_POSTCARD_EXCEPTION_TEMPLATE_FRONT_FILE_IS_NOT_READABLE);
  }

  return str_replace('{{content}}', $content, $template_file_content);
}

/**
 * Builds HTML content to use as the back of a postcard.
 *
 * Given a property node and a template node, builds HTML
 * content to use as the back of a postcard.
 */
function _reiscout_mail_postcard_build_back_html($property_nid, $template_nid) {
  $content = _reiscout_mail_postcard_build_back_content($property_nid, $template_nid);

  $template_file_path = drupal_get_path('module', 'reiscout_mail_postcard') . '/html/back.html';
  if (!$template_file_content = @file_get_contents($template_file_path)) {
    $msg = t('back.html file, that is used as a template for back of a postcard, cannot be read.');
    throw new Exception($msg, REISCOUT_MAIL_POSTCARD_EXCEPTION_TEMPLATE_BACK_FILE_IS_NOT_READABLE);
  }

  return str_replace('{{content}}', $content, $template_file_content);
}

/**
 * Combines an option list of HTML templates for postcard.
 */
function _reiscout_mail_postcard_combine_templates_options($global_templates, $user_defined_templates, $property_node) {
  $options = array();

  foreach ($global_templates as $template_nid => $template_node) {
    $options[$template_nid] = _reiscout_mail_postcard_combine_template_option($template_node, $property_node, 'predefined');
  }

  if ($user_defined_templates) {
    foreach ($user_defined_templates as $template_nid => $template_node) {
      $options[$template_nid] = _reiscout_mail_postcard_combine_template_option($template_node, $property_node, 'custom');
    }
  }

  return $options;
}

/**
 * Combines an HTML template option.
 */
function _reiscout_mail_postcard_combine_template_option($template_node, $property_node, $type = 'predefined') {
  $option = array();

  $tnw = entity_metadata_wrapper('node', $template_node);

  $front = _reiscout_mail_postcard_build_front_content($property_node->nid, $template_node->nid);
  $back = _reiscout_mail_postcard_build_back_content($property_node->nid, $template_node->nid);

  if ('predefined' == $type) {
    $title_prefix = t('Predefined:');
  }
  else {
    $title_prefix = t('Custom:');
  }

  $links = array();

  $url_current_path_options = array(
    'query' => array(
      'destination' => current_path()
    ),
    'absolute' => TRUE,
  );

  if (user_access('clone node') && node_access('create', 'postcard_template')) {
    $clone_token = clone_get_token($tnw->nid->value());
    $clone_url = url('node/' . $tnw->nid->value() . '/clone/' . $clone_token . '/', $url_current_path_options);
    $links[] = l(t('create my template based on this one'), $clone_url, array('html' => TRUE));
  }

  if (node_access('update', $template_node)) {
    $links[] = l(t('edit'), url('node/' . $tnw->nid->value() . '/edit', $url_current_path_options), array('html' => TRUE));
  }

  if (node_access('delete', $template_node)) {
    $links[] = l(t('delete'), url('node/' . $tnw->nid->value() . '/delete', $url_current_path_options), array('html' => TRUE));
  }

  $option['header'] = array(
    '#prefix' => '<div class="header">',
    '#markup' => $title_prefix . ' ' . $tnw->title->value() . ($links ? ' | ' . implode(' | ', $links) : ''),
    '#suffix' => '</div>',
  );

  $option['front'] = array(
    '#prefix' => '<div class="template ' . $type . '"><div class="front">',
    '#markup' => $front,
    '#suffix' => '</div>',
  );

  $option['back'] = array(
    '#prefix' => '<div class="back">',
    '#markup' => $back,
    '#suffix' => '</div></div>',
    '#attached' => array(
      'css' => array(
        drupal_get_path('module', 'reiscout_mail_postcard') . '/reiscout_mail_postcard.css',
      ),
    ),
  );

  return drupal_render($option);
}

/**
 * Replaces all tokens in a given string with appropriate values.
 */
function _reiscout_mail_postcard_replace_tokens($content, $property_nid) {
  if (FALSE !== strpos($content, '{{owner_name}}')) {
    $property_owner_address = _reiscout_property_get_owner_address_by_nid($property_nid);
    if (_reiscout_property_is_owner_an_individual_by_nid($property_nid)) {
      $names = explode(' ', $property_owner_address->name_line->value());
      $property_owner_name = mb_convert_case($names[1], MB_CASE_TITLE, "UTF-8");
    }
    else {
      $property_owner_name = $property_owner_address->name_line->value();
    }
    $content = str_replace('{{owner_name}}', $property_owner_name, $content);
  }

  if (FALSE !== strpos($content, '{{street_address}}')) {
    $property_address = _reiscout_property_get_address_by_nid($property_nid);
    $content = str_replace('{{street_address}}', $property_address->thoroughfare->value(), $content);
  }

  if (FALSE !== strpos($content, '{{city}}')) {
    $property_address = _reiscout_property_get_address_by_nid($property_nid);
    $content = str_replace('{{city}}', $property_address->locality->value(), $content);
  }

  if (FALSE !== strpos($content, '{{my_phone}}')) {
    $user_phone_number = _reiscout_property_get_user_phone();
    $content = str_replace('{{my_phone}}', $user_phone_number, $content);
  }

  return $content;
}

/**
 * Returns an ID of HTML template for a postcard for a given user.
 */
function _reiscout_mail_postcard_get_template_nid_by_uid($uid) {
  $available_templates = array();

  if ($global_templates = _reiscout_mail_postcard_get_global_templates_nids()) {
    $available_templates = $global_templates;
  }

  if ($user_defined_templates = _reiscout_mail_postcard_get_user_defined_templates_nids_by_uid($uid)) {
    $available_templates = array_merge($available_templates, $user_defined_templates);
  }

  if (!$available_templates) {
    $msg = t('There are no any postcard templates that a user can use.');
    throw new Exception($msg, REISCOUT_MAIL_POSTCARD_EXCEPTION_TEMPLATES_NOT_AVAILABLE);
  }

  $uw = entity_metadata_wrapper('user', $uid);
  $template_nid = $uw->field_default_template_nid->value();

  // If the 'Default template NID' is not set,
  // or it is set, but a user is not able to use it,
  // set it to the NID of the first available template.
  if (!$template_nid || ($template_nid && !in_array($template_nid, $available_templates))) {
    $template_nid = $available_templates[0];
  }

  return $template_nid;
}

/**
 * Returns a list of global HTML templates for a postcard.
 */
function _reiscout_mail_postcard_get_global_templates() {
  if (!$nids = _reiscout_mail_postcard_get_global_templates_nids()) {
    return FALSE;
  }

  return node_load_multiple($nids);
}

/**
 * Returns a nids of global HTML templates for a postcard.
 */
function _reiscout_mail_postcard_get_global_templates_nids() {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'postcard_template')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_postcard_template_global', 'value', TRUE)
    ->execute();

  if (!isset($result['node'])) {
    return FALSE;
  }

  return array_keys($result['node']);
}

/**
 * Returns a list of user defined HTML templates for a postcard.
 */
function _reiscout_mail_postcard_get_user_defined_templates_by_uid($uid) {
  if (!$nids = _reiscout_mail_postcard_get_user_defined_templates_nids_by_uid($uid)) {
    return FALSE;
  }

  return node_load_multiple($nids);
}

/**
 * Returns a nids of user defined HTML templates for a postcard.
 */
function _reiscout_mail_postcard_get_user_defined_templates_nids_by_uid($uid) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'postcard_template')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->propertyCondition('uid', $uid)
    ->fieldCondition('field_postcard_template_global', 'value', FALSE)
    ->execute();

  if (!isset($result['node'])) {
    return FALSE;
  }

  return array_keys($result['node']);
}
