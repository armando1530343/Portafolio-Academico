 <?php 

  if(!isset($_SESSION['validar'])){

    echo '<script> alert("No haz iniciado sesion") </script>';
    echo '<script> window.location = "index.php"; </script>';
    //header('Location:dashboard.php');
  }


  ?>
<div style="width: 50%;">
  <br><br><br>
  <div class="card card-info">
    <div class="card-header">
      <h1 class="card-title" align="center">Eliminar Usuario - Confirmar contraseña</h1>
    </div>
    <!-- /.card-header -->
    <!-- form start -->
    <?php 
      if(isset($_GET['status'])){
        if($_GET['status'] == 'error'){
          echo '  <div class="alert alert-warning alert-dismissible">
                      <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
                      <h5><i class="icon fa fa-warning"></i> Incorrecto!</h5>
                      Contraseña Incorrecta.
                    </div>';
        }
      }

     ?>
    
     

    <form class="form-horizontal" method="post">
      <br><br>
      <div class="card-body">
        <div class="form-group">
          <div class="col-sm-12">
            <input type="password" class="form-control" name="password" placeholder="Contraseña">
          </div>
        </div>
      </div>
      <!-- /.card-body -->
      <div class="card-footer" align="center">
        <button type="submit" class="btn btn-success">Confirmar</button>
        <a href="index.php?action=usuarios" class="btn btn-default">Cancelar</a>
      </div>
      <br>
      <!-- /.card-footer -->
    </form>
  </div>
</div>

<?php

$ingreso = new MvcController();
$ingreso -> eliminaUsuarioController();

?>