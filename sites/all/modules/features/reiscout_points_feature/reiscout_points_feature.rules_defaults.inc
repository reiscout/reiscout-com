<?php
/**
 * @file
 * reiscout_points_feature.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function reiscout_points_feature_default_rules_configuration() {
  $items = array();
  $items['rules_add_points_owner_info'] = entity_import('rules_config', '{ "rules_add_points_owner_info" : {
      "LABEL" : "Add points (owner info)",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [
        "commerce_order",
        "rules_conditional",
        "rules",
        "userpoints_rules",
        "commerce_checkout"
      ],
      "ON" : { "commerce_checkout_complete" : [] },
      "IF" : [
        { "commerce_order_contains_product" : {
            "commerce_order" : [ "commerce_order" ],
            "product_id" : "OWNER_INFO_POINTS",
            "operator" : "\\u003E=",
            "value" : "1"
          }
        }
      ],
      "DO" : [
        { "LOOP" : {
            "USING" : { "list" : [ "commerce-order:commerce-line-items" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "CONDITIONAL" : [
                  {
                    "IF" : { "text_matches" : {
                        "text" : [ "list-item:line-item-label" ],
                        "match" : "OWNER_INFO_POINTS"
                      }
                    },
                    "DO" : [
                      { "entity_query" : {
                          "USING" : {
                            "type" : "commerce_product",
                            "property" : "sku",
                            "value" : [ "list-item:line-item-label" ],
                            "limit" : "1"
                          },
                          "PROVIDE" : { "entity_fetched" : { "entity_fetched" : "Fetched entity" } }
                        }
                      },
                      { "CONDITIONAL" : [
                          {
                            "IF" : { "entity_has_field" : { "entity" : [ "entity-fetched:0" ], "field" : "field_points_amount" } },
                            "DO" : [
                              { "data_calc" : {
                                  "USING" : {
                                    "input_1" : [ "list-item:quantity" ],
                                    "op" : "*",
                                    "input_2" : [ "entity-fetched:0:field-points-amount" ]
                                  },
                                  "PROVIDE" : { "result" : { "result" : "Calculation result" } }
                                }
                              },
                              { "data_convert" : {
                                  "USING" : { "type" : "integer", "value" : [ "result" ] },
                                  "PROVIDE" : { "conversion_result" : { "int_points_result" : "Integer points result" } }
                                }
                              },
                              { "userpoints_action_grant_points" : {
                                  "user" : [ "list-item:order:owner" ],
                                  "points" : [ "int-points-result" ],
                                  "tid" : "1",
                                  "entity" : [ "" ],
                                  "description" : "[commerce-order:owner] buy [result:value] points (owner info).",
                                  "operation" : "[commerce-order:owner] buy [result:value] points (owner info).",
                                  "display" : "1",
                                  "moderate" : "approved"
                                }
                              }
                            ]
                          }
                        ]
                      }
                    ]
                  }
                ]
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_add_points_sending_letters'] = entity_import('rules_config', '{ "rules_add_points_sending_letters" : {
      "LABEL" : "Add points (sending letters)",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [
        "commerce_order",
        "rules_conditional",
        "rules",
        "userpoints_rules",
        "commerce_checkout"
      ],
      "ON" : { "commerce_checkout_complete" : [] },
      "IF" : [
        { "commerce_order_contains_product" : {
            "commerce_order" : [ "commerce_order" ],
            "product_id" : "LETTERS_POINTS",
            "operator" : "\\u003E=",
            "value" : "1"
          }
        }
      ],
      "DO" : [
        { "LOOP" : {
            "USING" : { "list" : [ "commerce-order:commerce-line-items" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "CONDITIONAL" : [
                  {
                    "IF" : { "text_matches" : { "text" : [ "list-item:line-item-label" ], "match" : "LETTERS_POINTS" } },
                    "DO" : [
                      { "entity_query" : {
                          "USING" : {
                            "type" : "commerce_product",
                            "property" : "sku",
                            "value" : [ "list-item:line-item-label" ],
                            "limit" : "1"
                          },
                          "PROVIDE" : { "entity_fetched" : { "entity_fetched" : "Fetched entity" } }
                        }
                      },
                      { "CONDITIONAL" : [
                          {
                            "IF" : { "entity_has_field" : { "entity" : [ "entity-fetched:0" ], "field" : "field_points_amount" } },
                            "DO" : [
                              { "data_calc" : {
                                  "USING" : {
                                    "input_1" : [ "list-item:quantity" ],
                                    "op" : "*",
                                    "input_2" : [ "entity-fetched:0:field-points-amount" ]
                                  },
                                  "PROVIDE" : { "result" : { "result" : "Calculation result" } }
                                }
                              },
                              { "data_convert" : {
                                  "USING" : { "type" : "integer", "value" : [ "result" ] },
                                  "PROVIDE" : { "conversion_result" : { "int_points_result" : "Integer points result" } }
                                }
                              },
                              { "userpoints_action_grant_points" : {
                                  "user" : [ "list-item:order:owner" ],
                                  "points" : [ "int-points-result" ],
                                  "tid" : "2",
                                  "entity" : [ "" ],
                                  "description" : "[commerce-order:owner] buy [result:value] points (sending letters).",
                                  "operation" : "[commerce-order:owner] buy [result:value] points (sending letters).",
                                  "display" : "1",
                                  "moderate" : "approved"
                                }
                              }
                            ]
                          }
                        ]
                      }
                    ]
                  }
                ]
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_link_condition__cloned'] = entity_import('rules_config', '{ "rules_link_condition__cloned" : {
      "LABEL" : "Rules link: Get Owner Button (cloned) condition",
      "PLUGIN" : "and",
      "OWNER" : "rules",
      "USES VARIABLES" : { "node" : { "type" : "node", "label" : "node" } },
      "AND" : []
    }
  }');
  $items['rules_link_condition_buy_owner_info'] = entity_import('rules_config', '{ "rules_link_condition_buy_owner_info" : {
      "LABEL" : "Rules link: Buy Owner Info Request Points condition",
      "PLUGIN" : "and",
      "OWNER" : "rules",
      "USES VARIABLES" : { "node" : { "type" : "node", "label" : "node" } },
      "AND" : []
    }
  }');
  $items['rules_link_condition_buy_sending_letter'] = entity_import('rules_config', '{ "rules_link_condition_buy_sending_letter" : {
      "LABEL" : "Rules link: Buy Ability to Send Letter condition",
      "PLUGIN" : "and",
      "OWNER" : "rules",
      "USES VARIABLES" : { "node" : { "label" : "node", "type" : "node" } },
      "AND" : []
    }
  }');
  $items['rules_link_set_'] = entity_import('rules_config', '{ "rules_link_set_" : {
      "LABEL" : "Rules link:  rules set",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "USES VARIABLES" : { "" : { "type" : null, "label" : null } },
      "RULES" : []
    }
  }');
  $items['rules_link_set_buy_owner_info'] = entity_import('rules_config', '{ "rules_link_set_buy_owner_info" : {
      "LABEL" : "Rules link: Buy Owner Info Request Points rules set",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "REQUIRES" : [ "commerce_cart" ],
      "USES VARIABLES" : { "node" : { "label" : "node", "type" : "node" } },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : { "product_add_line_item" : { "product_add_line_item" : "Added product line item" } },
            "DO" : [
              { "commerce_cart_product_add_by_sku" : {
                  "USING" : {
                    "user" : [ "site:current-cart-order:owner" ],
                    "sku" : "OWNER_INFO_POINTS",
                    "quantity" : "1",
                    "combine" : "1"
                  },
                  "PROVIDE" : { "product_add_line_item" : { "product_add_line_item" : "Added product line item" } }
                }
              }
            ],
            "LABEL" : "Buy points (for owner info)"
          }
        }
      ]
    }
  }');
  $items['rules_link_set_buy_sending_letter'] = entity_import('rules_config', '{ "rules_link_set_buy_sending_letter" : {
      "LABEL" : "Rules link: Buy Ability to Send Letter rules set",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "REQUIRES" : [ "commerce_cart" ],
      "USES VARIABLES" : { "node" : { "label" : "node", "type" : "node" } },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : { "product_add_line_item" : { "product_add_line_item" : "Added product line item" } },
            "DO" : [
              { "commerce_cart_product_add_by_sku" : {
                  "USING" : {
                    "user" : [ "site:current-cart-order:owner" ],
                    "sku" : "LETTERS_POINTS",
                    "quantity" : "1",
                    "combine" : "1"
                  },
                  "PROVIDE" : { "product_add_line_item" : { "product_add_line_item" : "Added product line item" } }
                }
              }
            ],
            "LABEL" : "Buy points (for send letters)"
          }
        }
      ]
    }
  }');
  return $items;
}
