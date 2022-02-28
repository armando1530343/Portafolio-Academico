<?php
//--

class Mvc{

	#LLAMADA A LA PLANTILLA
	#-------------------------------------

	public function pagina(){
		
		include "views/template.php";
	}

	#ENLACES
	#-------------------------------------

	public function enlacesPaginasController(){
		if(isset($_GET['action'])){
			$enlaces = $_GET['action'];
		}
		else{

			$enlaces = "index";
		}
		$respuesta = Paginas::enlacesPaginasModel($enlaces);
		include $respuesta;
	}

	public function ingresaAdminController(){
		if(isset($_POST['ingresar'])){
			#parametros de administrador
			$login = CRUD::ingresaUsuariosModel($_POST['username'], $_POST['password']);
			#se verifica que el nombre de usuario y la contraseña sea 'admin'
			if($login == 1){
				$_SESSION['validar'] = true;
				echo "<script> window.location = 'index.php?user=admin&pass=".$_POST['password']."&action=visitas&start=1'; </script>";
			}
			else if($login == 2){
				$_SESSION['validar'] = true;
				echo "<script> window.location = 'index.php?user=".$_POST['username']."&action=grupos_teacher'; </script>";
			}
			else{
				echo "<script> window.location = 'index.php?action=error'; </script>";
			}
		}
	}

	// GESTION DE TEACHERS --------------------------

	public function vistaTeachersController(){
		$teachers = CRUD::vistaTeachersModel();

		foreach($teachers as $row => $item){ 
			echo'<tr>
					<td>'.$item["id_teacher"].'</td>					
					<td>'.$item["nombre_completo"].'</td>
					<td style="text-align: center;"><a href="index.php?user=admin&action=editar_teacher&id='.$item["id_teacher"].'&username='.$item["username"].'"><button class="btn btn-warning">Editar</button></a></td>
					<td style="text-align: center;"><a href="index.php?user=admin&action=eliminar_teacher&id='.$item["id_teacher"].'"><button class="btn btn-danger">Eliminar</button></a></td>';

		}
	}
	public function agregarTeacherController(){

		echo '  <div class="card-body">
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="text" class="form-control" required name="nombre" placeholder="Nombre Completo">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="text" class="form-control" required name="username" placeholder="Nombre de Usuario">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="password" class="form-control" required name="password" placeholder="Contraseña">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="password" class="form-control" required name="password2" placeholder="Confirmar Contraseña">
	                </div>
	              </div>	              
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	              <button type="submit" class="btn btn-success">Agregar Teacher</button>
	              <a href="index.php?user=admin&action=teachers" class="btn btn-default">Cancelar</a>
	            </div>';
	}
	public function registroTeacherController(){
		if(isset($_POST["nombre"])){

			if($_POST['password'] == $_POST['password2']){
				$datosTeacher = array( "nombre"=>strtoupper($_POST["nombre"]), 
								      "username"=>$_POST["username"],
								  	  "password"=>$_POST["password"]);

				$respuesta = CRUD::registroTeacherModel($datosTeacher);
				echo '<script> window.location = "index.php?user=admin&action=teachers&status='.$respuesta.'"; </script>';
			}
			else
				echo '<script> window.location = "index.php?user=admin&action=agregar_teacher&status=password"; </script>';	
		}

	}
	public function editarTeacherController(){

		$teacher = CRUD::getTeacherModel($_GET['id']);

		echo '  <div class="card-body">
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="text" class="form-control" required name="nombre" placeholder="Nombre Completo" value="'.$teacher[0]['nombre_completo'].'">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="text" class="form-control" required name="username" placeholder="Nombre de Usuario" value="'.$teacher[0]['username'].'">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="password" class="form-control" required name="password" placeholder="Contraseña" value="'.$teacher[0]['password'].'">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="password" class="form-control" required name="password2" placeholder="Confirmar Contraseña" value="'.$teacher[0]['password'].'">
	                </div>
	              </div>	              
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	              <button type="submit" class="btn btn-success">Actualizar Información</button>
	              <a href="index.php?user=admin&action=teachers" class="btn btn-default">Cancelar</a>
	            </div>';
	}
	public function actualizarTeacherController(){
		if(isset($_POST["nombre"])){

			if($_POST['password'] == $_POST['password2']){
				$datosTeacher = array("id" => $_GET['id'], 
									  "nombre"=>strtoupper($_POST["nombre"]), 
								      "username"=>$_POST["username"],
								  	  "password"=>$_POST["password"]);

				$respuesta = CRUD::actualizarTeacherModel($datosTeacher, $_GET['username']);
				echo '<script> window.location = "index.php?user=admin&action=teachers&status='.$respuesta.'"; </script>';
			}
			else
				echo '<script> window.location = "index.php?user=admin&action=editar_teacher&status=password"; </script>';	
		}

	}
	public function eliminaTeacherController(){
		if(isset($_POST['password'])){
			if($_POST['password'] == $_SESSION['password']){
				$respuesta = CRUD::eliminaTeacherModel($_GET['id']);
				echo '<script> window.location = "index.php?user=admin&action=teachers&status='.$respuesta.'"; </script>';
			}
			else
				echo '<script> window.location = "index.php?user=admin&action=eliminar_teacher&id='.$_GET["id"].'&status=password"; </script>';
		}
	}

