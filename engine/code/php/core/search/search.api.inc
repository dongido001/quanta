<?php
function search($env) {
  $output = '';
  $results_arr = array();
  $results = array();
  $search_cmd = "grep -r -i -o -P -m100  --include \*.html  '.{0,140}" . $_REQUEST['search'] . ".{0,140}' " . $env->dir['docroot'];
  // $search_cmd = "find " . $page['dir']['docroot'] . " -iname=\"*.html\" -exec grep -r -i -o -m100 -P  '.{0,140}" . $_REQUEST['search'] . ".{0,140}' {} \; ";
  // Command with find: find "/Applications/MAMP/htdocs/websmenu"  -iname "*.html" -exec grep -r -i -o -m100  '.\{0,140\}mente.\{0,140\}' {} \;

  exec($search_cmd, $results_arr);
  $output .= '<h1>Search results</h1><div>You are searching for: <b>' . $_REQUEST['search'] . ' </div>
    <div id="data" class="search-results">';
  if (count($results_arr) == 0) {
    $output .= '<div class="search-no-results">No results found</div>';
  }
  foreach ($results_arr as $k => $result_string) {
    $r = explode(':' , $result_string);
    $result = preg_replace('/(' . $_REQUEST['search'] . ')/is', '<b class="search-result-match">$1</b>', strip_tags(nl2br(str_replace($r[0], '', $r[1]))));
    $filepath_exp = explode('/', $r[0]);
    $result_pagename = $filepath_exp[count($filepath_exp) - 2];
    if (substr($result_pagename, 0, 1) != '_') {
      $results[$result_pagename][] = '<div class="search-result-string">... ' . preg_replace('/\[(.*?)\]/', '', trim($result)) . ' ...</div>';
    }
  }
  $counter = array();
  $total_files = 0;
  $total_matches = 0;

  foreach ($results as $pname => $v) {
    $c = count($results[$pname]);
    $total_files++;
    $total_matches += $c;
    $counter[$pname] = $c;
  }
  arsort($counter);
  foreach ($counter as $pname => $result_count) {
    if (is_dir($env->dir['wiki'] . '/' . $pname)) {
      $result_file = str_replace('/', '&nbsp;&bull;&nbsp;', substr(str_replace($env->dir['docroot'], '', readlink($env->dir['wiki'] . '/' . $pname)), 1));
    }
    $output .= '<div class="search-result">' . $results[$pname][0] . '<div class="search-result-file"><b>' . $result_count. '</b> <span translate="yes">results found in:</span> [' . $pname . ':' . $result_file . ']</div></div>';
  }

  $output .= '<div class="search-results-total">Total: <b>' . $total_matches . '</b> matches found in <b>' . $total_files . '</b> files.</div>';
  $output .= '</div>';
  return $output;
}