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
    '#default_value' => variable_get('services_documentation_base_path', 'developers'),
    '#description' => 'If you enter "developers" here, your documentation will appear at /developers/1000, /developers/2000, /developers/3000. Your documentation homepage will be /developers.',
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
  $services_documentation_base_path = $form_state['values']['services_documentation_base_path'];
  if (variable_get('services_documentation_base_path', 'developers') !=  $services_documentation_base_path) {
    variable_set('services_documentation_base_path', $services_documentation_base_path);
    drupal_set_message('You will need to clear menu caches before changes to the base path take effect.');
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
      variable_set($variable, check_plain($value));
    }
  }

  // Simple variable saves.
  variable_set('services_documentation_intro', $form_state['values']['services_documentation_intro']);
  variable_set('services_documentation_toc', $form_state['values']['services_documentation_toc']);
}
