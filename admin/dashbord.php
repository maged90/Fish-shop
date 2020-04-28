<?php
	ob_start();
	// Start Sesstion
		session_start();
	// declar page name
		$pageName = "Dashbord";
	// include initialize file
		include "int.php";	
	// check if sesstion has username values 
	if (isset($_SESSION['adminName'])) {// sesstion now contain adminName in $_SESSION['adminName'] and AdminId in $_SESSION['id']
		$usercount 		= getAllUserInfo("n");
		$itemcount 		= getAllItem("","*","","n");
		$pendingusers 	= getAllPendingUser("n");
		$latestUSers 	= getLatsetUser('users');
		$latestItems 	= getLatsetUser('items');
?>
		<h1 class="text-center">Dashdord</h1>
		<div class="container main-dash">
			<div class="row">
				<div class="col-sm-6 col-lg-3">
					<div class="stat members-dash">
						<h3>Total Members</h3>
						<span><i class="fas fa-user"></i><a href="members.php"><?php echo $usercount?></a></span>
					</div>
				</div>
				<div class="col-sm-6 col-lg-3">
					<div class="stat pending-dash">
						<h3>Pending Members</h3>
						<span><i class="fas fa-user-clock"></i><a href="members.php?do=pend"><?php echo $pendingusers?></a></span>
					</div>
				</div>
				<div class="col-sm-6 col-lg-3">
					<div class="stat items-dash">
						<h3>Total Items</h3>
						<span><i class="fas fa-tag"></i><a href=""><?php echo $itemcount?></a></span>
					</div>
				</div>
				<div class="col-sm-6 col-lg-3">
					<div class="stat comments-dash">
						<h3>Total Comments</h3>
						<span><i class="fas fa-comment"></i><a href="">1000</a></span>
					</div>
				</div>
			</div>
			<div class="row fast-news">
				<div class="col-md-6">
					<div class="news-container">
					  	<div class="users-news">
					  		<i class="fas fa-user"></i>
					    	Latest Registered Users
					  	</div>
						    <ul class="news-header">
						      	<li>ID</li>
						      	<li>Name</li>
						      	<li>Activation</li>
						      	<li>Items</li>
						      	<li>Comments</li>	
						    </ul>
<?php
							if (is_array($latestUSers)) {
								foreach ($latestUSers as  $user) {
?>
						    <ul class="news-content">
						      	<li><?php echo $user['Id'];?></li>
							    <li><?php echo $user['userName'];?></li>
							    <li><?php $activestat = $user['regStatus'] == 1 ? "Active" : "Pending"; echo $activestat;?></li>
							    <li><?php echo getAny ("items", "user", $user['userName'],"y");?></li>
							    <li>3</li>	
						    </ul>
<?php									
								}
							}
?>
					</div>    	
				</div>
				<div class="col-md-6">
					<div class="news-container">
					  	<div class="users-news">
					  		<i class="fas fa-tag"></i>
					    	Latest Added Items
					  	</div>
						    <ul class="news-header">
						      	<li>ID</li>
						      	<li>Name</li>
						      	<li>Activation</li>
						      	<li>User</li>
						      	<li>Comments</li>	
						    </ul>
<?php
							if (is_array($latestItems)) {
								foreach ($latestItems as  $item) {
?>
						    <ul class="news-content">
						      	<li><?php echo $item['Id'];?></li>
							    <li><?php echo $item['itemName'];?></li>
							    <li><?php $activestat = $item['visibility'] == 1 ? "Active" : "Pending"; echo $activestat;?></li>
							    <li><?php echo $item['user'];?></li>
							    <li>3</li>	
						    </ul>
<?php									
								}
							}
?>
					</div> 
				</div>
			</div>
		</div>



<?php
		include  $tpl . "footer.inc";	
	}else{
		// return to login page if user try to access to dashbord dirctly without login
		header('location: index.php');
		exit();
	}
	ob_end_flush();
?> 