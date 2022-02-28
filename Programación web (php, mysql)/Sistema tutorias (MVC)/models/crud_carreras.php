<?php

#EXTENSIÓN DE CLASES: Los objetos pueden ser extendidos, y pueden heredar propiedades y métodos. Para definir una clase como extensión, debo definir una clase padre, y se utiliza dentro de una clase hija.

require_once "conexion.php";

//heredar la clase conexion de conexion.php para poder utilizar "Conexion" del archivo conexion.php.
// Se extiende cuando se requiere manipuar una funcion, en este caso se va a  manipular la función "conectar" del models/conexion.php:
class Carreras extends Conexion{

	//SE OBTIENEN LAS CARRERAS
	function getCarrerasModel(){
		$stmt = Conexion::conectar()->prepare("SELECT nombre FROM CARRERAS");
		$stmt->execute();
		return $stmt->fetchAll();
	}

	#VISTA CARRERA
	#-------------------------------------

	public function vistaCarreraModel(){


		if(isset($_GET['id'])){

			$id_carrera = $_GET['id'];


			$stmt = Conexion::conectar()->prepare(
				"SELECT * FROM CARRERAS WHERE id = :id_carrera");
			$stmt->bindParam('id_carrera', $id_carrera, PDO::PARAM_INT);
			

		}	
		else{
			$stmt = Conexion::conectar()->prepare("SELECT * FROM CARRERAS");

		}
		$stmt->execute();

		#fetchAll(): Obtiene todas las filas de un conjunto de resultados asociado al objeto PDOStatement. 
		return $stmt->fetchAll();

		$stmt->close();
		

	}
	#ACTUALIZAR MAESTRO
	#-------------------------------------

	public function actualizarCarreraModel($datosModel){

		
		//se hace la consulta para actualizar la tabla de alumnos
		$stmt = Conexion::conectar()->prepare("UPDATE CARRERAS SET nombre = :nombre WHERE id = :id");
		$stmt->bindParam(":id", $datosModel["id"], PDO::PARAM_INT);
		$stmt->bindParam(":nombre", $datosModel["nombre"], PDO::PARAM_STR);

		if($stmt->execute()){
			
			return "success";

		}

		else{

			return "error";

		}

		$stmt->close();

	}
	#REGISTRO DE MAESTROS
	#-------------------------------------
	public function registroCarreraModel($datosModel){

		#prepare() Prepara una sentencia SQL para ser ejecutada por el método PDOStatement::execute(). La sentencia SQL puede contener cero o más marcadores de parámetros con nombre (:name) o signos de interrogación (?) por los cuales los valores reales serán sustituidos cuando la sentencia sea ejecutada. Ayuda a prevenir inyecciones SQL eliminando la necesidad de entrecomillar manualmente los parámetros.

		//primero se verifica si la matricula existe, con la consulta siguiente

		$ex = Conexion::conectar()->prepare("SELECT COUNT(*) FROM CARRERAS WHERE nombre = :nombre");
		$ex->bindParam(':nombre', $datosModel['nombre'], PDO::PARAM_STR);
		$ex->execute();
		$ex = $ex->fetchColumn();

		if($ex == 0){

			$stmt = Conexion::conectar()->prepare("INSERT INTO CARRERAS (nombre) VALUES (:nombre)");	

			#bindParam() Vincula una variable de PHP a un parámetro de sustitución con nombre o de signo de interrogación correspondiente de la sentencia SQL que fue usada para preparar la sentencia.
			$stmt->bindParam(":nombre", $datosModel["nombre"], PDO::PARAM_STR);

			if($stmt->execute()){
				
				return "success";

			}

			else{

				return "error";

			}

			$stmt->close();
		}
		else{
			return "existe";
		}

	}

	#BORRAR MAESTRO
	#------------------------------------
	public function borrarCarreraModel($datosModel){

		//como el usuario que se desea eliminar esta ligado a la tabla de TUTORIAS como clave de referencia, 
		//primero se tendrá que eliminar el registro de la tabla de TUTORIAS que coincida con la matricula que se desea eliminar
		//y posteriormente se elimina el registro de la tabla original
		
		/*$alm = Conexion::conectar()->prepare("SELECT COUNT(*) FROM ALUMNOS WHERE tutor = :id");
		$alm->bindParam(':id', $datosModel, PDO::PARAM_INT);
		$alm->execute();
		$alm = $alm->fetchColumn();

		if($alm == 0){

			$stmt = Conexion::conectar()->prepare("DELETE FROM SESION_TUTORIA WHERE tutor = :id");
			$stmt->bindParam(':id', $datosModel, PDO::PARAM_INT);
			$stmt->execute();
		}*/

		$borra = Conexion::conectar()->prepare("DELETE FROM CARRERAS WHERE id = :id");
		$borra->bindParam(':id', $datosModel, PDO::PARAM_INT);
		$borra->execute();

		if($borra->execute()){

			return "success";

		}

		else{

			return "error";

		}
		//se cierra la conexion

		$borra->close();

	}

}
