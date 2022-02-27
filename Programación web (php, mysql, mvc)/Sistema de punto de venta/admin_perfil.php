<?php
    session_start();
    //echo "".$_SESSION['usuario'];
    if($_SESSION['usuario']!="administrador"){
        header('Location: index.php');
    }

    include("conexion.php");

    $consulta1 = $conexion->query("SELECT * FROM administrador WHERE usuario = '$user' and clave = '$pass'");
    $consulta2 = $conexion->query("SELECT * FROM empleado WHERE usuario = '$user' and clave = '$pass'");

    if($consulta1->num_rows > 0){
      $_SESSION["usuario"] = "administrador";
      //return true;
    }
    elseif ($consulta2->num_rows > 0){
      $_SESSION["usuario"] = "empleado";
      //return true;
    }

    //cuenta el numero de ventas que hay en la base de datos
    $numVentas = current($conexion->query("SELECT count(*) from venta")->fetch_assoc());
    //cuenta el total de ingresos acumulados de las ventas
    $ingresosTotales = current($conexion->query("SELECT SUM(total) from venta")->fetch_assoc());

    $dia = date('d');
    $reporte = $conexion->query("SELECT * from venta where DAY(fecha) = $dia");

    //$conexion->close();

    
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
                                        <li><a href="index.php"><i class="ti-power-off m-r-10"></i> Cerrar sesión</a></li>
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

                <div id="page-right-content">

                    <div class="container">
                        <div class="row">
                            <div class="col-md-12">
                                <div class="p-0 text-center">
                                    <div class="member-card">
                                        <div class="thumb-xl member-thumb m-b-10 center-block">
                                            <img src="imagenes/avatar.jpg" class="img-circle img-thumbnail" alt="profile-image">
                                            <i class="mdi mdi-star-circle member-star text-success" title="verified user"></i>
                                        </div><br>

                                        <div class="">
                                            <h4 class="m-b-5">Armando Hernandez</h4>
                                            <p class="text-muted">1530343@upv.edu.mx</p>
                                        </div>

                                        <p class="text-muted m-t-10">
                                            Mi nombre es Armando y soy el encargado de administrar este sitio.
                                        </p>
                                    </div>

                                </div> <!-- end card-box -->

                            </div> <!-- end col -->
                        </div> <!-- end row -->

                        <div class="m-t-30">
                            <ul class="nav nav-tabs tabs-bordered">
                                <li class="">
                                    <a href="#home-b1" data-toggle="tab" aria-expanded="true">
                                        Perfil
                                    </a>
                                </li>
                                <li class="active">
                                    <a href="#profile-b1" data-toggle="tab" aria-expanded="false">
                                        Configuracion
                                    </a>
                                </li>
                            </ul>
                            <div class="tab-content">
                                <div class="tab-pane" id="home-b1">
                                    <div class="row">
                                        <div class="col-md-12">
                                            <!-- Personal-Information -->
                                            <div class="panel panel-default panel-fill">
                                                <div class="panel-heading">
                                                    <h3 class="panel-title">Información Personal</h3>
                                                </div>
                                                <div class="panel-body">
                                                    <div class="m-b-20">
                                                        <strong>Nombre Completo</strong>
                                                        <br>
                                                        <p class="text-muted">Armando Isaac Hernandez Muñiz</p>
                                                    </div>
                                                    <div class="m-b-20">
                                                        <strong>Móvil</strong>
                                                        <br>
                                                        <p class="text-muted">(834) 175 69 72</p>
                                                    </div>
                                                    <div class="m-b-20">
                                                        <strong>Email</strong>
                                                        <br>
                                                        <p class="text-muted">1530343@upv.edu.mx</p>
                                                    </div>
                                                    <div class="about-info-p m-b-0">
                                                        <strong>Pais</strong>
                                                        <br>
                                                        <p class="text-muted">México</p>
                                                    </div>
                                                </div>
                                            </div>
                                            <!-- Personal-Information -->

                                            <!-- Social -->
                                            <div class="panel panel-default panel-fill">
                                                <div class="panel-heading">
                                                    <h3 class="panel-title">Social</h3>
                                                </div>
                                                <div class="panel-body">
                                                    <ul class="social-links list-inline m-b-0">
                                                        <li>
                                                            <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="http://www.facebook.com" data-original-title="Facebook"><i class="fa fa-facebook"></i></a>
                                                        </li>
                                                        <li>
                                                            <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="http://www.twitter.com" data-original-title="Twitter"><i class="fa fa-twitter"></i></a>
                                                        </li>
                                                        <li>
                                                            <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="http://www.skype.com" data-original-title="Skype"><i class="fa fa-skype"></i></a>
                                                        </li>
                                                    </ul>
                                                </div>
                                            </div>
                                            <!-- Social -->
                                        </div>

                                    </div>
                                </div>

                                <?php

                                  include("conexion.php");

                                  $guarda = false;
                                  $error = false;
                                  $cuenta = $conexion->query("SELECT * from administrador")->fetch_assoc();

                                  if(isset($_POST['guardar'])){
                                    if($_POST['pass']==$_POST['pass2']){
                                      $guardar = $conexion->query("UPDATE administrador set usuario = '".$_POST['usuario']."', clave = '".$_POST['pass']."'");
                                      if($guardar){$guarda = true;}
                                    }
                                    else{
                                      $error = true;
                                    }
                                    
                                  }


                                ?>
                                <div class="tab-pane active" id="profile-b1">
                                    <!-- Personal-Information -->
                                    <div class="panel panel-default panel-fill">
                                        <div class="panel-heading">
                                            <h3 class="panel-title">Editar Perfil</h3>
                                        </div>
                                        <?php if($guarda==true){?>
                                        <div class="alert alert-success alert-dismissible fade in" role="alert">
                                            <button type="button" class="close" data-dismiss="alert"
                                                    aria-label="Close">
                                                <span aria-hidden="true">&times;</span>
                                            </button>
                                            <strong>Guardado Exitoso!</strong> Se han cambiado los datos de tu cuenta.
                                        </div>
                                        <?php } if($error==true){?>
                                        <div class="alert alert-warning alert-dismissible fade in" role="alert">
                                            <button type="button" class="close" data-dismiss="alert"
                                                    aria-label="Close">
                                                <span aria-hidden="true">&times;</span>
                                            </button>
                                            <strong>Inválido!</strong> Las contraseñas no coinciden.
                                        </div><?php } ?>
                                        <div class="panel-body">
                                            <form role="form" method="post">                                                
                                                <div class="form-group">
                                                    <label for="Username">Nombre de Usuario</label>
                                                    <input type="text" id="Username" name="usuario" class="form-control" required value="<?php echo $cuenta['usuario']; ?>">
                                                </div>
                                                <div class="form-group">
                                                    <label for="Password">Contraseña</label>
                                                    <input type="password" placeholder="Contraseña" id="Password" class="form-control" name="pass" required value="<?php echo $cuenta['clave']; ?>">
                                                </div>
                                                <div class="form-group">
                                                    <label for="RePassword">Confirmar Contraseña</label>
                                                    <input type="password" placeholder="Confirmar Contraseña" id="RePassword" class="form-control" name="pass2" required value="<?php echo $cuenta['clave']; ?>">
                                                </div>
                                                <button class="btn btn-primary waves-effect waves-light w-md" name="guardar" type="submit">Guardar</button>
                                            </form>

                                        </div>
                                    </div>
                                    <!-- Personal-Information -->
                                </div>
                            </div>
                        </div>
                    </div>
                    <!-- end container -->

                    <div class="footer">
                        <div class="pull-right hidden-xs">
                            Project Completed <strong class="text-custom">39%</strong>.
                        </div>
                        <div>
                            <strong>Simple Admin</strong> - Copyright &copy; 2017
                        </div>
                    </div> <!-- end footer -->

                </div>

            </div>
            <!-- end .page-contentbar -->
        </div>




        <!-- js placed at the end of the document so the pages load faster -->
        <script src="assets/js/jquery-2.1.4.min.js"></script>
        <script src="assets/js/bootstrap.min.js"></script>
        <script src="assets/js/metisMenu.min.js"></script>
        <script src="assets/js/jquery.slimscroll.min.js"></script>

        <!--Morris Chart-->
    <script src="assets/plugins/morris/morris.min.js"></script>
    <script src="assets/plugins/raphael/raphael-min.js"></script>
    <script src="assets/pages/jquery.morris.init.js"></script>

    
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