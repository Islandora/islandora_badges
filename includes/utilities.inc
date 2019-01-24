<?php

/**
 * @file
 * Utility functions.
 */

/**
 * Get and return an array of the identifier types.
 *
 * @return array
 *   An associative array of identifiers. Each element
 *   contains 'weight' and 'xpath' keys with the
 *   corresponding variables for that identifier.
 */
function islandora_badges_get_identifier_types() {
  $identifiers = array(
    'doi' => array(
      'xpath' => variable_get('islandora_badges_doi_xpath', '/mods:mods/mods:identifier[@type="doi"]'),
      'weight' => variable_get('islandora_badges_doi_weight', 0),
    ),
    'handle' => array(
      'xpath' => variable_get('islandora_badges_hdl_xpath', '/mods:mods/mods:identifier[@type="hdl"]'),
      'weight' => variable_get('islandora_badges_hdl_weight', 1),
    ),
    'uri' => array(
      'xpath' => variable_get('islandora_badges_uri_xpath', '/mods:mods/mods:identifier[@type="uri"]'),
      'weight' => variable_get('islandora_badges_uri_weight', 2),
    ),
  );
  // Sort by weight.
  uasort($identifiers, function ($a, $b) {
    return $a['weight'] - $b['weight'];
  });

  return $identifiers;
}

/**
 * Get the identifier value for the given object, identifier and xpath.
 *
 * @param \AbstractObject $object
 *   The Fedora object.
 * @param string $identifier_type
 *   The identifier type to find the value for. Corresponds to a key returned in
 *   islandora_badges_get_identifier_types().
 * @param string $identifier_xpath
 *   The xpath expression to query.
 *
 * @return string
 *   The value of the node or FALSE.
 */
function islandora_badges_get_identifier_value(AbstractObject $object, $identifier_type, $identifier_xpath) {
  $node_value = islandora_badges_get_xpath_node_value($object, $identifier_xpath);
  if ($node_value && $identifier_type == 'handle') {
    // Need to strip the handle URL bit.
    return str_replace('http://hdl.handle.net/', '', $node_value);
  }
  else {
    return $node_value;
  }
}

/**
 * Find the value in the MODS corresponding to the given xpath.
 *
 * @param \AbstractObject $object
 *   The Fedora object.
 * @param string $xpath
 *   The xpath expression to query.
 *
 * @return string
 *   The value of the node or FALSE.
 */
function islandora_badges_get_xpath_node_value(AbstractObject $object, $xpath) {
  if (!isset($object['MODS'])) {
    return FALSE;
  }
  $doc = new DOMDocument();
  $doc->loadXML($object['MODS']->content);
  $domxpath = new DOMXPath($doc);
  $domxpath->registerNamespace('mods', 'http://www.loc.gov/mods/v3');
  $xpath_results = $domxpath->query($xpath);
  if ($xpath_results->length == 0) {
    return FALSE;
  }
  $value = $xpath_results->item(0)->nodeValue;
  if (!$value) {
    return FALSE;
  }
  return $value;
}

/**
 * Find a DOI in the MODS record and return it.
 *
 * Prefer islandora_badges_get_identifier_value().
 * This is for backwards compatibility.
 *
 * @param \AbstractObject $object
 *   The Fedora object.
 *
 * @return string
 *   The DOI or FALSE
 */
function islandora_badges_get_doi(AbstractObject $object) {
  $doi_xpath = variable_get('islandora_badges_doi_xpath', '/mods:mods/mods:identifier[@type="doi"]');
  return islandora_badges_get_xpath_node_value($object, $doi_xpath);
}

/**
 * Determine if the object has a Content model we want to show badges on.
 *
 * @param \AbstractObject $object
 *   The object we are viewing.
 *
 * @return bool
 *   Whether $object has a content model to show badges for.
 */
function islandora_badges_show_for_cmodel(AbstractObject $object) {
  $show_cmodels = variable_get('islandora_badges_selected_cmodels', array('ir:citationCModel', 'ir:thesisCModel'));
  return (count(array_intersect($object->models, $show_cmodels)) > 0);
}
