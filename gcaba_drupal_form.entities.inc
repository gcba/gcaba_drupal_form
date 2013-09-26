<?php

/**
 * Implements hook_entity_info().
 *
 * This is the fundamental description of the entity.
 *
 * It provides a single entity with a single bundle and without revision
 * support.
 */
function gcaba_drupal_form_entity_info() {
  $info['gcaba_forms_fields'] = array(
    // A human readable label to identify our entity.
    'label' => t('GCABA Forms Field'),

    // The controller for our Entity, extending the Drupal core controller.
    'controller class' => 'GCABAFormsFieldBasicController',

    // The table for this entity defined in hook_schema()
    'base table' => 'gcaba_forms_fields',

    // Returns the uri elements of an entity
    'uri callback' => 'gcaba_forms_fields_uri',

    // IF fieldable == FALSE, we can't attach fields.
    'fieldable' => TRUE,

    // entity_keys tells the controller what database fields are used for key
    // functions. It is not required if we don't have bundles or revisions.
    // Here we do not support a revision, so that entity key is omitted.
    'entity keys' => array(
      'id' => 'basic_id' , // The 'id' (basic_id here) is the unique id.
      'bundle' => 'bundle_type' // Bundle will be determined by the 'bundle_type' field
    ),
    'bundle keys' => array(
      'bundle' => 'bundle_type',
    ),

    // FALSE disables caching. Caching functionality is handled by Drupal core.
    'static cache' => TRUE,

    // Bundles are alternative groups of fields or configuration
    // associated with a base entity type.
    'bundles' => array(
      'gcaba_forms_fields_bundle' => array(
        'label' => 'GCABA Forms Field Bundle',
        // 'admin' key is used by the Field UI to provide field and
        // display UI pages.
        'admin' => array(
          'path' => 'admin/structure/gcaba_forms_fields/manage',
          'access arguments' => array('administer gcaba_forms_fields entities'),
        ),
      ),
    ),
    // View modes allow entities to be displayed differently based on context.
    // As a demonstration we'll support "Tweaky", but we could have and support
    // multiple display modes.
    'view modes' => array(
      'tweaky' => array(
        'label' => t('Tweaky'),
        'custom settings' =>  FALSE,
      ),
    )
  );

  $info['gcaba_forms_forms'] = array(
    // A human readable label to identify our entity.
    'label' => t('GCABA Forms Forms'),

    // The controller for our Entity, extending the Drupal core controller.
    'controller class' => 'GCABAFormsFormdBasicController',

    // The table for this entity defined in hook_schema()
    'base table' => 'gcaba_forms_forms',

    // Returns the uri elements of an entity
    'uri callback' => 'gcaba_forms_forms_uri',

    // IF fieldable == FALSE, we can't attach fields.
    'fieldable' => TRUE,

    // entity_keys tells the controller what database fields are used for key
    // functions. It is not required if we don't have bundles or revisions.
    // Here we do not support a revision, so that entity key is omitted.
    'entity keys' => array(
      'id' => 'basic_id' , // The 'id' (basic_id here) is the unique id.
      'bundle' => 'bundle_type' // Bundle will be determined by the 'bundle_type' field
    ),
    'bundle keys' => array(
      'bundle' => 'bundle_type',
    ),

    // FALSE disables caching. Caching functionality is handled by Drupal core.
    'static cache' => TRUE,

    // Bundles are alternative groups of fields or configuration
    // associated with a base entity type.
    'bundles' => array(
      'gcaba_forms_forms_bundle' => array(
        'label' => 'GCABA Forms Forms Bundle',
        // 'admin' key is used by the Field UI to provide field and
        // display UI pages.
        'admin' => array(
          'path' => 'admin/structure/gcaba_forms_forms/manage',
          'access arguments' => array('administer gcaba_forms_forms entities'),
        ),
      ),
    ),
    // View modes allow entities to be displayed differently based on context.
    // As a demonstration we'll support "Tweaky", but we could have and support
    // multiple display modes.
    'view modes' => array(
      'tweaky' => array(
        'label' => t('Tweaky'),
        'custom settings' =>  FALSE,
      ),
    )
  );

  return $info;
}

