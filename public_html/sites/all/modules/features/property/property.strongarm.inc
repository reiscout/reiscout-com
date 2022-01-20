<?php

/**
 * @file
 * property.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function property_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'auto_entitylabel_node_property';
  $strongarm->value = '1';
  $export['auto_entitylabel_node_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'auto_entitylabel_pattern_node_property';
  $strongarm->value = 'Property #[node:nid]';
  $export['auto_entitylabel_pattern_node_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'auto_entitylabel_php_node_property';
  $strongarm->value = 0;
  $export['auto_entitylabel_php_node_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_property';
  $strongarm->value = 0;
  $export['comment_anonymous_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_property';
  $strongarm->value = 1;
  $export['comment_default_mode_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_property';
  $strongarm->value = '50';
  $export['comment_default_per_page_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_property';
  $strongarm->value = 1;
  $export['comment_form_location_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_property';
  $strongarm->value = '1';
  $export['comment_preview_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_property';
  $strongarm->value = '1';
  $export['comment_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_property';
  $strongarm->value = 1;
  $export['comment_subject_field_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_property';
  $strongarm->value = 1;
  $export['diff_enable_revisions_page_node_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_property';
  $strongarm->value = 1;
  $export['diff_show_preview_changes_node_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_property';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__property';
  $strongarm->value = array(
    'extra_fields' => array(
      'display' => array(
        'address' => array(
          'default' => array(
            'visible' => TRUE,
            'weight' => '3',
          ),
          'drupalgap' => array(
            'visible' => FALSE,
            'weight' => '39',
          ),
          'full' => array(
            'visible' => TRUE,
            'weight' => '6',
          ),
        ),
        'product:commerce_price' => array(
          'default' => array(
            'visible' => TRUE,
            'weight' => '5',
          ),
          'drupalgap' => array(
            'visible' => FALSE,
            'weight' => '43',
          ),
          'full' => array(
            'visible' => FALSE,
            'weight' => '27',
          ),
        ),
        'product:field_property' => array(
          'default' => array(
            'visible' => TRUE,
            'weight' => '17',
          ),
          'drupalgap' => array(
            'visible' => TRUE,
            'weight' => '30',
          ),
          'full' => array(
            'visible' => FALSE,
            'weight' => '23',
          ),
        ),
        'product:sku' => array(
          'default' => array(
            'visible' => FALSE,
            'weight' => '47',
          ),
          'drupalgap' => array(
            'visible' => FALSE,
            'weight' => '44',
          ),
          'full' => array(
            'visible' => FALSE,
            'weight' => '25',
          ),
        ),
        'product:status' => array(
          'default' => array(
            'visible' => FALSE,
            'weight' => '49',
          ),
          'drupalgap' => array(
            'visible' => FALSE,
            'weight' => '46',
          ),
          'full' => array(
            'visible' => FALSE,
            'weight' => '28',
          ),
        ),
        'product:title' => array(
          'default' => array(
            'visible' => FALSE,
            'weight' => '48',
          ),
          'drupalgap' => array(
            'visible' => FALSE,
            'weight' => '45',
          ),
          'full' => array(
            'visible' => FALSE,
            'weight' => '26',
          ),
        ),
        'reiscout-mail-buttons' => array(
          'default' => array(
            'visible' => TRUE,
            'weight' => '4',
          ),
          'drupalgap' => array(
            'visible' => FALSE,
            'weight' => '38',
          ),
          'full' => array(
            'visible' => TRUE,
            'weight' => '24',
          ),
        ),
        'reiscout-number-of-property-lead-sales' => array(
          'default' => array(
            'visible' => TRUE,
            'weight' => '0',
          ),
          'drupalgap' => array(
            'visible' => TRUE,
            'weight' => '0',
          ),
          'full' => array(
            'visible' => TRUE,
            'weight' => '3',
          ),
        ),
        'reiscout-property-data-form' => array(
          'default' => array(
            'visible' => TRUE,
            'weight' => '1',
          ),
          'drupalgap' => array(
            'visible' => TRUE,
            'weight' => '1',
          ),
          'full' => array(
            'visible' => TRUE,
            'weight' => '1',
          ),
        ),
        'reiscout-property-lead-form' => array(
          'default' => array(
            'visible' => TRUE,
            'weight' => '2',
          ),
          'drupalgap' => array(
            'visible' => TRUE,
            'weight' => '2',
          ),
          'full' => array(
            'visible' => TRUE,
            'weight' => '0',
          ),
        ),
      ),
      'form' => array(
        'path' => array(
          'weight' => '21',
        ),
        'title' => array(
          'weight' => '1',
        ),
      ),
    ),
    'view_modes' => array(
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'drupalgap' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => TRUE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => FALSE,
      ),
      'teaser' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
  );
  $export['field_bundle_settings_node__property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_property';
  $strongarm->value = array();
  $export['menu_options_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_property';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_property';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_property';
  $strongarm->value = '0';
  $export['node_preview_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_property';
  $strongarm->value = 0;
  $export['node_submitted_property'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_property_pattern';
  $strongarm->value = 'property/[node:nid]';
  $export['pathauto_node_property_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_term_data_quality_tags_pattern';
  $strongarm->value = '';
  $export['pathauto_taxonomy_term_data_quality_tags_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_settings';
  $strongarm->value = array(
    'default_favicon' => 0,
    'default_logo' => 0,
    'favicon_mimetype' => 'image/vnd.microsoft.icon',
    'favicon_path' => 'sites/all/themes/reiscout_bootstrap/favicon.ico',
    'favicon_upload' => '',
    'logo_path' => 'sites/all/themes/reiscout_bootstrap/logo.png',
    'logo_upload' => '',
    'toggle_comment_user_picture' => 1,
    'toggle_comment_user_verification' => 1,
    'toggle_favicon' => 1,
    'toggle_logo' => 1,
    'toggle_main_menu' => 1,
    'toggle_name' => 1,
    'toggle_node_user_picture' => 1,
    'toggle_secondary_menu' => 1,
    'toggle_slogan' => 1,
  );
  $export['theme_settings'] = $strongarm;

  return $export;
}
