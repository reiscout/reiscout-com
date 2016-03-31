<?php

/**
 * @file
 *
 */


/**
 * Return display nodes associated with purchased products by user.
 *
 * @param integer $uid user id
 * @param string $order_status an order status, default to 'completed'
 * @param string $sku product sku
 */
function reiscout_property_commerce_get_order_display_entities($uid, $sku = '', $order_status = 'completed') {

  $purchased_entities = &drupal_static(__FUNCTION__ . '_' .$uid . '_' . $sku);
  if (!empty($purchased_entities)) {
    return $purchased_entities;
  }

  $purchased_entities = array();
  $orders = commerce_order_load_multiple(array(), array('uid' => $uid, 'status' => $order_status)); //

  foreach ($orders as $order) {
    $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
    foreach ($order_wrapper->commerce_line_items->getIterator() as $line_item_wrapper) {
      if (empty($sku) || $sku == $line_item_wrapper->commerce_product->sku->value()) {
        $line_item = $line_item_wrapper->value();
        $entity = $line_item->data['context']['entity'];
        $purchased_entities[ $entity['entity_type'] ][] = $entity['entity_id'];
      }
    }
  }

  return $purchased_entities;
}

function reiscout_property_commerce_is_display_node_purchased ($uid, $nid, $sku) {
  $purchased_entities = reiscout_property_commerce_get_order_display_entities($uid, $sku);
  if (!empty($purchased_entities['node'])) {
    return in_array($nid, $purchased_entities['node']);
  } else {
    return FALSE;
  }

}

/**
 * A helper wrapper for commerce_reiscout_get_purchased_display_entities()
 */
function reiscout_property_commerce_get_order_product_display_nids($sku, $status = 'completed', $uid = '') {
  if (empty($uid)) {
    $uid = $GLOBALS['user']->uid;
  }
  $entities = reiscout_property_commerce_get_order_display_entities($uid, $sku, $status);
  $nids = array();
  foreach ($entities as $entity) {
    if ($entity['entity_type'] == 'node') {
      $nids[] = $entity['entity_id'];
    }
  }
  return $nids;
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