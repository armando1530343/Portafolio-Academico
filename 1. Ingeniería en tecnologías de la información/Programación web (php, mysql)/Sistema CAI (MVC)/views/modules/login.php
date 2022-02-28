<div class="login">
  <br><br><br>
  <div class="card card-info">
    <!-- /.card-header -->
    <!-- form start -->
    <?php 

    #alerta de advertencia si no existe el usuario ingresado

      if(isset($_GET['action'])){
        if($_GET['action'] == 'error'){
          echo '  <div class="alert alert-warning alert-dismissible">
                      <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
                      <h5><i class="icon fa fa-warning"></i> Incorrecto!</h5>
                      No existe la cuenta de usuario.
                    </div>';
        }
      }

     ?>

    <form class="form-horizontal" method="post">
      <br><br>
      <h1>Sistema CAI</h1>
      <div class="card-body">
        <div class="form-group">
          <div class="col-sm-12">
            <input type="text" class="form-control" name="username" placeholder="Username">
          </div>
        </div>
        <div class="form-group">
          <div class="col-sm-12">
            <input type="password" class="form-control" name="password" placeholder="Password">
          </div>
        </div>
      </div>
      <!-- /.card-body -->
      <div class="card-footer" align="center">
        <button type="submit" name="ingresar" class="btn btn-success">Ingresar</button>
      </div>
      <br>
      <!-- /.card-footer -->
    </form>
  </div>
</div>

<?php

#se llama al controlador para ingresar al usuario

$ingreso = new Mvc();
$ingreso -> ingresaAdminController();

//include_once('links/link2.php');

?>