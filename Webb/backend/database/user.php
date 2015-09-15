<?php
/*
 * This file contains table functions for a specific table.
 * To define functions as init and get, simply return an array
 * with function names as keys and your desired function as the value.
 * Example:
 * 
 * return
 * [
 * 'init' => function()
 *	{
 *		//Perform initialization.
 *		//Maybe even return a value?
 *	}
 *	];
 *
 * This file will be included by $this->gygDb->callTableFunction in the database functions file.
 * Make sure to enable the function name in the db config file when using it.
 *
 * The items in the array does not have to be functions. If an item is not a function,
 * that items value will be returned by $this->gygDb->callTableFunction. So it's possible to do this:
 * return
 * [
 * 'init' => 'Hello!'
 *	];
 * When calling $this->gygDb->callTableFunction($tableId, 'init'), 'Hello!' will be returned.
 *
 * If an item is a function, it will be called by $this->gygDb->callTableFunction, and the return value 
 * of the function will subsequently be returned by $this->gygDb->callTableFunction.
 */

class UserTable
{
	private $mDb;
	public function __construct()
	{
		$this->mDb = new mysqli(ini_get("mysqli.default_host"), 
								ini_get("mysqli.default_user"),
								ini_get("mysqli.default_pw"),
								"typetwo"
								);
		
		//$this->mDb = new mysqli("localhost", "typetwo", "lethal type two diabetes", "typetwo");
	}
	
	public function getCredentials($username)
	{
        $stmt = $this->mDb->prepare("SET @username = ?;");
		$stmt->bind_param('s',$username);
		$stmt->execute();
	  
		$stmt->prepare("CALL user_get_credentials(@username, @hashedPassword, @salt)");
		$stmt->execute();
	   
		$stmt->prepare("SELECT @hashedPassword, @salt;");
		$stmt->execute();
	   
		$hashedPassword = null;
		$salt = null;
		$stmt->bind_result($hashedPassword, $salt);
		$stmt->fetch();
		
		return ['hashedPassword' => $hashedPassword, 'salt' => $salt];
	}
	
	public function createUser($username, $hashedPassword, $salt, $email)
	{	  
		$stmt = $this->mDb->prepare("CALL user_insert(?, ?, ?, ?, NOW())");
		$stmt->bind_param('ssss', $username, $hashedPassword, $salt, $email);
		return $stmt->execute();
	}
	
};