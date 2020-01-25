<?php

/*
 * @file
 * Definition of PropertyTableForm class.
 */

class PropertyTableForm {
  const PER_PAGE = 15;

  /**
   * Builds and attaches the filters to the Property Table Form.
   */
  static function attachFilters(array &$form): void {
    global $user;

    $filters = self::getFilters();

    $form['filters'] = array(
      '#type' => 'fieldset',
      '#title' => t('Show only properties where'),
    );

    $form['filters']['list'] = array(
      '#type' => 'radios',
      '#title' => t('List'),
      '#options' => array(
        0 => t('All'),
        1 => t('Dispossessory'),
      ),
      '#default_value' => $filters['list'] ?? 0,
    );

    $form['filters']['case_file_date_from'] = array(
      '#type' => 'date_popup',
      '#title' => t('Case File Date From'),
      '#date_format' => 'm/d/Y',
      '#date_year_range' => '2010:0',
      '#date_label_position' => 'invisible',
      '#default_value' => $filters['case_file_date_from'] ?? '',
      '#states' => array(
        'visible' => array(':input[name="list"]' => array('value' => 1)),
      ),
    );

    $form['filters']['case_file_date_to'] = array(
      '#type' => 'date_popup',
      '#title' => t('Case File Date To'),
      '#date_format' => 'm/d/Y',
      '#date_year_range' => '2010:0',
      '#date_label_position' => 'invisible',
      '#default_value' => $filters['case_file_date_to'] ?? '',
      '#states' => array(
        'visible' => array(':input[name="list"]' => array('value' => 1)),
      ),
    );

    $form['filters']['hide_sold_after_case_file_date'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide properties sold after Case File Date'),
      '#default_value' => $filters['hide_sold_after_case_file_date'] ?? 0,
      '#states' => array(
        'visible' => array(':input[name="list"]' => array('value' => 1)),
      ),
    );

    if ($counties = Property::getCountyListByUid($user->uid)) {
      $form['filters']['county'] = array(
        '#type' => 'select',
        '#title' => t('County'),
        '#options' => array(
          0 => t('Any'),
        ) + $counties,
        '#default_value' => $filters['county'] ?? 0,
      );
    }

    $form['filters']['owner_status'] = array(
      '#type' => 'select',
      '#title' => t('Owner Status'),
      '#options' => array(
        0 => t('Any'),
        1 => t('Corporate Owner'),
        5 => t('Individual Owner'),
        2 => t('Owner Occupied'),
        3 => t('Non-Owner Occupied'),
        4 => t('Out-Of-State Owner'),
      ),
      '#default_value' => $filters['owner_status'] ?? 0,
    );

    $form['filters']['phone'] = array(
      '#type' => 'select',
      '#title' => t('Phone'),
      '#options' => array(
        0 => t('Any'),
        1 => t('Not in DNC'),
        2 => t('In DNC'),
      ),
      '#default_value' => $filters['phone'] ?? 0,
    );

    $form['filters']['last_contacted_from'] = array(
      '#type' => 'date_popup',
      '#title' => t('Last Contacted From'),
      '#date_format' => 'm/d/Y',
      '#date_year_range' => '2017:0',
      '#date_label_position' => 'invisible',
      '#default_value' => $filters['last_contacted_from'] ?? '',
    );

    $form['filters']['last_contacted_to'] = array(
      '#type' => 'date_popup',
      '#title' => t('Last Contacted To'),
      '#date_format' => 'm/d/Y',
      '#date_year_range' => '2017:0',
      '#date_label_position' => 'invisible',
      '#default_value' => $filters['last_contacted_to'] ?? '',
    );

    if ($marketValues = Property::getMinAndMaxMarketValuesByUid($user->uid)) {
      if ($marketValues['min'] != $marketValues['max']) {
        $min = intval($marketValues['min']) * 1000;
        $max = ceil($marketValues['max']) * 1000;

        $form['filters']['market_value_from'] = array(
          '#type' => 'select',
          '#title' => t('Market Value >='),
          '#options' => array(
            '' => '',
          ) + self::genPriceOptions($min, $max - 1000, 1000, 10000),
          '#default_value' => $filters['market_value_from'] ?? '',
          '#prefix' => '<div id="filters-market-value">',
        );

        $form['filters']['market_value_to'] = array(
          '#type' => 'select',
          '#title' => t('Market Value <='),
          '#options' => array(
            '' => '',
          ) + self::genPriceOptions($min + 1000, $max, 1000, 10000),
          '#default_value' => $filters['market_value_to'] ?? '',
          '#suffix' => '</div>',
        );
      }
    }

    if ($bedrooms = Property::getMinAndMaxNumbersOfBedroomsByUid($user->uid)) {
      if ($bedrooms['min'] != $bedrooms['max']) {
        $form['filters']['beds'] = array(
          '#type' => 'select',
          '#title' => t('Beds'),
          '#options' => array(
            '' => '',
          ) + self::genIntOptions($bedrooms['min'], $bedrooms['max'], 1),
          '#default_value' => $filters['beds'] ?? '',
          '#prefix' => '<div id="filters-beds">',
        );

        $form['filters']['beds_from'] = array(
          '#type' => 'select',
          '#title' => t('Beds >='),
          '#options' => array(
            '' => '',
          ) + self::genIntOptions($bedrooms['min'], $bedrooms['max'] - 1, 1),
          '#default_value' => $filters['beds_from'] ?? '',
        );

        $form['filters']['beds_to'] = array(
          '#type' => 'select',
          '#title' => t('Beds <='),
          '#options' => array(
            '' => '',
          ) + self::genIntOptions($bedrooms['min'] + 1, $bedrooms['max'], 1),
          '#default_value' => $filters['beds_to'] ?? '',
          '#suffix' => '</div>',
        );
      }
    }

    if ($bathrooms = Property::getMinAndMaxNumbersOfBathroomsByUid($user->uid)) {
      if ($bathrooms['min'] != $bathrooms['max']) {
        $form['filters']['baths'] = array(
          '#type' => 'select',
          '#title' => t('Baths'),
          '#options' => array(
            '' => '',
          ) + self::genFloatOptions($bathrooms['min'], $bathrooms['max'], 0.5),
          '#default_value' => $filters['baths'] ?? '',
          '#prefix' => '<div id="filters-baths">',
        );

        $form['filters']['baths_from'] = array(
          '#type' => 'select',
          '#title' => t('Baths >='),
          '#options' => array(
            '' => '',
          ) + self::genFloatOptions($bathrooms['min'], $bathrooms['max'] - 0.5, 0.5),
          '#default_value' => $filters['baths_from'] ?? '',
        );

        $form['filters']['baths_to'] = array(
          '#type' => 'select',
          '#title' => t('Baths <='),
          '#options' => array(
            '' => '',
          ) + self::genFloatOptions($bathrooms['min'] + 0.5, $bathrooms['max'], 0.5),
          '#default_value' => $filters['baths_to'] ?? '',
          '#suffix' => '</div>',
        );
      }
    }

    if ($rooms = Property::getMinAndMaxNumbersOfRoomsByUid($user->uid)) {
      if ($rooms['min'] != $rooms['max']) {
        $form['filters']['rooms'] = array(
          '#type' => 'select',
          '#title' => t('Rooms'),
          '#options' => array(
            '' => '',
          ) + self::genIntOptions($rooms['min'], $rooms['max'], 1),
          '#default_value' => $filters['rooms'] ?? '',
          '#prefix' => '<div id="filters-rooms">',
        );

        $form['filters']['rooms_from'] = array(
          '#type' => 'select',
          '#title' => t('Rooms >='),
          '#options' => array(
            '' => '',
          ) + self::genIntOptions($rooms['min'], $rooms['max'] - 1, 1),
          '#default_value' => $filters['rooms_from'] ?? '',
        );

        $form['filters']['rooms_to'] = array(
          '#type' => 'select',
          '#title' => t('Rooms <='),
          '#options' => array(
            '' => '',
          ) + self::genIntOptions($rooms['min'] + 1, $rooms['max'], 1),
          '#default_value' => $filters['rooms_to'] ?? '',
          '#suffix' => '</div>',
        );
      }
    }

    if ($yearsBuilt = Property::getMinAndMaxYearsBuiltByUid($user->uid)) {
      if ($yearsBuilt['min'] != $yearsBuilt['max']) {
        $form['filters']['built_from'] = array(
          '#type' => 'select',
          '#title' => t('Built >='),
          '#options' => array(
            '' => '',
          ) + self::genIntOptions($yearsBuilt['min'], $yearsBuilt['max'] - 1, 1),
          '#default_value' => $filters['built_from'] ?? '',
          '#prefix' => '<div id="filters-built">',
        );

        $form['filters']['built_to'] = array(
          '#type' => 'select',
          '#title' => t('Built <='),
          '#options' => array(
            '' => '',
          ) + self::genIntOptions($yearsBuilt['min'] + 1, $yearsBuilt['max'], 1),
          '#default_value' => $filters['built_to'] ?? '',
          '#suffix' => '</div>',
        );
      }
    }

    $form['filters']['actions'] = array(
      '#type' => 'actions',
    );

    $form['filters']['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Filter'),
    );

