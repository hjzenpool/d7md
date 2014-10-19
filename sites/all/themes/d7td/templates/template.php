<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* this function overrides node_recent_content */

function d7td_node_recent_content($variables) {
  $node = $variables['node'];
  
  $output = '<div class="node-title">';
  $output .= l($node->title, 'node/' . $node->nid);
  $output .= theme('mark', array('type' => node_mark($node->nid, $node->changed)));
  $output .= '<div><dif class="node-author">';
  
  // original way:
  //$output .= theme('username', array('account' => user_load($node->uid)));

  /* updated to pass 'extra' theme 'username' */
  // then we don't need to override the username theme.
  $account = user_load($node->uid);
  $output .= theme('username', array('account' => $account ));
  $output .= '</div>';
  $output .= '<div class="node-created">';
  $output .= format_date($node->created);
  $output .= '</div>';

  return $output;
}

function d7td_mark($variables) {
  $type = $variables('type');
  global $user;
  if ($user->uid) {
    if ($type == MARK_NEW) {
      return ' <span class="marker">**</span>';
    }
    elseif ($type == MARK_UPDATED) {
      return ' <span class="marker">*</span>';
    }
  }
}


/**
 * copied from includes/theme.inc, line 2222
 * renamed theme_username to d7dt_username
 * NOTE: affects everywhere that username is displayed
 * NOTE: this was commented out since we pass 'extra' to standard username theme.
 * NOTE: check comment discussion in the function documentation on the API
 * 
 * Returns HTML for a username, potentially linked to the user's page.
 *
 * @param $variables
 *   An associative array containing:
 *   - account: The user object to format.
 *   - name: The user's name, sanitized.
 *   - extra: Additional text to append to the user's name, sanitized.
 *   - link_path: The path or URL of the user's profile page, home page, or
 *     other desired page to link to for more information about the user.
 *   - link_options: An array of options to pass to the l() function's $options
 *     parameter if linking the user's name to the user's page.
 *   - attributes_array: An array of attributes to pass to the
 *     drupal_attributes() function if not linking to the user's page.
 *
 * @see template_preprocess_username()
 * @see template_process_username()
 */
/*
function d7dt_username($variables) {
  if (isset($variables['link_path'])) {
    // We have a link path, so we should generate a link using l().
    // Additional classes may be added as array elements like
    // $variables['link_options']['attributes']['class'][] = 'myclass';
    $output = l($variables['name'] . $variables['extra'], $variables['link_path'], $variables['link_options']);
  }
  else {
    // Modules may have added important attributes so they must be included
    // in the output. Additional classes may be added as array elements like
    // $variables['attributes_array']['class'][] = 'myclass';
    $output = '<span' . drupal_attributes($variables['attributes_array']) . '>' . $variables['name'] . $variables['extra'] . '</span>';
  }
  
    // CUSTOM CODE: //
    if (!empty($variables['account']->mail)) {
      $output .= ' (' . $variables['account']->mail . ' )';
    }
    return $output;
}
*/

/* example of PRE-PROCESS */
/* Drupal will call ALL preprocess functions, not like overriding templates  */
// this runs in addition to theme_preprocess_username
// here we just want to fix a bug that doesn't handle extra 
function d7td_preprocess_username(&$variables) {
   if (!empty($variables['account']->mail)) {
     $variables['extra'] .= ' (' . $variables['account']->mail . ')';
   } 
}

/* example of PROCESS */
// this gets called AFTER all preprocessing 
function d7td_process_username(&$variables) {
  $variables['extra'] = str_replace('@', '@NOSPAM.', $variables['extra']);
}

/* copied from template_preprocess_node */
/* this will be run AFTER template_preprocess_node */
/* use this to replace 'Submitted' with 'Posted' */
function d7td_preprocess_node(&$variables) {
 $node = $variables['node'];

 // Display post information only on certain node types.
  if (variable_get('node_submitted_' . $node->type, TRUE)) {
    $variables['submitted'] = t('Posted by !username on !datetime', array('!username' => $variables['name'], '!datetime' => $variables['date']));
  } 
}

/* preprocessing function for HTML */
function d7td_preprocess_html(&$variables) {
  if ($GLOBALS['user']->uid == 1) {
    // this is superadmin, so use special css in superadmin.css
    
    drupal_add_css(drupal_get_path('theme', 'd7td') . '/css/superadmin.css');
  }
}