<?php
    session_start();
    //echo "".$_SESSION['usuario'];
    if($_SESSION['usuario']!="empleado"){
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

    //include("graficaVentas.php");
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
                                <li><a href="">Perfil</a></li>
                                <li><a href="">Contactos</a></li>
                                <li><a href="">Calendario</a></li>
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
                                        <li><a href=""><i class="ti-user m-r-10"></i> Perfil</a></li>
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
                                    <img src="imagenes/logo1.jpg" alt="" class="thumb-md img-circle">
                                </div>
                                <div class="user-info">
                                    <a href="#"><?php echo $_SESSION['nombre']; ?></a>
                                    <p class="text-muted m-0">Empleado</p>
                                </div>
                            </div>
                            <!--- End User Detail box -->

                            <!-- Left Menu Start -->
                            <ul class="metisMenu nav" id="side-menu">
                                <li><a href="cuenta_empleado.php"><i class="ti-home"></i> Tablero </a></li>

                                <li><a href="vender_cliente.php"><i class="mdi mdi-shopping-music"></i> Vender </a>
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
                            
                            
                          </div>
                        </div>
                        <div class="row">
            							<div class="col-sm-12">
            								<div class="card-box widget-inline">
            									<div class="row">
            										<div class="col-lg-6 col-sm-6">
            											<div class="widget-inline-box text-center">
            												<h3 class="m-t-10"><i class="text-primary mdi mdi-shopping-music"></i> <b data-plugin="counterup"><?php echo $numVentas; ?></b></h3>
            												<p class="text-muted">Total de Ventas</p>
            											</div>
            										</div>

            										<div class="col-lg-6 col-sm-6">
            											<div class="widget-inline-box text-center">
            												<h3 class="m-t-10"><i class="text-custom mdi mdi-database-plus"></i> <b data-plugin="counterup"><?php echo "$".$ingresosTotales; ?></b></h3>
            												<p class="text-muted">Total de Ingresos</p>
            											</div>
            										</div>
            									</div>
            								</div>
            							</div>
            						</div>

                        
                        <div class="row">
                            <div class="col-lg-12">
                                <div class="card-box">
                                    <h4 class="m-t-0">Total de Ingresos Mensuales</h4>
                                    
                                    <div id="ingresos-mes" style="height: 300px;"></div>
                                </div>
                            </div> <!-- end col -->
                        </div> <!-- end row -->



                        <div class="row">
                            <div class="col-sm-12">
                                <div class="card-box">
                                    <h4 class="m-t-0">Ventas de Hoy</h4>
                                    <div class="table-responsive">
                                        
                                        <table id="datatable" class="table table-striped table-bordered">
                                            <thead>
                                              <tr>
                                                  <th>Clave</th>
                                                  <th>Producto</th>
                                                  <th>Monto</th>
                                                  <th>Fecha</th>
                                                  <th>Cliente</th>
                                                  <th>Empleado</th>
                                              </tr>
                                            </thead>
                                            <tbody>
                                            <?php while($rep = $reporte->fetch_assoc()){ 

                                              $prod = $conexion->query("SELECT nombre from inventario where id_producto = ".$rep['id_producto'])->fetch_assoc();
                                              $client = $conexion->query("SELECT nombre from cliente where id = ".$rep['id_cliente'])->fetch_assoc();
                                              $emp = $conexion->query("SELECT nombre from empleado where Id = ".$rep['id_empleado'])->fetch_assoc();

                                            ?>
                                              <tr>
                                                  <td><?php echo $rep['id']; ?></td>
                                                  <td><?php echo $prod['nombre']; ?></td>
                                                  <td><?php echo $rep['total']; ?></td>
                                                  <td><?php echo $rep['fecha']; ?></td>
                                                  <td><?php echo $client['nombre']; ?></td>
                                                  <td><?php echo $emp['nombre']; ?></td>
                                              </tr>
                                            <?php } ?>                                         

                                            </tbody>
                                        </table>
                                    </div>
                                </div>
                            </div>
                        </div>


                    </div>
                    <!-- end container -->

                    

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

    <?php include('graficas _ingresos_mes.php'); ?>
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