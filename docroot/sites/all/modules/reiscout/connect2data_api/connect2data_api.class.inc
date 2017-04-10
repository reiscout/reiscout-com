<?php

/*
 * @file
 * Definition of the Connect2DataAPI class.
 */

class Connect2DataAPIException extends Exception {}

class Connect2DataAPI {
  const URL = 'https://staging.connect2data.com';

  private $loginAccountIdentifier;
  private $loginAccountPassword;
  private $propertyCriteria;
  private $requestReason;

  function __construct() {
    if (!$this->loginAccountIdentifier = variable_get('connect2data_api_login_account_id')) {
      throw new Connect2DataAPIException(t('LoginAccountIdentifier is not set.'), 1);
    }

    if (!$this->loginAccountPassword = variable_get('connect2data_api_login_account_pw')) {
      throw new Connect2DataAPIException(t('LoginAccountPassword is not set.'), 2);
    }

    $this->collectGarbageDetailedSubjectReports();
  }

  /**
   * Collects garbage for DetailedSubjectReport data.
   */
  private function collectGarbageDetailedSubjectReports() {
    $cache_lifetime = variable_get('connect2data_api_cache_lifetime_detailed_subject_report', CONNECT2DATA_API_CACHE_LIFETIME_DETAILED_SUBJECT_REPORT);
    $cache_lifetime *= 24 * 60 * 60;
    db_delete('c2d_detailed_subject_report')
      ->condition('created', REQUEST_TIME - $cache_lifetime, '<')
      ->execute();
  }

  /**
   * Returns DetailedSubjectReport info for a property.
   *
   * Given an array of property's criteria, for instance:
   *   $propertyCriteria = array(
   *     'street_address' => '2735 Williamsburg Way',
   *     'city' => 'Decatur',
   *     'state' => 'GA',
   *     'postal_code' => '30034',
   *   )
   *
   * this function generates a SHA1 representation of property criteria:
   *   $hash = sha1(implode($propertyCriteria));
   *
   * and checks if there is a record with this hash exists in DB.
   * If there is, the function returns the record.
   * If there is not, the function makes a request to the Connect2Data API
   * and then saves a response and the hash to DB.
   */
  public function getDetailedSubjectReport($propertyCriteria, $requestReason) {
    if (empty($propertyCriteria['street_address'])
     || empty($propertyCriteria['city'])
     || empty($propertyCriteria['state'])
     || empty($propertyCriteria['postal_code'])) {
      $errorMessage = t(
        'Not enough property criteria was provided: !property_criteria',
        array('!property_criteria' => print_r($propertyCriteria, TRUE))
      );
      throw new Connect2DataAPIException($errorMessage, 3);
    }

    if (!$requestReason) {
      throw new Connect2DataAPIException(t('A reason of a request was not provided.'), 4);
    }

    $this->setPropertyCriteria($propertyCriteria);
    $this->setRequestReason($requestReason);

    // Try to load a cached report from a database
    $hash = sha1(implode($this->propertyCriteria));
    if ($data = $this->loadDetailedSubjectReport($hash)) {
      $this->logRequest(CONNECT2DATA_API_RESPONSE_SOURCE_CACHE);
      return $data;
    }

    // Make a request to the Connect2Data API
    if ($xml = $this->requestDetailedSubjectReport()) {
      $this->logRequest(CONNECT2DATA_API_RESPONSE_SOURCE_HTTP);
      $data = $this->parseDetailedSubjectReport($xml);
      $this->saveDetailedSubjectReport($hash, $data);
      return $data;
    }
  }

  private function setPropertyCriteria($propertyCriteria) {
    $this->propertyCriteria = $propertyCriteria;
  }

  private function setRequestReason($requestReason) {
    $this->requestReason = $requestReason;
  }

  /**
   * Loads a DetailedSubjectReport record from DB.
   */
  private function loadDetailedSubjectReport($hash) {
    $xml = db_select('c2d_detailed_subject_report', 'r')
      ->fields('r', array('data'))
      ->condition('request_hash', $hash)
      ->execute()
      ->fetchField();

    if (!$xml) {
      return FALSE;
    }

    if (FALSE === $data = simplexml_load_string($xml)) {
      throw new Connect2DataAPIException(t('XML parsing error: not a valid XML.'), 5);
    }

    return $data;
  }

