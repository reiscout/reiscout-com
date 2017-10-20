<?php
/**
 * @file
 * reiscout_maps_demo_feature.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function reiscout_maps_demo_feature_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_demo_map_image'.
  $field_bases['field_demo_map_image'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_demo_map_image',
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => 0,
    'module' => 'image',
    'settings' => array(
      'default_image' => 0,
      'uri_scheme' => 'public',
    ),
    'translatable' => 0,
    'type' => 'image',
  );

  // Exported field_base: 'field_demo_map_location'.
  $field_bases['field_demo_map_location'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_demo_map_location',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'addressfield',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'addressfield',
  );

  return $field_bases;
}
