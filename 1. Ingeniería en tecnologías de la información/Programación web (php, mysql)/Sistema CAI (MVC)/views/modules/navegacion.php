<?php

  session_start();

  $_SESSION['validar'] = true; 

  if(isset($_GET['pass'])){
      $_SESSION['password'] = $_GET['pass'];
  }
  
  
  $_SESSION['fecha'] = date('Y-m-d');

  //$time = 1532149200; // jueves 20/julio/2018 

  $time = 1532926800; // martes 30/julio/2018 - 7:00 hrs

  $tiempo = time()-25200; //tiempo del servidor menos 7 hrs para la hora actual
  
  //echo '<script>alert("'.$tiempo.' - '.$time. '");</script>';

  $_SESSION['visitas'] = true;  

  while (true) {

  	if($tiempo >= $time && $tiempo < $time+86400)
  		break;

  	$time += 86400;
  	
  }

  /*while (true) {
    //$tiempo = time()+61200;//
    //$tiempo = time()+68400;//
    $tiempo = time()-25200;//
    echo '<script>alert("'.$tiempo.' - '.$time. '");</script>';

    if($tiempo >= $time && $tiempo < $time+86400)
      break;

    $time += 86400;
  }*/
  
  $aux_time = $time;
  $_SESSION['horario']='Ninguna';
  
  $hora_inicio[0] = $aux_time;/*7:00*/$aux_time += 3300;
  $hora_inicio[1] = $aux_time;/*7:55*/$aux_time += 3300;
  $hora_inicio[2] = $aux_time;/*8:50*/$aux_time += 3300;
  $hora_inicio[3] = $aux_time;/*9:45*/$aux_time += 5100;
  $hora_inicio[4] = $aux_time;/*11:10*/$aux_time += 3300;
  $hora_inicio[5] = $aux_time;/*12:05*/$aux_time += 3300;
  $hora_inicio[6] = $aux_time;/*1:00*/$aux_time += 3600;

  $hora_inicio[7] = $aux_time;/*2:00*/$aux_time += 3300;
  $hora_inicio[8] = $aux_time;/*2:55*/$aux_time += 3300;
  $hora_inicio[9] = $aux_time;/*3:50*/$aux_time += 3300;
  $hora_inicio[10] = $aux_time;/*4:45*/$aux_time += 4500;
  $hora_inicio[11] = $aux_time;/*6:00*/$aux_time += 3300;

  $horarios = array('7:00 - 7:54', '7:55 - 8:49','8:50 - 9:44', '9:45 - 10:40','11:10 - 12:04',
                        '12:05 - 12:59','13:00 - 13:54','14:00 - 14:54','14:55 - 15:49','15:50 - 16:44',
                        '16:45 - 17:39','18:00 - 18:54');
  
  //$tiempo = $time + (60*165);
  //echo "<script>alert(".$tiempo.");</script>";
  //$tiempo = 1533013200 + (60 * 0);
  

  $_SESSION['tiempo'] = $tiempo;
  $_SESSION['hora_limite'] = 0;
  $_SESSION['hora_inicio'] = 0;

  if($tiempo < $hora_inicio[0] || $tiempo > $hora_inicio[3]+3300 && $tiempo < $hora_inicio[4] ||
     $tiempo > $hora_inicio[6]+3300 && $tiempo < $hora_inicio[7] ||
     $tiempo > $hora_inicio[10]+3300 && $tiempo < $hora_inicio[11] || $tiempo > $hora_inicio[11]+3300 )
    $_SESSION['visitas'] = false;

  for($i = 0; $i < 12; $i++){
    if($tiempo >= $hora_inicio[$i] && $_SESSION['visitas'] == true){
      $_SESSION['horario'] = $horarios[$i];
      $_SESSION['hora_inicio'] = $hora_inicio[$i];
      $_SESSION['hora_limite'] = $_SESSION['hora_inicio'] + 600;
    }
  }
  //$tiempo = time();
  //$tiempo += 33198;
  //$hora = localtime(time()-(3600*7), true);

  //echo '<script>alert("'.$_SESSION['hora_limite'].'");</script>';
  
  $hora = localtime($tiempo, true);
  
  $min = $hora['tm_min'];
  $seg = $hora['tm_sec'];

  if($hora['tm_min'] < 10)
    $min = '0'.$hora['tm_min'];

  if($hora['tm_sec'] < 10)
    $seg = '0'.$hora['tm_sec'];

  $_SESSION['fecha'] = ($hora['tm_year']+ 1900).'-'.($hora['tm_mon']+1).'-'.$hora['tm_mday'];
  $_SESSION['hora'] = $hora['tm_hour'].':'.$min.':'.$seg;

  

 ?>
