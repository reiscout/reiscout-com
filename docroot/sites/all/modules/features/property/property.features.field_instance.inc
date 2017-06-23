<?php
/**
 * @file
 * property.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function property_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-property-body'.
  $field_instances['node-property-body'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'drupalgap' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 5,
      ),
      'full' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 600,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Notes',
    'required' => 0,
    'settings' => array(
      'display_summary' => 0,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-property-field_address'.
  $field_instances['node-property-field_address'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Enter property address. It will be visible only for users bought the access to this property.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'addressfield',
        'settings' => array(
          'format_handlers' => array(
            0 => 'address',
          ),
          'use_widget_handlers' => 1,
        ),
        'type' => 'addressfield_default',
        'weight' => 19,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'addressfield',
        'settings' => array(
          'format_handlers' => array(
            0 => 'address',
          ),
          'use_widget_handlers' => 1,
        ),
        'type' => 'addressfield_default',
        'weight' => 4,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'addressfield',
        'settings' => array(
          'format_handlers' => array(
            0 => 'address',
          ),
          'use_widget_handlers' => 1,
        ),
        'type' => 'addressfield_default',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_address',
    'label' => 'Address',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'addressfield_autocomplete',
      'settings' => array(
        'available_countries' => array(
          'US' => 'US',
        ),
        'default_country' => 'US',
        'draggable' => 0,
        'format_handlers' => array(
          'address' => 'address',
          'address-hide-country' => 'address-hide-country',
          'address-hide-postal-code' => 0,
          'address-hide-street' => 0,
          'organisation' => 0,
          'name-full' => 0,
          'name-oneline' => 0,
          'address-optional' => 0,
        ),
        'geolocation' => TRUE,
        'html5_geocode' => 0,
        'manual_text' => 'Enter the address manually',
        'map' => 0,
        'restrict_country' => array(),
        'reveal' => 1,
        'reverse_geocode' => 0,
        'types' => 'geocode',
        'visible_markers' => 0,
      ),
      'type' => 'addressfield_autocomplete',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-property-field_address_access_product'.
  $field_instances['node-property-field_address_access_product'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'commerce_cart',
        'settings' => array(
          'combine' => TRUE,
          'default_quantity' => 1,
          'line_item_type' => 'product',
          'show_quantity' => FALSE,
          'show_single_product_attributes' => FALSE,
        ),
        'type' => 'commerce_cart_add_to_cart_form',
        'weight' => 17,
      ),
      'drupalgap' => array(
        'label' => 'hidden',
        'module' => 'commerce_cart',
        'settings' => array(
          'combine' => TRUE,
          'default_quantity' => 1,
          'line_item_type' => 'product',
          'show_quantity' => FALSE,
          'show_single_product_attributes' => FALSE,
        ),
        'type' => 'commerce_cart_add_to_cart_form',
        'weight' => 0,
      ),
      'full' => array(
        'label' => 'hidden',
        'module' => 'commerce_cart',
        'settings' => array(
          'combine' => TRUE,
          'default_quantity' => 1,
          'line_item_type' => 'product',
          'show_quantity' => FALSE,
          'show_single_product_attributes' => FALSE,
        ),
        'type' => 'commerce_cart_add_to_cart_form',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_address_access_product',
    'label' => 'Buy Address Access',
    'required' => FALSE,
    'settings' => array(
      'field_injection' => 1,
      'referenceable_types' => array(
        'product' => 0,
        'reiscout_property_address_access' => 'reiscout_property_address_access',
        'reiscout_property_owner_info' => 0,
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'commerce_product_reference',
      'settings' => array(),
      'type' => 'commerce_product_reference_hidden',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'node-property-field_arv'.
  $field_instances['node-property-field_arv'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The estimate of a property’s value after all repairs and upgrades are completed',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 15,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 23,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 31,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_arv',
    'label' => 'ARV (estimated)',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '$',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 18,
    ),
  );

  // Exported field_instance: 'node-property-field_assessed_value'.
  $field_instances['node-property-field_assessed_value'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Combined value of the assessed land and improvements of the subject property',
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
        'weight' => 28,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => '',
        ),
        'type' => 'number_decimal',
        'weight' => 6,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => '',
        ),
        'type' => 'number_decimal',
        'weight' => 7,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_assessed_value',
    'label' => 'Assessed Value',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '$',
      'suffix' => 'k',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-property-field_bedrooms'.
  $field_instances['node-property-field_bedrooms'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Total number of bedroom contained in the subject property',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 7,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 15,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 23,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bedrooms',
    'label' => 'Bedrooms',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 17,
    ),
  );

  // Exported field_instance: 'node-property-field_data_locked'.
  $field_instances['node-property-field_data_locked'] = array(
    'bundle' => 'property',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Turn on to prevent user from editing the property data.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 23,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 29,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 16,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_data_locked',
    'label' => 'Lock data',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 16,
    ),
  );

  // Exported field_instance: 'node-property-field_data_quality_tags'.
  $field_instances['node-property-field_data_quality_tags'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 35,
      ),
      'drupalgap' => array(
        'label' => 'hidden',
        'module' => 'entityreference',
        'settings' => array(
          'links' => TRUE,
          'use_content_language' => TRUE,
          'view_mode' => 'default',
        ),
        'type' => 'entityreference_entity_view',
        'weight' => 3,
      ),
      'full' => array(
        'label' => 'hidden',
        'module' => 'entityreference',
        'settings' => array(
          'links' => TRUE,
          'use_content_language' => TRUE,
          'view_mode' => 'default',
        ),
        'type' => 'entityreference_entity_view',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_data_quality_tags',
    'label' => 'Data Quality Tags',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 15,
    ),
  );

  // Exported field_instance: 'node-property-field_effective_year_built'.
  $field_instances['node-property-field_effective_year_built'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The year that a building on the property was significantly improved or remodeled',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 26,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 19,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 28,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_effective_year_built',
    'label' => 'Effective Year Built',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => 1900,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 21,
    ),
  );

  // Exported field_instance: 'node-property-field_ep_appraised'.
  $field_instances['node-property-field_ep_appraised'] = array(
    'bundle' => 'property',
    'default_value' => array(
      0 => array(
        'value' => 60,
      ),
    ),
    'deleted' => 0,
    'description' => '',
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
        'weight' => 21,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => '',
        ),
        'type' => 'number_decimal',
        'weight' => 7,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => '',
        ),
        'type' => 'number_decimal',
        'weight' => 9,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ep_appraised',
    'label' => 'Equity Percentage Estimate (appraised)',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '%',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-property-field_ep_calculated'.
  $field_instances['node-property-field_ep_calculated'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
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
        'weight' => 20,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => '',
        ),
        'type' => 'number_decimal',
        'weight' => 8,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => '',
        ),
        'type' => 'number_decimal',
        'weight' => 8,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ep_calculated',
    'label' => 'Equity Percentage Estimate',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '%',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-property-field_full_baths'.
  $field_instances['node-property-field_full_baths'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Total number of full baths on the property',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 32,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 16,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 24,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_full_baths',
    'label' => 'Full Baths',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 18,
    ),
  );

  // Exported field_instance: 'node-property-field_geo_position'.
  $field_instances['node-property-field_geo_position'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Your current location (determined automatically)',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'geofield',
        'settings' => array(
          'data' => 'full',
        ),
        'type' => 'geofield_wkt',
        'weight' => 3,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 30,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 18,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_geo_position',
    'label' => 'Position',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'geofield',
      'settings' => array(
        'html5_geolocation' => 0,
      ),
      'type' => 'geofield_latlon',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-property-field_gross_area'.
  $field_instances['node-property-field_gross_area'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Total living area square footage including unfinished area',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 31,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 14,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 22,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_gross_area',
    'label' => 'Gross Area',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => 'sq ft',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 16,
    ),
  );

  // Exported field_instance: 'node-property-field_half_baths'.
  $field_instances['node-property-field_half_baths'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Total number of half baths on the property',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 33,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 17,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 25,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_half_baths',
    'label' => 'Half Baths',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 19,
    ),
  );

  // Exported field_instance: 'node-property-field_image'.
  $field_instances['node-property-field_image'] = array(
    'bundle' => 'property',
    'deleted' => 0,
    'description' => 'Upload property photo. ',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 2,
      ),
      'drupalgap' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'medium',
        ),
        'type' => 'image',
        'weight' => 1,
      ),
      'full' => array(
        'label' => 'hidden',
        'module' => 'colorbox',
        'settings' => array(
          'colorbox_caption' => 'auto',
          'colorbox_caption_custom' => '',
          'colorbox_gallery' => 'post',
          'colorbox_gallery_custom' => '',
          'colorbox_image_style' => 'large',
          'colorbox_multivalue_index' => NULL,
          'colorbox_node_style' => 'medium',
          'colorbox_node_style_first' => '',
        ),
        'type' => 'colorbox',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_image',
    'label' => 'Photo',
    'required' => 1,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => 'properties',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '12 MB',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-property-field_last_sale_date'.
  $field_instances['node-property-field_last_sale_date'] = array(
    'bundle' => 'property',
    'deleted' => 0,
    'description' => 'Date of most recent subject property sale',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => FALSE,
        ),
        'type' => 'date_default',
        'weight' => 30,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'short',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => 0,
        ),
        'type' => 'date_default',
        'weight' => 10,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'short',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => 0,
        ),
        'type' => 'date_default',
        'weight' => 11,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_last_sale_date',
    'label' => 'Last Sale Date',
    'required' => 0,
    'settings' => array(
      'default_value' => 'blank',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 15,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'no_fieldset' => 1,
        'text_parts' => array(),
        'year_range' => '1900:+0',
      ),
      'type' => 'date_popup',
      'weight' => 14,
    ),
  );

  // Exported field_instance: 'node-property-field_last_sale_price'.
  $field_instances['node-property-field_last_sale_price'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Price of the sale as depicted on the recorded sales transaction',
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
        'weight' => 29,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => '',
        ),
        'type' => 'number_decimal',
        'weight' => 9,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => '',
        ),
        'type' => 'number_decimal',
        'weight' => 10,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_last_sale_price',
    'label' => 'Last Sale Price',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '$',
      'suffix' => 'k',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 13,
    ),
  );

  // Exported field_instance: 'node-property-field_lot_area_acres'.
  $field_instances['node-property-field_lot_area_acres'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Total land lot area in acres',
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
        'weight' => 27,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => '',
        ),
        'type' => 'number_decimal',
        'weight' => 20,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => '',
        ),
        'type' => 'number_decimal',
        'weight' => 28,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lot_area_acres',
    'label' => 'Lot Area',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => 'ac',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 17,
    ),
  );

  // Exported field_instance: 'node-property-field_mortgage_company'.
  $field_instances['node-property-field_mortgage_company'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The name of the lender who grants the first mortgage on a property',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 13,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 11,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 13,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_mortgage_company',
    'label' => 'Mortgage Company',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 15,
    ),
  );

  // Exported field_instance: 'node-property-field_owner_phone'.
  $field_instances['node-property-field_owner_phone'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 5,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 13,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 23,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_owner_phone',
    'label' => 'Owner Phone',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'node-property-field_owner_postal_address'.
  $field_instances['node-property-field_owner_postal_address'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'addressfield',
        'settings' => array(
          'format_handlers' => array(
            0 => 'address',
          ),
          'use_widget_handlers' => 1,
        ),
        'type' => 'addressfield_default',
        'weight' => 4,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'addressfield',
        'settings' => array(
          'format_handlers' => array(
            0 => 'address',
          ),
          'use_widget_handlers' => 1,
        ),
        'type' => 'addressfield_default',
        'weight' => 12,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'addressfield',
        'settings' => array(
          'format_handlers' => array(
            0 => 'address',
          ),
          'use_widget_handlers' => 1,
        ),
        'type' => 'addressfield_default',
        'weight' => 21,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_owner_postal_address',
    'label' => 'Owner Address',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'addressfield',
      'settings' => array(
        'available_countries' => array(
          'US' => 'US',
        ),
        'default_country' => 'US',
        'format_handlers' => array(
          'address' => 'address',
          'address-hide-country' => 'address-hide-country',
          'name-oneline' => 'name-oneline',
          'address-optional' => 'address-optional',
          'address-hide-postal-code' => 0,
          'address-hide-street' => 0,
          'organisation' => 0,
          'name-full' => 0,
        ),
      ),
      'type' => 'addressfield_standard',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'node-property-field_place_on_marketplace'.
  $field_instances['node-property-field_place_on_marketplace'] = array(
    'bundle' => 'property',
    'default_value' => array(
      0 => array(
        'value' => 1,
      ),
    ),
    'deleted' => 0,
    'description' => 'Turn on to make this lead available for all the other users.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 22,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 28,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 15,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_place_on_marketplace',
    'label' => 'Place this lead on the marketplace',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-property-field_repairs_price'.
  $field_instances['node-property-field_repairs_price'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 14,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 22,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 30,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_repairs_price',
    'label' => 'Repairs (estimated)',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '$',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 17,
    ),
  );

  // Exported field_instance: 'node-property-field_under_contract'.
  $field_instances['node-property-field_under_contract'] = array(
    'bundle' => 'property',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Turn on if you have already made a contract to buy with the property owner',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 16,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 24,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 32,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_under_contract',
    'label' => 'Under Contract',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 19,
    ),
  );

  // Exported field_instance: 'node-property-field_year_built'.
  $field_instances['node-property-field_year_built'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The year that a building on the property was originally constructed',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 25,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 18,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 26,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_year_built',
    'label' => 'Year Built',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => 1900,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 20,
    ),
  );

  // Exported field_instance: 'node-property-field_zoning'.
  $field_instances['node-property-field_zoning'] = array(
    'bundle' => 'property',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The zoning classification of the subject property',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 34,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 21,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 29,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_zoning',
    'label' => 'Zoning',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 18,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('ARV (estimated)');
  t('Address');
  t('Assessed Value');
  t('Bedrooms');
  t('Buy Address Access');
  t('Combined value of the assessed land and improvements of the subject property');
  t('Data Quality Tags');
  t('Date of most recent subject property sale');
  t('Effective Year Built');
  t('Enter property address. It will be visible only for users bought the access to this property.');
  t('Equity Percentage Estimate');
  t('Equity Percentage Estimate (appraised)');
  t('Full Baths');
  t('Gross Area');
  t('Half Baths');
  t('Last Sale Date');
  t('Last Sale Price');
  t('Lock data');
  t('Lot Area');
  t('Mortgage Company');
  t('Notes');
  t('Owner Address');
  t('Owner Phone');
  t('Photo');
  t('Place this lead on the marketplace');
  t('Position');
  t('Price of the sale as depicted on the recorded sales transaction');
  t('Repairs (estimated)');
  t('The estimate of a property’s value after all repairs and upgrades are completed');
  t('The name of the lender who grants the first mortgage on a property');
  t('The year that a building on the property was originally constructed');
  t('The year that a building on the property was significantly improved or remodeled');
  t('The zoning classification of the subject property');
  t('Total land lot area in acres');
  t('Total living area square footage including unfinished area');
  t('Total number of bedroom contained in the subject property');
  t('Total number of full baths on the property');
  t('Total number of half baths on the property');
  t('Turn on if you have already made a contract to buy with the property owner');
  t('Turn on to make this lead available for all the other users.');
  t('Turn on to prevent user from editing the property data.');
  t('Under Contract');
  t('Upload property photo. ');
  t('Year Built');
  t('Your current location (determined automatically)');
  t('Zoning');

  return $field_instances;
}
