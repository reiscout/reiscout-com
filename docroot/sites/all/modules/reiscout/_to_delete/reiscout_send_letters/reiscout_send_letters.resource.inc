<?php

/**
 * Sends a letter to a property's owner
 *
 * @param $nid
 * @return array
 */
function _reiscout_send_letters_send_letter($data = array()) {
  global $user;

  // ToDo: check is node by nid exists and for bundle.
  $nid = $data['nid'];
  $tnid = _reiscout_send_letters_get_template_nid_by_uid($user->uid);

  return reiscout_send_letters_send_letter_drupalgap_callback($nid, $tnid);
}

/**
 * Checks which forms a user have an access to
 *
 * @return array
 */
function _reiscout_send_letters_get_show_button_info($data = array()) {
  global $user;

  $info = array(
    'viewSendLetters' => 0,
    'btnSendLetterTitle' => '',
    'viewBuyLettersPoints' => 0,
  );

  // ToDo: check is node by nid exists and for bundle.
  $nid = $data['nid'];
  $node = node_load($nid);

  if (_reiscout_send_letters_is_user_can_send($node)) {
    $points = userpoints_get_current_points($user->uid, TERM_ID_POINTS_SEND_LETTERS);

    // If user has enough points
    if ($points > 0) {
      $info['viewSendLetters'] = 1;
      $info['btnSendLetterTitle'] = t('Send a letter to Property Owner (!points points left)', array('!points' => $points));
    }
    // If not
    else {
      $info['viewBuyLettersPoints'] = 1;
    }
  }

  return $info;
}
