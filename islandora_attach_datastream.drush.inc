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

/**
 * Implements hook_drush_command().
 */
function drush_islandora_attach_datastream_to_object() {
  $target_pid = drush_get_option('target_pid', NULL);
  $datastream_dsid = drush_get_option('datastream_dsid', NULL);
  $source_filepath = drush_get_option('source_filepath', NULL);
  $datastream_label = drush_get_option('datastream_label', NULL);
  $datastream_mimetype = drush_get_option(
    'datastream_label',
    file_get_mimetype($source_filepath)
  );

  $fedora_object = islandora_object_load($target_pid);

  // Is this a valid Fedora object?
  if (!$fedora_object) {
    drupal_set_message(
      dt(
        'Fedora PID @pid could not be found.',
        array(
          '@pid' => $target_pid,
        )
      ),
      'error'
    );
    return;
  }

  // Determine if DSID already exists, and set appropriate action.
  if (!isset($fedora_object[$datastream_dsid])) {
    $target_datastream = $fedora_object->constructDatastream($datastream_dsid, 'M');
    $datastream_action = 'Create';
  }
  else {
    $target_datastream = $fedora_object[$datastream_dsid];
    $datastream_action = 'Update';
  }

  $target_datastream->label = $datastream_label;
  $target_datastream->mimeType = $datastream_mimetype;
  $target_datastream->setContentFromFile($source_filepath, FALSE);

  // Ingest the datastream.
  if ($fedora_object->ingestDatastream($target_datastream)) {
    $success_string = 'successful';
    $success_message_type = 'info';
  }
  else {
     $success_string = 'unsuccessful';
     $success_message_type = 'error';
  };

  drupal_set_message(
    dt(
      '@datastream_action of @dsid on PID @pid was @success_string.',
      array(
        '@datastream_action' => $datastream_action,
        '@dsid' => $datastream_dsid,
        '@pid' => $target_pid,
        '@success_string' => $success_string,
      )
    ),
    $success_message_type
  );
}
