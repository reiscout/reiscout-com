#!/usr/bin/env drush

<?php

/**
 * @file
 * Implements map squares operations.
 * @see print_description();
 */

namespace reiscout_generate_map_square_content {

  use DirectoryIterator;

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
}

namespace reiscout_generate_map_square_content {
  
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

      if ($echo_squares = drush_get_option('create-nodes')) {
        drush_print('Creating nodes for '. count($squares). 'found squares');
        create_nodes($squares);
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
   *     'N3996335E_9401244' => array(
   *       'gpx'  => 'file path',
   *       'kmz' => 'file path',
   *        ...
   *       'png' => 'file path',
   *     ),
   *     1 => ...
   *   )
   *
   * @return array
   */
  function scan_dir_for_squares($path) {

    $directoryIterator = new MapSquareDirectoryIterator($path);

    $result = array();

    $detect_files = array('png', 'gpx', 'kmz', 'kml');
    foreach ($detect_files as $ext) {
      if ($file = $directoryIterator->getFileByExt($ext)) {
        $result[$file->getBasename('.'.$file->getExtension())][$ext] = $directoryIterator->getFileByExt($ext);
      }
    }

    foreach($directoryIterator as $item) {
      if (!$item->isDot() && $item->isDir()) {
        $result = array_merge_recursive($result, scan_dir_for_squares($item->getRealPath()));
      }

    }

    return $result;
  }

  /**
   * Create nodes for passed squares
   *
   * @param array $squares
   *
   * @return integer
   *   Number of created nodes.
   */
  function create_nodes ($squares) {

  }


}

