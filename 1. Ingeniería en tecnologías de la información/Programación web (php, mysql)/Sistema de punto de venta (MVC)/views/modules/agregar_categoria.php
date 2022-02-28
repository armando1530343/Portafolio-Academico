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
    		if($_GET['status'] == 'passwords'){
    			echo '	<div class="alert alert-warning alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-warning"></i> Incorrecto!</h5>
		                  Las contraseñas no coinciden.
		                </div>';
    		}
    	}


    	 ?>
    	<div class="row" style="width: 80%;">    		
    		<div class="col-sm-12">
			  	<div class="card card-info">	
		          <div class="card-header">
		            <h3 class="card-title">Agregar Categoria</h3>
		          </div>
		          <!-- /.card-header -->
		          <!-- form start -->
		          <form class="form-horizontal" style="text-align: center;" method="post">
		            <?php 

		            	$mvc = new MvcController();
		            	$mvc -> agregarCategoriaController();
		            	$mvc -> registroCategoriaController();

		            	if($_POST)
		            		echo '<script> window.location = "index.php?action=productos&status='.$respuesta2.'"; </script>';

		             ?>
		            <!-- /.card-footer -->
		          </form>
		          
		          
		        </div>
		    </div>
		</div>
      <!-- /.row -->
      <!-- Main row -->
      <!-- /.row (main row) -->
    </div><!-- /.container-fluid -->
  </section>