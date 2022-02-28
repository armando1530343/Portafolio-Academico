<!--Es la plantilla que vera el usuario al ejecutar la aplicación -->
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>Practica 12</title>

	<?php include_once('links/link1.php'); ?>
	<style type="text/css">
		.login{
			padding: 50px;max-width: 450px; width: 50%; position: relative;margin: 0 auto;
		}
	</style>
	

</head>

<!--body class="hold-transition sidebar-mini"-->
<body class="hold-transition login-page">
	<div class="wrapper">

	<?php
		if(isset($_GET['action'])){
			if($_GET['action'] != 'fallo'){
				include "modules/navegacion.php";	
				
			}	

		}
		

		$mvc = new MvcController();
		$mvc -> enlacesPaginasController();

			

	?>
	</div>
</body>

<?php include_once('links/link2.php'); ?>
</html>