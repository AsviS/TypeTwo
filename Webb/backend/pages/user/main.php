<?php
/*
 * Page's main file.
 *
 * Control is redirected here when the controller
 * receives this page's ID as second argument.
 */
 
 
$args = $renderData['args'];
$argCount = count($args);

if($userSession->isLoggedIn())
	echo "You are now logged in!";

/*
 * Show register page by default.
 */
include(__DIR__ . '/create.php');