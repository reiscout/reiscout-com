<?php
/**
 * @file
 * reiscout_mail_feature.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function reiscout_mail_feature_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Two Columns Front',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 0,
    'machine_name' => 'two_columns_front',
    'uuid' => '57ba5f12-89ae-4b06-a6ca-a397f4463bd5',
    'vocabulary_machine_name' => 'postcard_design_templates',
  );
  $terms[] = array(
    'name' => 'Real Estate (text)',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 0,
    'machine_name' => 'real_estate_text',
    'uuid' => 'cdc7d70d-194d-45e0-8ef8-c7af2cd21d16',
    'vocabulary_machine_name' => 'postcard_design_templates',
  );
  $terms[] = array(
    'name' => 'Roofing',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 0,
    'machine_name' => 'roofing',
    'uuid' => 'df0509be-361d-4b61-ab0b-5e99ab4976e1',
    'vocabulary_machine_name' => 'postcard_design_templates',
  );
  $terms[] = array(
    'name' => 'Image Front',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 0,
    'machine_name' => 'image_front',
    'uuid' => 'e61734df-ae87-4875-a4fb-d55c77d77f59',
    'vocabulary_machine_name' => 'postcard_design_templates',
  );
  return $terms;
}
