<?php
    session_start();
    //echo "".$_SESSION['usuario'];
    if($_SESSION['usuario']!="administrador"){
        header('Location: index.php');
    }

    $guarda = false;
    $existe = false;
    $elimino = false;
    $buscarid = null;
    $error = false;

    include("conexion.php");

    //captura los datos de la base de datos en un advanced table
    $consultaCategoria = $conexion->query("SELECT * FROM categoria");

    if(isset($_POST['agrega'])){
      //se obtienen los valores de los campos
      $name = $_REQUEST['nombre'];

      $validar = current($conexion->query("SELECT COUNT(*) from categoria where nombre = '$name'")->fetch_assoc());

      if($validar > 0){
        $existe = true;
      }
      else{
        //se insertan los valores de los campos en la base de datos
        $insertar = $conexion->query("INSERT INTO categoria(nombre) VALUES('$name')");
        $guarda = true;
      }
      
    }
    $categorias = $conexion->query("SELECT * from categoria");

    //indica se se preciono el boton de eliminar
    if(isset($_POST['elimina'])){
      //elimina la fila con el id seleccionado
      $eliminar = $conexion->query("DELETE from categoria where id = ".$_POST['eliminaID']);
      //muestra mensaje
      if($eliminar){
        $elimino = true;//se elimino una fila
      }
      else{$error=true;}
    }

    
    
    if(isset($_POST['busca_id'])){
      if($_POST['idProd']!=""){
        $buscarid = $conexion->query("SELECT * from categoria where id = ".$_POST['idProd'])->fetch_assoc();
        $eliminaId= $buscarid['id'];        
      }
    }
?>


