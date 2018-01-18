<?php
/**
 * @file
 * Admin forms.
 */
/**
 * Generates admin form.
 */
function islandora_dimensions_admin_form($form, &$form_state) {
  $badge_styles = array(
    "large_rectangle" => "large rectangle",
    "small_rectangle" => "small rectangle",
    "large_circle" => "large circle",
    "medium_circle" => "medium circle",
    "small_circle" => "small circle",
  );
  $form['islandora_dimensions_badge'] = array(
    '#type' => 'select',
    '#title' => t('Dimensions Badge'),
    '#options' => $badge_styles,
    '#description' => t('Name of the badge style to use when displaying the Dimensions.ai information.'),
    '#default_value' => variable_get('islandora_dimensions_badge', 'small_rectangle'),
  );
/*  $badge = !empty($form_state['values']['islandora_dimensions_badge']) ?
    $form_state['values']['islandora_dimensions_badge'] :
    variable_get('islandora_dimensions_badge', 'small_rectangle'); */
  return system_settings_form($form);
}
