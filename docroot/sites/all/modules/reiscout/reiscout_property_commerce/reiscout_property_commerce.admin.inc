<?php
/**
 * Created by PhpStorm.
 * User: md761
 * Date: 4/3/16
 * Time: 20:23
 */

function reiscout_property_commerce_settings_form($form, &$form_state) {
  $form = array();

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

  $form['reiscout_property_commerce_owner_info_price'] = array(
    '#type' => 'textfield',
    '#title' => t('Owner Info product price'),
    '#default_value' => variable_get('reiscout_property_commerce_owner_info_price', 10),
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

function reiscout_property_commerce_settings_form_validate($form, &$form_state) {

  $check_to_be_numeric = array(
    'reiscout_property_commerce_address_access_basic_price',
    'reiscout_property_commerce_owner_info_price',
    'reiscout_property_commerce_address_access_per_field_price',
  );

  foreach ($check_to_be_numeric as $name) {
    $value = $form_state['values'][ $name ];
    if (!is_numeric($value)) {
      form_set_error($name, 'field value should be numeric');
    }
  }

}

function reiscout_property_commerce_settings_form_submit($form, &$form_state) {
  $to_save = array(
    'reiscout_property_commerce_address_access_basic_price',
    'reiscout_property_commerce_owner_info_price',
    'reiscout_property_commerce_address_access_per_field_price',
  );

  foreach ($to_save as $name) {
    variable_set($name, $form_state['values'][ $name ]);
  }
}