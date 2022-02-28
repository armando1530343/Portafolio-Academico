<?php

//session_start();

if(!$_SESSION["validar"]){

	header("location:index.php?action=ingresar");

	exit();

}

include_once('bootstrap/link1.php');

?>
<div class="container" style="width: 80%;">
	<div class="row">
	    <div class="col-sm-12">
	        <h1 class="m-b-20 header-title"><b>EDITAR MAESTRO</b></h1>

	        <form method="post">
	            <?php

	            $editarUsuario = new MvcController();
				$editarUsuario -> editarMaestroController();
				$editarUsuario -> actualizarMaestroController();

	            ?>
	        </form>
	    </div>
    </div>
</div>

<?php include_once('bootstrap/link1.php'); ?>