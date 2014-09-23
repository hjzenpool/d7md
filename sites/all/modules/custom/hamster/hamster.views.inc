<?php

/* put all view hooks here */

/* expose our tables to VIEWS */
function hamster_views_data() {
  $data = array();
  
  $data['hamster']['table'] = array(
    'group' => t('Hamster'),
    'title' => t('Hamster Information'),
    'help' => t('List information')
  );
  
  return $data;
}