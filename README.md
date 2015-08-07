# Islandora Drush Attach Datastream

## Introduction
This drush command attaches a datastream to a Fedora object.

## Requirements
This module requires the following modules/libraries:

* [Islandora](https://github.com/islandora/islandora)

## Use
`drush -u 1 islandora_attach_datastream_to_object --source_filepath /tmp/file.tif --target_pid islandora:3456 --datastream_dsid OBJ`

## Switches
* `--source_filepath` - (Required) A local filepath corresponding to the file to attach as the datastream.
* `--target_pid` - (Required) The PID of the Fedora object to attach the datastream.
* `--datastream_dsid` - (Required) The DSID (e.g. 'OBJ') to be applied to the datastream.
* `--datastream_label` - (Optional) The label (e.g. 'Web Surrogate JP2.') to be applied to the datastream. If unset, NULL will be used..
* `--datastream_mimetype` - (Optional) The mimetype (e.g. 'image/jp2') to be applied to the datastream. If not set, the value returned from file_get_mimetype() will be used.

## License
