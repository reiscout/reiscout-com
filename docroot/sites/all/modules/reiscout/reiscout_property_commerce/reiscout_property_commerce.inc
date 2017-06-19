<?php

/**
 * @file
 *
 */

function reiscout_property_commerce_create_product($type, $reference_node) {

  if (empty($reference_node->nid)) {
    throw new Exception('nid is required in passed node object');
  }

  $product = commerce_product_new($type);
  $product->field_property[LANGUAGE_NONE][0]['target_id'] = $reference_node->nid;
  $product->commerce_price[LANGUAGE_NONE][0] = array(
    'amount' => 0,
    'currency_code' => 'USD',
  );

  if ($type == REISCOUT_PROPERTY_COMMERCE_ADDRESS_ACCESS_PRODUCT_TYPE) {
    $product->title = 'Address Access for '. $reference_node->title;
    $product->sku = 'address-access-for-property-node-'. $reference_node->nid;
    $product->commerce_price[LANGUAGE_NONE][0] = reiscout_property_commerce_get_property_address_price($reference_node);
  }
  if ($type == REISCOUT_PROPERTY_COMMERCE_OWNER_INFO_PRODUCT_TYPE) {
    $product->title = 'Owner Info for '. $reference_node->title;
    $product->sku = 'owner-info-for-property-node-'. $reference_node->nid;
    $product->commerce_price[LANGUAGE_NONE][0] = reiscout_property_commerce_get_owner_info_price();
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
  if (empty($uid)) {
    $uid = $GLOBALS['user']->uid;
  }

  $purchased_nids = &drupal_static(__FUNCTION__ . '_' .$product_type . '_' . $uid);
  if (isset($purchased_nids)) {
    return $purchased_nids;
  }

  $query = db_select('commerce_order', 'ord');
  $query->join('commerce_line_item', 'li', 'ord.order_id = li.order_id');
  $query->join('field_data_commerce_product', 'li_prod', 'li.line_item_id = li_prod.entity_id');
  $query->join('commerce_product', 'prod', 'prod.product_id = li_prod.commerce_product_product_id');
  $query->join('field_data_field_property', 'prop_ref', 'prop_ref.entity_id = prod.product_id');

  $query->condition('ord.uid', $uid, '=')
    ->condition('ord.status', 'completed', '=')
    ->condition('prod.type', $product_type, '=')
    ->fields('prop_ref', array('field_property_target_id'));

  $result = $query->execute();
  return $result->fetchCol();
}

/**
 * Returns 'Property' nodes whose $type product was purchased.
 */
function reiscout_property_commerce_get_purchased_nodes($type) {
  $query = db_select('commerce_order', 'ord');
  $query->join('commerce_line_item', 'li', 'ord.order_id = li.order_id');
  $query->join('field_data_commerce_product', 'li_prod', 'li.line_item_id = li_prod.entity_id');
  $query->join('commerce_product', 'prod', 'prod.product_id = li_prod.commerce_product_product_id');
  $query->join('field_data_field_property', 'prop_ref', 'prop_ref.entity_id = prod.product_id');
  $query->join('node', 'n', 'n.nid = prop_ref.field_property_target_id');
  $query
    ->fields('prop_ref', array('field_property_target_id'))
    ->distinct()
    ->condition('ord.status', 'completed')
    ->condition('prod.type', $type)
    ->orderBy('field_property_target_id');

  return $query->execute()->fetchCol();
}

function reiscout_property_commerce_get_purchased_counters($nids) {
  $query = db_select('field_data_field_property', 'fdfp');
  $query->join('commerce_product', 'cp', 'cp.product_id = fdfp.entity_id');
  $query->join('field_data_commerce_product', 'fdcp', 'fdcp.commerce_product_product_id = cp.product_id');
  $query->join('commerce_line_item', 'cli', 'cli.line_item_id = fdcp.entity_id');
  $query->join('commerce_order', 'co', 'co.order_id = cli.order_id');
  $query->condition('fdfp.field_property_target_id', $nids, 'IN');
  $query->condition('co.status', 'completed', '=');
  $query->addField('fdfp', 'field_property_target_id', 'nid');
  $query->addExpression('COUNT(DISTINCT co.order_id)', 'counter');
  $query->groupBy('fdfp.field_property_target_id');

  return $query->execute()->fetchAll();
}

function reiscout_property_commerce_is_node_purchased($nid, $product_type, $uid = '') {
  $purchased_nids = reiscout_property_commerce_get_purchased_nids($product_type, $uid);
  return in_array($nid, $purchased_nids);
}

function reiscout_property_commerce_get_referenced_product($nid, $product_type) {
  // we don't need it for now
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
    $product = array_pop($result['commerce_product']);
    $product = commerce_product_load($product->product_id);
    return $product;
  } else {
    return FALSE;
  }
}

