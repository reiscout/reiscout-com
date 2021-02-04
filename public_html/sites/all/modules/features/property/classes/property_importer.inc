<?php

/*
 * @file
 * Definition of PropertyImporter class.
 */

require_once libraries_get_path('phpspreadsheet') . '/vendor/autoload.php';

use \PhpOffice\PhpSpreadsheet\IOFactory;
use \PhpOffice\PhpSpreadsheet\Reader\Xlsx;
use \PhpOffice\PhpSpreadsheet\Worksheet\Worksheet;

class PropertyImporterUnsupportedDocumentFormat extends Exception {}

class PropertyImporter {
  private const DOCUMENT_FORMAT1_HEADER = array(
    'Owner Name Unformatted',
    'Owner First Name',
    'Owner Last Name',
    'Company',
    'Owner Address',
    'Owner City',
    'Owner State',
    'Owner Zip',
    'Owner Phone',
    'Property Address',
    'Property City',
    'Property State',
    'Property Zip',
    'Notes',
  );

  private const DOCUMENT_FORMAT2_HEADER = array(
    'Case File Date',
    'Case Number',
    'Owner Name Unformatted',
    'Owner First Name',
    'Owner Last Name',
    'Company',
    'Owner Address',
    'Owner City',
    'Owner State',
    'Owner Zip',
    'Owner Phone',
    'Owner Phone 1',
    'Owner Phone 2',
    'Owner Email',
    'Owner Email 1',
    'Owner Email 2',
    'Property Address',
    'Property City',
    'Property State',
    'Property Zip',
    'Notes',
  );

  private const DOCUMENT_FORMAT3_HEADER = array(
    'Foreclosure Sale Date',
    'Case Number',
    'Owner Name Unformatted',
    'Owner First Name',
    'Owner Last Name',
    'Company',
    'Owner Address',
    'Owner City',
    'Owner State',
    'Owner Zip',
    'Owner Phone',
    'Owner Phone 1',
    'Owner Phone 2',
    'Owner Email',
    'Owner Email 1',
    'Owner Email 2',
    'Property Address',
    'Property City',
    'Property State',
    'Property Zip',
    'Notes',
  );

  private const DOCUMENT_FORMAT2_REQUIRED_COLUMNS = array('B', 'C', 'G', 'H', 'I', 'J', 'Q', 'R', 'S', 'T');
  private const DOCUMENT_FORMAT3_REQUIRED_COLUMNS = array('A', 'C', 'G', 'H', 'I', 'J', 'Q', 'R', 'S', 'T');

  private $filePath;
  private $spreadsheet;
  private $sheetsToProcess;

  /**
   * Prepares a spreadsheet by loading it from a file.
   *
   * Given a path to a XLSX document, checks if it has a supported format
   * and loads a spreadsheet from it.
   */
  function __construct(string $filePath) {
    $this->filePath = $filePath;

    try {
      $fileType = IOFactory::identify($filePath);
    }
    catch (\PhpOffice\PhpSpreadsheet\Reader\Exception $e) {
      $msg = t('!fileName has unsupported format.', array('!fileName' => basename($filePath)));
      throw new PropertyImporterUnsupportedDocumentFormat($msg);
    }

    if ('Xlsx' != $fileType) {
      $msg = t('!fileName has unsupported format.', array('!fileName' => basename($filePath)));
      throw new PropertyImporterUnsupportedDocumentFormat($msg);
    };

    $reader = new Xlsx();
    $this->spreadsheet = $reader->load($filePath);
  }

  /**
   * Checks if a XLSX document has a supported format.
   */
  static function documentHasSupportedFormat(string $filePath): bool {
    try {
      $instance = new self($filePath);
    }
    catch (PropertyImporterUnsupportedDocumentFormat $e) {
      return FALSE;
    }

    return (bool)$instance->determineDocumentFormat();
  }

