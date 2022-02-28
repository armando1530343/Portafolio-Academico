<?php
    session_start();
    //echo "".$_SESSION['usuario'];
    if($_SESSION['usuario']!="empleado"){
        header('Location: index.php');
    }
    

    include("conexion.php");

    $guarda = false;
    $mostrar = false;
    $buscaid=null;
    $next = false;
    $vendio = false;

    if(isset($_POST['continuar'])){
      
      $cliente = $_POST['nombre'];
      $tel = $_POST['telefono'];
      $domicilio = $_POST['domicilio'];
      $nuevo = $conexion->query("INSERT INTO cliente(nombre, telefono, domicilio) values('$cliente','$tel','$domicilio')");
      if($nuevo){
        $next = true;
      }
    }

    if(isset($_POST['busca_id'])){
      if($_POST['idProd']!=""){
        $mostrar = true;
        $next=true;
        $buscaid = $conexion->query("SELECT * FROM inventario where id_producto = ".$_POST['idProd'])->fetch_assoc();
      }
      
    }
    if(isset($_POST['vender'])){
      $idCliente = $conexion->query("SELECT MAX(id) as id from cliente")->fetch_assoc();
      $idProducto = $_POST['idProd'];
      $precio = $_POST['venta'];
      $fecha = date('Y')."-".date('m')."-".date('d');

      $idEmpleado = $conexion->query("SELECT MIN(Id) as id from empleado where nombre = '".$_SESSION['nombre']."'")->fetch_assoc();

      $venta = $conexion->query("INSERT INTO venta(id_producto, total, fecha, id_cliente, id_empleado)
                                  values($idProducto, $precio, '$fecha', $idCliente[id], $idEmpleado[id])");
      if($venta){$vendio=true;}
    }

    $productos = $conexion->query("SELECT * from inventario");
    

    
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

        <!-- Plugins css-->
        <link href="assets/plugins/bootstrap-tagsinput/css/bootstrap-tagsinput.css" rel="stylesheet" />
        <link rel="stylesheet" href="assets/plugins/switchery/switchery.min.css">
        <link href="assets/plugins/select2/css/select2.min.css" rel="stylesheet" type="text/css" />
        <link href="assets/plugins/timepicker/bootstrap-timepicker.min.css" rel="stylesheet">
        <link href="assets/plugins/bootstrap-colorpicker/css/bootstrap-colorpicker.min.css" rel="stylesheet">
        <link href="assets/plugins/bootstrap-datepicker/css/bootstrap-datepicker.min.css" rel="stylesheet">
        <link href="assets/plugins/clockpicker/css/bootstrap-clockpicker.min.css" rel="stylesheet">
        <link href="assets/plugins/bootstrap-daterangepicker/daterangepicker.css" rel="stylesheet">
        <!-- Summernote css -->
        <link href="assets/plugins/summernote/summernote.css" rel="stylesheet" />


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
                            <?php if ($guarda == true){?>

                            <div class="alert alert-success alert-dismissible fade in" role="alert">
                                <button type="button" class="close" data-dismiss="alert"
                                        aria-label="Close">
                                    <span aria-hidden="true">&times;</span>
                                </button>
                                <strong>Guardado Exitoso!</strong> El producto se agrego a la base de datos correctamente.
                            </div>
                            <?php } ?>
                            
                          </div>

                        </div>
                      
                        <div class="row">
                          <div class="col-lg-12">
                              <div class="card-box">
                                <h2 style="color: red">Nueva Venta</h2><br>
                                <?php if ($vendio == true){?>
                                <div class="alert alert-success alert-dismissible fade in" role="alert">
                                    <button type="button" class="close" data-dismiss="alert"
                                            aria-label="Close">
                                        <span aria-hidden="true">&times;</span>
                                    </button>
                                    <strong>Venta realizada!</strong> La venta se realizo correctamente.
                                </div>
                                <?php } ?>
                                <?php if($next == false){?>
                                <form class="form-horizontal" method="post" action="">                                      
                                      <div class="form-group">
                                          <label for="userName2">Nombre de Cliente<span class="text-danger">*</span></label>
                                          <input type="text" name="nombre" parsley-trigger="change" required
                                                 placeholder="Nombre" class="form-control" id="userName2">
                                      </div>
                                      <div class="form-group">
                                          <label for="userName2">Telefono<span class="text-danger">*</span></label>
                                          <input type="number" name="telefono" parsley-trigger="change" required
                                                 placeholder="Telefono" class="form-control" id="userName2">
                                      </div>
                                      <div class="form-group">
                                          <label for="userName2">Domicilio<span class="text-danger">*</span></label>
                                          <input type="text" name="domicilio" parsley-trigger="change" required
                                                 placeholder="Domicilio" class="form-control" id="userName2">
                                      </div>                                      
                                      
                                      <div class="form-group text-right m-b-0">                                            
                                          <button type="" class="btn btn-primary waves-effect m-l-5" name="continuar">
                                              Continuar
                                          </button>
                                      </div>
                                </form>
                                <?php } else{?>
                                <form class="form-horizontal" method="POST" action="">
                                  <div class="form-group">
                                      <label for="userName">Selecciona Id del Producto:<span class="text-danger">*</span></label>
                                      <select class="form-control select2" name="idProd">
                                          <option></option>
                                          <?php while($con2 = $productos->fetch_assoc()){ ?>
                                              <option><?php echo $con2['id_producto']; ?> </option>
                                          <?php } ?>                                                      
                                      </select><br>
                                  </div> 
                                  <div class="form-group">
                                      <button class="btn btn-primary waves-light" type="" name="busca_id">
                                          Mostrar datos
                                      </button><br><br>                                    
                                  </div>
                                </form>                                
                                <form class="form-horizontal" method="POST" action="">
                                    <div class="form-group">
                                        <label for="userName2">Id Producto<span class="text-danger">*</span></label>
                                        <input type="text" name="idProd" parsley-trigger="change" required
                                               placeholder="Nombre" class="form-control" id="userName2" 
                                               value="<?php echo $buscaid['id_producto'];?>">
                                    </div>
                                    <div class="form-group">
                                        <label for="userName2">Nombre<span class="text-danger">*</span></label>
                                        <input type="text" name="producto" parsley-trigger="change" required
                                               placeholder="Nombre de Producto" class="form-control" id="userName2"
                                               value="<?php echo $buscaid['nombre'];?>">
                                    </div>
                                    <div class="form-group">
                                        <label for="userName2">Precio Venta<span class="text-danger">*</span></label>
                                        <input type="number" name="venta" parsley-trigger="change" required
                                               placeholder="Precio Venta" class="form-control" id="userName2"
                                               value="<?php echo $buscaid['venta'];?>">
                                    </div>
                                    <div class="form-group">
                                          <label for="caja1">Fecha<span class="text-danger">*</span></label>
                                          <div class="input-group">
                                              <input type="text" class="form-control" placeholder="yyyy-mm-dd" id="datepicker-autoclose" name="fecha">
                                              <span class="input-group-addon bg-custom b-0"><i class="mdi mdi-calendar text-white"></i></span>
                                          </div><!-- input-group -->
                                      </div>
                                    <div class="form-group text-right m-b-0">                                            
                                        <button type="" class="btn btn-success waves-effect m-l-5" name="vender">
                                            Realizar venta
                                        </button>
                                    </div>
                                </form>
                                <?php } ?>
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
    
        <script src="assets/plugins/bootstrap-tagsinput/js/bootstrap-tagsinput.min.js"></script>
        <script src="assets/plugins/select2/js/select2.min.js" type="text/javascript"></script>
        <script src="assets/plugins/bootstrap-filestyle/js/bootstrap-filestyle.min.js" type="text/javascript"></script>
        <script src="assets/plugins/switchery/switchery.min.js"></script>
        <script type="text/javascript" src="assets/plugins/parsleyjs/parsley.min.js"></script>

        <script src="assets/plugins/moment/moment.js"></script>
        <script src="assets/plugins/timepicker/bootstrap-timepicker.js"></script>
        <script src="assets/plugins/bootstrap-colorpicker/js/bootstrap-colorpicker.min.js"></script>
        <script src="assets/plugins/bootstrap-datepicker/js/bootstrap-datepicker.min.js"></script>
        <script src="assets/plugins/clockpicker/js/bootstrap-clockpicker.min.js"></script>
        <script src="assets/plugins/bootstrap-daterangepicker/daterangepicker.js"></script>
        <script src="assets/plugins/summernote/summernote.min.js"></script>

        <!-- form advanced init js -->
        <script src="assets/pages/jquery.form-advanced.init.js"></script>

        <!-- KNOB JS -->
        <!--[if IE]>
        <script type="text/javascript" src="assets/plugins/jquery-knob/excanvas.js"></script>
        <![endif]-->
        <!-- App Js -->
        <script src="assets/js/jquery.app.js"></script>

        <script type="text/javascript">
            $('[data-plugin="knob"]').each(function(idx, obj) {
                $(this).knob();
             });
        </script>


    </body>
</html>