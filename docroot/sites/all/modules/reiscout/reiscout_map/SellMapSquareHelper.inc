<?php

/**
 * @class SellMapSquareHelper.
 */
class SellMapSquareHelper extends SellEntityProductHelper implements SellEntityProductHelperInterface {

  protected $product_type = 'individual_map_square';

  protected $entity_type = 'node';

  protected $entity_bundle = 'map_square';

  protected $entity_ref_field_name = 'field_map_square_ref';

  public function __construct() {
    parent::__construct();
  }

  private function fields_access_to_sell() {
    return array(
      'field_map_sq_kmz',
      'field_map_sq_gpx',
    );
  }

  private function user_has_access($entity, $account) {
    // Show property info fields only for
    // - admin role
    // - user is node author
    // - user who purchased the product

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
    if ($this->is_entity_purchased($entity)) {
      return TRUE;
    }

    /* ToDo: check for specific city product related to the current city square */
    /* For now all the squares are for Atlanta so thats fine. */
    $atlanta_product_helper = new SellAtlantaMapSquaresHelper();
    if ($atlanta_product_helper->is_purchased()) {
      return TRUE;
    }

    // Deny access otherwise.
    return FALSE;
  }

  public function hook_field_access($op, $field, $entity_type, $entity, $account) {
    // Access control for property info fields (address and etc) in property node.
    if ($op == 'view' && $entity_type == $this->entity_type && !empty($entity->type) && $entity->type == $this->entity_bundle
      &&  in_array($field['field_name'], $this->fields_access_to_sell()) ) {

      return $this->user_has_access($entity, $account);
    }

  }

}
