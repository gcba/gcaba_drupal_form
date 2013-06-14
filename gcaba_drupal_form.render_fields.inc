<?php

function gcaba_drupal_form_render_field_text($field,$form) {

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

}