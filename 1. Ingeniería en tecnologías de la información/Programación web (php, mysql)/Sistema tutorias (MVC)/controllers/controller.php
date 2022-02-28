<?php

class MvcController{

	#LLAMADA A LA PLANTILLA
	#-------------------------------------

	public function pagina(){	
		
		include "views/template.php";
	
	}

	#ENLACES
	#-------------------------------------

	public function enlacesPaginasController(){

		if(isset( $_GET['action'])){
			
			$enlaces = $_GET['action'];
		
		}

		else{

			$enlaces = "index";
		}

		$respuesta = Paginas::enlacesPaginasModel($enlaces);

		include $respuesta;

	}

	#INGRESO DE USUARIOS
	#------------------------------------
	public function ingresoUsuarioController(){

		if(isset($_POST["usuarioIngreso"])){

			$datosController = array( "email"=>$_POST["usuarioIngreso"], 
								      "password"=>$_POST["passwordIngreso"]);

			$respuesta = Maestros::ingresoUsuarioModel($datosController);
			//Valiación de la respuesta del modelo para ver si es un usuario correcto.
			if($respuesta["email"] == $_POST["usuarioIngreso"] && $respuesta["password"] == $_POST["passwordIngreso"]){

				session_start();

				$_SESSION["validar"] = true;
				$_SESSION["usuario"] = $respuesta;
				//$_SESSION["id_usuario"] = $respuesta['id'];
				if($respuesta['email']=='admin'){
					header("location:index.php?action=sesion_tutorias");	
				}
				else{
					header("location:index.php?action=alumnos");
				}

				

			}

			else{

				header("location:index.php?action=fallo");

			}

		}	

	}

	#VISTA DE SESION DE TUTORIAS
	#------------------------------------

	public function vistaTutoriasController(){

		$respuesta = Tutorias::vistaTutoriasModel();

		#El constructor foreach proporciona un modo sencillo de iterar sobre arrays. foreach funciona sólo sobre arrays y objetos, y emitirá un error al intentar usarlo con una variable de un tipo diferente de datos o una variable no inicializada.

		foreach($respuesta as $row => $item){
		echo'<tr>
				<td>'.$item["id"].'</td>
				<td>'.$item["alumno"].'</td>
				<td>'.$item["tutor"].'</td>
				<td>'.$item["fecha"].'</td>
				<td>'.$item["hora"].'</td>
				<td>'.$item["tipo"].'</td>
				<td>'.$item["tutoria"].'</td>
			</tr>';

		}

	}
	#VISTA DE ALUMNOS
	#------------------------------------

	public function vistaAlumnosController(){

		$respuesta = Alumnos::vistaAlumnosModel();

		#El constructor foreach proporciona un modo sencillo de iterar sobre arrays. foreach funciona sólo sobre arrays y objetos, y emitirá un error al intentar usarlo con una variable de un tipo diferente de datos o una variable no inicializada.

		foreach($respuesta as $row => $item){
		echo'<tr>
				<td>'.$item["matricula"].'</td>
				<td>'.$item["nombre"].'</td>
				<td>'.$item["carrera"].'</td>
				<td>'.$item["tutor"].'</td>';
				if($_SESSION['usuario']['nombre'] == "ADMINISTRADOR"){
					echo '<td><a href="index.php?action=alumno_editar&id='.$item["matricula"].'"><button>Editar</button></a></td>
						  <td><a href="index.php?action=alumno_borrar&id='.$item["matricula"].'"><button>Eliminar</button></a></td>';
				}
		echo '</tr>';

		}

	}

	#EDITAR ALUMNO
	#------------------------------------

