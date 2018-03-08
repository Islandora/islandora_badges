<?php

/**
 * @file
 * Admin forms.
 */

/**
 * Admin form for API key.
 */
function islandora_scopus_admin_form($form, &$form_state) {
  $form['islandora_scopus_api_endpoint'] = array(
    '#type' => 'textfield',
    '#title' => t('Scopus API Endpoint'),
    '#description' => t('Scopus query URL. Currently https://api.elsevier.com/content/abstract/citation-count.
    Only change this if Elsevier notifies you that it has changed.'),
    '#default_value' => variable_get('islandora_scopus_api_endpoint', 'https://api.elsevier.com/content/abstract/citation-count'),
  );
  $form['islandora_scopus_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Scopus API Key'),
    '#description' => t(
      'Scopus Badges are disabled if this field is blank. You need to get your own key from <a href="@url" target="_new">Elsevier</a>.',
      array('@url' => 'https://dev.elsevier.com/apikey/create')
    ),
    '#default_value' => variable_get('islandora_scopus_api_key', ''),
  );

  return system_settings_form($form);
}
