<?php

/* put all view hook implementations here */

/* expose our custom tables to VIEWS */
/* implements 'hook_views_data */
function hamster_views_data() {
  $data = array();
  
  /* information for views user interface, describing the table */
  $data['hamster']['table'] = array(
    'group' => t('Hamster'),
    'title' => t('Hamster Information'),
    'help' => t('List information about hamsters'),
  );
  
  /* tell views that this is a base table */
  $data['hamster']['table']['base'] = array(
    'field' => 'id',
    'title' => t('Hamsters'),
    'help' => t('Information about hamsters.'),
  );
  
  /* expose hamster.id field */
  $data['hamster']['id'] = array(
        'title' => t('ID'),
        'help' => t('The ID of the hamster.'),  
        'field' => array(
          'handler' => 'views_handler_field_numeric',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
        ),
  );
  
   /* expose hamster.name field */
  $data['hamster']['name'] = array(
        'title' => t('Name'),
        'help' => t('The name of the hamster.'),  
        'field' => array(
          'handler' => 'views_handler_field', /* use for strings */
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
  );
  
  /* expose hamster.gender field */
  $data['hamster']['gender'] = array(
        'title' => t('Gender'),
        'help' => t('The gender of the hamster.'),  
        'field' => array(
          'handler' => 'views_handler_field', /* use for strings */
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
  );
  
  /* expose hamster.weight field */
  $data['hamster']['weight'] = array(
        'title' => t('Weight'),
        'help' => t('The weight of the hamster.'),  
        'field' => array(
          'handler' => 'views_handler_field_numeric',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
        ),
  );
  
  /* expose hamster.birthdate field */
  $data['hamster']['birthdate'] = array(
        'title' => t('Birth Date'),
        'help' => t('The birth date of the hamster.'),  
        'field' => array(
          'handler' => 'views_handler_field_date',  /* use for date */
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_date',
        ),
  );
    
  /* expose hamster.image field */
  $data['hamster']['image'] = array(
        'title' => t('image'),
        'help' => t('The image File ID of the hamster.'),  
        'field' => array(
          'handler' => 'views_handler_field',  
        ),
  );
  
  /* expose hamster.habitat_id field */
  $data['hamster']['habitat_id'] = array(
        'title' => t('Habitat ID'),
        'help' => t('The habitat ID of the hamster.'),  
        'field' => array(
          'handler' => 'views_handler_field',
        ),
  );
  
  return $data;
}