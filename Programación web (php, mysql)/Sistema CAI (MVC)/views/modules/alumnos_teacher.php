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
		                  Se agregó un nuevo Alumno
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
		                  El Alumno se eliminó correctamente
		                </div>';
    		}
    		else if($_GET['status'] == 'error'){
    			echo '	<div class="alert alert-danger alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-ban"></i> Error!</h5>
		                  No se pudo guardar el Alumno
		                </div>';
    		}
    		else if($_GET['status'] == 'existe'){
    			echo '	<div class="alert alert-warning alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-warning"></i> Incorrecto!</h5>
		                  La matricula ingresada ya existe aqui o en otro grupo.
		                </div>';
    		}
    	}

    	$mvc = new Mvc();
    	$grupo = $mvc->getGrupoController();
    	$teacher = $mvc -> getUserTeacherController($_GET['user']);


    	 ?>
	    <div class="card">
	      <div class="card-header row">
	      	<div class="col-sm-6" align="left">
	      		<h3 class="card-title"><?php echo 'Grupo: '.$grupo[0]['grupo']; ?></h3>
	      	</div>
	      	<div class="col-sm-6" align="right">      		
	            <h3 class="card-title">Teacher: <?php echo $teacher[0]['nombre_completo']; ?></h3>        
	      	</div>
	        
	      </div>
	      <!-- /.card-header -->
	      <div class="card-body">
	        <table id="example1" class="table table-bordered table-striped">
	          <thead>
	          <tr>
	          	<th>Matricula</th>
	          	<th>Nombre Alumno</th>
	          	<th>Carrera</th>
	          	<th>Horas</th>
	          	<th></th>
	          </tr>
	          </thead>
	          <tbody>
	          <?php 

		          $mvc = new Mvc();
		          $mvc -> vistaAlumnosTeacherController();

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