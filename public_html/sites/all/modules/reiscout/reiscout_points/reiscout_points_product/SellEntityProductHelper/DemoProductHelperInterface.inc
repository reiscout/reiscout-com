<?php

/**
 * @interface SellEntityProductHelperInterface.
 *
 * Product helper implementing a demo products must implement this interface..
 */
interface DemoProductHelperInterface {

  /**
   * Return demo entities UUID array.
   *
   * @return array
   */
  public function getDemoEntitiesUUID();

  /**
   * Check is entity is a demo entity.
   *
   * @param object $entity.
   *
   * @return boolean
   */
  public function isDemoEntity($entity);

}
