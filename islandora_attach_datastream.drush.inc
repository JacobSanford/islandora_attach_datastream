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
        'source_filepath' => array(
          'value' => 'required',
          'description' => dt('A local filepath corresponding to the file to attach as the datastream.'),
        ),
        'target_pid' => array(
          'value' => 'required',
          'description' => dt('The PID of the Fedora object to attach the datastream.'),
        ),
        'datastream_dsid' => array(
          'value' => 'required',
          'description' => dt('The DSID (e.g. \'OBJ\') to be applied to the datastream.'),
        ),
        'datastream_label' => array(
          'value' => 'optional',
          'description' => dt('The label (e.g. \'Web Surrogate JP2.\') to be applied to the datastream. If unset, NULL will be used.'),
        ),
        'datastream_mimetype' => array(
          'value' => 'optional',
          'description' => dt('The mimetype (e.g. \'image/jp2\') to be applied to the datastream. If not set, the value returned from file_get_mimetype() will be used.'),
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
