<?php
/**
 * @file
 * reiscout_property_commerce_feature.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function reiscout_property_commerce_feature_default_rules_configuration() {
  $items = array();
  $items['commerce_checkout_reiscout_property_commerce_checkout_completion'] = entity_import('rules_config', '{ "commerce_checkout_reiscout_property_commerce_checkout_completion" : {
      "LABEL" : "Update the order status on checkout completion",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "1",
      "OWNER" : "rules",
      "TAGS" : [ "Commerce Checkout Reiscout Property" ],
      "REQUIRES" : [ "commerce_order", "commerce_checkout" ],
      "ON" : { "commerce_checkout_complete" : [] },
      "DO" : [
        { "commerce_order_update_state" : { "commerce_order" : [ "commerce-order" ], "order_state" : "completed" } }
      ]
    }
  }');
  return $items;
}
