<?php

/**
 * @file
 * User page callback file for the Reiscout Points module.
 */

/**
 * Menu callback; Adds '1 point' product to a user's cart.
 */
function reiscout_points_buy_page($amount) {
  // If a provided amount is not a positive integer
  if (!is_numeric($amount) || $amount <= 0) {
    $amount = 10;
  }

  if (!$product = commerce_product_load_by_sku(REISCOUT_POINTS_1_POINT_PRODUCT_SKU)) {
    $t_arg = array('!sku' => REISCOUT_POINTS_1_POINT_PRODUCT_SKU);
    throw new Exception(t("The product with '!sku' SKU does not exist.", $t_arg));
  }

  _reiscout_points_clear_cart();
  _reiscout_points_add_product_to_cart($product, $amount);
  drupal_goto('cart');
}

/**
 * Form builder; Allows a user to buy a Reiscout points package.
 *
 * @see reiscout_points_buy_package_form_submit()
 */
function reiscout_points_buy_package_form($form, &$form_state) {
  global $user;

  if (!$products_options = _reiscout_points_combine_package_products_options()) {
    drupal_set_message(t('Sorry, there are no any points packages available at this time.'), 'warning');
    $url = 'user/' . $user->uid . '/reiscout-points-balance';
    if ($query_parameters = drupal_get_query_parameters()) {
      if (isset($query_parameters['return_to'])) {
        $url = $query_parameters['return_to'];
      }
    }
    drupal_goto($url);
  }

  $form['product_id'] = array(
    '#type' => 'radios',
    '#title' => t('Choose a points package:'),
    '#options' => $products_options,
    '#default_value' => key($products_options),
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Buy Points'),
  );

  $form['actions']['cancel'] = array(
    '#type' => 'button',
    '#value' => t('Cancel'),
    '#attributes' => array(
      'onclick' => 'javascript:history.back();return false',
    ),
  );

  return $form;
}

/**
 * Form submission handler for reiscout_points_buy_package_form().
 *
 * @see reiscout_points_buy_package_form()
 */
function reiscout_points_buy_package_form_submit($form, &$form_state) {
  $product_id = $form_state['values']['product_id'];

  if (!$product = commerce_product_load($product_id)) {
    $t_arg = array('!id' => $product_id);
    throw new Exception(t("The product with '!id' ID does not exist.", $t_arg));
  }

  _reiscout_points_clear_cart();
  _reiscout_points_add_product_to_cart($product);
  drupal_goto('cart');
}

/**
 * Given a Drupal Commerce product, adds it to a user's cart.
 */
function _reiscout_points_add_product_to_cart($product, $amount = 1) {
  global $user;

  // Create the new line item with a product
  $line_item = commerce_product_line_item_new($product, $amount);

  // Add the line item to the cart
  commerce_cart_product_add($user->uid, $line_item, FALSE);

  // On checkout completion we want to redirect a user to a page he started
  // the buying process from. To do it we need save the value of 'return_to'
  // parameter first.
  if ($query_parameters = drupal_get_query_parameters()) {
    if (isset($query_parameters['return_to'])) {
      $_SESSION['reiscout_points']['return_to'] = $query_parameters['return_to'];
    }
  }

  // On checkout completion we want to display a user a message
  // to inform him that his points balance has been updated. But
  // we want to display the message only to a site's user, so we
  // set a flag here.
  $_SESSION['reiscout_points']['site_user'] = TRUE;
}
