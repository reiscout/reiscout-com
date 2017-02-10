<?php

function _get_info()
{
  $nid = (int)str_replace('"', '', array_keys($_POST)[0]);
  $result = reiscout_owner_info_get_owner_callback($nid, true);

  return array('status' => $result);
}

function _get_show_button_info()
{
  $viewBuyInfoPoints = $viewGetOwnerInfo = 0;

  if (user_is_logged_in()) {
    $nodeId = (int)str_replace('"', '', array_keys($_POST)[0]);

    if (reiscout_owner_info_access($nodeId, true)) {
      $viewBuyInfoPoints = 1;
    }

    if ($viewBuyInfoPoints == 0 && reiscout_owner_info_access($nodeId, false)) {
      $viewGetOwnerInfo = 1;
    }

  }

  return ['viewBuyInfoPoints' => $viewBuyInfoPoints, 'viewGetOwnerInfo' => $viewGetOwnerInfo];
}