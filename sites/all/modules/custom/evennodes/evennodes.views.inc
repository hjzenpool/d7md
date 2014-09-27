<?php

/*
 * this file for views hook implementations
*/
function evennodes_views_query_alter(&$view, &$query) {
  //dpm($view);
 
  
  /* add new condition to 'where' clause 
   *    APPLIES ANYWHERE THAT NODES are listed
   */
  if ($view->base_table== 'node') {
    /* only want to affect node table */
    
    // example to only print node 5
    // $query->add_where(1, 'node.nid', 5);  /* 1 is the 'where group' in the query. only return node 5 */
      
    // add an expression to the query 
    $query->add_where_expression(1, 'node.nid %2 = 0'); /* only take even nodes (remainder / 2 is 0) */
  }
  
   dpm($query); /*/* NOTE: print AFTER our customization, to see this in the output */
}

/* pre_render happens AFTER query, but before results are rendered as HTML and displayed */
/* can change or reformat any of the results pre-render */
function evennodes_views_pre_render(&$view) {

  /* alter the results */
   
   /* make sure only alter the desired view */
   if ($view->name == 'node_list') {
     foreach ($view->result as $i => $r) {
       // as an example, just insert the word 'Title: ' before the real title
       $view->result[$i]->node_title = 'Title: ' . $r->node_title;
     }
   }
   
  /* dump results from view to see the change */
   dpm($view->result); 
}

/* post_render is after HTML has been rendered, and just before it is displayed */
/* maybe you need to scrape the HTML at the last minute */
function evennodes_views_post_render(&$view, &$output, &$cache) {
   if ($view->name == 'node_list') {
     
    /* wrap the HTML in a div tag that changes background color */
    $output = '<div style="background: #ff0">' . $output . '<div>';
    
    /* dump the HTML that will be displayed */
    dpm($output); 
   }
}