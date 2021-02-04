#!/usr/bin/env drush

function reiscout_update_address_access_products_price() {
  $transaction = db_transaction();

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'commerce_product')
    ->entityCondition('bundle', REISCOUT_PROPERTY_COMMERCE_ADDRESS_ACCESS_PRODUCT_TYPE);
  $result = $query->execute();

  if (!isset($result['commerce_product'])) {
    return;
  }

  if (!$products = commerce_product_load_multiple(array_keys($result['commerce_product']))) {
    return;
  }

  foreach ($products as $product) {
    $nid = $product->field_property[LANGUAGE_NONE][0]['target_id'];
    if (!$property_node = node_load($nid)) {
      continue;
    }

    $product->commerce_price[LANGUAGE_NONE][0] = reiscout_property_commerce_get_property_address_price($property_node);
    commerce_product_save($product);
  }
}

reiscout_update_address_access_products_price();
