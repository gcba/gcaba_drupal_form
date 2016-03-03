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
  drupal_add_js('http://www.google.com/recaptcha/api/js/recaptcha_ajax.js');
  drupal_add_js(' var RecaptchaOptions = {
    theme : "custom",
    custom_theme_widget: "recaptcha_widget"
 };', 'inline');

  drupal_add_js(drupal_get_path('module', 'gcaba_drupal_form') . '/js/baid.js',array('type' => 'file', 'scope' => 'footer'));
    
  //Agrega los script para fix de jQuery - Drupal Form Ajax
  _gcaba_drupal_form_jquery_fix();

  $entity = gcaba_forms_forms_load($id);


  $form['Loggearse'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="miba_usardatos" style="color:blue;text-decoration:underline;cursor:pointer;float:right;font-size:12px" >No soy esa persona</div>',
  );

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
      'effect' => 'fade'
    ),
     // se le agrega a la clase btn-lg btn-block
    '#attributes' => array(
      'class' => array(' btn-lg btn-block')
    )
  );

$form['footer'] = array(
      '#type' => 'markup',
      '#prefix' => '<div class="gcaba_form_footer">',
      '#suffix' => '</div>',
      '#markup' => $entity->footer
  );

$form['error'] = array(
      '#type' => 'markup',
      '#prefix' => '<div id="'.$wrapperId.'">',
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
      case 'SELECTCHOSEN':
        $form = gcaba_drupal_form_render_field_select_chosen($v, $form);
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
      case 'FILE':
        $form = gcaba_drupal_form_render_field_file($v, $form);
        break;
      case 'TITLE':
        $form = gcaba_drupal_form_render_field_title($v, $form);
        break;
      case 'SELECTTOMAIL':
        $form = gcaba_drupal_form_render_field_selecttomail($v, $form);
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
      'openIDname'      => $v->openIDname
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

  $wrapperId = 'gcaba_drupal_form_result_' . $form['#attributes']['data-id'];

  $archivos = array();
  $attachments = array();

  $mailsto = array();


  /*
   * Se recorren los elementos del form,
   * si son del drupal_form se validan y agregan al acumulador
   */
  foreach ($form_state['input'] as $key => $value) {
    if (!strncmp($key, $prefix, strlen($prefix))){
      $field_node = gcaba_forms_fields_load($form[$key]['#attributes']['data-id']);

      _gcaba_drupal_form_validate_field($field_node, $key, $value, $errors);

      _gcaba_drupal_form_get_value($key, $value, $field_node, $form_state, $valores, $archivos, $mailsto);
    }
  }//end foreach ($form_state['input'] as $key => $value)
  
  /*
   * BEGIN Captcha
   */
  require_once('recaptcha/recaptchalib.php');
  $privatekey = "6LddOs8SAAAAAHBYfSCGWkS_4QDSsx7dnSg7u4-5";
  $resp = recaptcha_check_answer ($privatekey,
                                $_SERVER["REMOTE_ADDR"],
                                $_POST["recaptcha_challenge_field"],
                                $_POST["recaptcha_response_field"]);
  if (!$resp->is_valid) {
    return array("#markup" => "<div id='".$wrapperId."' class='text-error alert alert-error error-formulario'>El Captcha no fue correctamente ingresado.</div><script>Recaptcha.reload();</script>");    
  }
  /*
   * END Captcha
   */

  _gcaba_drupal_form_save_files($archivos, $attachments, $form_state, $errors);

  $proceso = TRUE;
  if(count($errors) > 0){
    $html = "<div id='".$wrapperId."' ><ul class='text-error alert alert-error error-formulario'>";
    foreach ($errors as $key => $value) {
      $html .= "<li>".$value."</li>";
    }
    $html .= "</ul><script>Recaptcha.reload();</script></div>";

    $form[$wrapperId]['#markup'] = $html;
    $proceso = FALSE;
  }

  // Send mail
  if($tomail && $proceso){
    _gcaba_drupal_form_send_email($form_entity, $valores, $attachments, $proceso, $mailsto);
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
      $form[$wrapperId]['#markup'] = '<div class= "alert alert-success">'.$form_entity->success_text.'</div>';
    }else{
      $form[$wrapperId]['#markup'] = '<div class= "alert alert-success">'.t('El formulario fue procesado correctamente.').'</div>';
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
    $message['params']['attachments'] = $params['attachments'];
    $message['headers'] = $params['headers'];
  }
}

/*
 * Auxiliar: Validadores
 */
