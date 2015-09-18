<?php

include(CONTROLLER_ROOT . '/database/user.php');
$userTable = new UserTable();

$users = $userTable->getUsers();
$columns = [];
if(isset($users[0]))
	foreach($users[0] as $key => $userData)
		$columns[] = $key;
else
	$users = [];

ob_start();
include(PAGE_ROOT . '/templates/list.html');
return ob_get_clean();