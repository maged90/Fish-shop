<?php
	// include file create database and all tables and create admin user and pass 
		require_once("dbcreator.php");
	// dataBase Connection 
		include "conn.php";
   // Routs
	   $tpl = "inc/templates/";
	   $css = "layout/css/";
	   $js  = "layout/js/";
	   $fun = "inc/functions/";



	// include header file
		include $tpl . "header.inc";
	// inculde db functions
		include $fun . 'dbfun.inc';	
	// include navbar if it necessary
	if ($pageName != "adminlogin") {include $tpl . "navbar.inc";};	 
?>
