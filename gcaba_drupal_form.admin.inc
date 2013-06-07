<?php
<<<<<<< HEAD

function gcaba_drupal_form_menu(){
	$items['admin/config/gcaba_drupal_form'] = array(
    'title' => 'GCABA Administrador de Formularios ',
    'position' => 'left',
    'weight' => -10,
    'page callback' => 'system_admin_menu_block_page',
    'access arguments' => array('access administration pages'),
    'file path' => drupal_get_path('module', 'system'),
    'file' => 'system.admin.inc',
	);

	$items['admin/config/gcaba_drupal_/administer'] = array(
    'access arguments' => array('administer site configuration'),
    'description' => 'Administrar Formularios',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gcaba_drupal_forms_admin'),
    'title' => 'Administrar',
    'weight' => 10,
  );

	$items['admin/gcaba_forms/drupal_gcaba_do'] = array(
    'access arguments' => array('administer site configuration'),
    'page callback' => 'gcaba_',
    'page arguments' => array(),
  );
return $items;
}


function gcaba_shortcuts_admin(){

    $my_fields = field_info_instances("node", "shortcut");
    //dpm($my_fields);  
    $info = field_info_field('field_imagen_list');
    //dpm($info);

    $form['#attributes']['enctype'] = 'multipart/form-data';
    
    $form['image_name'] = array(
    '#type'  => 'textfield',
    '#title' => t('Nombre del shortcut'),
    '#size' => 30, 
    '#required' => TRUE,
    );
    
    $form['file_upload'] = array(
    '#title' => t('Subir imagen'),
    '#type'  => 'file',
    );
    $form['submit_upload'] = array(
    '#type'  =>  'submit', 
    '#value'  =>  'Submit'
    );
return $form;
=======
>>>>>>> 166ba995edfd82fa1af59a7cc9d052598f79a518
