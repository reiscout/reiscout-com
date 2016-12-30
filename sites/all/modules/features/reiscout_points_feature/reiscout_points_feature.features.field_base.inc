<?php
/**
 * @file
 * reiscout_points_feature.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function reiscout_points_feature_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_points_amount'.
  $field_bases['field_points_amount'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_points_amount',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'decimal_separator' => '.',
      'precision' => 10,
      'scale' => 0,
    ),
    'translatable' => 0,
    'type' => 'number_decimal',
  );

  return $field_bases;
}