	public function getUserTeacherController(){
		return CRUD::getUserTeacherModel($_GET['user']);
	}

	// GESTION DE GRUPOS --------------------------

	public function vistaGruposController(){
		$grupos = CRUD::vistaGruposModel();

		foreach($grupos as $row => $item){ 
			echo'<tr>
					<td>'.$item["id_grupo"].'</td>					
					<td>'.$item["nivel"].'</td>
					<td>'.$item["teacher"].'</td>
					<td>'.$item["grupo"].'</td>
					<td>'.$item["unidades"].'</td>
					<td style="text-align: center;"><a href="index.php?user=admin&action=vista_grupo&id_grupo='.$item["id_grupo"].'"><button class="btn btn-info">Ver Grupo</button></a></td>
					<td style="text-align: center;"><a href="index.php?user=admin&action=editar_grupo&id='.$item["id_grupo"].'"><button class="btn btn-warning">Editar</button></a></td>
					<td style="text-align: center;"><a href="index.php?user=admin&action=eliminar_grupo&id='.$item["id_grupo"].'"><button class="btn btn-danger">Eliminar</button></a></td></tr>';

		}
	}
	
	public function getGrupoController(){
		return CRUD::getGrupoModel($_GET['id_grupo']);

	}
	public function agregarGrupoController(){

		$nivel = CRUD::getNivelModel();
		$teachers = CRUD::vistaTeachersModel();

		echo '  <div class="card-body">
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">Nivel:</label>
	                </div>
	                <div class="col-sm-10">
	                  <select class="form-control" name="nivel">';
	                 foreach ($nivel as $key => $value) {
	                 	echo '<option>'.$value['id_nivel'].'</option>';
	                 }
	            echo '</select>
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">Teacher:</label>
	                </div>
	                <div class="col-sm-10">
	                  <select class="form-control" name="teacher">';
	                 foreach ($teachers as $key => $value) {
	                 	echo '<option>'.$value['nombre_completo'].'</option>';
	                 }
	            echo '</select>
	                </div>
	              </div>	                       
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	              <button type="submit" class="btn btn-success">Agregar Grupo</button>
	              <a href="index.php?user=admin&action=grupos" class="btn btn-default">Cancelar</a>
	            </div>';
	}
	public function registroGrupoController(){
		if(isset($_POST["nivel"])){

			$datosGrupo = array( "nivel"=>$_POST["nivel"], 
								 "teacher"=>$_POST["teacher"]);

			$respuesta = CRUD::registroGrupoModel($datosGrupo);
			echo '<script> window.location = "index.php?user=admin&action=grupos&status='.$respuesta.'"; </script>';
		}

	}
	public function editarGrupoController(){

		$grupo = CRUD::getGrupoModel($_GET['id']);
		$teachers = CRUD::vistaTeachersModel();

		echo '  <div class="card-body">
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">Teacher:</label>
	                </div>
	                <div class="col-sm-10">
	                  <select class="form-control" name="teacher">
	                  		<option>'.$grupo[0]['teacher'].'</option>';
	                 foreach ($teachers as $key => $value) {
	                 	echo '<option>'.$value['nombre_completo'].'</option>';
	                 }
	            echo '</select>
	                </div>
	              </div>
	              <div class="form-group row" align="right">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">Unidades:</label>
	                </div>
	              	<div class="col-sm-10">
	                  <input type="number" class="form-control" name="unidades" required placeholder="Numero de Unidades" value="'.$grupo[0]['unidades'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	                <div class="col-sm-2" align="right">
	                  <label class="control-label">Horas:</label>
	                </div>
	              	<div class="col-sm-10">
	                  <input type="number" class="form-control" name="horas" required placeholder="Horas x Unidad" value="'.$grupo[0]['horas_unidad'].'">
	                </div>
	              </div>	              
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	              <button type="submit" class="btn btn-success">Actualizar Grupo</button>
	              <a href="index.php?user=admin&action=grupos" class="btn btn-default">Cancelar</a>
	            </div>';
	}
	public function actualizarGrupoController(){
		if(isset($_POST["teacher"])){

			$datosGrupo = array( "id"=>$_GET["id"],
								 "teacher"=>$_POST["teacher"],
								 "unidades"=>$_POST["unidades"],
								 "horas"=>$_POST["horas"]);

			$respuesta = CRUD::actualizarGrupoModel($datosGrupo);
			echo '<script> window.location = "index.php?user=admin&action=grupos&status='.$respuesta.'"; </script>';
		}

	}
	public function eliminaGrupoController(){
		if(isset($_POST['password'])){
			if($_POST['password'] == $_SESSION['password']){
				$respuesta = CRUD::eliminaGrupoModel($_GET['id']);
				echo '<script> window.location = "index.php?user=admin&action=grupos&status='.$respuesta.'"; </script>';
			}
			else
				echo '<script> window.location = "index.php?user=admin&action=eliminar_grupo&id='.$_GET["id"].'&status=password"; </script>';
		}
	}

