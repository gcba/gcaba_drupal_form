<?php

function gcaba_drupal_form_render_field_text($field, $form) {
  $form['gcaba_drupal_form_render_field_text_'.$field['id'] ] = array(
    '#title' => $field['title'],
    '#type' => 'textfield',
    '#value'  => $field['placeholder'],
    '#attributes' => array(
      'data-id' => $field['id'],
      'class' => array('gcaba_drupal_form_render_field_text'),
      'onfocus' => array('if(this.value == "'.$field['placeholder'].'") { this.value = ""; }'),
      'onblur' => array('if(this.value == "") { this.value = "'.$field['placeholder'].'"; }')
    ),
  );

  return $form;
}

function gcaba_drupal_form_render_field_select($field,$form) {
  // TODO: Se muestra pero no muestra <options>
  $form['gcaba_drupal_form_render_field_select_'.$field['id'] ] = array(
    '#title' => $field['title'],
    '#type' => 'select',
    '#value'  => $field['placeholder'],
    '#options' =>  array('return_value1' => t('Display Value 1'), 'return_value2' => t('Display Value 2')),
    '#attributes' => array(
      'data-id' => $field['id'],
      'class' => array('gcaba_drupal_form_render_field_select'),
      'onfocus' => array('if(this.value == "'.$field['placeholder'].'") { this.value = ""; }'),
      'onblur' => array('if(this.value == "") { this.value = "'.$field['placeholder'].'"; }')
    ),
  );

  return $form;
}

function gcaba_drupal_form_render_field_textarea($field,$form) {
  $form['gcaba_drupal_form_render_field_textarea'.$field['id'] ] = array(
    '#title' => $field['title'],
    '#type' => 'textarea',
    '#value'  => $field['placeholder'],
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
    '#type' => 'radio',
    '#value'  => $field['placeholder'],
    '#attributes' => array(
      'data-id' => $field['id'],
      'class' => array('gcaba_drupal_form_render_field_radio'),
      'onfocus' => array('if(this.value == "'.$field['placeholder'].'") { this.value = ""; }'),
      'onblur' => array('if(this.value == "") { this.value = "'.$field['placeholder'].'"; }')
    ),
  );

  return $form;
}

function gcaba_drupal_form_render_field_checkbox($field,$form) {
  $form['gcaba_drupal_form_render_field_checkbox'.$field['id'] ] = array(
    '#title' => $field['title'],
    '#type' => 'checkbox',
    '#value'  => $field['placeholder'],
    '#attributes' => array(
      'data-id' => $field['id'],
      'class' => array('gcaba_drupal_form_render_field_checkbox'),
      'onfocus' => array('if(this.value == "'.$field['placeholder'].'") { this.value = ""; }'),
      'onblur' => array('if(this.value == "") { this.value = "'.$field['placeholder'].'"; }')
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