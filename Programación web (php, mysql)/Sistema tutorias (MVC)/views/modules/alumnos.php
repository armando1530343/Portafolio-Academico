<?php

//se verifica que la sesion este iniciada para acceder a este apartado
if(!$_SESSION["validar"]){

	header("location:index.php");

	exit();

}

include_once('bootstrap/link1.php');

?>
<!-- START PAGE CONTENT -->

<div class="container" style="width: 80%;">
	<div class="row">
	    <div class="col-sm-12">
	        <div class="table-responsive m-b-20">
	            <h1>ALUMNOS</h1>
	            <!--Se imprime el reporte de la tabla de alumnos-->
	            <table id="datatable" class="table table-striped table-bordered">
	                <thead>
	                <tr>
						<th>Matricula</th>
						<th>Nombre</th>
						<th>Carrera</th>
						<th>Tutor</th>
						<?php 
						if($_SESSION['usuario']['nombre'] == "ADMINISTRADOR"){
							echo '<th></th>
								  <th></th>';
						}
						?>
					</tr>
	                </thead>


	                <tbody>
	                <?php

	                //se llama al controlador de la vista del formulario
					$vistaUsuario = new MvcController();
					$vistaUsuario -> vistaAlumnosController();

					?>
	                </tbody>
	            </table>
	        </div>
	    </div>
	</div>
</div>
<?php

include_once('bootstrap/link2.php');

?>




