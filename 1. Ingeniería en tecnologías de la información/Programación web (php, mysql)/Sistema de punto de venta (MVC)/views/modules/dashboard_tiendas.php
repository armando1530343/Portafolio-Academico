<?php 
  
  $mvc = new MvcController();
/*
  $historial = $mvc->dashboardStockController();
  $productos = $mvc->dashboardProductosController();
  $usuarios = $mvc->dashboardUsuariosController();
  $categorias = $mvc->dashboardCategoriasController();
  */

  $mvc->estadoTiendaController();


 ?>

  <section class="content">
    <div class="container-fluid">
      <?php 

      if(isset($_GET['status'])){
        if($_GET['status'] == 'registrado'){
          echo '  <div class="alert alert-success alert-dismissible">
                      <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
                      <h5><i class="icon fa fa-check"></i>Correcto !</h5>
                      Se agregó una nueva Tienda.
                    </div>';
        }
        else if($_GET['status'] == 'borrado'){
          echo '  <div class="alert alert-success alert-dismissible">
                      <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
                      <h5><i class="icon fa fa-check"></i>Correcto !</h5>
                      Se elimino la una Tienda.
                    </div>';
        }
        else if($_GET['status'] == 'error'){
          echo '  <div class="alert alert-danger alert-dismissible">
                      <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
                      <h5><i class="icon fa fa-ban"></i> Error!</h5>
                      No se pudo guardar la actualizacion.
                    </div>';
        }
        else{
          echo '  <div class="alert alert-warning alert-dismissible">
                      <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
                      <h5><i class="icon fa fa-warning"></i> Incorrecto!</h5>
                      El nombre de la Tienda ya existe.
                    </div>';
        }
      }


       ?>
      <div class="card">
        <div class="card-header row">
          <div class="col-sm-6" align="left">
            <h3 class="card-title">Tiendas</h3>
          </div>
          <div class="col-sm-6" align="right">          
              <a href="index.php?action=agregar_tienda" class="btn btn-success">Nueva Tienda</a>             
          </div>
          
        </div>
        <!-- /.card-header -->
        <div class="card-body">
          <table id="example1" class="table table-bordered table-striped">
            <thead>
            <tr>
              <th>Nombre</th>
              <th>Estado</th>
              <th>Autor</th>
              <th>Fecha</th>
              <th>Fecha Modificacion</th>
              <th></th>
              <th></th>
              <th></th>
              <th></th>
            </tr>
            </thead>
            <tbody>
            <?php 

            $mvc = new MvcController();
            $mvc -> vistaTiendasController(); 

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