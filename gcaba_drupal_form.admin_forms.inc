<?php

/*
	Add forms
*/
function gcaba_drupal_form_admin_forms_add(){
	$form['fields']['title'] = array(
		'#type' => 'textfield',
		'#required' => true,
		'#description' => t('Field name.'), 
		'#title' => t("Title"),
	);

	$form['fields']['gcaba_form_success_text'] = array(
		'#type' => 'textfield',
		'#required' => false,
		'#description' => t('Text to show on success form. Blank for default text.'), 
		'#title' => "Success text",
	);

	// Available types 
	$type = "gcaba_form_field"; 
	$nodes = node_load_multiple(array(), array('type' => $type)); 

	$avail_type = "<table style='width:30% !important;'><tr><th>Available types</th></tr>";
	foreach($nodes as $node){
		$avail_type .= "<tr><td>".$node->title."</td></tr>";
	}
	$avail_type .= "</table>";

	$form['avail_types'] = array( 
		'#title' => 'Field type', 
		'#description' => t('Select a field type.'), 
		'#type' => 'textfield', 
		'#required' => TRUE,
		'#ajax' => array(
			'event'=>'keyup',
 			'callback' =>'sandbox_ajax_dropdown_city',
			'wrapper' => 'city-wrapper',
		),
	);




	// Buttons
	$form['buttons'] = array();
	$form['buttons']['#weight'] = 100;
	$form['buttons']['submit'] = array(
		'#type'  =>  'submit', 
		'#value'  =>  t('Add form')
	);
    
    return $form;
}

/*
	Listado de formularios creados
*/
function gcaba_drupal_form_admin_forms(){
	// Forms Content Types 
	$type = "gcaba_form_form"; 
	$nodes = node_load_multiple(array(), array('type' => $type)); 

	$content = "<table><tr><th>Forms</th><th>Creator</th></tr>";
	foreach($nodes as $node){
		$content .= "<tr><td>".$node->title."</td><td>".$node->name."</td></tr>";
	}
	$content .= "</table>";

	// General attributes
	$form['#attributes']['enctype'] = 'multipart/form-data';
	$form['#id'] = 'form_list';

	$form['header'] = array(
		'#markup' => "<h2>Form list</h2>"
	);

	$form['list'] = array(
		'#markup' => $content
	);

	// Buttons
	$form['buttons'] = array();
	$form['buttons']['#weight'] = 100;
	$form['buttons']['submit'] = array(
		'#type'  =>  'submit', 
		'#value'  =>  t('Add form')
	);
    
    return $form;
}

function gcaba_drupal_form_admin_forms_submit($form_id, &$form_state) {
	// Add form
	$form_state['redirect'] = '/admin/config/gcaba_drupal_form/forms/add';
}