	// --------------------------------------------

	// GESTION DE UNIDADES --------------------------

	public function vistaUnidadesController(){
		$unidades = CRUD::vistaUnidadesModel($_GET['id_grupo']);
		$ultimo = $unidades->rowCount();

		$i = 1;
		//echo '<script>alert("'.$unidades->rowCount().'");</script>';
		foreach($unidades->fetchAll() as $row => $item){ 
			echo'<tr>
					<td>UNIDAD '.$item["unidad"].'</td>					
					<td>'.$item["fecha_inicio"].'</td>
					<td>'.$item["fecha_fin"].'</td>
					<td>'.$item["horas"].'</td>';
			if($_GET['user'] == 'admin'){
			  echo '<td style="text-align: center;"><a href="index.php?user=admin&action=editar_unidad&id='.$item["id_unidad"].'&id_grupo='.$_GET["id_grupo"].'"><button class="btn btn-warning">Editar</button></a></td>';
				
				if($i == $unidades->rowCount()){
			  echo '<td style="text-align: center;"><a href="index.php?user=admin&action=eliminar_unidad&id='.$item["id_unidad"].'&id_grupo='.$_GET["id_grupo"].'"><button class="btn btn-danger">Eliminar</button></a></td></tr>';
			    }
				$i++;
			}

		}
	}
	public function agregarUnidadController(){

		echo '  <div class="card-body">
				  <div class="form-group row">
	                <div class="col-sm-3" align="right">
	                  <label class="control-label">Fecha Inicio:</label>
	                </div>
	              	<div class="col-sm-9">
	                  <input type="date" class="form-control" name="inicio" required>
	                </div>
	              </div>
	              <div class="form-group row">
	                <div class="col-sm-3" align="right">
	                  <label class="control-label">Fecha Fin:</label>
	                </div>
	              	<div class="col-sm-9">
	                  <input type="date" class="form-control" name="fin" required>
	                </div>
	              </div>
	              <div class="form-group row">
	                <div class="col-sm-3" align="right">
	                  <label class="control-label">Horas:</label>
	                </div>
	              	<div class="col-sm-9">
	                  <input type="number" class="form-control" name="horas" required>
	                </div>
	              </div>
	                                 
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	              <button type="submit" class="btn btn-success">Agregar Unidad</button>
	              <a href="index.php?user=admin&action=unidades&id_grupo='.$_GET['id_grupo'].'" class="btn btn-default">Cancelar</a>
	            </div>';
	}
	public function registroUnidadController(){
		if(isset($_POST["inicio"])){

			$datosUnidad = array("inicio"=>$_POST["inicio"], 
								 "fin"=>$_POST["fin"],
								 "horas"=>$_POST["horas"],
								 "id_grupo" => $_GET['id_grupo']);

			$respuesta = CRUD::registroUnidadModel($datosUnidad);
			echo '<script> window.location = "index.php?user=admin&action=unidades&id_grupo='.$_GET['id_grupo'].'&status='.$respuesta.'"; </script>';
		}

	}
	public function editarUnidadController(){

		$unidad = CRUD::getUnidadModel($_GET['id']);
		
		echo '  <div class="card-body">
				  <div class="form-group row">
	                <div class="col-sm-3" align="right">
	                  <label class="control-label">Fecha Inicio:</label>
	                </div>
	              	<div class="col-sm-9">
	                  <input type="date" class="form-control" name="inicio" required value="'.$unidad[0]['fecha_inicio'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	                <div class="col-sm-3" align="right">
	                  <label class="control-label">Fecha Fin:</label>
	                </div>
	              	<div class="col-sm-9">
	                  <input type="date" class="form-control" name="fin" required value="'.$unidad[0]['fecha_fin'].'">
	                </div>
	              </div>
	                                 
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	              <button type="submit" class="btn btn-success">Guardar Cambios</button>
	              <a href="index.php?user=admin&action=unidades&id_grupo='.$_GET['id_grupo'].'" class="btn btn-default">Cancelar</a>
	            </div>';
	}
	public function actualizarUnidadController(){
		if(isset($_POST["inicio"])){

			$datosUnidad = array("id" => $_GET['id'], 
								 "inicio"=>$_POST["inicio"], 
								 "fin"=>$_POST["fin"],
								 "id_grupo" => $_GET['id_grupo']);

			$respuesta = CRUD::actualizarUnidadModel($datosUnidad);
			echo '<script> window.location = "index.php?user=admin&action=unidades&id_grupo='.$_GET['id_grupo'].'&status='.$respuesta.'"; </script>';
		}

	}
	public function eliminaUnidadController(){
		if(isset($_POST['password'])){
			if($_POST['password'] == $_SESSION['password']){
				$respuesta = CRUD::eliminaUnidadModel($_GET['id']);
				echo '<script> window.location = "index.php?user=admin&action=unidades&id_grupo='.$_GET["id_grupo"].'"; </script>';
			}
			else
				echo '<script> window.location = "index.php?user=admin&action=eliminar_grupo&id='.$_GET["id"].'&id_grupo='.$_GET["id_grupo"].'&status=password"; </script>';
		}
	}

