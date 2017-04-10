<?php
/**
 * @file
 * reiscout_points_feature.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function reiscout_points_feature_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access rules link buy_owner_info'.
  $permissions['access rules link buy_owner_info'] = array(
    'name' => 'access rules link buy_owner_info',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'rules_link',
  );

  // Exported permission: 'access rules link buy_sending_letter'.
  $permissions['access rules link buy_sending_letter'] = array(
    'name' => 'access rules link buy_sending_letter',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'rules_link',
  );

  // Exported permission: 'administer search'.
  $permissions['administer search'] = array(
    'name' => 'administer search',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'search',
  );

  return $permissions;
}
