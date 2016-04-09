<?php
/**
 * @file
 * property.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function property_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_owner_info|node|property|drupalgap';
  $field_group->group_name = 'group_owner_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'drupalgap';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Owner Info',
    'weight' => '17',
    'children' => array(
      0 => 'field_owner_fname',
      1 => 'field_owner_lname',
      2 => 'field_owner_address',
      3 => 'field_owner_phone',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-owner-info field-group-fieldset',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_owner_info|node|property|drupalgap'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_owner_info|node|property|form';
  $field_group->group_name = 'group_owner_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Owner Info',
    'weight' => '7',
    'children' => array(
      0 => 'field_owner_fname',
      1 => 'field_owner_lname',
      2 => 'field_owner_address',
      3 => 'field_owner_phone',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-owner-info field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_owner_info|node|property|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_owner_info|node|property|full';
  $field_group->group_name = 'group_owner_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Owner Info',
    'weight' => '17',
    'children' => array(
      0 => 'field_owner_fname',
      1 => 'field_owner_lname',
      2 => 'field_owner_address',
      3 => 'field_owner_phone',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-owner-info field-group-fieldset',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_owner_info|node|property|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_property_info|node|property|drupalgap';
  $field_group->group_name = 'group_property_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'drupalgap';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Property Info',
    'weight' => '5',
    'children' => array(
      0 => 'field_size',
      1 => 'field_bedrooms',
      2 => 'field_bathrooms',
      3 => 'field_lot_size',
      4 => 'field_last_purchase_price',
      5 => 'field_last_purchase_time',
      6 => 'field_assessed_value',
      7 => 'field_mortgage_company',
      8 => 'field_repairs_price',
      9 => 'field_arv',
      10 => 'field_under_contract',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-property-info field-group-fieldset',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_property_info|node|property|drupalgap'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_property_info|node|property|form';
  $field_group->group_name = 'group_property_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Property Info',
    'weight' => '12',
    'children' => array(
      0 => 'field_size',
      1 => 'field_bedrooms',
      2 => 'field_bathrooms',
      3 => 'field_lot_size',
      4 => 'field_last_purchase_price',
      5 => 'field_last_purchase_time',
      6 => 'field_assessed_value',
      7 => 'field_mortgage_company',
      8 => 'field_repairs_price',
      9 => 'field_arv',
      10 => 'field_under_contract',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-property-info field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_property_info|node|property|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_property_info|node|property|full';
  $field_group->group_name = 'group_property_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Property Info',
    'weight' => '5',
    'children' => array(
      0 => 'field_size',
      1 => 'field_bedrooms',
      2 => 'field_bathrooms',
      3 => 'field_lot_size',
      4 => 'field_last_purchase_price',
      5 => 'field_last_purchase_time',
      6 => 'field_assessed_value',
      7 => 'field_mortgage_company',
      8 => 'field_repairs_price',
      9 => 'field_arv',
      10 => 'field_under_contract',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-property-info field-group-fieldset',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_property_info|node|property|full'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Owner Info');
  t('Property Info');

  return $field_groups;
}
