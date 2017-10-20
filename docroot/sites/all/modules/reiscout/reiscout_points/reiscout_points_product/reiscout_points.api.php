<?php
/**
 * @file
 * This file contains no working PHP code; it exists to provide additional
 * documentation for doxygen as well as to document hooks in the standard
 * Drupal manner.
 */

/**
 * Defines reiscout points products ().
 *
 * @return
 *   An array of points products data arrays
 *   Points product data array should include:
 *     - title: A product title that will appear in purchase button title.
 *     - description:
 *     - desc_callback: description callback will be called by web service.
 *     - sell_callback: callback will be called just before points charging. Must return true on success.
 *     - services_sell_callback: a sell callback for we service call.
 *     - access_callback: a callback defining does user has an access to the product for given node. Called by web service only.
 *     - params_callback: a callback to return arguments will be used by reiscout_points_product_get_price() called from service callback.
 */
function hook_reiscout_points_product_info() {
  return array(
    'property_lead' => array(
      'title' => t('Buy Property Lead'),
      'description' => t("Gives a user an 'Address Access' and an 'Owner Info' products"),
      'desc_callback' => 'get_desc_for_property_lead_product',
      'sell_callback' => 'sell_property_lead_product',
      'services_sell_callback' => 'sell_property_lead_product_services',
      'access_callback' => 'user_can_buy_property_lead',
      'params_callback' => 'build_params_for_property_lead_product',
    ),
  );
}

/**
 * Implements hook_node_view().
 * Example attaching the product form to a node.
 */
function mymodule_node_view(&$node) {
  $params = array();
  $form = reiscout_points_product_get_buy_form('property_lead', $params);
  $node->content['buy_property_lead'] = $form;
}

/**
 * Implement desc_callback.
 */
function get_desc_for_property_lead_product ($service_request_args) {
  return t('You will get all the info about the property');
}

/**
 * Implement sell_callback.
 */
function sell_property_lead_product ($params) {
  return TRUE;
}

/**
 * Implement services_sell_callback.
 */
function sell_property_lead_product_services ($params) {
  return TRUE;
}

/**
 * Implement access_callback.
 */
function user_can_buy_property_lead ($node) {
  // If the product avaliable for this node
  return TRUE;
}

/**
 * Implement params_callback.
 */
function build_params_for_property_lead_product ($node) {
  $params = [];
  return $params;
}
