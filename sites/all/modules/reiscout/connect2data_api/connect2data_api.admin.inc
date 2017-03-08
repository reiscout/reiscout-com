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
  reiscout_owner_info_get_owner_drupalgap_callback(336);

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

  return system_settings_form($form);
}