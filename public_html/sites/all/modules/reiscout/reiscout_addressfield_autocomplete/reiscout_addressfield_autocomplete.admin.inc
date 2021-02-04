<?php

/**
 * @file
 * Admin page callback file for Reiscout Address Field Autocomplete module.
 */

/**
 * Form builder; Configure Reiscout Address Field Autocomplete settings.
 *
 * @see system_settings_form()
 */
function reiscout_addressfield_autocomplete_admin_settings_form() {
  $form['reiscout_addressfield_autocomplete_fields'] = array(
    '#type' => 'textarea',
    '#title' => t("List of fields to attach the address autocomplete feature to"),
    '#description' => t("List of fields in the following format: 'form1_id | field1_name, field2_name, ..., fieldN_name'. One form per line."),
    '#default_value' => variable_get('reiscout_addressfield_autocomplete_fields', ''),
  );

  return system_settings_form($form);
}
