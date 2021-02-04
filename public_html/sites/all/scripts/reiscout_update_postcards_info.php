#!/usr/bin/env drush

/**
 * Requests from Lob API info about postcards sent
 * and updates corresponding data in DB.
 */
function reiscout_update_postcards_info() {
  require_once libraries_get_path('lob') . '/vendor/autoload.php';
  $lob_api_key = variable_get('lob_api_key');
  $lob = new \Lob\Lob($lob_api_key);
  $events = new Events();

  $args = array(
    'offset' => 0,
    'limit' => 50, // number of postcards to process
  );

  if ($postcards = $lob->postcards()->all($args)) {
    foreach ($postcards as $postcard) {
      $q_args = array(
        ':date' => strtotime($postcard['expected_delivery_date']),
        ':id' => $postcard['id'],
      );
      db_query('UPDATE {reiscout_mail_postcard_history}
               SET `expected_delivery_date` = :date
               WHERE `lob_api_postcard_id` = :id', $q_args);
      foreach ($postcard['tracking_events'] as $event) {
        $events->log($postcard['id'], $event);
      }
    }
  }
}

reiscout_update_postcards_info();
