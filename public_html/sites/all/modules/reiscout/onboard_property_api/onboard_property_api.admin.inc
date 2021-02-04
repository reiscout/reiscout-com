<?php

/**
 * @file
 * Admin page callback file for Onboard Property API module.
 */

/**
 * Form builder; Configure Onboard Property API settings.
 *
 * @see system_settings_form()
 */
function onboard_property_api_admin_settings_form() {
  $form['onboard_property_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API key'),
    '#default_value' => variable_get('onboard_property_api_key', ''),
    '#required' => TRUE,
  );

  $form['onboard_property_api_cache_lifetime'] = array(
    '#type' => 'textfield',
    '#title' => t('Expiration of data, days'),
    '#description' => t('The maximum time cached data can be used.'),
    '#default_value' => variable_get('onboard_property_api_cache_lifetime', ONBOARD_PROPERTY_API_CACHE_LIFETIME),
    '#element_validate' => array('element_validate_integer_positive'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Page callback: displays history of requests.
 *
 * Page callback: displays history of requests that were made
 * to the Onboard Property API.
 */
function onboard_property_api_requests_history_page() {
  $content = array();

  $header = array(
    array('data' => t('Requested'), 'field' => 'timestamp', 'sort' => 'desc'),
    array('data' => t('Username'), 'field' => 'uid'),
    t('Filters'),
    array('data' => t('Reason'), 'field' => 'reason'),
    array('data' => t('Response source'), 'field' => 'response_source'),
  );

  $rows = array();

  if ($records = _onboard_property_api_get_requests_history($header)) {
    foreach ($records as $record) {
      // Build 'Username'
      $username = $record->name ? l($record->name, 'user/' . $record->uid) : 'cron';

      $rows[] = array(
        format_date($record->timestamp),
        $username,
        unserialize($record->filters),
        $record->reason,
        $record->response_source == CONNECT2DATA_API_RESPONSE_SOURCE_CACHE ? 'cache' : 'http',
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
 * Returns history of requests.
 */
function _onboard_property_api_get_requests_history($header) {
  $query = db_select('onboard_property_api_requests_history', 'rh')
    ->extend('PagerDefault')
    ->extend('TableSort');
  $query
    ->leftJoin('users', 'u', 'rh.uid = u.uid');
  $query
    ->fields('rh')
    ->fields('u', array('name'))
    ->orderByHeader($header)
    ->limit(20);

  return $query->execute()->fetchAll();
}
