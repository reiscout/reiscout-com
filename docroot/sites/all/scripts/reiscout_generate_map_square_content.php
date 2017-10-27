#!/usr/bin/env drush

<?php

/**
 * @file
 * Implements map squares operations.
 *
 * To run it just `./reiscout_generate_map_square_content.php`
 *
 * @see print_description();
 *
 */

namespace reiscout_generate_map_square_content;

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
  public function getFileByExt($ext) {
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
      drush_print('Creating nodes for ' . count($squares) . ' found squares');
      $errs = array();
      $created = create_nodes($squares, $errs);
      drush_print($created . ' nodes created');
      drush_print(count($errs) . ' exceptions catched');
      if (drush_get_option('show-exceptions')) {
        foreach ($errs as $e) {
          /* @var \Exception $e */
          drush_print('FILE: ' . $e->getFile() . ':'. $e->getLine() .' MESSAGE: '. $e->getMessage());
        }

      }
    }

  }


  if ($path = drush_get_option('drop-nodes')) {
    drush_print('Drop square nodes');
    drop_square_nodes();
  }


  if ($show_help) {
    print_description();
  }
}

/**
 * Print script help text.
 */
function print_description() {
  $help_text = <<<END
  With that script you can:
  * scan any folder for squares using  --scan-dir=<dir>
  * output found squares  --out-squares
  * create nodes for found squares  --create-nodes
  * output image map for Atlanta  --out-imagemap
  * drop all existed map nodes from database --drop-nodes

  Usage example:
    ./reiscout_generate_map_square_content.php --scan-dir='../squares' --out-squares  --create-nodes --drop-nodes --show-exceptions
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
      $result[$file->getBasename('.' . $file->getExtension())][$ext] = $directoryIterator->getFileByExt($ext);
    }
  }

  foreach ($directoryIterator as $item) {
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
 * @param array $exceptions
 *
 * @return integer
 *   Number of created nodes.
 */
function create_nodes($squares, &$exceptions) {
  $created = 0;
  foreach ($squares as $name => $square) {
    $square['name'] = $name;
    try {
      if (create_node($square)) {
        $created++;
      };
    } catch (\Exception $e) {
      $exceptions[] = $e;
    }
  }

  return $created;
}

/**
 * Create node for passed square
 *
 * @param array $square
 *
 * @return boolean
 */
function create_node($square) {
  if (square_node_exists($square)) {
    throw new \Exception('Node for square already exists');
  }

  // Create basic node object.
  $values = array(
    'type' => 'map_square',
    'uid' => 1,
    'status' => 1,
    'comment' => 1,
    'promote' => 0,
  );
  $e = entity_create('node', $values);
  /* @var \EntityDrupalWrapper $ew */
  $ew = entity_metadata_wrapper('node', $e);

  // Assign title field
  $ew->title->set($square['name']);

  // Assign KML/KMZ file.
  if (!empty($square['kmz']) || !empty($square['kml'])) {
    /* @var \SplFileInfo $f */
    $f = empty($square['kmz']) ? $square['kml'] : $square['kmz'];
    $file_entity = create_managed_file($f);
    $ew->field_map_sq_kmz->file->set($file_entity);
  }

  // Assign GPX file.
  if (!empty($square['gpx'])) {
    /* @var \SplFileInfo $f */
    $f = $square['gpx'];
    $file_entity = create_managed_file($f);
    $ew->field_map_sq_gpx->file->set($file_entity);
  }

  // Assign PNG file.
  if (!empty($square['png'])) {
    /* @var \SplFileInfo $f */
    $f = $square['png'];
    $file_entity = create_managed_file($f);
    $ew->field_map_sq_preview->file->set($file_entity);
  }

  $ew->save();

  return TRUE;
}

/**
 * Check is node for given square already exists.
 *
 * @param array $square Square data.
 *
 * @return boolean
 */
function square_node_exists($square) {
  $q = new \EntityFieldQuery();
  $q->entityCondition('entity_type', 'node');
  $q->entityCondition('bundle', 'map_square');
  $q->propertyCondition('title', $square['name']);
  $r = $q->execute();
  if ($r) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Remove all square nodes.
 * Useful for testing to drop all nodes just after import.
 */
function drop_square_nodes() {
  $q = new \EntityFieldQuery();
  $q->entityCondition('entity_type', 'node');
  $q->entityCondition('bundle', 'map_square');
  $r = $q->execute();
  if ($r) {
    $nids = array_keys($r['node']);
    node_delete_multiple($nids);
  }
}

/**
 * Create file entity.
 *
 * @param \SplFileInfo $file.
 *
 * @return object $file.
 */
function create_managed_file(\SplFileInfo $f) {
  if (!$f->isReadable()) {
    throw new \Exception('File ' . $f->getRealPath() . 'is not readable');
  }

  switch ($f->getExtension()) {
    case 'kmz':
    case 'kml':
      $dest = 'private://map-square/kmz/' . $f->getFilename();
      break;
    case 'gpx':
      $dest = 'private://map-square/kmz/' . $f->getFilename();
      break;
    case 'png':
      'private://map-square/kmz/' . $f->getFilename();
      break;
    default:
      'private://map-square/' . $f->getExtension() .'/'.$f->getFilename();
  }

  $f_data = file_get_contents($f->getRealPath());
  $file_entity = file_save_data($f_data, $dest, FILE_EXISTS_REPLACE);
  return $file_entity;
}