/**
 * Fetch a basic object.
 *
 * This function ends up being a shim between the menu system and
 * gcaba_forms_forms_load_multiple().
 *
 * This function gets its name from the menu system's wildcard
 * naming conventions. For example, /path/%wildcard would end
 * up calling wildcard_load(%wildcard value). In our case defining
 * the path: gcabaforms/entities/forms/%gcaba_forms_forms in
 * hook_menu() tells Drupal to call gcaba_forms_forms_load().
 *
 * @param $basic_id
 *   Integer specifying the basic entity id.
 * @param $reset
 *   A boolean indicating that the internal cache should be reset.
 * @return
 *   A fully-loaded $basic object or FALSE if it cannot be loaded.
 *
 * @see gcaba_forms_forms_load_multiple()
 * @see gcaba_drupal_form_menu()
 */
function gcaba_forms_forms_load($basic_id = NULL, $reset = FALSE) {
  $basic_ids = (isset($basic_id) ? array($basic_id) : array());
  $basic = gcaba_forms_forms_load_multiple($basic_ids, array(), $reset);
  return $basic ? reset($basic) : FALSE;
}

/**
 * Fetch a basic object.
 *
 * This function ends up being a shim between the menu system and
 * gcaba_forms_fields_load_multiple().
 *
 * This function gets its name from the menu system's wildcard
 * naming conventions. For example, /path/%wildcard would end
 * up calling wildcard_load(%wildcard value). In our case defining
 * the path: gcabaforms/entities/fields/%gcaba_forms_fields in
 * hook_menu() tells Drupal to call gcaba_forms_fields_load().
 *
 * @param $basic_id
 *   Integer specifying the basic entity id.
 * @param $reset
 *   A boolean indicating that the internal cache should be reset.
 * @return
 *   A fully-loaded $basic object or FALSE if it cannot be loaded.
 *
 * @see gcaba_forms_fields_load_multiple()
 * @see gcaba_drupal_form_menu()
 */
function gcaba_forms_fields_load($basic_id = NULL, $reset = FALSE) {
  $basic_ids = (isset($basic_id) ? array($basic_id) : array());
  $basic = gcaba_forms_fields_load_multiple($basic_ids, array(), $reset);
  return $basic ? reset($basic) : FALSE;
}

/**
 * Loads multiple basic entities.
 *
 * We only need to pass this request along to entity_load(), which
 * will in turn call the load() method of our entity controller class.
 */
function gcaba_forms_forms_load_multiple($basic_ids = FALSE, $conditions = array(), $reset = FALSE) {
  return entity_load('gcaba_forms_forms', $basic_ids, $conditions, $reset);
}

/**
 * Loads multiple basic entities.
 *
 * We only need to pass this request along to entity_load(), which
 * will in turn call the load() method of our entity controller class.
 */
function gcaba_forms_fields_load_multiple($basic_ids = FALSE, $conditions = array(), $reset = FALSE) {
  return entity_load('gcaba_forms_fields', $basic_ids, $conditions, $reset);
}

/**
 * Implements the uri callback.
 */
function gcaba_forms_fields_uri($basic) {
  return array(
    'path' => 'gcabaforms/entities/fields/' . $basic->basic_id,
  );
}

/**
 * Implements the uri callback.
 */
function gcaba_forms_forms_uri($basic) {
  return array(
    'path' => 'gcabaforms/entities/forms/' . $basic->basic_id,
  );
}

/**
 * Implements hook_permission().
 */