function _gcaba_drupal_form_validate_field($field_node, $form_field_name, $value, &$errors){
  foreach (unserialize($field_node->validators) as $key1 => $value1) {
    if($value1 != "0"){
      switch ($value1) {
        case 'REQUERIDO'://
          if($field_node->type === "FILE") {
            if (empty($_FILES['files']['name'][$form_field_name])) {
              array_push($errors, t("Field <b>").$field_node->title. t("</b> is required."));
            }
          } else {
            if (empty($value)){
              array_push($errors, t("Field <b>").$field_node->title. t("</b> is required."));
            }  
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
      } //END switch($value1)
    } //end if($value1 != "0")

  }
}

/*
 * Auxiliar: guardar valores
 */
function _gcaba_drupal_form_get_value($key, $value, $field_node, $form_state, &$valores, &$archivos, &$mailsto){
  if(is_array($value)){
    $value = implode(' ', $value);
  }
  array_push($valores, array($field_node->title, $value));

  
  $field = $form_state['complete form'][$key];
  //En caso de ser un archivo lo agrego al listado de archivos
  if(isset($field['#type']) && $field['#type'] == "file"){
    $archivos[] = $key;
  }

  //En caso de ser un mail adicional lo agrego al listado de mails
  if($field_node->type == "SELECTTOMAIL"){
    $mailsto[] = $value;
  }

}

/*
 * Auxiliar: guardar archivos subidos, si hay
 */
function _gcaba_drupal_form_save_files($archivos, &$attachments, &$form_state, &$errors){
  foreach($archivos as $archivo) {
    $file = file_save_upload($archivo);
    if ($file) {
      // Move the file into the Drupal file system.
      if ($file = file_move($file, 'public://')) {
      // Save the file for use in the submit handler.
        $form_state['storage']['file'][] = $file;
      }
      else {
        form_set_error('file', t("Failed to write the uploaded file to the site's file folder."));
        array_push($errors, t("Failed to write the uploaded file to the site's file folder."));
      }
    }
    else {
      form_set_error('file', t('No file was uploaded.'));
      array_push($errors, t('No file was uploaded.'));
    }
  }

  $files = array();
  foreach($form_state['storage']['file'] as $file){
    $attachment = array(
      'filecontent' => file_get_contents($file->uri),
      'filename' => $file->filename,
      'filemime' => $file->filemime,
    );
    $attachments[] = $attachment;
    $files[] = $file;
  }

  foreach($files as $file){
    file_delete($file, TRUE);
  }

}

/*
 * Auxiliar: enviar mail
 */
function _gcaba_drupal_form_send_email($form_entity, $valores, $attachments,&$proceso, $mailsto) {
  //Emails del form
  $emails = explode(",", trim( $form_entity->emails));
  //Emails agregados por campos
  $emails = array_merge($emails, $mailsto);

  array_walk($emails, 'trim_value');

  $body = "";
  foreach ($valores as $key5 => $value5) {
    $body .= utf8_decode($value5[0]). ": ".utf8_decode($value5[1])."\n";

  }

  foreach ($emails as $key => $email) {
    // TODO Valido correo
    $from = 'noreply@buenosaires.gob.ar';

    $params = array(
      'subject' => utf8_decode($form_entity->title),
    );
    $params['body'] = array(t($body));

    $params['attachments'] = $attachments;

    drupal_mail('gcaba_drupal_form', 'gcaba_drupal_form_email', $email, language_default(), $params, $from, TRUE);
    
    if (!sent){
      $proceso == FALSE;
    }
  }
}

/**
 * Agrega los fixs necesarios de jQuery para los drupal form ajax
 */
function _gcaba_drupal_form_jquery_fix(){
  drupal_add_js('jQuery.extend({
    handleError: function( s, xhr, status, e ) {
          // If a local callback was specified, fire it
          if ( s.error )
              s.error( xhr, status, e );
          // If we have some XML response text (e.g. from an AJAX call) then log it in the console
          else if(xhr.responseText)
              console.log(xhr.responseText);
      }
  });', 'inline');

  drupal_add_js('jQuery.extend({
    httpData: function( xhr, type, s ) {
      var ct = xhr.getResponseHeader("content-type") || "",
        xml = type === "xml" || !type && ct.indexOf("xml") >= 0,
        data = xml ? xhr.responseXML : xhr.responseText;

      if ( xml && data.documentElement.nodeName === "parsererror" ) {
        jQuery.error( "parsererror" );
      }

      // Allow a pre-filtering function to sanitize the response
      // s is checked to keep backwards compatibility
      if ( s && s.dataFilter ) {
        data = s.dataFilter( data, type );
      }

      // The filter can actually parse the response
      if ( typeof data === "string" ) {
        // Get the JavaScript object, if JSON is used.
        if ( type === "json" || !type && ct.indexOf("json") >= 0 ) {
          data = jQuery.parseJSON( data );

        // If the type is "script", eval it in global context
        } else if ( type === "script" || !type && ct.indexOf("javascript") >= 0 ) {
          jQuery.globalEval( data );
        }
      }

      return data;
    }
  });', 'inline');

}