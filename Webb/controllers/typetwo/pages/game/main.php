<?php

include(PAGE_ROOT . '/config.php');
/*
function loadGameScripts(&$scripts)
{
	foreach(glob(PAGE_ROOT . '/typetwo-game/*.js') as $script)
		$scripts[] = PAGE_REQPATH . "/typetwo-game/" . basename($script);
}

loadGameScripts($config['scripts']);
*/
///ob_start();
include(PAGE_ROOT . '/templates/main.html');
//$config['content'] = ob_get_clean();

exit();
