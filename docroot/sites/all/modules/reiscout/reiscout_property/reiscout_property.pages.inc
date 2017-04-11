<?php

/**
 * @file
 * Page callback file for the Reiscout Property module.
 */

/**
 * Page callback: returns a Connect2Data info for a given property.
 */
function reiscout_property_get_c2d_report_page($nid) {
  // Make a request to the Connect2Data API to get full info about property
  if (!$report = _reiscout_property_get_c2d_report_by_nid($nid, 'c2d_report_page')) {
    $message = t('An error occurred while requesting the information about property.');
    drupal_set_message($message, 'error');
    return t('No data');
  }

  // Return data as a parsed object in a text plain file
  $data = print_r($report, TRUE);
  if ($file_uri = file_unmanaged_save_data($data)) {
    $headers = array(
      'Cache-Control' => 'private',
      'Content-Type' => 'text/plain',
      'Content-Disposition' => 'attachment; filename=connect2data.txt',
      'Content-Length' => filesize($file_uri),
    );
    file_transfer($file_uri, $headers);
  }
}
