<?php

/**
 * @file
 * Admin page callback file for the Zillow API module.
 */

/**
 * Form builder; Configure Zillow API settings.
 *
 * @see zillow_api_admin_settings_form_submit()
 * @see zillow_api_admin_settings_form_mark_zwsid_as_valid_submit()
 */
function zillow_api_admin_settings_form() {
  $form['zillow_api_zwsid'] = array(
    '#type' => 'textfield',
    '#title' => t('Zillow Web Services ID'),
    '#default_value' => variable_get('zillow_api_zwsid', ''),
    '#required' => TRUE,
  );

  if (!ZillowApi::zwsidIsValid()) {
    $form['info'] = array(
      '#prefix' => '<div id="zillow-api-invalid-zwsid">',
      '#markup' => t('Zillow Web Services ID is marked as invalid.'),
      '#suffix' => '</div>',
    );

    $form['#attached']['css'][] = array(
      'data' => '#zillow-api-invalid-zwsid {color: red}',
      'type' => 'inline',
    );
  }

  $form['actions'] = array(
    '#type' => 'actions',
  );

  if (!ZillowApi::zwsidIsValid()) {
    $form['actions']['mark_zwsid_as_valid'] = array(
      '#type' => 'submit',
      '#value' => t('Mark as valid'),
      '#submit' => array('zillow_api_admin_settings_form_mark_zwsid_as_valid_submit'),
    );
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Form submission handler for zillow_api_admin_settings_form().
 *
 * @see zillow_api_admin_settings_form()
 */
function zillow_api_admin_settings_form_submit($form, &$form_state) {
  variable_set('zillow_api_zwsid', $form_state['values']['zillow_api_zwsid']);
  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * Form submission handler for zillow_api_admin_settings_form().
 *
 * @see zillow_api_admin_settings_form()
 */
function zillow_api_admin_settings_form_mark_zwsid_as_valid_submit($form, &$form_state) {
  ZillowApi::markZwsidAsValid();
  drupal_set_message(t('Zillow Web Services ID has been marked as valid.'));
}
