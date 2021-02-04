#!/usr/bin/env drush

/**
 * Updates 'Address' field to make it
 * work via Address Autocomplete widget.
 */
function reiscout_update_address_field() {
  $nids = db_query("SELECT nid
                    FROM {node} n
                    LEFT JOIN {field_data_field_address} fa
                    ON n.nid = fa.entity_id
                    WHERE type = 'property' AND field_address_data = ''
                    LIMIT 0, 70")->fetchCol();
  if (!$nids) {
    exit;
  }

  $transaction = db_transaction();

  foreach ($nids as $nid) {
    $node = node_load($nid);

    if (!empty($node->field_address[LANGUAGE_NONE][0]) && empty($node->field_address[LANGUAGE_NONE][0]['data'])) {
      $address = $node->field_address[LANGUAGE_NONE][0];

      $query = array(
        'address' => $address['thoroughfare'] . ', ' . $address['locality'] . ', ' . $address['administrative_area']. ' ' . $address['postal_code'],
      );
      if ($google_map_api_key = variable_get('geocoder_apikey_google')) {
        $query['key'] = $google_map_api_key;
      }

      $url = url('https://maps.googleapis.com/maps/api/geocode/json', array('query' => $query));
      $response = drupal_http_request($url);

      if (200 == $response->code) {
        $data = json_decode($response->data);
        if (!empty($data->results[0])) {
          $data = array(
            'formatted_address' => $data->results[0]->formatted_address,
            'latitude' => $data->results[0]->geometry->location->lat,
            'longitude' => $data->results[0]->geometry->location->lng,
          );
          $node->field_address[LANGUAGE_NONE][0]['data'] = serialize($data);
          node_save($node);
        }
      }
    }
  }
}

reiscout_update_address_field();