	// --------------------------------------------

	// GESTION DE ALUMNOS --------------------------

	public function vistaAlumnosController(){
		$alumnos = CRUD::vistaAlumnosModel($_GET['id_grupo'], $_SESSION['horario'].' '.$_SESSION['fecha']);

		foreach($alumnos as $row => $item){ 
			echo'<tr>
					<td>'.$item["matricula"].'</td>					
					<td>'.$item["nombre"].'</td>
					<td>'.$item["carrera"].'</td>
					<td>'.$item["horas"].'</td>
					<td style="text-align: center;"><a href="index.php?user='.$_GET["user"].'&action=horas_alumno&id_grupo='.$_GET["id_grupo"].'&mat='.$item["matricula"].'&alumno='.$item["nombre"].'"><button class="btn btn-info">Ver Horas</button></a></td>';
					if($_GET['user'] == 'admin'){

			  echo '<td style="text-align: center;"><a href="index.php?user=admin&action=editar_alumno&id_grupo='.$_GET["id_grupo"].'&mat='.$item["matricula"].'"><button class="btn btn-warning">Editar</button></a></td>
					<td style="text-align: center;"><a href="index.php?user=admin&action=eliminar_alumno&id_grupo='.$_GET["id_grupo"].'&mat='.$item["matricula"].'"><button class="btn btn-danger">Eliminar</button></a></td>';
					}

		}
	}
	public function vistaHorasAlumnoController(){
		$horas = CRUD::vistaHorasAlumnosModel($_GET['mat'], $_SESSION['horario'].' '.$_SESSION['fecha']);


		foreach($horas as $row => $item){ 
			echo'<tr>
					<td>'.$item["horario"].'</td>
					<td>'.$item["inicio"].'</td>					
					<td>'.$item["actividad"].'</td>
					<td>'.$item["unidad"].'</td>';

		}
	}
	public function agregarAlumnoController(){

		//$nivel = CRUD::getNivelModel();
		//$grupos = CRUD::vistaGruposModel();
		$carreras = CRUD::getCarrerasModel();

		echo '  <div class="card-body">
	              <div class="form-group row">
	                <div class="col-sm-3" align="right">
	                  <label class="control-label">Matricula:</label>
	                </div>
	              	<div class="col-sm-9">
	                  <input type="number" class="form-control" name="matricula" required placeholder="Matricula">
	                </div>
	              </div>
	              <div class="form-group row" align="right">
	              	<div class="col-sm-3" align="right">
	                  <label class="control-label">Nombre Completo:</label>
	                </div>
	              	<div class="col-sm-9">
	                  <input type="text" class="form-control" name="nombre" required placeholder="Nombre Completo">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-3" align="right">
	                  <label class="control-label">Carrera:</label>
	                </div>
	                <div class="col-sm-9">
	                  <select class="form-control" name="carrera" required>';
	                 foreach ($carreras as $key => $value) {
	                 	echo '<option>'.$value['nombre'].'</option>';
	                 }
	            echo '</select>
	                </div>
	              </div>          	              
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	              <button type="submit" class="btn btn-success">Agregar Alumno</button>
	              <a href="index.php?user=admin&action=vista_grupo&id_grupo='.$_GET['id_grupo'].'" class="btn btn-default">Cancelar</a>
	            </div>';
	}
	public function registroAlumnoController(){
		if(isset($_POST["matricula"])){

			$grupo = CRUD::getGrupoModel($_GET['id_grupo']);
			$grupo = $grupo[0]['id_grupo'];
			//echo '<script>alert("'.$grupo.'");</script>';
			$datosAlumno = array( "matricula"=>$_POST["matricula"], 
								 "nombre"=>strtoupper($_POST["nombre"]),
								 "carrera"=>$_POST["carrera"],
								 "grupo"=>$grupo);


			$respuesta = CRUD::registroAlumnoModel($datosAlumno);
			if($respuesta == 'existe_alumno')
				echo '<script> window.location = "index.php?user=admin&action=agregar_alumno&id_grupo='.$_GET['id_grupo'].'&status='.$respuesta.'"; </script>';
			else
				echo '<script> window.location = "index.php?user=admin&action=vista_grupo&id_grupo='.$_GET['id_grupo'].'&status='.$respuesta.'"; </script>';
		}

	}
	public function editarAlumnoController(){

		$alumno = CRUD::getAlumnoModel($_GET['mat'], $_GET['id_grupo']);
		
		$grupos = CRUD::vistaGruposModel();
		$carreras = CRUD::getCarrerasModel();

		echo '  <div class="card-body">
	              <div class="form-group row">
	                <div class="col-sm-3" align="right">
	                  <label class="control-label">Matricula:</label>
	                </div>
	              	<div class="col-sm-9">
	                  <input type="number" class="form-control" name="matricula" disabled value="'.$alumno[0]['matricula'].'">
	                </div>
	              </div>
	              <div class="form-group row" align="right">
	              	<div class="col-sm-3" align="right">
	                  <label class="control-label">Nombre Completo:</label>
	                </div>
	              	<div class="col-sm-9">
	                  <input type="text" class="form-control" name="nombre" required placeholder="Nombre Completo" value="'.$alumno[0]['nombre'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-3" align="right">
	                  <label class="control-label">Carrera:</label>
	                </div>
	                <div class="col-sm-9">
	                  <select class="form-control" name="carrera" required>
	                  		<option>'.$alumno[0]['carrera'].'</option>';
	                 foreach ($carreras as $key => $value) {
	                 	echo '<option>'.$value['nombre'].'</option>';
	                 }
	            echo '</select>
	                </div>
	              </div>   
	              <div class="form-group row">
	              	<div class="col-sm-3" align="right">
	                  <label class="control-label">Grupo:</label>
	                </div>
	                <div class="col-sm-9">
	                  <select class="form-control" name="grupo" required>
	                  		<option>'.$alumno[0]['grupo'].'</option>';
	                 foreach ($grupos as $key => $value) {
	                 	echo '<option>'.$value['grupo'].'</option>';
	                 }
	            echo '</select>
	                </div>
	              </div>
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	              <button type="submit" class="btn btn-success">Actualizar Informacion</button>
	              <a href="index.php?user=admin&action=vista_grupo&id_grupo='.$_GET['id_grupo'].'" class="btn btn-default">Cancelar</a>
	            </div>';
	}
	public function actualizarAlumnoController(){
		if(isset($_POST["nombre"])){

			$datosAlumno = array( "matricula"=>$_GET["mat"],
								 "nombre"=>strtoupper($_POST["nombre"]),
								 "carrera"=>$_POST["carrera"],
								 "grupo"=>$_POST["grupo"]);

			$respuesta = CRUD::actualizarAlumnoModel($datosAlumno);
			echo '<script> window.location = "index.php?user=admin&action=vista_grupo&id_grupo='.$_GET['id_grupo'].'&status='.$respuesta.'"; </script>';
		}

	}
	public function eliminaAlumnoController(){
		if(isset($_POST['password'])){
			if($_POST['password'] == $_SESSION['password']){
				CRUD::eliminaAlumnoModel($_GET['mat']);
				echo '<script> window.location = "index.php?user=admin&action=vista_grupo&id_grupo='.$_GET["id_grupo"].'&status=borrado"; </script>';
			}
			else
				echo '<script> window.location = "index.php?user=admin&action=eliminar_alumno&id_grupo='.$_GET["id_grupo"].'&mat='.$_GET["mat"].'&status=password"; </script>';
		}
	}

