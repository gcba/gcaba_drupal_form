<?php

/**
 * Implements hook_menu().
 */
function gcaba_drupal_form_menu() {
  // Forms wizzard
  $items['admin/structure/gcaba_forms/forms'] = array(
    'title'             => t('Forms'),
    'description'       => t('Manage forms from GCABA Forms'),
    'page callback'     => 'drupal_get_form',
    'page arguments'    => array('gcaba_drupal_form_forms'),
    'access arguments'  => array('administer site configuration'),
  );

  $items['admin/structure/gcaba_forms/forms/%gcaba_forms_forms/edit'] = array(
    'title' => 'Edit',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gcaba_drupal_form_forms', 4),
    'access arguments' => array('edit any gcaba_forms_fields entity'),
    'type' => MENU_LOCAL_TASK,
  );

  $items['admin/structure/gcaba_forms/forms/%gcaba_forms_forms/delete'] = array(
    'title' => 'Delete',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gcaba_drupal_form_form_delete', 4),
    'access arguments' => array('delete any gcaba_forms_forms entity'),
    'type' => MENU_LOCAL_TASK,
  );

 $items['gcabaforms/fields'] = array(
    'title' => 'GCABA Forms Field',
    'page callback' => 'gcaba_forms_fields_info_page',
    'access arguments' => array('view any gcaba_forms_fields entity'),
  );

  $items['admin/structure/gcaba_forms_fields/manage'] = array(
    'title' => 'GCABA Forms Field',
    'page callback' => 'gcaba_forms_fields_list_entities',
    'access arguments' => array('administer gcaba_forms_fields entities'),
  );

  $items['admin/structure/gcaba_forms_fields/manage/add'] = array(
    'title' => 'Add an GCABA Forms Field',
    'page callback' => 'gcaba_forms_fields_add',
    'access arguments' => array('create gcaba_forms_fields entities'),
    'type' => MENU_LOCAL_ACTION,
  );

  $items['admin/structure/gcaba_forms_fields/manage/list'] = array(
    'title' => 'List',
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  $items['gcabaforms/entities/fields/%gcaba_forms_fields'] = array(
    'title callback' => 'gcaba_forms_fields_title',
    'title arguments' => array(3),
    'page callback' => 'gcaba_forms_fields_view',
    'page arguments' => array(3),
    'access arguments' => array('view any gcaba_forms_fields entity'),
  );

  $items['gcabaforms/entities/fields/%gcaba_forms_fields/view'] = array(
    'title' => 'View',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10,
  );

  $items['gcabaforms/entities/fields/%gcaba_forms_fields/edit'] = array(
    'title' => 'Edit',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gcaba_forms_fields_form', 3),
    'access arguments' => array('edit any gcaba_forms_fields entity'),
    'type' => MENU_LOCAL_TASK,
  );

  $items['gcabaforms/entities/fields/add'] = array(
    'title' => 'Add an GCABA Forms Field Entity',
    'page callback' => 'gcaba_forms_fields_add',
    'access arguments' => array('create gcaba_forms_fields entities'),
  );

  $items['gcabaforms/forms'] = array(
    'title' => 'GCABA Forms Forms',
    'page callback' => 'gcaba_forms_forms_info_page',
    'access arguments' => array('view any gcaba_forms_forms entity'),
  );

  $items['admin/structure/gcaba_forms_forms/manage'] = array(
    'title' => 'GCABA Forms Forms',
    'page callback' => 'gcaba_forms_forms_list_entities',
    'access arguments' => array('administer gcaba_forms_forms entities'),
  );

  $items['admin/structure/gcaba_forms_forms/manage/add'] = array(
    'title' => 'Add an GCABA Forms Forms',
    'page callback' => 'gcaba_forms_forms_add',
    'access arguments' => array('create gcaba_forms_forms entities'),
    'type' => MENU_LOCAL_ACTION,
  );

  $items['admin/structure/gcaba_forms_forms/manage/list'] = array(
    'title' => 'List',
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  $items['gcabaforms/entities/forms/%gcaba_forms_forms'] = array(
    'title callback' => 'gcaba_forms_forms_title',
    'title arguments' => array(3),
    'page callback' => 'gcaba_forms_forms_view',
    'page arguments' => array(3),
    'access arguments' => array('view any gcaba_forms_forms entity'),
  );

  $items['gcabaforms/entities/forms/%gcaba_forms_forms/view'] = array(
    'title' => 'View',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10,
  );

  $items['gcabaforms/entities/forms/%gcaba_forms_forms/edit'] = array(
    'title' => 'Edit',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gcaba_forms_forms_form', 3),
    'access arguments' => array('edit any gcaba_forms_forms entity'),
    'type' => MENU_LOCAL_TASK,
  );

  $items['gcabaforms/entities/forms/add'] = array(
    'title' => 'Add an GCABA Forms Forms Entity',
    'page callback' => 'gcaba_forms_forms_add',
    'access arguments' => array('create gcaba_forms_forms entities'),
  );

  return $items;
}