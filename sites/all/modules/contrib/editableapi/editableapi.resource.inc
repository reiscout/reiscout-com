<?php

/**
 * @file
 * Service's resources callbacks.
 */

function _editableapi_resource_save($nid, $type, $field, $language, $delta, $value) {
  try {
    $node = node_load($nid);
    $node->{$field}[$language][$delta]['value'] = $value;
    node_save($node);

    $value  = '';
    $node   = node_load($nid, null, true);
    $values = field_get_items('node', $node, $field, $language);

    if ($values && isset($values[$delta])) {
      /*if (isset($values[$delta]['safe_value'])) {
        $value = $values[$delta]['safe_value'];
      }
      else*/ if (isset($values[$delta]['value'])) {
        $value = $values[$delta]['value'];
      }
    }

    return array('value' => $value, 'node' => $node);
  }
  catch (Exception $e) {
    services_error('Could not save changes', 500);
  }
}
