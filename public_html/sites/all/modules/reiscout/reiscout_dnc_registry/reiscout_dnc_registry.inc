<?php

/*
 * @file
 * Definition of DncRegistry class.
 */

class DncRegistry {
  /**
   * Returns the number of phone numbers stored in the registry.
   */
  static function getSize(): int {
    return db_query('SELECT COUNT(number) FROM {reiscout_dnc_registry}')->fetchField();
  }

  /**
   * Given a phone number, checks if it is in the registry.
   */
  static function contains(string $number): bool {
    return db_select('reiscout_dnc_registry', 'r')
      ->fields('r', array('number'))
      ->condition('number', self::formatNumber($number))
      ->execute()
      ->rowCount();
  }

  /**
   * Given a phone number, adds it into the registry.
   */
  static function addNumber(int $number): int {
    return db_query('INSERT IGNORE INTO {reiscout_dnc_registry} SET number = :number',
      array(':number' => $number),
      array('return' => Database::RETURN_AFFECTED));
  }

  /**
   * Empties the registry.
   */
  static function empty(): void {
    db_truncate('reiscout_dnc_registry')->execute();
  }

  /**
   * Given a phone number, converts it to the format used by the registry.
   */
  static function formatNumber(string $number): int {
    return preg_replace('!\D!', '', $number);
  }

  /**
   * Batch API operation callback; Imports phone numbers into the registry.
   *
   * @see reiscout_dnc_registry_configure_form_submit()
   */
  static function batchApiImportPhoneNumbersOperation($fid, $file_path, &$context): void {
    $file = new SplFileObject($file_path);
    $file->setFlags(SplFileObject::DROP_NEW_LINE);
    $file->fseek($context['sandbox']['file_pos'] ?? 0);

    if (!isset($context['sandbox']['numbers_total'])) {
      $context['sandbox']['numbers_total'] = 0;
      while (!$file->eof()) {
        $file->fgets();
        ++$context['sandbox']['numbers_total'];
      }
      $file->rewind();

      $context['sandbox']['numbers_processed'] = 0;
      $context['results']['numbers_imported'] = 0;
    }

    $transaction = db_transaction();

    $i = 0;
    while (!$file->eof() && $i < 100000) {
      $number = DncRegistry::formatNumber($file->fgets());
      if (DncRegistry::addNumber($number)) {
        ++$context['results']['numbers_imported'];
      }
      ++$context['sandbox']['numbers_processed'];
      ++$i;
    }

    $transaction = null;

    if ($file->eof()) {
      $file = null;
      file_delete(file_load($fid));
    }
    else {
      $context['sandbox']['file_pos'] = $file->ftell();
      $context['finished'] = $context['sandbox']['numbers_processed'] / $context['sandbox']['numbers_total'];
    }
  }

  /**
   * Batch API final callback.
   *
   * @see reiscout_dnc_registry_configure_form_submit()
   */
  static function batchApiImportPhoneNumbersFinished($success, $results, $operations): void {
    $t_args = array('!number' => $results['numbers_imported']);
    drupal_set_message(t('!number phone numbers have been imported.', $t_args));
  }
}
