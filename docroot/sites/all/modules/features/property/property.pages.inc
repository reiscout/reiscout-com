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
}