/**
 * Return owner info product price
 */
function reiscout_property_commerce_get_owner_info_price() {

  $price_decimal = variable_get('reiscout_property_commerce_owner_info_price', 10);

  return array(
    'amount' => $price_decimal * 100,
    'currency_code' => 'USD',
  );
}

/**
 * Calculate and return property address price
 */
function reiscout_property_commerce_get_property_address_price($node) {

  // Load fields from fieldgroup? see field_group_load_field_group()
  $fields_to_check = array(
    'body',
    'field_gross_area',
    'field_bedrooms',
    'field_full_baths',
    'field_half_baths',
    'field_lot_area_acres',
    'field_last_sale_price',
    'field_last_sale_date',
    'field_assessed_value',
    'field_mortgage_company',
    'field_repairs_price',
    'field_arv',
    'field_under_contract'
  );

  $served_types = array(
    'datetime', 'number_integer', 'number_decimal', 'list_integer', 'text', 'text_with_summary'
  );

  $filled_fields_count = 0;
  foreach ($fields_to_check as $field) {
    $field_info = field_info_field($field);
    if (!in_array($field_info['type'], $served_types)) {
      trigger_error($field_info['type'] . ' field type can\'t be handled', E_USER_WARNING);
      continue;
    }

    if (in_array($field_info['type'], array('list_integer', 'number_integer'))) {
      if (!isset($node->{$field}[LANGUAGE_NONE][0]['value'])) {
        continue;
      }

      if (!empty($node->{$field}[LANGUAGE_NONE][0]['value'])
      || $node->{$field}[LANGUAGE_NONE][0]['value'] == 0) {
        $filled_fields_count++;
      }

    } else {
      if (!empty($node->{$field}[LANGUAGE_NONE][0]['value'])) {
        $filled_fields_count++;
      }
    }
  }

  $bace_price_decimal = variable_get('reiscout_property_commerce_address_access_basic_price', 30);
  $per_field_price_decimal = variable_get('reiscout_property_commerce_address_access_per_field_price', 0);
  $price = $bace_price_decimal + $per_field_price_decimal * $filled_fields_count;
  return array(
    'amount' => $price * 100,
    'currency_code' => 'USD',
  );
}

/**
 * Check is price for product should be updated and update if needed.
 */
function reiscout_property_commerce_update_price($node, $product) {
  // Add try..catch block to make system show a reasonable error,
  // otherwise it will show entity_metadata exception with no reasonable call stack
  try {
    if (!isset($product->uid)) {
      $product->uid = '';
    }

    $pw = entity_metadata_wrapper('commerce_product', $product);

    if ($product->type == REISCOUT_PROPERTY_COMMERCE_ADDRESS_ACCESS_PRODUCT_TYPE) {
      $new_price = reiscout_property_commerce_get_property_address_price($pw->field_property->value());
    } elseif ($product->type == REISCOUT_PROPERTY_COMMERCE_OWNER_INFO_PRODUCT_TYPE) {
      $new_price = reiscout_property_commerce_get_owner_info_price();
    } else {
      throw new Exception('Product of passed type can\'t be processed');
    }

    // Check is new price is different then existed and save.
    if ($pw->commerce_price->amount->value() != $new_price['amount']
      || $pw->commerce_price->currency_code->value() != $new_price['currency_code']) {
      $pw->commerce_price->set($new_price);
    }

    $pw->title->set(preg_replace("/#([\d]+)?/",'#'.$node->nid, $product->title));
    $pw->save();

  } catch (Exception $e) {
    throw new Exception($e->getMessage());
  }
}

/**
 * Set product status to disabled.
 */
function reiscout_property_commerce_disable($product) {
  try {
    $pw = entity_metadata_wrapper('commerce_product', $product);
    $pw->status->set(0);
    $pw->save();
  } catch (Exception $e) {
    throw new Exception($e->getMessage());
  }
}
