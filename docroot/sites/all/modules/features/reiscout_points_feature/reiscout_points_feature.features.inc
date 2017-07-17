<?php
/**
 * @file
 * reiscout_points_feature.features.inc
 */

/**
 * Implements hook_commerce_product_default_types().
 */
function reiscout_points_feature_commerce_product_default_types() {
  $items = array(
    'points_owner' => array(
      'type' => 'points_owner',
      'name' => 'Points',
      'description' => 'Commerce product to get paid points.',
      'help' => '',
      'revision' => 0,
    ),
  );
  return $items;
}

/**
 * Implements hook_ctools_plugin_api().
 */
function reiscout_points_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_rules_link().
 */
function reiscout_points_feature_default_rules_link() {
  $items = array();
  $items['buy_owner_info'] = entity_import('rules_link', '{
    "settings" : {
      "text" : "Buy Ability to Get Owner Info",
      "link_type" : "token",
      "bundles" : { "property" : "property" },
      "entity_link" : 0,
      "view_mode" : { "full" : "full", "drupalgap" : "drupalgap" },
      "confirm_question" : "Are you sure?",
      "confirm_description" : ""
    },
    "name" : "buy_owner_info",
    "label" : "Buy Ability to Get Owner Info",
    "path" : "buy_owner_info",
    "entity_type" : "node",
    "rdf_mapping" : []
  }');
  $items['buy_sending_letter'] = entity_import('rules_link', '{
    "settings" : {
      "text" : "Buy Ability to Send Mail",
      "link_type" : "token",
      "bundles" : { "property" : "property" },
      "entity_link" : 0,
      "view_mode" : { "full" : "full", "drupalgap" : "drupalgap" },
      "confirm_question" : "Are you sure?",
      "confirm_description" : ""
    },
    "name" : "buy_sending_letter",
    "label" : "Buy Ability to Send Mail",
    "path" : "buy_sending_letter",
    "entity_type" : "node",
    "rdf_mapping" : []
  }');
  return $items;
}
