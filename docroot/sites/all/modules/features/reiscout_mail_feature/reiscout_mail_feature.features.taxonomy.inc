<?php
/**
 * @file
 * reiscout_mail_feature.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function reiscout_mail_feature_taxonomy_default_vocabularies() {
  return array(
    'postcard_design_templates' => array(
      'name' => 'Postcard design templates',
      'machine_name' => 'postcard_design_templates',
      'description' => 'Allows to classify postcard templates by their design',
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
