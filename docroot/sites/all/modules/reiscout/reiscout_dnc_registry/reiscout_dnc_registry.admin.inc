<?php

/**
 * @file
 * Admin page callback for the Reiscout DNC Registry module.
 */

/**
 * Form builder; Configure Reiscout DNC Registry.
 *
 * @see reiscout_dnc_registry_configure_form_validate()
 * @see reiscout_dnc_registry_configure_form_submit()
 */
function reiscout_dnc_registry_configure_form($form, &$form_state) {
  if ($number = DncRegistry::getSize()) {
    $info = t('There are !number phone numbers in the registry.', array('!number' => $number));
  }
  else {
    $info = t('The registry is empty.');
  }

  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Info'),
  );

  $form['info']['info'] = array(
    '#markup' => $info,
  );

  $form['empty'] = array(
    '#type' => 'fieldset',
    '#title' => t('Empty the registry'),
    '#description' => t('All the phone numbers will be removed from the registry.'),
  );

  $form['empty']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Empty'),
    '#validate' => array(),
    '#submit' => array('reiscout_dnc_registry_configure_form_empty_submit'),
  );

  $form['import'] = array(
    '#type' => 'fieldset',
    '#title' => t('Import phone numbers into the registry'),
    '#description' => t('Choose a file to import phone numbers from.'),
  );

  $form['import']['file'] = array(
    '#type' => 'file',
  );

  $form['import']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );

  $form['#attached']['css'][] = array(
    'data' => '#reiscout-dnc-registry-configure-form .form-type-file {display: inline}',
    'type' => 'inline',
  );

  return $form;
}

/**
 * Form validation handler for reiscout_dnc_registry_configure_form().
 *
 * @see reiscout_dnc_registry_configure_form()
 */
function reiscout_dnc_registry_configure_form_validate($form, &$form_state) {
  // Save the file as a temporary file.
  if ($file = file_save_upload('file', array('file_validate_extensions' => array()))) {
    $form_state['values']['file'] = $file;
  }
  else {
    form_set_error('file', t('Failed to upload the file.'));
  }
}

/**
 * Form submission handler for reiscout_dnc_registry_configure_form().
 *
 * @see reiscout_dnc_registry_configure_form()
 */
function reiscout_dnc_registry_configure_form_submit($form, &$form_state) {
  $batch = array(
    'operations' => array(
      array(
        array('DncRegistry', 'batchApiImportPhoneNumbersOperation'),
        array(
          $form_state['values']['file']->fid,
          $form_state['values']['file']->uri,
        ),
      ),
    ),
    'finished' => array('DncRegistry', 'batchApiImportPhoneNumbersFinished'),
  );
  batch_set($batch);
}

/**
 * Form submission handler for reiscout_dnc_registry_configure_form().
 *
 * @see reiscout_dnc_registry_configure_form()
 */
function reiscout_dnc_registry_configure_form_empty_submit($form, &$form_state) {
  DncRegistry::empty();
  drupal_set_message(t('The registry has been emptied.'));
}
