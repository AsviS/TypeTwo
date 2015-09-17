<?php
/*
 * Page's main file.
 *
 * Control is redirected here when the controller
 * receives this page's ID as second argument.
 */
 
include(PAGE_ROOT . '/config.php');
 
$args = $config['args'];
$argCount = count($args);

$subPage = isset($args[0]) ? $args[0] : null;
$subPagePath = PAGE_ROOT . "/{$subPage}.php";
if(file_exists($subPagePath))
	$config['content'] = include($subPagePath);
else
{
	$subPagePath = PAGE_ROOT . "/{$config['defaultSubPage']}.php";
	if(file_exists($subPagePath))
		$config['content'] = include($subPagePath);
	else
		httpStatus::send(404);
}