<?php
/**
 * @file
 * reiscout_video_tutorial.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function reiscout_video_tutorial_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-video_tutorial-field_video_file_url'.
  $field_instances['node-video_tutorial-field_video_file_url'] = array(
    'bundle' => 'video_tutorial',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'For example, <em>https://www.w3schools.com/html/mov_bbb.mp4</em>',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_video_file_url',
    'label' => 'URL of the video',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-video_tutorial-field_video_poster'.
  $field_instances['node-video_tutorial-field_video_poster'] = array(
    'bundle' => 'video_tutorial',
    'deleted' => 0,
    'description' => 'An image to be shown while the video is downloading, or until the user hits the play button.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 3,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_video_poster',
    'label' => 'Poster',
    'required' => 1,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => 'images/video',
      'file_extensions' => 'jpg',
      'max_filesize' => '100 KB',
      'max_resolution' => '576x360',
      'min_resolution' => '576x360',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-video_tutorial-field_wrapper_div_id'.
  $field_instances['node-video_tutorial-field_wrapper_div_id'] = array(
    'bundle' => 'video_tutorial',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The ID will be used as an anchor to navigate to the needed video',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'drupalgap' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_wrapper_div_id',
    'label' => 'ID of the wrapper div',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('An image to be shown while the video is downloading, or until the user hits the play button.');
  t('For example, <em>https://www.w3schools.com/html/mov_bbb.mp4</em>');
  t('ID of the wrapper div');
  t('Poster');
  t('The ID will be used as an anchor to navigate to the needed video');
  t('URL of the video');

  return $field_instances;
}
