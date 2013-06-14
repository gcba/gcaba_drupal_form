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
 * TERMINAR FORMULARIO
 */

function gcaba_drupal_form_admin_fields(){
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

return $form;

}

