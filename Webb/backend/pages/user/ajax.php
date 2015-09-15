<?php
if(isset($_GET['login']))
{
	$requiredArgs = ['name', 'password'];
	
	foreach($requiredArgs as $arg)
		if(!isset($_POST[$arg]))
			httpStatus::send(405, 'Invalid arguments');

	include_once(CONTROLLER_ROOT . '/database/user.php');
	$userTable = new UserTable();
	$credentials = $userTable->getCredentials($_POST['name']);
	
	if($credentials['hashedPassword'] && hash("sha512", $_POST['password'] . $credentials['salt']) == $credentials['hashedPassword'])
	{
		$userSession->login($_POST['name']);
		GygAjax::send(true);
	}
	else
		GygAjax::send(false, 'Invalid username or password.');
		
}
else if(isset($_GET['logout']))
{
	$userSession = new GygUserSession('user');
	$userSession->logout();
}
else if(isset($_GET['loginForm']))
{
	include('templates/loginForm.tpl.php');
	exit();
}