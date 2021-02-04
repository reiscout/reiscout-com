<?php

/**
 * @file
 * Admin page callback file for the Connect2Data API module.
 */

/**
 * Form builder; Configure Connect2Data API settings.
 *
 * @see system_settings_form()
 */
function connect2data_api_admin_settings_form() {
  $form['login_data'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login Data'),
  );

  $form['login_data']['connect2data_api_login_account_id'] = array(
    '#type' => 'textfield',
    '#title' => t('LoginAccountIdentifier'),
    '#default_value' => variable_get('connect2data_api_login_account_id', ''),
    '#required' => TRUE,
  );

  $form['login_data']['connect2data_api_login_account_pw'] = array(
    '#type' => 'textfield',
    '#title' => t('LoginAccountPassword'),
    '#default_value' => variable_get('connect2data_api_login_account_pw', ''),
    '#required' => TRUE,
  );

  $form['caching'] = array(
    '#type' => 'fieldset',
    '#title' => t('Caching'),
  );

  $form['caching']['connect2data_api_cache_lifetime_detailed_subject_report'] = array(
    '#type' => 'textfield',
    '#title' => t('Expiration of DetailedSubjectReport data, days'),
    '#description' => t('The maximum time cached report can be used.'),
    '#default_value' => variable_get('connect2data_api_cache_lifetime_detailed_subject_report', CONNECT2DATA_API_CACHE_LIFETIME_DETAILED_SUBJECT_REPORT),
    '#element_validate' => array('element_validate_integer_positive'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Page callback: displays a history of requests.
 *
 * Page callback: displays a history of requests that were made
 * to the Connect2Data API.
 */
function connect2data_api_history_page() {
  $content = array();

  $header = array(
    array('data' => t('Requested'), 'field' => 'timestamp', 'sort' => 'desc'),
    array('data' => t('Username'), 'field' => 'uid'),
    t('Property criteria'),
    array('data' => t('Reason'), 'field' => 'reason'),
    array('data' => t('Response source'), 'field' => 'response_source'),
  );

  $rows = array();

  if ($records = _connect2data_api_get_request_history($header)) {
    foreach ($records as $record) {
      // Build 'Username'
      $username = $record->name ? l($record->name, 'user/' . $record->uid) : 'cron';

      // Build 'Property criteria'
      $data = unserialize($record->request);
      $property_criteria = $data['street_address'] . ', '
                         . $data['city'] . ', '
                         . $data['state'] . ', '
                         . $data['postal_code'];

      $rows[] = array(
        format_date($record->timestamp),
        $username,
        $property_criteria,
        $record->reason,
        $record->response_source == CONNECT2DATA_API_RESPONSE_SOURCE_CACHE ? 'cache' : 'http',
      );
    }
  }

  $content['table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('There are no history to display.'),
  );

  $content['pager'] = array(
    '#theme' => 'pager',
  );

  return $content;
}

/**
 * Returns a history of requests.
 */
function _connect2data_api_get_request_history($header) {
  $query = db_select('c2d_request_history', 'rh')
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
