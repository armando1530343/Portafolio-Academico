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
    		if($_GET['status'] == 'existe_alumno'){
    			echo '	<div class="alert alert-warning alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-warning"></i> Incorrecto!</h5>
		                  La matricula ingresada ya existe.
		                </div>';
    		}
    	}

    	$mvc = new Mvc();
    	$grupo = $mvc->getGrupoController();


    	 ?>

    	<div class="card">

	      <div class="card-header row">
	      	<div class="col-sm-6" align="left">
	      		<h3 class="card-title"><?php echo 'Teacher: '.$grupo[0]['teacher']; ?></h3>
	      		<h3 class="card-title"><?php echo 'Grupo: '.$grupo[0]['grupo']; ?></h3>
	      		
	      	</div>
	      	<div class="col-sm-12" align="center">	      		
	      		<h3 class="card-title">Alta de Alumno</h3>
	      	</div>
	      	
	      </div>
	      <!-- /.card-header -->
	      <div class="row">
	      	<div class="col-sm-12" align="center">
	      		<form class="form-horizontal" style="text-align: center; width: 70%;" method="post">
		            <?php 

		            	$mvc = new Mvc();
		            	$mvc -> agregarAlumnoController();
		            	$mvc -> registroAlumnoController();
		            	
		            	
		             ?>
		            <!-- /.card-footer -->
		        </form>	
	      	</div>
	          
	      </div>
	      <!-- /.card-body -->
	    </div>
    	
      <!-- /.row -->
      <!-- Main row -->
      <!-- /.row (main row) -->
    </div><!-- /.container-fluid -->
  </section>