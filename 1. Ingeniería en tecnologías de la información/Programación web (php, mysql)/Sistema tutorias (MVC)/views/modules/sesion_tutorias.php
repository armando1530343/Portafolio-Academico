<?php 

	include_once('bootstrap/link1.php');

?>
 <!-- START PAGE CONTENT -->

<div class="container" style="width: 80%;">
	<div class="row">
	    <div class="col-sm-12">
	        <div class="table-responsive m-b-20">
	            <h1>Tutorias</h1>
	            <table id="datatable" class="table table-striped table-bordered">
	                <thead>
	                <tr>
						<th>Id</th>
						<th>Alumno</th>
						<th>Tutor</th>
						<th>Fecha</th>
						<th>Hora</th>
						<th>Tipo</th>
						<th>Tutoria</th>

					</tr>
	                </thead>


	                <tbody>
	                <?php

					$vistaUsuario = new MvcController();
					$vistaUsuario -> vistaTutoriasController();
					//$vistaUsuario -> borrarUsuarioController();

					?>
	                </tbody>
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




