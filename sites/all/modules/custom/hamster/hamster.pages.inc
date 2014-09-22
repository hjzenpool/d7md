<?php

/* code for user-facing pages */

/**
 * Hamster view page.
 */
function hamster_page($hamster) {
  return theme('hamster_info', array('hamster' => $hamster));
}

/**
 * Title callback for hamster view page.
 */
function hamster_page_title($hamster) {
  return $hamster->name;
}


/**
 * Page callback that lists all hamsters in the database.
 */
function hamster_list() {
  $output = '';
  
  $items_per_page = 10;
  $total = db_query("SELECT COUNT(*) FROM {hamster}")->fetchField();
  $page = pager_default_initialize($total, $items_per_page);
  
  $results = db_query_range("SELECT h.*, hh.name AS habitat_name FROM {hamster} h
                       LEFT JOIN {hamster_habitat} hh ON h.habitat_id = hh.id", $page * $items_per_page, $items_per_page);
  
  /* use file_load to load managed file */
  $rows = array();
  foreach ($results as $record) {
    $image = file_load($record->image);
    if (!empty($image)) {
      $image_thumbnail = theme('image_style', array('style_name' => 'thumbnail', 'path' => $image->uri));
    }
    else {
      $image_thumbnail = '';
    }
    
    /* create destination for edit, delete forms */
    $link_query = array('destination' => 'hamster');
    if (!empty($_GET['page'])) {
      /* this lets destination take you back to the same page in the list */
      /* _$GET takes any paramters from the URL */
      /* so we can get the page from the URL and use it in destination */
      $link_query['destination'] .= '?page=' . $_GET['page'];
    }
    $row = array(
      $record->id,
      l($record->name, 'hamster/' . $record->id),
      $record->gender,
      t('@weight g', array('@weight' => $record->weight)),
      format_date($record->birthdate, 'custom', 'Y-m-d'),
      $image_thumbnail,
      $record->habitat_name,
      /* View, Edit, Delete links */
      /* use L-function */
      /* link to hamster's record id */
      /* 
       * third param to L-function is options array, 
       * query key composes the variables in the URL after the '?'
       * ...?destination=hamster
       * in a form, if destination is in URL, it tells Drupal where to go after form is saved
       * link_query is array created above
      */
      l('View', 'hamster/' . $record->id) . ' - ' .
      l('Edit', 'hamster/' . $record->id . '/edit', array('query' => $link_query)) . ' - ' .
      l('Delete', 'hamster/' . $record->id . '/delete', array('query' => $link_query)),
    );
    
    $rows[] = $row;
  }
  
  $header = array(
    t('ID'),
    t('Name'),
    t('Gender'),
    t('Weight'),
    t('Birth Date'),
    t('Image'),
    t('Habitat'),
    t('Actions'),
  );
  
  $variables = array(
    'rows' => $rows,
    'header' => $header,
  );
  
  $output .= theme('table', $variables);
  $output .= theme('pager');
  
  return $output;
}

/*
 * Hamster add/edit form.
 * parameter hamster object is optional
 * for add, there is no hamster to edit 
 */
function hamster_edit_form($form, &$form_state, $hamster = NULL) {
  
  $form['id'] = array(
    '#type' => 'value',
    '#value' => isset($hamster->id) ? $hamster->id : NULL,
  );
  
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => isset($hamster->name) ? $hamster->name : NULL,
    '#requied' => TRUE,
  );
  
  $form['gender'] = array(
    '#type' => 'radios',
    '#title' => t('Gender'),
    '#options' => array('male' => t('Male'), 'female' => t('Female')),
    '#default_value' => isset($hamster->gender) ? $hamster->gender : NULL,
  );
  
  $form['weight'] = array(
    '#type' => 'textfield',
    '#title' => t('Weight'),
    '#field_suffix' => 'grams',
    '#size' => 5,
    '#default_value' => isset($hamster->weight) ? $hamster->weight : NULL,
  );
  
  
  if (isset($hamster->birthdate)) {
    $birthdate_default = array(
      'year' => date('Y', $hamster->birthdate),
      'month' => date('n', $hamster->birthdate),
      'day' => date('j', $hamster->birthdate),
    );
  }
  $form['birthdate'] = array(
    '#type' => 'date',
    '#title' => t('Birth Date'),
    '#default_value' => isset($birthdate_default) ? $birthdate_default : NULL,
  );
  
  $form['image'] = array(
    '#type' => 'managed_file',
    '#title' => t('Image'),
    '#upload_location' => 'public://hamster-images/',
    '#default_value' => isset($hamster->image) ? $hamster->image : NULL,
  );
  
  $habitats = db_query("SELECT id, name FROM {hamster_habitat}")->fetchAllKeyed(0);
  $habitats = array('' => '--Select a Habitat--') + $habitats;
  
  $form['habitat_id'] = array(
    '#type' => 'select',
    '#title' => t('Habitat'),
    '#options' => $habitats,
    '#default_value' => isset($hamster->habitat_id) ? $hamster->habitat_id : NULL,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Hamster'),
  );
  
  return $form;
}

/**
 * Submit handler for hamster add/edit form.
 */
function hamster_edit_form_submit($form, &$form_state) {
  $hamster = $form_state['values'];
  $hamster['birthdate'] = strtotime($hamster['birthdate']['year'] . '-' 
                                    . $hamster['birthdate']['month'] . '-' 
                                    . $hamster['birthdate']['day']);
  
  if (!empty($hamster['id'])) {
    drupal_write_record('hamster', $hamster, array('id'));
    drupal_set_message(t('Hamster %name updated.', array('%name' => $hamster['name'])));
  }
  else {
    drupal_write_record('hamster', $hamster);
    drupal_set_message(t('Hamster %name created.', array('%name' => $hamster['name'])));
  }
  
  $form_state['redirect'] = 'hamster/' . $hamster['id'];
}

/**
 * Hamster delete form. second param is required, which is the hamster object 
 */
function hamster_delete_form($form, &$form_state, $hamster) {
  $form['id'] = array(
    '#type' => 'value',
    '#value' => $hamster->id,
  );
  $form['name'] = array(
    '#type' => 'value',
    '#value' => $hamster->name,
  );
  return confirm_form($form, t('Are you sure you want to delete hamster %name?', array('%name' => $hamster->name)), 'hamster/' . $hamster->id);
}

/**
 * Hamster delete submit form.
 */
function hamster_delete_form_submit($form, &$form_state) {
  db_query("DELETE FROM {hamster} WHERE id = :id", array(':id' => $form_state['values']['id']));
  drupal_set_message(t('Hamster %name deleted.', array('%name' => $form_state['values']['name'])));
  $form_state['redirect'] = 'hamster';
}
