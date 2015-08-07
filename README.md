# Islandora Drush Attach Datastream

## Introduction
This drush command attaches a datastream to a Fedora object.

## Requirements
This module requires the following modules/libraries:

* [Islandora](https://github.com/islandora/islandora)

## Use
`drush -u 1 islandora_attach_datastream_to_object --target_pid islandora:3456 --datastream_label OBJ --source_filepath /tmp/file.tif`

## Switches
* `--target_pid` - (Required) The PID of the target Fedora object.
* `--datastream_label` - (Required) The label (e.g. OBJ) for the datastream.
* `--source_filepath` - (Required) The file to attach.

## License
