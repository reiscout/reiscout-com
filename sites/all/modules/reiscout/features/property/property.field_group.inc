<?php
/**
 * @file
 * property.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function property_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_owner_info|node|property|form';
  $field_group->group_name = 'group_owner_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'property';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Owner Info',
    'weight' => '4',
    'children' => array(
      0 => 'field_owner_fname',
      1 => 'field_owner_lname',
      2 => 'field_owner_address',
      3 => 'field_owner_phone',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-owner-info field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_owner_info|node|property|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Owner Info');

  return $field_groups;
}
