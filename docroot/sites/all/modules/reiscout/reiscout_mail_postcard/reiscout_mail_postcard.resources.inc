<?php

/**
 * Returns the list of available actions.
 */
function _reiscout_mail_postcard_resource_get_available_actions($nid) {
  global $user;

  $actions = array(
    'send_postcard' => 0,
    'btn_send_postcard_title' => '',
    'buy_mail_sending_points' => 0,
  );

  $node = node_load($nid);

  if (_reiscout_mail_postcard_is_user_can_send($node)) {
    $points = userpoints_get_current_points($user->uid, REISCOUT_MAIL_POSTCARD_USERPOINTS_TID);

    // If user has enough points
    if ($points > 0) {
      $actions['send_postcard'] = 1;
      $actions['btn_send_postcard_title'] = t('Send a postcard to the property owner (!points points left)', array('!points' => $points));
    }
    // If not
    else {
      $actions['buy_mail_sending_points'] = 1;
    }
  }

  return $actions;
}

/**
 * Sends a postcard to an owner of a property.
 */
function _reiscout_mail_postcard_resource_send($property_nid) {
  global $user;

  $result = array(
    'status' => FALSE,
    'message' => '',
  );

  try {
    module_load_include('inc', 'reiscout_mail_postcard', 'reiscout_mail_postcard.pages');

    $template_nid = _reiscout_mail_postcard_get_template_nid_by_uid($user->uid);
    $postcard = _reiscout_mail_postcard_send($property_nid, $template_nid);

    _reiscout_mail_postcard_decrease_user_points();
    _reiscout_mail_postcard_log($property_nid, $template_nid, $postcard['id']);

    $t_args = array(
      '!url' => $postcard['url'],
      '%carrier' => $postcard['carrier'],
      '%date' => $postcard['expected_delivery_date'],
      '!url_login' => url('/user', array('absolute' => TRUE)),
    );
    $message = t('Your <a href="!url" target="_blank">postcard</a> will be sent via %carrier. Expected delivery date is %date. <br><a onclick="javascript:window.open(\'!url_login\', \'_blank\', \'location=yes\');">Log in to reiscout.com</a> with the same credentials and create your own template for a postcard.', $t_args);

    $result['status'] = TRUE;
    $result['message'] = $message;
  }
  catch (ReiscoutPropertyUserAddressIsNotSet $e) {
    watchdog_exception('reiscout_mail_postcard', $e);
    $t_args = array('!user_edit_link' => 'user/' . $user->uid . '/edit');
    $result['message'] = t("Please fill in your postal address to be able to sent a postcard for <a href='#' onclick='javascript:drupalgap_goto(\"!user_edit_link\", {});'>your profile</a>.", $t_args);
  }
  catch (ReiscoutPropertyUserPhoneNumberIsNotSet $e) {
    watchdog_exception('reiscout_mail_postcard', $e);
    $t_args = array('!user_edit_link' => 'user/' . $user->uid . '/edit');
    $result['message'] = t("Please fill in your phone number to be able to sent a postcard for <a href='#' onclick='javascript:drupalgap_goto(\"!user_edit_link\", {});'>your profile</a>.", $t_args);
  }
  catch (LobApiException $e) {
    $result['message'] = t("Letter to the property's owner cannot be sent. Please, try again later or contact technical support for assistance!");
  }
  catch (Exception $e) {
    watchdog_exception('reiscout_mail_postcard', $e);
    $result['message'] = t("Letter to the property's owner cannot be sent. Please, try again later or contact technical support for assistance!");
  }

  return $result;
}

/**
 * Determines whether the current user can access to reiscout_mail_postcard resource.
 *
 * @param $op
 *   One of get_available_actions, send.
 * @param $args
 *   Resource arguments passed through from the original request.
 * @return bool
 */
function _reiscout_mail_postcard_resource_access($op, $args = array()) {
  global $user;

  if ('get_available_actions' == $op) {
    return TRUE;
  }

  $nid = $args[0];
  $node = node_load($nid);

  if (_reiscout_mail_postcard_is_user_can_send($node)) {
    $points = userpoints_get_current_points($user->uid, REISCOUT_MAIL_POSTCARD_USERPOINTS_TID);

    // If user has enough points
    if ($points > 0) {
      return TRUE;
    }
  }

  return FALSE;
}
