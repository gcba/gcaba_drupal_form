<?php

function _add_field_to_form_callback(){
	if(!isset($_SESSION["tmp_fields_list"])){
	    $_SESSION["tmp_fields_list"] = array();
    }

	// Get form data
	list($form, $form_state) = ajax_get_form();

	if(!empty($form_state['input']['field_fields'])){
		// Validate field existance
		$type = "gcaba_form_field"; 
		$nodes = node_load_multiple(array(), array('type' => $type)); 
		$doit = false;
		foreach ($nodes as $key => $value) {
			if($value->title == $form_state['input']['field_fields'] ){ 
				$doit = true; 
			}
		}

		// Verify duplicated field
		if(in_array($form_state['input']['field_fields'], $_SESSION["tmp_fields_list"])){
			$doit = false;
		}

		// Add to SESSION if it´s validated
		if($doit == true){
			array_push($_SESSION["tmp_fields_list"], $form_state['input']['field_fields']);
		}
	}

	// Draw the field s table
	$table = "<table name='table_fields' id='table_fields'><tr><th>".t('Field')."</th></tr>";
	if(!empty($_SESSION["tmp_fields_list"])){
		foreach ($_SESSION["tmp_fields_list"] as $key => $value) {
			$table .= "<tr><td>".$value."</td></tr>";
		}
	}
	$table .= "</table>";

	return array(
		'#type' => 'ajax',
		'#commands' => array(
			ajax_command_replace('#table_fields', $table),
		)
	);
}


/**
 * Fields autocomplete helper
 * $string = string for search
 */
function _fields_autocomplete($string) {
	// JSON with Fields Nodes
	$type = "gcaba_form_field"; 
	$nodes = node_load_multiple(array(), array('type' => $type)); 
	$rta = array();

	foreach ($nodes as $key => $value) {
		if(!empty($string)){
			if(stripos($value->title, $string) !== false ){
				$rta[$value->title] = $value->title;
			}
		}else{
			$rta[$value->title] = $value->title;
		}
		
	}

	print drupal_json_output( $rta );
}

/*
	Add forms
*/
function gcaba_drupal_form_admin_forms_add($form, &$form_state){
	// TODO: Add text for submit button

	// Draw the field s table
	$table = "<table name='table_fields' id='table_fields'><tr><th>". t("Field")."</th></tr>";
	if(!empty($_SESSION["tmp_fields_list"])){
		
		foreach ($_SESSION["tmp_fields_list"] as $key => $value) {
			$table .= "<tr><td>".$value."</td></tr>";
		}
		
	}

	$table .= "</table>";
	
	// Form name
	$form['fields']['title'] = array(
		'#type' => 'textfield',
		'#required' => true,
		'#description' => t('Form name'), 
		'#title' => t("Title"),
	);

	$form['fields']['field_fields'] = array(
		'#type' => 'textfield',
        '#title' => t('Fields'),
        '#size' => 30,
        '#maxlength' => 60,
        '#autocomplete_path' => 'fields/autocomplete',
        '#description' => t('Form fields'), 
        '#default' => "",
    );	

	// Success text field
	$form['fields']['gcaba_form_success_text'] = array(
		'#type' => 'textfield',
		'#required' => false,
		'#description' => t('Text to show on success form. Blank for default text.'), 
		'#title' => "Success text",
	);

	// TODO: Validate list of emails
	$form['fields']['toemails'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Emails'),
	    '#required' => FALSE,
	    '#default_value' => "",
	    '#description' => "List all email receivers separated by a white space.",
	);

	// TODO: Validate API existance
	$form['fields']['toapi'] = array(
	    '#type' => 'textfield',
	    '#title' => t('URL API List'),
	    '#required' => FALSE,
	    '#default_value' => "",
	    '#description' => "API list URL where save results.",
	);
    
    $form['fields']['add'] = array(
    	'#type' => 'button', 
    	'#value' => t('Add field'),
    	'#weight' => 19,
    	'#ajax' => array(
			'callback' => '_add_field_to_form_callback',
			'wrapper' => 'fields_table',
			'effect' => 'fade',
     	),
	);

	$form['fields']['fields_table'] = array(
		'#markup' => $table,
	);


    $form['fields']['submit'] = array(
    	'#type' => 'submit', 
    	'#value' => t('Create form'),
    	'#weight' => 19,
	);
    return $form;
}

/*
	Add forms validate
*/
function gcaba_drupal_form_admin_forms_add_validate($form, &$form_state){ 
	
	// Verify that forms name is available
	$type_form = "gcaba_form_form"; 
	$nodes_form = node_load_multiple(array(), array('type' => $type_form));
	$doit = true;
	foreach ($nodes_form as $key => $value) {
		if($value->title == $form_state['input']['title'] ){ 
			form_set_error($name = "title", $message = t('Title is already taken.'));
		}
	}

	// Verify that fields were added to form
	if($_SESSION['tmp_fields_list'] == null || $_SESSION['tmp_fields_list'] == array()){
		form_set_error($name = "field_fields", $message = t('There are no fields added'));
	}
}

