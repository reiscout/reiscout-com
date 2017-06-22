<?php
/**
 * @file
 * reiscout_data_quality_tags.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function reiscout_data_quality_tags_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Owner contacts',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 0,
    'machine_name' => 'owner_contacts',
    'uuid' => '3ce39630-afd5-4afb-a9df-e804cd9b6673',
    'vocabulary_machine_name' => 'data_quality_tags',
  );
  $terms[] = array(
    'name' => 'Fully populated',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 1,
    'machine_name' => 'fully_populated',
    'uuid' => '5bc252c6-d983-4035-8cbf-7389b958a769',
    'vocabulary_machine_name' => 'data_quality_tags',
  );
  $terms[] = array(
    'name' => 'Verified data',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 2,
    'machine_name' => 'verified_data',
    'uuid' => 'c35e891f-2c63-4a35-adf8-47e2d972499f',
    'vocabulary_machine_name' => 'data_quality_tags',
  );
  return $terms;
}
