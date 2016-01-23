<?php
/**
 * @file
 * property.features.inc
 */

/**
 * Implements hook_views_api().
 */
function property_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function property_node_info() {
  $items = array(
    'property' => array(
      'name' => t('Property'),
      'base' => 'node_content',
      'description' => t('A real property object.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
