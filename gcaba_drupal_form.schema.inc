<?php

require_once drupal_get_path('module','gcaba_drupal_form').'/gcaba_drupal_form.fields.inc';

function gcaba_drupal_form_create_schema() {
	gcaba_drupal_form_create_content_types();
	gcaba_drupal_form_create_fields();
	gcaba_drupal_form_create_instances();
}

function gcaba_drupal_form_remove_schema() {
	gcaba_drupal_form_remove_instances();
	gcaba_drupal_form_remove_fields();
	gcaba_drupal_form_remove_content_types();
}

//CREATE =================================================
function gcaba_drupal_form_create_fields(){
	foreach (gcaba_drupal_form_get_fields_base() as $key => $value) {
    	field_create_field($value);
  	}
}

function gcaba_drupal_form_create_content_types(){
	foreach (gcaba_drupal_form_get_content_types() as $key => $value) {
		$value['type'] = $key;
		$form_type = node_type_set_defaults($value);
		node_type_save($form_type);
		node_add_body_field($form_type);
	}

}

function gcaba_drupal_form_create_instances(){
	foreach (gcaba_drupal_form_get_field_instances() as $key => $value) {
		//field_info_instance('node','');
		field_create_instance($value);
	}
}


//REMOVE =================================================
function gcaba_drupal_form_remove_content_types(){
	foreach (gcaba_drupal_form_get_content_types() as $key => $value) {
		node_type_delete($key);	
	}
}

function gcaba_drupal_form_remove_fields(){
	foreach (gcaba_drupal_form_get_fields_base() as $key => $value) {
    	field_delete_field($key);
  	}
}

function gcaba_drupal_form_remove_instances(){
	foreach (gcaba_drupal_form_get_field_instances() as $key => $value) {
		field_delete_instance($key);	
	}
}
?>