# Islandora Handled Datastream Access

## Introduction

Islandora handled datastream access allows view access to datastreams via the handle of the object.

### Usage

This module adds the following URLs:

* /islandora/handled_access/_handle_/_what_/view
  With this URL a specific datastream can be viewed by using the handle, for example /islandora/handled_access/1887/12345/JPG/view
  will view the JPG datastream of the Islandora item with handle 1887/12345.
  If the TN datastream (thumbnail) is accessed and the islandora_imagecache is installed, the cached thumbnail will be used.
  As a special case, the _what_ can be ```image```: an JP2, JPG or MEDIUM_SIZE datastream (in that order) is then used if
  it exists, has an image mimetype (image/png, image/jpeg or image/jp2) and is accessible.
  Also, _what_ can be ```document``` and then a document (PDF) or image or binary is returned.
  Also, _what_ can be ```thumbnail``` and then the TN datastream is returned.
* /islandora/handled_access/_handle_/_what_/access
  This URL returns a JSON response that indicates if an item and datastream can be found based on the handle and if access is
  allowed. The special cases _what_ are also possible.
* /access/_handle_/view
  This does the same as /islandora/handled_access/_handle_/_what_/view for _what_ = ```document```
* /access/_handle_/access
  This does the same as /islandora/handled_access/_handle_/_what_/access for _what_ = ```document```
* /access/_handle_/download
  This does the same as /islandora/handled_access/_handle_/_what_/view for _what_ = ```document``` but downloads the document
* /access/_handle_/thumbnail
  This does the same as /islandora/handled_access/_handle_/_what_/view for _what_ = ```thumbnail```
* /access/_PID_/view
  Same as /access/_handle_/view but with a PID of an object.
* /access/_PID_/access
  Same as /access/_handle_/access but with a PID of an object.
* /access/_PID_/download
  Same as /access/_handle_/download but with a PID of an object.
* /access/_PID_/thumbnail
  Same as /access/_handle_/thumbnail but with a PID of an object.

## Requirements

This module requires the following modules/libraries:

* [Islandora](https://github.com/islandora/islandora)
* [Islandora handle](https://github.com/discoverygarden/islandora_handle)

This module uses the following modules/libraries if they are installed:

* [Islandora image cache](https://github.com/discoverygarden/islandora_imagecache)
* [curl](https://github.com/curl) (is used when islandora_imagecache is installed, but by default installed with islandora)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Maintainers/Sponsors

Current maintainers:

* [Lucas van Schaik](https://github.com/lucasvanschaik)

## Development

If you would like to contribute to this module, please contact the current maintainer.


## License

[GPLv3](LICENSE.txt)
Copyright 2019-2020 Leiden University Library

