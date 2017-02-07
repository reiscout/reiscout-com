<?php

function _send_letter()
{
  $nid = (int)str_replace('"', '', array_keys($_POST)[0]);
//  $result = reiscout_send_letters_send_letter_callback($nid, $template_nid)
  $result = reiscout_send_letters_send_letter_callback($nid, null, true);

  return array('status' => $result);
}

function _get_show_button_info()
{
  $viewBuyLettersPoints = $viewSendLetters = 0;
  if (user_is_logged_in()) {
    $nodeId = (int)str_replace('"', '', array_keys($_POST)[0]);

    if (reiscout_send_letters_access($nodeId, true)) {
      $viewBuyLettersPoints = 1;
    }

    if ($viewBuyLettersPoints == 0 && reiscout_send_letters_access($nodeId, false)) {
      $viewSendLetters = 1;
    }
  }

  return ['viewBuyLettersPoints' => $viewBuyLettersPoints, 'viewSendLetters' => $viewSendLetters];
}