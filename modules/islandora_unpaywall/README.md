# Islandora Unpaywall

## Introduction

Islandora Unpaywall provides block containing a link to an open-access version of a citation-only object. It uses the API from unpaywall.org. 

The badge will only display on objects with a MODS datastream and a DOI (Digital Object Identifier).

## Requirements

This module requires the following modules/libraries:

* [Islandora](https://github.com/islandora/islandora)
* [Islandora Badges](../../)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration

Configuration path is admin/islandora/tools/badges/unpaywall (Administration > Islandora > Islandora Utility Modules > Islandora Badges Configuration > Unpaywall).

* Link text: Defines the text used in the PDF link. Defaults to "Link to PDF".
* Email: The Unpaywall API now requires an email address appended to every call.
* API endpoint: The correct, current one is given by default. This is done in case the endpoint changes in the future.

## Styling
The link text is enclosed in a block with the class "unpaywall". This can be styled with CSS.

## Troubleshooting/Issues

Having problems or solved a problem? Check out the Islandora google groups for a solution.

* [Islandora Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora)
* [Islandora Dev Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora-dev)

## Maintainers/Sponsors

Current maintainers:

* [Brandon Weigel](https://github.com/bondjimbond)

## Development

If you would like to contribute to this module, please check out [CONTRIBUTING.md](CONTRIBUTING.md). In addition, we have helpful [Documentation for Developers](https://github.com/Islandora/islandora/wiki#wiki-documentation-for-developers) info, as well as our [Developers](http://islandora.ca/developers) section on the [Islandora.ca](http://islandora.ca) site.

## License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
