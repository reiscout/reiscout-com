<?php

/**
 * @class SellMapSquareHelper.
 */
class SellMapSquareHelper extends SellEntityProductHelper
  implements SellEntityProductHelperInterface, DemoProductHelperInterface {

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
   * @inheritdoc
   */
  public function getDemoEntitiesUUID() {
    $uuids = array();

    // A square on prod for Atlanta, the one on the 'A' of 'Atlanta' caption.
    $uuids[] = 'd0856f1a-09e2-420a-ac04-9dfb4b3fb366';

    // Test squares on north, east, west, south
    $uuids[] = '65279ff1-eea5-4980-a2de-b6c8fd96185e';
    $uuids[] = 'adefcdc9-eb7e-4552-8458-2a8505082f75';
    $uuids[] = '80aeca37-b271-4bd9-b270-6a3fdcbc3337';
    $uuids[] = 'e68c796e-4110-4cc9-8da9-7eec91a40cb1';

    return $uuids;
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

  /**
   * Return a render array of links to demo squares.
   *
   * @return array
   *   Render array
   */
  public function getDemoSquaresLinks() {
    $demo_squares = entity_uuid_load($this->getEntityType(), $this->getDemoEntitiesUUID());

    $links = array();
    foreach ($demo_squares as $square) {
      try {
        /* @var EntityDrupalWrapper $wrapper  */
        $wrapper = entity_metadata_wrapper($this->getEntityType(), $square);
        $links[] = array(
          '#type' => 'link',
          '#title' => $wrapper->label(),
          '#href' => $wrapper->url->value(),
        );
      } catch (Exception $e) {
        watchdog_exception(__CLASS__, $e, 'Error on demo map squares operation.');
      }
    }

    return $links;
  }

}
