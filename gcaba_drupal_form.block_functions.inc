<?php

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
  $block['content'] = '';

  if($delta[0] && $delta[0]=='GCABAForm')
      $block['content'] = gcaba_drupal_form_render_form($delta[1]);

  return $block;
}

function gcaba_drupal_form_render_form($nodeId) {
  $formData = node_load($nodeId);
  return json_encode($formData);
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