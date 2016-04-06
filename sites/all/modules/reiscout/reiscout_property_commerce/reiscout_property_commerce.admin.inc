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
  $address_access_price = $form_state['values']['reiscout_property_commerce_address_access_basic_price'];
  $owner_info_price = $form_state['values']['reiscout_property_commerce_owner_info_price'];

  if (!is_numeric($address_access_price)) {
    form_set_error('reiscout_property_commerce_address_access_basic_price', t('Price should be a number'));
  }

  if (!is_numeric($owner_info_price)) {
    form_set_error('reiscout_property_commerce_owner_info_price', t('Price should be a number'));
  }

}

function reiscout_property_commerce_settings_form_submit($form, &$form_state) {
  variable_set('reiscout_property_commerce_address_access_basic_price', $form_state['values']['reiscout_property_commerce_address_access_basic_price']);
  variable_set('reiscout_property_commerce_owner_info_price', $form_state['values']['reiscout_property_commerce_owner_info_price']);
}