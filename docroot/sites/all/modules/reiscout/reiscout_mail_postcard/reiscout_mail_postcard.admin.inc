<?php

/**
 * @file
 * Admin page callback file for the Reiscout Mail Postcard module.
 */

/**
 * Form builder; Configure Reiscout Mail Postcard settings.
 *
 * @see system_settings_form()
 */
function reiscout_mail_postcard_admin_settings_form() {
  $form['reiscout_mail_postcard_send_limit_period'] = array(
    '#type' => 'textfield',
    '#title' => t('Send Limit Period, days'),
    '#description' => t("The period of time during which a user is allowed to send one postcard to the same property's owner."),
    '#default_value' => variable_get('reiscout_mail_postcard_send_limit_period', REISCOUT_MAIL_POSTCARD_SEND_LIMIT_PERIOD),
    '#element_validate' => array('element_validate_integer_positive'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
