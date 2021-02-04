<?php

/**
 * @file
 * Theme implementation to build the content of a letter.
 *
 * Available variables:
 * - $address_block: block with addresses;
 * - $page1: content of the first page;
 * - $page2: content of the second page;
 * - $page3: content of the third page.
 *
 * @see template_preprocess()
 *
 * @ingroup themeable
 */
?>
<?php if ($is_preview): ?>
<div id="preview">
<?php endif; ?>
<div class="page">
    <?php if ($address_block): ?>
      <?php print $address_block ?>
    <?php endif; ?>
    <div class="safe-zone">
      <?php print $page1 ?>
    </div>
</div>
<?php if ($page2): ?>
<div class="page">
    <div class="safe-zone">
      <?php print $page2 ?>
    </div>
</div>
<?php endif; ?>
<?php if ($page3): ?>
<div class="page">
    <div class="safe-zone">
      <?php print $page3 ?>
    </div>
</div>
<?php endif; ?>
<?php if ($is_preview): ?>
</div>
<?php endif; ?>
