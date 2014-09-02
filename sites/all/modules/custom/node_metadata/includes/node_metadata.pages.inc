<?php

/* 
 * this file contains user-facing callbacks
 */

/* argument is the node id */
function node_metadata_page($node) {
  /* $node = node_load($nid); */ /* not needed if pass fully loaded node */
  
  /* return t('Node ID is @nid' . array('@nid' => $nid)); */  /* simple way just return node id */
  /* dpm($node); */ /* dump all variables */
  $output = '';  
  $output .= '<div><label>Author:<label> ' . $node->name . '</div>';
  $output .= '<div><label>Created:<label> ' . format_date($node->created) . '</div>';
  $output .= '<div><label>Updated:<label> ' . format_date($node->changed) . '</div>';
  $output .= '<div><label>Comment Count:<label> ' . $node->comment_count . '</div>';
        
  return $output;
}