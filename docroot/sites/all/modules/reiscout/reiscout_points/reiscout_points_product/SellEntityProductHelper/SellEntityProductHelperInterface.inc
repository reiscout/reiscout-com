<?php

/**
 * @interface SellEntityProductHelperInterface.
 */
interface SellEntityProductHelperInterface {

  public function get_product_type();

  public function get_entity_type();

  public function get_entity_bundle();

  public function on_entity_create($entity);

  public function on_entity_update($entity);

  public function on_entity_delete($entiry);

  public function get_product_by_entity($entity);

  public function get_entity_by_product($product);

  public function get_product_form($entity);

  public function is_entity_purchased($entity);

}
