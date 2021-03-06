<?php

/*
 * @file
 * Definition of the PropertyAddressSuggestionMyProperties class.
 */

/**
 * Provides suggestions of address components for properties added by a user.
 */
class PropertyAddressSuggestionMyProperties extends PropertyAddressSuggestion {
  private $uid;

  function __construct($uid) {
    $this->uid = $uid;
  }

  /**
   * Returns a list of ZIP codes whose value starts with $search.
   *
   * Example: '30303'.
   */
  public function getZipCodes($search, $limit = 5) {
    $query = db_select('node', 'n');
    $query->leftJoin('field_data_field_address', 'fa', 'n.nid = fa.entity_id');
    $query
      ->fields('fa', array('field_address_postal_code'))
      ->distinct()
      ->condition('field_address_postal_code', db_like($search) . '%', 'LIKE')
      ->condition('n.type', 'property')
      ->condition('n.uid', $this->uid)
      ->orderBy('field_address_postal_code')
      ->addTag('node_access')
      ->range(0, $limit);

    return $query->execute()->fetchCol();
  }

  /**
   * Returns a list of states whose name starts with $search.
   *
   * Example: 'Georgia'.
   */
  public function getStates($search, $limit = 5) {
    module_load_include('inc', 'addressfield', 'addressfield.administrative_areas');
    $areas = addressfield_get_administrative_areas('US');

    foreach ($areas as $code => $name) {
      if (strtolower($search) != strtolower(substr($name, 0, strlen($search)))) {
        unset($areas[$code]);
      }
    }

    if (!$areas) {
      return FALSE;
    }

    $query = db_select('node', 'n');
    $query->leftJoin('field_data_field_address', 'fa', 'n.nid = fa.entity_id');
    $query
      ->fields('fa', array('field_address_administrative_area'))
      ->distinct()
      ->condition('field_address_administrative_area', array_keys($areas))
      ->condition('n.type', 'property')
      ->condition('n.uid', $this->uid)
      ->orderBy('field_address_administrative_area')
      ->addTag('node_access')
      ->range(0, $limit);
    $states = $query->execute()->fetchCol();

    for ($i = 0, $len = count($states); $i < $len; ++$i) {
      $states[$i] = $areas[$states[$i]];
    }

    return $states;
  }

  /**
   * Returns a list of cities whose name starts with $search.
   *
   * Example: 'Atlanta GA'.
   */
  public function getCities($search, $limit = 5) {
    $query = db_select('node', 'n');
    $query->leftJoin('field_data_field_address', 'fa', 'n.nid = fa.entity_id');
    $query->addExpression("CONCAT(field_address_locality, ' ', field_address_administrative_area)", 'city_state');
    $query
      ->distinct()
      ->condition('field_address_locality', db_like($search) . '%', 'LIKE')
      ->condition('n.type', 'property')
      ->condition('n.uid', $this->uid)
      ->orderBy('city_state')
      ->addTag('node_access')
      ->range(0, $limit);

    return $query->execute()->fetchCol();
  }

  /**
   * Returns a list of streets whose name starts with $search.
   *
   * Example: 'Peachtree St NW, Atlanta GA'.
   */
  public function getStreets($search, $limit = 5) {
    $query = db_select('node', 'n');
    $query->leftJoin('field_data_field_address', 'fa', 'n.nid = fa.entity_id');
    $query->addExpression("CONCAT(TRIM(REGEXP_SUBSTR(field_address_thoroughfare, '[a-z[:space:]]+')), ', ', field_address_locality, ' ', field_address_administrative_area)", 'street_city_state');
    $query
      ->distinct()
      ->condition('field_address_thoroughfare', '^[0-9]*[[:space:]]*' . db_like($search) . '.*', 'RLIKE')
      ->condition('n.type', 'property')
      ->condition('n.uid', $this->uid)
      ->orderBy('street_city_state')
      ->addTag('node_access')
      ->range(0, $limit);

    return $query->execute()->fetchCol();
  }

  /**
   * Returns a list of addresses whose name starts with $search.
   *
   * Example: '49 Lakeshore Drive, Stockbridge GA'.
   */
  public function getAddresses($search, $limit = 5) {
    $query = db_select('node', 'n');
    $query->leftJoin('field_data_field_address', 'fa', 'n.nid = fa.entity_id');
    $query->addExpression("CONCAT(field_address_thoroughfare, ', ', field_address_locality, ' ', field_address_administrative_area)", 'address_city_state');
    $query
      ->distinct()
      ->condition('field_address_thoroughfare', db_like($search) . '%', 'LIKE')
      ->condition('n.type', 'property')
      ->condition('n.uid', $this->uid)
      ->orderBy('address_city_state')
      ->addTag('node_access')
      ->range(0, $limit);

    return $query->execute()->fetchCol();
  }
}
