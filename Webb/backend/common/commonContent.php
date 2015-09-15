<?php

/*
 * This content will always be shown.
 * The header and menu will never be changed.
 * The title is just a default value, so feel
 * free to change it in a specific page.
 */
 
// Meta data
$renderData['description'] = 'Massively multiplayer online grand strategy in space';
$renderData['keywords'] =
[
	'typetwo',
];
 
// Base url
$renderData['baseUrl'] = $gyg->getBaseUrl();
 
// Title of page
$renderData['baseTitle'] = "TypeTwo";

// Scripts
$renderData['scripts'] = 
[
	COMMON_REQPATH . 'js/jquery.js',
	COMMON_REQPATH . 'js/login.js',
];


// Main template.
$renderData['templatePath'] = __DIR__ . "/templates/main.tpl.php";

////////////////////////////////
// Above
$renderData['above'] = include('above.php');
////////////////////////////////

$renderData['style'] = "@import url(" . COMMON_REQPATH . "style/login.css)";