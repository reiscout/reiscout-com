<?php

/*
 * @file
 * Definition of Postcard class.
 */

class Postcard {
  /**
   * Returns a list of global templates.
   */
  static function getGlobalTemplates() {
    $nids = self::getGlobalTemplateNids();
    return node_load_multiple($nids);
  }

  /**
   * Returns nids of global templates.
   */
  static function getGlobalTemplateNids() {
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'postcard_template')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->fieldCondition('field_postcard_template_global', 'value', TRUE)
      ->fieldOrderBy('field_postcard_design_template', 'tid')
      ->propertyOrderBy('created')
      ->execute();

    if (!isset($result['node'])) {
      $msg = t('No global postcard templates defined.');
      throw new ReiscoutMailNoGlobalTemplatesDefined($msg);
    }

    return array_keys($result['node']);
  }

  /**
   * Returns a list of user defined templates.
   */
  static function getUserDefinedTemplates($uid) {
    if (!$nids = self::getUserDefinedTemplateNids($uid)) {
      return FALSE;
    }

    return node_load_multiple($nids);
  }

  /**
   * Returns nids of user defined templates.
   */
  static function getUserDefinedTemplateNids($uid) {
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'postcard_template')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->propertyCondition('uid', $uid)
      ->fieldCondition('field_postcard_template_global', 'value', FALSE)
      ->execute();

    if (!isset($result['node'])) {
      return FALSE;
    }

    return array_keys($result['node']);
  }

  /**
   * Returns the NID of a template for a given user.
   */
  static function getTemplateNidByUid($uid) {
    $templateNids = self::getGlobalTemplateNids();

    if ($nids = self::getUserDefinedTemplateNids($uid)) {
      $templateNids = array_merge($templateNids, $nids);
    }

    $templateNid = self::getDefaultTemplateNidByUid($uid);

    // If the default template is not set for a given user, or the template is
    // not available anymore, set it to the NID of the first available template.
    if (!$templateNid || !in_array($templateNid, $templateNids)) {
      $templateNid = $templateNids[0];
    }

    return $templateNid;
  }

  /**
   * Returns the NID of the default template for a given user.
   */
  static function getDefaultTemplateNidByUid($uid) {
    $query = db_select('reiscout_mail_user_settings', 's')
      ->fields('s', array('default_postcard_template_nid'))
      ->condition('uid', $uid);

    return $query->execute()->fetchField();
  }

  /**
   * Saves the NID of the default template for a given user.
   */
  static function saveDefaultTemplateNidForUser($uid, $tid) {
    $fields = array(
      'default_postcard_template_nid' => $tid,
    );
    db_merge('reiscout_mail_user_settings')
      ->key(array('uid' => $uid))
      ->fields($fields)
      ->execute();
  }

  /**
   * Returns a list of templates.
   *
   * Returns a list of templates that will be used as a list of options
   * of an HTML select tag.
   */
  static function getTemplatesOptions($node) {
    global $user;

    $globalTemplates = self::getGlobalTemplates();
    $userDefinedTemplates = self::getUserDefinedTemplates($user->uid);

    return self::combineTemplatesOptions($globalTemplates, $userDefinedTemplates, $node);
  }

  /**
   * Combines a list of templates.
   *
   * Combines a list of templates that will be used as a list of options
   * of an HTML select tag.
   */
  static function combineTemplatesOptions($globalTemplates, $userDefinedTemplates, $propertyNode) {
    $options = array();

    foreach ($globalTemplates as $templateNid => $templateNode) {
      $options[$templateNid] = self::combineTemplateOption($templateNode, $propertyNode);
    }

    if ($userDefinedTemplates) {
      foreach ($userDefinedTemplates as $templateNid => $templateNode) {
        $options[$templateNid] = self::combineTemplateOption($templateNode, $propertyNode, 'custom');
      }
    }

    return $options;
  }

  /**
   * Generates a template preview.
   *
   * Generates a template preview that will be used as an option
   * of an HTML select tag.
   */
  static function combineTemplateOption($templateNode, $propertyNode, $type = 'predefined') {
    $option = array();

    $tnw = entity_metadata_wrapper('node', $templateNode);
    $designTemplate = $tnw->field_postcard_design_template->machine_name->value();

    $front = self::buildFrontContent($propertyNode->nid, $templateNode->nid);
    $back = self::buildBackContent($propertyNode->nid, $templateNode->nid);
    $back = self::addAddressBlock($back, $propertyNode->nid);

    if ('predefined' == $type) {
      $titlePrefix = t('Predefined:');
    }
    else {
      $titlePrefix = t('Custom:');
    }

    $links = array();

    $urlOptions = array(
      'query' => array(
        'destination' => current_path(),
      ),
      'absolute' => TRUE,
    );

    if (user_access('clone node') && node_access('create', 'postcard_template')) {
      $cloneToken = clone_get_token($tnw->nid->value());
      $cloneUrl = url('node/' . $tnw->nid->value() . '/clone/' . $cloneToken . '/', $urlOptions);
      $links[] = l(t('create my template based on this one'), $cloneUrl, array('html' => TRUE));
    }

    if (node_access('update', $templateNode)) {
      $links[] = l(t('edit'), url('node/' . $tnw->nid->value() . '/edit', $urlOptions), array('html' => TRUE));
    }

    if (node_access('delete', $templateNode)) {
      $links[] = l(t('delete'), url('node/' . $tnw->nid->value() . '/delete', $urlOptions), array('html' => TRUE));
    }

    $option['header'] = array(
      '#prefix' => '<div class="header">',
      '#markup' => $titlePrefix . ' ' . $tnw->title->value() . ($links ? ' | ' . implode(' | ', $links) : ''),
      '#suffix' => '</div>',
    );

    $option['front'] = array(
      '#prefix' => '<div class="template ' . $type . ' ' . $designTemplate . '"><div class="front">',
      '#markup' => $front,
      '#suffix' => '</div>',
    );

    $option['back'] = array(
      '#prefix' => '<div class="back">',
      '#markup' => $back,
      '#suffix' => '</div></div>',
    );

    return drupal_render($option);
  }

  /**
   * Adds an address block to content.
   *
   * Given a property node and content that will be used as the back
   * of a postcard, builds an address block and adds it to the content.
   */
  static function addAddressBlock($content, $propertyNid) {
    $propertyOwnerAddress = _reiscout_property_get_owner_address_by_nid($propertyNid);
    $propertyOwnerName = _reiscout_property_get_owner_name_by_nid($propertyNid);
    $userAddress = _reiscout_property_get_user_address();

    $addressBlockContent = array(
      '#theme' => 'reiscout_mail_postcard_address_block',
      '#to' => array(
        'name'         => $propertyOwnerName,
        'thoroughfare' => $propertyOwnerAddress->thoroughfare->value(),
        'premise'      => $propertyOwnerAddress->premise->value(),
        'city'         => $propertyOwnerAddress->locality->value(),
        'state'        => $propertyOwnerAddress->administrative_area->value(),
        'zip'          => $propertyOwnerAddress->postal_code->value(),
      ),
      '#from' => array(
        'name'         => $userAddress->name_line->value(),
        'thoroughfare' => $userAddress->thoroughfare->value(),
        'premise'      => $userAddress->premise->value(),
        'city'         => $userAddress->locality->value(),
        'state'        => $userAddress->administrative_area->value(),
        'zip'          => $userAddress->postal_code->value(),
      ),
    );

    return $content . drupal_render($addressBlockContent);
  }

  /*
   * Sends a postcard to the owner of a property.
   */
  static function send($propertyNid, $templateNid) {
    $propertyOwnerAddress = _reiscout_property_get_owner_address_by_nid($propertyNid);
    $propertyOwnerName = _reiscout_property_get_owner_name_by_nid($propertyNid);
    $userAddress = _reiscout_property_get_user_address();

    $front = self::buildFrontHtml($propertyNid, $templateNid);
    $back = self::buildBackHtml($propertyNid, $templateNid);

    $data = array(
      'to' => array(
        'name'            => $propertyOwnerName,
        'address_line1'   => $propertyOwnerAddress->thoroughfare->value(),
        'address_line2'   => $propertyOwnerAddress->premise->value(),
        'address_city'    => $propertyOwnerAddress->locality->value(),
        'address_state'   => $propertyOwnerAddress->administrative_area->value(),
        'address_zip'     => $propertyOwnerAddress->postal_code->value(),
        'address_country' => $propertyOwnerAddress->country->value(),
      ),

      'from' => array(
        'name'            => $userAddress->name_line->value(),
        'address_line1'   => $userAddress->thoroughfare->value(),
        'address_line2'   => $userAddress->premise->value(),
        'address_city'    => $userAddress->locality->value(),
        'address_state'   => $userAddress->administrative_area->value(),
        'address_zip'     => $userAddress->postal_code->value(),
        'address_country' => $userAddress->country->value(),
      ),

      'front'             => $front,
      'back'              => $back,
    );

    return lob_api_send_postcard($data);
  }

  /**
   * Builds content to use as the front of a postcard.
   *
   * Given a property node and a template node, builds
   * content to use as the front of a postcard.
   */
  static function buildFrontContent($propertyNid, $templateNid) {
    $tnw = entity_metadata_wrapper('node', $templateNid);

    if (_reiscout_property_is_owner_an_individual_by_nid($propertyNid)) {
      $content = $tnw->field_postcard_template_front->value()['safe_value'];
    }
    else {
      $content = $tnw->field_postcard_template_front_co->value()['safe_value'];
    }

    return ReiscoutMail::replaceTokens($content, $propertyNid);
  }

  /**
   * Builds content to use as the back of a postcard.
   *
   * Given a property node and a template node, builds
   * content to use as the back of a postcard.
   */
  static function buildBackContent($propertyNid, $templateNid) {
    $tnw = entity_metadata_wrapper('node', $templateNid);
    $content = $tnw->field_postcard_template_back->value()['safe_value'];

    return ReiscoutMail::replaceTokens($content, $propertyNid);
  }

  /**
   * Builds HTML content to use as the front of a postcard.
   *
   * Given a property node and a template node, builds HTML
   * content to use as the front of a postcard.
   */
  static function buildFrontHtml($propertyNid, $templateNid) {
    $content = self::buildFrontContent($propertyNid, $templateNid);

    $tnw = entity_metadata_wrapper('node', $templateNid);
    $designTemplate = $tnw->field_postcard_design_template->machine_name->value();
    $templateFileName = $designTemplate . '_front.html';
    $templateFilePath = drupal_get_path('module', 'reiscout_mail') . '/html_templates/postcard/' . $templateFileName;

    if (!$templateFileContent = @file_get_contents($templateFilePath)) {
      $msg = t('!file_name file, that is used as the template for the front of a postcard, cannot be read.', array('!file_name' => $templateFileName));
      throw new ReiscoutMailTemplateFileIsNotReadable($msg);
    }

    return str_replace('{{content}}', $content, $templateFileContent);
  }

  /**
   * Builds HTML content to use as the back of a postcard.
   *
   * Given a property node and a template node, builds HTML
   * content to use as the back of a postcard.
   */
  static function buildBackHtml($propertyNid, $templateNid) {
    $content = self::buildBackContent($propertyNid, $templateNid);

    $tnw = entity_metadata_wrapper('node', $templateNid);
    $designTemplate = $tnw->field_postcard_design_template->machine_name->value();
    $templateFileName = $designTemplate . '_back.html';
    $templateFilePath = drupal_get_path('module', 'reiscout_mail') . '/html_templates/postcard/' . $templateFileName;

    if (!$templateFileContent = @file_get_contents($templateFilePath)) {
      $msg = t('!file_name file, that is used as the template for the back of a postcard, cannot be read.', array('!file_name' => $templateFileName));
      throw new ReiscoutMailTemplateFileIsNotReadable($msg);
    }

    return str_replace('{{content}}', $content, $templateFileContent);
  }
}