	// --------------------------------------------
	// GESTION DE VISITAS --------------------------

	public function vistaVisitasController(){
		$visitas = CRUD::vistaVisitasModel($_SESSION['horario'].' '.$_SESSION['fecha']);

		foreach($visitas as $row => $item){ 
			echo'<tr>
					<td>'.$item["id_visita"].'</td>
					<td>'.$item["alumno"].'</td>
					<td>'.$item["teacher"].'</td>
					<td>'.$item["grupo"].'</td>
					<td>'.$item["unidad"].'</td>
					<td>'.$item["actividad"].'</td>
					<td style="text-align: center;"><a href="index.php?user=admin&action=eliminar_visita&id='.$item["id_visita"].'"><button class="btn btn-danger">Marcar Salida</button></a></td>';

		}
	}
	public function agregarVisitaController(){

		$teacher = null;
		
		$alumnos = CRUD::getMatriculas();
		$actividades = CRUD::vistaActividadesModel();
		if(isset($_GET['matricula'])){
			$alumno = CRUD::getUnidadesMatriculaModel($_GET['matricula'], $_SESSION['fecha']);
			if($alumno == "error")
				echo '<script> window.location = "index.php?user=admin&action=agregar_visita&status='.$alumno.'"; </script>';
		}

		if(isset($_GET['alumno'])){
			$alumno = CRUD::getUnidadesNombreModel($_GET['alumno'], $_SESSION['fecha']);
			if($alumno == "error")
				echo '<script> window.location = "index.php?user=admin&action=agregar_visita&status='.$alumno.'"; </script>';
		}

		$_SESSION['unidad'] = 0;		
		
		$carreras = CRUD::getCarrerasModel();

		echo "<script>
				function activa_matricula(matricula){
					window.location = 'index.php?user=admin&action=agregar_visita&matricula=' + matricula.value;
				}

				function activa_alumno(alumno){
					window.location = 'index.php?user=admin&action=agregar_visita&alumno=' + alumno.value;
				}
			  </script> ";

		echo '  <div class="card-body">
				  <div class="form-group row">
	              	<div class="col-sm-3" align="right">
	                  <label class="control-label">Matricula:</label>
	                </div>
	                <div class="col-sm-9">
	                  <select class="form-control select2" name="matricula" onChange="activa_matricula(this)" required>';
	                if(isset($_GET['matricula']))
		            	echo '<option>'.$_GET['matricula'].'</option>';
		            else if(isset($_GET['alumno']))
		            	echo '<option>'.$alumno[0]['matricula'].'</option>';
		            else
	            		echo '<option></option>';

	                 foreach ($alumnos as $key => $value) {
	                 	echo '<option>'.$value['matricula'].'</option>';
	                 }
	            echo '</select>
	                </div>
	              </div> 
	              <div class="form-group row">
	              	<div class="col-sm-3" align="right">
	                  <label class="control-label">Alumno:</label>
	                </div>
	                <div class="col-sm-9">
	                  <select class="form-control select2" name="alumno" onChange="activa_alumno(this)" required>';
	                if(isset($_GET['alumno']))
		            	echo '<option>'.$_GET['alumno'].'</option>';
		            else if(isset($_GET['matricula']))
		            	echo '<option>'.$alumno[0]['alumno'].'</option>';
		            else
	            		echo '<option></option>';

	                 foreach ($alumnos as $key => $value) {
	                 	echo '<option>'.$value['nombre_completo'].'</option>';
	                 }
	            echo '</select>
	                </div>
	              </div> 
	               <div class="form-group row">
	                <div class="col-sm-3" align="right">
	                  <label class="control-label">Teacher:</label>
	                </div>
	              	<div class="col-sm-9">
	                  <input type="text" class="form-control" name="teacher" disabled ';
	                  if(isset($_GET['matricula']) || isset($_GET['alumno'])){ 
	                  	if($alumno != "error")
	                  		echo 'value="'.$alumno[0]['teacher'].'"';
	                  }
	                  echo '>
	                </div>
	              </div>
	               <div class="form-group row">
	                <div class="col-sm-3" align="right">
	                  <label class="control-label">Grupo:</label>
	                </div>
	              	<div class="col-sm-9">
	                  <input type="text" class="form-control" name="grupo" disabled ';
	                  if(isset($_GET['matricula']) || isset($_GET['alumno'])) echo 'value="'.$alumno[0]['grupo'].'"';
	                  echo '>
	                </div>
	              </div>
	               <div class="form-group row">
	                <div class="col-sm-3" align="right">
	                  <label class="control-label">Unidad:</label>
	                </div>
	              	<div class="col-sm-9">
	                  <input type="text" class="form-control" name="unidad" disabled ';
	                  if(isset($_GET['matricula']) || isset($_GET['alumno'])) {
	                  	echo 'value="'.$alumno[0]['unidad'].'"';
	                  	$_SESSION['unidad'] = $alumno[0]['unidad'];
	                  }
	                  echo '>
	                </div>
	              </div>
	              
	              <div class="form-group row">
	              	<div class="col-sm-3" align="right">
	                  <label class="control-label">Actividad:</label>
	                </div>
	                <div class="col-sm-9">
	                  <select class="form-control" name="actividad" required">';
	                 foreach ($actividades as $key => $value) {
	                 	echo '<option>'.$value['nombre'].'</option>';
	                 }
	            echo '</select>
	                </div>
	              </div>

	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	              <button type="submit" class="btn btn-success">Agregar Registro</button>
	              <a href="index.php?user=admin&action=visitas" class="btn btn-default">Cancelar</a>
	            </div>';
	}
	public function registroVisitaController(){
		if(isset($_POST["matricula"])){

			//$grupo = CRUD::getGrupoModel($_GET['id_grupo']);
			//$grupo = $grupo[0]['id_grupo'];
			//echo '<script>alert("'.$grupo.'");</script>';
			//echo '<script>alert("'.$_POST['actividad'].'");</script>';

			$datosVisita = array("matricula"=>$_POST["matricula"],
								 "actividad"=>$_POST["actividad"],
								 "horario"=>$_SESSION['horario'].' '.$_SESSION['fecha'],
								 "hora_inicio"=>$_SESSION['hora'],
								 "unidad" => $_SESSION['unidad'],
								 "fecha" =>$_SESSION['fecha']);


			$respuesta = CRUD::registroVisitasModel($datosVisita);
			echo '<script> window.location = "index.php?user=admin&action=visitas&status='.$respuesta.'"; </script>';				
		}

	}
	public function eliminaVisitaController(){
		CRUD::eliminaVisitaModel($_GET['id']);
		echo '<script> window.location = "index.php?user=admin&action=visitas&status=salida"; </script>';
	}

