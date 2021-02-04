#!/usr/bin/env drush

function reiscout_copy_values_of_one_field_to_another() {
  $transaction = db_transaction();

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'property')
    ->fieldCondition('field_source');
  $result = $query->execute();

  if (!isset($result['node'])) {
    return;
  }

  $nids = array_keys($result['node']);
  foreach ($nids as $nid) {
    $nw = entity_metadata_wrapper('node', $nid);
    $nw->field_list = $nw->field_source->value();
    $nw->save();
  }
}

reiscout_copy_values_of_one_field_to_another();
