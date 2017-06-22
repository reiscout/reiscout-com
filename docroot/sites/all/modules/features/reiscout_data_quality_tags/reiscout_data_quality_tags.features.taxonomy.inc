<?php
/**
 * @file
 * reiscout_data_quality_tags.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function reiscout_data_quality_tags_taxonomy_default_vocabularies() {
  return array(
    'data_quality_tags' => array(
      'name' => 'Data Quality Tags',
      'machine_name' => 'data_quality_tags',
      'description' => 'Allows to classify properties by quality of its data',
      'hierarchy' => 0,
      'module' => 'taxonomy',
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
