<?php

/**
 * @file
 * reiscout_property_commerce_feature.default_field_validation_rules.inc
 */

/**
 * Implements hook_default_field_validation_rule().
 */
function reiscout_property_commerce_feature_default_field_validation_rule() {
  $export = array();

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'Only one product can reference to each property node';
  $rule->name = 'unique_property_nid';
  $rule->field_name = 'field_property';
  $rule->col = 'target_id';
  $rule->entity_type = 'commerce_product';
  $rule->bundle = 'reiscout_property_address_access';
  $rule->validator = 'field_validation_unique_validator';
  $rule->settings = array(
    'data' => 'bundle',
    'per_user' => 0,
    'bypass' => 0,
    'roles' => array(
      1 => 0,
      2 => 0,
      3 => 0,
    ),
    'errors' => 0,
    'condition' => 0,
    'condition_wrapper' => array(
      'condition_field' => '',
      'condition_operator' => 'equals',
      'condition_value' => '',
    ),
  );
  $rule->error_message = 'Property with nid [value] already referenced by product [existing-entity-label] and can\'t be referenced twice.';
  $export['unique_property_nid'] = $rule;

  return $export;
}
