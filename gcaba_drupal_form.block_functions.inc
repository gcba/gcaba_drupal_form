<?php

/**
 * Implementa hook_info().
 */
function gcaba_drupal_form_block_info() {
  //TODO buscar todos los creados por el módulo y agregarlos.

  $blocks['bloque1'] = array(
    'info' => t('bloque 1'), 
    'cache' => DRUPAL_NO_CACHE,
  );

  return $blocks;
}

/**
 * Implementa hook_view().
 */
function gcaba_drupal_form_block_view($delta = '') {

  //TOOD no llega a este hook cuando renderiza, revisar

  $delta = split('-', $delta);

  $block = array();
  $block['content'] = 
  '<p>ID:'+$delta[1]+'</p>'.
  '<p>NOMBRE:'+$delta[2]+'</p>';

  return $block;
}


//Ejemplo de uso - gcaba_drupal_insert_block_form(44,'Bloque de Test');

function gcaba_drupal_insert_block($id,$title) {
  //graba pero tiene algún problema porque no llama al hook block_view de arriba

  $identifier = 'GCABAForm-'.$id.'-'.$title;

  $delta = db_insert('block_custom')->fields(array(
    'body' => $identifier,
    'info' => $identifier,
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


/*$query = db_insert('block_role')->fields(array('rid', 'module', 'delta'));
  foreach (array_filter($form_state['values']['roles']) as $rid) {
    $query->values(array(
      'rid' => $rid,
      'module' => $form_state['values']['module'],
      'delta' => $delta,
    ));
  }
  $query->execute();*/

}



?>