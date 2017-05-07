<?php
// $Id$

/**
 * @file
 * Plugin to provide a google reverse geocoder.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Google Reverse Geocoder"),
  'description' => t('Reverse Geocodes via google reverse geocoder'),
  'callback' => 'geocoder_reverse_google',
  'terms_of_service' => 'http://code.google.com/apis/maps/documentation/geocoding/#Limits',
);

/**
 * Process Markup
 */
function geocoder_reverse_google($lat, $long, $options = array()) {
  try {
    geophp_load();

    // See https://developers.google.com/maps/documentation/geocoding/intro#ReverseGeocoding
    // for description of parameters that is used in a request.
    $query = array(
      'latlng' => $lat . ',' . $long,
      'location_type' => 'ROOFTOP',
      'result_type' => 'street_address|premise',
      'language' => 'en',
    );

    if ($google_map_api_key = variable_get('geocoder_apikey_google')) {
      $query['key'] = $google_map_api_key;
    }

    // Build the URL.
    $url = url('https://maps.googleapis.com/maps/api/geocode/json', array('query' => $query));
    $response = drupal_http_request($url);

    if (isset($response->error)) {
      $args = array(
        '@code' => $response->code,
        '@error' => $response->error,
      );
      $msg = t('HTTP request to google API failed.\nCode: @code\nError: @error', $args);
      throw new Exception($msg);
    }

    $data = json_decode($response->data);

    if ($data->status != 'OK') {
      $args = array('@status' => $data->status);
      $msg = t('Google API returned bad status.\nStatus: @status', $args);
      throw new Exception($msg);
    }

    if (empty($data->results)) {
      return FALSE;
    }

    $address = array(
      'location' => $data->results[0]->geometry->location,
      'formatted_address' => $data->results[0]->formatted_address,
      'address_components' => $data->results[0]->address_components,
    );

    return $address;
  }
  catch (Exception $e) {
    watchdog_exception('geocoder', $e);
    return FALSE;
  }
}
