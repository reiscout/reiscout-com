<?php

/**
 * @file
 * Admin page callback file for Reiscout Points Product module.
 */

/**
 * Form builder; Configure prices of Reiscout products.
 *
 * @see system_settings_form()
 */
function reiscout_points_product_prices_form($form, &$form_state) {
  if (!$products = reiscout_points_product_get_all()) {
    $form['info'] = array(
      '#markup' => t('There are no any registered Reiscout products.'),
    );

    return $form;
  }

  foreach ($products as $product_id => $product) {
    $form[$product_id] = array(
      '#type' => 'fieldset',
      '#title' => $product['title'],
      '#description' => $product['description'],
    );

    if ($product['price_callback']) {
      $form[$product_id]['info'] = array(
        '#markup' => t('<em>A price of the product is defined by its price_callback</em>'),
      );
    }
    else {
      $form[$product_id]['reiscout_points_product_prices'][$product_id] = array(
        '#type' => 'textfield',
        '#title' => t('Price, points'),
        '#default_value' => reiscout_points_product_get_price($product_id),
        '#element_validate' => array('element_validate_integer_positive'),
        '#required' => TRUE,
        '#tree' => TRUE,
        '#parents' => array('reiscout_points_product_prices', $product_id),
      );
    }
  }

  return system_settings_form($form);
}
