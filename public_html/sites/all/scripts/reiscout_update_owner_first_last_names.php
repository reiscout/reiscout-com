#!/usr/bin/env drush

/**
 * Updates a property owner's name.
 *
 * It makes a property's owner name compatible with format we use,
 * for example, it transforms:
 *
 * - First Name: Kerriann
 * - Last Name: N Stark
 *
 * to
 *
 * - First Name: Kerriann N
 * - Last Name: Stark
 */
function reiscout_update_owner_first_last_names() {
  $nids = db_query("SELECT nid
                    FROM {node} n
                    WHERE type = 'property' AND nid >= 2389")->fetchCol();

  for ($i = 0, $len = sizeof($nids); $i < $len; ++$i) {
    $nw = entity_metadata_wrapper('node', $nids[$i]);

    if ($name = $nw->field_owner_postal_address->name_line->value()) {
      $name = explode(' ', $name);

      if (2 < count($name)) {
        $last_name = array_pop($name);
        $first_name = implode(' ', $name);

        $nw->field_owner_postal_address->name_line = NULL;
        $nw->field_owner_postal_address->first_name = $first_name;
        $nw->field_owner_postal_address->last_name = $last_name;

        $nw->save();
      }
    }
  }
}

reiscout_update_owner_first_last_names();
