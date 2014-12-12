<?php

/**
 * @file
 * Default theme implementation for a method example implementation.
 *
 * Available variables:
 * - $name:
 * - $path:
 * - $type:
 * - $contents:
 * - $children
 */
?>
<!-- services-documentation-method-example-implementation -->
<div class="services-documentation-method-example-implementation-file">
  <?php if($type && $type == 'directory' && $children): ?>
  <li>
    <ul><div class="file-name"><em><?php print $name; ?></em></div>
      <div class="file-children"><?php print render($children); ?></div>
    </ul>
  </li>
  <?php elseif($type && $type == 'file' && $contents): ?>
  <li><div class="file-name"><em><?php print $name; ?></em></div>
    <pre class="file-contents"><?php print $contents; ?></pre>
  </li>
  <?php endif; ?>
</div>
<!-- /services-documentation-method-example-implementation -->
