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

function gcaba_forms_forms_uri($gcaba_forms_forms){
    return array(
        'path'  => 'gcaba_forms_forms/' . $gcaba_forms_forms->aid,
    );
}

function gcaba_forms_form_fields_uri($gcaba_forms_form_fields){
    return array(
        'path'  => 'gcaba_forms_form_fields/' . $gcaba_forms_form_fields
    );
}

?>