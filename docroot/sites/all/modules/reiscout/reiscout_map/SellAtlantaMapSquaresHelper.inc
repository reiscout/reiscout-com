<?php

/**
 * @class SellAtlantaMapSquaresHelper.
 */
class SellAtlantaMapSquaresHelper {

  const PRODUCT_TYPE = 'city_map_square';

  const SKU = 'all-atlanta-map-squares';

  /**
   * Constructor
   */
  public function __construct() {
    $product = commerce_product_load_by_sku(self::SKU);
    if (empty($product)) {
      throw new Exception(self::SKU . ' product is missed.');
    }
  }

  /**
   * Return commerce product type name.
   */
  public function getProductType() {
    return self::PRODUCT_TYPE;
  }

  /**
   * Return product SKU.
   */
  public function getProductSKU() {
    return self::SKU;
  }

  /**
   * Check is product purchased.
   */
  public function isPurchased($account = NULL) {
    if (!isset($account)) {
      $account = $GLOBALS['user'];
    }

    if (reiscout_points_product_is_purchased(self::SKU, $account)) {
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Return form to purchase a product.
   */
  public function getProductForm() {
    $form = reiscout_points_product_get_buy_form_by_sku(self::SKU);
    return $form;
  }

}
