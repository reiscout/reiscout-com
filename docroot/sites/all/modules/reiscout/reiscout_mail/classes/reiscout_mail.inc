<?php

/*
 * @file
 * Definition of ReiscoutMail class.
 */

class ReiscoutMail {
  const SEND_LIMIT_PERIOD = 14;
  const TYPE_LETTER = 0;
  const TYPE_POSTCARD = 1;

  /**
   * Given the type of a mail, returns its name.
   */
  static function getTypeName($type) {
    $name = '';

    if (self::TYPE_LETTER == $type) {
      return t('letter');
    }
    elseif (self::TYPE_POSTCARD == $type) {
      return t('postcard');
    }

    return $name;
  }

  /**
   * Checks if the current user can send a mail to a property's owner.
   *
   * A user can send a mail to a property's owner if:
   * - he either is the creator of the property node OR he has purchased the property's address
   *   AND
   * - 'Owner postal address' field has been filled out.
   */
  static function canUserSend($node) {
    global $user;

    if (user_is_anonymous()) {
      return FALSE;
    }

    // If the "Owner postal address" field has not been filled out,
    // user cannot send a postcard.
    if (!_reiscout_property_is_owner_address_filled_by_nid($node->nid)) {
      return FALSE;
    }

    // If the user is not the creator of the property node
    if ($node->uid != $user->uid) {
      // Check if the user has purchased the property's address
      $user_has_purchased_node = reiscout_property_commerce_is_node_purchased(
        $node->nid,
        REISCOUT_PROPERTY_COMMERCE_ADDRESS_ACCESS_PRODUCT_TYPE,
        $user->uid);

      if (!$user_has_purchased_node) {
        return FALSE;
      }
    }

    return TRUE;
  }

  /**
   * Checks if the current user can send a mail by the send limit period.
   *
   * We want to allow a user to send a mail to the same property's owner
   * only once per defined send limit period of time.
   */
  static function canUserSendBySendLimitPeriod($nid) {
    global $user;

    $query = db_select('reiscout_mail_history', 'h')
      ->fields('h', array('hid'))
      ->condition('uid', $user->uid)
      ->condition('pnid', $nid)
      ->condition('timestamp', time() - self::getSendLimitPeriod() * 24 * 60 * 60, '>');

    return 0 == $query->execute()->rowCount();
  }

  /**
   * Checks if the current user can see mail sent history.
   *
   * A user can see mail sent history if:
   * - (he has 'view all users mail sent history' permission
   *   AND
   * - at least one mail was sent to the property's owner)
   *   OR
   * - (he either is the creator of the property node OR he has purchased the property's address
   *   AND
   * - he sent at least one mail to the property's owner).
   */
  static function canUserSeeSentHistory($node) {
    global $user;

    if (user_access('view all users mail sent history')
     && self::getSentCnt($node->nid)) {
      return TRUE;
    }

    // Flag if the user has purchased the property's address
    $hasUserPurchasedLead = reiscout_property_commerce_is_node_purchased($node->nid,
      REISCOUT_PROPERTY_COMMERCE_ADDRESS_ACCESS_PRODUCT_TYPE,
      $user->uid);

    if (($node->uid == $user->uid || $hasUserPurchasedLead)
     && self::getSentCnt($node->nid, $user->uid)) {
      return TRUE;
    }

    return FALSE;
  }

  /**
   * Given Property nid, returns the number of mails sent to the property's owner.
   */
  static function getSentCnt($nid, $uid = NULL) {
    $query = db_select('reiscout_mail_history', 'h')
      ->fields('h')
      ->condition('pnid', $nid);

    if ($uid) {
      $query->condition('uid', $uid);
    }

    return $query->execute()->rowCount();
  }

  /**
   * Returns info about the last mail sent by the current user.
   *
   * Given property's NID, returns info about the last mail
   * sent to an owner of the property by the current user.
   */
  static function getLastMailSentInfo($nid) {
    global $user;

    $query = db_select('reiscout_mail_history', 'h')
      ->fields('h', array('type', 'timestamp'))
      ->condition('uid', $user->uid)
      ->condition('pnid', $nid)
      ->orderBy('timestamp', 'DESC')
      ->range(0, 1);

    $data = $query->execute()->fetch();
    $data->typeName = self::getTypeName($data->type);

    return $data;
  }

  /**
   * Returns the send limit period.
   */
  static function getSendLimitPeriod() {
    return variable_get('reiscout_mail_send_limit_period', self::SEND_LIMIT_PERIOD);
  }

