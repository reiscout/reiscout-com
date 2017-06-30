<?php

/**
 * @file
 * Page callback file for the Reiscout Property module.
 */

/**
 * Page callback: returns a Connect2Data info for a given property.
 */
function reiscout_property_get_c2d_report_page($nid) {
  // Make a request to the Connect2Data API to get full info about property
  if (!$report = _reiscout_property_get_c2d_report_by_nid($nid, 'c2d_report_page')) {
    $message = t('An error occurred while requesting the information about property.');
    drupal_set_message($message, 'error');
    return t('No data');
  }

  // Return data as a parsed object in a text plain file
  $data = print_r($report, TRUE);
  if ($file_uri = file_unmanaged_save_data($data)) {
    $headers = array(
      'Cache-Control' => 'private',
      'Content-Type' => 'text/plain',
      'Content-Disposition' => 'attachment; filename=connect2data.txt',
      'Content-Length' => filesize($file_uri),
    );
    file_transfer($file_uri, $headers);
  }
}

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