<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="utf-8" />
        <title>Administador CyberGames</title>
        <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no" />
        <meta content="A fully featured admin theme which can be used to build CRM, CMS, etc." name="description" />
        <meta content="Coderthemes" name="author" />
        <meta http-equiv="X-UA-Compatible" content="IE=edge" />

        <link rel="shortcut icon" href="assets/images/favicon.ico">

        <!--Morris Chart CSS -->
		<link rel="stylesheet" href="assets/plugins/morris/morris.css">

        <!-- Bootstrap core CSS -->
        <link href="assets/css/bootstrap.min.css" rel="stylesheet">
        <!-- MetisMenu CSS -->
        <link href="assets/css/metisMenu.min.css" rel="stylesheet">
        <!-- Icons CSS -->
        <link href="assets/css/icons.css" rel="stylesheet">
        <!-- Custom styles for this template -->
        <link href="assets/css/style.css" rel="stylesheet">

    </head>


    <body>

        <div id="page-wrapper">

            <!-- Top Bar Start -->
            <div class="topbar">

                <!-- LOGO -->
                <div class="topbar-left">
                    <div class="">
                        
                            <img src="imagenes/logo2.jpg" width="150" height="65" class="logo" class="logo-lg" />
                        
                    </div>
                </div>
                <div class="topbar-left">
                    <!--<div class="">!-->
                    <!--<h2>Cybergames</h2>

                        
                    <!--</div>!-->
                </div>


                <!-- Top navbar -->
                <div class="navbar navbar-default" role="navigation">
                    <div class="container">
                        <div class="">

                            <!-- Mobile menu button -->
                            <div class="pull-left">
                                <button type="button" class="button-menu-mobile visible-xs visible-sm">
                                    <i class="fa fa-bars"></i>
                                </button>
                                <span class="clearfix"></span>
                            </div>

                            <!-- Top nav left menu -->
                            <ul class="nav navbar-nav hidden-sm hidden-xs top-navbar-items">
                                <li><a href="admin_perfil.php">Perfil</a></li>
                                <li><a href="contactos.php">Contactos</a></li>
                                <li><a href="calendario.php">Calendario</a></li>
                            </ul>

                            <!-- Top nav Right menu -->
                            <ul class="nav navbar-nav navbar-right top-navbar-items-right pull-right">
                                <li class="hidden-xs">
                                    <form role="search" class="navbar-left app-search pull-left">
                                         <input type="text" placeholder="Search..." class="form-control">
                                         <a href=""><i class="fa fa-search"></i></a>
                                    </form>
                                </li>
                                <li class="dropdown top-menu-item-xs">
                                    <a href="" class="dropdown-toggle menu-right-item profile" data-toggle="dropdown" aria-expanded="true"><img src="imagenes/avatar1.jpg" alt="user-img" class="img-circle"> </a>
                                    <ul class="dropdown-menu">
                                        <li><a href="admin_perfil.php"><i class="ti-user m-r-10"></i> Perfil</a></li>
                                        <li><a href="index.php"><i class="ti-power-off m-r-10"></i> Cerrar sesi??n</a></li>
                                    </ul>
                                </li>
                            </ul>
                        </div>
                    </div> <!-- end container -->
                </div> <!-- end navbar -->
            </div>
            <!-- Top Bar End -->


            <!-- Page content start -->
            <div class="page-contentbar">

                <!--left navigation start-->
                <aside class="sidebar-navigation">
                    <div class="scrollbar-wrapper">
                        <div>
                            <button type="button" class="button-menu-mobile btn-mobile-view visible-xs visible-sm">
                                <i class="mdi mdi-close"></i>
                            </button>
                            <!-- User Detail box -->
                            <div class="user-details">
                                <div class="pull-left">
                                    <img src="imagenes/avatar1.jpg" alt="" class="thumb-md img-circle">
                                </div>
                                <div class="user-info">
                                    <a href="#">Armando</a>
                                    <p class="text-muted m-0">Administrator</p>
                                </div>
                            </div>
                            <!--- End User Detail box -->

                            <!-- Left Menu Start -->
                            <ul class="metisMenu nav" id="side-menu">
                                <li><a href="admin.php"><i class="ti-home"></i> Tablero </a></li>

                                <li><a href="ventas.php"><i class="mdi mdi-shopping-music"></i> Ventas </a>
                                </li>
                                <li><a href="typography.html"><i class="mdi mdi-xbox-controller"></i> Productos </a>
                                  <ul class="nav-second-level nav" aria-expanded="true">
                                      <li><a href="productos_agregar.php">Nuevo Producto</a></li>
                                      <li><a href="productos_modificar.php">Modificar Producto</a></li>
                                      <li><a href="productos_inventario.php">Inventario</a></li>
                                      <li><a href="productos_consulta.php">Consulta</a></li>
                                      <li><a href="categorias.php">Categorias</a></li>
                                  </ul>
                                </li>
                                <li><a href="clientes.php"><i class="mdi mdi-account-check"></i> Clientes </a></li>
                                <li><a href="typography.html"><i class="mdi mdi-account-key"></i> Empleados </a>
                                    <ul class="nav-second-level nav" aria-expanded="true">
                                        <li><a href="empleados_agregar.php">Nuevo Empleado</a></li>
                                        <li><a href="empleados_modificar.php">Modificar Empleado</a></li>
                                        <li><a href="empleados_eliminar.php">Eliminar Empleado</a></li>
                                        <li><a href="empleados.php">Ver Empleados</a></li>
                                    </ul>
                                </li>
                                <li><a href="mantenimiento.php"><i class="mdi mdi-wrench"></i>Mantenimiento </a></li>
                                <li><a href="typography.html"><i class="mdi mdi-wallet-travel"></i> Proveedores </a>
                                    <ul class="nav-second-level nav" aria-expanded="true">
                                        <li><a href="proveedores_agregar.php">Nuevo Proveedor</a></li>
                                        <li><a href="proveeodres_eliminar.php">Eliminar Proveedor</a></li>
                                        <li><a href="proveedores.php">Ver Proveedores</a></li>
                                    </ul>    
                                </li>
                            </ul>
                        </div>
                    </div><!--Scrollbar wrapper-->
                </aside>
                <!--left navigation end-->

                <!-- START PAGE CONTENT -->
                <div id="page-right-content">

                    <div class="container">
                        <div class="row">
                          <div class="col-sm-12">
                            <div class="widget-inline-box text-center">
                              <?php
                                $dias = array('Domingo', 'Lunes', 'Martes', 'Miercoles', 'Jueves', 'Vienes', 'Sabado');
                                $meses = array('Enero','Febrero','Marzo','Abril','Mayo','Junio','Julio','Agosto','Septiembre','Octubre','Noviembre','Diciembre');
                                //$dia = $dias[getDay()];
                                $numDia = date('d');
                                $mes = date('m');
                                $anio = date('y');
                                
                              ?>
                              <h2><?php echo "Fecha Actual: ".$numDia." - ".$mes." - 20".$anio; ?></h2>
                            </div>
                            <?php if ($guarda == true){?>
                            <div class="alert alert-success alert-dismissible fade in" role="alert">
                                <button type="button" class="close" data-dismiss="alert"
                                        aria-label="Close">
                                    <span aria-hidden="true">&times;</span>
                                </button>
                                <strong>Guardado Exitoso!</strong> Se a??adi?? un correctamente la categoria.
                            </div>
                            <?php } if($existe == true) {?>
                            <div class="alert alert-warning alert-dismissible fade in" role="alert">
                                <button type="button" class="close" data-dismiss="alert"
                                        aria-label="Close">
                                    <span aria-hidden="true">&times;</span>
                                </button>
                                <strong>Inv??lido!</strong> Ya existe la categoria.
                            </div>
                            <?php } if($elimino==true){?>
                            <div class="alert alert-success alert-dismissible fade in" role="alert">
                                <button type="button" class="close" data-dismiss="alert"
                                        aria-label="Close">
                                    <span aria-hidden="true">&times;</span>
                                </button>
                                <strong>Se elimin??!</strong> Se ha eliminado el proveedor de la base de datos.
                            </div>
                            <?php } if($error == true) {?>
                            <div class="alert alert-danger alert-dismissible fade in" role="alert">
                                <button type="button" class="close" data-dismiss="alert"
                                        aria-label="Close">
                                    <span aria-hidden="true">&times;</span>
                                </button>
                                <strong>Error!</strong> No se pudo eliminar la categoria ya que existe una relaci??n entre otros datos.
                            </div>
                            <?php } ?>
                            
                          </div>

                        </div>
                        <div class="row">
                          <div class="col-lg-12">
                              <div class="card-box">
                                  <h2 style="color: red">Categorias de Producto</h2>
                                  <ul class="nav nav-tabs">
                                      <li class="active">
                                          <a href="#eliminar" data-toggle="tab" aria-expanded="false">
                                              <span class="visible-xs"><i class="fa fa-user"></i></span>
                                              <span class="hidden-xs">Eliminar</span>
                                          </a>
                                      </li>
                                      <li class="">
                                          <a href="#lista" data-toggle="tab" aria-expanded="false">
                                              <span class="visible-xs"><i class="fa fa-envelope-o"></i></span>
                                              <span class="hidden-xs">Lista de Categorias</span>
                                          </a>
                                      </li>
                                      <li class="">
                                          <a href="#nueva" data-toggle="tab" aria-expanded="true">
                                              <span class="visible-xs"><i class="fa fa-home"></i></span>
                                              <span class="hidden-xs">A??adir Nueva</span>
                                          </a>
                                      </li>
                                      
                                      
                                  </ul>
                                  <div class="tab-content">
                                      <div class="tab-pane active" id="eliminar">
                                          <form class="form-horizontal" method="POST" action="">
                                                <div class="form-group">
                                                    <label for="userName">Selecciona Id de Categoria:<span class="text-danger">*</span></label>
                                                    <select class="form-control select2" name="idProd">
                                                        <option></option>
                                                        <?php while($con2 = $consultaCategoria->fetch_assoc()){ ?>
                                                            <option><?php echo $con2['id']; ?> </option>
                                                        <?php } ?>                                                      
                                                    </select><br>
                                                    
                                                    <label for="caja1">ID<span class="text-danger">*</span></label>
                                                    <input type="text" class="form-control" name="eliminaID" id="caja1" placeholder="Id Proveedor" value="<?php echo $buscarid['id']; ?>"><br>
                                                    
                                                    <table id="" class="table table-striped table-bordered">
                                                        <thead>
                                                          <tr>
                                                              <th>Id</th>
                                                              <th>Nombre</th>
                                                          </tr>
                                                        </thead>

                                                        <tbody>                                                      
                                                          <tr>
                                                            <td><?php echo $buscarid['id']; ?></td>
                                                            <td><?php echo $buscarid['nombre']; ?></td>     
                                                          </tr>
                                                        </tbody>
                                                    </table>
                                                </div> 

                                                <div class="form-group text-right m-b-0">
                                                    <button class="btn btn-primary waves-light" type="" name="busca_id">
                                                        Mostrar datos
                                                    </button>
                                                    <button type="" class="btn btn-danger waves-effect m-l-5" name="elimina">
                                                        Eliminar Producto
                                                    </button>
                                                </div>
                                          </form>
                                      </div>
                                      <div class="tab-pane" id="lista">                                              
                                          <div class="table-responsive m-b-20">
                                              <table id="datatable" class="table table-striped table-bordered">
                                                  <thead>
                                                  <tr>
                                                      <th>Id</th>
                                                      <th>Nombre</th>                                                      
                                                  </tr>
                                                  </thead>

                                                  <tbody>
                                                  <?php while($con = $categorias->fetch_assoc()){ ?>
                                                  <tr>
                                                    <td><?php echo $con['id']; ?></td>
                                                    <td><?php echo $con['nombre']; ?></td>
                                                  </tr>
                                                  <?php } ?>

                                                  </tbody>
                                              </table>
                                          </div>
                                      </div>
                                      <div class="tab-pane" id="nueva">
                                          <form class="form-horizontal" method="post" action="">
                                              <div class="form-group" >
                                                  <label for="caja1">Nombre<span class="text-danger">*</span></label>
                                                  <input type="text" class="form-control" name="nombre" id="caja1" placeholder="Nombre de categoria" required>
                                              </div>                                             
                                              
                                              <div class="form-group text-right m-b-0">
                                                  <button class="btn btn-primary waves-effect waves-light" type="submit" name="agrega">
                                                      A??adir Categoria
                                                  </button>                                                  
                                              </div>
                                              
                                          </form>
                                      </div>
                                      
                                  </div>  
                              </div>
                          </div>
                        </div> <!-- end col -->
                        <div class="row">
                            <div class="col-lg-12">
                                <div class="card-box">
                                    <h4 class="m-t-0">Productos por Categoria</h4>
                                    <div id="categoria-producto" style="height: 300px;"></div>
                                </div>
                            </div> <!-- end col -->
                        </div>
                        <div class="row">
                            <div class="col-lg-12">
                                <div class="card-box">
                                    <h4 class="m-t-0">Ingresos por Categoria</h4>
                                    <div id="ingresos-categoria" style="height: 300px;"></div>
                                </div>
                            </div> <!-- end col -->
                        </div>

                      
                      </div>
                        


                    </div>
                    <!-- end container -->

                  

                </div>
                <!-- End #page-right-content -->

            </div>
            <!-- end .page-contentbar -->
        </div>
        <!-- End #page-wrapper -->



        <!-- js placed at the end of the document so the pages load faster -->
        <script src="assets/js/jquery-2.1.4.min.js"></script>
        <script src="assets/js/bootstrap.min.js"></script>
        <script src="assets/js/metisMenu.min.js"></script>
        <script src="assets/js/jquery.slimscroll.min.js"></script>

        <!--Morris Chart-->
    <script src="assets/plugins/morris/morris.min.js"></script>
    <script src="assets/plugins/raphael/raphael-min.js"></script>
    <script src="assets/pages/jquery.morris.init.js"></script>

    <?php include('graficas3.php'); ?>
    <?php include('grafica_ingresos_categoria.php'); ?>
    <?php include('datatables.php'); ?>

    <!--<script src="assets/pages/jquery.dashboard.js"></script>-->

        <!-- Flot chart -->
        <script src="assets/plugins/flot-chart/jquery.flot.min.js"></script>
        <script src="assets/plugins/flot-chart/jquery.flot.time.js"></script>
        <script src="assets/plugins/flot-chart/jquery.flot.tooltip.min.js"></script>
        <script src="assets/plugins/flot-chart/jquery.flot.resize.js"></script>
        <script src="assets/plugins/flot-chart/jquery.flot.pie.js"></script>
        <script src="assets/plugins/flot-chart/jquery.flot.selection.js"></script>
        <script src="assets/plugins/flot-chart/jquery.flot.stack.js"></script>
        <script src="assets/plugins/flot-chart/jquery.flot.orderBars.min.js"></script>
        <script src="assets/plugins/flot-chart/jquery.flot.crosshair.js"></script>
        <script src="assets/pages/jquery.flot.init.js"></script>

        <!-- KNOB JS -->
        <!--[if IE]>
        <script type="text/javascript" src="assets/plugins/jquery-knob/excanvas.js"></script>
        <![endif]-->
        <script src="assets/plugins/jquery-knob/jquery.knob.js"></script>

        <!-- App Js -->
        <script src="assets/js/jquery.app.js"></script>

        <script type="text/javascript">
            $('[data-plugin="knob"]').each(function(idx, obj) {
                $(this).knob();
             });
        </script>


    </body>
</html>