#!/usr/bin/env drush

function reiscout_update_fields_using_c2d_data() {
  $transaction = db_transaction();

  // Get a list of Property nodes that 'Owner Address' field is filled
  $query = new EntityFieldQuery;
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'property')
    ->fieldCondition('field_owner_postal_address', 'thoroughfare', '', '!=')
    ->fieldCondition('field_owner_postal_address', 'locality', '', '!=')
    ->fieldCondition('field_owner_postal_address', 'administrative_area', '', '!=')
    ->fieldCondition('field_owner_postal_address', 'postal_code', '', '!=');
  $result = $query->execute();

  if (!isset($result['node'])) {
    return;
  }

  $nids = array_keys($result['node']);
  foreach ($nids as $nid) {
    // Make a request to the Connect2Data API to get full info about property
    if ($info = _reiscout_property_get_c2d_report_by_nid($nid, 'owner_info')) {
      _reiscout_property_update_fields($nid, $info);
    }
  }
}

reiscout_update_fields_using_c2d_data();
