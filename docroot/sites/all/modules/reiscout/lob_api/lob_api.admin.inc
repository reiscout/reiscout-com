<?php

/**
 * @file
 * Admin page callback file for the Lob API module.
 */

/**
 * Form builder; Configure Lob API settings.
 *
 * @see system_settings_form()
 */
function lob_api_admin_settings_form() {
  $form['lob_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API key'),
    '#default_value' => variable_get('lob_api_key', ''),
    '#required' => TRUE,
  );

  $form['lob_api_debug_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Debug mode on'),
    '#description' => t('Log to the watchdog a request and a response.'),
    '#default_value' => variable_get('lob_api_debug_enabled', FALSE),
  );

  return system_settings_form($form);
}
