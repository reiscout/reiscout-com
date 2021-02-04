<?php

/**
 * @file
 * Page callback file for the Reiscout Equity Percentage module.
 */

/**
 * Page callback: Displays a list of purchased properties with uncalculated EPE.
 *
 * Displays a list of properties whose 'Address Access' product was purchased,
 * but 'Calculated Equity Percentage' field is not filled.
 */
function reiscout_equity_percentage_report_page() {
  $content = array();

  $header = array('Title');
  $rows = array();

  if ($nodes = _reiscout_equity_percentage_get_uncalculated_nodes()) {
    foreach ($nodes as $nid => $title) {
      $rows[] = array(l($title, 'node/' . $nid));
    }
  }

  $content['table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('There are no uncalculated purchased properties.'),
  );

  return $content;
}

/**
 * Returns a list of purchased properties with uncalculated EPE.
 *
 * Returns nodes whose 'Address Access' product was purchased,
 * but 'Calculated Equity Percentage' field is not filled.
 */
function _reiscout_equity_percentage_get_uncalculated_nodes() {
  if (!$purchased_nodes_nids = reiscout_property_commerce_get_purchased_nodes(REISCOUT_PROPERTY_COMMERCE_ADDRESS_ACCESS_PRODUCT_TYPE)) {
    return FALSE;
  }

  $query = db_select('node', 'n');
  $query->leftJoin('field_data_field_ep_calculated', 'fc', 'n.nid = fc.entity_id');
  $query
    ->fields('n', array('nid', 'title'))
    ->condition('n.nid', $purchased_nodes_nids)
    ->isNull('fc.field_ep_calculated_value');

  return $query->execute()->fetchAllKeyed(0, 1);
}