	public function vistaHistorialController(){
		$historial = CRUD::vistaHistorialModel($_SESSION['horario'].' '.$_SESSION['fecha']);

		foreach($historial as $row => $item){ 
			echo'<tr>
					<td>'.$item["id_visita"].'</td>
					<td>'.$item["entrada"].'</td>
					<td>'.$item["alumno"].'</td>
					<td>'.$item["teacher"].'</td>
					<td>'.$item["grupo"].'</td>
					<td>'.$item["actividad"].'</td>
					<td>'.$item["unidad"].'</td>
					<td>'.$item["horario"].'</td></tr>';

		}
	}
	//---------------------------------------------
	// GESTION DE ACTIVIDADES --------------------------

	public function vistaActividadesController(){
		$actividad = CRUD::vistaActividadesModel();

		foreach($actividad as $row => $item){ 
			echo'<tr>
					<td>'.$item["id_actividad"].'</td>					
					<td>'.$item["nombre"].'</td>
					<td style="text-align: center;"><a href="index.php?user=admin&action=editar_actividad&id='.$item["id_actividad"].'&nombre='.$item["nombre"].'"><button class="btn btn-warning">Editar</button></a></td>
					<td style="text-align: center;"><a href="index.php?user=admin&action=eliminar_actividad&id='.$item["id_actividad"].'"><button class="btn btn-danger">Eliminar</button></a></td>';

		}
	}
	public function agregarActividadController(){

		echo '  <div class="card-body">
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="text" class="form-control" required name="nombre" placeholder="Nombre Actividad">
	                </div>
	              </div>	                           
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	              <button type="submit" class="btn btn-success">Agregar Actividad</button>
	              <a href="index.php?user=admin&action=actividades" class="btn btn-default">Cancelar</a>
	            </div>';
	}
	public function registroActividadController(){
		if(isset($_POST["nombre"])){

			$datosActividad = array( "nombre"=>strtoupper($_POST["nombre"]));

			$respuesta = CRUD::registroActividadModel($datosActividad);
			echo '<script> window.location = "index.php?user=admin&action=actividades&status='.$respuesta.'"; </script>';
				
		}

	}
	public function editarActividadController(){

		$actividad = CRUD::getActividadModel($_GET['id']);

		echo '  <div class="card-body">
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="text" class="form-control" required name="nombre" placeholder="Nombre Actividad" value="'.$actividad[0]['nombre'].'">
	                </div>
	              </div>	                           
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	              <button type="submit" class="btn btn-success">Actualizar Actividad</button>
	              <a href="index.php?user=admin&action=actividades" class="btn btn-default">Cancelar</a>
	            </div>';
	}
	public function actualizarActividadController(){
		if(isset($_POST["nombre"])){

			$datosActividad = array("id" => $_GET['id'], 
								  "nombre"=>strtoupper($_POST["nombre"]));

			$respuesta = CRUD::actualizarActividadModel($datosActividad, $_GET['nombre']);
			echo '<script> window.location = "index.php?user=admin&action=actividades&status='.$respuesta.'"; </script>';	
		}

	}
	public function eliminaActividadController(){
		if(isset($_POST['password'])){
			if($_POST['password'] == $_SESSION['password']){
				$respuesta = CRUD::eliminaActividadModel($_GET['id']);
				echo '<script> window.location = "index.php?user=admin&action=actividades&status='.$respuesta.'"; </script>';
			}
			else
				echo '<script> window.location = "index.php?user=admin&action=eliminar_actividad&id='.$_GET["id"].'&status=password"; </script>';
		}
	}

