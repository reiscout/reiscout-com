<?php

/**
 * Adds corresponding amount of Points product to a user's cart.
 *
 * Clears a user's cart and adds corresponding amount of
 * Points product to the cart.
 */
function _reiscout_points_resource_add_product_to_cart($product_id, $amount) {
  global $user;

  $result = array(
    'status' => FALSE,
    'message' => '',
  );

  if ($product_id) {
    $product = commerce_product_load($product_id);
  }
  else {
    // If an ID of the product is not set, we add '1 point' product to the cart
    $product = commerce_product_load_by_sku(REISCOUT_POINTS_1_POINT_PRODUCT_SKU);
  }

  if (!$product) {
    $result['message'] = t('Points cannot be purchased now. Please, try again later or contact technical support for assistance!');
  }
  else {
    _reiscout_points_clear_cart();

    // Create the new line item with a product
    $line_item = commerce_product_line_item_new($product, $amount);

    // Add the line item to the cart
    commerce_cart_product_add($user->uid, $line_item, FALSE);

    $result['status'] = TRUE;
  }

  return $result;
}

/**
 * Returns an option list of available points package products.
 */
function _reiscout_points_resource_get_package_products_options() {
  $result = array();

  if ($package_products =_reiscout_points_combine_package_products_options()) {
    $result['package_products'] = $package_products;
  }

  return $result;
}

/**
 * Access callback.
 *
 * Determines whether the current user can access resources of
 * 'reiscout_points' Services service.
 *
 * @param $op
 *   The id of the resource.
 * @param $args
 *   Resource arguments passed through from the original request.
 * @return bool
 */
function _reiscout_points_resource_access($op, $args = array()) {
  return user_is_logged_in();
}
