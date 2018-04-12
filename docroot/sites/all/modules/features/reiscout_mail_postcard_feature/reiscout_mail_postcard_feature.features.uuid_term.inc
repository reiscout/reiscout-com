<?php
/**
 * @file
 * reiscout_mail_postcard_feature.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function reiscout_mail_postcard_feature_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'HVAC Repair',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 0,
    'machine_name' => 'hvac_repair',
    'uuid' => '682d9936-0a56-4015-9304-371e6f79c549',
    'vocabulary_machine_name' => 'postcard_design_templates',
  );
  $terms[] = array(
    'name' => 'General Trades',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 0,
    'machine_name' => 'general_trades',
    'uuid' => '8e938c3b-e2c4-494e-9def-dc4e4c9ec127',
    'vocabulary_machine_name' => 'postcard_design_templates',
  );
  $terms[] = array(
    'name' => 'Women Fitness',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 0,
    'machine_name' => 'women_fitness',
    'uuid' => '9208dd5b-9971-455f-8896-161cfc7e731e',
    'vocabulary_machine_name' => 'postcard_design_templates',
  );
  $terms[] = array(
    'name' => 'Tree Service',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 0,
    'machine_name' => 'tree_service',
    'uuid' => '95f00936-f3f5-401c-81e2-61df59bcba09',
    'vocabulary_machine_name' => 'postcard_design_templates',
  );
  $terms[] = array(
    'name' => 'Roofing Raindrops',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 0,
    'machine_name' => 'roofing_raindrops',
    'uuid' => 'c5eb537d-63b9-45a3-8b51-3f5fde1296b7',
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
    'name' => 'Garage Door Repair',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 0,
    'machine_name' => 'garage_door_repair',
    'uuid' => 'ce124360-d844-49c8-8bdb-5bc1a1ad144c',
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
    'name' => 'Lawn Care',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 0,
    'machine_name' => 'lawn_care',
    'uuid' => 'f1354e65-975a-471b-80cc-f445fc5f9fb7',
    'vocabulary_machine_name' => 'postcard_design_templates',
  );
  return $terms;
}
