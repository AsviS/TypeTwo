<?php

class ajax
{
	static public function send($success, $message = null)
	{
		header('Content-type: application/json');
		echo json_encode(['success' => $success, 'output' => $message]);
		exit();
	}
}