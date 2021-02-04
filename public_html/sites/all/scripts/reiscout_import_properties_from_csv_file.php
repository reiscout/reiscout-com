#!/usr/bin/env drush

define('CSV_FILE_PATH', 'public://properties.csv');
define('UID_TO_IMPORT_TO', 10);

function reiscout_import_properties_from_csv_file() {
  $csv = file(CSV_FILE_PATH);
  array_shift($csv);
  $csv = array_map('trim', $csv);

  for ($i = 0, $len = sizeof($csv); $i < $len; ++$i) {
    $csv[$i] = explode(';', $csv[$i]);

    $node = entity_create('node', array('type' => 'property'));
    $node->uid = UID_TO_IMPORT_TO;

    $nw = entity_metadata_wrapper('node', $node);

    // Property Address
    $nw->field_address->country = 'US';
    $nw->field_address->thoroughfare = $csv[$i][9];
    $nw->field_address->locality = $csv[$i][10];
    $nw->field_address->administrative_area = $csv[$i][11];

    if ($zip = explode('-', $csv[$i][12])) {
      $zip = $zip[0];
    }
    else {
      $zip = $csv[$i][12];
    }
    $nw->field_address->postal_code = $zip;

    // Owner Info
    $nw->field_owner_postal_address->name_line = NULL;
    $nw->field_owner_postal_address->first_name = $csv[$i][2] . ($csv[$i][3] ? ' ' . $csv[$i][3] : '');
    $nw->field_owner_postal_address->last_name = $csv[$i][4];

    $nw->field_owner_postal_address->country = 'US';
    $nw->field_owner_postal_address->thoroughfare = $csv[$i][5];
    $nw->field_owner_postal_address->locality = $csv[$i][6];
    $nw->field_owner_postal_address->administrative_area = $csv[$i][7];

    if ($zip = explode('-', $csv[$i][8])) {
      $zip = $zip[0];
    }
    else {
      $zip = $csv[$i][8];
    }
    $nw->field_owner_postal_address->postal_code = $zip;

    if ($csv[$i][13]) {
      $nw->field_gross_area = $csv[$i][13];
    }

    if ($csv[$i][14]) {
      $nw->field_year_built = $csv[$i][14];
    }

    if ($csv[$i][15]) {
      $nw->field_lot_area_acres = $csv[$i][15];
    }

    $nw->save();
  }
}

reiscout_import_properties_from_csv_file();