<!-- Navbar -->
<nav style="background-color: #135351;" class="navbar navbar-expand navbar-light border-bottom">
<!-- Left navbar links -->
	<ul class="navbar-nav">
      <li class="nav-item d-none d-sm-inline-block">
        <h1 style="color: white;">CAI</h1>
    </li>
      
  </ul>

  <?php 

  if(isset($_GET['user'])){ ?>

  <!-- Right navbar links -->
  <ul class="navbar-nav ml-auto" >
    <?php if($_GET['user'] == 'admin'){ ?>
    <li class="nav-item d-none d-sm-inline-block">
        <a href="index.php?user=admin&action=visitas" class="nav-link" style="color: white;">Visitas</a>
    </li>
    <li class="nav-item d-none d-sm-inline-block">
      <a href="index.php?user=admin&action=teachers" class="nav-link" style="color: white;">Teachers</a>
    </li>
    <li class="nav-item d-none d-sm-inline-block">
      <a href="index.php?user=admin&action=grupos" class="nav-link" style="color: white;">Grupos</a>
    </li>
     <li class="nav-item d-none d-sm-inline-block">
      <a href="index.php?user=admin&action=actividades" class="nav-link" style="color: white;">Actividades</a>
    </li>
    <?php }else{ ?>
    <li class="nav-item d-none d-sm-inline-block">
      <a href="index.php?user=<?php echo $_GET['user']; ?>&action=grupos_teacher" class="nav-link" style="color: white;">Grupos</a>
    </li>
  <?php } ?>
    <li class="nav-item d-none d-sm-inline-block">
      <a href="index.php?action=salir" class="nav-link" style="color: white;">Cerrar Sesion</a>
    </li>
  </ul>
  

  <?php
  }
  else{ ?>

	<!-- Right navbar links >
	<ul class="navbar-nav ml-auto" >
    <li class="nav-item d-none d-sm-inline-block">
        <a href="index.php?action=inicio" class="nav-link" style="color: white;">Inicio</a>
    </li>
    <li class="nav-item d-none d-sm-inline-block">
      <a href="index.php?action=lugares" class="nav-link" style="color: white;">Lugares</a>
    </li>
	  <li class="nav-item d-none d-sm-inline-block">
	    <a href="index.php?action=admin" class="nav-link" style="color: white;">Admin</a>
	  </li>
	</ul-->
<?php } ?>
</nav>
<!-- /.navbar -->
<div class="" align="center">
    <!-- Content Header (Page header) -->
    <div class="content-header">
      <div class="container-fluid">
        <div class="row mb-2">
          <?php if(isset($_GET['user'])){ ?>
          <div class="col-sm-4">
            <h5>Fecha<br> <?php echo $_SESSION['fecha']; ?></h5>  
          </div>
          <div class="col-sm-4">
            <?php if(isset($_GET['user'])){
            if($_GET['user'] == 'admin'){ ?>
            <h5>Hora Asistencia<br><?php echo $_SESSION['horario']; ?></h5>  
          <?php }} ?>
          </div>
          <div class="col-sm-4">
            <h5>Hora Actual<br> <?php echo $_SESSION['hora']; ?></h5>  
          </div>
        <?php } ?>
          
          
        </div><!-- /.row -->
      </div><!-- /.container-fluid -->
    </div>