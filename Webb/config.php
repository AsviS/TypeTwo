<?php

$userSession = new Session('user');

// It is recommended that you use a whitelist for your pages
// and use it for your controller.
$gyg->whitelistPages(
[
	'user',
	'chat',
]);

	
// Always use english.
$renderData['lang'] = 'en';

$renderData['style'] = '';

define('CONTROLLER_REQPATH', $gyg->getBaseUrl() . '/file/typetwo');
define('COMMON_REQPATH', CONTROLLER_REQPATH . '/common/');

define('CONTROLLER_ROOT', __DIR__);
define('COMMON_PATH', __DIR__ . '/common/');