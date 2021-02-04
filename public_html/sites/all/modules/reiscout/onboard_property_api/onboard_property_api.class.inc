<?php

/*
 * @file
 * Definition of the OnboardPropertyApi class.
 */

class OnboardPropertyApiException extends Exception {}
class OnboardPropertyApiBadRequestException extends Exception {}
class OnboardPropertyApiJsonInvalidException extends Exception {}

class OnboardPropertyApi {
  const BASE_URL = 'https://search.onboard-apis.com/propertyapi/v1.0.0/';
  const ALLEVENTS_DETAIL_URL = self::BASE_URL . 'allevents/detail';
  const PROPERTY_DETAILMORTGAGEOWNER_URL = self::BASE_URL . 'property/detailmortgageowner';

  const RESPONSE_SOURCE_CACHE = 0;
  const RESPONSE_SOURCE_HTTP = 1;

  private $apiKey;
  private $address1;
  private $address2;
  private $requestReason;

  function __construct() {
    $this->collectGarbage();
  }

  /**
   * Returns property data by its address.
   *
   * Given $address1 and $address2, for instance:
   *   $address1 = '4929 River Overlook Way';
   *   $address2 = 'Lithonia, GA 30038';
   *
   * function checks if DB has been already populated with property data
   * for a property with this address. If yes, function returns the data.
   * Otherwise, function makes a request to the Onboard Property API
   * for the property data and then saves the data to DB.
   */
  public function getData($address1, $address2, $requestReason) {
    if (empty($address1)) {
      $msg = t('Value of the address1 filter is not provided.');
      throw new OnboardPropertyApiException($msg);
    }

    if (empty($address2)) {
      $msg = t('Value of the address2 filter is not provided.');
      throw new OnboardPropertyApiException($msg);
    }

    if (empty($requestReason)) {
      $msg = t('Reason of the request is not provided.');
      throw new OnboardPropertyApiException($msg);
    }

    $this->setAddress1($address1);
    $this->setAddress2($address2);
    $this->setRequestReason($requestReason);

    // Try to load cached data from the database
    if ($data = $this->loadDataFromDb()) {
      $this->logRequest(self::RESPONSE_SOURCE_CACHE);
      return $data;
    }

    // Make a request to the Onboard Property API
    if ($data = $this->requestData()) {
      $this->logRequest(self::RESPONSE_SOURCE_HTTP);
      $this->saveDataToDB($data);
      return $data;
    }
  }

  /**
   * Removes records from the DB that are too old.
   */
  private function collectGarbage() {
    $cacheLifetime = variable_get('onboard_property_api_cache_lifetime', ONBOARD_PROPERTY_API_CACHE_LIFETIME);
    $cacheLifetime *= 24 * 60 * 60;
    db_delete('onboard_property_api_data')
      ->condition('created', REQUEST_TIME - $cacheLifetime, '<')
      ->execute();
  }

  private function setAddress1($address1) {
    $this->address1 = $address1;
  }

  private function setAddress2($address2) {
    $this->address2 = $address2;
  }

  private function setRequestReason($requestReason) {
    $this->requestReason = $requestReason;
  }

  /**
   * Saves property data to DB.
   */
  private function saveDataToDB($data) {
    $record = new stdClass();
    $record->address1 = $this->address1;
    $record->address2 = $this->address2;
    $record->data = serialize($data);
    $record->created = time();

    drupal_write_record('onboard_property_api_data', $record);
  }

  /**
   * Loads data from DB.
   */
  private function loadDataFromDb() {
    $data = db_select('onboard_property_api_data', 'd')
      ->fields('d', array('data'))
      ->condition('address1', $this->address1)
      ->condition('address2', $this->address2)
      ->execute()
      ->fetchField();

    return unserialize($data);
  }

  /**
   * Saves information about request to DB.
   */
  private function logRequest($responseSource) {
    global $user;

    $record = new stdClass();
    $record->filters = serialize($this->address1 . ';' . $this->address2);
    $record->reason = $this->requestReason;
    $record->response_source = $responseSource;
    $record->uid = $user->uid;
    $record->timestamp = time();

    drupal_write_record('onboard_property_api_requests_history', $record);
  }

  /**
   * Requests property data from the Onboard Property API.
   */
  private function requestData() {
    $data = NULL;

    $response = $this->requestAllEventsDetailData();
    $data = $response->property[0];

    $response = $this->propertyDetailMortageOwnerData();
    $data->mortgage = $response->property[0]->mortgage;
    $data->owner = $response->property[0]->owner;

    return $data;
  }

  /**
   * Makes a GET request to the 'allevents/detail' endpoint.
   */
  private function requestAllEventsDetailData() {
    $query = array(
      'address1' => $this->address1,
      'address2' => $this->address2,
    );

    return $this->makeGetRequest(self::ALLEVENTS_DETAIL_URL, $query);
  }

  /**
   * Makes a GET request to the 'property/detailmortgageowner' endpoint.
   */
  private function propertyDetailMortageOwnerData() {
    $query = array(
      'address1' => $this->address1,
      'address2' => $this->address2,
    );

    return $this->makeGetRequest(self::PROPERTY_DETAILMORTGAGEOWNER_URL, $query);
  }

  /**
   * Returns the API key.
   */
  private function getApiKey() {
    if (!isset($this->apiKey)) {
      if (!$this->apiKey = variable_get('onboard_property_api_key')) {
        throw new OnboardPropertyApiException(t('API key is not set.'));
      }
    }

    return $this->apiKey;
  }

  /**
   * Makes a GET request.
   */
  private function makeGetRequest($url, $query) {
    $options = array(
      'headers' => array(
        'Accept' => 'application/json',
        'apikey' => $this->getApiKey(),
      ),
      'timeout' => 5,
    );

    $response = drupal_http_request($url . '?' . drupal_http_build_query($query), $options);

    if (200 != $response->code) {
      $msg = t('Bad Request: <pre>!response</pre>', array('!response' => var_export($response, true)));
      throw new OnboardPropertyApiBadRequestException($msg);
    }

    if (!$data = json_decode($response->data)) {
      $msg = t('JSON object cannot be decoded: <pre>!response</pre>', array('!response' => var_export($response, true)));
      throw new OnboardPropertyApiJsonInvalidException($msg);
    }

    return $data;
  }
}
