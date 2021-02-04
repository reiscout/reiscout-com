#!/usr/bin/env drush

function reiscout_activate_place_on_marketplace_field() {
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
    $nw = entity_metadata_wrapper('node', $nid);
    $nw->field_place_on_marketplace = 1;
    $nw->save();
  }
}

reiscout_activate_place_on_marketplace_field();