  /**
   * Saves information about request to DB.
   */
  private function logRequest($responseSource) {
    global $user;

    $record = new stdClass();
    $record->request = serialize($this->propertyCriteria);
    $record->reason = $this->requestReason;
    $record->response_source = $responseSource;
    $record->uid = $user->uid;
    $record->timestamp = time();

    drupal_write_record('c2d_request_history', $record);
  }

  /**
   * Saves a DetailedSubjectReport record to DB.
   */
  private function saveDetailedSubjectReport($hash, $data) {
    $record = new stdClass();
    $record->request_hash = $hash;
    $record->data = $data->asXML();
    $record->created = time();
    drupal_write_record('c2d_detailed_subject_report', $record);
  }

  /**
   * Makes a POST request to Connect2Data API.
   */
  private function requestDetailedSubjectReport() {
    $xml = $this->buildDetailedSubjectReportRequest();

    $options = array(
      'method' => 'POST',
      'data' => $xml,
    );

    $result = drupal_http_request($this::URL, $options);

    if (200 != $result->code) {
      throw new Connect2DataAPIException(t('Bad Request.'), 6);
    }

    return $result->data;
  }

  /**
   * Parses XML response that was received from Connect2Data API.
   */
  private function parseDetailedSubjectReport($xml) {
    if (FALSE === $data = simplexml_load_string($xml)) {
      throw new Connect2DataAPIException(t('XML parsing error: not a valid XML.'), 7);
    }

    $this->checkForStatusCodes($data->RESPONSE->RESPONSE_DATA);

    return $data->RESPONSE->RESPONSE_DATA->PROPERTY_INFORMATION_RESPONSE->_PROPERTY_INFORMATION->PROPERTY;
  }

  /**
   * Checks if response is successful.
   *
   * Checks if our request was processed successfully
   * and we have received a product we requested for.
   */
  private function checkForStatusCodes($responseData) {
    // Check for a response status.
    $responseStatus = $responseData->PROPERTY_INFORMATION_RESPONSE->STATUS;
    $code = $responseStatus->attributes()->_Code;
    $desc = $responseStatus->attributes()->_Description;

    // Status code '0400' means that our request was processed successfully.
    if ('0400' != $code) {
      throw new Connect2DataAPIException(t('Failure response status. Code: !code, message: !message.', array('!code' => $code, '!message' => $desc)), 8);
    }

    // Check for a product (a report that we have requested) status.
    $productStatus = $responseData->PROPERTY_INFORMATION_RESPONSE->_PRODUCT->STATUS;
    $code = $productStatus->attributes()->_Code;
    $desc = $productStatus->attributes()->_Description;

    // Status code '0500' means that product we requested for, was returned successfully.
    if ('0500' != $code) {
      $errorMessage = t(
        'Failure product status. Code: !code, message: !message, property criteria: !property_criteria.',
        array(
          '!code' => $code,
          '!message' => $desc,
          '!property_criteria' => print_r($this->propertyCriteria, TRUE),
        )
      );
      throw new Connect2DataAPIException($errorMessage, 9);
    }
  }

  /**
   * Builds an XML request to Connect2Data API.
   */
  private function buildDetailedSubjectReportRequest() {
    return '<?xml version="1.0" encoding="UTF-8"?>
    <!DOCTYPE REQUEST_GROUP SYSTEM "C2DRequestv2.0.dtd">
    <REQUEST_GROUP MISMOVersionID="2.1">
    <REQUEST LoginAccountIdentifier="' . $this->loginAccountIdentifier . '"
             LoginAccountPassword="' . $this->loginAccountPassword . '"
             _JobIdentifier="_DetailedSubjectReport">
    <REQUESTDATA>
    <PROPERTY_INFORMATION_REQUEST _ActionType="Submit">
       <_CONNECT2DATA_PRODUCT _DetailedSubjectReport="Y" />
       <_PROPERTY_CRITERIA _StreetAddress="' . $this->propertyCriteria['street_address'] . '"
                           _City="' . $this->propertyCriteria['city'] . '"
                           _State="' . $this->propertyCriteria['state'] . '"
                           _PostalCode="' . $this->propertyCriteria['postal_code'] . '" />
    </PROPERTY_INFORMATION_REQUEST>
    </REQUESTDATA>
    </REQUEST>
    </REQUEST_GROUP>';
  }
}
