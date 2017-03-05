<?php

/**
 * Send letter
 *
 * @param $nid
 * @return array
 */
function _reiscout_send_letters_send_letter($nid) {
  // ToDo: check is node by nid exists and for bundle.
  $node = node_load($nid);
  global $user;
  $user = user_load($user->uid);
  if (!empty($user->field_default_template_nid[LANGUAGE_NONE][0]['value'])) {
    $template_node = $user->field_default_template_nid[LANGUAGE_NONE][0]['value'];
  }

  if (empty($template_node)) {
    watchdog('reiscout_send_letters', 'Letter template for user @uid not found', array('@uid' => $user->uid), WATCHDOG_ERROR);
    return ['status' => false];
  }


  $result = reiscout_send_letters_send_letter_drupalgap_callback($node, $template_node);

  return ['status' => $result];
}

/**
 * Checking view buttons
 *
 * @return array
 */
function _reiscout_send_letters_get_show_button_info($nid) {
  // ToDo: check is node by nid exists and for bundle.s
  $viewBuyLettersPoints = $viewSendLetters = 0;
  if (user_is_logged_in()) {
    if (reiscout_send_letters_access_points($nid)) {
      $viewBuyLettersPoints = 1;
    }

    if ($viewBuyLettersPoints == 0 && reiscout_send_letters_access($nid)) {
      $viewSendLetters = 1;
    }
  }
  return ['viewBuyLettersPoints' => $viewBuyLettersPoints, 'viewSendLetters' => $viewSendLetters];
}