<?php

/*
 * @file
 * Definition of the SmartyStreetsAPI_StreetAddressAPI class.
 */

class SmartyStreetsAPIException extends Exception {}

class SmartyStreetsAPI_StreetAddressAPI {
  const URL = 'https://us-street.api.smartystreets.com/street-address';

  private $authID;
  private $authToken;

  function __construct($auth_id, $auth_token) {
    if (!$auth_id) {
      throw new SmartyStreetsAPIException(t('Auth ID is not set.'), 1);
    }

    if (!$auth_token) {
      throw new SmartyStreetsAPIException(t('Auth Token is not set.'), 2);
    }

    $this->authID = $auth_id;
    $this->authToken = $auth_token;
  }

  /**
   * Makes a GET request to SmartyStreets 'US Street Address API'.
   * This function is used to send a single address only.
   */
  public function requestData($address) {
    $params = array(
      'auth-id' => $this->authID,
      'auth-token' => $this->authToken,
      'street' => $address,
    );

    $url = $this::URL . '?' . drupal_http_build_query($params);
    $result = drupal_http_request($url);

    if (400 == $result->code) {
      throw new SmartyStreetsAPIException(t('Bad Request (Malformed Payload).'), 3);
    }

    if (401 == $result->code) {
      throw new SmartyStreetsAPIException(t('Unauthorized.'), 4);
    }

    if (402 == $result->code) {
      throw new SmartyStreetsAPIException(t('Payment Required.'), 5);
    }

    if (413 == $result->code) {
      throw new SmartyStreetsAPIException(t('Request Entity Too Large.'), 6);
    }

    if (429 == $result->code) {
      throw new SmartyStreetsAPIException(t('Too Many Requests.'), 7);
    }

    if (200 != $result->code) {
      throw new SmartyStreetsAPIException(t('Unknown error.'), 8);
    }

    if (!json_decode($result->data)) {
      throw new SmartyStreetsAPIException(t('There is no matches for that address: @address', array('@address' => $address)), 9);
    }

    return $result->data;
  }

  /**
   * Makes a POST request to SmartyStreets 'US Street Address API'.
   * This function is used to send multiple addresses.
   */
  public function requestDataMultiple($addresses) {
    $params = array(
      'auth-id' => $this->authID,
      'auth-token' => $this->authToken,
    );

    $options = array(
      'headers' => array(
        'Content-Type' => 'application/json',
      ),
      'method' => 'POST',
      'data' => json_encode($addresses),
    );

    $url = $this::URL . '?' . drupal_http_build_query($params);
    $result = drupal_http_request($url, $options);

    if (400 == $result->code) {
      throw new SmartyStreetsAPIException(t('Bad Request (Malformed Payload).'), 3);
    }

    if (401 == $result->code) {
      throw new SmartyStreetsAPIException(t('Unauthorized.'), 4);
    }

    if (402 == $result->code) {
      throw new SmartyStreetsAPIException(t('Payment Required.'), 5);
    }

    if (413 == $result->code) {
      throw new SmartyStreetsAPIException(t('Request Entity Too Large.'), 6);
    }

    if (429 == $result->code) {
      throw new SmartyStreetsAPIException(t('Too Many Requests.'), 7);
    }

    if (200 != $result->code) {
      throw new SmartyStreetsAPIException(t('Unknown error.'), 8);
    }

    if (!json_decode($result->data)) {
      $address_list = '';
      foreach ($addresses as $address) {
        $address_list .= $address_list ? '; ' . $address->street : $address->street;
      }
      throw new SmartyStreetsAPIException(t('There are no matches for these addresses: @address_list', array('@address_list' => $address_list)), 10);
    }

    return $result->data;
  }

  /**
   * Decodes a JSON data.
   */
  public function decodeData($json) {
    return json_decode($json);
  }
}