function gcaba_drupal_form_permission() {
  $permissions = array(
    'administer gcaba_forms_forms entities' =>  array(
      'title' => t('Administer GCABA Forms Forms'),
    ),
    'view any gcaba_forms_forms entity' => array(
      'title' => t('View any GCABA Forms Forms entity'),
    ),
    'edit any gcaba_forms_forms entity' => array(
      'title' => t('Edit any GCABA Forms Forms entity'),
    ),
    'create gcaba_forms_forms entities' => array(
      'title' => t('Create GCABA Forms Forms Entities'),
    ),
    'administer gcaba_forms_fields entities' =>  array(
      'title' => t('Administer GCABA Forms Field'),
    ),
    'view any gcaba_forms_fields entity' => array(
      'title' => t('View any GCABA Forms Field entity'),
    ),
    'edit any gcaba_forms_fields entity' => array(
      'title' => t('Edit any GCABA Forms Field entity'),
    ),
    'create gcaba_forms_fields entities' => array(
      'title' => t('Create GCABA Forms Field Entities'),
    ),
  );
  return $permissions;
}

/**
 * Returns a render array with all gcaba_forms_forms entities.
 *
 * In this basic example we know that there won't be many entities,
 * so we'll just load them all for display. See pager_example.module
 * to implement a pager. Most implementations would probably do this
 * with the contrib Entity API module, or a view using views module,
 * but we avoid using non-core features in the Examples project.
 *
 * @see pager_example.module
 */
function gcaba_forms_forms_list_entities() {
  $content = array();
  // Load all of our entities.
  $entities = gcaba_forms_forms_load_multiple();
  if (!empty($entities)) {
    foreach ( $entities as $entity ) {
      // Create tabular rows for our entities.
      $rows[] = array(
        'data' => array(
          'id' => $entity->basic_id,
          'title' => l($entity->title, 'gcabaforms/entities/forms/' . $entity->basic_id),
          'bundle' => $entity->bundle_type,
        ),
      );
    }
    // Put our entities into a themed table. See theme_table() for details.
    $content['entity_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => array(t('ID'), t('Title'), t('Bundle')),
    );
  }
  else {
    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('No GCABA Forms Form currently exist.'),
    );
  }
  return $content;
}

/**
 * Callback for a page title when this entity is displayed.
 */
function gcaba_forms_forms_title($entity) {
  return t('@title', array('@title' => $entity->title));
}

/**
 * Callback for a page title when this entity is displayed.
 */
function gcaba_forms_fields_title($entity) {
  return t('@title', array('@title' => $entity->title));
}

/**
 * Menu callback to display an entity.
 *
 * As we load the entity for display, we're responsible for invoking a number
 * of hooks in their proper order.
 *
 * @see hook_entity_prepare_view()
 * @see hook_entity_view()
 * @see hook_entity_view_alter()
 */
function gcaba_forms_fields_view($entity, $view_mode = 'tweaky') {
  // Our entity type, for convenience.
  $entity_type = 'gcaba_forms_fields';
  // Start setting up the content.
  $entity->content = array(
    '#view_mode' => $view_mode,
  );
  // Build fields content - this is where the Field API really comes in to play.
  // The task has very little code here because it all gets taken care of by
  // field module.
  // field_attach_prepare_view() lets the fields load any data they need
  // before viewing.
  field_attach_prepare_view($entity_type, array($entity->basic_id => $entity),
    $view_mode);
  // We call entity_prepare_view() so it can invoke hook_entity_prepare_view()
  // for us.
  entity_prepare_view($entity_type, array($entity->basic_id => $entity));
  // Now field_attach_view() generates the content for the fields.
  $entity->content += field_attach_view($entity_type, $entity, $view_mode);

  // OK, Field API done, now we can set up some of our own data.
  $entity->content['created'] = array(
    '#type' => 'item',
    '#title' => t('Created date'),
    '#markup' => format_date($entity->created),
  );
  $entity->content['title'] = array(
    '#type' => 'item',
    '#title' => t('Title'),
    '#markup' => $entity->title,
  );

  // Now to invoke some hooks. We need the language code for
  // hook_entity_view(), so let's get that.
  global $language ;
  $langcode = $language->language ;
  // And now invoke hook_entity_view().
  module_invoke_all('entity_view', $entity, $entity_type, $view_mode,
    $langcode);
  // Now invoke hook_entity_view_alter().
  drupal_alter(array('gcaba_forms_fields_view', 'entity_view'),
    $entity->content, $entity_type);

  // And finally return the content.
  return $entity->content;
}

