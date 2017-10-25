<?php

/**
 * @class SellFieldsAccessHelper.
 *
 * Selling an access to fields of entity for points it is a common task for this project.
 * Implementation is a common to and including:
 *  - implement hook_field_access to deny access if the product not been purchased yet.
 *  - implement hook_node_view to add a purchase form if the product not been purchased yet.
 *  - implement hook_node_presave to have a product for each node containing fields to sale.
 *  - implement hook_node_delete to delete a products.
 *
 * This class provide an implementation for each of these hooks.
 *
 * Probably it is better to implement it as a CTools plugin but let it be just a simple class for now.
 *
 * ToDo: remove it.
 */
class SellNodeFieldsAccessHelper {

  private $sku;

  private $node_type;

  private $product_type;

  /* Include node ? */
  private $node;

  /**
   * Field reference name referencing product from node.
   */
  private $product_ref_field_name;

  /**
   * Field reference name referencing node from product.
   */
  private $node_ref_field_name;

  private $fields;

  public function __construct($node_type, $fields, $product_type) {
    $this->node_type = $node_type;
    $this->fields = $fields;
    $this->product_type = $product_type;
  }

  public function load_product_by_node($node) {
    $efq = new EntityFieldQuery();
    $efq->entityCondition('entity_type', 'commerce_product')
      ->entityCondition('bundle', $this->product_type)
      ->propertyCondition('status', TRUE)
      ->fieldCondition($this->node_ref_field_name, 'target_id', $node->nid);

    $result = $efq->execute();
    if (isset($result['commerce_product'])) {
      $product_id = key($result['commerce_product']);
      return entity_load('commerce_product', $product_id);
    }
  }

  public function hook_field_access($op, $field, $entity_type, $entity, $account) {
    // Access control for property info fields (address and etc) in property node.
    if ($op == 'view' && $entity_type == 'node' && !empty($entity->type) && $entity->type == $this->node_type
      &&  in_array($field['field_name'], $this->fields) ) {

      // Show property info fields only for
      // - admin role
      // - user is node author
      // - user who purchased the product

      // User is an administrator
      $role_admin = user_role_load_by_name('administrator');
      if (user_has_role($role_admin->rid, $account)) {
        return TRUE;
      }

      // User is a property's author
      if ($entity->uid == $account->uid) {
        return TRUE;
      }

      // User has bought a product
      if (reiscout_points_product_is_purchased($this->sku, $account)) {
        return TRUE;
      }

      // Deny access otherwise
      return FALSE;
    }

  }

  public function hook_node_view($node, $view_mode, $langcode) {
    if ('property' != $node->type || 'full' != $view_mode) {
      return;
    }
    $form = $this->get_product_form($node);
    $node->content['reiscout-property-lead-form'] = $form;
  }

  public function get_product_form ($node) {
    $product = $this->load_product_by_node($node);
    $form = reiscout_points_product_get_buy_form($product->sku);
    return $form;
  }

  public function hook_node_delete($node) {
    if ($node->type == $this->node_type) {
      $product = $this->load_product_by_node($node);
      if ($product) {
        $this->disable_product($product);
      }
    }
  }

  /**
   * Set product status to disabled.
   */
  public function disable_product($product) {
    try {
      $pw = entity_metadata_wrapper('commerce_product', $product);
      $pw->status->set(0);
      $pw->save();
    } catch (Exception $e) {
      throw new Exception($e->getMessage());
    }
  }

  public function attach_product($node) {
    $product = create_product($node);
    if ($this->product_ref_field_name) {
      // ToDo: attach product to node via reference field.
    }
  }

  public function create_product($reference_node) {
    if (empty($reference_node->nid)) {
      throw new Exception('nid is required in passed node object');
    }

    if (empty($this->node_ref_field_name)) {
      throw new Exception('node_ref_field_name should not be empty');
    }

    $product_type = $this->product_type;

    $product = commerce_product_new($product_type);
    $product->{$this->node_ref_field_name}[LANGUAGE_NONE][0]['target_id'] = $reference_node->nid;
    $product->commerce_price[LANGUAGE_NONE][0] = array(
      'amount' => 0,
      'currency_code' => 'USD',
    );

    $product->title = $this->product_type . ' for '. $reference_node->title;
    $product->sku =  $this->product_type . '-for-property-node-'. $reference_node->nid;

    commerce_product_save($product);

    return $product;
  }

  public function hook_node_presave($node) {

    // Looking for existed product or create one and attach to node if it is not attached yet
    if (empty($node->{$this->product_ref_field_name}[LANGUAGE_NONE][0])) {
      if (!empty($node->nid)) {
        $product = $this->load_product_by_node($node->nid);
      }

      if (empty($address_access_product)) {
        $address_access_product = reiscout_property_commerce_create_product(REISCOUT_PROPERTY_COMMERCE_ADDRESS_ACCESS_PRODUCT_TYPE, $node);
      }
      $node->field_address_access_product[LANGUAGE_NONE][0]['product_id'] = $address_access_product->product_id;
    }

  }

}