	// GESTION DE TEACHERS --------------------------

	public function vistaGruposTeacherController(){
		$grupos = CRUD::vistaGruposTeacherModel($_GET['user']);

		foreach($grupos as $row => $item){ 
			echo'<tr>
					<td>'.$item["id_grupo"].'</td>					
					<td>'.$item["nivel"].'</td>
					<td>'.$item["teacher"].'</td>
					<td>'.$item["grupo"].'</td>
					<td>'.$item["unidades"].'</td>
					<td style="text-align: center;"><a href="index.php?user='.$_GET['user'].'&action=vista_grupo&id_grupo='.$item["id_grupo"].'"><button class="btn btn-info">Ver asistencia</button></a></td></tr>';

		}
	}

	public function vistaAlumnosTeacherController(){
		$alumnos = CRUD::vistaAlumnosTeacherModel($_GET['id_grupo']);


		foreach($alumnos as $row => $item){ 
			echo'<tr>
					<td>'.$item["matricula"].'</td>					
					<td>'.$item["alumno"].'</td>
					<td>'.$item["carrera"].'</td>
					<td>'.$item["horas"].'</td>
					<td style="text-align: center;"><a href="index.php?user='.$_GET['user'].'&action=horas_alumno&matricula='.$_GET["matricula"].'&id_grupo='.$_GET["id_grupo"].'"><button class="btn btn-info">Ver Horas</button></a></td></tr>';
			
			echo "</tr>";

		}
	}
}
////
?>