/**
 * Menu callback to display an entity.
 *
 * As we load the entity for display, we're responsible for invoking a number
 * of hooks in their proper order.
 *
 * @see hook_entity_prepare_view()
 * @see hook_entity_view()
 * @see hook_entity_view_alter()
 */
function gcaba_forms_forms_view($entity, $view_mode = 'tweaky') {
  // Our entity type, for convenience.
  $entity_type = 'gcaba_forms_forms';
  // Start setting up the content.
  $entity->content = array(
    '#view_mode' => $view_mode,
  );
  // Build fields content - this is where the Field API really comes in to play.
  // The task has very little code here because it all gets taken care of by
  // field module.
  // field_attach_prepare_view() lets the fields load any data they need
  // before viewing.
  field_attach_prepare_view($entity_type, array($entity->basic_id => $entity),
    $view_mode);
  // We call entity_prepare_view() so it can invoke hook_entity_prepare_view()
  // for us.
  entity_prepare_view($entity_type, array($entity->basic_id => $entity));
  // Now field_attach_view() generates the content for the fields.
  $entity->content += field_attach_view($entity_type, $entity, $view_mode);

  // OK, Field API done, now we can set up some of our own data.
  $entity->content['created'] = array(
    '#type' => 'item',
    '#title' => t('Created date'),
    '#markup' => format_date($entity->created),
  );
  $entity->content['title'] = array(
    '#type' => 'item',
    '#title' => t('Title'),
    '#markup' => $entity->title,
  );

  // Now to invoke some hooks. We need the language code for
  // hook_entity_view(), so let's get that.
  global $language ;
  $langcode = $language->language ;
  // And now invoke hook_entity_view().
  module_invoke_all('entity_view', $entity, $entity_type, $view_mode,
    $langcode);
  // Now invoke hook_entity_view_alter().
  drupal_alter(array('gcaba_forms_forms_view', 'entity_view'),
    $entity->content, $entity_type);

  // And finally return the content.
  return $entity->content;
}

/**
 * Implements hook_field_extra_fields().
 *
 * This exposes the "extra fields" (usually properties that can be configured
 * as if they were fields) of the entity as pseudo-fields
 * so that they get handled by the Entity and Field core functionality.
 * Node titles get treated in a similar manner.
 */
function gcaba_drupal_form_field_extra_fields() {
  $form_elements['title'] = array(
    'label' => t('Title'),
    'description' => t('Title'),
    'weight' => -5,
  );
  $display_elements['created'] = array(
    'label' => t('Creation date'),
    'description' => t('Creation date (an extra display field)'),
    'weight' => 0,
  );
  $display_elements['title'] = array(
    'label' => t('Title'),
    'description' => t('Just like title, but trying to point out that it is a separate property'),
    'weight' => 0,
  );

  // Since we have only one bundle type, we'll just provide the extra_fields
  // for it here.
  $extra_fields['gcaba_forms_forms']['gcaba_forms_forms_bundle']['form'] = $form_elements;
  $extra_fields['gcaba_forms_forms']['gcaba_forms_forms_bundle']['display'] = $display_elements;

  $extra_fields['gcaba_forms_fields']['gcaba_forms_fields_bundle']['form'] = $form_elements;
  $extra_fields['gcaba_forms_fields']['gcaba_forms_fields_bundle']['display'] = $display_elements;

  return $extra_fields;
}

/**
 * We save the entity by calling the controller.
 */
function gcaba_forms_fields_save(&$entity) {
  return entity_get_controller('gcaba_forms_fields')->save($entity);
}

/**
 * We save the entity by calling the controller.
 */
function gcaba_forms_forms_save(&$entity) {
  return entity_get_controller('gcaba_forms_forms')->save($entity);
}

/**
 * Use the controller to delete the entity.
 */
