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
    'name' => 'Point',
    'description' => 'A user can use this type of userpoints for buying such products as \'Property Lead\', \'Pull Property Data\' and \'Send a Postcard\'',
    'format' => 'plain_text',
    'weight' => 0,
    'machine_name' => 'point',
    'uuid' => 'b4bd66ff-f570-46a8-9ed5-7dba32659dc2',
    'vocabulary_machine_name' => 'userpoints',
  );

  return $terms;
}
