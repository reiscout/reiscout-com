<?php

/**
 * @file
 * reiscout_property_commerce_feature.features.inc
 */

/**
 * Implements hook_commerce_product_default_types().
 */
function reiscout_property_commerce_feature_commerce_product_default_types() {
  $items = array(
    'reiscout_property_address_access' => array(
      'type' => 'reiscout_property_address_access',
      'name' => 'Property Address Access',
      'description' => 'Reiscout Property Commerce module creates an individual product of this type for each property.
By purchasing the product user own the access to property address and property owner contacts.',
      'help' => '',
      'revision' => 0,
    ),
    'reiscout_property_owner_info' => array(
      'type' => 'reiscout_property_owner_info',
      'name' => 'Owner Info',
      'description' => 'Reiscout Property Commerce module creates an individual product of this type for each property.
Only property submitter able to buy the product.
By purchasing the product property submitter request the Reiscout Team to find and update the property content with property owner info.',
      'help' => '',
      'revision' => 0,
    ),
  );
  return $items;
}

/**
 * Implements hook_ctools_plugin_api().
 */
function reiscout_property_commerce_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "field_validation" && $api == "default_field_validation_rules") {
    return array("version" => "2");
  }
}

/**
 * Implements hook_views_api().
 */
function reiscout_property_commerce_feature_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
