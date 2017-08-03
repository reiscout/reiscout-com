<?php
/**
 * @file
 * reiscout_points_feature.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function reiscout_points_feature_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Paid points (mail sending)',
    'description' => 'Points that is used for send mail',
    'format' => 'plain_text',
    'weight' => 0,
    'machine_name' => 'payed_points_mail_sending',
    'uuid' => '60f4dea3-882f-4bcb-9447-fc59c273dd08',
    'vocabulary_machine_name' => 'userpoints',
  );
  $terms[] = array(
    'name' => 'Paid points (property data pulling)',
    'description' => 'Points that is used for pull a property data',
    'format' => 'plain_text',
    'weight' => 0,
    'machine_name' => 'paid_points_property_data_pulling',
    'uuid' => 'baf37be4-29d8-4040-9f37-47b53e68e4c5',
    'vocabulary_machine_name' => 'userpoints',
  );
  return $terms;
}
