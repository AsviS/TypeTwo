<?php
include(__DIR__ . "/config.php");
 
$request = $gyg->getRequest();

$config['controller'] = $request['controller'];
$config['page'] = isset($request['args'][0]) ? $request['args'][0] : null;
$config['args'] = $request['argCount'] > 1 ? array_splice($request['args'], 1) : null;

if($config['page'] === null)
	$config['page'] = $config['defaultPage'];
else if(!$gyg->pageIsWhitelisted($config['page']))
	httpStatus::send('404');

$pageMainPath = CONTROLLER_ROOT . "/pages/{$config['page']}/main.php";
if(!file_exists($pageMainPath))
	httpStatus::send('404');
else
{
	define('PAGE_ROOT', CONTROLLER_ROOT . "/pages/{$config['page']}");
	define('PAGE_REQPATH', CONTROLLER_REQPATH . "/pages/{$config['page']}");
	include($pageMainPath);
}
	
extract($config);
include(COMMON_PATH . '/templates/main.html');
