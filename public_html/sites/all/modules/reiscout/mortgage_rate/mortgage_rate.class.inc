<?php

/*
 * @file
 * Definition of the MortgageRate class.
 */

class MortgageRateException extends Exception {}

class MortgageRate {
  const URL = 'https://fred.stlouisfed.org/graph/fredgraph.csv';

  private $dataWereUpdated;

  /**
   * Returns a fixed mortgage rate for a term and date provided.
   */
  public function get($term, $date) {
    $rate = NULL;

    if (15 != $term && 30 != $term) {
      $message = t('There are data only for 15 year and 30 year fixed-rate mortgages. Provided mortgage term: !term.', array('!term' => $term));
      throw new MortgageRateException($message, 3);
    }

    if (!$dateTs = strtotime($date)) {
      $message = t('Provided date is invalid: !date.', array('!date' => $date));
      throw new MortgageRateException($message, 4);
    }

    if (15 == $term) {
      $rate = $this->get15Year($dateTs);
    }
    else {
      $rate = $this->get30Year($dateTs);
    }

    if (!$rate) {
      $message = t('There is no rate info for provided criteria; term: !term, date: !date.', array('!term' => $term, '!date' => $date));
      throw new MortgageRateException($message, 5);
    }

    return $rate;
  }

  /**
   * Returns info about collected mortgage rates data.
   */
  public function getStatistics() {
    $info = array();

    $info['15'] = array(
      'min_date' => $this->getFirstStoredDate15Year(),
      'max_date' => $this->getLastStoredDate15Year(),
    );

    $info['30'] = array(
      'min_date' => $this->getFirstStoredDate30Year(),
      'max_date' => $this->getLastStoredDate30Year(),
    );

    return $info;
  }

  /**
   * Updates mortgage rates data.
   */
  public function updateData() {
    $updateInterval = variable_get('mortgage_rate_update_interval', MORTGAGE_RATE_UPDATE_PERIOD);
    $updateInterval *= 24 * 60 * 60;

    if ($lastStoredDate = $this->getLastStoredDate15Year()) {
      if (REQUEST_TIME - $lastStoredDate > $updateInterval) {
        $this->update15YearData($lastStoredDate);
      }
    }
    else {
      $this->update15YearData();
    }

    if ($lastStoredDate = $this->getLastStoredDate30Year()) {
      if (REQUEST_TIME - $lastStoredDate > $updateInterval) {
        $this->update30YearData($lastStoredDate);
      }
    }
    else {
      $this->update30YearData();
    }

    return $this->dataWereUpdated;
  }

  /**
   * Returns a 15-year fixed mortgage rate for date provided.
   */
  private function get15Year($dateTs) {
    $tsFrom = $dateTs - 7 * 24 * 60 * 60;

    $query = db_select('mortgage_rate_15', 'mr')
      ->fields('mr', array('rate'))
      ->condition('date', $tsFrom, '>')
      ->condition('date', $dateTs, '<=')
      ->execute();

    return $query->fetchField();
  }

  /**
   * Returns a 30-year fixed mortgage rate for date provided.
   */
  private function get30Year($dateTs) {
    $tsFrom = $dateTs - 7 * 24 * 60 * 60;

    $query = db_select('mortgage_rate_30', 'mr')
      ->fields('mr', array('rate'))
      ->condition('date', $tsFrom, '>')
      ->condition('date', $dateTs, '<=')
      ->execute();

    return $query->fetchField();
  }

  /**
   * Updates 15-year fixed mortgage rates data.
   */
  private function update15YearData($from = FALSE) {
    $url = $this->buildURL(15, $from);

    if ($csv = $this->requestData($url)) {
      $data = $this->parseData($csv);
      $this->save15YearData($data);
      $this->dataWereUpdated = TRUE;
    }
  }

  /**
   * Updates 30-year fixed mortgage rates data.
   */
  private function update30YearData($from = FALSE) {
    $url = $this->buildURL(30, $from);

    if ($csv = $this->requestData($url)) {
      $data = $this->parseData($csv);
      $this->save30YearData($data);
      $this->dataWereUpdated = TRUE;
    }
  }

  /**
   * Returns the first date for which there is data stored in DB.
   *
   * Returns the first date for which there is a 15-year fixed
   * mortgage rate data stored in DB.
   */
  private function getFirstStoredDate15Year() {
    $query = db_select('mortgage_rate_15', 'mr');
    $query->addExpression('MIN(date)');
    return $query->execute()->fetchField();
  }

  /**
   * Returns the last date for which there is data stored in DB.
   *
   * Returns the last date for which there is a 15-year fixed
   * mortgage rate data stored in DB.
   */
  private function getLastStoredDate15Year() {
    $query = db_select('mortgage_rate_15', 'mr');
    $query->addExpression('MAX(date)');
    return $query->execute()->fetchField();
  }

  /**
   * Returns the first date for which there is data stored in DB.
   *
   * Returns the first date for which there is a 30-year fixed
   * mortgage rate data stored in DB.
   */
  private function getFirstStoredDate30Year() {
    $query = db_select('mortgage_rate_30', 'mr');
    $query->addExpression('MIN(date)');
    return $query->execute()->fetchField();
  }

  /**
   * Returns the last date for which there is data stored in DB.
   *
   * Returns the last date for which there is a 30-year fixed
   * mortgage rate data stored in DB.
   */
  private function getLastStoredDate30Year() {
    $query = db_select('mortgage_rate_30', 'mr');
    $query->addExpression('MAX(date)');
    return $query->execute()->fetchField();
  }

  /**
   * Builds a URL to request mortgage rates data.
   */
  private function buildUrl($term, $from) {
    $params = array(
      'id' => 'MORTGAGE' . $term . 'US',
    );

    if ($from) {
      $params['cosd'] = date('Y-m-d', $from);
    }

    return $this::URL . '?' . drupal_http_build_query($params);
  }

  /**
   * Makes a GET request for mortgage rates data.
   */
  private function requestData($url) {
    $result = drupal_http_request($url);

    if (200 != $result->code) {
      throw new MortgageRateException(t('Bad Request.'), 1);
    }

    if ('text/csv;charset=UTF-8' != $result->headers['content-type']) {
      throw new MortgageRateException(t('A response is not in CSV format.'), 2);
    }

    return $result->data;
  }

  /**
   * Parses a CSV response.
   */
  private function parseData($csv) {
    $data = explode(PHP_EOL, trim($csv));

    // Remove a header
    array_shift($data);

    return array_map('str_getcsv', $data);
  }

  /**
   * Saves 15-year fixed mortgage rates data to DB.
   */
  private function save15YearData($data) {
    $transaction = db_transaction();

    for ($i = 0, $len = count($data); $i < $len; ++$i) {
      $fields = array(
        'rate' => $data[$i][1],
      );
      db_merge('mortgage_rate_15')
        ->fields($fields)
        ->key(array('date' => strtotime($data[$i][0])))
        ->execute();
    }
  }

  /**
   * Saves 30-year fixed mortgage rates data to DB.
   */
  private function save30YearData($data) {
    $transaction = db_transaction();

    for ($i = 0, $len = count($data); $i < $len; ++$i) {
      $fields = array(
        'rate' => $data[$i][1],
      );
      db_merge('mortgage_rate_30')
        ->fields($fields)
        ->key(array('date' => strtotime($data[$i][0])))
        ->execute();
    }
  }
}
