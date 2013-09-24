<?php
/**
 * Delete Form
 */
function gcaba_drupal_form_form_delete($form, &$form_state, $id = NULL){
	gcaba_forms_forms_delete($id);
	//drupal_set_message(t('The entity %title has been deleted', array('%title' => $id->title)));
  	drupal_goto( 'admin/structure/gcaba_forms/forms');	
}

/**
 * Multistep ABM
 */
function gcaba_drupal_form_forms($form, &$form_state, $id = NULL){
	// TODO: Pasar a call_user_func_array
    global $user;

    if (!isset($form_state['stage'])){	
    	$form_state['stage'] = 'step_1';
    }else{
    	if ($form_state['triggering_element']['#id'] == 'add_new_field') {
    		$form_state['stage'] = 'step_3';
    	}
    	
    	if ($form_state['triggering_element']['#id'] == 'finish') {
    		drupal_goto( 'admin/structure/gcaba_forms/forms');
    	}
    }

    $form['#attributes']['enctype'] = 'multipart/form-data';
    $form['#id'] = 'form_list';
    $form['actions'] = array('#type' => 'actions');

    switch ($form_state['stage']) {
        case "step_1":
            return gcaba_drupal_form_forms_step_1($form, $form_state, $id);
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

function gcaba_drupal_form_forms_validate($form, &$form_state, $id = NULL) {
	// TODO: Pasar a call_user_func_array
  if ($form_state['triggering_element']['#value'] == t('Back')) {
    return;
  }  
     
  switch ($form_state['stage']) { 
       
    case 'step_1':
      return gcaba_drupal_form_forms_step_1_validate($form, $form_state, $id);
     break;  
  
    case 'step_2': 
      return gcaba_drupal_form_forms_step_2_validate($form, $form_state);  
     break;

     case 'step_3':
     	return gcaba_drupal_form_forms_step_3_validate($form, $form_state);
     	break;
  }
  
}

function gcaba_drupal_form_forms_submit($form, &$form_state){
	switch ($form_state['stage']) {
		case 'step_1':
			$entity = entity_get_controller('gcaba_forms_forms')->create();
			$entity = $form_state['values']['basic_entity'];
			$entity->title 			= $form_state['values']['title'];
    		$entity->success_text 	= $form_state['values']['success_text'];
    		$entity->emails 		= $form_state['values']['toemails'];
    		$entity->url 			= $form_state['values']['urlapi'];
    		field_attach_submit('gcaba_forms_forms', $entity, $form, $form_state);
    		$entity = gcaba_forms_forms_save($entity);

			$form_state['multistep_values'][$form_state['stage']] = $form_state['values'];
			$form_state['multistep_values']['form_entity_id'] = $entity->basic_id;
			$form_state['new_stage'] = gcaba_drupal_form_forms_move_to_next_stage($form, $form_state);
      		break;
      	case 'step_3':
			$entity = entity_get_controller('gcaba_forms_fields')->create();
			$form['basic_entity'] = array('#type' => 'value','#value' => $entity);
		    $entity = $form_state['values']['basic_entity'];
		    $entity->title 		= $form_state['values']['title'];
		    $entity->type 		= $form_state['values']['type'];
		    $entity->help 		= $form_state['values']['help'];
		    $entity->placeholder= $form_state['values']['placeholder'];
		    $entity->value 		= $form_state['values']['value'];
		    $entity->label 		= $form_state['values']['label'];
		    $entity->options 	= $form_state['values']['options'];
		    //$entity->order 	= $form_state['values']['order'];
		    field_attach_submit('gcaba_forms_fields', $entity, $form, $form_state);
		    $entity = gcaba_forms_fields_save($entity);
			
			$form_state['multistep_values'][$form_state['stage']] = $form_state['values'];
			$form_state['new_stage'] = gcaba_drupal_form_forms_move_to_next_stage($form, $form_state);
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

/**
 * Third step validate
 */
function gcaba_drupal_form_forms_step_3_validate($form, &$form_state){
}

/**
 * Third step
 */
function gcaba_drupal_form_forms_step_3($form, &$form_state){
	$values = isset($form_state['multistep_values']['step_3']) ? $form_state['multistep_values']['step_3'] : array();
	$entity = entity_get_controller('gcaba_forms_fields')->create();

  $form['basic_entity'] = array(
    '#type' => 'value',
    '#value' => $entity,
  );

  field_attach_form('gcaba_forms_fields', $entity, $form, $form_state);

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
			'#default_value'=> $entity->title,
			'#size'         => 40,
			'#maxlength'    => 128,
			'#required'     => TRUE,
	);
	$form['step_3']['type'] = array(
			'#type' => 'radios',
			'#title' => t('Type'),
			'#default_value' => $entity->type,
			'#options' => $field_types,
			'#description' => t('Field type.'),
			'#required'     => TRUE,
	);
	$form['step_3']['help'] = array(
			'#type'         => 'textfield',
			'#title'        => t('Help'),
			'#description'  => t("Help text for field"),
			'#default_value'=> $entity->help,
			'#size'         => 80,
			'#maxlength'    => 400,
			'#required'     => FALSE,
	);
	$form['step_3']['placeholder'] = array(
			'#type'         => 'textfield',
			'#title'        => t('Placeholder'),
			'#description'  => t("Placeholder"),
			'#default_value'=> $entity->placeholder,
			'#size'         => 80,
			'#maxlength'    => 400,
			'#required'     => FALSE,
	);
	$form['step_3']['value'] = array(
			'#type'         => 'textfield',
			'#title'        => t('Value'),
			'#description'  => t("Initial value"),
			'#default_value'=> $entity->value,
			'#size'         => 80,
			'#maxlength'    => 400,
			'#required'     => FALSE,
	);
	$form['step_3']['label'] = array(
			'#type'         => 'textfield',
			'#title'        => t('Label'),
			'#description'  => t("Label"),
			'#default_value'=> $entity->label,
			'#size'         => 40,
			'#maxlength'    => 400,
			'#required'     => FALSE,
	);
	$form['step_3']['order'] = array(
			'#type'         => 'textfield',
			'#title'        => t('Order'),
			'#description'  => t("Filds order"),
			'#default_value'=> "",
			'#size'         => 10,
			'#maxlength'    => 2,
			'#required'     => TRUE,
	);
	$form['step_3']['options'] = array(
			'#type'         => 'textarea',
			'#title'        => t('Options'),
			'#description'  => t("Field options."),
			'#default_value'=> $entity->options,
			'#required'     => FALSE,
	);
	$form['step_3']['submit']  = array(
			'#type'     =>  'submit',
			'#value'    =>  t('Create field'),
	);

	return $form;
}


function gcaba_drupal_form_forms_step_2_submit($form, &$form_state){
}

/**
 * Second step validate
 */
function gcaba_drupal_form_forms_step_2_validate($form, &$form_state){
	$entity = gcaba_forms_forms_load($basic_id = $form_state['multistep_values']['form_entity_id']);
    
    if ($form_state['triggering_element']['#id'] == 'del_field') {
    	// DELETE FIELD FROM FORM

		if (count($form_state['complete form']['step_2']['form_fields']['#value']) >= 1) {
			$tmp = unserialize($entity->fields);

			foreach ($form_state['complete form']['step_2']['form_fields']['#value'] as $key_tmp => $value_tmp) {
				$key = array_search($value_tmp, $tmp);
				if($key!==false){ unset($tmp[$key]); }
			}

			$entity->fields = serialize($tmp);
			$entity = gcaba_forms_forms_save($entity);
		}else{
			form_set_error('step_2', t('No field selected.'));
		}
	}
    
    if ($form_state['triggering_element']['#id'] == 'add_field') {
    	// ADD FIELD FROM FORM
    	if (empty($form_state['complete form']['available']['fields']['#value'])) {
    		form_set_error('step_2', t('Forms has not any field.'));
    	}else{
	    	if(empty($entity->fields)){
	    		$entity->fields = serialize(array($form_state['complete form']['available']['fields']['#value']));
	    	}else{
	    		$tmp = unserialize($entity->fields);
	    		if(array_search($form_state['complete form']['available']['fields']['#value'], $tmp) === false){
		    		array_push($tmp, $form_state['complete form']['available']['fields']['#value']);	    			
	    		}else{
	    			form_set_error('step_2', t('Field already added.'));
	    		}
	    		$entity->fields = serialize($tmp);
	    	}
			$entity = gcaba_forms_forms_save($entity);

    	}

    }	
	return $form;
}

/**
 * Second step
 */
function gcaba_drupal_form_forms_step_2($form, &$form_state){
	$values = isset($form_state['multistep_values']['step_2']) ? $form_state['multistep_values']['step_2'] : array();

	$header = array('title' =>  t('Title'));
	$rows = array();
	$rows_f = array();

	$entities = gcaba_forms_fields_load_multiple();

	if (!empty($entities)) {
		foreach ( $entities as $entity ) {
			$rows[$entity->basic_id] = array(
        		'title' => $entity->title);
    	}
	}

	$entity = gcaba_forms_forms_load($basic_id = $form_state['multistep_values']['form_entity_id']);

	if (!empty($entity)) {
		$fields = unserialize($entity->fields);
		if(!empty($fields)){
			foreach ( $fields as $field_id ) {
				$entity = gcaba_forms_fields_load($basic_id=$field_id);
				$rows_f[$entity->basic_id] = array(
        			'title' => $entity->title);
    		}
    	}
	}else{
		$rows_f = array();
	}

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
			'#header' => $header,
			'#options' => $rows_f,
			'#empty' => t('No fields yet.'),
			'#multiple' => TRUE,
	);

	$form['step_2']['del_field'] = array(
			'#type' => 'button',
			'#value' => t('Delete'),
			'#id'	=> 'del_field',
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
			'#header' => $header,
			'#options' => $rows,
			'#multiple' => FALSE,
			'#js_select' => FALSE,
			'#empty' => t('No available fields, please create one.'),
	);
	$form['available']['actions'] = array(
			'#type' => 'actions'
	);
	$form['available']['actions']['add_new_field'] = array(
			'#type' => 'button',
			'#value' => t('New field'),
			'#id'	=> 'add_new_field',
	);
	$form['available']['actions']['add_field'] = array(
			'#type' => 'button',
			'#value' => t('Add'),
			'#id'	=> 'add_field',
	);

	
	/* Actions */
	$form['actions'] = array(
			'#type' => 'actions'
	);
	$form['actions']['finish'] = array(
			'#type' => 'submit',
			'#value' => t('Finish'),
			'#id'	=> 'finish',
	);
	
	return $form;
}

/**
 * First step validate
 */
function gcaba_drupal_form_forms_step_1_validate($form, &$form_state, $id){
		
	if($form_state['values']['basic_entity']->basic_id === "0"){
		$gcaba_forms_forms = entity_load('gcaba_forms_forms');
	    foreach($gcaba_forms_forms as $entity){
			if($entity->title == $form_state['values']['title']){
				form_set_error('title', t('Form title already used.'));
			}
	    }
	}
}

/**
 * First step
 */
function gcaba_drupal_form_forms_step_1($form, &$form_state, $id = NULL){
	$values = isset($form_state['multistep_values']['step_1']) ? $form_state['multistep_values']['step_1'] : array();

	if($id === NULL){
		$entity = entity_get_controller('gcaba_forms_forms')->create();		
	}else{
		$entity = $id;
	}

	$form['basic_entity'] = array(
    	'#type' => 'value',
    	'#value' => $entity,
  	);

  	field_attach_form('gcaba_forms_forms', $entity, $form, $form_state);

    /* Forms list */
    $rows = array();

    $gcaba_forms_forms = entity_load('gcaba_forms_forms');
    foreach($gcaba_forms_forms as $node){
        $rows[] = array(
        	$node->title,
			l(t('Edit'), 'admin/structure/gcaba_forms/forms/'.$node->basic_id.'/edit') . " " . l(t('Delete'), 'admin/structure/gcaba_forms/forms/'.$node->basic_id.'/delete')
        );
    }

    $form['forms_table'] = array(
        '#markup' => theme_table(array(
            "header"    => array(
                t("Name"),
                t("Operations")
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
        '#default_value'=> $entity->title,
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

    return $form;
}

function gcaba_drupal_form_forms_move_to_next_stage($form, &$form_state) {
	switch ($form_state['stage']) {
		case 'step_1':
			return 'step_2';
			break;

		case 'step_2':
			return 'step_3';
			break;

		case 'step_3':
			return 'step_2';
			break;
	}

}

function gcaba_drupal_form_forms_move_to_previous_stage($form, &$form_state) {
	switch ($form_state['stage']) {
		case 'step_2':
			return 'step_1';
			break;

		case 'step_3':
			return 'step_2';
			break;
	}
	 
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
