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
	
	return $items;
}