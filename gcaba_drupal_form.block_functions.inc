<?php
require_once drupal_get_path('module','gcaba_drupal_form').'/gcaba_drupal_form.render_fields.inc';

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

  return $form;//$formData->title;
}

/**
 * Implementa hook_FORM_ID_validate().
 * Valida la información que llega al momento del submit del formulario inicial.
 */
function gcaba_drupal_form_render_form_validate($form,&$form_state) {
  //TODO validate
}

function gcaba_drupal_form_render_form_submit($form, &$form_state) {
  $formId = $form['#attributes']['data-id'];
  $prefix = 'gcaba_drupal_form_render_field_';

  foreach ($form_state['input'] as $key => $value) {

    if (!strncmp($key, $prefix, strlen($prefix))){
      $fieldId = $form[$key]['#attributes']['data-id'];

      //TODO hacer que grabe la data en algún lado

      /*$node = new stdClass();
      $node->type = 'gcaba_form_form_data';
      node_object_prepare($node);

      $node->title    = 'Node Created Programmatically on ' . date('c');
      $node->language = LANGUAGE_NONE;
      $path = 'content/programmatically_created_node_' . date('YmdHis');
      $node->path = array('alias' => $path);
      $node->body[$node->language][0]['value']   = 'text';
      $node->body[$node->language][0]['summary'] = text_summary('summary');
      $node->body[$node->language][0]['format']  = 'filtered_html';

      $node->gcaba_form_form_id = $formId;
      $node->gcaba_form_field_id = $fieldId;
      $node->gcaba_form_data = $value;

      node_save($node);*/
    }

  }

  return array("#markup" => 'gracias!!' );
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

      //TODO los otros tipos
      
    }

  }

  return $form;

}

function gcaba_drupal_form_get_fields($fields){
  $ids = array();

  //var_dump($fields["und"]);
  //echo '<br/>';
  $language = LANGUAGE_NONE;
  foreach ($fields[$language] as $key => $value) {
    $ids[]=(int)$value["target_id"];
  }

  $fields = node_load_multiple($ids);

  $cleanFields = array();

  foreach ($fields as $key => $v) {
    $f = array(
      'id' => $v->nid,
      'title' => $v->title,
      'type' => $v->field_gcaba_form_field_type[$language][0]["value"],
      'placeholder' => (count($v->field_gcaba_form_placeholder)>0)?$v->field_gcaba_form_placeholder[$language][0]["value"]:''
      ///TODO los demás campos...
    );

    $cleanFields[] = $f;
  }

  return $cleanFields;
}

//Ejemplo de uso - gcaba_drupal_form_insert_block(44,'Bloque de Test');

/*function gcaba_drupal_form_insert_block($id,$title) {
  //graba pero tiene algún problema porque no llama al hook block_view de arriba

  $identifier = 'GCABAForm-'.$id.'-'.$title;

  $delta = db_insert('block_custom')->fields(array(
    'info' => $identifier,
    'body' => 'Formulario creado con GCABA Drupal Form: ID:'.$id.' - NOMBRE:'.$title,
    'format' => 'filtered_html',
  ))->execute();

  $query = db_insert('block')->fields(array('visibility', 'pages', 'custom', 'title', 'module', 'theme', 'status', 'weight', 'delta', 'cache'));
    foreach (list_themes() as $key => $theme) {
      if ($theme->status) {
        $query->values(array(
          'visibility' => 1,
          'pages' => "2",
          'custom' => 1,
          'title' => $identifier,
          'module' => 'gcaba_drupal_form',
          'theme' => '',
          'status' => 1,
          'weight' => 1,
          'delta' => $identifier,
          'cache' => DRUPAL_NO_CACHE,
        ));
      }
    }
    $query->execute();

}
*/


?>