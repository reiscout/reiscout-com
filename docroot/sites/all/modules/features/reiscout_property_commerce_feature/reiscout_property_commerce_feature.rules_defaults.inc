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
  $items['rules_reiscout_property_commerce_limit_line_items_quantity'] = entity_import('rules_config', '{ "rules_reiscout_property_commerce_limit_line_items_quantity" : {
      "LABEL" : "Limit line items quantity to one item",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "TAGS" : [ "reiscout" ],
      "REQUIRES" : [ "rules", "entity" ],
      "ON" : { "commerce_line_item_update" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "commerce-line-item:type" ], "value" : "product" } },
        { "data_is" : {
            "data" : [ "commerce-line-item:quantity" ],
            "op" : "\\u003E",
            "value" : "1"
          }
        }
      ],
      "DO" : [
        { "data_set" : { "data" : [ "commerce-line-item:quantity" ], "value" : "1" } },
        { "drupal_message" : { "message" : "[commerce-line-item-unchanged:commerce_product] item already added to cart." } }
      ]
    }
  }');
  $items['rules_reiscout_property_order_email_to_admin'] = entity_import('rules_config', '{ "rules_reiscout_property_order_email_to_admin" : {
      "LABEL" : "Send an order notification e-mail to admin",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "reiscout" ],
      "REQUIRES" : [ "commerce_order", "rules", "commerce_checkout" ],
      "ON" : { "commerce_checkout_complete" : [] },
      "IF" : [
        { "commerce_order_contains_product_type" : {
            "commerce_order" : [ "commerce_order" ],
            "product_type" : { "value" : { "reiscout_property_address_access" : "reiscout_property_address_access" } },
            "operator" : "\\u003E=",
            "value" : "1"
          }
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : "boris@reiscout.com",
            "subject" : "A new order [commerce-order:order-number] at [site:name]",
            "message" : "\\u0027Address Access\\u0027 product was purchased.\\r\\n\\r\\nOrder number: [commerce-order:order-number]\\r\\nOrder link: [commerce-order:admin-url]",
            "language" : [ "commerce-order:state" ]
          }
        }
      ]
    }
  }');
  return $items;
}
