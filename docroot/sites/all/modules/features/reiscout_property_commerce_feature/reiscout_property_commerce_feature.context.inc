<?php
/**
 * @file
 * reiscout_property_commerce_feature.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function reiscout_property_commerce_feature_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'reiscout_property_commerce_admin_form';
  $context->description = '';
  $context->tag = 'reiscout_property_commerce';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'admin/commerce/config/reiscout' => 'admin/commerce/config/reiscout',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-1' => array(
          'module' => 'block',
          'delta' => '1',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
        'devel-execute_php' => array(
          'module' => 'devel',
          'delta' => 'execute_php',
          'region' => 'preface_first',
          'weight' => '-10',
        ),
        'views-property_listing-block_1' => array(
          'module' => 'views',
          'delta' => 'property_listing-block_1',
          'region' => 'content',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('reiscout_property_commerce');
  $export['reiscout_property_commerce_admin_form'] = $context;

  return $export;
}
