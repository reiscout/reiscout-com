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
  // 'node-postcard_template-field_postcard_design_template'.
  $field_instances['node-postcard_template-field_postcard_design_template'] = array(
    'bundle' => 'postcard_template',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 4,
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
    'field_name' => 'field_postcard_design_template',
    'label' => 'Design template',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'node-postcard_template-field_postcard_template_back'.
  $field_instances['node-postcard_template-field_postcard_template_back'] = array(
    'bundle' => 'postcard_template',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The content to use as the back of your postcard.<br>
You can use these tokens:
<ul>
<li>{{owner_name}}</em> - the first name of a property owner</li>
<li>{{street_address}}</em> - the street address of a property</li>
<li>{{city}}</em> - the city name of a property</li>
<li>{{my_company}}</em> - the name of your company from your <a href="/user" target="_blank">user profile</a></li>
<li>{{my_phone}}</em> - your phone number from your <a href="/user" target="_blank">user profile</a></li>
<li>{{my_website}}</em> - your website from your <a href="/user" target="_blank">user profile</a></li>
</ul>',
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
      'weight' => 4,
    ),
  );

  // Exported field_instance:
  // 'node-postcard_template-field_postcard_template_front'.
  $field_instances['node-postcard_template-field_postcard_template_front'] = array(
    'bundle' => 'postcard_template',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The content to use as the front of your postcard.<br>
You can use these tokens:
<ul>
<li>{{owner_name}}</em> - the first name of a property owner</li>
<li>{{street_address}}</em> - the street address of a property</li>
<li>{{city}}</em> - the city name of a property</li>
<li>{{my_company}}</em> - the name of your company from your <a href="/user" target="_blank">user profile</a></li>
<li>{{my_phone}}</em> - your phone number from your <a href="/user" target="_blank">user profile</a></li>
<li>{{my_website}}</em> - your website from your <a href="/user" target="_blank">user profile</a></li>
</ul>',
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
    'label' => 'Front (a property owner is an individual)',
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
  // 'node-postcard_template-field_postcard_template_front_co'.
  $field_instances['node-postcard_template-field_postcard_template_front_co'] = array(
    'bundle' => 'postcard_template',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The content to use as the front of your postcard.<br>
You can use these tokens:
<ul>
<li>{{owner_name}}</em> - the name of a corporation</li>
<li>{{street_address}}</em> - the street address of a property</li>
<li>{{city}}</em> - the city name of a property</li>
<li>{{my_company}}</em> - the name of your company from your <a href="/user" target="_blank">user profile</a></li>
<li>{{my_phone}}</em> - your phone number from your <a href="/user" target="_blank">user profile</a></li>
<li>{{my_website}}</em> - your website from your <a href="/user" target="_blank">user profile</a></li>
</ul>',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
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
    'field_name' => 'field_postcard_template_front_co',
    'label' => 'Front (a property owner is a corporation)',
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
      'weight' => 3,
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
      'weight' => 5,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Back');
  t('Design template');
  t('Front (a property owner is a corporation)');
  t('Front (a property owner is an individual)');
  t('Global template');
  t('If checked, all the users will be able to use this template.');
  t('The content to use as the back of your postcard.<br>
You can use these tokens:
<ul>
<li>{{owner_name}}</em> - the first name of a property owner</li>
<li>{{street_address}}</em> - the street address of a property</li>
<li>{{city}}</em> - the city name of a property</li>
<li>{{my_company}}</em> - the name of your company from your <a href="/user" target="_blank">user profile</a></li>
<li>{{my_phone}}</em> - your phone number from your <a href="/user" target="_blank">user profile</a></li>
<li>{{my_website}}</em> - your website from your <a href="/user" target="_blank">user profile</a></li>
</ul>');
  t('The content to use as the front of your postcard.<br>
You can use these tokens:
<ul>
<li>{{owner_name}}</em> - the first name of a property owner</li>
<li>{{street_address}}</em> - the street address of a property</li>
<li>{{city}}</em> - the city name of a property</li>
<li>{{my_company}}</em> - the name of your company from your <a href="/user" target="_blank">user profile</a></li>
<li>{{my_phone}}</em> - your phone number from your <a href="/user" target="_blank">user profile</a></li>
<li>{{my_website}}</em> - your website from your <a href="/user" target="_blank">user profile</a></li>
</ul>');
  t('The content to use as the front of your postcard.<br>
You can use these tokens:
<ul>
<li>{{owner_name}}</em> - the name of a corporation</li>
<li>{{street_address}}</em> - the street address of a property</li>
<li>{{city}}</em> - the city name of a property</li>
<li>{{my_company}}</em> - the name of your company from your <a href="/user" target="_blank">user profile</a></li>
<li>{{my_phone}}</em> - your phone number from your <a href="/user" target="_blank">user profile</a></li>
<li>{{my_website}}</em> - your website from your <a href="/user" target="_blank">user profile</a></li>
</ul>');

  return $field_instances;
}
