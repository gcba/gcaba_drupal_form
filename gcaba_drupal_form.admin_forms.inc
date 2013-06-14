<?php
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
	// JSON with Fields Nodes
	$type = "gcaba_form_field"; 

	// If not empty, user is addind a field
	if(!empty($form_state['input']['field_fields'])){
		$nodes = node_load_multiple(array(), array('type' => $type)); 
		$doit = false;
		foreach ($nodes as $key => $value) {
			if($value->title == $form_state['input']['field_fields'] ){ 
				$doit = true; 
			}

		}
		// If field is valid, add to SESSION
		if($doit == true && !in_array($value->title, $_SESSION['tmp_fields_list'])){
			if(!isset($_SESSION['tmp_fields_list'])){
				$_SESSION['tmp_fields_list'] = array();
			}
			array_push($_SESSION['tmp_fields_list'], $form_state['input']['field_fields']);
		}else{
			drupal_set_message(t('Field isn´t valid or it´s already added.'), 'error');
		}
		
	}

	if(!empty($_SESSION["tmp_fields_list"])){
		$table = "<table><tr><th>Field</th></tr>";
		foreach ($_SESSION["tmp_fields_list"] as $key => $value) {
			$table .= "<tr><td>".$value."</td></tr>";
		}
		$table .= "</table>";
	}


	// Form name
	$form['fields']['title'] = array(
		'#type' => 'textfield',
		'#required' => true,
		'#description' => t('Form name.'), 
		'#title' => t("Title"),
	);

	// Success text field
	$form['fields']['gcaba_form_success_text'] = array(
		'#type' => 'textfield',
		'#required' => false,
		'#description' => t('Text to show on success form. Blank for default text.'), 
		'#title' => "Success text",
	);

   
	$form['fields']['field_fields'] = array(
		'#type' => 'textfield',
        '#title' => t('Field'),
        '#size' => 30,
        '#maxlength' => 60,
        '#autocomplete_path' => 'fields/autocomplete',
        '#description' => t('Field type.'), 
    );	
    
    $form['fields']['add'] = array(
    	'#type' => 'button', 
    	'#value' => t('Add field'),
    	'#weight' => 19,
	);

	$form['fields']['fields_table'] = array(
		'#markup' => $table,
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


/**
 * Implementa hook_admin().
 *
 */

function gcaba_drupal_form_admin_fields(){
	$nodes = node_load_multiple(array(), array('type' => 'gcaba_form_field')); 
	$content = "<table><tr><th>Campos</th><th>Creator</th></tr>";
	foreach($nodes as $node){
		$content .= "<tr><td>".$node->title."</td><td>".$node->name."</td></tr>";
	}
	$content .= "</table>";

	$form['list'] = array(
		'#markup' => $content
	);

	$form['title'] = array(
		'#markup' => "<h1>Crear un nuevo campo</h1>"
	);

		
	$form['fields']['title'] = array(
		'#type' => 'textfield',
		'#required' => true,
		'#description' => t('nombre del field que desea agregar'), 
		'#title' => t("Nombre"),
	);

	$info = field_info_field('field_gcaba_form_field_type');
	$values = $info['settings']['allowed_values'];
	$form['selected'] = array(
       '#type' => 'select',
       '#title' => t('Tipo de dato'),
       '#options' => $values,
       '#description' => t('Seleccione el tipo de campo.'),
   );

	$info = field_info_field('field_gcaba_form_validators');
	$values = $info['settings']['allowed_values'];
	
	$form['validations'] = array(
  '#type' => 'checkboxes',
  '#options' => $values,
  '#title' => t('Qué validaciones te gustarian agregar?'),
    );

	$form['fields']['placeholder'] = array(
		'#type' => 'textfield',
		'#required' => false,
		'#description' => t('agregue el place holder del campo'), 
		'#title' => t("Place Holder"),
	);

	$form['fields']['label'] = array(
		'#type' => 'textfield',
		'#required' => false,
		'#description' => t('agregue el label del campo'), 
		'#title' => t("Label"),
	);

	$form['fields']['tip'] = array(
		'#type' => 'textfield',
		'#required' => false,
		'#description' => t('agregue una descripción del campo'), 
		'#title' => t("Descripcion"),
	);

	$form['fields']['initial_value'] = array(
		'#type' => 'textfield',
		'#required' => false,
		'#description' => t('agregue el valor por defecto del campo'), 
		'#title' => t("Valor por defecto"),
	);

	$form['buttons'] = array();
	$form['buttons']['#weight'] = 100;
	$form['buttons']['submit'] = array(
		'#type'  =>  'submit', 
		'#value'  =>  t('Agregar Campo')
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
	$node->revision = 0;
	$path = 'node_created_on' . date('YmdHis');
	$node->path = array('alias' => $path);
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
