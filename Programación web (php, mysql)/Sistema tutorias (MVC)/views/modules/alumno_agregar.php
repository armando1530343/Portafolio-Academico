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
	        <h1 class="m-b-20 header-title"><b>NUEVO ALUMNO</b></h1>

	        <form method="post">
	            <?php

	            $nuevoAlumno = new MvcController();
				$nuevoAlumno -> agregarAlumnosController();
				$nuevoAlumno -> registroAlumnoController();

	            ?>
	        </form>
	    </div>
    </div>
</div>

<?php include_once('bootstrap/link1.php'); ?>