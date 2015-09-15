<?php

$userSession = new Session('user');

// It is recommended that you use a whitelist for your pages
// and use it for your controller.
$gyg->whitelistPages(
[
	'user',	
]);

	
// Always use english.
$renderData['lang'] = 'en';


define('COMMON_REQPATH', $gyg->getBaseUrl() . '/file/typetwo/common/');
define('CONTROLLER_ROOT', __DIR__);
define('COMMON_PATH', __DIR__ . '/common/');