 <?php 

 	if($_SESSION['validar']==false){

		echo '<script> alert("No haz iniciado sesion") </script>';
		echo '<script> window.location = "index.php"; </script>';
 		//header('Location:dashboard.php');
 	}

 	



  ?>

  <section class="content">
    <div class="container-fluid">
    	<div class="card">
	      <div class="card-header row">
	      	<div class="col-sm-6" align="left">
	      		<h3 class="card-title">Historial de Visitas</h3>
	      	</div>
	      	
	      </div>
	      <!-- /.card-header -->
	        <div class="card-body">
		        <table id="example1" class="table table-bordered table-striped">
		          <thead>
		          <tr>
		          	<th>No.Registro</th>
		          	<th>Hora Entrada</th>
		          	<th>Alumno</th>
		          	<th>Teacher</th>
		            <th>Grupo</th>
	              	<th>Actividad</th>
	              	<th>No.Unidad</th>
	              	<th>Horario</th>
		          </tr>
		          </thead>
		          <tbody>
		          <?php 

			          $mvc = new Mvc();
			          $mvc -> vistaHistorialController();

		          ?> 
		          
		          </tbody>
		          
		        </table>
	        </div>
	      <!-- /.card-body -->
	    </div>
      <!-- /.row -->
      <!-- Main row -->
      <!-- /.row (main row) -->
    </div><!-- /.container-fluid -->
  </section>