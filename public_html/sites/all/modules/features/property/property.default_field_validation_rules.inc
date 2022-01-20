<?php

/**
 * @file
 * property.default_field_validation_rules.inc
 */

/**
 * Implements hook_default_field_validation_rule().
 */
function property_default_field_validation_rule() {
  $export = array();

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'Unique Address';
  $rule->name = 'unique_address';
  $rule->field_name = 'field_address_text';
  $rule->col = 'value';
  $rule->entity_type = 'node';
  $rule->bundle = 'property';
  $rule->validator = 'field_validation_unique_validator';
  $rule->settings = array(
    'bypass' => 0,
    'condition' => 0,
    'condition_wrapper' => array(
      'condition_field' => '',
      'condition_operator' => 'not_equals',
      'condition_value' => '',
    ),
    'data' => 'bundle',
    'errors' => 1,
    'per_user' => 0,
    'roles' => array(
      1 => 0,
      2 => 0,
      3 => 0,
    ),
  );
  $rule->error_message = 'Property with such address already exist. Please select another address.';
  $export['unique_address'] = $rule;

  return $export;
}
