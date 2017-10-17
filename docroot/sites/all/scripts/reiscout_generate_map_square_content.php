#!/usr/bin/env drush

<?php

if ($path = drush_get_option('scan-dir')) {
  drush_print('Scanning dir `' . $path . '` for map squares');
  if (!is_dir($path)) {
    drush_print('Directory does not exists.');
  }
  $result = scan_dir_for_squares($path);
  print_r($result);
} else {
  print_description();
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

function print_description () {
  $help_text = <<<END
  This is the help text
END;

  drush_print($help_text);

}

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
  }

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