<?php
// Set up user-defined settings.
include("config.php");
 

/*
 * Set up module loader.
*/ 
require_once('globalModules/ModuleLoader.php');
$moduleLoader = new ModuleLoader($globalModulesPath);

/*
 * Set up whitelists and other settings as
 * defined in config.
 */
$gyg = new GygFramework($controllersPath, $defaultController);
$gyg->useRewriteRule($useRewriteRule);
$gyg->whitelistControllers($controllers);
$gyg->whitelistShortcuts($shortcuts);


// Let the show begin.
include($gyg->routeControl());