<?php

/**
 * @file
 * Service's resources callbacks.
 */

function reiscout_address_resource_action_view_address($nid) {
  if (!reiscout_address_user_has_view($nid) && !reiscout_address_set_view($nid)) {
    services_error('Could not flag', 500);
  }

  return array('status' => 'OK');
}
