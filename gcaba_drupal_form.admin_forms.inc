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
