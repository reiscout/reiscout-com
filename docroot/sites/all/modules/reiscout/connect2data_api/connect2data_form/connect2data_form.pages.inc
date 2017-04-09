<?php

/**
 * @file
 * Page callback file for the Connect2Data Form module.
 */

/**
 * Form builder; a form for requesting data from the CoreLogic Connect2Data.
 */
function connect2data_form() {
  $form['street_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#description' => t('For example, %example', array('%example' => '2735 Williamsburg Way')),
    '#required' => TRUE,
  );

  $form['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#description' => t('For example, %example', array('%example' => 'Decatur')),
    '#required' => TRUE,
  );

  $form['state'] = array(
    '#type' => 'textfield',
    '#title' => t('State'),
    '#description' => t('For example, %example', array('%example' => 'GA')),
    '#required' => TRUE,
  );

  $form['postal_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal code'),
    '#description' => t('For example, %example', array('%example' => '30034')),
    '#required' => TRUE,
  );

  $form['data_format'] = array(
    '#type' => 'radios',
    '#title' => t('Data format'),
    '#options' => array(
      'xml' => 'xml',
      'parsed'=> 'parsed',
    ),
    '#default_value' => 'xml',
    '#required' => TRUE,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Get data'),
  );

  return $form;
}

/**
 * Form submission handler for connect2data_form().
 *
 * @see connect2data_form()
 */
function connect2data_form_submit($form, &$form_state) {
  $property_criteria = array(
    'street_address' => $form_state['values']['street_address'],
    'city' => $form_state['values']['city'],
    'state' => $form_state['values']['state'],
    'postal_code' => $form_state['values']['postal_code'],
  );

  if (!$report = connect2data_api_get_detailed_subject_report($property_criteria)) {
    $message = t('There are no data for the address provided. Please check if the address is valid.');
    drupal_set_message($message, 'error');
    return FALSE;
  }

  if ('xml' == $form_state['values']['data_format']) {
    $data = $report->asXML();
    if ($file_uri = file_unmanaged_save_data($data)) {
      $headers = array(
        'Cache-Control' => 'private',
        'Content-Type' => 'text/xml',
        'Content-Disposition' => 'attachment; filename=connect2data.xml',
        'Content-Length' => filesize($file_uri),
      );
      file_transfer($file_uri, $headers);
    }
  }
  else {
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
}