	public function editarAlumnosController(){

		$datosController = $_GET["id"];
		//se cargan los datos del alumno que se editará
		$respuesta = Alumnos::editarAlumnoModel($datosController);
		//se cargan las carreras disponibles
		$carreras = Carreras::getCarrerasModel();
		//se cargan los profesores disponibles
		$tutores = Maestros::getTutoresModel();

		//se realiza la estructura del formulario de edicion

		echo '<div class="form-group">
                <label for="exampleInputEmail1">Matricula</label>
                <input type="text" class="form-control" disabled placeholder="Matricula" value="'.$respuesta[0]["matricula"].'" name="matricula">
            </div>
			<div class="form-group">
                <label for="exampleInputEmail1">Nombre</label>
                <input type="text" class="form-control" id="exampleInputEmail1" placeholder="Nombre"  value="'.$respuesta[0]["nombre"].'" name="nombre" required>
            </div>
            <div class="form-group">
                <label for="exampleInputPassword1">Carrera</label>
                <select class="form-control" name="carrera"><option>'.$respuesta[0]["carrera"].'</option>';
                foreach ($carreras as $key => $car) {
                	echo "<option>".$car['nombre']."</option>";
                }
          echo '</select>
            </div>
            <div class="form-group">
                <label for="exampleInputPassword1">Tutor</label>
                <select class="form-control" name="tutor"><option>'.$respuesta[0]["tutor"].'</option>';
                foreach ($tutores as $key => $tutor) {
                	echo "<option>".$tutor['nombre']."</option>";
                }
          echo '</select>
            </div>
            <div class="form-group">
                <input type="submit" class="btn btn-primary" value="Actualizar">
            </div>';

	}
	#ACTUALIZAR ALUMNO
	#------------------------------------
	public function actualizarAlumnoController(){

		if(isset($_POST['nombre'])){

			//se guardan los valores de POST en un arreglo obtenidos del formulario

			$datosController = array( "matricula"=>$_GET['id'],
									  "nombre"=>strtoupper($_POST["nombre"]),
							          "carrera"=>strtoupper($_POST["carrera"]),
				                      "tutor"=>strtoupper($_POST["tutor"]));
			
			$respuesta = Alumnos::actualizarAlumnoModel($datosController);

			if($respuesta == "success"){

				//muestra una alerta de confirmacion de la accion
				echo '<script> alert("Se actualizo correctamente") </script>';
				//se redirecciona a la pagina principal de la seccion
				echo '<script> window.location = "index.php?action=alumnos"; </script>';

			}

			else{

				echo "error";

			}

		}
	
	}
	public function agregarAlumnosController(){

		//se obtienen las carreras disponibles
		$carreras = Carreras::getCarrerasModel();
		//se obtienen los tutores que existen
		$tutores = Maestros::getTutoresModel();


		//formulario para agregar nuevos registros

		echo '<div class="form-group">
                <label for="exampleInputEmail1">Matricula</label>
                <input type="number" class="form-control" placeholder="Matricula" name="matricula" required>
            </div>
			<div class="form-group">
                <label for="exampleInputEmail1">Nombre</label>
                <input type="text" class="form-control" id="exampleInputEmail1" placeholder="Nombre" name="nombre" required>
            </div>
            <div class="form-group">
                <label for="exampleInputPassword1">Carrera</label>
                <select class="form-control" name="carrera"><option>';
                foreach ($carreras as $key => $car) {
                	echo "<option>".$car['nombre']."</option>";
                }
          echo '</select>
            </div>
            <div class="form-group">
                <label for="exampleInputPassword1">Tutor</label>
                <select class="form-control" name="tutor"><option>';
                foreach ($tutores as $key => $tutor) {
                	echo "<option>".$tutor['nombre']."</option>";
                }
          echo '</select>
            </div>
            <div class="form-group">
                <input type="submit" class="btn btn-primary" value="Agregar">
            </div>';

	}
	#REGISTRO DE USUARIOS
	#------------------------------------
	public function registroAlumnoController(){

		if(isset($_POST["matricula"])){
			//Recibe a traves del método POST el name (html) de usuario, password y email, se almacenan los datos en una variable de tipo array con sus respectivas propiedades (usuario, password y email):
			$datosController = array( "matricula"=>$_POST["matricula"], 
								      "nombre"=>strtoupper($_POST["nombre"]),
								      "carrera"=>strtoupper($_POST["carrera"]),
								  	  "tutor"=>strtoupper($_POST["tutor"]));

			//Se le dice al modelo models/crud.php (Datos::registroUsuarioModel),que en la clase "Datos", la funcion "registroUsuarioModel" reciba en sus 2 parametros los valores "$datosController" y el nombre de la tabla a conectarnos la cual es "usuarios":
			$respuesta = Alumnos::registroAlumnoModel($datosController);

			//se imprime la respuesta en la vista 
			if($respuesta == "success"){
				echo '<script> alert("Se Agregó correctamente") </script>';
			}

			else if($respuesta == "Error"){

				echo '<script> alert("Error") </script>';
			}
			else{
				echo '<script> alert("Ya existe la matricula ingresada") </script>';
			}

			echo '<script> window.location = "index.php?action=alumnos"; </script>';

		}

	}
	
