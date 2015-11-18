<?php

//list files with same title only 1 time.
function springfiles_views_pre_render(&$view) {
  if ($view->name == "categories") {
       /* The nice stuff */
      $new = array();
      $exclude = array("");
      for ($i = 0; $i<=count($view->result)-1; $i++) {
         if (!in_array(trim($view->result[$i]->node_title) ,$exclude))
	  {
	    $new[] = $view->result[$i];
	    $exclude[] = trim($view->result[$i]->node_title);
	  }
      }
     $view->result = $new;
      // $new is our filtered array with only the latest version of a file
  }
  if ($view->name == "last_downloaded") {
       /* The nice stuff */
      $new = array();
      $exclude = array("");
      for ($i = 0; $i<=count($view->result)-1; $i++) {
         if ($view->result[$i+1]->download_count_timestamp == $view->result[$i]->download_count_timestamp &&
	     $view->result[$i+1]->node_title == $view->result[$i]->node_title)
	  { 	  }
	  else {
	    $new[] = $view->result[$i];
	  }
      }
     $view->result = $new;
      // $new is our filtered array with only the unique last downloads
  }
}

//change the textfield into a dropdown in exposed view filters
function springfiles_form_views_exposed_form_alter(&$form, $form_state)
{
  if (($form['#id'] == 'views-exposed-form-latest-page-4' || $form['#id'] == 'views-exposed-form-front-block-2' || $form['#id'] == 'views-exposed-form-categories-block-1' || $form['#id'] == 'views-exposed-form-categories-block-4') && drupal_get_path_alias($_GET["q"]) != 'spring/spring-maps' && drupal_get_path_alias($_GET["q"]) != 'online-games')
  {
    $content_field = content_fields('field_freeware'); // CCK field we want to filter on
    $allowed_values = content_allowed_values($content_field);
    
    $db_info = content_database_info($content_field);
    $result = db_query("SELECT DISTINCT " . $db_info['columns']['value']['column'] . " FROM {" . $db_info['table'] . "}");
    
    $options["All"] = "<Any>";
    while($row = db_fetch_array($result)) {
      $key = $row[$db_info['columns']['value']['column']];
      $options[$key] = $allowed_values[$key];
    }
    asort($options);
    $field = &$form['field_freeware_value']; 
    $field['#type'] = "select";
    $field['#options'] = $options;
    $field['#maxlength'] = 10;
    $field['#size'] = 1;
  }
}