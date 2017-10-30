<?php
/**
 * @file
 * reiscout_map_feature.features.inc
 */

/**
 * Implements hook_commerce_product_default_types().
 */
function reiscout_map_feature_commerce_product_default_types() {
  $items = array(
    'city_map_square' => array(
      'type' => 'city_map_square',
      'name' => 'City Square',
      'description' => 'Buying this product user get an access to route data files attached for all map square nodes belongs to the city.',
      'help' => '',
      'revision' => 1,
    ),
    'individual_map_square' => array(
      'type' => 'individual_map_square',
      'name' => 'Individual Square',
      'description' => 'Buying this product user get and access to route data files attached Individual map square node.',
      'help' => 'This product created automatically a one per square node. ',
      'revision' => 0,
    ),
  );
  return $items;
}

/**
 * Implements hook_ctools_plugin_api().
 */
function reiscout_map_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function reiscout_map_feature_node_info() {
  $items = array(
    'map_square' => array(
      'name' => t('Map Square'),
      'base' => 'node_content',
      'description' => t('Map square item.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
