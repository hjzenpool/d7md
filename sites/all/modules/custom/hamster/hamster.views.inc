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
  
  /* tell views that this is a BASE table */
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
        'sort' => array(
          'handler' => 'views_handler_sort',
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
        'sort' => array(
          'handler' => 'views_handler_sort',
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
          'handler' => 'views_handler_filter_in_operator',  /* use this for a set of values (default: yes/no) */
          'options callback' => 'hamster_views_gender_options', /* function to return array of the options to be selected */
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
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
        'sort' => array(
          'handler' => 'views_handler_sort',
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
        'sort' => array(
          'handler' => 'views_handler_filter_date',
        ),   
  );
    
  /* expose hamster.image field */
  $data['hamster']['image'] = array(
        'title' => t('image'),
        'help' => t('The image File ID of the hamster.'),  
        'field' => array(
        'handler' => 'hamster_views_handler_field_image',  /* custom handler */  
         /* NOTE: convention is to put views handlers in includes/hamster_views_handler_field_image.inc */
        ),
       'relationship' => array(  /* relationship to field in another table */
          'label' => t('Image'),
          'base' => 'file_managed',  /* the other table it relates to */
          'base field' => 'fid',  /* file_managed.fid */
        ),
  );
  
  /* expose hamster.habitat_id field */
  $data['hamster']['habitat_id'] = array(
        'title' => t('Habitat ID'),
        'help' => t('The habitat of the hamster.'),  
        'field' => array(
          'handler' => 'views_handler_field',
        ),
    /* NOTE: this is where you could us a filter_in_operator
     * to specify callback that gets the list of Habitats from the database
     * (similar to gender, but dynamically)
     */
        'relationship' => array(  /* relationship to field in another table */
          'label' => t('Habitat'),
          'base' => 'hamster_habitat',  /* the other table it relates to */
          'base field' => 'id',  /* hamster_habitat.id */
        ),
  );
  
  /* Hamster Habitat table */
  /* make it available, but we do not add it as a BASE table */
  $data['hamster_habitat']['table'] = array(
    'group' => t('Hamster Habitat'),
    'title' => t('Hamster Habitat Information'),
    'help' => t('List information about hamster cages'),
  );
  
  /* expose hamster_habitat.id field */
  $data['hamster_habitat']['id'] = array(
        'title' => t('ID'),
        'help' => t('The ID of the hamster habitat.'),  
        'field' => array(
          'handler' => 'views_handler_field_numeric',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
        ),        
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
  );
  
   /* expose hamster_habitat.name field */
  $data['hamster_habitat']['name'] = array(
        'title' => t('Name'),
        'help' => t('The name of the hamster habitat.'),  
        'field' => array(
          'handler' => 'views_handler_field', /* use for strings */
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
  );
  
  /* expose hamster_habitat.capacity field */
  $data['hamster_habitat']['capacity'] = array(
        'title' => t('Capacity'),
        'help' => t('The capacity of the hamster habitat.'),  
        'field' => array(
          'handler' => 'views_handler_field_numeric',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
  );
  
  return $data;
}

/* callback to provide set of values for gender views_handler_filter_in_operator  */
function hamster_views_gender_options() {
  return array('male' => t('Male'), 'female' => t('Female'));
}