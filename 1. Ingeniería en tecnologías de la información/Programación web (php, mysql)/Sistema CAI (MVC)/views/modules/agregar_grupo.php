 <?php 

 	if(!isset($_SESSION['validar'])){

		echo '<script> alert("No haz iniciado sesion") </script>';
		echo '<script> window.location = "index.php"; </script>';
 		//header('Location:dashboard.php');
 	}



  ?>

  <section class="content">
    <div class="container-fluid" style="width: 60%;">
    	<?php 

    	if(isset($_GET['status'])){
    		if($_GET['status'] == 'password'){
    			echo '	<div class="alert alert-warning alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-ban"></i> Incorrecto!</h5>
		                  Las contraseñas no coinciden
		                </div>';
    		}
    	}


    	 ?>
    	<div class="card" align="center">
	      <div class="card-header row">
	      	<div class="col-sm-6" align="left">
	      		<h3 class="card-title">Nuevo Grupo</h3>
	      	</div>	        
	      </div>
	      <div style="">
	      	  <form class="form-horizontal" style="text-align: center;" method="post">
	            <?php 

	            	$mvc = new Mvc();
	            	$mvc -> agregarGrupoController();
	            	$mvc -> registroGrupoController();
	            	
	            	
	             ?>
	            <!-- /.card-footer -->
	          </form>
	      </div>
	      
	    </div>
      <!-- /.row -->
      <!-- Main row -->
      <!-- /.row (main row) -->
    </div><!-- /.container-fluid -->
  </section>