<?php
/**
 * @file
 * reiscout_points_feature.features.inc
 */

/**
 * Implements hook_commerce_product_default_types().
 */
function reiscout_points_feature_commerce_product_default_types() {
  $items = array(
    'points_owner' => array(
      'type' => 'points_owner',
      'name' => 'Points',
      'description' => 'Commerce product to get paid points.',
      'help' => '',
      'revision' => 0,
    ),
  );
  return $items;
}

/**
 * Implements hook_ctools_plugin_api().
 */
function reiscout_points_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
