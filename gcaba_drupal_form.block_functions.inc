<?php
require_once drupal_get_path('module','gcaba_drupal_form').'/gcaba_drupal_form.render_fields.inc';

function trim_value(&$value){ 
    $value = trim($value); 
}

/**
 * Implementa hook_info().
 */
function gcaba_drupal_form_block_info() {
  //TODO buscar todos los creados por el módulo y agregarlos.
 
  $nids = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->fields('n', array('title'))
    ->condition('n.type', 'gcaba_form_form')
    ->execute()
    ->fetchAll();

  foreach ($nids as $key => $form) {
    $identifier = 'GCABAForm-'.$form->nid;
    $blocks[$identifier] = array(
      'info' => 'GCABA Drupal Form: '.$form->title, 
      'cache' => DRUPAL_NO_CACHE
    );
  }

  return $blocks;
}

/**
 * Implementa hook_view().
 */
function gcaba_drupal_form_block_view($delta = '') {
  $delta = explode('-', $delta);
  $block = array();

  if($delta[0] && $delta[0]=='GCABAForm'){
    $block = array(
      'content' => drupal_get_form('gcaba_drupal_form_render',$delta[1])
    );
  }

  return $block;
}

function gcaba_drupal_form_render($form, &$form_state,$nodeId) {
  $nodeData = node_load($nodeId);

  $form['#attributes']['id'] = 'gcaba_drupal_form_render_form_'.$nodeId;

  $form['#attributes']['data-id'] = $nodeId;

  $form['#attributes']['class'][] = 'gcaba-drupal-form-render-form';

  $form = gcaba_drupal_form_render_fields($form,$nodeData);

  $wrapperId = 'gcaba_drupal_form_result_'.$nodeId;

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Enviar'),
    '#submit' => array(),
    '#ajax' => array(
      'callback' => 'gcaba_drupal_form_render_form_submit',
      'wrapper' => $wrapperId,
      'progress' => array('type' => 'throbber','message' => '<div class="feedback form_loading">Consultando...</div>'),
      'method' => 'replace',
      'effect' => 'fade'
    )
  );

  $form[$wrapperId] = array(
      '#type' => 'markup',
      '#prefix' => '<div id="'.  $wrapperId . '" class="feedback email form_error">',
      '#suffix' => '</div>',
      '#markup' => ''
  );

  return $form;
}

function gcaba_drupal_form_render_form_submit($form, &$form_state) {
  $language   = LANGUAGE_NONE; // #duda
  $prefix     = 'gcaba_drupal_form_render_field_';
  $valores    = array();
  $errors     = array();

  $form_node  = node_load($form['#attributes']['data-id']);
  $tomail     = $form_node->field_gcaba_form_toemails[$language][0]['safe_value'] == '' ? FALSE : TRUE;
  $toapi      = $form_node->field_gcaba_form_urlapi[$language][0]['safe_value'] == '' ? FALSE : TRUE;

  $wrapperId = 'gcaba_drupal_form_result_' . $form['#attributes']['data-id'] ;
  
  foreach ($form_state['input'] as $key => $value) {
    if (!strncmp($key, $prefix, strlen($prefix))){
      $field_node = node_load($form[$key]['#attributes']['data-id']);

      foreach ($field_node->field_gcaba_form_validators[$language] as $key1 => $value1) {
        switch ($value1["value"]) {
          case 'REQUERIDO':
            if (empty($value)){
              array_push($errors, t("Field <b>").$field_node->title. t("</b> is required."));
            }
            break;
          case 'URL':
            if (!valid_url($value)){
              array_push($errors, t("Field <b>").$field_node->title. t("</b> is not an URL."));
            }
            break;
          case 'EMAIL':
            if (!valid_email_address($value)){
              array_push($errors, t("Field <b>").$field_node->title. t("</b> must be a valid email address."));
            }
            break;
          case 'NUMERIC':
            if (!is_numeric($value)){
              array_push($errors, t("Field <b>").$field_node->title. t("</b> must be a number."));
            }
            break;
          case 'NON-NUMERIC':
            if (is_numeric($value)){
              array_push($errors, t("Field <b>").$field_node->title. t("</b> must not be a number."));
            }
            break;
        }
      }
      array_push($valores, array($field_node->title, $value));
    }
  }

  $proceso = TRUE;
  if(count($errors) > 0){
    $html = "<ul class='error'>";
    foreach ($errors as $key => $value) {
      $html .= "<li>".$value."</li>";
    }
    $html .= "</ul>";

    $form[$wrapperId]['#markup'] = $html;
    $proceso = FALSE;
  }

  // Send mail
  if($tomail && $proceso){
    $emails = explode(",", trim( $form_node->field_gcaba_form_toemails[$language][0]['safe_value'] ) );
    array_walk($emails, 'trim_value');

    $body = "";
    foreach ($valores as $key5 => $value5) {
      $body .= $value5[0]. ": ".$value5[1]."<br>";
    }

    foreach ($emails as $key => $email) {
      // TODO Valido correo
      $from = 'noreply@buenosaires.gob.ar';

      $params = array(
        'body' => $body,
        'subject' => $form_node->title,
      );

      if (!drupal_mail('gcaba_drupal_form', 'gcaba_drupal_form_email', $email, language_default(), $params, $from, TRUE)){
        $proceso == FALSE;
      }
    }
  }

  // Save it to API List
  if($toapi && $proceso){
    dd("TODO: Sale por API");
  }

  if($proceso == TRUE){
    if($form_node->field_gcaba_form_success_text[$language][0]['safe_value'] != ''){
      $form[$wrapperId]['#markup'] = $form_node->field_gcaba_form_success_text[$language][0]['safe_value'] ;
    }else{
      $form[$wrapperId]['#markup'] = t('El formulario fue procesado correctamente.');
    }
  }
  
  return $form[$wrapperId];
}

