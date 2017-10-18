#!/usr/bin/env drush

<?php

/**
 * @file
 * Implements map squares operations.
 * @see print_description();
 */

main();

/**
 * Handle script execution.
 */
function main() {
  $show_help = TRUE;

  if ($path = drush_get_option('scan-dir')) {
    $show_help = FALSE;
    drush_print('Scanning dir `' . $path . '` for map squares');
    if (!is_dir($path)) {
      drush_print('Directory does not exists.');
    }
    $squares = scan_dir_for_squares($path);

    if ($echo_squares = drush_get_option('out-squares')) {
      drush_print('Scan results:');
      print_r($squares);
    }

  }

  if ($show_help) {
    print_description();
  }
}

/**
 * Print script help text.
 */
function print_description () {
  $help_text = <<<END
  With that you can:
  * scan any folder for squares using  --scan-dir=<dir>
  * output found squares  --out-squares
  * create nodes for found squares  --create-nodes
  * output image map for Atlanta  --out-imagemap
END;

  drush_print($help_text);

}

/**
 * Recursively scan passed directory and return all found squares as a flat (not nested) array.
 * Result format:
 *   array(
 *     0 => array(
 *       'name' => 'N3996335E_9401244',
 *       'gpx'  => 'file path',
 *       'kmz' => 'file path',
 *       'png' => 'file path',
 *       'html' => 'file path'
 *     ),
 *     1 => ...
 *   )
 *
 * @return array
 */
function scan_dir_for_squares($path) {

  $directoryIterator = new MapSquareDirectoryIterator($path);

  $result = array();

  if ($directoryIterator->isSquareDir()) {
    $result[] = array(
      'name' => basename($directoryIterator->getPath()),
      'gpx' => $directoryIterator->getFileByExt('gpx'),
      'kmz' => $directoryIterator->getFileByExt('kmz'),
      'png' => $directoryIterator->getFileByExt('png'),
    );

  }

  foreach($directoryIterator as $item) {
    if (!$item->isDot() && $item->isDir()) {
      $result += scan_dir_for_squares($item->getRealPath());
    }

  }

  return $result;
}

/**
 * @class MapSquareDirectoryIterator
 *
 * DirectoryIterator wrapper implementing some help methods for squares directories scanning.
 */
class MapSquareDirectoryIterator extends DirectoryIterator {

  /**
   * Return path for file by extention in directory.
   *
   * @param string $ext extention
   *
   * @return SplFileInfo
   */
  public function getFileByExt ($ext) {
    foreach ($this as $item) {
      if (!$item->isDot() && $item->isFile()) {
        $file = $item->getFileInfo();
        if ($file->getExtension() == $ext) {
          return $file;
        }
      }
    }
    return FALSE;
  }

  /**
   * Detect is a current dir is a square dir.
   */
  public function isSquareDir() {
    $extentions = array('gpx', 'kmz');
    foreach ($this as $item) {
      if (!$item->isDot() && $item->isFile() && in_array($item->getFileInfo()->getExtension(), $extentions)) {
        return TRUE;
      }
    }
    return FALSE;
  }

}