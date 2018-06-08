<?php
/**
 * @file
 * Unpaywall badge admin options
 */

/**
 * Admin form: configure PDF link text.
 */
function islandora_unpaywall_admin_form($form, $form_settings) {
  $form['islandora_unpaywall_linktext'] = array(
    '#type' => 'textfield',
    '#title' => t('Link text'),
    '#description' => t('Text to use when generating external download link.'),
    '#default_value' => variable_get('islandora_unpaywall_linktext', 'Link to PDF'),
  );
  $form['islandora_unpaywall_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email address'),
    '#description' => t('Unpaywall API calls require an email address.'),
    '#default_value' => variable_get('islandora_unpaywall_email', 'email@example.com'),
  );
  $form['islandora_unpaywall_api_endpoint'] = array(
    '#type' => 'textfield',
    '#title' => t('Unpaywall API endpoint'),
    '#description' => t('Defaults to https://api.unpaywall.org/v2/. Do not change without good reason.'),
    '#default_value' => variable_get('islandora_unpaywall_api_endpoint', 'https://api.unpaywall.org/v2/'),
  );
  $email = variable_get('islandora_unpaywall_email', 'email@example.com');
  if ($email == 'email@example.com' || $email == '') {
    drupal_set_message(t('The Unpaywall API requires a valid email address.'), 'warning');
  }
  return system_settings_form($form);
}