  /**
   * Generates mail sent history page.
   *
   * Given a property node, generates a page with the corresponding
   * mail sent history.
   */
  static function genSentHistoryPage($node) {
    global $user;

    $content = array();

    $header = array(
      array('data' => t('Username'), 'field' => 'uid'),
      array('data' => t('Type'), 'field' => 'type'),
      array('data' => t('Created'), 'field' => 'timestamp', 'sort' => 'desc'),
      t('Expected Delivery Date'),
      t('Current Status'),
      t('Current Location'),
    );

    $rows = array();

    if (user_access('view all users mail sent history')) {
      $records = self::getSentHistory($header, $node->nid);
    }
    else {
      $records = self::getSentHistory($header, $node->nid, $user->uid);
    }

    if ($records) {
      foreach ($records as $record) {
        $rows[] = array(
          l($record->name, 'user/' . $record->uid),
          self::getTypeName($record->type),
          date('M j, Y - g:i a', $record->timestamp) . ' (' . format_interval(time() - $record->timestamp) . ' ago)',
          date('M j, Y', $record->expected_delivery_date),
          array('data' => Event::getNameByType($record->event_type), 'title' => Event::getDescByType($record->event_type)),
          $record->location,
        );
      }
    }

    $content['table'] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#empty' => t('There is no history to display.'),
    );

    $content['pager'] = array(
      '#theme' => 'pager',
    );