	#BORRAR USUARIO
	#------------------------------------
	public function borrarAlumnoController(){

		if(isset($_GET["id"])){

			//se obtiene el id por medio del metodo GET
			$datosController = $_GET["id"];

			//se llama al modelo para eliminar el registro con el parametro del id
			
			$respuesta = Alumnos::borrarAlumnoModel($datosController);

			if($respuesta == "success"){

				echo '<script> alert("Se eliminó correctamente") </script>';				
			
			}
			else{
				echo '<script> alert("error") </script>';
			}
			echo '<script> window.location = "index.php?action=alumnos"; </script>';

		}

	}

	#VISTA DE MAESTROS
	#------------------------------------

	public function vistaMaestrosController(){

		$respuesta = Maestros::vistaMaestrosModel();

		#El constructor foreach proporciona un modo sencillo de iterar sobre arrays. foreach funciona sólo sobre arrays y objetos, y emitirá un error al intentar usarlo con una variable de un tipo diferente de datos o una variable no inicializada.

		foreach($respuesta as $row => $item){
		echo'<tr>
				<td>'.$item["id"].'</td>
				<td>'.$item["carrera"].'</td>
				<td>'.$item["nombre"].'</td>
				<td>'.$item["email"].'</td>
				<td>'.$item["password"].'</td>
				<td><a href="index.php?action=maestro_editar&id='.$item["id"].'"><button>Editar</button></a></td>
				<td><a href="index.php?action=maestro_borrar&id='.$item["id"].'"><button>Eliminar</button></a></td>
		    </tr>';

		}

	}
	#EDITAR MAESTRO
	#------------------------------------

