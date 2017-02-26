<?php

/**
 * Send letter
 *
 * @param $nid
 * @return array
 */
function _reiscout_send_letters_send_letter($nid) {
  $node = node_load($nid);
  global $user;

  $result = reiscout_send_letters_send_letter_drupalgap_callback($node, null);

  return ['status' => $result];
}

/**
 * Checking view buttons
 *
 * @return array
 */
function _reiscout_send_letters_get_show_button_info($nid) {
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