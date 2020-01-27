<?php

/*
 * @file
 * Definition of Property class.
 */

class Property {
  /**
   * Checks if a user has a property with data obtained from a court case.
   *
   * Given a user id and case number, checks if the user has a property whose
   * data have been obtained from the case.
   */
  static function userHasByCaseNumber(int $uid, string $number): bool {
    $query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'property')
      ->fieldCondition('field_case_number', 'value', $number)
      ->propertyCondition('uid', $uid);

    return $query->count()->execute();
  }

  /**
   * Given a property address and user id, returns the corresponding property.
   */
  static function getByAddressAndUid(stdClass $address, int $uid): ?stdClass {
    $query = new EntityFieldQuery;
    $result = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'property')
      ->fieldCondition('field_address', 'thoroughfare', $address->thoroughfare)
      ->fieldCondition('field_address', 'locality', $address->city)
      ->fieldCondition('field_address', 'administrative_area', $address->state)
      ->propertyCondition('uid', $uid)
      ->execute();

    return isset($result['node']) ? node_load(key($result['node'])) : NULL;
  }

  /**
   * Given a property address, checks if all the required fields are filled out.
   */
  static function isAddressFilledOut(EntityStructureWrapper $address): bool {
    if (!$address->value()) {
      return FALSE;
    }

    return $address->thoroughfare->value()
        && $address->locality->value()
        && $address->administrative_area->value()
        && $address->postal_code->value();
  }

  /**
   * Given an owner's address, checks if all the required fields are filled out.
   */
  static function isOwnerAddressFilledOut(EntityStructureWrapper $address): bool {
    if (!$address->value()) {
      return FALSE;
    }

    $isNameFilledOut = ($address->first_name->value() && $address->last_name->value())
                    || $address->organisation_name->value();

    return $isNameFilledOut
        && $address->thoroughfare->value()
        && $address->locality->value()
        && $address->administrative_area->value()
        && $address->postal_code->value();
  }

  /**
   * Given an owner's address, returns the owner's name.
   */
  static function getOwnerName(EntityStructureWrapper $address): string {
    return $address->organisation_name->value() ? $address->organisation_name->value() : $address->name_line->value();
  }

  /**
   * Given an owner's status, returns its name.
   */
  static function getOwnerStatusName(int $status): string {
    switch ($status) {
      case 1:
        $name = t('Corporate Owner');
        break;
      case 2:
        $name = t('Owner Occupied');
        break;
      case 3:
        $name = t('Non-Owner Occupied');
        break;
      default:
        $name = t('Out-Of-State Owner');
    }

    return $name;
  }

  /**
   * Given the id of a list, returns its name.
   */
  static function getListName(int $list): string {
    switch ($list) {
      case 1:
        $name = t('Dispossessory');
        break;
      default:
        $name = t('Pre-foreclosure');
    }

    return $name;
  }

  /**
   * Given a lead status, returns its name.
   */
  static function getLeadStatusName(int $status): string {
    switch ($status) {
      case 1:
        $name = t('Hot');
        break;
      case 2:
        $name = t('Warm');
        break;
      case 3:
        $name = t('Cold');
        break;
      case 4:
        $name = t('DNC');
        break;
      case 5:
        $name = t('Open');
        break;
      case 6:
        $name = t('Hold');
        break;
      default:
        $name = t('Closed');
    }

    return $name;
  }

  /**
   * Given a PIPS county code, returns its name.
   */
  static function getCountyNameByFipsCode(int $code): string {
    $counties = array(
      13021 => 'Bibb',
      13067 => 'Cobb',
      13089 => 'DeKalb',
      13121 => 'Fulton',
      13135 => 'Gwinnett',
      13151 => 'Henry',
    );

    return $counties[$code] ?? $code;
  }

  /**
   * Given a county name, returns its FIPS code.
   */
  static function getCountyFipsCodeByName(string $name): ?int {
    $counties = array(
      13021 => 'Bibb',
      13067 => 'Cobb',
      13089 => 'DeKalb',
      13121 => 'Fulton',
      13135 => 'Gwinnett',
      13151 => 'Henry',
    );

    $counties = array_map('strtolower', $counties);
    $counties = array_flip($counties);

    return $counties[strtolower($name)] ?? NULL;
  }

  /**
   * Given a user id, returns the list of counties his properties in.
   */
  static function getCountyListByUid(int $uid): ?array {
    $query = db_select('field_data_field_fips_county_code', 'fcc')
      ->distinct();
    $query
      ->join('node', 'n', 'fcc.entity_id = n.nid');
    $query
      ->fields('fcc', array('field_fips_county_code_value'))
      ->condition('uid', $uid);

    if (!$codes = $query->execute()->fetchCol()) {
      return NULL;
    }

    $counties = array();
    foreach ($codes as $code) {
      $counties[$code] = self::getCountyNameByFipsCode($code);
    }

    return $counties;
  }

  /**
   * Given a user id, returns the min and max market values for his properties.
   */
  static function getMinAndMaxMarketValuesByUid(int $uid): ?array {
    $query = db_select('field_data_field_market_value', 'fmv');
    $query
      ->join('node', 'n', 'fmv.entity_id = n.nid');
    $query
      ->addExpression('MIN(field_market_value_value)', 'min');
    $query
      ->addExpression('MAX(field_market_value_value)', 'max');
    $values = $query
      ->condition('uid', $uid)
      ->execute()
      ->fetchAssoc();

    return $values['min'] ? $values : NULL;
  }

  /**
   * Given a user id, returns the min and max numbers of bedrooms for his properties.
   */
  static function getMinAndMaxNumbersOfBedroomsByUid(int $uid): ?array {
    $query = db_select('field_data_field_bedrooms', 'fb');
    $query
      ->join('node', 'n', 'fb.entity_id = n.nid');
    $query
      ->addExpression('MIN(field_bedrooms_value)', 'min');
    $query
      ->addExpression('MAX(field_bedrooms_value)', 'max');
    $values = $query
      ->condition('uid', $uid)
      ->execute()
      ->fetchAssoc();

    return $values['min'] ? $values : NULL;
  }

  /**
   * Given a user id, returns the min and max numbers of bathrooms for his properties.
   */
  static function getMinAndMaxNumbersOfBathroomsByUid(int $uid): ?array {
    $query = db_select('field_data_field_baths', 'fb');
    $query
      ->join('node', 'n', 'fb.entity_id = n.nid');
    $query
      ->addExpression('MIN(field_baths_value)', 'min');
    $query
      ->addExpression('MAX(field_baths_value)', 'max');
    $values = $query
      ->condition('uid', $uid)
      ->execute()
      ->fetchAssoc();

    return $values['min'] ? $values : NULL;
  }

  /**
   * Given a user id, returns the min and max numbers of rooms for his properties.
   */
  static function getMinAndMaxNumbersOfRoomsByUid(int $uid): ?array {
    $query = db_select('field_data_field_rooms', 'fr');
    $query
      ->join('node', 'n', 'fr.entity_id = n.nid');
    $query
      ->addExpression('MIN(field_rooms_value)', 'min');
    $query
      ->addExpression('MAX(field_rooms_value)', 'max');
    $values = $query
      ->condition('uid', $uid)
      ->execute()
      ->fetchAssoc();

    return $values['min'] ? $values : NULL;
  }

  /**
   * Given a user id, returns the min and max years his properties were built in.
   */
  static function getMinAndMaxYearsBuiltByUid(int $uid): ?array {
    $query = db_select('field_data_field_year_built', 'fyb');
    $query
      ->join('node', 'n', 'fyb.entity_id = n.nid');
    $query
      ->addExpression('MIN(field_year_built_value)', 'min');
    $query
      ->addExpression('MAX(field_year_built_value)', 'max');
    $values = $query
      ->condition('uid', $uid)
      ->execute()
      ->fetchAssoc();

    return $values['min'] ? $values : NULL;
  }
}
