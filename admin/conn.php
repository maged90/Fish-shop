<?php 
	$servername = "localhost";
	$dns        = "mysql:host=$servername;dbname=fishshop";
	$dbuser     = "root";
	$dbpass     = "";
	$dboption   = array(
		PDO::MYSQL_ATTR_INIT_COMMAND => "set NAMES utf8",
	);

	try{
		$con = new PDO($dns, $dbuser, $dbpass, $dboption);
		$con->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
		$status ='<div style="width: 250px; position: absolute; right:10px; top:0;">
					<div style="font-size: 25px; display: block; color: blue;">DB Connection status</div>
					<div style="text-align: center;">
					<span style="display:inline-block; background-color: green; width: 15px; height: 15px; border-radius: 50%;"></span>
					<span style="font-size: 18px; display: inline-block; color: green;">Connected</span>
					</div>
				</div>';
	}

	catch(PDOException $e)
    {
    	$status ='<div style="width: 250px; position: absolute; right:10px; top:0;">
					<div style="font-size: 25px; display: block; color: blue;">DB Connection status</div>
					<div style="text-align: center;">
						<span style="display:inline-block; background-color: red; width: 15px; height: 15px; border-radius: 50%;"></span>
					<span style="font-size: 18px; display: inline-block; color: red;">Connect failed</span>
					</div>
				</div>';
    echo "Connection failed: " . $e->getMessage();
    }
?>