/*
	Add forms validate
*/
function gcaba_drupal_form_admin_forms_add_submit($form, &$form_state){
	// Create node object.
	$node = new StdClass();
	$node->type = 'gcaba_form_form';
	$node->language = LANGUAGE_NONE;
	node_object_prepare($node);
	$node->title = $form_state['input']['title'];
	node_save($node);
	
	// Clean SESSION
	$_SESSION['tmp_fields_list'] = array();

	// Redirect to list
	$form_state['redirect'] = '/admin/config/gcaba_drupal_form/forms/';
}

/*
	Listado de formularios creados
*/
function gcaba_drupal_form_admin_forms(){
	// Forms Content Types 
	$type = "gcaba_form_form"; 
	$nodes = node_load_multiple(array(), array('type' => $type)); 

	$content = "<table><tr><th>".t("Forms")."</th><th>".t("Creator")."</th></tr>";
	foreach($nodes as $node){
		$content .= "<tr><td>".$node->title."</td><td>".$node->name."</td></tr>";
	}
	$content .= "</table>";

	// General attributes
	$form['#attributes']['enctype'] = 'multipart/form-data';
	$form['#id'] = 'form_list';

	$form['header'] = array(
		'#markup' => "<h2>".t("Form list")."</h2>"
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


/**
 * Implementa hook_admin().
 *
 */

function gcaba_drupal_form_admin_fields(){
	$nodes = node_load_multiple(array(), array('type' => 'gcaba_form_field')); 
	$content = "<table><tr><th>".t("Fields")."</th><th>".t("Creator")."</th></tr>";
	foreach($nodes as $node){
		$content .= "<tr><td>".$node->title."</td><td>".$node->name."</td></tr>";
	}
	$content .= "</table>";

	$form['list'] = array(
		'#markup' => $content
	);

	$form['title'] = array(
		'#markup' => "<h1>".t("Add field")."</h1>"
	);

		
	$form['fields']['title'] = array(
		'#type' => 'textfield',
		'#required' => true,
		'#description' => t('Field name'), 
		'#title' => t("Field name"),
	);

	$info = field_info_field('field_gcaba_form_field_type');
	$values = $info['settings']['allowed_values'];

	// Avoid SUBMIT type
	$key = array_search("SUBMIT",$values);
	if($key!==false){
	    unset($values[$key]);
	}

	$form['selected'] = array(
       '#type' => 'select',
       '#title' => t('Data type'),
       '#options' => $values,
       '#description' => t('Select data type'),
   );

	$info = field_info_field('field_gcaba_form_validators');
	$values = $info['settings']['allowed_values'];
	
	$form['validations'] = array(
  		'#type' => 'checkboxes',
  		'#options' => $values,
  		'#title' => t('Add some validations'),
    );

	$form['fields']['placeholder'] = array(
		'#type' => 'textfield',
		'#required' => false,
		'#description' => t('Field placeholder'), 
		'#title' => t("Field placeholder"),
	);

	$form['fields']['label'] = array(
		'#type' => 'textfield',
		'#required' => false,
		'#description' => t('Field label'), 
		'#title' => t("Field label"),
	);

	$form['fields']['tip'] = array(
		'#type' => 'textfield',
		'#required' => false,
		'#description' => t('Field description'), 
		'#title' => t("Field description"),
	);

	$form['fields']['initial_value'] = array(
		'#type' => 'textfield',
		'#required' => false,
		'#description' => t('Field default value'), 
		'#title' => t("Field default value"),
	);

	$form['fields']['options'] = array(
		'#type' => 'textarea',
		'#required' => false,
		'#description' => t('Field options. Noy valid for all types.'), 
		'#title' => t("Field options"),
	);

	$form['buttons'] = array();
	$form['buttons']['#weight'] = 100;
	$form['buttons']['submit'] = array(
		'#type'  =>  'submit', 
		'#value'  =>  t('Add field')
	);

	return $form;
}


function gcaba_drupal_form_admin_fields_submit($form_id, &$form_state) {
	__save_field_node($form_state);
	$form_state['redirect'] = '/admin/config/gcaba_drupal_form/fields';
}

function __save_field_node($data){
	$node = new stdClass();
    $node->type = 'gcaba_form_field';
    $node->language = LANGUAGE_NONE;
    $node->status = 0;
	$node->title = $data['values']['title'];
	$node->field_gcaba_form_field_type[$node->language][0]['value'] = $data['values']['selected'];
	__checkbox_format($node, $data['values']['validations']);
	$node->field_gcaba_form_placeholder[$node->language][0]['value'] = $data['values']['placeholder'];
	$node->field_gcaba_form_label[$node->language][0]['value'] = $data['values']['label'];
	$node->field_gcaba_form_help[$node->language][0]['value'] = $data['values']['tip'];
	$node->field_gcaba_form_initial_value[$node->language][0]['value'] = $data['values']['initial_value'];
	$node->field_field_gcaba_form_options[$node->language][0]['value'] = $data['values']['options'];
	$node->revision = 0;
	$path = 'node_created_on' . date('YmdHis');
	$node->path = array('alias' => $path);
	node_object_prepare($node);
	if($node = node_submit($node)) { 
    	node_save($node);
	}

}

function __checkbox_format($node, $data){
	$i=0;
	foreach($data as $key => $value){
		if($key == $value){
			$node->field_gcaba_form_validators[$node->language][$i]['value'] = $value;
			$i++;
		}
	}
}