  /**
   * Determines the document format of a spreadsheet.
   */
  private function determineDocumentFormat(): ?int {
    if ($sheet = $this->spreadsheet->getSheetByName('All Data')) {
      $header = $sheet->rangeToArray('A1:N1', NULL, FALSE, FALSE)[0];
      if (!array_udiff(self::DOCUMENT_FORMAT1_HEADER, $header, 'strcasecmp')) {
        return 1;
      }
    }
    elseif ($sheet = $this->spreadsheet->getSheetByName('Owner Occupied') ??
                     $this->spreadsheet->getSheetByName('Non Owner Occupied') ??
                     $this->spreadsheet->getSheetByName('Out Of State Owners')) {
      $header = $sheet->rangeToArray('A1:U1', NULL, FALSE, FALSE)[0];
      if (!array_udiff(self::DOCUMENT_FORMAT2_HEADER, $header, 'strcasecmp')) {
        return 2;
      }
      elseif (!array_udiff(self::DOCUMENT_FORMAT3_HEADER, $header, 'strcasecmp')) {
        return 3;
      }
    }

    return NULL;
  }

  /**
   * Returns the number of the last row containing data.
   *
   * Given a sheet and column name, determines and returns the number of the
   * last row containing data in the column.
   */
  private function getLastRowNumberByColumn(Worksheet $sheet, string $col): int {
    $number = 0;

    // We init $row to 2, because the row index are 1-based and the first row is a header.
    for ($row = 2, $rowsNumber = $sheet->getHighestRow(); $row <= $rowsNumber; ++$row) {
      if ($sheet->getCell($col . $row)->getValue()) {
        $number = $row;
      }
    }

    return $number;
  }

  /**
   * Returns the data of the current row.
   */
  private function getRow(): ?array {
    if (!$this->sheetsToProcess) {
      return NULL;
    }

    $info = reset($this->sheetsToProcess);
    $sheetName = key($this->sheetsToProcess);
    $sheet = $this->spreadsheet->getSheetByName($sheetName);
    $range = 'A' . $info['from'] .':U' . $info['from'];
    $row = $sheet->rangeToArray($range, NULL, TRUE, TRUE, TRUE);

    return reset($row);
  }

  /**
   * Move the row pointer to the next row.
   */
  private function nextRow(): void {
    $sheetName = key($this->sheetsToProcess);

    if ($this->sheetsToProcess[$sheetName]['to'] == $this->sheetsToProcess[$sheetName]['from']) {
      unset($this->sheetsToProcess[$sheetName]);
    }
    else {
      ++$this->sheetsToProcess[$sheetName]['from'];
    }
  }

  /**
   * Sets a case file date.
   */
  private function setCaseFileDate(string $date): void {
    $sheetName = key($this->sheetsToProcess);
    $this->sheetsToProcess[$sheetName]['caseFileDate'] = $date;
  }

  /**
   * Returns a case file date.
   */
  private function getCaseFileDate(): ?string {
    $sheetName = key($this->sheetsToProcess);
    return $this->sheetsToProcess[$sheetName]['caseFileDate'] ?? NULL;
  }

  /**
   * Checks if all the given keys are set in the given array.
   */
  private function arrayKeysAreSet(array $array, array $keys): bool {
    foreach ($keys as $key) {
      if (!$array[$key]) {
        return FALSE;
      }
    }
    return TRUE;
  }

  /**
   * Uppercases the first character of each word in a lowercase string.
   */
  private function ucWordsInLowercaseString(string $str): string {
    return $str == strtolower($str) ? ucwords($str) : $str;
  }

  /**
   * Removes non decimal characters from the given string.
   */
  private function removeNonDecimalCharacters(string $str): string {
    return preg_replace('!\D!', '', $str);
  }

  /**
   * Checks if all the required columns are filled out in the given row.
   */
  private function requiredColumnsFilledOut(array $row): bool {
    $cols = $this->getCaseFileDate() ?
            self::DOCUMENT_FORMAT2_REQUIRED_COLUMNS :
            array_merge(array('A'), self::DOCUMENT_FORMAT2_REQUIRED_COLUMNS);

    return $this->arrayKeysAreSet($row, $cols);
  }

  /**
   * Checks if all the required columns are filled out in the given row.
   */
  private function requiredColumnsFilledOut3(array $row): bool {
    return $this->arrayKeysAreSet($row, self::DOCUMENT_FORMAT3_REQUIRED_COLUMNS);
  }

