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
    		<div class="col-sm-8">
			  	<div class="card card-info">	
		          <div class="card-header">
		            <h3 class="card-title">Nueva Visita</h3>
		          </div>
		          <!-- /.card-header -->
		          <!-- form start -->
		          <form class="form-horizontal" style="text-align: center;" method="post">
		            <?php 

		            	$mvc = new Mvc();
		            	$mvc -> agregarVisitaController();
		            	//$respuesta1 = $mvc -> registroProductosController();
		            	//$respuesta2 = $mvc -> agregaHistorialController($respuesta1);
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