<?php
/**
 * @file
 * reiscout_maps_demo_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function reiscout_maps_demo_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function reiscout_maps_demo_feature_node_info() {
  $items = array(
    'demo_map' => array(
      'name' => t('Demo map'),
      'base' => 'node_content',
      'description' => t('Use <em>Demo map</em> for a demo map that will be displayed on the <em>Maps</em> page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