  /**
   * Returns a county name parsed from the filename of a XLSX document.
   */
  private function parseCountyNameFromDocumentFileName(): ?string {
    if (preg_match('!^([a-z\-. ]+)\s+\d+!i', basename($this->filePath), $matches)) {
      return trim($matches[1]);
    }
    return NULL;
  }

  /**
   * Returns a first and last names parsed from the given string.
   */
  private function parseFirstAndLastNames(string $str): ?array {
    $names = explode(',', $str);
    $names = array_map('trim', $names);
    $names = array_filter($names);

    if (2 == count($names) || 3 == count($names)) {
      $names = array_map(array($this, 'ucWordsInLowercaseString'), $names);

      if (2 == count($names)) {
        return array($names[1], $names[0]);
      }
      elseif (3 == count($names)) {
        $names[2] = str_replace(array('I.', 'II.', 'III.', 'IV.', 'V.'), array('I', 'II', 'III', 'IV', 'V'), $names[2]);
        return array($names[1], $names[0] . ' ' . $names[2]);
      }
    }

    return NULL;
  }

  /**
   * Returns an address parsed from the given string.
   */
  private function parseAddress(string $str): ?string {
    $addressComponents = explode(PHP_EOL, $str);
    $addressComponents = array_map('trim', $addressComponents);
    $addressComponents = array_filter($addressComponents);

    if (1 == count($addressComponents)) {
      $address = $addressComponents[0];
    }
    elseif (2 == count($addressComponents)) {
      $address = $addressComponents[0] . ' ' . $addressComponents[1];
    }

    return $address ? _reiscout_misc_standardize_address_thoroughfare($address) : NULL;
  }

  /**
   * Checks if the given string is a valid state.
   */
  private function validState(string $str): bool {
    module_load_include('inc', 'addressfield', 'addressfield.administrative_areas');
    return array_key_exists($str, addressfield_get_administrative_areas('US'));
  }

  /**
   * Returns a state parsed from the given string.
   */
  private function parseState(string $str): ?string {
    $state = strtoupper($str);
    return $this->validState($state) ? $state : NULL;
  }

  /**
   * Returns a zip code parsed from the given string.
   */
  private function parseZip(string $str): ?string {
    $zip = explode('-', $str);
    $zip = $this->removeNonDecimalCharacters($zip[0]);

    if (4 == strlen($zip)) {
      $zip = '0' . $zip;
    }

    return 5 == strlen($zip) ? $zip : NULL;
  }

  /**
   * Returns a phone number parsed from the given string.
   */
  private function parsePhoneNumber(string $str): ?string {
    $digits = $this->removeNonDecimalCharacters($str);

    if (10 == strlen($digits)) {
      return '(' . $digits[0] . $digits[1] . $digits[2] . ') '
           . $digits[3] . $digits[4] . $digits[5] . '-'
           . $digits[6] . $digits[7] . $digits[8] . $digits[9];
    }

    return NULL;
  }

