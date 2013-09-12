<?php

/**
 * Third step submit
 */
function gcaba_drupal_form_forms_step_3_submit($form, $form_state){
	dpm("gcaba_drupal_form_forms_step_3_submit");
}

/**
 * Third step validate
 */
function gcaba_drupal_form_forms_step_3_validate($form, $form_state){
	dpm("gcaba_drupal_form_forms_step_3_validate");
}

/**
 * Third step
 */
function gcaba_drupal_form_forms_step_3($form, &$form_state){
	dpm("gcaba_drupal_form_forms_step_3");
	$values = isset($form_state['multistep_values']['step_3']) ? $form_state['multistep_values']['step_3'] : array();

	/* Field types */
	$field_types = array(
			'TEXT' => 'TEXT',
			'TEXTAREA' => 'TEXTAREA',
			'SELECT' => 'SELECT',
			'RADIO' => 'RADIO',
			'CHECKBOX' => 'CHECKBOX',
			'RECAPTCHA' => 'RECAPTCHA'
	);
	
	/* Add new field */
	$form['step_3'] = array(
			'#type' => 'fieldset',
			'#title' => t($form_state['multistep_values']['step_1']['title'].' - Add form field'),
			'#weight' => 10,
			'#collapsible' => FALSE,
			'#collapsed' => FALSE,
	);
	$form['step_3']['title'] = array(
			'#type'         => 'textfield',
			'#title'        => t('Title'),
			'#description'  => t("Field title"),
			'#default_value'=> "",
			'#size'         => 40,
			'#maxlength'    => 128,
			'#required'     => TRUE,
	);
	$form['step_3']['type'] = array(
			'#type' => 'radios',
			'#title' => t('Type'),
			'#default_value' => "",
			'#options' => $field_types,
			'#description' => t('Field type.'),
			'#required'     => TRUE,
	);
	$form['step_3']['help'] = array(
			'#type'         => 'textfield',
			'#title'        => t('Help'),
			'#description'  => t("Help text for field"),
			'#default_value'=> "",
			'#size'         => 80,
			'#maxlength'    => 400,
			'#required'     => FALSE,
	);
	$form['step_3']['placeholder'] = array(
			'#type'         => 'textfield',
			'#title'        => t('Placeholder'),
			'#description'  => t("Placeholder"),
			'#default_value'=> "",
			'#size'         => 80,
			'#maxlength'    => 400,
			'#required'     => FALSE,
	);
	$form['step_3']['value'] = array(
			'#type'         => 'textfield',
			'#title'        => t('Value'),
			'#description'  => t("Initial value"),
			'#default_value'=> "",
			'#size'         => 80,
			'#maxlength'    => 400,
			'#required'     => FALSE,
	);
	$form['step_3']['label'] = array(
			'#type'         => 'textfield',
			'#title'        => t('Label'),
			'#description'  => t("Label"),
			'#default_value'=> "",
			'#size'         => 40,
			'#maxlength'    => 400,
			'#required'     => FALSE,
	);
	$form['step_3']['order'] = array(
			'#type'         => 'textfield',
			'#title'        => t('Order'),
			'#description'  => t("Filds order"),
			'#default_value'=> 0,
			'#size'         => 10,
			'#maxlength'    => 2,
			'#required'     => TRUE,
	);
	$form['step_3']['options'] = array(
			'#type'         => 'textarea',
			'#title'        => t('Options'),
			'#description'  => t("Field options."),
			'#default_value'=> "",
			'#required'     => FALSE,
	);
	$form['step_3']['submit']  = array(
			'#type'     =>  'submit',
			'#value'    =>  t('Create field'),
	);

	return $form;
}

/**
 * Second step validate
 */
function gcaba_drupal_form_forms_step_2_validate($form, $form_state){
	dpm("gcaba_drupal_form_forms_step_2_validate --> ". $form_state['stage']);

	return $form;
}

/**
 * Second step
 */
function gcaba_drupal_form_forms_step_2($form, &$form_state){
	dpm("gcaba_drupal_form_forms_step_2 --> ". $form_state['stage']);
	$values = isset($form_state['multistep_values']['step_2']) ? $form_state['multistep_values']['step_2'] : array();
	/* Fields */
	$form['step_2'] = array(
			'#type' => 'fieldset',
			'#title' => t($form_state['multistep_values']['step_1']['title'].' form fields'),
			'#weight' => 10,
			'#collapsible' => FALSE,
			'#collapsed' => FALSE,
	);
	
	$form['step_2']['form_fields'] = array(
			'#type' => 'tableselect',
			'#header' => array(),
			'#options' => array(),
			'#empty' => t('No fields yet.'),
	);
	
	/* Available fields */
	$form['available'] = array(
			'#type' => 'fieldset',
			'#title' => t('Available fields'),
			'#weight' => 20,
			'#collapsible' => FALSE,
			'#collapsed' => FALSE,
	);
	$form['available']['fields'] = array(
			'#type' => 'tableselect',
			'#header' => array(),
			'#options' => array(),
			'#empty' => t('No available fields, please create one.'),
	);
	$form['available']['actions'] = array(
			'#type' => 'actions'
	);
	$form['available']['actions']['add_fields'] = array(
			'#type' => 'button',
			'#value' => t('New field'),
			'#id'	=> 'add_fields',
	);

	
	/* Actions */
	$form['actions'] = array(
			'#type' => 'actions'
	);
	$form['actions']['finish'] = array(
			'#type' => 'submit',
			'#value' => t('Finish'),
	);

	return $form;
}

