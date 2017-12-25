<?php

/**
 * @file
 * Page callback file for the Reiscout Property module.
 */

/**
 * Page callback: returns an autocomplete suggestion list of cities.
 */
function reiscout_property_address_locality_autocomplete($string) {
  $matches = array();

  $cities = _reiscout_property_get_cities_used_in_property_address($string);
  if ($cities) {
    foreach ($cities as $city) {
      $matches[$city] = check_plain($city);
    }
  }

  drupal_json_output($matches);
}

/**
 * Page callback: returns an autocomplete suggestion list of cities.
 */
function reiscout_property_address_locality_autocomplete_drupalgap() {
  $matches = array();

  $string = isset($_GET['value']) ? check_plain($_GET['value']) : '';

  $cities = _reiscout_property_get_cities_used_in_property_address($string, 5);
  if ($cities) {
    foreach ($cities as $city) {
      $matches[] = array('value' => check_plain($city));
    }
  }

  // We need to set this key, because it will be used in drupalgap;
  // see _theme_autocomplete() function:
  //
  //   var fn = _theme_autocomplete_success_handlers[autocomplete_id];
  //   fn(autocomplete_id, result_items, wrapped, results.view.child);
  $matches['view']['child'] = '';

  drupal_json_output($matches);
}

/**
 * Returns a list of cities that are used as a component of property's address.
 */
function _reiscout_property_get_cities_used_in_property_address($string, $limit = 10) {
  $query = db_select('node', 'n');
  $query->leftJoin('field_data_field_address', 'fa', 'n.nid = fa.entity_id');
  $query
    ->fields('fa', array('field_address_locality'))
    ->distinct()
    ->condition('field_address_locality', '%' . db_like($string) . '%', 'LIKE')
    ->condition('n.type', 'property')
    ->orderBy('field_address_locality')
    ->addTag('node_access')
    ->range(0, $limit);

  return $query->execute()->fetchCol();
}
