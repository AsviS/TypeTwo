<?php
define('CONTROLLER_REQPATH', $gyg->getBaseUrl() . '/file/typetwo');
define('COMMON_REQPATH', CONTROLLER_REQPATH . '/common/');

define('CONTROLLER_ROOT', __DIR__);
define('COMMON_PATH', __DIR__ . '/common/');


$userSession = new Session('user');

// It is recommended that you use a whitelist for your pages
// and use it for your controller.
$gyg->whitelistPages(
[
	'user',
	'chat',
]);

$config =
[
	'lang'  		=> 'en',
	'baseTitle' 	=> 'TypeTwo',
	'baseUrl' 		=> $gyg->getBaseUrl(),
	'keywords'		=> 
		[
			'typetwo'
		],
	'description'	=> 'Massively multiplayer online grand strategy in space',
	'defaultPage'	=> 'user',
	
	'favicon' 		=> null,
	'stylesheet' 	=> null,
	'style' 		=> "@import url(" . COMMON_REQPATH . "style/login.css);",
	'templatePath'	=> COMMON_PATH . '/templates/main.html',
	'scripts'		=> 
		[
			COMMON_REQPATH . 'js/jquery.js',
			COMMON_REQPATH . 'js/login.js',
		],
	'above'			=> include(COMMON_PATH . '/above.php'),
	'content'		=> null,
];