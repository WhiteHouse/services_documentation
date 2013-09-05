<?php
/**
 * @file
 * Provides various helper functions for services_documentation.
 */


/**
 * Generates an array of Services resources keyed by API version.
 */
function services_documentation_build_documentation($endpoint) {
  $documentation_resources = array();

  // Build menu items for Services resource documentation.
  if ($resources = services_get_resources($endpoint->name)) {
    // Cycle through resources. E.g., users, taxonomy_term, etc.
    foreach ($resources as $resource_name => $resource) {
      // Skip to next iteration if this resource is not enabled for endpoint.
      if (empty($resource['endpoint'])) {
        continue;
      }
      // Cycle through operation bundles. E.g., targeted_actions, actions, etc.
      foreach ($resource as $method_bundle_type => $method_bundle) {
        // Cycle through each operation in bundle. E.g., create, retrieve, etc.
        if (is_array($method_bundle)) {
          foreach ($method_bundle as $method_name => $method) {
            if (empty($resource['endpoint'][$method_bundle_type][$method_name]['enabled'])) {
              continue;
            }
            if (is_array($resource[$method_bundle_type][$method_name])) {
              // @todo make callback optional, add UI for specifying values.
              if (!empty($method['documentation callback'])) {
                $documentation_resources[$resource_name][$method_bundle_type][$method_name] = $method;
              }
            }
          }
        }
      }
    }
  }

  return $documentation_resources;
}


/**
 * Generate a renderable element for a services documentation method.
 */
function services_documentation_method_element($method) {
  // Call the documentation callback to generate the render element.
  if (!empty($method['documentation callback']) && function_exists(($method['documentation callback']))) {
    $documentation_callback = $method['documentation callback'];
    $element = call_user_func_array($documentation_callback, array());
  }
  else {
    // @todo build defaults from variables.
    $element = array(
      '#name' => $method['name'],
      '#path' => $method['endpoint']->path . '/' . $method['name'],
      '#weight' => 1,
      '#description' => '',
      '#request' => '',
      '#response' => '',
      '#auth' => !empty($method['endpoint']->authentication) ? TRUE : FALSE,
    );
  }

  // Specifying #type attaches #pre_render and #theme callbacks
  // via hook_element_info() implementation.
  $element['#type'] = 'services_documentation_method';
  $element['#method'] = isset($element['#method']) ? array_merge_recursive($method, (array) $element['#method']) : $method;

  return $element;
}

/**
 * Recursively scan the directory of an example implementation.
 */
function services_documentation_example_implementation_scan_recursively($directory) {
  $results = array();
  $current_directory = scandir($directory);

  // Remove "." and ".." from the array.
  if (in_array(".", $current_directory) && in_array("..", $current_directory)) {
    array_splice($current_directory, 0, 2);
  }

  // Construct the array that will be returned for output.
  foreach ($current_directory as $key => $value) {
    if (!in_array($value, array(".", ".."))) {
      $path = $directory . '/' . $value;
      $results[$value] = array();
      $results[$value]['#name'] = $value;
      $results[$value]['#path'] = $path;
      // Recursively scan directories.
      if (is_dir($path)) {
        $results[$value]['#type'] = 'directory';
        $results[$value]['#children'] = services_documentation_example_implementation_scan_recursively($path);
      }
      // Otherwise output code.
      else {
        $results[$value]['#type'] = 'file';
        $results[$value]['#contents'] = file_get_contents($path);
      }
      $results[$value]['#theme'] = 'services_documentation_implementation_file';
    }
  }

  return $results;
}

/**
 * Define method verbs.
 *
 * @param string $style
 *   The style of method verbs to use.
 *
 * @return array
 *   An array of method verbs values
 */
function services_documentation_verbs($style) {
  $verbs = array();

  switch ($style) {
    case 'services':
      $verbs = array(
        'retrieve' => 'retrieve',
        'create' => 'create',
        'update' => 'update',
        'delete' => 'delete',
        'index' => 'index',
      );
      break;

    case 'http':
      $verbs = array(
        'retrieve' => 'GET',
        'create' => 'POST',
        'update' => 'PUT',
        'delete' => 'DELETE',
        'index' => 'GET',
      );
      break;

    case 'crud':
      $verbs = array(
        'retrieve' => 'READ',
        'create' => 'CREATE',
        'update' => 'UPDATE',
        'delete' => 'DELETE',
        'index' => 'READ',
      );
      break;

    case 'custom':
      $verbs = array(
        'retrieve' => variable_get('services_documentation_verbs_custom_retrieve', 'retrieve'),
        'create' => variable_get('services_documentation_verbs_custom_create', 'create'),
        'update' => variable_get('services_documentation_verbs_custom_update', 'update'),
        'delete' => variable_get('services_documentation_verbs_custom_delete', 'delete'),
        'index' => variable_get('services_documentation_verbs_custom_index', 'index'),
      );
      break;
  }

  return $verbs;
}