	public function editarMaestroController(){

		//$datosController = $_GET["id"];
		//se cargan los datos del alumno que se editará
		$respuesta = Maestros::vistaMaestrosModel();
		//se cargan las carreras disponibles
		$carreras = Carreras::getCarrerasModel();
		
		//se realiza la estructura del formulario de edicion

		echo '<div class="form-group">
                <label for="exampleInputEmail1">Id</label>
                <input type="text" class="form-control" disabled placeholder="Id" value="'.$respuesta[0]["id"].'" name="id">
            </div>
            <div class="form-group">
                <label for="exampleInputPassword1">Carrera</label>
                <select class="form-control" name="carrera"><option>'.$respuesta[0]["carrera"].'</option>';
                foreach ($carreras as $key => $car) {
                	echo "<option>".$car['nombre']."</option>";
                }
          echo '</select>
            </div>
            <div class="form-group">
                <label for="exampleInputEmail1">Nombre</label>
                <input type="text" class="form-control" id="exampleInputEmail1" placeholder="Nombre"  value="'.$respuesta[0]["nombre"].'" name="nombre" required>
            </div>
            <div class="form-group">
                <label for="exampleInputEmail1">Email</label>
                <input type="email" class="form-control" id="exampleInputEmail1" placeholder="Email"  value="'.$respuesta[0]["email"].'" name="email" required>
            </div>
            <div class="form-group">
                <label for="exampleInputEmail1">Password</label>
                <input type="text" class="form-control" id="exampleInputEmail1" placeholder="Password"  value="'.$respuesta[0]["password"].'" name="password" required>
            </div>
            <div class="form-group">
                <input type="submit" class="btn btn-primary" value="Actualizar">
            </div>';

	}
	#ACTUALIZAR MAESTRO
	#------------------------------------
	public function actualizarMaestroController(){

		if(isset($_POST['nombre'])){

			//se guardan los valores de POST en un arreglo obtenidos del formulario

			$datosController = array( "id"=>$_GET['id'],
									  "nombre"=>strtoupper($_POST["nombre"]),
							          "carrera"=>strtoupper($_POST["carrera"]),
				                      "email"=>$_POST["email"],
				                      "password"=>$_POST["password"]);
			
			$respuesta = Maestros::actualizarMaestroModel($datosController);

			if($respuesta == "success"){

				//muestra una alerta de confirmacion de la accion
				echo '<script> alert("Se actualizo correctamente") </script>';
				//se redirecciona a la pagina principal de la seccion
				echo '<script> window.location = "index.php?action=maestros"; </script>';

			}

			else{

				echo "error";

			}

		}
	
	}
	# AGREGAR MAESTROS
	public function agregarMaestrosController(){

		//se obtienen las carreras disponibles
		$carreras = Carreras::getCarrerasModel();

		//formulario para agregar nuevos registros

		echo '<div class="form-group">
                <label for="exampleInputPassword1">Carrera</label>
                <select class="form-control" name="carrera">';
                foreach ($carreras as $key => $car) {
                	echo "<option>".$car['nombre']."</option>";
                }
          echo '</select>
            </div>
            <div class="form-group">
                <label for="exampleInputEmail1">Nombre</label>
                <input type="text" class="form-control" id="exampleInputEmail1" placeholder="Nombre" name="nombre" required>
            </div>
            <div class="form-group">
                <label for="exampleInputEmail1">Email</label>
                <input type="email" class="form-control" id="exampleInputEmail1" placeholder="Email" name="email" required>
            </div>
            <div class="form-group">
                <label for="exampleInputEmail1">Password</label>
                <input type="text" class="form-control" id="exampleInputEmail1" placeholder="Password" name="password" required>
            </div>
            <div class="form-group">
                <input type="submit" class="btn btn-primary" value="Agregar">
            </div>';

	}
	#REGISTRO DE MAESTROS
	#------------------------------------
	public function registroMaestroController(){

		if(isset($_POST["nombre"])){
			//Recibe a traves del método POST el name (html) de usuario, password y email, se almacenan los datos en una variable de tipo array con sus respectivas propiedades (usuario, password y email):
			$datosController = array( "nombre"=>strtoupper($_POST["nombre"]),
							          "carrera"=>strtoupper($_POST["carrera"]),
				                      "email"=>$_POST["email"],
				                      "password"=>$_POST["password"]);

			//Se le dice al modelo models/crud.php (Datos::registroUsuarioModel),que en la clase "Datos", la funcion "registroUsuarioModel" reciba en sus 2 parametros los valores "$datosController" y el nombre de la tabla a conectarnos la cual es "usuarios":
			$respuesta = Maestros::registroMaestroModel($datosController);

			//se imprime la respuesta en la vista 
			if($respuesta == "success"){
				echo '<script> alert("Se Agregó correctamente") </script>';
			}

			else if($respuesta == "Error"){

				echo '<script> alert("Error") </script>';
			}
			else{
				echo '<script> alert("Ya existe el email ingresado") </script>';
			}

			echo '<script> window.location = "index.php?action=maestros"; </script>';

		}

	}
	
	#BORRAR MAESTRO
	#------------------------------------
	public function borrarMaestroController(){

		if(isset($_GET["id"])){

			//se obtiene el id por medio del metodo GET
			$datosController = $_GET["id"];

			//se llama al modelo para eliminar el registro con el parametro del id
			
			$respuesta = Maestros::borrarMaestroModel($datosController);

			if($respuesta == "success"){

				echo '<script> alert("Se eliminó correctamente") </script>';				
			
			}
			else{
				echo '<script> alert("No se puede eliminar, se asignó como Tutor a un alumno. Para eliminar cambie de tutor al alumno") </script>';
			}
			echo '<script> window.location = "index.php?action=maestros"; </script>';

		}

	}
	#VISTA DE CARRERAS
	#------------------------------------

	public function vistaCarrerasController(){

		$respuesta = Carreras::vistaCarreraModel();

		#El constructor foreach proporciona un modo sencillo de iterar sobre arrays. foreach funciona sólo sobre arrays y objetos, y emitirá un error al intentar usarlo con una variable de un tipo diferente de datos o una variable no inicializada.

		foreach($respuesta as $row => $item){
		echo'<tr>
				<td>'.$item["id"].'</td>
				<td>'.$item["nombre"].'</td>
				<td><a href="index.php?action=carrera_editar&id='.$item["id"].'"><button>Editar</button></a></td>
				<td><a href="index.php?action=carrera_borrar&id='.$item["id"].'"><button>Eliminar</button></a></td>
		    </tr>';

		}

	}
	#EDITAR MAESTRO
	#------------------------------------