    return $content;
  }

  /**
   * Given Property NID, returns corresponding mail sent history.
   *
   * Returns a list of mail sent history records with info about
   * the most recent tracking event for each of these mails.
   */
  static function getSentHistory($header, $nid, $uid = NULL) {
    $order = tablesort_get_order($header);
    $sort = tablesort_get_sort($header);
    $per_page = 20;

    $query = 'SELECT u.uid, u.name, h.expected_delivery_date, h.type, h.timestamp, e.type AS event_type, e.location, e.time
            FROM {reiscout_mail_history} h
            LEFT JOIN {users} u ON h.uid = u.uid
            LEFT JOIN {reiscout_mail_tracking_events} e ON e.mid = h.lob_api_mail_id
            WHERE pnid = :pnid' . ($uid ? ' AND u.uid = :uid ' : '') . '
            AND (e.eid IN (
              SELECT e1.eid
              FROM {reiscout_mail_tracking_events} e1
              WHERE e1.time = (
                SELECT MAX(time)
                FROM {reiscout_mail_tracking_events} e2
                WHERE e2.mid = e1.mid
              )
            )
            OR e.eid IS NULL)
            ORDER BY ' . $order['sql'] . ' ' . $sort;

    $args = array(':pnid' => $nid);
    if ($uid) {
      $args[':uid'] = $uid;
    }

    pager_default_initialize(db_query($query, $args)->rowCount(), $per_page);

    return db_query_range($query, pager_find_page() * $per_page, $per_page, $args)->fetchAll();
  }

  /**
   * Replaces all tokens in a given string with appropriate values.
   */
  static function replaceTokens($content, $propertyNid) {
    if (FALSE !== strpos($content, '{{date}}')) {
      $content = str_replace('{{date}}', date('F j, Y', time()), $content);
    }

    if (FALSE !== strpos($content, '{{owner_name}}')) {
      $propertyOwnerAddress = _reiscout_property_get_owner_address_by_nid($propertyNid);
      if ($propertyOwnerAddress->first_name->value()) {
        $propertyOwnerName = mb_convert_case($propertyOwnerAddress->first_name->value(), MB_CASE_TITLE, "UTF-8");
      }
      else {
        $propertyOwnerName = $propertyOwnerAddress->organisation_name->value();
      }
      $content = str_replace('{{owner_name}}', $propertyOwnerName, $content);
    }

    if (FALSE !== strpos($content, '{{owner_fullname}}')) {
      $propertyOwnerAddress = _reiscout_property_get_owner_address_by_nid($propertyNid);
      if ($propertyOwnerAddress->first_name->value()) {
        $propertyOwnerFullName = mb_convert_case($propertyOwnerAddress->first_name->value(), MB_CASE_TITLE, "UTF-8")
                               . ' '
                               . mb_convert_case($propertyOwnerAddress->last_name->value(), MB_CASE_TITLE, "UTF-8");
      }
      else {
        $propertyOwnerFullName = $propertyOwnerAddress->organisation_name->value();
      }
      $content = str_replace('{{owner_fullname}}', $propertyOwnerFullName, $content);
    }

    if (FALSE !== strpos($content, '{{address}}')) {
      $propertyAddress = _reiscout_property_get_address_by_nid($propertyNid);
      $address = $propertyAddress->thoroughfare->value() . ', '
               . $propertyAddress->locality->value() . ', '
               . $propertyAddress->administrative_area->value() . ' '
               . $propertyAddress->postal_code->value();
      $content = str_replace('{{address}}', $address, $content);
    }

    if (FALSE !== strpos($content, '{{street_address}}')) {
      $propertyAddress = _reiscout_property_get_address_by_nid($propertyNid);
      $content = str_replace('{{street_address}}', $propertyAddress->thoroughfare->value(), $content);
    }

    if (FALSE !== strpos($content, '{{city}}')) {
      $propertyAddress = _reiscout_property_get_address_by_nid($propertyNid);
      $content = str_replace('{{city}}', $propertyAddress->locality->value(), $content);
    }

    if (FALSE !== strpos($content, '{{my_fullname}}')) {
      $userAddress = _reiscout_property_get_user_address();
      $content = str_replace('{{my_fullname}}', $userAddress->name_line->value(), $content);
    }

    if (FALSE !== strpos($content, '{{my_phone}}')) {
      $userPhoneNumber = _reiscout_property_get_user_phone();
      $content = str_replace('{{my_phone}}', $userPhoneNumber, $content);
    }

    if (FALSE !== strpos($content, '{{my_website}}')) {
      $website = _reiscout_property_get_user_website();
      $content = str_replace('{{my_website}}', $website, $content);
    }

    if (FALSE !== strpos($content, '{{my_email}}')) {
      $email = _reiscout_property_get_user_email();
      $content = str_replace('{{my_email}}', $email, $content);
    }

    if (FALSE !== strpos($content, '{{my_company}}')) {
      $company = _reiscout_property_get_user_company_name();
      $content = str_replace('{{my_company}}', $company, $content);
    }

    return $content;
  }

  /**
   * Calculates all formulas in a given string.
   */
  static function calculateFormulas($content, $propertyNid) {
    if (FALSE !== strpos($content, 'MARKET_VALUE')) {
      $value = _reiscout_property_get_value_by_nid($propertyNid);
      $content = str_replace('MARKET_VALUE', $value, $content);
    }

    if (FALSE !== strpos($content, 'SQ_FOOTAGE')) {
      $grossArea = _reiscout_property_get_gross_area_by_nid($propertyNid);
      $content = str_replace('SQ_FOOTAGE', $grossArea, $content);
    }

    // Calculate expressions like '=[DATE + 45 DAYS]'
    if (preg_match_all('!=\[DATE\s?\+\s?(\d+)\s?DAYS\]!', $content, $matches)) {
      for ($i = 0, $len = count($matches[0]); $i < $len; ++$i) {
        $date = date('M j, Y', strtotime('+' . $matches[1][$i] . ' days'));
        $content = str_replace($matches[0][$i], $date, $content);
      }
    }

    // Calculate expressions like '=[(13 + 2) / 5]'
    if (preg_match_all('!=\[(.+?)\]!', $content, $matches)) {
      for ($i = 0, $len = count($matches[0]); $i < $len; ++$i) {
        $expression = preg_replace('![^0-9-+/*().]!', '', $matches[1][$i]);
        $result = round(eval('return ' . $expression . ';'));
        $content = str_replace($matches[0][$i], $result, $content);
      }
    }

    return $content;
  }

  /**
   * Saves information about mail sent into DB.
   */
  static function log($propertyNid, $templateNid, $lobApiMailId, $expectedDeliveryDate, $type) {
    global $user;

    $record = new stdClass();
    $record->uid = $user->uid;
    $record->pnid = $propertyNid;
    $record->tnid = $templateNid;
    $record->lob_api_mail_id = $lobApiMailId;
    $record->expected_delivery_date = strtotime($expectedDeliveryDate);
    $record->type = $type;
    $record->timestamp = time();

    drupal_write_record('reiscout_mail_history', $record);
  }

  /**
   * Processes a notification from Lob on tracking events for mail.
   */
  static function processLobNotification() {
    if (!$request = file_get_contents('php://input')) {
      return;
    }

    if (!$data = json_decode($request)) {
      watchdog('reiscout_mail', 'Request cannot be decoded from JSON. Request: <pre>!request</pre>.', array('!request' => var_export($request, TRUE)));
      return;
    }

    if ('postcards' == $data->event_type->resource || 'letters' == $data->event_type->resource) {
      foreach ($data->body->tracking_events as $event) {
        Event::log($data->reference_id, $event);
      }
    }
  }
}
