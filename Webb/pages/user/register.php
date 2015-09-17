<?php
/*
 * Page's main file.
 *
 * Control is redirected here when the controller
 * receives this page's ID as second argument.
 */
 
if(isset($_POST['name']) && isset($_POST['password']))
{
	include_once(CONTROLLER_ROOT . "/database/user.php");
	$userTable = new UserTable();
	$salt = base64_encode(openssl_random_pseudo_bytes(189, $secure));
	$hashedPassword = hash("sha512", $_POST['password'] . $salt);
	
	if($userTable->createUser($_POST['name'], $hashedPassword, $salt, $_POST['name'] . '@mail.com'))
		$userSession->login($_POST['name']);
		
	header("Location: http://mikael.hernvall.com/typetwo/user/");
	exit;
	
}

ob_start();
include(PAGE_ROOT . '/templates/registerForm.html');
return ob_get_clean();