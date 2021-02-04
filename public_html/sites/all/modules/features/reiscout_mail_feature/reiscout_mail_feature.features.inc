<?php
/**
 * @file
 * reiscout_mail_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function reiscout_mail_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function reiscout_mail_feature_node_info() {
  $items = array(
    'letter_template' => array(
      'name' => t('Letter template'),
      'base' => 'node_content',
      'description' => t('Use <em>Letter templates</em> for creating letters that will be sent to an owner of a property.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'postcard_template' => array(
      'name' => t('Postcard template'),
      'base' => 'node_content',
      'description' => t('Use <em>Postcard templates</em> for creating postcards that will be sent to an owner of a property.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
