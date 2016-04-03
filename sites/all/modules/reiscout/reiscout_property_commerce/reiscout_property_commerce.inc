<?php

/**
 * @file
 *
 */


/**
 * Return display nodes associated with purchased products by user.
 *
 * @param integer $uid user id
 * @param string $order_status an order status
 * @param string $sku product sku
 */
function reiscout_property_commerce_get_purchased_nids($sku, $uid = '') {

  // static cache here

  return [];
}

function reiscout_property_commerce_is_node_purchased ($nid, $product_type, $uid = '') {
  $purchased_entities = reiscout_property_commerce_get_order_display_entities($uid, $sku);
  if (!empty($purchased_entities['node'])) {
    return in_array($nid, $purchased_entities['node']);
  } else {
    return FALSE;
  }

}

function reiscout_property_commerce_get_referenced_product($nid, $product_type) {
  // we dont need it for now
}

/**
 * Return owner info product price
 */
function reiscout_property_commerce_get_owner_info_price() {
  $product = commerce_product_load(REISCOUT_PROPERTY_COMMERCE_OWNER_INFO_PRODUCT_ID);
  $price = $product->commerce_price[LANGUAGE_NONE][0];
  return $price;
}

/**
 * Calculate and return property address price
 * ToDo: implement it.
 */
function reiscout_property_commerce_get_property_address_price($node) {
  $product = commerce_product_load(REISCOUT_PROPERTY_COMMERCE_ADDRESS_ACCESS_PRODUCT_ID);
  $price = $product->commerce_price[LANGUAGE_NONE][0];
  $price['amount'] = $node->nid;
  return $price;
}