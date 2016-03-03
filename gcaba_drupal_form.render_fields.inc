<?php

function gcaba_drupal_form_render_field_text($field, $form) {

	$form['gcaba_drupal_form_render_field_text_'.$field['id'] ] = array(
		'#title' => $field['title'],
		'#type' => 'textfield',
		'#description' => $field['help'],
		'#value'  => "",
		'#attributes' => array(
			'data-id' => $field['id'],
			'class' => array('gcaba_drupal_form_render_field_text', "button-form-custom"),
			'placeholder'=> array($field['placeholder']),
			'miba_id'=> array($field['openIDname'])
		),
	);

	return $form;
}

function gcaba_drupal_form_render_field_select($field, $form) {
	$form['gcaba_drupal_form_render_field_select_'.$field['id'] ] = array(
		'#title' => $field['title'],
		'#type' => 'select',
		'#description' => $field['help'],
		'#options' => $field['options'],
		'#attributes' => array(
			'data-id' => $field['id'],
			'class' => array('gcaba_drupal_form_render_field_select')
		),
	);
	return $form;
}

function gcaba_drupal_form_render_field_textarea($field,$form) {
	$form['gcaba_drupal_form_render_field_textarea'.$field['id'] ] = array(
		'#title' => $field['title'],
		'#type' => 'textarea',
		'#description' => $field['help'],
		'#value'  => "",
		'#attributes' => array(
			'data-id' => $field['id'],
			'class' => array('gcaba_drupal_form_render_field_textarea'),
//			'placeholder'=> array($field['placeholder'])
		),
	);

	return $form;
}

function gcaba_drupal_form_render_field_radio($field,$form) {
	$form['gcaba_drupal_form_render_field_radio'.$field['id'] ] = array(
		'#title' => $field['title'],
		'#type' => 'radios',
//		'#value'  => $field['placeholder'],
		'#description' => $field['help'],
		'#options' => $field['options'],
		'#attributes' => array(
			'data-id' => $field['id'],
			'class' => array('gcaba_drupal_form_render_field_radio')
		),
	);

	return $form;
}

function gcaba_drupal_form_render_field_checkbox($field,$form) {
	$form['gcaba_drupal_form_render_field_checkbox'.$field['id'] ] = array(
		'#title' => $field['title'],
		'#type' => 'checkboxes',
		'#description' => $field['help'],
		'#options' => $field['options'],
		'#attributes' => array(
			'data-id' => $field['id'],
			'class' => array('gcaba_drupal_form_render_field_checkbox')
		),
	);

	return $form;
}

function gcaba_drupal_form_render_field_recaptcha($field,$form) {
	$form['gcaba_drupal_form_render_field_recaptcha'.$field['id'] ] = array(
		'#title' => $field['title'],
		'#type' => 'radio',
//		'#value'  => $field['placeholder'],
		'#attributes' => array(
			'data-id' => $field['id'],
			'class' => array('gcaba_drupal_form_render_field_recaptcha'),
			'onfocus' => array('if(this.value == "'.$field['placeholder'].'") { this.value = ""; }'),
			'onblur' => array('if(this.value == "") { this.value = "'.$field['placeholder'].'"; }')
		),
	);

	return $form;
}

function gcaba_drupal_form_render_field_select_chosen($field, $form) {
	$form['gcaba_drupal_form_render_field_select_'.$field['id'] ] = array(
		'#title' => $field['title'],
		'#type' => 'select',
		//'#description' => $field['help'],
		'#options' => $field['options'],
		'#chosen' => TRUE,
		'#attributes' => array(
			'data-id' => $field['id'],
			'class' => array('gcaba_drupal_form_render_field_select'),
			'data-placeholder' => "Esto es un simple test",
		),
	);
	return $form;
}

function gcaba_drupal_form_render_field_file($field, $form) {
	$form['gcaba_drupal_form_render_field_file_'.$field['id'] ] = array(
		'#title' => $field['title'],
		'#type' => 'file',
		'#description' => $field['help'],
		'#attributes' => array(
			'data-id' => $field['id'],
			'class' => array('gcaba_drupal_form_render_field_text', "button-form-custom"),
		),
	);

	return $form;
}

function gcaba_drupal_form_render_field_title($field, $form) {
	$form['gcaba_drupal_form_render_field_title_'.$field['id']] = array(
		'#markup' => $field['title'],
		'#prefix' => '<h3>',
		'#suffix' => '</h3>'
		);

	return $form;
}

function gcaba_drupal_form_render_field_selecttomail($field,$form) {
	$form['gcaba_drupal_form_render_field_selecttomail'.$field['id'] ] = array(
		'#title' => $field['title'],
		'#type' => 'select',
		'#description' => $field['help'],
		'#options' => $field['options'],
		'#attributes' => array(
			'data-id' => $field['id'],
			'class' => array('gcaba_drupal_form_render_field_selecttomail')
		),
	);

	return $form;
}