  /**
   * Returns property data parsed from the given sheet row.
   */
  private function parsePropertyData(array $row): ?stdClass {
    $data = new stdClass();

    if ($countyName = $this->parseCountyNameFromDocumentFileName()) {
      $data->countyName = $countyName;
    }

    $data->caseFileDate = strtotime($row['A'] ? $row['A'] : $this->getCaseFileDate());
    $data->caseNumber = $row['B'];

    if ($names = $this->parseFirstAndLastNames($row['C'])) {
      $data->ownerFirstName = $names[0];
      $data->ownerLastName = $names[1];
    }
    else {
      return NULL;
    }

    if ($address = $this->parseAddress($row['G'])) {
      $data->ownerAddressThoroughfare = $address;
    }
    else {
      return NULL;
    }

    $data->ownerAddressCity = $this->ucWordsInLowercaseString($row['H']);

    if ($state = $this->parseState($row['I'])) {
      $data->ownerAddressState = $state;
    }
    else {
      return NULL;
    }

    if ($zip = $this->parseZip($row['J'])) {
      $data->ownerAddressZip = $zip;
    }
    else {
      return NULL;
    }

    foreach (array($row['K'], $row['L'], $row['M']) as $str) {
      if ($str && $number = $this->parsePhoneNumber($str)) {
        $data->ownerPhoneNumbers[] = $number;
      }
    }

    foreach (array($row['N'], $row['O'], $row['P']) as $str) {
      if ($str && valid_email_address($str)) {
        $emails[] = $str;
      }
    }

    if (isset($emails)) {
      $data->notes = implode("\n", $emails);
    }

    if ($address = $this->parseAddress($row['Q'])) {
      $data->propertyAddressThoroughfare = $address;
    }
    else {
      return NULL;
    }

    $data->propertyAddressCity = $this->ucWordsInLowercaseString($row['R']);

    if ($state = $this->parseState($row['S'])) {
      $data->propertyAddressState = $state;
    }
    else {
      return NULL;
    }

    if ($zip = $this->parseZip($row['T'])) {
      $data->propertyAddressZip = $zip;
    }
    else {
      return NULL;
    }

    if ($row['U']) {
      $data->notes = isset($data->notes) ? $data->notes . "\n\n" . $row['U'] : $row['U'];
    }

    return $data;
  }

  /**
   * Returns property data parsed from the given sheet row.
   */
  private function parsePropertyData3(array $row): ?stdClass {
    $data = new stdClass();

    if ($countyName = $this->parseCountyNameFromDocumentFileName()) {
      $data->countyName = $countyName;
    }

    $data->foreclosureSaleDate = strtotime($row['A']);

    if ($names = $this->parseFirstAndLastNames($row['C'])) {
      $data->ownerFirstName = $names[0];
      $data->ownerLastName = $names[1];
    }
    else {
      return NULL;
    }

    if ($address = $this->parseAddress($row['G'])) {
      $data->ownerAddressThoroughfare = $address;
    }
    else {
      return NULL;
    }

    $data->ownerAddressCity = $this->ucWordsInLowercaseString($row['H']);

    if ($state = $this->parseState($row['I'])) {
      $data->ownerAddressState = $state;
    }
    else {
      return NULL;
    }

    if ($zip = $this->parseZip($row['J'])) {
      $data->ownerAddressZip = $zip;
    }
    else {
      return NULL;
    }

    foreach (array($row['K'], $row['L'], $row['M']) as $str) {
      if ($str && $number = $this->parsePhoneNumber($str)) {
        $data->ownerPhoneNumbers[] = $number;
      }
    }

    foreach (array($row['N'], $row['O'], $row['P']) as $str) {
      if ($str && valid_email_address($str)) {
        $emails[] = $str;
      }
    }

    if (isset($emails)) {
      $data->notes = implode("\n", $emails);
    }

    if ($address = $this->parseAddress($row['Q'])) {
      $data->propertyAddressThoroughfare = $address;
    }
    else {
      return NULL;
    }

    $data->propertyAddressCity = $this->ucWordsInLowercaseString($row['R']);

    if ($state = $this->parseState($row['S'])) {
      $data->propertyAddressState = $state;
    }
    else {
      return NULL;
    }

    if ($zip = $this->parseZip($row['T'])) {
      $data->propertyAddressZip = $zip;
    }
    else {
      return NULL;
    }

    if ($row['U']) {
      $data->notes = isset($data->notes) ? $data->notes . "\n\n" . $row['U'] : $row['U'];
    }

    return $data;
  }

