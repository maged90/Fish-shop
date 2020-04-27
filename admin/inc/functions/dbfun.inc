<?php
ob_start();
	// Check if That Real admin 
		function checkAdmin ($admin, $shapass){
			global $con;
			$stmt = $con->prepare("	SELECT 
										Id, userName, password 
								   	FROM 
								   		users 
							   		WHERE 
							   			userName = ? 
						   			AND 
						   				password = ? 
					   				And 
					   					groupId =1 
				   					LIMIT 1");
			$stmt->execute(array($admin , $shapass));
			$row = $stmt->fetch();
			$count = $stmt->rowCount();
			if ($count == 1) {	
			 	$_SESSION['adminName'] = $row['userName'] ;
			 	$_SESSION['id'] = $row['Id'] ;
			 	header ('location: dashbord.php');
			 	exit();
			}else{
				echo "<div class='container' style='margin-top: 63px;'><div class='alert alert-danger'> - username or password  is not right</div></div>";;
			} 
		}

ob_end_flush();
?>