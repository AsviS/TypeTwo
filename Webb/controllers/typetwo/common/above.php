<?php

/*
 * Generate HTML for the above
 */

ob_start();
include(__DIR__ . '/templates/above.html');
$above = ob_get_clean();

return $above;