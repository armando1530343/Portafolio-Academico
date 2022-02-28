 <?php 

 	if(!isset($_SESSION['validar'])){

		echo '<script> alert("No haz iniciado sesion") </script>';
		echo '<script> window.location = "index.php"; </script>';
 		//header('Location:dashboard.php');
 	}

 	



  ?>

  <section class="content">
    <div class="container-fluid">
    	<?php 

    	if(isset($_GET['status'])){
    		if($_GET['status'] == 'success'){
    			echo '	<div class="alert alert-success alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-check"></i>Correcto !</h5>
		                  Se agregó un nuevo Teacher
		                </div>';
    		}
    		else if($_GET['status'] == 'actualizado'){
    			echo '	<div class="alert alert-success alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-check"></i>Correcto !</h5>
		                  Se actualizo un registro
		                </div>';
    		}
    		else if($_GET['status'] == 'borrado'){
    			echo '	<div class="alert alert-success alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-check"></i>Correcto !</h5>
		                  El Teacher se eliminó correctamente
		                </div>';
    		}
    		else if($_GET['status'] == 'error'){
    			echo '	<div class="alert alert-danger alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-ban"></i> Error!</h5>
		                  No se pudo guardar el Teacher
		                </div>';
    		}
    		else if($_GET['status'] == 'password'){
    			echo '	<div class="alert alert-warning alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-ban"></i> Incorrecto!</h5>
		                  Las contraseñas no coinciden
		                </div>';
    		}
    		else if($_GET['status'] == 'incorrecto'){
    			echo '	<div class="alert alert-warning alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-warning"></i> Incorrecto!</h5>
		                  No se pueden eliminar Teachers con grupos asignados.
		                </div>';
    		}
    	}


    	 ?>
	    <div class="card">
	      <div class="card-header row">
	      	<div class="col-sm-6" align="left">
	      		<h3 class="card-title">Teachers</h3>
	      	</div>
	      	<div class="col-sm-6" align="right">      		
	            <a href="index.php?user=admin&action=agregar_teacher" class="btn btn-success">Agregar Teacher</a>	           
	      	</div>
	        
	      </div>
	      <!-- /.card-header -->
	      <div class="card-body">
	        <table id="example1" class="table table-bordered table-striped">
	          <thead>
	          <tr>
	          	<th>Id</th>
	          	<th>Nombre</th>
	            <th></th>
	            <th></th>
	          </tr>
	          </thead>
	          <tbody>
	          <?php 

		          $mvc = new Mvc();
		          $mvc -> vistaTeachersController();

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