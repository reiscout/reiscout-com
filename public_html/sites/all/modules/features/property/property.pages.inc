<?php

/**
 * @file
 * User page callback file for the Property feature.
 */

/**
 * Form builder; Displays a list of properties in table form.
 *
 * @see property_table_form_submit()
 */
function property_table_form($form, $form_state) {
  drupal_set_title('My Properties');

  PropertyTableForm::attachFilters($form);
  PropertyTableForm::attachShowingRowsInfo($form);
  PropertyTableForm::attachPropertyList($form);

  $form['#attached']['js'][] = drupal_get_path('module', 'property') . '/property.table_form.js';
  $form['#attached']['css'][] = drupal_get_path('module', 'property') . '/property.table_form.css';

  return $form;
}

/**
 * Form submission handler for property_table_form().
 *
 * @see property_table_form()
 */
function property_table_form_submit($form, &$form_state) {
  if (t('Filter') == $form_state['values']['op']) {
    PropertyTableForm::setFilters($form_state['values']);
  }
  else {
    PropertyTableForm::clearFilters();
  }

  if (isset($_GET['page'])) {
    unset($_GET['page']);
  }
}

/**
 * Form builder; Allows to import properties from a XLSX document.
 *
 * @see property_import_form_validate()
 * @see property_import_form_submit()
 */
function property_import_form($form, $form_state) {
  $form['file'] = array(
    '#type' => 'file',
    '#title' => t('XLSX document'),
    '#description' => t('Allowed file extensions: <strong>xlsx</strong>.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );

  return $form;
}

/**
 * Form validation handler for property_import_form().
 *
 * @see property_import_form()
 */
function property_import_form_validate($form, &$form_state) {
  // Save the file as a temporary file.
  if ($file = file_save_upload('file', array('file_validate_extensions' => array('xlsx')))) {
    if (PropertyImporter::documentHasSupportedFormat(drupal_realpath($file->uri))) {
      $form_state['values']['file'] = $file;
    }
    else {
      form_set_error('file', t('The uploaded document has unsupported format.'));
    }
  }
  elseif (NULL === $file) {
    form_set_error('file', t('Please choose a XLSX document to import properties from.'));
  }
}

/**
 * Form submission handler for property_import_form().
 *
 * @see property_import_form()
 */
function property_import_form_submit($form, &$form_state) {
  $batch = array(
    'operations' => array(
      array(
        array('PropertyImporter', 'batchApiOperation'),
        array(
          $form_state['values']['file']->fid,
          drupal_realpath($form_state['values']['file']->uri),
        ),
      ),
    ),
    'finished' => array('PropertyImporter', 'batchApiFinished'),
  );
  batch_set($batch);
}

/**
 * Page callback: returns the value of a field.
 */
function property_field_get_value($nid, $field) {
  $response = new stdClass();

  if ($node = node_load($nid)) {
    $node = entity_metadata_wrapper('node', $node);
    $response->success = TRUE;

    if ('last-contacted' == $field) {
      $response->value = date('Y-m-d', $node->field_last_contacted->value() ?? time());
    }
    elseif ('lead-status' == $field) {
      $response->value = $node->field_lead_status->value() ?? 3;
    }
  }
  else {
    $response->success = FALSE;
  }

  drupal_json_output($response);
}

/**
 * Page callback: saves the value of a field.
 */
function property_field_save_value($nid, $field) {
  $response = new stdClass();

  if ($node = node_load($nid)) {
    $node = entity_metadata_wrapper('node', $node);
    $response->success = TRUE;

    if ('last-contacted' == $field) {
      if ($_POST['value']) {
        $ts = strtotime($_POST['value']);
        $node->field_last_contacted = $ts;
        $node->save();
        $response->value = date('M j, Y', $ts);
      }
      else {
        $node->field_last_contacted = NULL;
        $node->save();
        $response->value = t('never');
      }
    }
    elseif ('lead-status' == $field) {
      if ($_POST['value']) {
        $node->field_lead_status = $_POST['value'];
        $node->save();
        $response->value = Property::getLeadStatusName($_POST['value']);
      }
      else {
        $node->field_lead_status = NULL;
        $node->save();
        $response->value = t('- None -');
      }
    }
  }
  else {
    $response->success = FALSE;
  }

  drupal_json_output($response);
}
