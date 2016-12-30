<?php
/**
 * @file
 * reiscout_points_feature.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function reiscout_points_feature_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'commerce_product-points_owner-field_points_amount'.
  $field_instances['commerce_product-points_owner-field_points_amount'] = array(
    'bundle' => 'points_owner',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Amount of points granted to user after buying this product.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => '',
        ),
        'type' => 'number_decimal',
        'weight' => 1,
      ),
      'line_item' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'node_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'commerce_product',
    'field_name' => 'field_points_amount',
    'label' => 'Points amount',
    'required' => 1,
    'settings' => array(
      'max' => '',
      'min' => 1,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Amount of points granted to user after buying this product.');
  t('Points amount');

  return $field_instances;
}
