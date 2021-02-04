<?php

/**
 * @file
 * Service's resources callbacks.
 */

function _editableapi_resource_save($nid, $type, $field, $language, $delta, $value) {
  try {
    $node = node_load($nid);
    $node->{$field}[$language][$delta]['value'] = $value;
    field_attach_validate('node', $node, ['field_name' => $field, 'language' => $language]);
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
  catch (FieldValidationException $e) {
    $errors = [];

    if (isset($e->errors[$field]) && isset($e->errors[$field][$language]) && isset($e->errors[$field][$language][$delta])
        && is_array($e->errors[$field][$language][$delta]) && $e->errors[$field][$language][$delta]
    ) {
      foreach ($e->errors[$field][$language][$delta] as $error) {
        if (is_array($error) && !empty($error['message'])) {
          $errors = $error['message'];
        }
      }
    }

    services_error('Could not save changes', 500, $errors);
  }
  catch (Exception $e) {
    services_error('Could not save changes', 500);
  }
}
