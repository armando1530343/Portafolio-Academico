<?php
    session_start();
    //echo "".$_SESSION['usuario'];
    if($_SESSION['usuario']!="administrador"){
        header('Location: index.php');
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

                <!-- START PAGE CONTENT -->
                <div id="page-right-content">

                    <div class="container">
                        <div class="row">
                            <div class="col-sm-12">
                                <h4 class="header-title m-t-0 m-b-20">Contactos</h4>
                            </div>
                        </div> <!-- end row -->


                        <div class="row">
                            <div class="col-md-4">
                                <div class="text-center card-box">
                                    <div class="dropdown pull-right">
                                        <a href="#" class="dropdown-toggle card-drop" data-toggle="dropdown" aria-expanded="false">
                                            <h3 class="m-0 text-muted"><i class="mdi mdi-dots-horizontal"></i></h3>
                                        </a>
                                        <ul class="dropdown-menu" role="menu">
                                            <li><a href="#">Editar</a></li>
                                            <li><a href="#">Eliminar</a></li>
                                            <li><a href="#">Block</a></li>
                                        </ul>
                                    </div>
                                    <div class="clearfix"></div>
                                    <div class="member-card">
                                        <span class="user-badge bg-warning">Founder</span>
                                        <div class="thumb-xl member-thumb m-b-10 center-block">
                                            <img src="assets/images/users/avatar-1.jpg" class="img-circle img-thumbnail" alt="profile-image">
                                            <i class="mdi mdi-information-outline member-star text-success" title="verified user"></i>
                                        </div>

                                        <div class="">
                                            <h4 class="m-b-5">Isamar Moreno</h4>
                                            <p class="text-muted">@CEO <span> | </span> <span> <a href="#" class="text-pink">websitename.com</a> </span></p>
                                        </div>

                                        <p class="text-muted font-13">
                                            Hi I'm Johnathn Deo,has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type.
                                        </p>

                                        <button type="button" class="btn btn-default btn-sm m-t-10">Mensaje</button>
                                        <button type="button" class="btn btn-default btn-sm m-t-10">Ver Perfil</button>

                                        <ul class="social-links list-inline m-t-30">
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Facebook"><i class="fa fa-facebook"></i></a>
                                            </li>
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Twitter"><i class="fa fa-twitter"></i></a>
                                            </li>
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Skype"><i class="fa fa-skype"></i></a>
                                            </li>
                                        </ul>

                                    </div>

                                </div>

                            </div> <!-- end col -->

                            <div class="col-md-4">
                                <div class="text-center card-box">
                                    <div class="dropdown pull-right">
                                        <a href="#" class="dropdown-toggle card-drop" data-toggle="dropdown" aria-expanded="false">
                                            <h3 class="m-0 text-muted"><i class="mdi mdi-dots-horizontal"></i></h3>
                                        </a>
                                        <ul class="dropdown-menu" role="menu">
                                            <li><a href="#">Edit</a></li>
                                            <li><a href="#">Delete</a></li>
                                            <li><a href="#">Block</a></li>
                                        </ul>
                                    </div>
                                    <div class="clearfix"></div>
                                    <div class="member-card">
                                        <div class="thumb-xl member-thumb m-b-10 center-block">
                                            <img src="assets/images/users/avatar-2.jpg" class="img-circle img-thumbnail" alt="profile-image">
                                            <i class="mdi mdi-information-outline member-star text-muted" title="unverified user"></i>
                                        </div>

                                        <div class="">
                                            <h4 class="m-b-5">Rodrigo Rojas</h4>
                                            <p class="text-muted">@Founder <span> | </span> <span> <a href="#" class="text-pink">websitename.com</a> </span></p>
                                        </div>

                                        <p class="text-muted font-13">
                                            Hi I'm Johnathn Deo,has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type.
                                        </p>

                                        <button type="button" class="btn btn-default btn-sm m-t-10">Message</button>
                                        <button type="button" class="btn btn-default btn-sm m-t-10">View Profile</button>

                                        <ul class="social-links list-inline m-t-30">
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Facebook"><i class="fa fa-facebook"></i></a>
                                            </li>
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Twitter"><i class="fa fa-twitter"></i></a>
                                            </li>
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Skype"><i class="fa fa-skype"></i></a>
                                            </li>
                                        </ul>

                                    </div>

                                </div>

                            </div> <!-- end col -->

                            <div class="col-md-4">
                                <div class="text-center card-box">
                                    <div class="dropdown pull-right">
                                        <a href="#" class="dropdown-toggle card-drop" data-toggle="dropdown" aria-expanded="false">
                                            <h3 class="m-0 text-muted"><i class="mdi mdi-dots-horizontal"></i></h3>
                                        </a>
                                        <ul class="dropdown-menu" role="menu">
                                            <li><a href="#">Edit</a></li>
                                            <li><a href="#">Delete</a></li>
                                            <li><a href="#">Block</a></li>
                                        </ul>
                                    </div>
                                    <div class="clearfix"></div>
                                    <div class="member-card">
                                        <div class="thumb-xl member-thumb m-b-10 center-block">
                                            <img src="assets/images/users/avatar-3.jpg" class="img-circle img-thumbnail" alt="profile-image">
                                            <i class="mdi mdi-information-outline member-star text-success" title="verified user"></i>
                                        </div>

                                        <div class="">
                                            <h4 class="m-b-5">Josue Coronado</h4>
                                            <p class="text-muted">@Webdesigner <span> | </span> <span> <a href="#" class="text-pink">websitename.com</a> </span></p>
                                        </div>

                                        <p class="text-muted font-13">
                                            Hi I'm Johnathn Deo,has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type.
                                        </p>

                                        <button type="button" class="btn btn-default btn-sm m-t-10">Message</button>
                                        <button type="button" class="btn btn-default btn-sm m-t-10">View Profile</button>

                                        <ul class="social-links list-inline m-t-30">
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Facebook"><i class="fa fa-facebook"></i></a>
                                            </li>
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Twitter"><i class="fa fa-twitter"></i></a>
                                            </li>
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Skype"><i class="fa fa-skype"></i></a>
                                            </li>
                                        </ul>

                                    </div>

                                </div>

                            </div> <!-- end col -->
                        </div>
                        <!-- end row -->



                        <div class="row">
                            <div class="col-md-4">
                                <div class="text-center card-box">
                                    <div class="dropdown pull-right">
                                        <a href="#" class="dropdown-toggle card-drop" data-toggle="dropdown" aria-expanded="false">
                                            <h3 class="m-0 text-muted"><i class="mdi mdi-dots-horizontal"></i></h3>
                                        </a>
                                        <ul class="dropdown-menu" role="menu">
                                            <li><a href="#">Edit</a></li>
                                            <li><a href="#">Delete</a></li>
                                            <li><a href="#">Block</a></li>
                                        </ul>
                                    </div>
                                    <div class="clearfix"></div>
                                    <div class="member-card">
                                        <div class="thumb-xl member-thumb m-b-10 center-block">
                                            <img src="assets/images/users/avatar-4.jpg" class="img-circle img-thumbnail" alt="profile-image">
                                            <i class="mdi mdi-information-outline member-star text-muted" title="unverified user"></i>
                                        </div>

                                        <div class="">
                                            <h4 class="m-b-5">Sandra D. Duby</h4>
                                            <p class="text-muted">@Manager <span> | </span> <span> <a href="#" class="text-pink">websitename.com</a> </span></p>
                                        </div>

                                        <p class="text-muted font-13">
                                            Hi I'm Johnathn Deo,has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type.
                                        </p>

                                        <button type="button" class="btn btn-default btn-sm m-t-10">Message</button>
                                        <button type="button" class="btn btn-default btn-sm m-t-10">View Profile</button>

                                        <ul class="social-links list-inline m-t-30">
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Facebook"><i class="fa fa-facebook"></i></a>
                                            </li>
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Twitter"><i class="fa fa-twitter"></i></a>
                                            </li>
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Skype"><i class="fa fa-skype"></i></a>
                                            </li>
                                        </ul>

                                    </div>

                                </div>

                            </div> <!-- end col -->

                            <div class="col-md-4">
                                <div class="text-center card-box">
                                    <div class="dropdown pull-right">
                                        <a href="#" class="dropdown-toggle card-drop" data-toggle="dropdown" aria-expanded="false">
                                            <h3 class="m-0 text-muted"><i class="mdi mdi-dots-horizontal"></i></h3>
                                        </a>
                                        <ul class="dropdown-menu" role="menu">
                                            <li><a href="#">Edit</a></li>
                                            <li><a href="#">Delete</a></li>
                                            <li><a href="#">Block</a></li>
                                        </ul>
                                    </div>
                                    <div class="clearfix"></div>
                                    <div class="member-card">
                                        <span class="user-badge bg-custom">Co-Founder</span>
                                        <div class="thumb-xl member-thumb m-b-10 center-block">
                                            <img src="assets/images/users/avatar-5.jpg" class="img-circle img-thumbnail" alt="profile-image">
                                            <i class="mdi mdi-information-outline member-star text-success" title="verified user"></i>
                                        </div>

                                        <div class="">
                                            <h4 class="m-b-5">Edmund D. Barton</h4>
                                            <p class="text-muted">@Webdeveloper <span> | </span> <span> <a href="#" class="text-pink">websitename.com</a> </span></p>
                                        </div>

                                        <p class="text-muted font-13">
                                            Hi I'm Johnathn Deo,has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type.
                                        </p>

                                        <button type="button" class="btn btn-default btn-sm m-t-10">Message</button>
                                        <button type="button" class="btn btn-default btn-sm m-t-10">View Profile</button>

                                        <ul class="social-links list-inline m-t-30">
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Facebook"><i class="fa fa-facebook"></i></a>
                                            </li>
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Twitter"><i class="fa fa-twitter"></i></a>
                                            </li>
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Skype"><i class="fa fa-skype"></i></a>
                                            </li>
                                        </ul>

                                    </div>

                                </div>

                            </div> <!-- end col -->

                            <div class="col-md-4">
                                <div class="text-center card-box">
                                    <div class="dropdown pull-right">
                                        <a href="#" class="dropdown-toggle card-drop" data-toggle="dropdown" aria-expanded="false">
                                            <h3 class="m-0 text-muted"><i class="mdi mdi-dots-horizontal"></i></h3>
                                        </a>
                                        <ul class="dropdown-menu" role="menu">
                                            <li><a href="#">Edit</a></li>
                                            <li><a href="#">Delete</a></li>
                                            <li><a href="#">Block</a></li>
                                        </ul>
                                    </div>
                                    <div class="clearfix"></div>
                                    <div class="member-card">
                                        <div class="thumb-xl member-thumb m-b-10 center-block">
                                            <img src="assets/images/users/avatar-6.jpg" class="img-circle img-thumbnail" alt="profile-image">
                                            <i class="mdi mdi-information-outline member-star text-success" title="verified user"></i>
                                        </div>

                                        <div class="">
                                            <h4 class="m-b-5">Janene C. Cox</h4>
                                            <p class="text-muted">@Product Manager <span> | </span> <span> <a href="#" class="text-pink">websitename.com</a> </span></p>
                                        </div>

                                        <p class="text-muted font-13">
                                            Hi I'm Johnathn Deo,has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type.
                                        </p>

                                        <button type="button" class="btn btn-default btn-sm m-t-10">Message</button>
                                        <button type="button" class="btn btn-default btn-sm m-t-10">View Profile</button>

                                        <ul class="social-links list-inline m-t-30">
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Facebook"><i class="fa fa-facebook"></i></a>
                                            </li>
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Twitter"><i class="fa fa-twitter"></i></a>
                                            </li>
                                            <li>
                                                <a title="" data-placement="top" data-toggle="tooltip" class="tooltips" href="" data-original-title="Skype"><i class="fa fa-skype"></i></a>
                                            </li>
                                        </ul>

                                    </div>

                                </div>

                            </div> <!-- end col -->
                        </div>
                        <!-- end row -->

                        <div class="row">
                            <div class="col-sm-12 text-center">
                                <button class="btn btn-primary btn-rounded btn-lg m-b-30" data-toggle="modal" data-target="#add-contact">Add Contact</button>
                            </div><!-- end col -->
                        </div>
                        <!-- end row -->

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
                <!-- End #page-right-content -->


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
    <?php include('graficas_ventas_mes.php'); ?>
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