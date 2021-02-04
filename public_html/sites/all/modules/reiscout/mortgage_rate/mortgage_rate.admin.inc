<?php

/**
 * @file
 * Admin page callback file for Mortgage Rate module.
 */

/**
 * Form builder; Configure Mortgage Rate settings.
 *
 * @see mortgage_rate_admin_settings_form_submit()
 */
function mortgage_rate_admin_settings_form() {
  $statistics = mortgage_rate_get_statistics();

  if ($statistics['15']['min_date'] && $statistics['15']['max_date']) {
    $t_args = array('%from' => date('Y-m-d', $statistics['15']['min_date']), '%to' => date('Y-m-d', $statistics['15']['max_date']));
    $info_15 = t('Data were collected over period from %from to %to.', $t_args);
  }
  else {
    $info_15 = t('Data were not collected yet.');
  }

  if ($statistics['30']['min_date'] && $statistics['30']['max_date']) {
    $t_args = array('%from' => date('Y-m-d', $statistics['30']['min_date']), '%to' => date('Y-m-d', $statistics['30']['max_date']));
    $info_30 = t('Data were collected over period from %from to %to.', $t_args);
  }
  else {
    $info_30 = t('Data were not collected yet.');
  }

  $form['15_year'] = array(
    '#type' => 'fieldset',
    '#title' => t('15-year fixed-rate mortgages'),
  );

  $form['15_year']['info'] = array(
    '#markup' => $info_15,
  );

  $form['30_year'] = array(
    '#type' => 'fieldset',
    '#title' => t('30-year fixed-rate mortgages'),
  );

  $form['30_year']['info'] = array(
    '#markup' => $info_30,
  );

  $form['updating'] = array(
    '#type' => 'fieldset',
    '#title' => t('Updating'),
  );

  $form['updating']['mortgage_rate_update_interval'] = array(
    '#type' => 'textfield',
    '#title' => t('Update interval, days'),
    '#default_value' => variable_get('mortgage_rate_update_interval', MORTGAGE_RATE_UPDATE_PERIOD),
    '#element_validate' => array('element_validate_integer_positive'),
    '#required' => TRUE,
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  $form['actions']['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update data'),
    '#submit' => array('mortgage_rate_admin_settings_form_update_submit'),
  );

  return $form;
}

/**
 * Form submission handler for mortgage_rate_admin_settings_form().
 *
 * @see mortgage_rate_admin_settings_form()
 */
function mortgage_rate_admin_settings_form_submit($form, &$form_state) {
  variable_set('mortgage_rate_update_interval', $form_state['values']['mortgage_rate_update_interval']);
  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * Form submission handler for mortgage_rate_admin_settings_form().
 *
 * @see mortgage_rate_admin_settings_form()
 */
function mortgage_rate_admin_settings_form_update_submit($form, &$form_state) {
  if (mortgage_rate_update_data()) {
    drupal_set_message(t('Data were updated.'));
  }
  else {
    drupal_set_message(t('Data do not need to be updated.'), 'warning');
  }
}