/**
 * First step validate
 */
function gcaba_drupal_form_forms_step_1_validate($form, $form_state){
	dpm("gcaba_drupal_form_forms_step_1_validate");
}

/**
 * First step
 */
function gcaba_drupal_form_forms_step_1($form, &$form_state){
	dpm("gcaba_drupal_form_forms_step_1");
    $values = isset($form_state['multistep_values']['step_1']) ? $form_state['multistep_values']['step_1'] : array();

    /* Forms list */
    $rows = array();

    $gcaba_forms_forms = entity_load('gcaba_forms_forms');
    foreach($gcaba_forms_forms as $node){
        $rows[] = array($node->title, $node->name);
    }

    $form['forms_table'] = array(
        '#markup' => theme_table(array(
            "header"    => array(
                t("Name"), 
                t("Owner")
            ),
            "rows"      => $rows,
            "attributes" => array(),
            "caption"   => "",
            "colgroups" => array(),
            "sticky"    => TRUE,
            "empty"     => t("No forms available")
        )),
    );

    /* Add Form */
    $form['step_1'] = array(
        '#type' => 'fieldset',
        '#title' => t('Add new form'),
        '#weight' => 10,
        '#collapsible' => FALSE, 
        '#collapsed' => FALSE,
    );
    $form['step_1']['title'] = array(
        '#type'         => 'textfield', 
        '#title'        => t('Title'), 
        '#description'  => t("Form title"),
        '#default_value'=> isset($values['title']) ? $values['title'] : NULL,
        '#size'         => 60, 
        '#maxlength'    => 128,
        '#required'     => TRUE,
    );
    $form['step_1']['success_text'] = array(
        '#type' => 'textfield', 
        '#title' => t('Success Text'), 
        '#default_value' => isset($values['success_text']) ? $values['success_text'] : "The form was processed correctly",
        '#description'  => t('Text displayed when the form is processed correctly.'), 
        '#size' => 60, 
        '#maxlength' => 400,
        '#required' => TRUE,
    );
    $form['step_1']['urlapi'] = array(
        '#type' => 'textfield', 
        '#title' => t('URL for API REST'), 
        '#description'  => t('URL where POST form results.'),
        '#default_value' => isset($values['urlapi']) ? $values['urlapi'] : NULL,
        '#size' => 100, 
        '#maxlength' => 800,
        '#required' => FALSE,
    );
    $form['step_1']['toemails'] = array(
        '#type' => 'textfield', 
        '#title' => t('Emails'), 
        '#description'  => t('Comma-separated emails list where send form results.'),
        '#default_value' => isset($values['toemails']) ? $values['toemails'] : NULL,
        '#size' => 100, 
        '#maxlength' => 800,
        '#required' => FALSE,
    );

    $form['step_1']['submit'] = array(
        '#type'     =>  'submit', 
        '#value'    =>  t('Next'),
    );
    /* End add */ 
    
    return $form;
}


function gcaba_drupal_form_forms_move_to_next_stage($form, &$form_state) {
	dpm("gcaba_drupal_form_forms_move_to_next_stage");
	switch ($form_state['stage']) {
		case 'step_1':
			return 'step_2';
			break;

		case 'step_2':
			return 'step_3';
			break;
	}

}


function gcaba_drupal_form_forms_move_to_previous_stage($form, &$form_state) {
	dpm("gcaba_drupal_form_forms_move_to_previous_stage");
	switch ($form_state['stage']) {
		case 'step_2':
			return 'step_1';
			break;

		case 'step_3':
			return 'step_2';
			break;
	}
	 
}


function gcaba_drupal_form_forms_submit($form, &$form_state){
	dpm("gcaba_drupal_form_forms_submit");
	switch ($form_state['stage']) {
		case 'step_3':
			return gcaba_drupal_form_forms_step_3_submit($form, $form_state);
			break;
		case 'personal_details':
			$form_state['multistep_values'][$form_state['stage']] = $form_state['values'];
			if ($form_state['triggering_element']['#value'] != 'Back') {
				customer_survey_personal_details_submit($form, $form_state);
				$form_state['complete'] = TRUE;
			}
			break;
	
		default:
			$form_state['multistep_values'][$form_state['stage']] = $form_state['values'];
			$form_state['new_stage'] = gcaba_drupal_form_forms_move_to_next_stage($form, $form_state);
			break;
	
	}
	
	if (isset($form_state['complete'])) drupal_goto('complete-page');
	 
	if ($form_state['triggering_element']['#value'] == t('Back')) {
		$form_state['new_stage'] = gcaba_drupal_form_forms_move_to_previous_stage($form, $form_state);
	}
	
	if (isset($form_state['multistep_values']['form_build_id'])) {
		$form_state['values']['form_build_id'] = $form_state['multistep_values']['form_build_id'];
	}
	$form_state['multistep_values']['form_build_id'] = $form_state['values']['form_build_id'];
	$form_state['stage'] = $form_state['new_stage'];
	$form_state['rebuild'] = TRUE;
}