  /**
   * Creates a new Property node using the given property data.
   */
  private function createProperty(stdClass $data): void {
    global $user;

    $property = entity_create('node', array('type' => 'property', 'uid' => $user->uid));
    $property = entity_metadata_wrapper('node', $property);

    $property->field_address->thoroughfare = $data->propertyAddressThoroughfare;
    $property->field_address->locality = $data->propertyAddressCity;
    $property->field_address->administrative_area = $data->propertyAddressState;
    $property->field_address->postal_code = $data->propertyAddressZip;
    $property->field_address->country = 'US';

    if (isset($data->countyName)) {
      $property->field_fips_county_code = Property::getCountyFipsCodeByName($data->countyName);
    }

    if (isset($data->notes)) {
      $property->body->set(array('value' => $data->notes));
    }

    $property->field_owner_postal_address->name_line = NULL;
    $property->field_owner_postal_address->first_name = $data->ownerFirstName;
    $property->field_owner_postal_address->last_name = $data->ownerLastName;
    $property->field_owner_postal_address->thoroughfare = $data->ownerAddressThoroughfare;
    $property->field_owner_postal_address->locality = $data->ownerAddressCity;
    $property->field_owner_postal_address->administrative_area = $data->ownerAddressState;
    $property->field_owner_postal_address->postal_code = $data->ownerAddressZip;
    $property->field_owner_postal_address->country = 'US';

    if (isset($data->ownerPhoneNumbers)) {
      $property->field_owner_phone->set($data->ownerPhoneNumbers);
    }

    $property->field_list = 1;
    $property->field_case_number = $data->caseNumber;
    $property->field_case_file_date = $data->caseFileDate;

    $property->save();
  }

  /**
   * Creates a new Property node using the given property data.
   */
  private function createProperty3(stdClass $data): void {
    global $user;

    $property = entity_create('node', array('type' => 'property', 'uid' => $user->uid));
    $property = entity_metadata_wrapper('node', $property);

    $property->field_address->thoroughfare = $data->propertyAddressThoroughfare;
    $property->field_address->locality = $data->propertyAddressCity;
    $property->field_address->administrative_area = $data->propertyAddressState;
    $property->field_address->postal_code = $data->propertyAddressZip;
    $property->field_address->country = 'US';

    if (isset($data->countyName)) {
      $property->field_fips_county_code = Property::getCountyFipsCodeByName($data->countyName);
    }

    if (isset($data->notes)) {
      $property->body->set(array('value' => $data->notes));
    }

    $property->field_owner_postal_address->name_line = NULL;
    $property->field_owner_postal_address->first_name = $data->ownerFirstName;
    $property->field_owner_postal_address->last_name = $data->ownerLastName;
    $property->field_owner_postal_address->thoroughfare = $data->ownerAddressThoroughfare;
    $property->field_owner_postal_address->locality = $data->ownerAddressCity;
    $property->field_owner_postal_address->administrative_area = $data->ownerAddressState;
    $property->field_owner_postal_address->postal_code = $data->ownerAddressZip;
    $property->field_owner_postal_address->country = 'US';

    if (isset($data->ownerPhoneNumbers)) {
      $property->field_owner_phone->set($data->ownerPhoneNumbers);
    }

    $property->field_list = 2;
    $property->field_foreclosure_sale_date = $data->foreclosureSaleDate;

    $property->save();
  }

  /**
   * Updates a Property node using the given property data.
   */
  private function updateProperty(EntityMetadataWrapper $property, stdClass $data): void {
    if (isset($data->countyName)) {
      $property->field_fips_county_code = Property::getCountyFipsCodeByName($data->countyName);
    }

    if (isset($data->notes)) {
      $data->notes .= $property->body->value() ? "\n\n" . $property->body->value->value() : '';
      $property->body->set(array('value' => $data->notes));
    }

    $property->field_owner_postal_address->name_line = NULL;
    $property->field_owner_postal_address->first_name = $data->ownerFirstName;
    $property->field_owner_postal_address->last_name = $data->ownerLastName;
    $property->field_owner_postal_address->thoroughfare = $data->ownerAddressThoroughfare;
    $property->field_owner_postal_address->locality = $data->ownerAddressCity;
    $property->field_owner_postal_address->administrative_area = $data->ownerAddressState;
    $property->field_owner_postal_address->postal_code = $data->ownerAddressZip;
    $property->field_owner_postal_address->country = 'US';

    if (isset($data->ownerPhoneNumbers)) {
      $property->field_owner_phone->set($data->ownerPhoneNumbers);
    }

    $property->field_list = 1;
    $property->field_case_number = $data->caseNumber;
    $property->field_case_file_date = $data->caseFileDate;

    $property->save();
  }

