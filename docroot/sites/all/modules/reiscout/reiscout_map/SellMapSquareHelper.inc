<?php

/**
 * @class SellMapSquareHelper.
 */
class SellMapSquareHelper extends SellEntityProductHelper implements SellEntityProductHelperInterface {

  protected $productType = 'individual_map_square';

  protected $entityType = 'node';

  protected $entityBundle = 'map_square';

  protected $entityRefFieldName = 'field_map_square_ref';

  /**
   * @inheritdoc
   */
  public function __construct() {
    parent::__construct();
  }

  /**
   * Payed access fields.
   */
  private function fieldsAccessToSell() {
    return array(
      'field_map_sq_kmz',
      'field_map_sq_gpx',
    );
  }

  /**
   * Is $account has full payed access to $entity.
   */
  private function userHasAccess($entity, $account) {
    // Show property info fields only for
    // - admin role
    // - user is node author
    // - user who purchased the product.

    // User is an administrator.
    $role_admin = user_role_load_by_name('administrator');
    if (user_has_role($role_admin->rid, $account)) {
      return TRUE;
    }

    // User is an entity author.
    if ($entity->uid == $account->uid) {
      return TRUE;
    }

    // User has bought a product.
    if ($this->isEntityPurchased($entity)) {
      return TRUE;
    }

    /* ToDo: check for specific city product related to the current city square */
    /* For now all the squares are for Atlanta so thats fine. */
    $atlanta_product_helper = new SellAtlantaMapSquaresHelper();
    if ($atlanta_product_helper->isPurchased()) {
      return TRUE;
    }

    // Deny access otherwise.
    return FALSE;
  }

  /**
   * hook_field_access implementation.
   */
  public function hookFieldAccess($op, $field, $entity_type, $entity, $account) {
    // Access control for property info fields (address and etc) in property node.
    if ($op == 'view' && $entity_type == $this->entityType && !empty($entity->type) && $entity->type == $this->entityBundle
      &&  in_array($field['field_name'], $this->fieldsAccessToSell())) {

      return $this->userHasAccess($entity, $account);
    }

  }

}
