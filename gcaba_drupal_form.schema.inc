<?php

function gcaba_drupal_form_create_schema() {
	gcaba_drupal_form_create_fields();
	gcaba_drupal_form_create_content_types();
}


function gcaba_drupal_form_remove_schema() {
	gcaba_drupal_form_remove_fields();
	gcaba_drupal_form_remove_content_types();
}

function gcaba_drupal_form_create_fields(){
	//TODO
}

function gcaba_drupal_form_create_content_types(){

	$form_type = array(
	    'type' => 'GCABA_form',
	    'name' => st('GCABA Form'),
	    'base' => 'node_content',
	    'description' => st('Crear un nuevo cuestionario GCABA'),
	    'custom' => TRUE,
	    'modified' => TRUE,
	    'locked' => FALSE,
  	);

	$form_type = node_type_set_defaults($form_type);
	node_type_save($form_type);
	node_add_body_field($form_type);

}

function gcaba_drupal_form_remove_fields(){
	//TODO
}

function gcaba_drupal_form_remove_content_types(){
	node_type_delete('GCABA_form');	
}
?>