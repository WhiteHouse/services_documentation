<?php
/**
 * @file
 * services_documentation.admin.inc
 * Provides the Services Documentation administrative interface.
 */

/**
 * Configuration settings for the Services Documentation module.
 */
function services_documentation_configure() {
  $form = array();

  // Designate documentation basepath.
  $form['services_documentation_base_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Set your documentation base path here'),
    '#default_value' => variable_get('services_documentation_base_path', ''),
    '#description' => 'If you enter "developers" here, your documentation will appear at /developers/1000, /developers/2000, /developers/3000. Your documentation homepage will be /developers. If you enter "documentation", your homepage will be /documentation, and your documentation will live here: /documentation/1000, /documentation/2000, etc.',
  );

  // Designate page to use for "homepage" (at basepath).
  $form['services_documentation_homepage'] = array(
    '#type' => 'textfield',
    '#title' => t('Services Documentation home page (base path above will point here)'),
    '#default_value' => variable_get('services_documentation_homepage', ''),
    '#description' => "Enter a valid Drupal path for your Services Documentation homepage. For example: node/1 or [services-documentation-base-path]/[recommended-api-version]. If you don't set anything, Services Documentation will simply present a list of links to different versions of documentation for each major API version.",
  );

  $form['services_documentation_intro'] = array(
    '#type' => 'textarea',
    '#title' => t('API Introduction'),
    '#default_value' => variable_get('services_documentation_intro'),
    '#description' => t('This text will be displayed at the top of each API version documentation page.'),
  );

  $form['services_documentation_toc'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display table of contents'),
    '#default_value' => variable_get('services_documentation_toc', TRUE),
    '#description' => t('If enabled, a table of contents will be displayed after the introduction of each API version documentation page.'),
  );

  $form['services_documentation_display_bundle_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display method bundle titles'),
    '#default_value' => variable_get('services_documentation_display_bundle_title', FALSE),
    '#description' => t('If enabled, method bundle titles will be displayed. E.g., operations, relationships, targeted actions, etc.'),
  );


  // Designate verbs to use.
  $form['services_documentation_verbs'] = array(
    '#type' => 'radios',
    '#title' => t('Services Documentation Verbs'),
    '#default_value' => variable_get('services_documentation_verbs', 'services'),
    '#options' => array(
      'services' => t('Services'),
      'http' => t('HTTP'),
      'crud' => t('CRUD'),
      'custom' => t('Custom'),
    ),
    '#description' => t('Select verbs used to describe operations.'),
  );

  // Designate custom verbs.
  $form['services_documentation_verbs_custom'] = array(
    '#type' => 'fieldset',
    '#title' => t('Services Documentation Custom Verbs'),
    '#description' => t('Select verbs used to describe operations.'),
    '#tree' => TRUE,
    '#states' => array(
      'visible' => array(
        ':input[name="services_documentation_verbs"]' => array('value' => 'custom'),
      ),
    ),
  );

  // Designate custom retrieve verb.
  $form['services_documentation_verbs_custom']['retrieve'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom Retrieve Verb'),
    '#default_value' => variable_get('services_documentation_verbs_custom_retrieve', t('retrieve')),
    '#description' => t('Select verbs used to describe operations.'),
  );

  // Designate custom create verb.
  $form['services_documentation_verbs_custom']['create'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom Create Verb'),
    '#default_value' => variable_get('services_documentation_verbs_custom_create', t('create')),
    '#description' => t('Select verbs used to describe operations.'),
  );

  // Designate custom update verb.
  $form['services_documentation_verbs_custom']['update'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom Update Verb'),
    '#default_value' => variable_get('services_documentation_verbs_custom_update', t('update')),
    '#description' => t('Select verbs used to describe operations.'),
  );

  // Designate custom delete verb.
  $form['services_documentation_verbs_custom']['delete'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom Delete Verb'),
    '#default_value' => variable_get('services_documentation_verbs_custom_delete', t('delete')),
    '#description' => t('Select verbs used to describe operations.'),
  );

  // Designate custom index verb.
  $form['services_documentation_verbs_custom']['index'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom Index Verb'),
    '#default_value' => variable_get('services_documentation_verbs_custom_index', t('index')),
    '#description' => t('Select verbs used to describe operations.'),
  );

  // Use custom submit handler, rather than system_settings_form.
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  $form['#submit'][] = 'services_documentation_config_submit';

  return $form;
}

/**
 * Submit handler for services_documentation_configure form.
 *
 * Check to see if values have changed for base_path and homepage alias.
 *
 * If they have, remove old path alias, save new values, and save new path
 * aliases.
 */
function services_documentation_config_submit($form, &$form_state) {
  $services_documentation_homepage = $form_state['values']['services_documentation_homepage'];
  $services_documentation_base_path = $form_state['values']['services_documentation_base_path'];

  // Determine if anything has changed.
  $old_base_path = variable_get('services_documentation_base_path', '');
  $old_homepage_alias = variable_get('services_documentation_homepage', '');
  $is_same_base_path = ($services_documentation_homepage == $old_homepage_alias) ? TRUE : FALSE;
  $is_same_homepage_alias = ($services_documentation_homepage == $old_homepage_alias) ? TRUE : FALSE;

  // Update stale or missing variables and path aliases.
  if (!$is_same_base_path || $is_same_homepage_alias) {

    // Delete the stale path alias.
    if ($path = path_load(array('alias' => $old_base_path))) {
      path_delete($path);
    }

    // Save new variables and path alias.
    variable_set('services_documentation_homepage', $services_documentation_homepage);
    variable_set('services_documentation_base_path', $services_documentation_base_path);
    $path = array(
      'source' => $services_documentation_homepage,
      'alias' => $services_documentation_base_path,
    );
    path_save($path);

    // Notify user.
    $text = t('Services Documentation\'s base path has been set to @base_path. This is like your documentation "home page". By default your home page points to Services Documentation\'s <a href="@versions">Versions</a> page. You can change this setting <a href="@config">here</a>', array(
      '@base_path' => $services_documentation_base_path,
      '@versions' => '/services-documentation/versions',
      '@config' => '/admin/config/services/documentation',
    ));
    drupal_set_message($text);
  }

  // Get verb-related values from form.
  $verbs = array(
    'services_documentation_verbs' => $form_state['values']['services_documentation_verbs'],
    'services_documentation_verbs_custom_retrieve' => $form_state['values']['services_documentation_verbs_custom']['retrieve'],
    'services_documentation_verbs_custom_update' => $form_state['values']['services_documentation_verbs_custom']['update'],
    'services_documentation_verbs_custom_delete' => $form_state['values']['services_documentation_verbs_custom']['delete'],
    'services_documentation_verbs_custom_index' => $form_state['values']['services_documentation_verbs_custom']['index'],
  );

  // Save updated verb-related variable values.
  foreach ($verbs as $variable => $value) {
    if ($value != variable_get($variable, '')) {
      variable_set($variable, $value);
    }
  }

  // Simple variable saves.
  variable_set('services_documentation_intro', $form_state['values']['services_documentation_intro']);
  variable_set('services_documentation_toc', $form_state['values']['services_documentation_toc']);
}
