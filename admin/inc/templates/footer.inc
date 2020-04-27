<?php
	if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['button1']) && $_POST['button1'] == 'logout') {
			// remove all session variables
				session_unset();

			// destroy the session
				session_destroy();

				header('location: index.php');
				exit();
		}
?>
		<script src="<?php echo $js ?>jquery.js"></script>
		<script src="<?php echo $js ?>popper.js"></script>
		<script src="<?php echo $js ?>bootstrap.js"></script>
		<script  src="<?php echo $js ?>myjs.js"></script>
	</body>
</html>