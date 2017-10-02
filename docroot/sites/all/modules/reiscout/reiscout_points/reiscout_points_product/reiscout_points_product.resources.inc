<?php

/**
 * Sells a Reiscout product.
 */
function _reiscout_points_product_resource_sell($product_id, $params) {
  $result = array(
    'status' => FALSE,
    'message' => '',
    'balance' => 0,
  );

  $balance = reiscout_points_user_balance_get();
  $product = reiscout_points_product_get($product_id);
  $price = reiscout_points_product_get_price($product_id, $params);

  // If a user has sent (has submit) a form to buy a product,
  // while he has not enough amount of points to buy the product,
  // we display him a message about that.
  if ($balance < $price) {
    $result['message'] = _reiscout_points_product_build_not_enough_points_message(
      $price,
      $balance,
      call_user_func($product['desc_callback'], 'condition')
    );
  }
  else {
    $result = call_user_func($product['services_sell_callback'], $params);
    if ($result['status']) {
      reiscout_points_product_charge($product_id, $params);
    }
  }

  $result['balance'] = reiscout_points_user_balance_get();

  return $result;
}

/**
 * Access callback.
 *
 * Determines whether the current user can access 'sell' resource of
 * 'reiscout_points_product' Services service.
 *
 * @param $op
 *   The only allowed value is 'sell'.
 * @param $args
 *   Resource arguments passed through from the original request.
 * @return bool
 */
function _reiscout_points_product_resource_access($op, $args = array()) {
  $product_id = $args[0];
  $params = $args[1];

  $node = node_load($params['nid']);
  $product = reiscout_points_product_get($product_id);

  if (isset($product['access_callback'])) {
    return call_user_func($product['access_callback'], $node);
  }

  return FALSE;
}
