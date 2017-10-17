<?php
/**
 * @file
 * reiscout_map_feature.features.inc
 */

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
