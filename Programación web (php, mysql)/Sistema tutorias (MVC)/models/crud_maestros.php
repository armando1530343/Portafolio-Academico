<?php

#EXTENSIÓN DE CLASES: Los objetos pueden ser extendidos, y pueden heredar propiedades y métodos. Para definir una clase como extensión, debo definir una clase padre, y se utiliza dentro de una clase hija.

require_once "conexion.php";

//heredar la clase conexion de conexion.php para poder utilizar "Conexion" del archivo conexion.php.
// Se extiende cuando se requiere manipuar una funcion, en este caso se va a  manipular la función "conectar" del models/conexion.php:
class Maestros extends Conexion{

	
	//SE OBTIENEN LOS TUTORES
	function getTutoresModel(){
		$stmt = Conexion::conectar()->prepare("SELECT nombre FROM MAESTROS");
		$stmt->execute();
		return $stmt->fetchAll();
	}

	#VISTA MAESTROS
	#-------------------------------------

	public function vistaMaestrosModel(){


		if(isset($_GET['id'])){

			$id_maestro = $_GET['id'];


			$stmt = Conexion::conectar()->prepare(
				"SELECT m.id as id, c.nombre as carrera, m.nombre as nombre, m.email as email, m.password as password
				FROM MAESTROS as m 
				INNER JOIN CARRERAS as c ON m.carrera = c.id WHERE m.id = :id_maestro");
			$stmt->bindParam('id_maestro', $id_maestro, PDO::PARAM_INT);
			

		}	
		else{
			$stmt = Conexion::conectar()->prepare(
				"SELECT m.id as id, c.nombre as carrera, m.nombre as nombre, m.email as email, m.password as password
				FROM MAESTROS as m 
				INNER JOIN CARRERAS as c ON m.carrera = c.id");

		}
		$stmt->execute();

		#fetchAll(): Obtiene todas las filas de un conjunto de resultados asociado al objeto PDOStatement. 
		return $stmt->fetchAll();

		$stmt->close();
		

	}
	#ACTUALIZAR MAESTRO
	#-------------------------------------

	public function actualizarMaestroModel($datosModel){

		//se obtiene el id de la tabla de carreras segun el nombre
		$nombre_carrera = Conexion::conectar()->prepare("SELECT id FROM CARRERAS WHERE nombre = :nombre_carrera");
		$nombre_carrera->bindParam(':nombre_carrera', $datosModel['carrera']);
		$nombre_carrera->execute();
		$nombre_carrera = $nombre_carrera->fetchColumn();

		//se hace la consulta para actualizar la tabla de alumnos
		$stmt = Conexion::conectar()->prepare("UPDATE MAESTROS SET nombre = :nombre, carrera = :carrera, email = :email, password = :password WHERE id = :id");

		$stmt->bindParam(":id", $datosModel["id"], PDO::PARAM_INT);
		$stmt->bindParam(":nombre", $datosModel["nombre"], PDO::PARAM_STR);
		$stmt->bindParam(":carrera", $nombre_carrera, PDO::PARAM_INT);
		$stmt->bindParam(":email", $datosModel["email"], PDO::PARAM_STR);
		$stmt->bindParam(":password", $datosModel["password"], PDO::PARAM_STR);
		
		if($stmt->execute()){
			//si se actualizan los datos de un alumno esto tambien debe afectar a la tabla de TUTORIAS y 
			//por eso se hace una sentencia para ello segun los datos modificados
			/*$stmt = Conexion::conectar()->prepare("UPDATE SESION_TUTORIA SET tutor = :tutor WHERE alumno = :matricula");
			$stmt->bindParam(":tutor", $nombre_tutor, PDO::PARAM_INT);
			$stmt->bindParam(":matricula", $datosModel["matricula"], PDO::PARAM_INT);
			$stmt->execute();*/

			return "success";

		}

		else{

			return "error";

		}

		$stmt->close();

	}
	#REGISTRO DE MAESTROS
	#-------------------------------------
	public function registroMaestroModel($datosModel){

		#prepare() Prepara una sentencia SQL para ser ejecutada por el método PDOStatement::execute(). La sentencia SQL puede contener cero o más marcadores de parámetros con nombre (:name) o signos de interrogación (?) por los cuales los valores reales serán sustituidos cuando la sentencia sea ejecutada. Ayuda a prevenir inyecciones SQL eliminando la necesidad de entrecomillar manualmente los parámetros.

		//primero se verifica si la matricula existe, con la consulta siguiente

		$ex = Conexion::conectar()->prepare("SELECT COUNT(*) FROM MAESTROS WHERE email = :email");
		$ex->bindParam(':email', $datosModel['email'], PDO::PARAM_STR);
		$ex->execute();
		$ex = $ex->fetchColumn();

		if($ex == 0){
			//si el numero de filas devueltas es de cero entonces se agrega el nuevo registro

			//se obtiene el id de la carrera segun la eleccion
			$nombre_carrera = Conexion::conectar()->prepare("SELECT id FROM CARRERAS WHERE nombre = :nombre_carrera");
			$nombre_carrera->bindParam(':nombre_carrera', $datosModel['carrera']);
			$nombre_carrera->execute();
			$nombre_carrera = $nombre_carrera->fetchColumn();

			$stmt = Conexion::conectar()->prepare("INSERT INTO MAESTROS (carrera, nombre, email, password) VALUES (:carrera,:nombre,:email,:password)");	

			#bindParam() Vincula una variable de PHP a un parámetro de sustitución con nombre o de signo de interrogación correspondiente de la sentencia SQL que fue usada para preparar la sentencia.

			$stmt->bindParam(":carrera", $nombre_carrera, PDO::PARAM_INT);
			$stmt->bindParam(":nombre", $datosModel["nombre"], PDO::PARAM_STR);
			$stmt->bindParam(":email", $datosModel["email"], PDO::PARAM_STR);
			$stmt->bindParam(":password", $datosModel["password"], PDO::PARAM_STR);

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
	public function borrarMaestroModel($datosModel){

		//como el usuario que se desea eliminar esta ligado a la tabla de TUTORIAS como clave de referencia, 
		//primero se tendrá que eliminar el registro de la tabla de TUTORIAS que coincida con la matricula que se desea eliminar
		//y posteriormente se elimina el registro de la tabla original
		
		$alm = Conexion::conectar()->prepare("SELECT COUNT(*) FROM ALUMNOS WHERE tutor = :id");
		$alm->bindParam(':id', $datosModel, PDO::PARAM_INT);
		$alm->execute();
		$alm = $alm->fetchColumn();

		if($alm == 0){

			$stmt = Conexion::conectar()->prepare("DELETE FROM SESION_TUTORIA WHERE tutor = :id");
			$stmt->bindParam(':id', $datosModel, PDO::PARAM_INT);
			$stmt->execute();
		}

		$borra = Conexion::conectar()->prepare("DELETE FROM MAESTROS WHERE id = :id");
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

?>