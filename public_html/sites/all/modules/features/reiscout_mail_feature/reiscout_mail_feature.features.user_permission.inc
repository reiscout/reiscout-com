<?php
/**
 * @file
 * reiscout_mail_feature.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function reiscout_mail_feature_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create letter_template content'.
  $permissions['create letter_template content'] = array(
    'name' => 'create letter_template content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create postcard_template content'.
  $permissions['create postcard_template content'] = array(
    'name' => 'create postcard_template content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own letter_template content'.
  $permissions['delete own letter_template content'] = array(
    'name' => 'delete own letter_template content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own postcard_template content'.
  $permissions['delete own postcard_template content'] = array(
    'name' => 'delete own postcard_template content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own letter_template content'.
  $permissions['edit own letter_template content'] = array(
    'name' => 'edit own letter_template content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own postcard_template content'.
  $permissions['edit own postcard_template content'] = array(
    'name' => 'edit own postcard_template content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
