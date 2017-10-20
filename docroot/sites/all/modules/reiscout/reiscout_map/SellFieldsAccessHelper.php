<?php

/**
 * @class SellFieldsAccessHelper.
 *
 * Selling an access to fields of entity for points it is a common task for this project.
 * Implementation is a common to and including:
 *  - implement hook_field_access to deny access if the product not been purchased yet.
 *  - implement hook_node_view to add a purchase form if the product not been purchased yet.
 *  - implement hook_node_presave to have a product for each node containing fields to sale.
 *  - implement hook_node_delete to delete a products.
 *
 * This class provide an implementation for each of these hooks.
 *
 * Probably it is better to implement it as a CTools plugin but let it be just a simple class for now.
 */
class SellNodeFieldsAccessHelper {

  private $sku;

  private $node_type;

  private $fields;

  public function __construct($node_type, $fields, $sku) {

  }

  public function hook_field_access() {

  }

  public function hook_node_view() {

  }

  public function hook_node_presave($hook_args) {

  }

  public function hook_node_delete($hook_args) {

  }

}
