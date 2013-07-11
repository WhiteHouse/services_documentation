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

  // Designate verbs to use.
  $form['services_documentation_verbs'] = array(
    '#type' => 'radios',
    '#title' => t('Services Documentation Verbs'),
    '#default_value' => variable_get('services_documentation_verbs', 'services'),
    '#options' => array(
      'services' => 'Services',
      'http' => 'HTTP',
      'crud' => 'CRUD',
      'custom' => 'Custom',
    ),
    '#description' => "Select verbs used to describe operations.",
  );

  // Designate custom verbs.
  $form['services_documentation_verbs_custom'] = array(
    '#type' => 'fieldset',
    '#title' => t('Services Documentation Custom Verbs'),
    '#description' => "Select verbs used to describe operations.",
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
    '#default_value' => variable_get('services_documentation_verbs_custom_retrieve', 'retrieve'),
    '#description' => "Select verbs used to describe operations.",
  );

  // Designate custom create verb.
  $form['services_documentation_verbs_custom']['create'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom Create Verb'),
    '#default_value' => variable_get('services_documentation_verbs_custom_create', 'create'),
    '#description' => "Select verbs used to describe operations.",
  );

  // Designate custom update verb.
  $form['services_documentation_verbs_custom']['update'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom Update Verb'),
    '#default_value' => variable_get('services_documentation_verbs_custom_update', 'update'),
    '#description' => "Select verbs used to describe operations.",
  );

  // Designate custom delete verb.
  $form['services_documentation_verbs_custom']['delete'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom Delete Verb'),
    '#default_value' => variable_get('services_documentation_verbs_custom_delete', 'delete'),
    '#description' => "Select verbs used to describe operations.",
  );

  // Designate custom index verb.
  $form['services_documentation_verbs_custom']['index'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom Index Verb'),
    '#default_value' => variable_get('services_documentation_verbs_custom_index', 'index'),
    '#description' => "Select verbs used to describe operations.",
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
 * Check to see if values have changed for base_path and homepage alias.
 *
 * If they have, remove old path alias, save new values, and save new path
 * aliases.
 *
 * Submit handler for services_documentation_configure form.
 */
function services_documentation_config_submit($form, &$form_state) {
  // Get values from form.
  $values = $form_state['values'];
  $services_documentation_homepage = $values['services_documentation_homepage'];
  $services_documentation_base_path = $values['services_documentation_base_path'];

  // Get verb-related values from form.
  $verbs = array(
    'services_documentation_verbs' => $values['services_documentation_verbs'],
    'services_documentation_verbs_custom_retrieve' => $values['services_documentation_verbs_custom']['retrieve'],
    'services_documentation_verbs_custom_create' => $values['services_documentation_verbs_custom']['create'],
    'services_documentation_verbs_custom_update' => $values['services_documentation_verbs_custom']['update'],
    'services_documentation_verbs_custom_delete' => $values['services_documentation_verbs_custom']['delete'],
    'services_documentation_verbs_custom_index' => $values['services_documentation_verbs_custom']['index'],
  );

  // Save updated verb-related variable values.
  foreach ($verbs as $variable => $value) {
    $old_var = variable_get($variable, '');
    $is_same_var = ($value == $old_var) ? TRUE : FALSE;
    if (!$is_same_var) {
      variable_set($variable, $value);
    }
  }

  // Save path-related variable values.
  services_documentation_save_settings($services_documentation_base_path,
                                       $services_documentation_homepage);
}
