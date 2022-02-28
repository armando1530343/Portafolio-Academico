<?php

//session_start();
if(!$_SESSION["validar"]){

	header("location:index.php");

	exit();

}

//se incluye los los estilos de bootstrap

include_once('bootstrap/link1.php');

?>
<!-- START PAGE CONTENT -->

<div class="container" style="width: 50%;">
	<div class="row">
	    <div class="col-sm-12">
	        <div class="table-responsive m-b-20">
	            <h1>PERFIL: <?php echo $_SESSION['usuario']['nombre']; ?></h1>
	            <!--Se imprimen los datos del perfil del maestro con la variable de session-->
	            <table id="datatable" class="table table-striped table-bordered">
	                <tr><td style="text-align: center;"><strong>NOMBRE:</strong> <?php echo $_SESSION['usuario']['nombre']; ?></td></tr>
	                <tr><td style="text-align: center;"><strong>CARRERA:</strong> <?php echo $_SESSION['usuario']['carrera']; ?></td></tr>
	                <tr><td style="text-align: center;"><strong>EMAIL:</strong> <?php echo $_SESSION['usuario']['email']; ?></td></tr>
	                <tr><td style="text-align: center;"><strong>PASSWORD:</strong> <?php echo $_SESSION['usuario']['password']; ?></td></tr>
	            </table>
	        </div>
	    </div>
	</div>
</div>
<?php

include_once('bootstrap/link2.php');

if(isset($_GET["action"])){

	if($_GET["action"] == "cambio"){

		echo "Cambio Exitoso";
	
	}

}

?>




