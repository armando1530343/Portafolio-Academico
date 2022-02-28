<?php 

 ?>

<nav>
	<ul><li style="width: 100%; color: #51B8FF;"><?php session_start(); echo $_SESSION['usuario']['nombre'] ?></li></ul>
	
	<ul>
		
		<?php 
		if($_SESSION['usuario']['nombre'] == 'ADMINISTRADOR'){
		?>
		<li><a href="index.php?action=sesion_tutorias">TUTORIAS</a></li>
		<li><a href="index.php?action=alumnos">ALUMNOS</a></li>
		<li><a href="index.php?action=maestros">MAESTROS</a></li>
		<li><a href="index.php?action=carreras">CARRERAS</a></li>
		<?php } else{?>
		<li><a href="index.php?action=alumnos">TUTORADOS</a></li>
		<li><a href="index.php?action=perfil_tutor">PERFIL</a></li>
		<?php } ?>
		<li><a href="index.php?action=salir">SALIR</a></li>
	</ul>
	
</nav>

<nav style="background: gray;">
	<ul>
		<?php 

		$enlaces = array('agregar' => '', 'editar' => '', 'borrar' => '');

		if($_SESSION['usuario']['nombre'] == 'ADMINISTRADOR'){
			switch ($_GET['action']) {
				case 'alumnos':
					$enlaces['agregar'] = 'alumno_agregar';
					$enlaces['editar'] = 'alumno_editar';
					$enlaces['borrar'] = 'alumno_borrar';
					echo '<li><a href="index.php?action='.$enlaces['agregar'].'">AGREGAR</a></li>';					
					break;
				case 'maestros':
					$enlaces['agregar'] = 'maestro_agregar';
					$enlaces['editar'] = 'maestro_editar';
					$enlaces['borrar'] = 'maestro_borrar';
					echo '<li><a href="index.php?action='.$enlaces['agregar'].'">AGREGAR</a></li>';				
					break;
				case 'carreras':
					$enlaces['agregar'] = 'carrera_agregar';
					$enlaces['editar'] = 'carrera_editar';
					$enlaces['borrar'] = 'carrera_borrar';
					echo '<li><a href="index.php?action='.$enlaces['agregar'].'">AGREGAR</a></li>';
					break;
			}
		?>
		<!--li><a href="index.php">Registro</a></li-->
		<?php } ?>
	</ul>
	
</nav>