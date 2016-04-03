<?php

/**
 * @file
 *
 */

function reiscout_property_commerce_create_product($type, $reference_node) {
  $product = commerce_product_new($type);
  $product->field_property[LANGUAGE_NONE][0]['target_id'] = $reference_node->nid;
  $product->commerce_price[LANGUAGE_NONE][0] = array(
    'amount' => 0,
    'currency_code' => 'USD',
  );

  if ($type == REISCOUT_PROPERTY_COMMERCE_ADDRESS_ACCESS_PRODUCT_TYPE) {
    $product->title = 'Address Access for '. $reference_node->title;
    $product->sku = 'address-access-for-property-node-'. $reference_node->nid;
  }
  if ($type == REISCOUT_PROPERTY_COMMERCE_OWNER_INFO_PRODUCT_TYPE) {
    $product->title = 'Owner Info for '. $reference_node->title;
    $product->sku = 'owner-info-for-property-node-'. $reference_node->nid;
  }

  commerce_product_save($product);

  return $product;
}

/**
 * Return display nodes associated with purchased products by user.
 *
 * @param integer $uid user id
 * @param string $order_status an order status
 * @param string $sku product sku
 */
function reiscout_property_commerce_get_purchased_nids($product_type, $uid = '') {

  // static cache here

  return [];
}

function reiscout_property_commerce_is_node_purchased ($nid, $product_type, $uid = '') {
  $purchased_entities = reiscout_property_commerce_get_purchased_nids ($product_type);
  if (!empty($purchased_entities['node'])) {
    return in_array($nid, $purchased_entities['node']);
  } else {
    return FALSE;
  }

}

function reiscout_property_commerce_get_referenced_product($nid, $product_type) {
  // we dont need it for now
}

function reiscout_property_commerce_load_product_by_property($product_type, $nid) {
  //return;
  $query = new EntityFieldQuery();

  $query->entityCondition('entity_type', 'commerce_product')
    ->entityCondition('bundle', $product_type)
    //->propertyCondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_property', 'target_id', $nid, '=')
    ->range(0, 1); // we need only single item as only the single one is allowed so we don't need to check all index.

  $result = $query->execute();
  if (!empty($result['commerce_product'])) {
    return array_pop($result['commerce_product']);
  } else {
    return FALSE;
  }
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