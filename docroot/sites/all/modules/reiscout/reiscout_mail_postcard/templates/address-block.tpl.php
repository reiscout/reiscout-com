<?php

/**
 * @file
 * Theme implementation to build content of an address block
 * that will be added to a predefined template for a postcard.
 *
 * Available variables:
 * - $to: property owner address;
 * - $from: user address.
 *
 * @see template_preprocess()
 * @see template_preprocess_reiscout_mail_postcard_address_block()
 *
 * @ingroup themeable
 */
?>
<div id="ink-free">
  <div id="postage-indicia">
    POSTAGE INDICIA
  </div>
  <div id="user-address">
    <?php print $from['name'] ?><br />
    <?php print $from['thoroughfare'] . ($from['premise'] ? ' ' . $from['premise'] : '') ?><br />
    <?php print $from['city'] . ', ' . $from['state'] . ' ' . $from['zip'] ?>
  </div>
  <div id="owner-address">
    <?php print $to['name'] ?><br />
    <?php print $to['thoroughfare'] . ($to['premise'] ? ' ' . $to['premise'] : '') ?><br />
    <?php print $to['city'] . ', ' . $to['state'] . ' ' . $to['zip'] ?>
  </div>
</div>
