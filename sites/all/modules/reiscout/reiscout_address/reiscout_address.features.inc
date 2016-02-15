<?php
/**
 * @file
 * reiscout_address.features.inc
 */

/**
 * Implements hook_flag_default_flags().
 */
function reiscout_address_flag_default_flags() {
  $flags = array();
  // Exported flag: "address viewed by user".
  $flags['reiscout_address_viewed_by_user'] = array(
    'entity_type' => 'node',
    'title' => 'address viewed by user',
    'global' => 0,
    'types' => array(
      0 => 'property',
    ),
    'flag_short' => 'Flag this item',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Unflag this item',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => 'Unflag not allowed',
    'link_type' => 'normal',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 0,
      'teaser' => 0,
      'rss' => 0,
      'search_index' => 0,
      'search_result' => 0,
      'drupalgap' => 0,
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'api_version' => 3,
    'module' => 'reiscout_address',
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;

}
