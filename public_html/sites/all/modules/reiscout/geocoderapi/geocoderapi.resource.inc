<?php

/**
 * @file
 * Service's resources callbacks.
 */

function _geocoderapi_action_geocode_reverse($latitude, $longitude, array $options = array()) {
  try {
    $address = geocoder_reverse('google', $latitude, $longitude, $options);

    if (!$address) {
      services_error('Could not detect address', 500);
    }

    return $address;
  }
  catch (Exception $e) {
    services_error('Could not proccess geocoding', 500);
  }
}
