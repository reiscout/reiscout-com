<?php

/*
 * @file
 * Definition of the ZillowApi class.
 */

class ZillowApiNetworkError extends Exception {}
class ZillowApiUnavailable extends Exception {}
class ZillowApiInvalidZwsid extends Exception {}
class ZillowApiRequestLimitIsReached extends Exception {}
class ZillowApiInvalidRequest extends Exception {}
class ZillowApiInvalidResponse extends Exception {}
class ZillowApiNoResultsFound extends Exception {}
class ZillowApiUnknownError extends Exception {}

class ZillowApi {
  const URL = 'https://www.zillow.com/webservice/';

  private $zwsid;
  private $defaultZwsidIsUsed = FALSE;

  function __construct(string $zwsid = NULL) {
    if (!$zwsid) {
      if (!self::zwsidIsValid()) {
        throw new ZillowApiInvalidZwsid();
      }
      if ($reached = $this->getRequestLimitReachedTimestamp()) {
        // We want to defer requests to Zillow API for 24 hours
        if ($reached + 24 * 60 * 60 > time()) {
          throw new ZillowApiRequestLimitIsReached();
        }
        else {
          $this->unsetRequestLimitReachedTimestamp();
        }
      }
      $zwsid = variable_get('zillow_api_zwsid');
      $this->defaultZwsidIsUsed = TRUE;
    }
    $this->zwsid = $zwsid;
  }

  /**
   * Makes a request to the Zillow GetDeepSearchResults API.
   *
   * @throws \ZillowApiInvalidRequest
   * @throws \ZillowApiInvalidResponse
   * @throws \ZillowApiInvalidZwsid
   * @throws \ZillowApiNetworkError
   * @throws \ZillowApiNoResultsFound
   * @throws \ZillowApiRequestLimitIsReached
   * @throws \ZillowApiUnavailable
   * @throws \ZillowApiUnknownError
   */
  public function getDeepSearchResults(string $address, string $city, string $state, string $zip): stdClass {
    $info = new stdClass();

    $params = array(
      'zws-id' => $this->zwsid,
      'address' => $address,
      'citystatezip' => $city . ', ' . $state . ', ' . $zip,
    );

    $url = $this::URL . 'GetDeepSearchResults.htm?' . drupal_http_build_query($params);
    $result = drupal_http_request($url, array('timeout' => 10));
    $resultStr = '<pre>' . print_r($result, TRUE) . '</pre>';

    if (200 != $result->code) {
      watchdog('zillow_api', $resultStr);
      throw new ZillowApiNetworkError();
    }

    if (FALSE === $data = simplexml_load_string($result->data)) {
      watchdog('zillow_api', 'XML error: ' . $resultStr);
      throw new ZillowApiInvalidResponse();
    }

    if ($errorCode = (int)$data->message->code) {
      switch ($errorCode) {
        case 1:
        case 500:
        case 501:
        case 503:
        case 506:
          watchdog('zillow_api', $resultStr);
          throw new ZillowApiInvalidRequest(NULL, $errorCode);
        case 2:
          watchdog('zillow_api', 'ZWSID is invalid. ' . $resultStr, array(), WATCHDOG_ERROR);
          if ($this->defaultZwsidIsUsed) {
            $this->markZwsidAsInvalid();
          }
          throw new ZillowApiInvalidZwsid();
        case 3:
        case 4:
        case 505:
          watchdog('zillow_api', $resultStr);
          throw new ZillowApiUnavailable();
        case 502:
        case 504:
        case 507:
        case 508:
          watchdog('zillow_api', $resultStr);
          throw new ZillowApiNoResultsFound(NULL, $errorCode);
        default:
          watchdog('zillow_api', $resultStr);
          throw new ZillowApiUnknownError(NULL, $errorCode);
      }
    }

    if ($data->message->{'limit-warning'}) {
      $message = 'We are limited to 1000 requests to Zillow API per day. ' . $resultStr;
      watchdog('zillow_api', $message, array(), WATCHDOG_WARNING);
      if ($this->defaultZwsidIsUsed) {
        $this->setRequestLimitReachedTimestamp();
      }
      throw new ZillowApiRequestLimitIsReached();
    }

    if (1 < count($data->response->results->result)) {
      // @todo: For now we assume the first result contains the most accurate data,
      // so we use it and reject the rest ones. But we still log all such events,
      // and if it turns out that our assumption is wrong, we will need to write
      // the logic of choosing a result contains the most accurate data.
      $message = 'There are more than one result for specified address: ' . $resultStr;
      watchdog('zillow_api', $message, array(), WATCHDOG_INFO);
    }

    $data = $data->response->results->result;

    if (!empty($data->FIPScounty)) {
      $info->FIPScounty = (string)$data->FIPScounty;
    }

    if ($data->zestimate->amount) {
      $info->zestimate = (int)$data->zestimate->amount;
    }

    if ($data->taxAssessment) {
      $info->taxAssessment = (int)$data->taxAssessment;
    }

    if ($data->lastSoldPrice) {
      $info->lastSoldPrice = (int)$data->lastSoldPrice;
    }

    if ($data->lastSoldDate) {
      $info->lastSoldDate = (string)$data->lastSoldDate;
    }

    if ($data->finishedSqFt) {
      $info->finishedSqFt = (int)$data->finishedSqFt;
    }

    if ($data->lotSizeSqFt) {
      $info->lotSizeSqFt = (int)$data->lotSizeSqFt;
    }

    if ($data->bedrooms) {
      $info->beds = (string)$data->bedrooms;
    }

    if ($data->bathrooms) {
      $info->baths = (string)$data->bathrooms;
    }

    if ($data->totalRooms) {
      $info->rooms = (string)$data->totalRooms;
    }

    if ($data->yearBuilt) {
      $info->built = (int)$data->yearBuilt;
    }

    $info->url = (string)$data->links->homedetails;

    return $info;
  }

  /**
   * Checks if the ZWSID is valid.
   */
  static function zwsidIsValid(): bool {
    return !variable_get('zillow_api_zwsid_is_invalid');
  }

  /**
   * Marks the ZWSID as invalid.
   */
  private function markZwsidAsInvalid(): void {
    variable_set('zillow_api_zwsid_is_invalid', TRUE);
  }

  /**
   * Marks the ZWSID as valid.
   */
  static function markZwsidAsValid(): void {
    variable_del('zillow_api_zwsid_is_invalid');
  }

  /**
   * Returns the timestamp when the request limit has been reached.
   */
  private function getRequestLimitReachedTimestamp(): ?int {
    return variable_get('zillow_api_request_limit_reached');
  }

  /**
   * Sets the timestamp when the request limit has been reached.
   */
  private function setRequestLimitReachedTimestamp(): void {
    variable_set('zillow_api_request_limit_reached', time());
  }

  /**
   * Unsets the timestamp when the request limit has been reached.
   */
  private function unsetRequestLimitReachedTimestamp(): void {
    variable_del('zillow_api_request_limit_reached');
  }
}
