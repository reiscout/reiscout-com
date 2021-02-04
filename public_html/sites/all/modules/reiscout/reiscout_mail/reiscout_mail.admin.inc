<?php

/**
 * @file
 * Admin page callback file for the Reiscout Mail module.
 */

/**
 * Form builder; Configure Reiscout Mail settings.
 *
 * @see system_settings_form()
 */
function reiscout_mail_admin_settings_form() {
  $form['reiscout_mail_send_limit_period'] = array(
    '#type' => 'textfield',
    '#title' => t('Send Limit Period, days'),
    '#description' => t("The period of time during which a user will not be able to send another letter or postcard to the same property's owner."),
    '#default_value' => ReiscoutMail::getSendLimitPeriod(),
    '#element_validate' => array('element_validate_integer_positive'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
