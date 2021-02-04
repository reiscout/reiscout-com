<?php
/**
 * @file
 * reiscout_map_atlanta_content_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function reiscout_map_atlanta_content_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
