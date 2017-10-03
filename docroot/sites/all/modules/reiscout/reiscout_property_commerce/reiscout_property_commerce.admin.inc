<?php

/**
 * @file
 * Admin page callback file for the Reiscout Property Commerce module.
 */

/**
 * Form builder; Configure Reiscout Property Commerce settings.
 *
 * @see reiscout_property_commerce_settings_form_validate()
 * @see reiscout_property_commerce_settings_form_submit()
 */
function reiscout_property_commerce_settings_form($form, &$form_state) {
  $form['help'] = array(
    '#markup' => t('Update the price for new created products below.'),
  );

  $form['reiscout_property_commerce_address_access_basic_price'] = array(
    '#type' => 'textfield',
    '#title' => t('Address Access basic price'),
    '#default_value' => variable_get('reiscout_property_commerce_address_access_basic_price', 10),
    '#size' => 5,
    '#maxlength' => 5,
    '#required' => TRUE,
  );

  $form['reiscout_property_commerce_address_access_per_field_price'] = array(
    '#type' => 'textfield',
    '#title' => t('Address Access price per field'),
    '#default_value' => variable_get('reiscout_property_commerce_address_access_per_field_price', 0.10),
    '#size' => 5,
    '#maxlength' => 5,
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Form validation handler for reiscout_property_commerce_settings_form().
 *
 * @see reiscout_property_commerce_settings_form()
 */
function reiscout_property_commerce_settings_form_validate($form, &$form_state) {
  $check_to_be_numeric = array(
    'reiscout_property_commerce_address_access_basic_price',
    'reiscout_property_commerce_address_access_per_field_price',
  );

  foreach ($check_to_be_numeric as $name) {
    $value = $form_state['values'][ $name ];
    if (!is_numeric($value)) {
      form_set_error($name, 'field value should be numeric');
    }
  }
}

/**
 * Form submission handler for reiscout_property_commerce_settings_form().
 *
 * @see reiscout_property_commerce_settings_form()
 */
function reiscout_property_commerce_settings_form_submit($form, &$form_state) {
  $to_save = array(
    'reiscout_property_commerce_address_access_basic_price',
    'reiscout_property_commerce_address_access_per_field_price',
  );

  foreach ($to_save as $name) {
    variable_set($name, $form_state['values'][ $name ]);
  }
}
