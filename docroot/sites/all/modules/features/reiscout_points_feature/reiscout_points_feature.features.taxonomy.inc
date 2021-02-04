<?php
/**
 * @file
 * reiscout_points_feature.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function reiscout_points_feature_taxonomy_default_vocabularies() {
  return array(
    'userpoints' => array(
      'name' => 'Userpoints',
      'machine_name' => 'userpoints',
      'description' => 'Automatically created by the userpoints module',
      'hierarchy' => 0,
      'module' => 'userpoints',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
