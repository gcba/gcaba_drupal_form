<?php
function trim_value(&$value){ 
    $value = trim($value); 
}

/**
 * Implementa hook_info().
 */
function gcaba_drupal_form_block_info() {
  $blocks = array();
  $entities = gcaba_forms_forms_load_multiple();

  foreach ($entities as $key => $form) {
    $identifier = 'GCABAForm-'.$form->basic_id;
    $blocks[$identifier] = array(
      'info' => 'GCABA Form: '.$form->title, 
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

  if($delta[0] && $delta[0] == 'GCABAForm'){
    $block = array(
      'content' => drupal_get_form('gcaba_drupal_form_render', $delta[1])
    );
  }

  return $block;
}

function gcaba_drupal_form_render($form, &$form_state, $id) {
  $entity = gcaba_forms_forms_load($id);

  $form['#attributes']['id'] = 'gcaba_drupal_form_render_form_'.$id;

  $form['#attributes']['data-id'] = $id;

  $form['#attributes']['class'][] = 'gcaba-drupal-form-render-form';

  $form = gcaba_drupal_form_render_fields($form, $entity);

  $wrapperId = 'gcaba_drupal_form_result_'.$id;

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Enviar'),
    '#submit' => array(),
    '#ajax' => array(
      'callback' => 'gcaba_drupal_form_render_form_submit',
      'wrapper' => $wrapperId,
      'progress' => array('type' => 'throbber','message' => '<div class="feedback form_loading">Consultando...</div>'),
      'method' => 'replace',
      'effect' => 'fade',
      'class' => 'input.form-submit'
    )
  );

  $form[$wrapperId] = array(
      '#type' => 'markup',
      '#prefix' => '<div id="'.  $wrapperId . '" class="feedback email">',
      '#suffix' => '</div>',
      '#markup' => ''
  );

  return $form;
}

function gcaba_drupal_form_render_fields($form, $form_entity){
  $fields = gcaba_drupal_form_get_fields(unserialize($form_entity->fields));

  foreach ($fields as $v) {
    switch ($v['type']) {
      case 'TEXT':
        $form = gcaba_drupal_form_render_field_text($v, $form);
        break;
      case 'SELECT':
        $form = gcaba_drupal_form_render_field_select($v, $form);
        break;
      case 'TEXTAREA':
        $form = gcaba_drupal_form_render_field_textarea($v, $form);
        break;
      case 'RADIO':
        $form = gcaba_drupal_form_render_field_radio($v, $form);
        break;
      case 'CHECKBOX':
        $form = gcaba_drupal_form_render_field_checkbox($v, $form);
        break;
      case 'RECAPTCHA':
        $form = gcaba_drupal_form_render_field_recaptcha($v, $form);
        break;
    }


  }

  //ugly captcha
  $form['captcha'] = array(
    '#type' => 'markup',
    '#markup' => '<div id="recaptcha_div"></div><div id="recaptcha_widget" style="display:none">

                       <div id="recaptcha_image"></div>
                       <div class="recaptcha_only_if_incorrect_sol" style="color:red">Incorrecto, por favor intente de nuevo</div>

                       <span class="recaptcha_only_if_image">Ingrese las palabras de arriba:</span>
                       <span class="recaptcha_only_if_audio">Ingrese los números que escuche:</span>

                       <input type="text" id="recaptcha_response_field" name="recaptcha_response_field" />
                      
                       <ul id="recaptcha_options">
                       <li class="first"><div><a href="javascript:Recaptcha.reload()">Nuevo código</a></div></li>
                       <li class="last"><div class="recaptcha_only_if_image"><a href="javascript:Recaptcha.switch_type(\'audio\');">Audio</a></div>
                       <div class="recaptcha_only_if_audio"><a href="javascript:Recaptcha.switch_type(\'image\');">Imagen</a></div></li>
                       </ul>
                     </div>

                     <script type="text/javascript"
                        src="http://www.google.com/recaptcha/api/challenge?k=6LddOs8SAAAAAKwxz9Et9Lujx2YVb0LBft3PB1-G">
                     </script>
                     <noscript>
                       <iframe src="http://www.google.com/recaptcha/api/noscript?k=6LddOs8SAAAAAKwxz9Et9Lujx2YVb0LBft3PB1-G"
                            height="300" width="500" frameborder="0"></iframe><br>
                       <textarea name="recaptcha_challenge_field" rows="3" cols="40">
                       </textarea>
                       <input type="hidden" name="recaptcha_response_field"
                            value="manual_challenge">
                     </noscript>',
  );
  return $form;

}

function gcaba_drupal_form_get_fields($fields){
  $fields = gcaba_forms_fields_load_multiple($fields);
  $cleanFields = array();

  foreach ($fields as $key => $v) {
    // Parse OPTIONS var
    $result_final = array();

    if(!empty($v->options)){
      $result = explode( "\n", $v->options);
      foreach ($result as $key => $value) {
        $tmp = explode("|", $value);
        $result_final[$tmp[0]] = $tmp[1];
      }
      // End parse
    }

    // TODO: Ugli...
    $f = array(
      'id'              => $v->basic_id,
      'title'           => $v->title,
      'type'            => $v->type,
      'options'         => $result_final,
      'validators'      => unserialize($v->validators),
      'placeholder'     => $v->placeholder,
      'label'           => $v->label,
      'help'            => $v->help,
      'initial_value'   => $v->value,
    );
    $cleanFields[] = $f;
  }

  return $cleanFields;
}

function gcaba_drupal_form_render_form_submit($form, &$form_state) {
  $prefix     = 'gcaba_drupal_form_render_field_';
  $valores    = array();
  $errors     = array();
  $form_entity = gcaba_forms_forms_load($form['#attributes']['data-id']);

  $tomail     = $form_entity->emails  == '' ? FALSE : TRUE;
  $toapi      = $form_entity->url     == '' ? FALSE : TRUE;

  $wrapperId = 'gcaba_drupal_form_result_' . $form['#attributes']['data-id'] ;
  
  foreach ($form_state['input'] as $key => $value) {
    if (!strncmp($key, $prefix, strlen($prefix))){
      $field_node = gcaba_forms_fields_load($form[$key]['#attributes']['data-id']);

      foreach (unserialize($field_node->validators) as $key1 => $value1) {
        if($value1 != "0"){
          switch ($value1) {
            case 'REQUERIDO'://
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
          array_push($valores, array($field_node->title, $value));
        }

      }

    }
  }
  require_once('recaptcha/recaptchalib.php');
  $privatekey = "6LddOs8SAAAAAHBYfSCGWkS_4QDSsx7dnSg7u4-5";
  $resp = recaptcha_check_answer ($privatekey,
                                $_SERVER["REMOTE_ADDR"],
                                $_POST["recaptcha_challenge_field"],
                                $_POST["recaptcha_response_field"]);

  if (!$resp->is_valid) {
    return array("#markup" => "<div id='gcaba_email_result' class='email form_error'>El Captcha no fue correctamente ingresado.</div><script>Recaptcha.reload();</script>");    
  }

  $proceso = TRUE;
  if(count($errors) > 0){
    $html = "<ul class='text-error alert alert-error error-formulario'>";
    foreach ($errors as $key => $value) {
      $html .= "<li>".$value."</li>";
    }
    $html .= "</ul>";

    $form[$wrapperId]['#markup'] = $html;
    $proceso = FALSE;
  }

  
  // Send mail
  if($tomail && $proceso){
    $emails = explode(",", trim( $form_entity->emails));
    array_walk($emails, 'trim_value');

    $body = "";
    foreach ($valores as $key5 => $value5) {
      $body .= $value5[0]. ": ".$value5[1]."<br />";
    }

    foreach ($emails as $key => $email) {
      // TODO Valido correo
      $from = 'noreply@buenosaires.gob.ar';

      $params = array(
        'subject' => $form_entity->title,
      );
      $params['body'] = array(t($body));  

      drupal_mail('gcaba_drupal_form', 'gcaba_drupal_form_email', $email, language_default(), $params, $from, TRUE);
      
      if (!sent){
        $proceso == FALSE;
      }
    }
  }

/*
  // Save it to API List coming soon
  if($toapi && $proceso){
    $url = $form_entity->url;
    if(valid_url($url, TRUE)){
      
      $options = array(
        'method' => 'POST',
        'data' => json_encode($valores),
        'headers' => array('Content-Type' => 'application/json'),
      );

      $result = drupal_http_request($url, $options);
      dd($result);
    }else{
      dd("URL NO VALIDA");
    }
    dd($url);
  }
*/

  if($proceso == TRUE){
    if($form_entity->success_text != ''){
      $form[$wrapperId]['#markup'] = $form_entity->success_text ;
    }else{
      $form[$wrapperId]['#markup'] = t('El formulario fue procesado correctamente.');
    }
  }

  return $form[$wrapperId];
}

/**
 * Implements hook_mail().
 */
function gcaba_drupal_form_mail($key, &$message, $params) {
  if ($key == 'gcaba_drupal_form_email') {
    $message['subject'] = $params['subject'];
    $message['body'] = $params['body'];
    $message['headers'] = $params['headers'];
  }
}


?>
