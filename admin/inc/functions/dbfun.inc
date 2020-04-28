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
	// Get one User Info 
		function getUserInfo ($id){
			global $con;
			$stmt = $con->prepare("	SELECT * FROM users WHERE Id =? LIMIT 1");
			$stmt->execute(array($id));
			$count = $stmt->rowCount();
			if ($count== 1) {	
			 	$row = $stmt->fetch();
			 	return $row;
			}else{
				header('location: members.php');
			} 
		}
	// Get All User Info or count
		function getAllUserInfo ($x="d"){
			global $con;
			$stmt = $con->prepare("	SELECT * FROM users ");
			$stmt->execute(array());
			$count = $stmt->rowCount();
			if ($x == "d") {
				if ($count>= 1) {	
				 	$rows = $stmt->fetchAll();
				}else{
					$rows = "";
				} 
				return $rows;
			}else{
				return $count;
			}
		}
		// Get All Pending User Info 
		function getAllPendingUser ($x="d"){
			global $con;
			$stmt = $con->prepare("	SELECT * FROM users WHERE regStatus = 0");
			$stmt->execute();
			$count = $stmt->rowCount();
			if ($x == "d") {
				if ($count>= 1) {	
				 	$rows = $stmt->fetchAll();
				}else{
					$rows = "";
				} 
				return $rows;
			}else{
				return $count;
			}
		}
	// Update user Info
		function updatedUserInfo ($id="",$username="",$password="",$email="",$fullname=""){
			$order =$password!=""? "UPDATE users SET userName = ? , password =? , email=? , fullName=? WHERE Id =? LIMIT 1" :"UPDATE users SET userName = ? , email=? , fullName=? WHERE Id =? LIMIT 1" ;
			$hashpass = $password !=""? sha1($password): "";
			$exarray = $password !=""? array($username, $hashpass, $email, $fullname, $id) : array($username, $email, $fullname, $id);
			global $con;
			$stmt = $con->prepare($order);
			$stmt->execute($exarray);
			$count = $stmt->rowCount();
			return $count;
		}
	//insert NEW user to member 
		function insertNewUser($username, $password, $email, $fullname="",$groupid=0){
			global $con;
			$stmt = $con->prepare("SELECT userName  FROM users WHERE userName = ?");
        	$stmt->execute(array($username));
        	$count = $stmt->rowCount();
        	if ($count == 0) {
                $stmt = $con->prepare("INSERT INTO users (userName, password, email , fullName, groupId, trustStatus, regStatus, regDate)
                 VALUES (:zuser, :zpass, :zemail, :zfull, :zgroup, '1', '1', CURRENT_TIMESTAMP());");
                $stmt->execute(array(
                				'zuser' 	=> $username,
                				'zpass' 	=> $password,
                				'zemail' 	=> $email,
                				'zfull' 	=> $fullname,
                				'zgroup' 	=> $groupid

                ));
                   $count = $stmt->rowCount();
 				if ($count > 0) {
 					return "<div class='alert alert-success'> - Member has been Added</div>";
 				}else{
 					return "<div class='alert alert-danger'> -there is a problem Call Support</div>";
 				}
        	}else{
        		return "<div class='alert alert-danger'> -This userName is Already Taken</div>";
        	}
		}













/*
====
====  STart Cartegories DB functions
====
*/




	// Get All Categories Info or count or one category
		function getAllCat ($id="", $selctor="*", $limit ="1" ,$x="d"){
			global $con;
			$stmt = $id == ""? $con->prepare("SELECT $selctor FROM categories ") :$con->prepare("	SELECT $selctor FROM categories WHERE Id = ? LIMIT $limit");
			$stmt->execute(array($id));
			$count = $stmt->rowCount();
			if ($x == "d") {
				if ($count> 1) {	
				 	$rows = $stmt->fetchAll();
				 	return $rows;
				}elseif($count == 1){
					$row = $stmt->fetch();
					return $row;
				}else{
					if ($id =="") {
						header('location: Categories.php?do=start');
						exit();
					}else{
						header('location: Categories.php');
						exit();
					}	
				} 
			}else{
				return $count;
			}
		}

	//insert NEW Category  
		function insertCat($catname, $description, $order, $visability = 0,$comments = 0){
			global $con;
			$stmt = $con->prepare("SELECT catName  FROM categories WHERE catName = ?");
        	$stmt->execute(array($catname));
        	$count = $stmt->rowCount();
        	if ($count == 0) {
                $stmt = $con->prepare("INSERT INTO categories (catName, description, catorder , visibility, commallow, addDate)
                 VALUES (:zcat, :zdes, :zord, :zvis, :zcom, CURRENT_TIMESTAMP());");
                $stmt->execute(array(
                				'zcat' 	=> $catname,
                				'zdes' 	=> $description,
                				'zord' 	=> $order,
                				'zvis' 	=> $visability,
                				'zcom' 	=> $comments

                ));
                   $count = $stmt->rowCount();
 				if ($count > 0) {
 					return "<div class='alert alert-success'> - Category has been Added</div>";
 				}else{
 					return "<div class='alert alert-danger'> -there is a problem Call Support</div>";
 				}
        	}else{
        		return "<div class='alert alert-danger'> -This Category Name is Already Taken</div>";
        	}
		}

	// Update categories Info
		function updatedcategory ($id="",$catname="",$description="",$catorder="",$visability="", $comment=""){
			global $con;
			if ($id != "") {
				$order 	= "UPDATE categories SET ";
				$order .= $catname != ""? "catName = '$catname', " : "";
				$order .= $description != ""? "description = '$description', " : "";
				$order .= $catorder != ""? "catorder = '$catorder', " : "";
				$order .= $visability != ""? "visibility = '$visability', " : "";
				$order .= $comment != ""? "commallow =  '$comment', " : "";
				$order .= " WHERE Id = $id LIMIT 1";
				$order = substr_replace($order," ", strripos($order, ","),1);
				echo $order;
				if (stripos($order, "SET WHERE") > 0) {
					header('location: Categories.php');
					exit();
				}else{
					$stmt = $con->prepare($order);
					$stmt->execute();
					$count = $stmt->rowCount();
					if ($count >0) {
						header('location: Categories.php?do=Manage&update=done');
						exit();
					}else{
						header('location: Categories.php?do=Manage&update=false');
					}
					
				}
				
			}else{
				header('location: Categories.php');
				exit();
			}
			
		}





/*
===== sections fuunctions 
=====
*/

	// Get All Categories Info or count or one category
		function getAllSec ($id="", $selctor="*", $limit ="1" ,$x="d"){
			global $con;
			$stmt = $id == ""? $con->prepare("SELECT $selctor FROM sections ") :$con->prepare("	SELECT $selctor FROM sections WHERE Id = ? LIMIT $limit");
			$stmt->execute(array($id));
			$count = $stmt->rowCount();
			if ($x == "d") {
				if ($count> 1) {	
				 	$rows = $stmt->fetchAll();
				 	return $rows;
				}elseif($count == 1){
					$row = $stmt->fetch();
					return $row;
				}else{
					if ($id =="") {
						header('location: sections.php?do=start');
						exit();
					}else{
						header('location: sections.php');
						exit();
					}	
				} 
			}else{
				return $count;
			}
		}

		//insert NEW Sections  
		function insertSec($secname, $visability = 0, $catid){
			global $con;
			$stmt = $con->prepare("SELECT secName  FROM sections WHERE secName = ?");
        	$stmt->execute(array($secname));
        	$count = $stmt->rowCount();
        	if ($count == 0) {
                $stmt = $con->prepare("INSERT INTO sections (secName, visibility, catName, addDate)
                 VALUES (:zcat, :zvis, :zcom, CURRENT_TIMESTAMP());");
                $stmt->execute(array(
                				'zcat' 	=> $secname,
                				'zvis' 	=> $visability,
                				'zcom' 	=> $catid

                ));
                   $count = $stmt->rowCount();
 				if ($count > 0) {
 					return "<div class='alert alert-success'> - Section has been Added</div>";
 				}else{
 					return "<div class='alert alert-danger'> -there is a problem Call Support</div>";
 				}
        	}else{
        		return "<div class='alert alert-danger'> -This Section Name is Already Taken</div>";
        	}
		}
		// Update user Info
				function updatedsection ($id="",$secname="",$visability="", $catname=""){
					global $con;
					if ($id != "") {
						$order 	= "UPDATE sections SET ";
						$order .= $catname != ""? "secName = '$secname', " : "";
						$order .= $visability != ""? "visibility = '$visability', " : "";
						$order .= $catname != ""? "catName =  '$catname', " : "";
						$order .= " WHERE Id = $id LIMIT 1";
						$order = substr_replace($order," ", strripos($order, ","),1);
						echo $order;
						if (stripos($order, "SET WHERE") > 0) {
							header('location: Sections.php');
							exit();
						}else{
							$stmt = $con->prepare($order);
							$stmt->execute();
							$count = $stmt->rowCount();
							if ($count >0) {
								header('location: Sections.php?do=Manage&update=done');
								exit();
							}else{
								header('location: Sections.php?do=Manage&update=false&' . $order);
							}
							
						}
						
					}else{
						header('location: Sections.php');
						exit();
					}
					
				}


/*
====
====
==== items functions
====
====
*/


// Get All items Info or count or one category
		function getAllItem ($id="", $selctor="*", $limit ="1" ,$x="d"){
			global $con;
			$stmt = $id == ""? $con->prepare("SELECT $selctor FROM items ") :$con->prepare("SELECT $selctor FROM items WHERE Id = ? LIMIT $limit");
			$stmt->execute(array($id));
			$count = $stmt->rowCount();
			if ($x == "d") {
				if ($count> 1) {	
				 	$rows = $stmt->fetchAll();
				 	return $rows;
				}elseif($count == 1){
					$row = $stmt->fetch();
					return $row;
				}else{
					if ($id =="") {
						header('location: items.php?do=start');
						exit();
					}else{
						header('location: items.php');
						exit();
					}	
				} 
			}else{
				return $count;
			}
		}


	//insert NEW items  
		function insertItem($itemname, $description, $price, $visibility = 0,$comments = 0, $img='', $user, $cat, $sec){
			global $con;
			$stmt = $con->prepare("SELECT itemName  FROM items WHERE itemName = ?");
        	$stmt->execute(array($itemname));
        	$count = $stmt->rowCount();
        	if ($count == 0) {
                $stmt = $con->prepare("INSERT INTO items (itemName, description, price , visibility, commallow, imge, user, cat, sec, addDate)
                 VALUES (:zites, :zdes, :zprice, :zvis, :zcom, :zimg, :zuser, :zcat, :zsec, CURRENT_TIMESTAMP());");
                $stmt->execute(array(
                				'zites' 	=> $itemname,
                				'zdes' 		=> $description,
                				'zprice' 	=> $price,
                				'zvis' 		=> $visibility,
                				'zcom' 		=> $comments,
                				'zimg' 		=> $img,
                				'zuser' 	=> $user,
                				'zcat' 		=> $cat,
                				'zsec' 		=> $sec

                ));
                   $count = $stmt->rowCount();
 				if ($count > 0) {
 					return "<div class='alert alert-success'> - item has been Added</div>";
 				}else{
 					return "<div class='alert alert-danger'> -there is a problem Call Support</div>";
 				}
        	}else{
        		return "<div class='alert alert-danger'> -This item Name is Already Taken</div>";
        	}
		}


	// Update Item Info
		function updateItem ($id="",$secname="",$description="",$price="",$visability="", $comment="", $img, $cat, $sec){
			global $con;
			if ($id != "") {
				$order 	= "UPDATE items SET ";
				$order .= $catname 		!= ""? "secName = '$secname', " : "";
				$order .= $description 	!= ""? "description = '$description', " : "";
				$order .= $price	 	!= ""? "price = '$price', " : "";
				$order .= $visability 	!= ""? "visibility = '$visability', " : "";
				$order .= $comment 		!= ""? "commallow =  '$comment', " : "";
				$order .= $img 			!= ""? "imge =  '$img', " : "";
				$order .= $cat 			!= ""? "cat =  '$cat', " : "";
				$order .= $sec 			!= ""? "sec =  '$sec', " : "";
				$order .= " WHERE Id = $id LIMIT 1";
				$order = substr_replace($order," ", strripos($order, ","),1);
				echo $order;
				if (stripos($order, "SET WHERE") > 0) {
					header('location: items.php');
					exit();
				}else{
					$stmt = $con->prepare($order);
					$stmt->execute();
					$count = $stmt->rowCount();
					if ($count >0) {
						header('location: items.php?do=Manage&update=done');
						exit();
					}else{
						header('location: items.php?do=Manage&update=false');
					}
					
				}
				
			}else{
				header('location: items.php');
				exit();
			}
			
		}





/*
====
==== All Functions 
====
*/
	// Get Delte any   
		function delete ($id,$from){
			global $con;
			$stmt = $con->prepare("DELETE FROM $from WHERE Id =? LIMIT 1");
			$stmt->execute(array($id));
			$count = $stmt->rowCount();
			if ($count== 1) {	
			 	return "<div class='alert alert-success'> - Record has been Deleted </div>";
			}else{
				return "<div class='alert alert-danger'> - there is no member Has that Id if you sure please Call Support</div>";
			} 
		}


	// change all Satuts
		function regStatus ($id, $table, $column, $stat){
			$toggoleStatus = $stat ==1 ? 0 : 1;
			if ($table == 'users') {
				$msg = $stat ==1 ? 'Deactivate' : 'Actavaite';
			}else{
				$msg = $stat ==0 ? 'Deactivate' : 'Actavaite';
			}
			
			global $con;
			$stmt = $con->prepare("UPDATE $table SET $column = $toggoleStatus  WHERE Id = $id LIMIT 1");
			$stmt->execute();
			$count = $stmt->rowCount();
			if ($count== 1) {	
			 	return "<div class='alert alert-success'> - Record has been $msg </div>";
			}else{
				return "<div class='alert alert-danger'> - there is no member Has that Id if you sure please Call Support</div>";
			} 
		}



		// search  	
		function search ($searchvalues, $table){
				global $con;
				if ($table == 'users') {
					$stmt = $con->prepare("	SELECT * FROM users WHERE userName LIKE '%$searchvalues%' OR email LIKE '%$searchvalues%' OR fullName LIKE '%$searchvalues%' ");
				}elseif ($table == 'categories') {
					$stmt = $con->prepare("	SELECT * FROM categories WHERE catName LIKE '%$searchvalues%' OR description LIKE '%$searchvalues%' ;");
				}elseif ($table == 'sections') {
					$stmt = $con->prepare("	SELECT * FROM Sections WHERE secName LIKE '%$searchvalues%' OR catName LIKE '%$searchvalues%' ;");
				}
				elseif ($table == 'items') {
					$stmt = $con->prepare("	SELECT * FROM items WHERE itemName LIKE '%$searchvalues%' OR description LIKE '%$searchvalues%' OR price LIKE '%$searchvalues%' ;");
				}
				
				$stmt->execute(array());
				$count = $stmt->rowCount();
					if ($count>= 1) {	
					 	$rows = $stmt->fetchAll();
					}else{
						$rows = "";
					} 
					return $rows;
			}

		// ordring table 	
		function Allorder ($order, $table,$v="ASC"){
				global $con;
				$stmt = $con->prepare("	SELECT * FROM $table ORDER BY $order $v");
				$stmt->execute(array());
				$count = $stmt->rowCount();
					if ($count>= 1) {	
					 	$rows = $stmt->fetchAll();
					}else{
						$rows = "";
					} 
					return $rows;
			}

		// Get last five recordes 	
		function getLatsetUser ($table){
				global $con;
				$stmt = $con->prepare("	SELECT * FROM $table ORDER BY Id DESC LIMIT 5");
				$stmt->execute(array());
				$count = $stmt->rowCount();
					if ($count>= 1) {	
					 	$rows = $stmt->fetchAll();
					}else{
						$rows = "";
					} 
					return $rows;
			}

		
		// Get any
			function getAny ($table, $depend, $value,$x="d"){
				global $con;
				$stmt = $con->prepare("	SELECT * FROM $table WHERE $depend = '$value' ");
				$stmt->execute();
				$count = $stmt->rowCount();
				if ($x == "d") {
					if ($count> 1) {	
					 	$rows = $stmt->fetchAll();
					 	return $rows;
					}elseif($count == 1){
						$row = $stmt->fetch();
						return $row;
					}else{
						return 0;
					} 
				}else{
					return $count;
				}
			}		
ob_end_flush();
?>