<?php

function gcaba_drupal_form_render_field_text($field, $form) {
  $form['gcaba_drupal_form_render_field_text_'.$field['id'] ] = array(
    '#title' => $field['title'],
    '#type' => 'textfield',
    '#value'  => "",
    '#attributes' => array(
      'data-id' => $field['id'],
      'class' => array('gcaba_drupal_form_render_field_text')
      //'onfocus' => array('if(this.value == "'.$field['placeholder'].'") { this.value = ""; }'),
      //'onblur' => array('if(this.value == "") { this.value = "'.$field['placeholder'].'"; }')
    ),
  );

  return $form;
}

function gcaba_drupal_form_render_field_select($field, $form) {
  $form['gcaba_drupal_form_render_field_select_'.$field['id'] ] = array(
    '#title' => $field['title'],
    '#type' => 'select',
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
    '#value'  => "",
    '#attributes' => array(
      'data-id' => $field['id'],
      'class' => array('gcaba_drupal_form_render_field_textarea'),
      'onfocus' => array('if(this.value == "'.$field['placeholder'].'") { this.value = ""; }'),
      'onblur' => array('if(this.value == "") { this.value = "'.$field['placeholder'].'"; }')
    ),
  );

  return $form;
}

function gcaba_drupal_form_render_field_radio($field,$form) {
  $form['gcaba_drupal_form_render_field_radio'.$field['id'] ] = array(
    '#title' => $field['title'],
    '#type' => 'radios',
    '#value'  => $field['placeholder'],
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
    '#value'  => $field['placeholder'],
    '#attributes' => array(
      'data-id' => $field['id'],
      'class' => array('gcaba_drupal_form_render_field_recaptcha'),
      'onfocus' => array('if(this.value == "'.$field['placeholder'].'") { this.value = ""; }'),
      'onblur' => array('if(this.value == "") { this.value = "'.$field['placeholder'].'"; }')
    ),
  );

  return $form;
}