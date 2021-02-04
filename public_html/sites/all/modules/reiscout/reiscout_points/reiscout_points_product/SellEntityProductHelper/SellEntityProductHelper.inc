<?php

/**
 * @class SellEntityProductHelper.
 *
 * Default implementation of methods for SellEntityProductHelperInterface and some other methods.
 *
 * ToDo: turn member variables to static.
 *
 */
abstract class SellEntityProductHelper implements SellEntityProductHelperInterface {

  protected $productType;

  protected $entityType;

  protected $entityBundle;

  protected $entityRefFieldName = NULL;

  protected $productRefFieldName = NULL;

  /**
   * Class constructor.
   *
   * Check for requirements.
   */
  public function __construct() {
    if (!isset($this->entityRefFieldName) && !isset($this->productRefFieldName)) {
      throw new Exception('Either $entityRefFieldName or $productRefFieldName member variable should not be empty.');
    }
  }

  /**
   * @inheritdoc
   */
  public function getProductType() {
    return $this->productType;
  }

  /**
   * @inheritdoc
   */
  public function getEntityType() {
    return $this->entityType;
  }

  /**
   * @inheritdoc
   */
  public function getEntityBundle() {
    return $this->entityBundle;
  }

  /**
   * @inheritdoc
   */
  public function onEntityCreate($entity) {
    $this->createProduct($entity);
  }

  /**
   * @inheritdoc
   */
  public function onEntityUpdate($entity) {
    /* Do nothing on update */
  }

  /**
   * @inheritdoc
   */
  public function onEntityDelete($entity) {
    $product = $this->getProductByEntity($entity);
    if ($product) {
      $this->disableProduct($product);
    }
  }

  /**
   * @inheritdoc
   */
  public function getProductByEntity($entity) {
    $wrapper = entity_metadata_wrapper($this->entityType, $entity);
    $efq = new EntityFieldQuery();
    $efq->entityCondition('entity_type', 'commerce_product')
      ->entityCondition('bundle', $this->productType)
      ->propertyCondition('status', TRUE)
      ->fieldCondition($this->entityRefFieldName, 'target_id', $wrapper->getIdentifier());

    $result = $efq->execute();
    if (isset($result['commerce_product'])) {
      $product_id = key($result['commerce_product']);
      $product = commerce_product_load($product_id);
      return $product;
    }

    return FALSE;
  }

  /**
   * @inheritdoc
   */
  public function getEntityByProduct($product) {
    $wrapper = entity_metadata_wrapper('commerce_product', $product);

    if (!empty($this->entityRefFieldName)) {
      $entity = $wrapper->{$this->entityRefFieldName}->get();
      if ($entity) {
        return $entity;
      }
    }

    if (!empty($this->productRefFieldName)) {
      $efq = new EntityFieldQuery();
      $efq->entityCondition('entity_type', $this->entityType);
      if ($this->entityBundle) {
        $efq->entityCondition('bundle', $this->entityBundle);
      }
      $efq->fieldCondition($this->productRefFieldName, 'target_id', $wrapper->getIdentifier());

      $result = $efq->execute();
      if (isset($result[$this->entityType])) {
        $entity_id = key($result[$this->entityType]);
        return entity_load($this->entityType, $entity_id);
      }
    }
  }

  /**
   * @inheritdoc
   */
  public function getProductForm($entity) {
    $product = $this->getProductByEntity($entity);
    $form = reiscout_points_product_get_buy_form_by_sku($product->sku);
    return $form;
  }

  /**
   * @inheritdoc
   */
  public function isEntityPurchased($entity, $account = NULL) {
    if (!isset($account)) {
      $account = $GLOBALS['user'];
    }

    if ($this instanceof DemoProductHelperInterface) {
      if ($this->isDemoEntity($entity)) {
        return TRUE;
      }
    }

    // User has bought a product.
    $product = $this->getProductByEntity($entity);

    if (reiscout_points_product_is_purchased($product->sku, $account)) {
      return TRUE;
    }
    return FALSE;
  }

  /**
   *
   */
  protected function createProduct($entity) {

    if (empty($this->entityRefFieldName)) {
      throw new Exception('entity_ref_field_name should not be empty');
    }

    $entity_wrapper = entity_metadata_wrapper($this->entityType, $entity);

    $product_type = $this->productType;

    $product = commerce_product_new($product_type);
    $product->{$this->entityRefFieldName}[LANGUAGE_NONE][0]['target_id'] = $entity_wrapper->getIdentifier();

    $points_product = reiscout_points_product_get($product_type);
    if ($points_product) {
      $price = reiscout_points_product_get_price($points_product['id']);
      if ($price === FALSE) {
        throw new Exception('Price for ' . $product_type . 'points product type is not set.');
      }
      $product->commerce_price[LANGUAGE_NONE][0] = array(
        'amount' => $price,
        'currency_code' => 'PTS',
      );
    }
    else {
      $product->commerce_price[LANGUAGE_NONE][0] = array(
        'amount' => 0,
        'currency_code' => 'USD',
      );
    }

    $product->title = $this->productType . ' for ' . $entity_wrapper->label();
    $product->sku = $this->productType . '-for-' . $this->getEntityType() . '-' . $this->getEntityBundle() . '-' . $entity_wrapper->getIdentifier();

    commerce_product_save($product);

    return $product;
  }

  /**
   *
   */
  protected function disableProduct($product) {
    try {
      $pw = entity_metadata_wrapper('commerce_product', $product);
      $pw->status->set(0);
      $pw->save();
    }
    catch (Exception $e) {
      throw new Exception($e->getMessage());
    }
  }

  /**
   * Default implementation for DemoProductHelperInterface::isDemoEntity
   */
  public function isDemoEntity($entity) {
    if (!($this instanceof DemoProductHelperInterface)) {
      throw new Exception('Object must implement DemoProductHelperInterface');
    }

    if (in_array($entity->uuid, $this->getDemoEntitiesUUID())) {
      return TRUE;
    }
    return FALSE;

  }

}
