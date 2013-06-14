<?php
/*
	Add forms
*/
function gcaba_drupal_form_admin_forms_add(){
	// Form name
	$form['fields']['title'] = array(
		'#type' => 'textfield',
		'#required' => true,
		'#description' => t('Field name.'), 
		'#title' => t("Title"),
	);

	// Success text field
	$form['fields']['gcaba_form_success_text'] = array(
		'#type' => 'textfield',
		'#required' => false,
		'#description' => t('Text to show on success form. Blank for default text.'), 
		'#title' => "Success text",
	);

	$form['fields']['author'] = array(
		'#type' => 'textfield',
        '#title' => t('Authored by'),
        '#size' => 30,
        '#maxlength' => 60,
        '#autocomplete_path' => 'user/autocomplete',
        '#default_value' => $author,
        '#weight' => -1,
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
	if($node = node_submit($node)) { // Prepare node for saving
    node_save($node);
    //echo "Node with nid " . $node->nid . " saved!\n";
    //print_r($node);
	//die();
	}

}

function __checkbox_format($node, $data){
	//print_r($data);
	//die();
	$i=0;
	foreach($data as $key => $value){
		if($key == $value){
			$node->field_gcaba_form_validators[$node->language][$i]['value'] = $value;
			$i++;
		}
	}
}