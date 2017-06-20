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
  $field_group->identifier = 'group_owner_info|node|property|form';
  $field_group->group_name = 'group_owner_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_property_info';
  $field_group->data = array(
    'label' => 'Owner Info',
    'weight' => '14',
    'children' => array(
      0 => 'field_owner_phone',
      1 => 'field_owner_postal_address',
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
  $field_group->parent_name = 'group_property_info';
  $field_group->data = array(
    'label' => 'Owner Info',
    'weight' => '18',
    'children' => array(
      0 => 'field_owner_phone',
      1 => 'field_owner_postal_address',
      2 => 'reiscout-mail-buttons',
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
  $field_group->identifier = 'group_property_info|node|property|form';
  $field_group->group_name = 'group_property_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Property Info',
    'weight' => '10',
    'children' => array(
      0 => 'field_bedrooms',
      1 => 'field_mortgage_company',
      2 => 'field_repairs_price',
      3 => 'field_arv',
      4 => 'field_under_contract',
      5 => 'field_ep_calculated',
      6 => 'field_ep_appraised',
      7 => 'field_year_built',
      8 => 'field_effective_year_built',
      9 => 'field_lot_area_acres',
      10 => 'field_assessed_value',
      11 => 'field_last_sale_price',
      12 => 'field_last_sale_date',
      13 => 'field_gross_area',
      14 => 'field_full_baths',
      15 => 'field_half_baths',
      16 => 'field_zoning',
      17 => 'group_owner_info',
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
    'weight' => '8',
    'children' => array(
      0 => 'field_bedrooms',
      1 => 'field_mortgage_company',
      2 => 'field_repairs_price',
      3 => 'field_arv',
      4 => 'field_under_contract',
      5 => 'field_ep_calculated',
      6 => 'field_ep_appraised',
      7 => 'field_year_built',
      8 => 'field_effective_year_built',
      9 => 'field_lot_area_acres',
      10 => 'field_assessed_value',
      11 => 'field_last_sale_price',
      12 => 'field_last_sale_date',
      13 => 'field_gross_area',
      14 => 'field_full_baths',
      15 => 'field_half_baths',
      16 => 'field_zoning',
      17 => 'group_owner_info',
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
