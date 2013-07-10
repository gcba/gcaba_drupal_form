<?php
/**
 * Implementa hook_menu().
 */

function gcaba_drupal_form_menu(){

    $items['fields/autocomplete'] = array(
        'title' => t('Fields s Autocompleter'),
        'page callback' => '_fields_autocomplete',
        'access callback' => true, //TODO: Verify access
        'type' => MENU_CALLBACK
    );
    
	$items['admin/config/gcaba_drupal_form'] = array(
        'title' => t('Manage forms'),
        'position' => 'left',
        'weight' => -10,
        'page callback' => 'system_admin_menu_block_page',
        'access arguments' => array('access administration pages'),
        'file path' => drupal_get_path('module', 'system'),
        'file' => 'system.admin.inc',
	);

	$items['admin/config/gcaba_drupal_form/administer'] = array(
    'access arguments' => array('administer site configuration'),
    'description' => t('Global forms configuration'),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gcaba_drupal_form_admin'),
    'title' => t('Forms configuration'),
    'weight' => 10,
  );
    $items['admin/config/gcaba_drupal_form/fields'] = array(
    'access arguments' => array('administer site configuration'),
    'description' => t('Add, modify and delete fields'),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gcaba_drupal_form_admin_fields'),
    'title' => t('Manage fields'),
    'weight' => 10,
  );
    $items['admin/config/gcaba_drupal_form/forms'] = array(
    'access arguments' => array('administer site configuration'),
    'description' => t('Add, modify and delete forms'),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gcaba_drupal_form_admin_forms'),
    'title' => t('Manage forms'),
    'weight' => 10,
  );

    $items['admin/config/gcaba_drupal_form/forms/add'] = array(
    'access arguments' => array('administer site configuration'),
    'description' => t('Add form'),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gcaba_drupal_form_admin_forms_add'),
    'title' => t('Add form'),
    'weight' => 10,
  );

	$items['admin/gcaba_drupal_form/drupal_gcaba_do'] = array(
    'access arguments' => array('administer site configuration'),
    'page callback' => 'gcaba_',
    'page arguments' => array(),
  );
return $items;
}

/**
 * Implementa hook_admin().
 */

function gcaba_drupal_form_admin(){
    $html = '<h2>'.t('No settings, yet').'</h2>';
    $form['fields']['fields_table'] = array(
        '#markup' => $html,
    );

    return $form;
}

/**
 * Implementa hook_admin().
 */