	public function editarCarreraController(){

		//$datosController = $_GET["id"];
		//se cargan los datos del alumno que se editará
		$respuesta = Carreras::vistaCarreraModel();
		
		//se realiza la estructura del formulario de edicion

		echo '<div class="form-group">
                <label for="exampleInputEmail1">Id</label>
                <input type="text" class="form-control" disabled placeholder="Id" value="'.$respuesta[0]["id"].'" name="id">
            </div>
            <div class="form-group">
                <label for="exampleInputEmail1">Nombre</label>
                <input type="text" class="form-control" id="exampleInputEmail1" placeholder="Nombre"  value="'.$respuesta[0]["nombre"].'" name="nombre" required>
            </div>
            <div class="form-group">
                <input type="submit" class="btn btn-primary" value="Actualizar">
            </div>';

	}
	#ACTUALIZAR CARRERA
	#------------------------------------
	public function actualizarCarreraController(){

		if(isset($_POST['nombre'])){

			//se guardan los valores de POST en un arreglo obtenidos del formulario

			$datosController = array( "id"=>$_GET['id'],
									  "nombre"=>strtoupper($_POST["nombre"]));
			
			$respuesta = Carreras::actualizarCarreraModel($datosController);

			if($respuesta == "success"){

				//muestra una alerta de confirmacion de la accion
				echo '<script> alert("Se actualizo correctamente") </script>';
				//se redirecciona a la pagina principal de la seccion
				echo '<script> window.location = "index.php?action=carreras"; </script>';

			}

			else{

				echo "error";

			}

		}
	
	}
	# AGREGAR CARRERA
	public function agregarCarreraController(){

		//formulario para agregar nuevos registros

		echo '<div class="form-group">
                <label for="exampleInputEmail1">Nombre</label>
                <input type="text" class="form-control" id="exampleInputEmail1" placeholder="Nombre" name="nombre" required>
            </div>
            <div class="form-group">
                <input type="submit" class="btn btn-primary" value="Agregar">
            </div>';

	}
	#REGISTRO DE MAESTROS
	#------------------------------------
	public function registroCarreraController(){

		if(isset($_POST["nombre"])){
			//Recibe a traves del método POST el name (html) de usuario, password y email, se almacenan los datos en una variable de tipo array con sus respectivas propiedades (usuario, password y email):
			$datosController = array( "nombre"=>strtoupper($_POST["nombre"]));

			//Se le dice al modelo models/crud.php (Datos::registroUsuarioModel),que en la clase "Datos", la funcion "registroUsuarioModel" reciba en sus 2 parametros los valores "$datosController" y el nombre de la tabla a conectarnos la cual es "usuarios":
			$respuesta = Carreras::registroCarreraModel($datosController);

			//se imprime la respuesta en la vista 
			if($respuesta == "success"){
				echo '<script> alert("Se Agregó correctamente") </script>';
			}

			else if($respuesta == "Error"){

				echo '<script> alert("Error") </script>';
			}
			else{
				echo '<script> alert("Ya existe la carrera ingresado") </script>';
			}

			echo '<script> window.location = "index.php?action=carreras"; </script>';

		}

	}
	
	#BORRAR MAESTRO
	#------------------------------------
	public function borrarCarreraController(){

		if(isset($_GET["id"])){

			//se obtiene el id por medio del metodo GET
			$datosController = $_GET["id"];

			//se llama al modelo para eliminar el registro con el parametro del id
			
			$respuesta = Carreras::borrarCarreraModel($datosController);

			if($respuesta == "success"){

				echo '<script> alert("Se eliminó correctamente") </script>';				
			
			}
			else{
				echo '<script> alert("No se puede eliminar porque esta referenciada") </script>';
			}
			echo '<script> window.location = "index.php?action=carreras"; </script>';

		}

	}
	
}

////
?>