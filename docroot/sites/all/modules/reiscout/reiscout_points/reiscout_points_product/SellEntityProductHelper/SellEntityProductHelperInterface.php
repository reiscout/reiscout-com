<?php

/**
 * Created by PhpStorm.
 * User: vlad
 * Date: 25.10.17
 * Time: 13:29
 */
class SellEntityProductHelperInterface {

  private $product_type;

  private $entity_type;

  private $entity_bundle;

  public function on_entity_create($entity) {

  }

  public function on_entity_update($entity) {}

  public function on_entity_delete($entiry) {}

  public function get_product_by_entity($entity) {}

  public function get_entity_by_product($product) {}

  public function get_product_form($entity) {}

  public function is_entity_purchased($entity) {}



}
