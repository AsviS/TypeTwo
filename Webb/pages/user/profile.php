<?php

if(!$userSession->isLoggedIn())
{
	header('Location: http://mikael.hernvall.com/typetwo');
	exit();
}


ob_start();
include(PAGE_ROOT . '/templates/profile.html');
return ob_get_clean();