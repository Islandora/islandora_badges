<?php

/**
 * @file
 * Admin form functions for Islandora Altmetrics.
 */

/**
 * Theme function to create an admin table for identifier fields.
 *
 * @param array $variables
 *   Array containing form elements to be themed.
 *
 * @return string
 *   Rendered table.
 */
function theme_islandora_badges_admin_identifier_fields(array $variables) {

  $form = $variables['form'];

  $rows = array();
  foreach ($form['terms'] as $key => $element) {
    if (is_array($element) && element_child($key)) {
      $row = array();
      $row[] = array('data' => drupal_render($form['terms'][$key]['draggable_handler']), 'class' => 'islandora-badges-multiple-drag');
      $row[] = array('data' => drupal_render($form['terms'][$key]['name']));
      $row[] = array('data' => drupal_render($form['terms'][$key]['xpath']));
      $row[] = array('data' => drupal_render($form['terms'][$key]['weight']));

      $rows[] = array('data' => $row, 'class' => array('draggable'));
    }
  }

  // Create header array.
  $header = array();
  $header[] = array(
    'data' => t('Name'),
    'colspan' => 2,
    'clas' => 'islandora-badges-identifier-field-header',
  );
  $header[] = array('data' => t('XPath'));
  $header[] = array('data' => t('Weight'), 'class' => 'islandora-badges-identifier-field-weight');

  $output = '';
  $output .= theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array(
      'id' => 'islandora-badges-identifiers',
      'class' => array('islandora-badges-identifiers-table'),
    ),
  ));
  $output .= drupal_render_children($form);
  drupal_add_tabledrag('islandora-badges-identifiers', 'order', 'sibling', 'islandora-badges-identifiers-weight');
  return $output;
}

/**
 * Admin form for Islandora Badges.
 */
function islandora_badges_admin_form($form, $form_settings) {
  // Add admin form css.
  $form['#attached'] = array(
    'css' => array(
      drupal_get_path('module', 'islandora_badges') . '/css/islandora_badges.admin.css',
    ),
  );

  module_load_include('inc', 'islandora', 'includes/utilities');

  $all_cmodels = islandora_get_content_models();
  $already_chosen = variable_get('islandora_badges_selected_cmodels', array('ir:citationCModel', 'ir:thesisCModel'));
  $selected_rows = drupal_map_assoc($already_chosen);

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
      'weight' => variable_get('islandora_badges_uri_weight', 2)
    ),
  );
  // Sort by weight.
  uasort($identifiers, function($a, $b) {
    return $a['weight'] - $b['weight'];
  });

  $form['islandora_badges_identifier_table'] = array(
    '#title' => t('Identifier Fields'),
    '#type' => 'item',
    '#description' => t('MODS XPaths for retrieving identifier information. Set weights to change the order of identifiers to look for. DOI is first by default.'),
    '#tree' => TRUE,
    '#theme' => 'islandora_badges_admin_identifier_fields',
  );

  $terms = [];
  foreach ($identifiers as $name => $value) {
    $terms[$name] = array(
      'draggable_handler' => array(
        '#type' => 'item',
        '#markup' => '',
      ),
      'name' => array(
        '#type' => 'item',
        '#markup' => $name,
      ),
      'xpath' => array(
        '#type' => 'textfield',
        '#default_value' => $value['xpath'],
      ),
      'weight' => array(
        '#type' => 'weight',
        '#default_value' => $value['weight'],
        '#attributes' => array('class' => array('islandora-badges-identifiers-weight')),
      ),
    );
  }
  $form['islandora_badges_identifier_table']['terms'] = $terms;

  $form['content_model_wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configure which content models will display badges.'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['content_model_wrapper']['badges_table'] = array(
    '#type' => 'tableselect',
    '#title' => t('Enable custom pathauto settings for these content models'),
    '#tree' => TRUE,
    '#multiple' => TRUE,
    '#header' => array(
      'label' => array('data' => t('Content-Model')),
    ),
    '#default_value' => $selected_rows,
  );

  $options = array();
  foreach ($all_cmodels as $cmodel) {
    $pid = $cmodel['pid'];
    $label = $cmodel['label'];
    $options[$pid] = array('label' => array('data' => $label));
  }
  $form['content_model_wrapper']['badges_table']['#options'] = $options;

  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Configuration'),
    '#weight' => 0,
  );

  return $form;
}

/**
 * Drupal form validation handler.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 */
function islandora_badges_admin_form_validate(array $form, array &$form_state) {
  if (!array_keys(array_filter($form_state['values']['badges_table']))) {
    form_set_error(
      'badges_table',
      t("Please select at least one content-model to display the badges on.")
    );
  }
}

/**
 * Submit handler for admin form.
 */
function islandora_badges_admin_form_submit(array $form, array &$form_state) {
  $enabled = array_keys(array_filter($form_state['values']['badges_table']));
  variable_set('islandora_badges_selected_cmodels', $enabled);

  variable_set('islandora_badges_doi_xpath', $form_state['values']['islandora_badges_identifier_table']['terms']['doi']['xpath']);
  variable_set('islandora_badges_hdl_xpath', $form_state['values']['islandora_badges_identifier_table']['terms']['handle']['xpath']);
  variable_set('islandora_badges_uri_xpath', $form_state['values']['islandora_badges_identifier_table']['terms']['uri']['xpath']);
  variable_set('islandora_badges_doi_weight', $form_state['values']['islandora_badges_identifier_table']['terms']['doi']['weight']);
  variable_set('islandora_badges_hdl_weight', $form_state['values']['islandora_badges_identifier_table']['terms']['handle']['weight']);
  variable_set('islandora_badges_uri_weight', $form_state['values']['islandora_badges_identifier_table']['terms']['uri']['weight']);
  drupal_set_message(t("Configuration saved."));
}
