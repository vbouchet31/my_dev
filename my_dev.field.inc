<?php

/**
 * @file
 * Functions about fields.
 */

/**
 * Return the field bases without any related field instance.
 */
function _my_dev_get_orphan_field_base() {
  $orphans = array();
  foreach (field_info_fields() as $field_name => $field_info) {
    if (empty($field_info['bundles'])) {
      $orphans[$field_name] = $field_info;
    }
  };

  return $orphans;
}

/**
 * Page callback for admin/reports/fields.
 *
 * Add warning message for each orphan field base to the default field_ui page.
 *
 * @see field_ui_fields_list().
 */
function my_dev_field_ui_fields_list() {
  foreach (_my_dev_get_orphan_field_base() as $field_name => $field_info) {
    drupal_set_message(t('Field @field_name has only a field base without any field instance', array('@field_name' => $field_name)), 'warning');
  }

  module_load_include('inc', 'field_ui', 'field_ui.admin');
  return field_ui_fields_list();
}