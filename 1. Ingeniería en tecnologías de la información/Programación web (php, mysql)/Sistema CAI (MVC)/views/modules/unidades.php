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
		                  Se agregó una Unidad
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
		                  Se elimino una Unidad
		                </div>';
    		}
    		else if($_GET['status'] == 'error'){
    			echo '	<div class="alert alert-danger alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-ban"></i> Error!</h5>
		                  No se pudo guardar los cambios
		                </div>';
    		}
    		else if($_GET['status'] == 'existe'){
    			echo '	<div class="alert alert-warning alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-warning"></i> Incorrecto!</h5>
		                  Ya existe el periodo de unidad
		                </div>';
    		}
    	}

    	$mvc = new Mvc();
    	$grupo = $mvc->getGrupoController();


    	 ?>
	    <div class="card">
	      <div class="card-header row">
	      	<div class="col-sm-4" align="left">
	      		<h3 class="card-title"><?php echo 'Teacher: '.$grupo[0]['teacher']; ?></h3>
	      		<h3 class="card-title"><?php echo 'Grupo: '.$grupo[0]['grupo']; ?></h3>
	      		
	      	</div>
	      	<div class="col-sm-4" align="center">
	      		<h3 class="card-title">Unidades</h3>
	      	</div>
	      	<div class="col-sm-4" align="right">     
	      		<?php if($_GET['user'] == 'admin'){ ?> 		
	            <a href="index.php?user=admin&action=agregar_unidad&id_grupo=<?php echo $_GET['id_grupo']?>" class="btn btn-success">Dar de alta Unidad</a>
	            <?php } ?>          
	      	</div>
	        
	      </div>
	      <!-- /.card-header -->
	      <div class="card-body">
	        <table id="example1" class="table table-bordered table-striped">
	          <thead>
	          <tr>
	          	<th>Nombre</th>
	          	<th>Fecha Inicio</th>
	          	<th>Fecha Fin</th>
	          	<th>Horas</th>
	          	<?php if($_GET['user'] == 'admin'){ ?> 	
	            <th></th>
	            <th></th>
	        	<?php } ?>
	          </tr>
	          </thead>
	          <tbody>
	          <?php 

		          $mvc = new Mvc();
		          $mvc -> vistaUnidadesController();

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