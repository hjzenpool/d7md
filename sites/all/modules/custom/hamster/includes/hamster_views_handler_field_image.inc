<?php

/* custom views handler for image */
/* you can extend and override an object */
/* definition of hamster_views_handler_field_image */
/* note, this name must match the field handler name
 * and the filename .inc
 *  
 * extends will bring in all the code and only customize those mentioned below
 */
class hamster_views_handler_field_image extends views_handler_field {
  
  /* this creates the default */
  function option_definition() {
    $options = parent::option_definition();
    $options['image_style'] = array('default' => '');
    return $options;
  }
  
  /* replace this from views_handler_field */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    
    /* check that image module is enabled */
    if (module_exists('image')) {
      $styles = image_styles(); /* retrieve list of available styles */
      $style_options = array('' => t('Full Size'));  /* add Full size */
      foreach ($styles as $style) {
        $style_options[$style['name']] = $style['name'];
      }
      
      /* create a form element */
      /* let user select image size to display */
      $form['image_style'] = array(
        '#title' => t('Image style'),
        '#description' => t('Choose an image style for the hamster images.'),
        '#type' => 'select',
        '#options' => $style_options,
        '#default_value' => $this->options['image_style'], /* default is the currently selected value */
      );
    }
  }
  
  /* NOTE: sometimes you only need to override the render function */
  /* replace this from views_handler_field */
  /* instead of rendering the id number, get the file and render the image */
  function render($values) {
    $output='';
    $image_fid = $this->get_value($values); /* retrieve fid value for the column */

    /* set the image variable and evaluate true succeeded */
    if ($image = file_load($image_fid)) { /* load file based on fid */
      
      /* check that image style has been enabled and that image module is still enabled */
      if ($this->options['image_style'] && module_exists('image')) {
        $output = theme('image_style', array('style_name' => $this->options['image_style'], 'path' => $image->uri));
      }
      else {
        /* dump full size image if no image style or image module not enabled */
        $output = theme('image', array('path' => $image->uri));
      }
    }
    
    return $output;
  }
}