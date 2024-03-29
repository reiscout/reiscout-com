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
  $field_group->identifier = 'group_last_mkt_sale_information|node|property|form';
  $field_group->group_name = 'group_last_mkt_sale_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'children' => array(
      0 => 'field_mortgage_company',
      1 => 'field_last_sale_price',
      2 => 'field_last_sale_date',
    ),
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-last-mkt-sale-information field-group-fieldset',
        'description' => '',
        'id' => '',
        'required_fields' => 1,
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'Last Market Sale Information',
    'weight' => '12',
  );
  $field_groups['group_last_mkt_sale_information|node|property|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_last_mkt_sale_information|node|property|full';
  $field_group->group_name = 'group_last_mkt_sale_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'children' => array(
      0 => 'field_mortgage_company',
      1 => 'field_last_sale_price',
      2 => 'field_last_sale_date',
    ),
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-last-mkt-sale-information field-group-fieldset',
        'description' => '',
        'id' => '',
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'Last Market Sale Information',
    'weight' => '12',
  );
  $field_groups['group_last_mkt_sale_information|node|property|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_list|node|property|form';
  $field_group->group_name = 'group_list';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'children' => array(
      0 => 'field_case_file_date',
      1 => 'field_case_number',
      2 => 'field_list',
      3 => 'field_foreclosure_sale_date',
    ),
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-list field-group-fieldset',
        'description' => '',
        'id' => '',
        'required_fields' => 1,
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'List',
    'weight' => '16',
  );
  $field_groups['group_list|node|property|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_list|node|property|full';
  $field_group->group_name = 'group_list';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'children' => array(
      0 => 'field_case_file_date',
      1 => 'field_case_number',
      2 => 'field_list',
      3 => 'field_foreclosure_sale_date',
    ),
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-list field-group-fieldset',
        'description' => '',
        'id' => '',
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'List',
    'weight' => '17',
  );
  $field_groups['group_list|node|property|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_other_information|node|property|form';
  $field_group->group_name = 'group_other_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'children' => array(
      0 => 'field_repairs_price',
      1 => 'field_arv',
      2 => 'field_under_contract',
      3 => 'field_zillow_page_url',
    ),
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-other-information field-group-fieldset',
        'description' => '',
        'id' => '',
        'required_fields' => 1,
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'Other Information',
    'weight' => '18',
  );
  $field_groups['group_other_information|node|property|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_other_information|node|property|full';
  $field_group->group_name = 'group_other_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'children' => array(
      0 => 'field_repairs_price',
      1 => 'field_arv',
      2 => 'field_under_contract',
      3 => 'field_zillow_page_url',
    ),
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-other-information field-group-fieldset',
        'description' => '',
        'id' => '',
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'Other Information',
    'weight' => '18',
  );
  $field_groups['group_other_information|node|property|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_owner_information|node|property|form';
  $field_group->group_name = 'group_owner_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'children' => array(
      0 => 'field_owner_phone',
      1 => 'field_owner_postal_address',
      2 => 'field_owner_status',
      3 => 'field_last_contacted',
      4 => 'field_lead_status',
    ),
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-owner-information field-group-fieldset',
        'description' => '',
        'id' => '',
        'required_fields' => 1,
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'Owner Information',
    'weight' => '13',
  );
  $field_groups['group_owner_information|node|property|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_owner_information|node|property|full';
  $field_group->group_name = 'group_owner_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'children' => array(
      0 => 'field_owner_phone',
      1 => 'field_owner_postal_address',
      2 => 'field_owner_status',
      3 => 'field_last_contacted',
      4 => 'field_lead_status',
      5 => 'reiscout-mail-buttons',
    ),
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-owner-information field-group-fieldset',
        'description' => '',
        'id' => '',
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'Owner Information',
    'weight' => '13',
  );
  $field_groups['group_owner_information|node|property|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_owner_info|node|property|form';
  $field_group->group_name = 'group_owner_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_property_info';
  $field_group->data = array(
    'children' => array(
      0 => 'field_owner_phone',
      1 => 'field_owner_postal_address',
    ),
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-owner-info field-group-fieldset',
        'description' => '',
        'id' => '',
        'required_fields' => 1,
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'Owner Info',
    'weight' => '14',
  );
  $field_groups['group_owner_info|node|property|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_owner_info|node|property|full';
  $field_group->group_name = 'group_owner_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'full';
  $field_group->parent_name = 'group_property_info';
  $field_group->data = array(
    'children' => array(
      0 => 'field_owner_phone',
      1 => 'field_owner_postal_address',
      2 => 'reiscout-mail-buttons',
    ),
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-owner-info field-group-fieldset',
        'description' => '',
        'id' => '',
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'Owner Info',
    'weight' => '18',
  );
  $field_groups['group_owner_info|node|property|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_property_characteristics|node|property|form';
  $field_group->group_name = 'group_property_characteristics';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'children' => array(
      0 => 'field_bedrooms',
      1 => 'field_year_built',
      2 => 'field_effective_year_built',
      3 => 'field_gross_area',
      4 => 'field_full_baths',
      5 => 'field_half_baths',
      6 => 'field_finished_area',
      7 => 'field_baths',
      8 => 'field_rooms',
    ),
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-property-characteristics field-group-fieldset',
        'description' => '',
        'id' => '',
        'required_fields' => 1,
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'Property Characteristics',
    'weight' => '14',
  );
  $field_groups['group_property_characteristics|node|property|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_property_characteristics|node|property|full';
  $field_group->group_name = 'group_property_characteristics';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'children' => array(
      0 => 'field_bedrooms',
      1 => 'field_year_built',
      2 => 'field_effective_year_built',
      3 => 'field_gross_area',
      4 => 'field_full_baths',
      5 => 'field_half_baths',
      6 => 'field_finished_area',
      7 => 'field_baths',
      8 => 'field_rooms',
    ),
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-property-characteristics field-group-fieldset',
        'description' => '',
        'id' => '',
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'Property Characteristics',
    'weight' => '14',
  );
  $field_groups['group_property_characteristics|node|property|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_property_info|node|property|form';
  $field_group->group_name = 'group_property_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
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
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-property-info field-group-fieldset',
        'description' => '',
        'id' => '',
        'required_fields' => 1,
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'Property Info',
    'weight' => '10',
  );
  $field_groups['group_property_info|node|property|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_property_info|node|property|full';
  $field_group->group_name = 'group_property_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
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
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-property-info field-group-fieldset',
        'description' => '',
        'id' => '',
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'Property Info',
    'weight' => '8',
  );
  $field_groups['group_property_info|node|property|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_site_information|node|property|form';
  $field_group->group_name = 'group_site_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'children' => array(
      0 => 'field_lot_area_acres',
      1 => 'field_zoning',
    ),
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-site-information field-group-fieldset',
        'description' => '',
        'id' => '',
        'required_fields' => 1,
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'Site Information',
    'weight' => '15',
  );
  $field_groups['group_site_information|node|property|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_site_information|node|property|full';
  $field_group->group_name = 'group_site_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'children' => array(
      0 => 'field_lot_area_acres',
      1 => 'field_zoning',
    ),
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-site-information field-group-fieldset',
        'description' => '',
        'id' => '',
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'Site Information',
    'weight' => '15',
  );
  $field_groups['group_site_information|node|property|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_source_information|node|property|form';
  $field_group->group_name = 'group_source_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'children' => array(
      0 => 'field_source',
    ),
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-source-information field-group-fieldset',
        'description' => '',
        'id' => '',
        'required_fields' => 1,
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'Source Information',
    'weight' => '16',
  );
  $field_groups['group_source_information|node|property|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_source_information|node|property|full';
  $field_group->group_name = 'group_source_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'children' => array(
      0 => 'field_source',
    ),
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => 'group-source-information field-group-fieldset',
        'description' => '',
        'id' => '',
      ),
    ),
    'format_type' => 'fieldset',
    'label' => 'Source Information',
    'weight' => '16',
  );
  $field_groups['group_source_information|node|property|full'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Last Market Sale Information');
  t('List');
  t('Other Information');
  t('Owner Info');
  t('Owner Information');
  t('Property Characteristics');
  t('Property Info');
  t('Site Information');
  t('Source Information');

  return $field_groups;
}