    if ($filters) {
      $form['filters']['actions']['reset'] = array(
        '#type' => 'submit',
        '#value' => t('Reset'),
      );
    }
  }

  /**
   * Builds and attaches info about showing rows to the Property Table Form.
   */
  static function attachShowingRowsInfo(array &$form): void {
    $page = isset($_GET['page']) ? $_GET['page'] + 1 : 1;
    $cnt = self::getPropertyListCnt();
    $to = $page * self::PER_PAGE;

    $t_args = array(
      '!from' => ($page - 1) * self::PER_PAGE + 1,
      '!to' => $cnt >= $to ? $to : $cnt,
      '!total' => $cnt,
    );

    $form['statistics'] = array(
      '#prefix' => '<div id="showing-rows-info">',
      '#markup' => t('Showing rows !from - !to (!total total)', $t_args),
      '#suffix' => '</div>',
    );
  }

  /**
   * Builds and attaches the property list to the Property Table Form.
   */
  static function attachPropertyList(array &$form): void {
    $header = array(
      t('Address'),
      array(
        'data' => t('Owner Info'),
        'id' => 'owner-info',
      ),
      array(
        'data' => t('Market Value'),
        'field' => 'field_market_value',
        'sort' => 'desc',
      ),
      array(
        'data' => t('Last Sold Date'),
        'field' => 'field_last_sale_date',
      ),
      array(
        'data' => t('Beds'),
        'field' => 'field_bedrooms',
      ),
      array(
        'data' => t('Baths'),
        'field' => 'field_baths',
      ),
      array(
        'data' => t('Rooms'),
        'field' => 'field_rooms',
      ),
      array(
        'data' => t('Finished sqft'),
        'field' => 'field_finished_area',
      ),
      array(
        'data' => t('Built'),
        'field' => 'field_year_built',
      ),
    );

    $filters = self::getFilters();

    if (isset($filters['list']) && 1 == $filters['list']) {
      $header[] = array(
        'data' => t('Case File Date'),
        'field' => 'field_case_file_date',
      );
    }
    else {
      $header[] = t('List');
    }

    $rows = array();
    if ($properties = self::getPropertyList($header)) {
      $form['#attached']['js'][] = array(
        'type' => 'setting',
        'data' => array(
          'property' => array(
            'field_lead_status_allowed_values' => field_info_field('field_lead_status')['settings']['allowed_values'],
          ),
        ),
      );

      $form['#attached']['library'][] = array('system', 'ui.dialog');

      $form['jquery_dialog_message_property_deleted'] = array(
        '#markup' => '<div id="jquery-dialog-message-property-deleted" title="Property does not exist">
                         The property was deleted.
                      </div>',
      );

      $form['jquery_dialog_message_403'] = array(
        '#markup' => '<div id="jquery-dialog-message-403" title="Please log in">
                         You logged out.<br/>Please <a href="/user" target="_blank">log in</a> again.
                      </div>',
      );

      foreach ($properties as $property) {
        $property = entity_metadata_wrapper('node', $property);

        $address = $property->field_address->thoroughfare->value() . ', '
                 . $property->field_address->locality->value() . ', ';

        if ($property->field_fips_county_code->value()) {
          $address .= Property::getCountyNameByFipsCode($property->field_fips_county_code->value()) . ', ';
        }

        $address .= $property->field_address->administrative_area->value() . ' '
                  . $property->field_address->postal_code->value();

        $ownerInfo = '';

        if (Property::isOwnerAddressFilledOut($property->field_owner_postal_address)) {
          if ($property->field_owner_status->value()) {
            $ownerInfo .= '<div class="owner-status">'
                        . Property::getOwnerStatusName($property->field_owner_status->value())
                        . '</div>';
          }

          $ownerInfo .= '<div class="owner-name">'
                      . Property::getOwnerName($property->field_owner_postal_address)
                      . '</div>';

          $ownerInfo .= '<div class="owner-address">'
                      . $property->field_owner_postal_address->thoroughfare->value() . ', '
                      . $property->field_owner_postal_address->locality->value() . ', '
                      . $property->field_owner_postal_address->administrative_area->value() . ' '
                      . $property->field_owner_postal_address->postal_code->value()
                      . '</div>';

          if ($numbers = $property->field_owner_phone->value()) {
            $ownerInfo .= '<div class="owner-phones">';
            foreach ($numbers as $number) {
              $ownerInfo .= '<div class="owner-phone' . (DncRegistry::contains($number) ? ' in-dnc' : '') . '">'
                          . l($number, 'tel:' . DncRegistry::formatNumber($number))
                          . '</div>';
            }
            $ownerInfo .= '</div>';
          }

          $lastContacted = $property->field_last_contacted->value() ?
                           date('M j, Y', $property->field_last_contacted->value()) :
                           t('never');

          $leadStatus = $property->field_lead_status->value() ?
                        Property::getLeadStatusName($property->field_lead_status->value()) :
                        t('New');

          $ownerInfo .= '<div id="crm-fields-' . $property->nid->value(). '" class="crm-fields">
                            <div class="field last-contacted">
                               <div class="title">Last Contacted:</div>
                               <div class="value">' . $lastContacted . '</div>
                               <div class="icon edit"></div>
                            </div>
                            <div class="field lead-status">
                               <div class="title">Lead Status:</div>
                               <div class="value">' . $leadStatus . '</div>
                               <div class="icon edit"></div>
                            </div>
                         </div>';
        }

        $lastSold = '';

        if ($property->field_last_sale_date->value()) {
          $lastSold .= date('M j, Y', $property->field_last_sale_date->value());

          if ($property->field_last_sale_price->value()) {
            $lastSold .= ' for $' . number_format($property->field_last_sale_price->value() * 1000);
          }
        }

        if (isset($filters['list']) && 1 == $filters['list']) {
          $caseFileDate = date('m/d/Y', $property->field_case_file_date->value());
        }
        else {
          $listName = $property->field_list->value() ? Property::getListName($property->field_list->value()) : '';
        }

        $rows[] = array(
          l($address, 'node/' . $property->nid->value()),
          $ownerInfo,
          $property->field_market_value->value() ? '$' . number_format($property->field_market_value->value() * 1000) : '',
          $lastSold,
          $property->field_bedrooms->value(),
          $property->field_baths->value(),
          $property->field_rooms->value(),
          $property->field_finished_area->value() ? number_format($property->field_finished_area->value()) : '',
          $property->field_year_built->value(),
          $caseFileDate ?? $listName,
        );
      }
    }

    $form['property_list'] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#empty' => t('There are no properties for specified criteria.'),
    );

    $form['pager'] = array(
      '#theme' => 'pager',
    );
  }

  /**
   * Builds and returns a query to retrieve the property list.
   */
  static function genPropertyListQuery(): EntityFieldQuery {
    static $query;

    if (isset($query)) {
      return clone $query;
    }

    global $user;

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'property')
      ->propertyCondition('uid', $user->uid);

    $filters = self::getFilters();

    if (isset($filters['list'])) {
      if (1 == $filters['list']) {
        $query->fieldCondition('field_list', 'value', 1);

        if (isset($filters['case_file_date_from'])) {
          $query->fieldCondition('field_case_file_date', 'value', $filters['case_file_date_from'], '>=');
        }

        if (isset($filters['case_file_date_to'])) {
          $query->fieldCondition('field_case_file_date', 'value', $filters['case_file_date_to'], '<=');
        }

        if (!empty($filters['hide_sold_after_case_file_date'])) {
          $query->addTag('exclude_sold_after_case_file_date');
        }
      }
    }

    if (!empty($filters['county'])) {
      $query->fieldCondition('field_fips_county_code', 'value', $filters['county']);
    }

    if (!empty($filters['owner_status'])) {
      switch ($filters['owner_status']) {
        case 1:
        case 2:
        case 3:
        case 4:
          $query->fieldCondition('field_owner_status', 'value', $filters['owner_status']);
          break;
        case 5:
          $query->fieldCondition('field_owner_status', 'value', 1, '<>');
      }
    }

    if (!empty($filters['phone'])) {
      if (1 == $filters['phone']) {
        $query->addTag('phone_not_in_dnc');
      }
      else {
        $query->addTag('phone_in_dnc');
      }
    }

    if (isset($filters['last_contacted_from'])) {
      $query->fieldCondition('field_last_contacted', 'value', $filters['last_contacted_from'], '>=');
    }

    if (isset($filters['last_contacted_to'])) {
      $query->fieldCondition('field_last_contacted', 'value', $filters['last_contacted_to'], '<=');
    }

    if (!empty($filters['market_value_from'])) {
      $query->fieldCondition('field_market_value', 'value', $filters['market_value_from'] / 1000, '>=');
    }

    if (!empty($filters['market_value_to'])) {
      $query->fieldCondition('field_market_value', 'value', $filters['market_value_to'] / 1000, '<=');
    }

    if (!empty($filters['beds'])) {
      $query->fieldCondition('field_bedrooms', 'value', $filters['beds']);
    }
    else {
      if (!empty($filters['beds_from'])) {
        $query->fieldCondition('field_bedrooms', 'value', $filters['beds_from'], '>=');
      }

      if (!empty($filters['beds_to'])) {
        $query->fieldCondition('field_bedrooms', 'value', $filters['beds_to'], '<=');
      }
    }

    if (!empty($filters['baths'])) {
      $query->fieldCondition('field_baths', 'value', $filters['baths']);
    }
    else {
      if (!empty($filters['baths_from'])) {
        $query->fieldCondition('field_baths', 'value', $filters['baths_from'], '>=');
      }

      if (!empty($filters['baths_to'])) {
        $query->fieldCondition('field_baths', 'value', $filters['baths_to'], '<=');
      }
    }

    if (!empty($filters['rooms'])) {
      $query->fieldCondition('field_rooms', 'value', $filters['rooms']);
    }
    else {
      if (!empty($filters['rooms_from'])) {
        $query->fieldCondition('field_rooms', 'value', $filters['rooms_from'], '>=');
      }

      if (!empty($filters['rooms_to'])) {
        $query->fieldCondition('field_rooms', 'value', $filters['rooms_to'], '<=');
      }
    }

    if (!empty($filters['built_from'])) {
      $query->fieldCondition('field_year_built', 'value', $filters['built_from'], '>=');
    }

    if (!empty($filters['built_to'])) {
      $query->fieldCondition('field_year_built', 'value', $filters['built_to'], '<=');
    }

    return clone $query;
  }

  /**
   * Returns the size of the property list.
   */
  static function getPropertyListCnt(): int {
    return self::genPropertyListQuery()->count()->execute();
  }

  /**
   * Returns the property list.
   *
   * Sine fieldOrderBy() excludes entities with empty field values from results,
   * we add 'order_by' tag to the query, the field and the direction as meta
   * data, and order results in the implementation of the corresponding hook.
   */
  static function getPropertyList(array $header): ?array {
    $order = tablesort_get_order($header);
    $sort = tablesort_get_sort($header);

    $result = self::genPropertyListQuery()
      ->addTag('order_by')
      ->addMetaData('order_field', $order['sql'])
      ->addMetaData('order_direction', $sort)
      ->pager(self::PER_PAGE)
      ->execute();

    return isset($result['node']) ? node_load_multiple(array_keys($result['node'])) : NULL;
  }

  /**
   * Saves the values of the filters used to filter the property list by.
   */
  static function setFilters(array $values): void {
    $_SESSION['property_table_form_filters']['list'] = $values['list'];
    $_SESSION['property_table_form_filters']['case_file_date_from'] = $values['case_file_date_from'];
    $_SESSION['property_table_form_filters']['case_file_date_to'] = $values['case_file_date_to'];
    $_SESSION['property_table_form_filters']['hide_sold_after_case_file_date'] = $values['hide_sold_after_case_file_date'];

    if (isset($values['county'])) {
      $_SESSION['property_table_form_filters']['county'] = $values['county'];
    }

    $_SESSION['property_table_form_filters']['owner_status'] = $values['owner_status'];
    $_SESSION['property_table_form_filters']['phone'] = $values['phone'];
    $_SESSION['property_table_form_filters']['last_contacted_from'] = $values['last_contacted_from'];
    $_SESSION['property_table_form_filters']['last_contacted_to'] = $values['last_contacted_to'];

    if (isset($values['market_value_from'])) {
      $_SESSION['property_table_form_filters']['market_value_from'] = $values['market_value_from'];
      $_SESSION['property_table_form_filters']['market_value_to'] = $values['market_value_to'];
    }

    if (isset($values['beds'])) {
      $_SESSION['property_table_form_filters']['beds'] = $values['beds'];
      $_SESSION['property_table_form_filters']['beds_from'] = $values['beds_from'];
      $_SESSION['property_table_form_filters']['beds_to'] = $values['beds_to'];
    }

    if (isset($values['baths'])) {
      $_SESSION['property_table_form_filters']['baths'] = $values['baths'];
      $_SESSION['property_table_form_filters']['baths_from'] = $values['baths_from'];
      $_SESSION['property_table_form_filters']['baths_to'] = $values['baths_to'];
    }

    if (isset($values['rooms'])) {
      $_SESSION['property_table_form_filters']['rooms'] = $values['rooms'];
      $_SESSION['property_table_form_filters']['rooms_from'] = $values['rooms_from'];
      $_SESSION['property_table_form_filters']['rooms_to'] = $values['rooms_to'];
    }

    if (isset($values['built_from'])) {
      $_SESSION['property_table_form_filters']['built_from'] = $values['built_from'];
      $_SESSION['property_table_form_filters']['built_to'] = $values['built_to'];
    }
  }

  /**
   * Returns the values of the filters used to filter the property list by.
   */
  static function getFilters(): array {
    return $_SESSION['property_table_form_filters'] ?? array();
  }

  /**
   * Clears the values of the filters used to filter the property list by.
   */
  static function clearFilters(): void {
    unset($_SESSION['property_table_form_filters']);
  }

  /**
   * Generates a list of price values as options for a select element.
   */
  static function genPriceOptions(int $from, int $to, int $stepBeforeMillion, int $stepAfterMillion): array {
    if (1000000 >= $to) {
      $prices = range($from, $to, $stepBeforeMillion);
      $prices = array_combine($prices, array_map('number_format', $prices));
    }
    else {
      $prices1 = range($from, 1000000, $stepBeforeMillion);
      $prices1 = array_combine($prices1, array_map('number_format', $prices1));
      $prices2 = range(1000000 + $stepAfterMillion, $to, $stepAfterMillion);
      $prices2 = array_combine($prices2, array_map('number_format', $prices2));
      $prices = $prices1 + $prices2;
    }

    return $prices;
  }

  /**
   * Generates a list of int values as options for a select element.
   */
  static function genIntOptions(int $from, int $to, int $step): array {
    $numbers = range($from, $to, $step);
    return array_combine($numbers, $numbers);
  }

  /**
   * Generates a list of float values as options for a select element.
   */
  static function genFloatOptions(float $from, float $to, float $step): array {
    $numbers = range($from, $to, $step);
    return array_combine($numbers, $numbers);
  }
}
