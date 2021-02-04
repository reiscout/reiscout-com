<?php

/**
 * @file
 * Theme implementation to build content of an address block
 * that will be added to a template for a letter.
 *
 * Available variables:
 * - $to: property owner address;
 * - $from: user address.
 *
 * @see template_preprocess()
 * @see template_preprocess_reiscout_mail_letter_address_block()
 *
 * @ingroup themeable
 */
?>
<div id="return-address-window">
    <div id="return-address-text">
      <?php print $from['name'] ?><br />
      <?php print $from['thoroughfare'] . ($from['premise'] ? ' ' . $from['premise'] : '') ?><br />
      <?php print $from['city'] . ', ' . $from['state'] . ' ' . $from['zip'] ?>
    </div>
</div>

<div id="recipient-address-window">
    <div id="recipient-address-text">
      <?php print $to['name'] ?><br />
      <?php print $to['thoroughfare'] . ($to['premise'] ? ' ' . $to['premise'] : '') ?><br />
      <?php print $to['city'] . ', ' . $to['state'] . ' ' . $to['zip'] ?>
    </div>
</div>
