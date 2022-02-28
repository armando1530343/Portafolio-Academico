 <?php 

 	if(!isset($_SESSION['validar'])){

		echo '<script> alert("No haz iniciado sesion") </script>';
		echo '<script> window.location = "index.php"; </script>';
 		//header('Location:dashboard.php');
 	}



  ?>

  <section class="content">
    <div class="container-fluid">
    	<div class="row"  style="width: 80%;">
    		<div class="col-sm-12">
			  	<div class="card card-info">	
		          <div class="card-header">
		            <h3 class="card-title">Editar Categoria</h3>
		          </div>
		          <form class="form-horizontal" style="text-align: center;" method="post">
		            <?php 

		            	$mvc = new MvcController();
		            	$mvc -> editarCategoriaController();
		            	$mvc -> actualizarCategoriaController();
		            	

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