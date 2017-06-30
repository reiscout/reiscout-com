#!/usr/bin/env drush

function reiscout_resave_property_nodes() {
  $transaction = db_transaction();

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'property');
  $result = $query->execute();

  if (!isset($result['node'])) {
    return;
  }

  $nids = array_keys($result['node']);
  foreach ($nids as $nid) {
    $node = node_load($nid);
    node_save($node);
  }
}

reiscout_resave_property_nodes();
