<?php

/**
 * @file
 * Default theme implementation for a method example implementations bundle.
 *
 * Available variables:
 * - $language
 * - $examples
 */
?>
<!-- services-documentation-method-example-implementations-bundle -->
<div class="services-documentation-method-example-implementations-bundle">
  <h6 class="examples-language"><?php print $language; ?></h6>
  <?php foreach ($examples as $example): ?>
    <?php print render($example); ?>
  <?php endforeach; ?>
</div>
<!-- /services-documentation-method-example-implementations-bundle -->
