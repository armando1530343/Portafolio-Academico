 <?php 

 	if(!isset($_SESSION['validar'])){

		echo '<script> alert("No haz iniciado sesion") </script>';
		echo '<script> window.location = "index.php"; </script>';
 		//header('Location:dashboard.php');
 	}



  ?>

  <section class="content">
    <div class="container-fluid">
    	<div class="row">
    		<div class="col-sm-12">
			  	<div class="card card-info">	
		          <div class="card-header">
		            <h3 class="card-title">Editar Usuario</h3>
		          </div>
		          <div class="row">
		          	  <div class="col-sm-4" align="center">    			          
				           	<br><br>
				            	        
				            <img src="user.png" width="200">  
				        
					  </div>
			          <div class="col-sm-8">
				          <!-- /.card-header -->
				          <!-- form start -->
				          <form class="form-horizontal" style="text-align: center;" method="post">
				            <?php 

				            	$mvc = new MvcController();
				            	$mvc -> editarUsuariosController();
				            	$mvc -> actualizarUsuarioController();
				            	

				             ?>
				            <!-- /.card-footer -->
				          </form>
				      </div>

					</div>
			    </div>
		    </div>
		</div>
	  <!-- /.row -->
      <!-- Main row -->
      <!-- /.row (main row) -->
    </div><!-- /.container-fluid -->
  </section>