<?php

/**
 * @file
 * Admin page callback file for the Reiscout Block Spam module.
 */

/**
 * Form builder; Configure Reiscout Block Spam settings.
 *
 * @see system_settings_form()
 */
function reiscout_block_spam_admin_settings_form() {
  $form['reiscout_block_spam_message_ids'] = array(
    '#type' => 'textarea',
    '#title' => t("List of messages' ID"),
    '#description' => t("List of messages' ID that must be processed by <em>Reiscout Block Spam</em>. One message's ID per line."),
    '#default_value' => variable_get('reiscout_block_spam_message_ids', ''),
  );

  $form['reiscout_block_spam_cyrillic_symbols'] = array(
    '#type' => 'checkbox',
    '#title' => t('Block an email if it contains cyrillic symbols'),
    '#default_value' => variable_get('reiscout_block_spam_cyrillic_symbols', FALSE),
  );

  $form['reiscout_block_spam_stop_words'] = array(
    '#type' => 'textarea',
    '#title' => t('Block an email if it contains any of these words'),
    '#description' => t('One word per line. It will match inside words, so “sex” will match “unisex”.'),
    '#default_value' => variable_get('reiscout_block_spam_stop_words', ''),
  );

  $form['reiscout_block_spam_log_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log blocked emails'),
    '#description' => t('Log emails that are blocked due to <em>Reiscout Block Spam</em> protection.'),
    '#default_value' => variable_get('reiscout_block_spam_log_enabled', FALSE),
  );

  return system_settings_form($form);
}
