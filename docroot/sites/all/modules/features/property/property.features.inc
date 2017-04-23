<?php
/**
 * @file
 * property.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function property_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "field_validation" && $api == "default_field_validation_rules") {
    return array("version" => "2");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function property_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function property_image_default_styles() {
  $styles = array();

  // Exported image style: mobapp_property_listing.
  $styles['mobapp_property_listing'] = array(
    'label' => 'MobApp Property Listing',
    'effects' => array(
      4 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 320,
          'height' => 320,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: mobapp_property_page.
  $styles['mobapp_property_page'] = array(
    'label' => 'MobApp Property Page',
    'effects' => array(
      5 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 320,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: property_listing.
  $styles['property_listing'] = array(
    'label' => 'Website Property Listing',
    'effects' => array(
      2 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 480,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: property_page.
  $styles['property_page'] = array(
    'label' => 'Website Property Page',
    'effects' => array(
      3 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 650,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
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
      'help' => t('You will be able to change this data later.'),
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
