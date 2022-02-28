 <?php 

 	if($_SESSION['validar']==false){

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
		                  Alumno registrado
		                </div>';
    		}
    		else if($_GET['status'] == 'salida'){
    			echo '	<div class="alert alert-warning alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-warning"></i>Salida !</h5>
		                  Salio un alumno antes de terminar la hora.
		                </div>';
    		}
    		else if($_GET['status'] == 'error'){
    			echo '	<div class="alert alert-danger alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-ban"></i> Error!</h5>
		                  No se pudo guardar el registro
		                </div>';
    		}
    		else if($_GET['status'] == 'error_alumno'){
    			echo '	<div class="alert alert-danger alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-ban"></i> Error!</h5>
		                  No se pudo guardar el Alumno
		                </div>';
    		}    		
    		else{
    			echo '	<div class="alert alert-warning alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-warning"></i> Incorrecto!</h5>
		                  El codigo de producto ingresado ya existe en la tienda.
		                </div>';
    		}
    	}


    	 ?>
	    <div class="card">
	      <div class="card-header row">
	      	<div class="col-sm-6" align="left">
	      		<h3 class="card-title">Visitas al CAI</h3>
	      	</div>
	      	<div class="col-sm-6" align="right">    	
	      	<?php if($_SESSION['visitas'] == true && $_SESSION['tiempo'] >= $_SESSION['hora_inicio'] && $_SESSION['tiempo'] < $_SESSION['hora_limite']){?>  		
	            <a href="index.php?user=admin&action=agregar_visita" class="btn btn-success">Nuevo Registro</a>	
	            <?php } ?>           
	            <a href="index.php?user=admin&action=historial" class="btn btn-info">Ver Historial</a>
	      	</div>
	        
	      </div>
	      <!-- /.card-header -->
	        <div class="card-body">
	        	<?php 

			      if($_SESSION['visitas'] == true){

			    ?>
		        <table id="example1" class="table table-bordered table-striped">
		          <thead>
		        	<tr>
		          	<th>No.Registro</th>
		          	<th>Alumno</th>
		            <th>Teacher</th>
		            <th>Grupo</th>
		            <th>Unidad</th>
	              	<th>Actividad</th>
		            <th></th>
		          </tr>
		          </thead>
		          <tbody>
		          <?php 

			          $mvc = new Mvc();
			          $mvc -> vistaVisitasController();

		          ?> 
		          
		          </tbody>
		          
		        </table>
		    <?php }else{ ?>
		    	<h3>No es horario de visitas</h3>
		    <?php } ?>
	        </div>
	      <!-- /.card-body -->
	    </div>
      <!-- /.row -->
      <!-- Main row -->
      <!-- /.row (main row) -->
    </div><!-- /.container-fluid -->
  </section>