function gcaba_forms_fields_delete($entity) {
  entity_get_controller('gcaba_forms_fields')->delete($entity);
}

/**
 * Use the controller to delete the entity.
 */
function gcaba_forms_forms_delete($entity) {
  entity_get_controller('gcaba_forms_forms')->delete($entity);
}

/**
 * GCABAFormsFieldBasicControllerInterface definition.
 *
 * We create an interface here because anyone could come along and
 * use hook_entity_info_alter() to change our controller class.
 * We want to let them know what methods our class needs in order
 * to function with the rest of the module, so here's a handy list.
 *
 * @see hook_entity_info_alter()
 */

interface GCABAFormsFieldBasicControllerInterface
  extends DrupalEntityControllerInterface {
  public function create();
  public function save($entity);
  public function delete($entity);
}

/**
 * GCABAFormsFormdBasicControllerInterface definition.
 *
 * We create an interface here because anyone could come along and
 * use hook_entity_info_alter() to change our controller class.
 * We want to let them know what methods our class needs in order
 * to function with the rest of the module, so here's a handy list.
 *
 * @see hook_entity_info_alter()
 */

interface GCABAFormsFormdBasicControllerInterface
  extends DrupalEntityControllerInterface {
  public function create();
  public function save($entity);
  public function delete($entity);
}

/**
 * GCABAFormsFieldBasicController extends DrupalDefaultEntityController.
 *
 * Our subclass of DrupalDefaultEntityController lets us add a few
 * important create, update, and delete methods.
 */
class GCABAFormsFieldBasicController
  extends DrupalDefaultEntityController
  implements GCABAFormsFieldBasicControllerInterface {

  /**
   * Create and return a new gcaba_forms_fields entity.
   */
  public function create() {
    $entity = new stdClass();
    $entity->type = 'gcaba_forms_fields';
    $entity->basic_id = 0;
    $entity->bundle_type = 'gcaba_forms_fields_bundle';
    $entity->title = '';
    $entity->help = '';
    $entity->placeholder = '';
    $entity->value = '';
    $entity->label = '';
    $entity->validators = '';
    $entity->options = '';
    return $entity;
  }

  /**
   * Saves the custom fields using drupal_write_record()
   */
  public function save($entity) {
    // If our entity has no basic_id, then we need to give it a
    // time of creation.
    if (empty($entity->basic_id)) {
      $entity->created = time();
    }
    // Invoke hook_entity_presave().
    module_invoke_all('entity_presave', $entity, 'gcaba_forms_fields');
    // The 'primary_keys' argument determines whether this will be an insert
    // or an update. So if the entity already has an ID, we'll specify
    // basic_id as the key.
    $primary_keys = $entity->basic_id ? 'basic_id' : array();
    // Write out the entity record.
    drupal_write_record('gcaba_forms_fields', $entity, $primary_keys);
    // We're going to invoke either hook_entity_update() or
    // hook_entity_insert(), depending on whether or not this is a
    // new entity. We'll just store the name of hook_entity_insert()
    // and change it if we need to.
    $invocation = 'entity_insert';
    // Now we need to either insert or update the fields which are
    // attached to this entity. We use the same primary_keys logic
    // to determine whether to update or insert, and which hook we
    // need to invoke.
    if (empty($primary_keys)) {
      field_attach_insert('gcaba_forms_fields', $entity);
    }
    else {
      field_attach_update('gcaba_forms_fields', $entity);
      $invocation = 'entity_update';
    }
    // Invoke either hook_entity_update() or hook_entity_insert().
    module_invoke_all($invocation, $entity, 'gcaba_forms_fields');
    return $entity;
  }

  /**
   * Delete a single entity.
   *
   * Really a convenience function for delete_multiple().
   */
  public function delete($entity) {
    $this->delete_multiple(array($entity));
  }

  /**
   * Delete one or more gcaba_forms_fields entities.
   *
   * Deletion is unfortunately not supported in the base
   * DrupalDefaultEntityController class.
   *
   * @param $basic_ids
   *   An array of entity IDs or a single numeric ID.
   */
  public function delete_multiple($entities) {
    $basic_ids = array();
    if (!empty($entities)) {
      $transaction = db_transaction();
      try {
        foreach ($entities as $entity) {
          // Invoke hook_entity_delete().
          module_invoke_all('entity_delete', $entity, 'gcaba_forms_fields');
          field_attach_delete('gcaba_forms_fields', $entity);
          $basic_ids[] = $entity->basic_id;
        }
        db_delete('gcaba_forms_fields')
          ->condition('basic_id', $basic_ids, 'IN')
          ->execute();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('gcaba_drupal_form', $e);
        throw $e;
      }
    }
  }
}

