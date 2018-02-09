<?php

/*
 * @file
 * Definition of Events class.
 */

class Events {
  const TYPE_CREATED = 1;
  const TYPE_RENDERED_PDF = 2;
  const TYPE_RENDERED_THUMBNAILS = 3;
  const TYPE_IN_TRANSIT = 4;
  const TYPE_IN_LOCAL_AREA = 5;
  const TYPE_PROCESSED_FOR_DELIVERY = 6;
  const TYPE_RE_ROUTED = 7;
  const TYPE_RETURNED_TO_SENDER = 8;

  /**
   * Given the name of an event, returns its type.
   */
  private function getTypeByName($name) {
    $type = '';

    switch ($name) {
      case 'In Transit':
        $type = self::TYPE_IN_TRANSIT;
        break;
      case 'In Local Area':
        $type = self::TYPE_IN_LOCAL_AREA;
        break;
      case 'Processed for Delivery':
        $type = self::TYPE_PROCESSED_FOR_DELIVERY;
        break;
      case 'Re-routed':
        $type = self::TYPE_RE_ROUTED;
        break;
      case 'Returned to Sender':
        $type = self::TYPE_RETURNED_TO_SENDER;
        break;
    }

    return $type;
  }

  /**
   * Given the type of an event, returns its name.
   */
  public function getNameByType($type) {
    $name = '';

    switch ($type) {
      case self::TYPE_IN_TRANSIT:
        $name = 'In Transit';
        break;
      case self::TYPE_IN_LOCAL_AREA:
        $name = 'In Local Area';
        break;
      case self::TYPE_PROCESSED_FOR_DELIVERY:
        $name = 'Processed for Delivery';
        break;
      case self::TYPE_RE_ROUTED:
        $name = 'Re-routed';
        break;
      case self::TYPE_RETURNED_TO_SENDER:
        $name = 'Returned to Sender';
        break;
    }

    return $name;
  }

  /**
   * Given the type of an event, returns its description.
   */
  public function getDescByType($type) {
    $desc = '';

    switch ($type) {
      case self::TYPE_IN_TRANSIT:
        $desc = 'The mailpiece is being processed at the entry/origin facility';
        break;
      case self::TYPE_IN_LOCAL_AREA:
        $desc = 'The mailpiece is being processed at the destination facility';
        break;
      case self::TYPE_PROCESSED_FOR_DELIVERY:
        $desc = "The mailpiece has been greenlit for delivery at the recipient's nearest postal facility. The mailpiece should reach the mailbox within 1 to 2 business days of this scan event";
        break;
      case self::TYPE_RE_ROUTED:
        $desc = 'The mailpiece is re-routed due to recipient change of address, address errors, or USPS relabeling of barcode/ID tag area';
        break;
      case self::TYPE_RETURNED_TO_SENDER:
        $desc = 'The mailpiece is being returned to sender due to barcode, ID tag area, or address errors';
        break;
    }

    return $desc;
  }

  /**
   * Saves info about tracking event into DB.
   */
  public function log($postcardId, $info) {
    $fields = array(
      'pid' => $postcardId,
      'type' => $this->getTypeByName($info['name']),
      'location' => $info['location'],
      'time' => strtotime($info['time']),
    );
    db_merge('reiscout_mail_postcard_tracking_events')
      ->key(array('eid' => $info['id']))
      ->fields($fields)
      ->execute();
  }
}