function gcaba_drupal_form_render_fields($form,$nodeData){
  $fields = gcaba_drupal_form_get_fields($nodeData->field_gcaba_form_fields);

  foreach ($fields as $v) {
    switch ($v['type']) {
      case 'TEXT':
        $form = gcaba_drupal_form_render_field_text($v,$form);
        break;
      case 'SELECT':
        $form = gcaba_drupal_form_render_field_select($v,$form);
        break;
      case 'TEXTAREA':
        $form = gcaba_drupal_form_render_field_textarea($v,$form);
        break;
      case 'RADIO':
        $form = gcaba_drupal_form_render_field_radio($v,$form);
        break;
      case 'CHECKBOX':
        $form = gcaba_drupal_form_render_field_checkbox($v,$form);
        break;
      case 'RECAPTCHA':
        $form = gcaba_drupal_form_render_field_recaptcha($v,$form);
        break;
    }

  }
  return $form;

}

function gcaba_drupal_form_get_fields($fields){
  $ids = array();

  $language = LANGUAGE_NONE;
  foreach ($fields[$language] as $key => $value) {
    $ids[]=(int)$value["target_id"];
  }

  $fields = node_load_multiple($ids);

  $cleanFields = array();

  foreach ($fields as $key => $v) {
    // Parse OPTIONS var
    $result_final = array();
    $result = explode( "\n", (count($v->field_field_gcaba_form_options)>0)?$v->field_field_gcaba_form_options[$language][0]["value"]:'' );
    foreach ($result as $key => $value) {
      $tmp = explode("|", $value);
      $result_final[$tmp[0]] = $tmp[1];
    }
    // End parse

    $f = array(
      'id'              => $v->nid,
      'title'           => $v->title,
      'type'            => $v->field_gcaba_form_field_type[$language][0]["value"],
      'options'         => $result_final,
      'validators'      => (count($v->field_gcaba_form_validators)>0)?$v->field_gcaba_form_validators[$language][0]["value"]:'',
      'placeholder'     => (count($v->field_gcaba_form_placeholder)>0)?$v->field_gcaba_form_placeholder[$language][0]["value"]:'',
      'label'           => (count($v->field_gcaba_form_label)>0)?$v->field_gcaba_form_label[$language][0]["value"]:'',
      'help'            => (count($v->field_gcaba_form_help)>0)?$v->field_gcaba_form_help[$language][0]["value"]:'',
      'initial_value'   => (count($v->field_gcaba_form_initial_value)>0)?$v->field_gcaba_form_initial_value[$language][0]["value"]:'',
      'order'           => (count($v->field_field_gcaba_form_order)>0)?$v->field_field_gcaba_form_order[$language][0]["value"]:'',
    );

    $cleanFields[] = $f;
  }

  return $cleanFields;
}

?>