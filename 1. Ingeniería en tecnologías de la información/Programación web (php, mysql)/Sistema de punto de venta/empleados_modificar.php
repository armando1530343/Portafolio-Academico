<?php
    session_start();
    
    if($_SESSION['usuario']!="administrador"){
        header('Location: index.php');
    }

    include("conexion.php");
    

    $modifico = false;//no se ha eliminado una fila
    $buscarid = null;
    $preciona = false;

    //indica se se preciono el boton de eliminar
    if(isset($_POST['modifica'])){
      $preciono = true;
      //modifica la fila con el id seleccionado
      $modifica = $conexion->query("UPDATE empleado set nombre = '".$_POST['nombre']."', apellidos = '".$_POST['apellido']."', edad =".$_POST['edad'].", domicilio = '".$_POST['domicilio']."', usuario = '".$_POST['usuario']."', clave = '".$_POST['password']."' where Id = ".$_POST['modificaID']);
      //muestra mensaje
      if($modifica){
        $modifico = true;//se elimino una fila
      }
    }

    $consultaProductos2 = $conexion->query("SELECT * FROM empleado");
    
    if(isset($_POST['busca_id'])){
      if($_POST['idProd']!=""){
        $buscarid = $conexion->query("SELECT * from empleado where Id = ".$_POST['idProd'])->fetch_assoc();
        $eliminaId= $buscarid['Id'];        
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
                            
                            <?php if($modifico==true){?>
                            <div class="alert alert-success alert-dismissible fade in" role="alert">
                                <button type="button" class="close" data-dismiss="alert"
                                        aria-label="Close">
                                    <span aria-hidden="true">&times;</span>
                                </button>
                                <strong>Datos Guardados!</strong> El producto se modific?? correctamente.
                            </div>
                            <?php } ?>
                          </div>

                        </div>
                        <div class="row">
                          <div class="col-lg-12">
                              <div class="card-box">
                                  <h2 style="color: red">Modificar datos de Empleados</h2>
                                  <form class="form-horizontal" method="POST" action="">
                                        <div class="form-group">
                                            <label for="userName">Selecciona Id del Empleado:<span class="text-danger">*</span></label>
                                            <select class="form-control select2" name="idProd">
                                                <option></option>
                                                <?php while($con2 = $consultaProductos2->fetch_assoc()){ ?>
                                                    <option><?php echo $con2['Id']; ?> </option>
                                                <?php } ?>                                                      
                                            </select><br>
                                            <button class="btn btn-primary waves-light" type="" name="busca_id">
                                                Mostrar datos
                                            </button><br><br>
                                            
                                        </div> 
                                  </form>
                                  <form class="form-horizontal" method="POST" action="">
                                        <div class="form-group">

                                            
                                            <label for="caja1">ID<span class="text-danger">*</span></label>
                                            <input type="text" class="form-control" name="modificaID" id="caja1" placeholder="Id Empleado" value="<?php echo $buscarid['Id']; ?>" required><br>

                                            <label for="caja1">Nombre<span class="text-danger">*</span></label>
                                            <input type="text" class="form-control" name="nombre" id="caja1" placeholder="Nombre" value="<?php echo $buscarid['nombre']; ?>" required>
                                            
                                            <label for="userName2">Apellidos<span class="text-danger">*</span></label>
                                            <input type="text" name="apellido" parsley-trigger="change" placeholder="Apellidos" class="form-control" id="userName2" value="<?php echo $buscarid['apellidos']; ?>" required>
                                            
                                            <label for="userName2">Edad<span class="text-danger">*</span></label>
                                            <input type="number" name="edad" parsley-trigger="change" placeholder="Edad" class="form-control" id="userName2" value="<?php echo $buscarid['edad']; ?>" required>
                                            
                                            <label for="userName">Domicilio<span class="text-danger">*</span></label>
                                            <input type="text" name="domicilio" parsley-trigger="change" placeholder="Domicilio" class="form-control" id="userName3" value="<?php echo $buscarid['domicilio']; ?>" required>
                                            
                                            <label for="userName">Usuario<span class="text-danger">*</span></label>
                                            <input type="text" name="usuario" parsley-trigger="change" placeholder="Nombre de Usuario" class="form-control" id="userName4" value="<?php echo $buscarid['usuario']; ?>" required>
                                            
                                            <label for="userName">Contrase??a<span class="text-danger">*</span></label>
                                            <input type="text" name="password" parsley-trigger="change" placeholder="Contrase??a" class="form-control" id="userName4" value="<?php echo $buscarid['clave']; ?>" required>
                                        
                                        </div> 

                                        <div class="form-group text-right m-b-0">
                                            
                                            <button type="" class="btn btn-success waves-effect m-l-5" name="modifica">
                                                Guardar Modificaci??n
                                            </button>
                                        </div>
                                  </form>
                              </div>
                          </div>
                        </div> <!-- end col -->

                      
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