function gcaba_drupal_form_forms_validate($form, &$form_state) {
	dpm("gcaba_drupal_form_forms_validate --> ". $form_state['stage']);

  if ($form_state['triggering_element']['#value'] == t('Back')) {
    return;
  }  
     
  switch ($form_state['stage']) { 
       
    case 'step_1':
      return gcaba_drupal_form_forms_step_1_validate($form, $form_state);
     break;  
  
    case 'step_2': 
      return gcaba_drupal_form_forms_step_2_validate($form, $form_state);  
     break;

     case 'step_3':
     	return gcaba_drupal_form_forms_step_3_validate($form, $form_state);
     	break;
  }
  
}

/**
 * Multistep ABM
 */
function gcaba_drupal_form_forms($form, &$form_state){
	dpm("gcaba_drupal_form_forms --> ". $form_state['stage']);	
    global $user;
    
    if (!isset($form_state['stage'])){ 
    	$form_state['stage'] = 'step_1';
    }else{
    	if ($form_state['triggering_element']['#id'] == 'add_fields') {
    		$form_state['stage'] = 'step_3';
    	}	
    }

    $form['#attributes']['enctype'] = 'multipart/form-data';
    $form['#id'] = 'form_list';
    $form['actions'] = array('#type' => 'actions');

    switch ($form_state['stage']) {
        case "step_1":
            return gcaba_drupal_form_forms_step_1($form, $form_state);
            break;
        case "step_2":
            return gcaba_drupal_form_forms_step_2($form, $form_state);
           	break;
        case "step_3":
           	return gcaba_drupal_form_forms_step_3($form, $form_state);
           	break;
        default:
            return gcaba_drupal_form_forms($form, $form_state);
            break; 
    }
}

/**
 * Implementa hook_menu().
 */
function gcaba_drupal_form_menu(){
    // Forms
    $items['admin/structure/gcaba_drupal_form/forms'] = array(
        'title'             => t('Forms'),
        'description'       => t('Manage forms from GCABA Forms'),
        'page callback'     => 'drupal_get_form',
        'page arguments'    => array('gcaba_drupal_form_forms'),
        'access arguments'  => array('administer site configuration'),
    );


/*


    // Autocomplete for fields
    $items['fields/autocomplete'] = array(
        'title' => t('Fields s Autocompleter'),
        'page callback' => '_fields_autocomplete',
        'access callback' => true, //TODO: Verify access
        'type' => MENU_CALLBACK
    );
    
    // General configuration block
	$items['admin/config/gcaba_drupal_form'] = array(
        'title' => t('Manage forms'),
        'position' => 'left',
        'weight' => -10,
        'page callback' => 'system_admin_menu_block_page',
        'access arguments' => array('access administration pages'),
        'file path' => drupal_get_path('module', 'system'),
        'file' => 'system.admin.inc',
	);

    // General configuration menu
	$items['admin/config/gcaba_drupal_form/administer'] = array(
        'access arguments' => array('administer site configuration'),
        'description' => t('Global forms configuration'),
        'page callback' => 'drupal_get_form',
        'page arguments' => array('gcaba_drupal_form_admin'),
        'title' => t('Forms configuration'),
        'weight' => 10,
    );

    // Fields
    $items['admin/structure/gcaba_drupal_form/fields'] = array(
        'access arguments' => array('administer site configuration'),
        'description' => t('Manage fields'),
        'page callback' => 'drupal_get_form',
        'page arguments' => array('gcaba_drupal_form_admin_fields'),
        'title' => t('Fields'),
        'weight' => 10,
    );

    // Add form
    $items['admin/structure/gcaba_drupal_form/forms/add'] = array(
        'access arguments' => array('administer site configuration'),
        'description' => t('Create new form'),
        'page callback' => 'drupal_get_form',
        'page arguments' => array('gcaba_drupal_form_admin_forms_add'),
        'title' => t('Create new form'),
        'weight' => 10,
    );

	$items['admin/gcaba_drupal_form/drupal_gcaba_do'] = array(
        'access arguments' => array('administer site configuration'),
        'page callback' => 'gcaba_',
        'page arguments' => array(),
    );
   */ 
    return $items;
}

/**
 * Implementa hook_admin().
 */
function gcaba_drupal_form_admin(){
    $html = '<h2>'.t('No settings, yet').'</h2>';
    $form['fields']['fields_table'] = array(
        '#markup' => $html,
    );

    return $form;
}