  /**
   * Updates a Property node using the given property data.
   */
  private function updateProperty3(EntityMetadataWrapper $property, stdClass $data): void {
    if (isset($data->countyName)) {
      $property->field_fips_county_code = Property::getCountyFipsCodeByName($data->countyName);
    }

    if (isset($data->notes)) {
      $data->notes .= $property->body->value() ? "\n\n" . $property->body->value->value() : '';
      $property->body->set(array('value' => $data->notes));
    }

    $property->field_owner_postal_address->name_line = NULL;
    $property->field_owner_postal_address->first_name = $data->ownerFirstName;
    $property->field_owner_postal_address->last_name = $data->ownerLastName;
    $property->field_owner_postal_address->thoroughfare = $data->ownerAddressThoroughfare;
    $property->field_owner_postal_address->locality = $data->ownerAddressCity;
    $property->field_owner_postal_address->administrative_area = $data->ownerAddressState;
    $property->field_owner_postal_address->postal_code = $data->ownerAddressZip;
    $property->field_owner_postal_address->country = 'US';

    if (isset($data->ownerPhoneNumbers)) {
      $property->field_owner_phone->set($data->ownerPhoneNumbers);
    }

    $property->field_list = 2;
    $property->field_foreclosure_sale_date = $data->foreclosureSaleDate;

    $property->save();
  }

  /**
   * Imports the given property data by creating or updating a Property node.
   */
  private function importPropertyData(stdClass $data): bool {
    global $user;

    if (Property::userHasByCaseNumber($user->uid, $data->caseNumber)) {
      return FALSE;
    }

    $address = (object) array(
      'thoroughfare' => $data->propertyAddressThoroughfare,
      'city' => $data->propertyAddressCity,
      'state' => $data->propertyAddressState,
    );

    if ($property = Property::getByAddressAndUid($address, $user->uid)) {
      $property = entity_metadata_wrapper('node', $property);

      if (!Property::isOwnerAddressFilledOut($property->field_owner_postal_address)
       || (($ownerInfoActualDate = $property->field_foreclosure_sale_date->value() ??
                                   $property->field_case_file_date->value() ??
                                   $property->field_last_sale_date->value())
        && $ownerInfoActualDate < $data->caseFileDate)) {
        $this->updateProperty($property, $data);
        return TRUE;
      }
    }
    else {
      $this->createProperty($data);
      return TRUE;
    }

    return FALSE;
  }

  /**
   * Imports the given property data by creating or updating a Property node.
   */
  private function importPropertyData3(stdClass $data): bool {
    global $user;

    $address = (object) array(
      'thoroughfare' => $data->propertyAddressThoroughfare,
      'city' => $data->propertyAddressCity,
      'state' => $data->propertyAddressState,
    );

    if ($property = Property::getByAddressAndUid($address, $user->uid)) {
      $property = entity_metadata_wrapper('node', $property);

      if (!Property::isOwnerAddressFilledOut($property->field_owner_postal_address)
       || (($ownerInfoActualDate = $property->field_foreclosure_sale_date->value() ??
                                   $property->field_case_file_date->value() ??
                                   $property->field_last_sale_date->value())
        && $ownerInfoActualDate < $data->foreclosureSaleDate)) {
        $this->updateProperty3($property, $data);
        return TRUE;
      }
    }
    else {
      $this->createProperty3($data);
      return TRUE;
    }

    return FALSE;
  }

  /**
   * Imports properties data from a document of format 1 (Dispossessory 1).
   */
  private function importFromDocumentFormat1(array &$context): bool {
    drupal_set_message('Support of this document format has not been implemented yet.');
    return TRUE;
  }

