<?php

/**
 * @file
 * Admin page callback file for the user module.
 */

/**
 * Form builder; Configure SmartyStreets API settings.
 *
 * @see system_settings_form()
 */
function smartystreetsapi_admin_settings_form() {
  $form['secret_keys'] = array(
    '#type' => 'fieldset',
    '#title' => t('Secret Keys'),
  );

  $form['secret_keys']['smartystreetsapi_auth_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Auth ID'),
    '#default_value' => variable_get('smartystreetsapi_auth_id', ''),
    '#required' => TRUE,
  );

  $form['secret_keys']['smartystreetsapi_auth_token'] = array(
    '#type' => 'textfield',
    '#title' => t('Auth Token'),
    '#default_value' => variable_get('smartystreetsapi_auth_token', ''),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}