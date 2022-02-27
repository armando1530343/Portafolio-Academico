<?php  
    session_start();
    if($_SESSION['usuario'] == "administrador"){
        header('Location: admin.php');
    }
    elseif ($_SESSION['usuario'] == "empleado") {
        header('Location: cuenta_empleado.php');
    }
    $_SESSION['usuario']="";
    $_SESSION['nombre']="";


?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8" />
    <title>SimpleAdmin - Responsive Admin Dashboard Template</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no" />
    <meta content="A fully featured admin theme which can be used to build CRM, CMS, etc." name="description" />
    <meta content="Coderthemes" name="author" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />

    <link rel="shortcut icon" href="assets/images/favicon.ico">

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
        <?php 
            include("conexion.php");

            if(isset($_POST['submit'])){
                if($_POST['user']=="" || $_POST['pass']==""){
                    //echo "<script>alert('No debe dejar campos vacios');</script>";
                    $hoy = date('d');
                    //echo "dia: ".$hoy;
                }
                else {
                    

                    $usuario = $_POST['user'];
                    $password = $_POST['pass'];

                    //require("validarLogin.php");
                    $consulta1 = $conexion->query("SELECT * FROM administrador WHERE usuario = '$usuario' and clave = '$password'")->fetch_assoc();
                    $consulta2 = $conexion->query("SELECT * FROM empleado WHERE usuario = '$usuario' and clave = '$password'")->fetch_assoc();
                            
                    if($consulta1){
                        $_SESSION["usuario"] = "administrador";
                        echo "<script> alert('".$_SESSION['usuario']."');</script>";
                        $_SESSION['nombre']=$consulta1['usuario'];
                        header('Location: admin.php');
                    }
                    elseif ($consulta2){
                        $_SESSION["usuario"] = "empleado";
                        echo "<script> alert('".$_SESSION['usuario']."');</script>";
                        $_SESSION['nombre']=$consulta2['nombre'];
                        header('Location: cuenta_empleado.php');
                    }
                    else{
                        echo "<script> alert('No existe usuario');</script>";

                    }
                }  
            }
            else{
                //header('Location: admin.php');
            }

        ?>  

        <!-- HOME -->
        <section>
            <div class="container" style="background-color: white">
                <div class="row">
                    <div class="col-sm-12">

                        <div class="wrapper-page">

                            <div class="m-t-40 card-box">
                                <div class="text-center">
                                    <h2 class="text-uppercase m-t-0 m-b-30">
                                        <a href="index.html" class="text-success">
                                            <span><img src="imagenes/logo2.jpg" alt="" width="200" height="120"></span>
                                        </a>
                                    </h2>
                                    <!--<h4 class="text-uppercase font-bold m-b-0">Sign In</h4>-->
                                </div>
                                <div class="account-content">
                                    <form class="form-horizontal" method="post" action="" >

                                        <div class="form-group m-b-20">
                                            <div class="col-xs-12">
                                                <label for="text">Nombre de Usuario</label>
                                                <input class="form-control" name="user" type="text" required placeholder="Username">
                                            </div>
                                        </div>

                                        <div class="form-group m-b-20">
                                            <div class="col-xs-12">
                                                <a href="pages-forget-password.html" class="text-muted pull-right font-14">Olvidaste tu contraseña?</a>
                                                <label for="password">Contraseña</label>
                                                <input class="form-control" name="pass" type="password" required placeholder="Password">
                                            </div>
                                        </div>

                                        <div class="form-group m-b-30">
                                            <div class="col-xs-12">
                                                <div class="checkbox checkbox-primary">
                                                    <input id="checkbox5" type="checkbox">
                                                    <label for="checkbox5">
                                                        Guardar Contraseña
                                                    </label>
                                                </div>
                                            </div>
                                        </div>

                                        <div class="form-group text-center m-t-10">
                                            <div class="col-xs-12">
                                                <input type="submit" class="btn btn-lg btn-primary btn-block" value="Ingresar" name="submit"/>
                                            	<!--<a href="" class="btn btn-lg btn-primary btn-block" type="submit" name="submit">Ingresar</a>
                                                <!--<button href="admin.html" class="btn btn-lg btn-primary btn-block" type="submit">Ingresar</button>-->
                                            </div>
                                            
                                        </div>
                                        

                                    </form>

                                    <div class="clearfix"></div>

                                </div>
                            </div>
                            <!-- end card-box-->


                            <div class="row m-t-50">
                                <div class="col-sm-12 text-center">
                                    <p class="text-muted">No tienes una Cuenta en CyberGames? <a href="pages-register.html" class="text-dark m-l-5">Registrarse</a></p>
                                </div>
                            </div>

                        </div>
                        <!-- end wrapper -->

                    </div>
                </div>
            </div>

        
        
        </section>
        <!-- END HOME -->

		<!-- js placed at the end of he document so the pages load faster -->
	    <script src="assets/js/jquery-2.1.4.min.js"></script>
	    <script src="assets/js/bootstrap.min.js"></script>
	    <script src="assets/js/metisMenu.min.js"></script>
	    <script src="assets/js/jquery.slimscroll.min.js"></script>

	    <!-- App Js -->
	    <script src="assets/js/jquery.app.js"></script>

	</body>
</html>