<?php
/**
 * @file
 * services-documentation-method.tpl.php
 *
 * Template file for theming the documentation for a given Services method.
 *
 * Available custom variables:
 * - $name:
 * - $path:
 * - $weight:
 * - $verb:
 * - $description:
 * - $request:
 * - $response:
 * - $example_implementation_bundles:
 * - $method: the method array defined in hook_services_resources().
 */
?>
<!-- services-documentation-method -->
<div class="resource-method">
  <?php if (!empty($path)): ?>
    <h4 class="method">
      <?php if (!empty($verb)): ?>
        <span class="method-verb"><?php print $verb; ?></span>
      <?php endif; ?>
      <span class="method-path"><?php print $path; ?></span>
    </h4>
  <?php elseif (!empty($name)): ?>
    <h4 class="method"><span class="method-name"><?php print $name; ?></span></h4>
  <?php endif; ?>

  <?php if ($description): ?>
    <p class="method-description"><?php print $description; ?></p>
  <?php endif; ?>

  <div class="method-arguments">
    <?php if ($method && !empty($method['args'])): ?>
      <h5 class="title">Arguments</h5>
      <ul>
        <?php foreach ($method['args'] as $argument): ?>
          <li class="method-argument">

            <div class="argument-title">
              <em class="argument-type"><?php print $argument['type']; ?></em>
              <strong class="argument-key"><?php (isset($argument['source']['param'])) ? print $argument['source']['param'] : print $argument['name']; ?></strong>

              <span class="argument-source">
                <?php print $argument['http_method'] ?>
              </span>
            </div>

            <div class="argument-description">
              <?php if ($argument['optional']): ?>
                (optional)
              <?php endif; ?>
              <?php print $argument['description']; ?>
            </div>

          </li>
        <?php endforeach; ?>
      </ul>
    <?php endif; ?>
  </div>

  <?php if ($request): ?>
    <div class="method-request">
      <h5 class="request-title">Request Example</h5>
      <pre class="request-body"><?php print $request; ?></pre>
    </div>
  <?php endif; ?>

  <?php if ($response): ?>
    <div class="method-response">
      <h5 class="response-title">Response Example</h5>
      <pre class="response-body"><?php print $response; ?></pre>
    </div>
  <?php endif; ?>

  <?php if ($example_implementations_bundles): ?>
    <div class="implementations">
    <h5 class="implementations-title">Implementation Examples</h5>
      <?php foreach ($example_implementations_bundles as $example_implementations_bundle): ?>
        <?php print render($example_implementations_bundle); ?>
      <?php endforeach; ?>
    </div>
  <?php endif; ?>

</div>
<!-- /services-documentation-method -->
