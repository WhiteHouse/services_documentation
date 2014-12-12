<?php

/**
 * @file
 * Default theme implementation for the documentation versions overview.
 *
 * Available custom variables:
 * - $versions: A list of links to documentation pages for each version.
 */
?>
<!-- services-documentation-versions template -->
<div id="services-documentation-versions">
  <h2>API Versions</h2>
  <?php print render($versions); ?>
</div>
<!-- /services-documentation-versions template -->
