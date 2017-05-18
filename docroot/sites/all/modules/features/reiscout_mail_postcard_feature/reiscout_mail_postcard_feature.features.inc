<?php
/**
 * @file
 * reiscout_mail_postcard_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function reiscout_mail_postcard_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function reiscout_mail_postcard_feature_node_info() {
  $items = array(
    'postcard_template' => array(
      'name' => t('HTML template for a postcard'),
      'base' => 'node_content',
      'description' => t('Use <em>HTML template for a postcard</em> for HTML templates which will be used for sending a postcard to an owner of a property.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