  /**
   * Imports properties data from a document of format 2 (Dispossessory 2).
   */
  private function importFromDocumentFormat2(array &$context): bool {
    $sandbox = &$context['sandbox'];

    if (!isset($sandbox['sheetsToProcess'])) {
      $sandbox['sheetsToProcess'] = array();
      $sandbox['rowsTotal'] = 0;
      $sandbox['rowsProcessed'] = 0;
      $context['results']['propertiesImported'] = 0;

      foreach (array('Owner Occupied', 'Non Owner Occupied', 'Out Of State Owners') as $sheetName) {
        if ($sheet = $this->spreadsheet->getSheetByName($sheetName)) {
          if ($lastRowNumber = $this->getLastRowNumberByColumn($sheet, 'B')) {
            // We set 'from' to 2, because the row index are 1-based and the first row is a header.
            $sandbox['sheetsToProcess'][$sheetName] = array(
              'from' => 2,
              'to' => $lastRowNumber,
            );
            $sandbox['rowsTotal'] += $lastRowNumber;
          }
        }
      }
    }

    $this->sheetsToProcess = &$sandbox['sheetsToProcess'];

    $i = 0;
    while (($row = $this->getRow()) && $i < 25) {
      $row = array_map('trim', $row);

      if ($this->requiredColumnsFilledOut($row)) {
        if ($data = $this->parsePropertyData($row)) {
          if ($this->importPropertyData($data)) {
            ++$context['results']['propertiesImported'];
            ++$i;
          }
        }
      }

      if ($row['A']) {
        $this->setCaseFileDate($row['A']);
      }

      $this->nextRow();
      ++$sandbox['rowsProcessed'];
    }

    if ($this->sheetsToProcess) {
      $context['finished'] = $sandbox['rowsProcessed'] / $sandbox['rowsTotal'];
      return FALSE;
    }
    else {
      return TRUE;
    }
  }

  /**
   * Imports properties data from a document of format 3 (Pre-foreclosure).
   */
  private function importFromDocumentFormat3(array &$context): bool {
    $sandbox = &$context['sandbox'];

    if (!isset($sandbox['sheetsToProcess'])) {
      $sandbox['sheetsToProcess'] = array();
      $sandbox['rowsTotal'] = 0;
      $sandbox['rowsProcessed'] = 0;
      $context['results']['propertiesImported'] = 0;

      foreach (array('Owner Occupied', 'Non Owner Occupied', 'Out Of State Owners') as $sheetName) {
        if ($sheet = $this->spreadsheet->getSheetByName($sheetName)) {
          if ($lastRowNumber = $this->getLastRowNumberByColumn($sheet, 'A')) {
            // We set 'from' to 2, because the row index are 1-based and the first row is a header.
            $sandbox['sheetsToProcess'][$sheetName] = array(
              'from' => 2,
              'to' => $lastRowNumber,
            );
            $sandbox['rowsTotal'] += $lastRowNumber;
          }
        }
      }
    }

    $this->sheetsToProcess = &$sandbox['sheetsToProcess'];

    $i = 0;
    while (($row = $this->getRow()) && $i < 25) {
      $row = array_map('trim', $row);

      if ($this->requiredColumnsFilledOut3($row)) {
        if ($data = $this->parsePropertyData3($row)) {
          if ($this->importPropertyData3($data)) {
            ++$context['results']['propertiesImported'];
            ++$i;
          }
        }
      }

      $this->nextRow();
      ++$sandbox['rowsProcessed'];
    }

    if ($this->sheetsToProcess) {
      $context['finished'] = $sandbox['rowsProcessed'] / $sandbox['rowsTotal'];
      return FALSE;
    }
    else {
      return TRUE;
    }
  }

  /**
   * Batch API operation callback; Imports properties from a XLSX document.
   *
   * @see property_import_form_submit()
   */
  static function batchApiOperation(int $fid, string $filePath, array &$context): void {
    $sandbox = &$context['sandbox'];

    $instance = new self($filePath);

    if (!isset($sandbox['methodName'])) {
      $sandbox['methodName'] = 'importFromDocumentFormat' . $instance->determineDocumentFormat();
    }

    if ($instance->{$sandbox['methodName']}($context)) {
      file_delete(file_load($fid));
    }
  }

  /**
   * Batch API final callback.
   *
   * @see property_import_form_submit()
   */
  static function batchApiFinished(bool $success, array $results, array $operations): void {
    if (isset($results['propertiesImported'])) {
      $tArgs = array('!number' => $results['propertiesImported']);
      drupal_set_message(t('!number properties have been imported.', $tArgs));
    }
  }
}
