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