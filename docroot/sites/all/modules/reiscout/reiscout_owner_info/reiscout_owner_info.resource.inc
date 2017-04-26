<?php

/*
 * Requests info about a property's owner and saves it
 */
function _reiscout_owner_info_get_info($data = array()) {
  // ToDo: check is node by nid exists and for bundle.
  $nid = $data['nid'];

  $result = reiscout_owner_info_get_owner_drupalgap_callback($nid);

  return array('status' => $result);
}

/**
 * Checks which forms a user have an access to
 *
 * @return array
 */
function _reiscout_owner_info_get_show_button_info($data = array()) {
  global $user;

  $info = array(
    'viewGetOwnerInfo' => 0,
    'btnGetOwnerInfoTitle' => '',
    'viewBuyInfoPoints' => 0,
  );

  // ToDo: check is node by nid exists and for bundle.
  $nid = $data['nid'];
  $node = node_load($nid);

  if (reiscout_owner_info_access_common($node)) {
    $points = userpoints_get_current_points($user->uid, TERM_ID_POINTS_OWNER_INFO);

    // If user has enough points
    if ($points > 0) {
      $info['viewGetOwnerInfo'] = 1;
      $info['btnGetOwnerInfoTitle'] = t('Get Property Owner (!points points left)', array('!points' => $points));
    }
    // If not
    else {
      $info['viewBuyInfoPoints'] = 1;
    }
  }

  return $info;
}
