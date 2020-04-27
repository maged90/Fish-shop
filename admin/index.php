<?php 
	// Start Sesstion
		session_start();
	// declar page name
		$pageName = "adminlogin";
	// include initialize file
		include "int.php";			
	// check if sesstion has username values 
		if (isset($_SESSION['adminName'])) {
			header ('location: dashbord.php');
		}

	// Check if admin Coming from Http post requset
		if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['admin'])) {
	// put values that are come from sever requset in variable
			$admin = $_POST['admin'];
			$pass = $_POST['pass'];
		// change pass to hashed pass
			$shapass = sha1($pass);
		// used function from dbfun file that includes in int file to chech if that adimn or not 
			checkAdmin($admin,$shapass);
	}
		echo $status 
?>
	<h1 class="text-center login-header">Admin Login</h1>
	<form class="login" action="<?php echo $_SERVER['PHP_SELF']?>" method="POST">
		<input class="form-control" type="text" name="admin" placeholder="AdminName" autocomplete="off" onfocus="focusplaceHolder(this);" onblur="blurplaceHolder(this);">
		<input class="form-control" type="password" name="pass" placeholder="Password" autocomplete="new-password" onfocus="focusplaceHolder(this);" onblur="blurplaceHolder(this);">
		<input class="btn btn-primary btn-block" type="submit" name="Submit" value="Login">
	</form> 
<?php
 	// include footer	
		 include  $tpl . "footer.inc"; 
?>