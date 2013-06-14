<?php
function _cities_autocompletes(){
    print "hello";
}

/*
	Add forms
*/

/**
 * autocomplete helper
 * $string = string for search
 */
function _fields_autocomplete($string) {
	// Fields Content Types 
	$type = "gcaba_form_field"; 
	$nodes = node_load_multiple(array(), array('type' => $type)); 

	print drupal_json_output($nodes);
}

function gcaba_drupal_form_admin_forms_add(){
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

	$form['fields']['author'] = array(
		'#type' => 'textfield',
        '#title' => t('Authored by'),
        '#size' => 30,
        '#maxlength' => 60,
        '#autocomplete_path' => 'fields/autocomplete',
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

