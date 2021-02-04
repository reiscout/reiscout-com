<?php
/**
 * @file
 * reiscout_video_tutorial.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function reiscout_video_tutorial_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'video_tutorials';
  $view->description = 'Returns a list of \'Video tutorial\' nodes in JSON format.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Video tutorials';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_json';
  $handler->display->display_options['style_options']['plaintext_output'] = 1;
  $handler->display->display_options['style_options']['remove_newlines'] = 0;
  $handler->display->display_options['style_options']['jsonp_prefix'] = '';
  $handler->display->display_options['style_options']['using_views_api_mode'] = 0;
  $handler->display->display_options['style_options']['object_arrays'] = 0;
  $handler->display->display_options['style_options']['numeric_strings'] = 0;
  $handler->display->display_options['style_options']['bigint_string'] = 0;
  $handler->display->display_options['style_options']['pretty_print'] = 0;
  $handler->display->display_options['style_options']['unescaped_slashes'] = 0;
  $handler->display->display_options['style_options']['unescaped_unicode'] = 0;
  $handler->display->display_options['style_options']['char_encoding'] = array();
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: ID of the wrapper div */
  $handler->display->display_options['fields']['field_wrapper_div_id']['id'] = 'field_wrapper_div_id';
  $handler->display->display_options['fields']['field_wrapper_div_id']['table'] = 'field_data_field_wrapper_div_id';
  $handler->display->display_options['fields']['field_wrapper_div_id']['field'] = 'field_wrapper_div_id';
  $handler->display->display_options['fields']['field_wrapper_div_id']['label'] = 'id';
  /* Field: Content: URL of the video */
  $handler->display->display_options['fields']['field_video_file_url']['id'] = 'field_video_file_url';
  $handler->display->display_options['fields']['field_video_file_url']['table'] = 'field_data_field_video_file_url';
  $handler->display->display_options['fields']['field_video_file_url']['field'] = 'field_video_file_url';
  $handler->display->display_options['fields']['field_video_file_url']['label'] = 'video_src';
  /* Field: Content: Poster */
  $handler->display->display_options['fields']['field_video_poster']['id'] = 'field_video_poster';
  $handler->display->display_options['fields']['field_video_poster']['table'] = 'field_data_field_video_poster';
  $handler->display->display_options['fields']['field_video_poster']['field'] = 'field_video_poster';
  $handler->display->display_options['fields']['field_video_poster']['label'] = 'poster';
  $handler->display->display_options['fields']['field_video_poster']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_video_poster']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'video_tutorial' => 'video_tutorial',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'drupalgap/views_datasource/video_tutorials';
  $export['video_tutorials'] = $view;

  return $export;
}
