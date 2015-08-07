<?php
/**
 * @file
 * Drush command : Attach a datastream to a fedora object.
 */

/**
 * Implements hook_drush_help().
 */
function registry_rebuild_drush_help($section) {
  switch ($section) {
    case 'drush:islandora_attach_datastream_to_object':
      return dt('Attaches a datastream via Islandora to a Fedora object.');
  }
}

/**
 * Implements hook_drush_command().
 */
function islandora_attach_datastream_command() {
  return array(
    'islandora_attach_datastream_to_object' => array(
      'bootstrap' => DRUSH_BOOTSTRAP_MAX,
      'options' => array(
        'target_pid' => array(
          'value' => 'required',
          'description' => dt('The PID of the target Fedora object.'),
        ),
        'datastream_label' => array(
          'value' => 'required',
          'description' => dt('The label (e.g. OBJ) for the datastream.'),
        ),
        'source_filepath' => array(
          'value' => 'required',
          'description' => dt('The file to attach.'),
        ),
      ),
      'drupal_dependencies' => array(
        'islandora',
      ),
      'description' => 'Attaches a datastream via Islandora to a Fedora object.',
      'examples' => array(
        'drush -u 1 islandora_attach_datastream_to_object --target_pid islandora:3456 --datastream_label OBJ --source_filepath /tmp/file.tif',
      ),
    ),
  );
}
