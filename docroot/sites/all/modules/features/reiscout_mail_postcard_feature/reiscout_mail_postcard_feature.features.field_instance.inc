<?php
/**
 * @file
 * reiscout_mail_postcard_feature.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function reiscout_mail_postcard_feature_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'node-postcard_template-field_postcard_template_back'.
  $field_instances['node-postcard_template-field_postcard_template_back'] = array(
    'bundle' => 'postcard_template',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The content to use as the back of your postcard.<br>
You can use these tokens: <em>{{owner_name}}</em> - full name of a property owner, <em>{{street_address}}</em> - property street address, <em>{{city}}</em> - property city name, <em>{{my_phone}}</em> - your phone from your <a href="/user">user profile</a>.',
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
    'field_name' => 'field_postcard_template_back',
    'label' => 'Back',
    'required' => 1,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 15,
      ),
      'type' => 'text_textarea',
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'node-postcard_template-field_postcard_template_front'.
  $field_instances['node-postcard_template-field_postcard_template_front'] = array(
    'bundle' => 'postcard_template',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The content to use as the front of your postcard.<br>
You can use these tokens: <em>{{owner_name}}</em> - full name of a property owner, <em>{{street_address}}</em> - property street address, <em>{{city}}</em> - property city name, <em>{{my_phone}}</em> - your phone from your <a href="/user">user profile</a>.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
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
    'field_name' => 'field_postcard_template_front',
    'label' => 'Front',
    'required' => 1,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 15,
      ),
      'type' => 'text_textarea',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'node-postcard_template-field_postcard_template_global'.
  $field_instances['node-postcard_template-field_postcard_template_global'] = array(
    'bundle' => 'postcard_template',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'If checked, all the users will be able to use this template.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
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
    'field_name' => 'field_postcard_template_global',
    'label' => 'Global template',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 3,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Back');
  t('Front');
  t('Global template');
  t('If checked, all the users will be able to use this template.');
  t('The content to use as the back of your postcard.<br>
You can use these tokens: <em>{{owner_name}}</em> - full name of a property owner, <em>{{street_address}}</em> - property street address, <em>{{city}}</em> - property city name, <em>{{my_phone}}</em> - your phone from your <a href="/user">user profile</a>.');
  t('The content to use as the front of your postcard.<br>
You can use these tokens: <em>{{owner_name}}</em> - full name of a property owner, <em>{{street_address}}</em> - property street address, <em>{{city}}</em> - property city name, <em>{{my_phone}}</em> - your phone from your <a href="/user">user profile</a>.');

  return $field_instances;
}
