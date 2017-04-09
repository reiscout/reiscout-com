<?php

/*
 * Get owner info
 */
function _reiscout_owner_info_get_info($nid) {
  // ToDo: check is node by nid exists and for bundle.
  $result = reiscout_owner_info_get_owner_drupalgap_callback($nid);

  return ['status' => $result];
}

/**
 * Checking view buttons
 *
 * @return array
 */
function _reiscout_owner_info_get_show_button_info($nid) {
  // ToDo: check is node by nid exists and for bundle.
  $viewBuyInfoPoints = $viewGetOwnerInfo = 0;

  $node = node_load($nid);
  if (user_is_logged_in()) {
    if (reiscout_owner_info_access_points($node)) {
      $viewBuyInfoPoints = 1;
    }

    if ($viewBuyInfoPoints == 0 && reiscout_owner_info_access($nid)) {
      $viewGetOwnerInfo = 1;
    }

  }

  return ['viewBuyInfoPoints' => $viewBuyInfoPoints, 'viewGetOwnerInfo' => $viewGetOwnerInfo];
}