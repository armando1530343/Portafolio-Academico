 <?php 


 	if(!isset($_SESSION['validar'])){

		echo '<script> alert("No haz iniciado sesion") </script>';
		echo '<script> window.location = "index.php"; </script>';
 		//header('Location:dashboard.php');
 	}
 ?>

 <div class="login">
  <br><br><br>
  <div class="card card-info">
    <div class="card-header">
      <h1 class="card-title" align="center">Confirmar contraseña de usuario</h1>
    </div>
    <!-- /.card-header -->
    <!-- form start -->

    <?php 
    	$mvc = new MvcController();
    	$mvc -> 
     ?>

    <form class="form-horizontal" method="post">
      <br><br>
      <div class="card-body">
        
        <div class="form-group">
          <div class="col-sm-12">
            <input type="password" class="form-control" name="password" placeholder="Password">
          </div>
        </div>
      </div>
      <!-- /.card-body -->
      <div class="card-footer" align="center">
        <button type="submit" class="btn btn-success">Aceptar</button>
      </div>
      <br>
      <!-- /.card-footer -->
    </form>
  </div>
</div>