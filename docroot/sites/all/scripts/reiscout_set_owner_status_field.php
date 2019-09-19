#!/usr/bin/env drush

function reiscout_set_owner_status_field() {
  $transaction = db_transaction();

  $query = db_select('node', 'n');
  $query->leftJoin('field_data_field_owner_status', 'fos', 'nid = entity_id');
  $query
    ->fields('n', array('nid'))
    ->condition('type', 'property')
    ->isNull('field_owner_status_value');

  if (!$nids = $query->execute()->fetchCol()) {
    return;
  }

  foreach ($nids as $nid) {
    $nw = entity_metadata_wrapper('node', $nid);

    if (_reiscout_property_is_address_filled_by_nid($nw)
     && Property::isOwnerAddressFilledOut($nw->field_owner_postal_address)) {
      $nw->field_owner_status = _reiscout_property_determine_owner_status($nw->field_address, $nw->field_owner_postal_address);
    }

    $nw->save();
  }
}

reiscout_set_owner_status_field();
