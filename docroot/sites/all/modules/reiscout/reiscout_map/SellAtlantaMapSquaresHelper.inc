<?php

/**
 * @class SellAtlantaMapSquaresHelper.
 */
class SellAtlantaMapSquaresHelper {

  const PRODUCT_TYPE = 'city_map_square';

  const SKU = 'all-atlanta-map-squares';

  public function __construct() {
    $product = commerce_product_load_by_sku(self::SKU);
    if (empty($product)) {
      throw new Exception(self::SKU . ' product is missed.');
    }
  }

  public function get_product_type() {
    return self::PRODUCT_TYPE;
  }

  public function get_product_sku() {
    return self::SKU;
  }

  public function is_purchased($account = NULL) {
    if (!isset($account)) {
      $account = $GLOBALS['user'];
    }

    if (reiscout_points_product_is_purchased(self::SKU, $account)) {
      return TRUE;
    }
    return FALSE;
  }

  public function get_product_form () {
    $form = reiscout_points_product_get_buy_form_by_sku(self::SKU);
    return $form;
  }

}
