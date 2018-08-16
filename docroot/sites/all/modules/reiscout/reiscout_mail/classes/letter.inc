<?php

/*
 * @file
 * Definition of Letter class.
 */

class Letter {
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
      ->entityCondition('bundle', 'letter_template')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->fieldCondition('field_letter_tpl_global', 'value', TRUE)
      ->propertyOrderBy('created')
      ->execute();

    if (!isset($result['node'])) {
      $msg = t('No global letter templates defined.');
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
      ->entityCondition('bundle', 'letter_template')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->propertyCondition('uid', $uid)
      ->fieldCondition('field_letter_tpl_global', 'value', FALSE)
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
      ->fields('s', array('default_letter_template_nid'))
      ->condition('uid', $uid);

    return $query->execute()->fetchField();
  }

  /**
   * Saves the NID of the default template for a given user.
   */
  static function saveDefaultTemplateNidForUser($uid, $tid) {
    $fields = array(
      'default_letter_template_nid' => $tid,
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

    if (user_access('clone node') && node_access('create', 'letter_template')) {
      $cloneToken = clone_get_token($templateNode->nid);
      $cloneUrl = url('node/' . $templateNode->nid . '/clone/' . $cloneToken . '/', $urlOptions);
      $links[] = l(t('create my template based on this one'), $cloneUrl, array('html' => TRUE));
    }

    if (node_access('update', $templateNode)) {
      $links[] = l(t('edit'), url('node/' . $templateNode->nid . '/edit', $urlOptions), array('html' => TRUE));
    }

    if (node_access('delete', $templateNode)) {
      $links[] = l(t('delete'), url('node/' . $templateNode->nid . '/delete', $urlOptions), array('html' => TRUE));
    }

    $option['header'] = array(
      '#prefix' => '<div class="header">',
      '#markup' => $titlePrefix . ' ' . $templateNode->title . ($links ? '<div class="links">' . implode(' | ', $links)  . '</div>' : ''),
      '#suffix' => '</div>',
    );

    $urlPreviewLetter = '/reiscout-mail/preview-letter/' . $propertyNode->nid . '/' . $templateNode->nid;
    $linkPreviewLetter = l('View Full Letter', $urlPreviewLetter, array('attributes' => array('target' => '_blank')));
    $option['content'] = array(
      '#prefix' => '<div class="template ' . $type . '">',
      '#markup' => '<div class="page-hover">' . $linkPreviewLetter . '</div>'
                 . self::buildFirstPageContent($propertyNode->nid, $templateNode->nid),
      '#suffix' => '</div>',
    );

    return drupal_render($option);
  }

  /**
   * Given a property node, builds the address block.
   */
  static function buildAddressBlock($propertyNid) {
    $propertyOwnerAddress = _reiscout_property_get_owner_address_by_nid($propertyNid);
    $propertyOwnerName = _reiscout_property_get_owner_name_by_nid($propertyNid);
    $userAddress = _reiscout_property_get_user_address();

    $addressBlockContent = array(
      '#theme' => 'reiscout_mail_letter_address_block',
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

    return drupal_render($addressBlockContent);
  }

  /**
   * Extends the greeting token.
   *
   * Extends the greeting token to the corresponding greeting,
   * depending on the type of an owner.
   */
  static function extendGreetingToken($content, $propertyNid, $templateNid) {
    $tnw = entity_metadata_wrapper('node', $templateNid);

    if (_reiscout_property_is_owner_an_individual_by_nid($propertyNid)) {
      $greeting = $tnw->field_letter_tpl_greeting->value();
    }
    else {
      $greeting = $tnw->field_letter_tpl_greeting_co->value();
    }

    return str_replace('{{greeting}}', $greeting, $content);
  }

  /**
   * Builds content of the first page of a letter.
   *
   * Given a property node and a template node, builds content
   * of the first page of a letter.
   */
  static function buildFirstPageContent($propertyNid, $templateNid) {
    $tnw = entity_metadata_wrapper('node', $templateNid);

    $content = array(
      '#theme' => 'reiscout_mail_letter_content',
      '#address_block' => self::buildAddressBlock($propertyNid),
      '#page1' => self::extendGreetingToken($tnw->field_letter_tpl_page1->value()['safe_value'], $propertyNid, $templateNid),
    );
    $content = drupal_render($content);
    $content = ReiscoutMail::replaceTokens($content, $propertyNid);

    return ReiscoutMail::calculateFormulas($content, $propertyNid);
  }

  /**
   * Builds content of a letter preview.
   *
   * Given a property node and a template node, builds content
   * of a letter preview.
   */
  static function buildPreviewContent($propertyNid, $templateNid) {
    $tnw = entity_metadata_wrapper('node', $templateNid);

    $content = array(
      '#theme' => 'reiscout_mail_letter_content',
      '#is_preview' => true,
      '#address_block' => self::buildAddressBlock($propertyNid),
      '#page1' => self::extendGreetingToken($tnw->field_letter_tpl_page1->value()['safe_value'], $propertyNid, $templateNid),
      '#page2' => $tnw->field_letter_tpl_page2->value()['safe_value'],
      '#page3' => $tnw->field_letter_tpl_page3->value()['safe_value'],
    );
    $content = drupal_render($content);
    $content = ReiscoutMail::replaceTokens($content, $propertyNid);

    return ReiscoutMail::calculateFormulas($content, $propertyNid);
  }

  /**
   * Builds content of a letter.
   *
   * Given a property node and a template node, builds content of a letter.
   */
  static function buildContent($propertyNid, $templateNid) {
    $tnw = entity_metadata_wrapper('node', $templateNid);

    $content = array(
      '#theme' => 'reiscout_mail_letter_content',
      '#page1' => self::extendGreetingToken($tnw->field_letter_tpl_page1->value()['safe_value'], $propertyNid, $templateNid),
      '#page2' => $tnw->field_letter_tpl_page2->value()['safe_value'],
      '#page3' => $tnw->field_letter_tpl_page3->value()['safe_value'],
    );
    $content = drupal_render($content);
    $content = ReiscoutMail::replaceTokens($content, $propertyNid);

    return ReiscoutMail::calculateFormulas($content, $propertyNid);
  }

  /**
   * Wraps a letter content in the content of a letter template file.
   */
  static function wrapInTemplateFile($content, $templateNid) {
    $templateFileName = 'letter.html';
    $templateFilePath = drupal_get_path('module', 'reiscout_mail') . '/html_templates/letter/' . $templateFileName;

    if (!$templateFileContent = @file_get_contents($templateFilePath)) {
      $msg = t('!file_name file, that is used as the template for a letter, cannot be read.', array('!file_name' => $templateFileName));
      throw new ReiscoutMailTemplateFileIsNotReadable($msg);
    }

    return str_replace('{{content}}', $content, $templateFileContent);
  }

  /**
   * Builds HTML content of a letter preview.
   *
   * Given a property node and a template node, builds HTML content
   * of a letter preview.
   */
  static function buildPreviewHtml($propertyNid, $templateNid) {
    $content = self::buildPreviewContent($propertyNid, $templateNid);
    return self::wrapInTemplateFile($content, $templateNid);
  }

  /**
   * Builds HTML content of a letter.
   *
   * Given a property node and a template node, builds HTML content of a letter.
   */
  static function buildHtml($propertyNid, $templateNid) {
    $content = self::buildContent($propertyNid, $templateNid);
    return self::wrapInTemplateFile($content, $templateNid);
  }

  /*
   * Sends a letter to the owner of a property.
   */
  static function send($propertyNid, $templateNid) {
    $propertyOwnerAddress = _reiscout_property_get_owner_address_by_nid($propertyNid);
    $propertyOwnerName = _reiscout_property_get_owner_name_by_nid($propertyNid);
    $userAddress = _reiscout_property_get_user_address();

    $html = self::buildHtml($propertyNid, $templateNid);

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

      'color'             => false,
      'file'              => $html,
      'double_sided'      => false,
    );

    return lob_api_send_letter($data);
  }
}
