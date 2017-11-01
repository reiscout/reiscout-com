<?php

/**
 * @interface SellEntityProductHelperInterface.
 *
 * Class implementing entity to product relationships and helper methods must implement this interface.
 */
interface SellEntityProductHelperInterface {

  /**
   * Return commerce product type name.
   */
  public function getProductType();

  /**
   * Return entity type name that has attached commerce product.
   */
  public function getEntityType();

  /**
   * Return bundle name of entity type returned by getProductType() that has attached commerce product.
   */
  public function getEntityBundle();

  /**
   * Perform all actions on entity creation.
   *
   * Like creating and attaching the product.
   */
  public function onEntityCreate($entity);

  /**
   * Perform all actions on entity update.
   *
   * Like updating the product.
   */
  public function onEntityUpdate($entity);

  /**
   * Perform all actions on entity delete.
   *
   * Like deleting or disabling the product.
   */
  public function onEntityDelete($entiry);

  /**
   * Return commerce product attached to passed entity.
   */
  public function getProductByEntity($entity);

  /**
   * Return entity attached to passed commerce product.
   */
  public function getEntityByProduct($product);

  /**
   * Return form to purchase an entity.
   */
  public function getProductForm($entity);

  /**
   * Check is entity purchased.
   */
  public function isEntityPurchased($entity);

}
