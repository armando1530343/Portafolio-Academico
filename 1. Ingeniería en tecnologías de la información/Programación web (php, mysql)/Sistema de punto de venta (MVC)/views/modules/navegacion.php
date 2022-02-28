<!--nav>
	<ul>
		<!-- Pra navegar al URL podemos hacerlo mediante la variable GET, la cual la toma del URL, se representa por el simbolo "?">
		<li><a href="index.php?action=ingresar">Ingreso</a></li>
		<li><a href="index.php?action=inventario">Inventarios</a></li>
		<li><a href="index.php?action=categorias">Categorias</a></li>
		<li><a href="index.php?action=usuarios">Usuarios</a></li>
		<li><a href="index.php?action=salir">Salir</a></li>
	</ul>
</nav-->
<?php

#se inicia secion una vez entrando al navegador
  session_start();
  if(isset($_GET['user'])){

      #se crean las variables de sesion del usuario
    
      $_SESSION['user'] = $_GET['user'];
      $_SESSION['validar'] = true;
      $_SESSION['id_user'] = $_GET['id_user'];
      //$_SESSION['id_tienda'] = $_GET['tienda'];

  }
  if(isset($_GET['password'])){
      $_SESSION['password'] = $_GET['password'];
  }

  if(isset($_GET['tienda'])){
      $_SESSION['id_tienda'] = $_GET['tienda'];
      $mvc = new MvcController();

      $tienda = $mvc->getTiendaController();
      $_SESSION['tienda'] = $tienda[0]['nombre'];
      $_SESSION['tienda_status'] = $tienda[0]['estado'];

      if($_SESSION['tienda_status'] == 'DESACTIVA' && $_SESSION['user'] != 'admin' ){
        echo '<script> window.location = "index.php?action=sin_servicio"; </script>';
      }
  }

	//session_start();

	$_SESSION['fecha'] = date('Y-m-d');

  $hora = localtime(time()-(3600*7), true);

  $_SESSION['fecha'] = ($hora['tm_year']+ 1900).'-'.($hora['tm_mon']+1).'-'.$hora['tm_mday'];
  $_SESSION['hora'] = $hora['tm_hour'].':'.$hora['tm_min'].':'.$hora['tm_sec'];

  if(isset($_GET['action'])){
  	if($_GET['action']!='agregar_venta'){
  		$mvc = new MvcController();
  		$mvc->quitarProductosController();
  	}

  }


?>


<!-- Navbar -->
<nav class="main-header navbar navbar-expand bg-white navbar-light border-bottom">
<!-- Left navbar links -->
	<ul class="navbar-nav">
      
      <li class="nav-item d-none d-sm-inline-block">
        <a href="index.php?action=perfil" class="nav-link">Perfil</a>
      </li>
    </ul>

	<!-- Right navbar links -->
	<ul class="navbar-nav ml-auto">
	  <!-- Messages Dropdown Menu -->
	  <li class="nav-item d-none d-sm-inline-block">
	    <a href="" class="nav-link">Fecha de Hoy: <?php echo $_SESSION['fecha']; ?> </a>
	  </li>
	  <li class="nav-item d-none d-sm-inline-block">
	    <a href="index.php?action=salir" class="nav-link">Cerrar Sesion</a>
	  </li>
	</ul>
</nav>
<!-- /.navbar -->

<!-- Main Sidebar Container -->
<aside class="main-sidebar sidebar-dark-primary elevation-4">
<!-- Brand Logo -->
	<a href="index.php?action=<?php if($_SESSION['tienda_status']!='ACTIVA' && $_SESSION['user']!='admin'){echo 'sin_servicio';}else if($_SESSION['user']!='admin'){echo 'dashboard';} else{echo 'dashboard_tiendas ';} ?>" class="brand-link" style="text-align: center;">
	  <span class="brand-text font-weight-light">SISTEMA INVENTARIO</span>
	</a>

  <?php

  if($_GET['action'] != 'dashboard_tiendas'){
   
   ?>
  
  <a href="" class="brand-link" style="text-align: center;">
    <span class="brand-text font-weight-light"><?php echo $_SESSION['tienda']; ?></span>
  </a>

  <?php } ?>

	<!-- Sidebar -->
	<div class="sidebar">
	  <!-- Sidebar user panel (optional) -->
	  <div class="user-panel mt-3 pb-3 mb-3 d-flex">
	    <div class="image">
        <img src="user.png" alt="User Avatar" class="img-size-50 mr-3 img-circle">	      
	    </div>
	    <div class="info" style="text-align: center;">
	      <a href="" class="d-block"><?php echo $_SESSION['user']; ?></a>
	    </div>
	  </div>

	  <nav class="mt-2">
        <ul class="nav nav-pills nav-sidebar flex-column" data-widget="treeview" role="menu" data-accordion="false">
          <!-- Add icons to the links using the .nav-icon class
               with font-awesome or any other icon font library -->
          <?php 
          if($_GET['action'] != 'dashboard_tiendas' && $_GET['action'] != 'agregar_tienda' && $_GET['action'] != 'perfil' && ($_SESSION['tienda_status'] == 'ACTIVA' || $_SESSION['user'] == 'admin')){
           ?>
          
          <li class="nav-item has-treeview">
            <a href="index.php?action=productos" class="nav-link">
              <i class="nav-icon fa fa-pie-chart"></i>
              <p>
                Productos
              </p>
            </a>
            
          </li>

          <li class="nav-item has-treeview">
            <a href="index.php?action=categorias" class="nav-link">
              <i class="nav-icon fa fa-pie-chart"></i>
              <p>
                Categorias
              </p>
            </a>            
          </li>

          <li class="nav-item has-treeview">
            <a href="index.php?action=usuarios" class="nav-link">
              <i class="nav-icon fa fa-pie-chart"></i>
              <p>
                Usuarios
              </p>
            </a>            
          </li>

          <li class="nav-item has-treeview">
            <a href="index.php?action=ventas" class="nav-link">
              <i class="nav-icon fa fa-pie-chart"></i>
              <p>
                Ventas
              </p>
            </a>            
          </li>
        <?php } 

        if($_GET['action'] != 'dashboard_tiendas' && $_GET['action'] != 'agregar_tienda' && $_GET['action'] != 'perfil'  && $_SESSION['user'] == 'admin'){
        ?>
        <li class="nav-item has-treeview">
          <a href="index.php?action=dashboard_tiendas" class="nav-link">
            <i class="nav-icon fa fa-pie-chart"></i>
            <p>
              Tiendas
            </p>
          </a>            
        </li>
      <?php } ?>
		 


        </ul>
      </nav>
	  <!-- /.sidebar-menu -->
	</div>
	<!-- /.sidebar -->
</aside>
<div class="content-wrapper" align="center">
    <!-- Content Header (Page header) -->
    <div class="content-header">
      <div class="container-fluid">
        <div class="row mb-2">
          
        </div><!-- /.row -->
      </div><!-- /.container-fluid -->
    </div>