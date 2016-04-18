<?php
/**
 * @file
 * property.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function property_default_rules_configuration() {
  $items = array();
  $items['rules_address_reverse_geocode'] = entity_import('rules_config', '{ "rules_address_reverse_geocode" : {
      "LABEL" : "Address reverse geocode",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "TAGS" : [ "reiscout" ],
      "REQUIRES" : [ "rules", "geocoder_rules" ],
      "ON" : { "node_presave--property" : { "bundle" : "property" } },
      "IF" : [
        { "entity_is_of_type" : { "entity" : [ "node" ], "type" : "node" } },
        { "entity_is_of_bundle" : {
            "entity" : [ "node" ],
            "type" : "node",
            "bundle" : { "value" : { "property" : "property" } }
          }
        },
        { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_geo_position" } },
        { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_address_text" } },
        { "NOT data_is_empty" : { "data" : [ "node:field-geo-position:lat" ] } },
        { "NOT data_is_empty" : { "data" : [ "node:field-geo-position:lon" ] } },
        { "data_is_empty" : { "data" : [ "node:field-address-text" ] } }
      ],
      "DO" : [
        { "geocoder_rules_reverse_geocode" : {
            "USING" : {
              "handler" : "google",
              "latitude" : [ "node:field-geo-position:lat" ],
              "longitude" : [ "node:field-geo-position:lon" ],
              "language" : "en"
            },
            "PROVIDE" : {
              "address" : { "address" : "Geodecoded Address" },
              "accuracy" : { "accuracy" : "Geodecoded Accuracy" }
            }
          }
        },
        { "data_set" : { "data" : [ "node:field-address-text" ], "value" : "[address:value]" } }
      ]
    }
  }');
  $items['rules_set_created_property_node_staus_to_published'] = entity_import('rules_config', '{ "rules_set_created_property_node_staus_to_published" : {
      "LABEL" : "Set created property node staus to published",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "reiscout" ],
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert--property" : { "bundle" : "property" } },
      "DO" : [ { "node_publish" : { "node" : [ "node" ] } } ]
    }
  }');
  return $items;
}
