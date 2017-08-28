<?php
/**
 * @file
 * reiscout_video_tutorial.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function reiscout_video_tutorial_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function reiscout_video_tutorial_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function reiscout_video_tutorial_node_info() {
  $items = array(
    'video_tutorial' => array(
      'name' => t('Video tutorial'),
      'base' => 'node_content',
      'description' => t('Use <em>Video tutorial</em> for tutorial that will be displayed on the <em>Tutorials</em> page of the mobile application.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
