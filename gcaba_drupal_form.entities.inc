<?php

/**
 * Implements hook_entity_info().
 */
function gcaba_drupal_form_entity_info(){
	$return['gcaba_forms_forms'] = array(
		'label' 			=> t('GCABA Form form'),
		'controller class'	=> "GCABAFormsFormsController",
		'base table'		=> 'gcaba_forms_forms',
		'revision table'	=> 'gcaba_forms_forms_revision',
		'uri callback'		=> 'gcaba_forms_forms_uri',
		'fieldable'			=> TRUE,
		'entity keys'		=> array(
			'id'		=> 'aid',
			'revision'	=> 'vid',
			'bundle'	=> 'type',
			'label'		=> 'title',
		),
		'bundle keys'		=> array(
			'bundle'	=> 'type',
		),
		'static cache'		=> TRUE,
		'bundles'			=> array(),
		'view modes'		=> array(
			'full'	=> array(
				'label'				=> t('Full content'),
				'custom settings'	=> FALSE,
			),
			'teaser'=> array(
				'label'				=> t('Teaser'),
				'custom settings'	=> FALSE,
			),
		),
	);

	foreach (gcaba_forms_forms_types() as $type => $info) {
		$return['gcaba_forms_forms']['bundles'][$type] = array(
			'label'	=> $info->name,
			'admin'	=> array(
				'path'				=> 'admin/structure/gcaba_forms_forms/manage/%gcaba_forms_forms_type',
				'real path' 		=> 'admin/structure/gcaba_forms_forms/manage/' . 
					str_replace('_', '-', $type),
				'bundle argument'	=> 4,
				'access arguments'	=> array('administer gcaba_forms_forms'),
			),
		);
	}


	$return['gcaba_forms_form_fields'] = array(
		'label' 			=> t('GCABA Form field'),
		'controller class'	=> "GCABAFormsFieldsController",
		'base table'		=> 'gcaba_forms_form_fields',
		'revision table'	=> 'gcaba_forms_form_fields_revision',
		'uri callback'		=> 'gcaba_forms_form_fields_uri',
		'fieldable'			=> TRUE,
		'entity keys'		=> array(
			'id'		=> 'aid',
			'revision'	=> 'vid',
			'bundle'	=> 'type',
			'label'		=> 'title',
		),
		'bundle keys'		=> array(
			'bundle'	=> 'type',
		),
		'static cache'		=> TRUE,
		'bundles'			=> array(),
		'view modes'		=> array(
			'full'	=> array(
				'label'				=> t('Full content'),
				'custom settings'	=> FALSE,
			),
			'teaser'=> array(
				'label'				=> t('Teaser'),
				'custom settings'	=> FALSE,
			),
		),
	);

	foreach (gcaba_forms_form_fields_types() as $type => $info) {
		$return['gcaba_forms_form_fields']['bundles'][$type] = array(
			'label'	=> $info->name,
			'admin'	=> array(
				'path'				=> 'admin/structure/gcaba_forms_form_fields/manage/%gcaba_forms_form_fields_type',
				'real path' 		=> 'admin/structure/gcaba_forms_form_fields/manage/' . 
					str_replace('_', '-', $type),
				'bundle argument'	=> 4,
				'access arguments'	=> array('administer gcaba_forms_form_fields'),
			),
		);
	}



	return $return;
}

/**
 * GCABA Forms URI
 */
function gcaba_forms_forms_uri($gcaba_forms_forms){
    return array(
        'path'  => 'gcaba_forms_forms/' . $gcaba_forms_forms->aid,
    );
}

/**
 * GCABA Form Fields URI
 */
function gcaba_forms_form_fields_uri($gcaba_forms_form_fields){
    return array(
        'path'  => 'gcaba_forms_form_fields/' . $gcaba_forms_form_fields
    );
}

/**
 * GCABA Forms Types
 */
function gcaba_forms_forms_types() {
  $types = &drupal_static(__FUNCTION__);

  if (empty($types)) {
    $types['forms'] = (object) array(
      'type' =>  'Forms',
      'name' => t('Form'),
      'description' => t('A form object.')
    );
  }
  return $types;
}

/**
 * GCABA Form Fields Types
 */
function gcaba_forms_form_fields_types() {
  $types = &drupal_static(__FUNCTION__);

  if (empty($types)) {
    $types['fields'] = (object) array(
      'type' =>  'fields',
      'name' => t('field'),
      'description' => t('A form field object.')
    );
  }
  return $types;
}

/**
 * GCABA Form Fields Type Load
 */
function gcaba_forms_form_fields_type_load($type){
    $types 	= gcaba_forms_form_fields_types();
    $type 	= str_replace('-', '_', $types);
    return 	isset($types[$type]) ? $types[$type] : FALSE;
}

/**
 * GCABA Forms Type Load
 */
function gcaba_forms_forms_type_load($type){
    $types = gcaba_forms_forms_types();
    $type 	= str_replace('-', '_', $types);
    return 	isset($types[$type]) ? $types[$type] : FALSE;
}

/**
 * GCABA Forms Controller
 */
class GCABAFormsFormsController extends DrupalDefaultEntityController {
	function gcaba_forms_forms_load($aid = NULL, $vid = NULL, $reset = FALSE) {
		$aids = (isset($aid) ? array($aid) : array());
		$conditions = (isset($vid) ? array('vid' => $vid) : array());
		$gcaba_forms_forms = gcaba_forms_forms_load_multiple($aids, $conditions, $reset);
		return $gcaba_forms_forms ? reset($gcaba_forms_forms) : FALSE;
	}
	
	function gcaba_forms_forms_load_multiple($aids = array(), $conditions = array(), $reset = FALSE){
		return entity_load('gcaba_forms_forms', $aids, $conditions, $reset);
	}
}

/**
 * GCABA Form Fields Controller
 */
class GCABAFormsFieldsController extends DrupalDefaultEntityController {
	function gcaba_forms_form_fields_load($aid = NULL, $vid = NULL, $reset = FALSE) {
		$aids = (isset($aid) ? array($aid) : array());
		$conditions = (isset($vid) ? array('vid' => $vid) : array());
		$gcaba_forms_form_fields = gcaba_forms_form_fields_load_multiple($aids, $conditions, $reset);
		return $gcaba_forms_form_fields ? reset($gcaba_forms_form_fields) : FALSE;
	}
	
	function gcaba_forms_form_fields_load_multiple($aids = array(), $conditions = array(), $reset = FALSE){
		return entity_load('gcaba_forms_form_fields', $aids, $conditions, $reset);
	}
}
?>