/**
 * GCABAFormsFormdBasicController extends DrupalDefaultEntityController.
 *
 * Our subclass of DrupalDefaultEntityController lets us add a few
 * important create, update, and delete methods.
 */
class GCABAFormsFormdBasicController
  extends DrupalDefaultEntityController
  implements GCABAFormsFormdBasicControllerInterface {

  /**
   * Create and return a new gcaba_forms_forms entity.
   */
  public function create() {
    $entity = new stdClass();
    $entity->type = 'gcaba_forms_forms';
    $entity->basic_id = 0;
    $entity->bundle_type = 'gcaba_forms_forms_bundle';
    $entity->title = '';
    $entity->success_text = '';
    $entity->emails = '';
    $entity->url = '';
    return $entity;
  }

  /**
   * Saves the custom fields using drupal_write_record()
   */
  public function save($entity) {
    // If our entity has no basic_id, then we need to give it a
    // time of creation.
    if (empty($entity->basic_id)) {
      $entity->created = time();
    }
    // Invoke hook_entity_presave().
    module_invoke_all('entity_presave', $entity, 'gcaba_forms_forms');
    // The 'primary_keys' argument determines whether this will be an insert
    // or an update. So if the entity already has an ID, we'll specify
    // basic_id as the key.
    $primary_keys = $entity->basic_id ? 'basic_id' : array();
    // Write out the entity record.
    drupal_write_record('gcaba_forms_forms', $entity, $primary_keys);
    // We're going to invoke either hook_entity_update() or
    // hook_entity_insert(), depending on whether or not this is a
    // new entity. We'll just store the name of hook_entity_insert()
    // and change it if we need to.
    $invocation = 'entity_insert';
    // Now we need to either insert or update the fields which are
    // attached to this entity. We use the same primary_keys logic
    // to determine whether to update or insert, and which hook we
    // need to invoke.
    if (empty($primary_keys)) {
      field_attach_insert('gcaba_forms_forms', $entity);
    }
    else {
      field_attach_update('gcaba_forms_forms', $entity);
      $invocation = 'entity_update';
    }
    // Invoke either hook_entity_update() or hook_entity_insert().
    module_invoke_all($invocation, $entity, 'gcaba_forms_forms');
    return $entity;
  }

  /**
   * Delete a single entity.
   *
   * Really a convenience function for delete_multiple().
   */
  public function delete($entity) {
    $this->delete_multiple(array($entity));
  }

  /**
   * Delete one or more gcaba_forms_forms entities.
   *
   * Deletion is unfortunately not supported in the base
   * DrupalDefaultEntityController class.
   *
   * @param $basic_ids
   *   An array of entity IDs or a single numeric ID.
   */
  public function delete_multiple($entities) {
    $basic_ids = array();
    if (!empty($entities)) {
      $transaction = db_transaction();
      try {
        foreach ($entities as $entity) {
          // Invoke hook_entity_delete().
          module_invoke_all('entity_delete', $entity, 'gcaba_forms_forms');
          field_attach_delete('gcaba_forms_forms', $entity);
          $basic_ids[] = $entity->basic_id;
        }
        db_delete('gcaba_forms_forms')
          ->condition('basic_id', $basic_ids, 'IN')
          ->execute();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('gcaba_drupal_form', $e);
        throw $e;
      }
    }
  }
}
