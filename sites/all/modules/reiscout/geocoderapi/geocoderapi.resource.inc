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

    return array(
      'address'   => $address->address,
      'accuracy'  => $address->data['geocoder_accuracy'],
      'distance'  => $address->data['distance'],
      'latitude'  => $address->y(),
      'longitude' => $address->x(),
    );
  }
  catch (Exception $e) {
    services_error('Could not proccess geocoding', 500);
  }
}
