<?php

#EXTENSIÓN DE CLASES: Los objetos pueden ser extendidos, y pueden heredar propiedades y métodos. Para definir una clase como extensión, debo definir una clase padre, y se utiliza dentro de una clase hija.

require_once "conexion.php";

//heredar la clase conexion de conexion.php para poder utilizar "Conexion" del archivo conexion.php.
// Se extiende cuando se requiere manipuar una funcion, en este caso se va a  manipular la función "conectar" del models/conexion.php:
class Alumnos extends Conexion{

	//SE OBTIENEN LOS TUTORES
	function getAlumnosModel(){
		$stmt = Conexion::conectar()->prepare("SELECT nombre FROM ALUMNOS");
		$stmt->execute();
		return $stmt->fetchAll();
	}

	#REGISTRO DE USUARIOS
	#-------------------------------------
	public function registroAlumnoModel($datosModel){

		#prepare() Prepara una sentencia SQL para ser ejecutada por el método PDOStatement::execute(). La sentencia SQL puede contener cero o más marcadores de parámetros con nombre (:name) o signos de interrogación (?) por los cuales los valores reales serán sustituidos cuando la sentencia sea ejecutada. Ayuda a prevenir inyecciones SQL eliminando la necesidad de entrecomillar manualmente los parámetros.

		//primero se verifica si la matricula existe, con la consulta siguiente

		$ex = Conexion::conectar()->prepare("SELECT COUNT(*) FROM ALUMNOS WHERE matricula = :matricula");
		$ex->bindParam(':matricula', $datosModel['matricula'], PDO::PARAM_INT);
		$ex->execute();
		$ex = $ex->fetchColumn();

		if($ex == 0){
			//si el numero de filas devueltas es de cero entonces se agrega el nuevo registro

			//se obtiene el id de la carrera segun la eleccion
			$nombre_carrera = Conexion::conectar()->prepare("SELECT id FROM CARRERAS WHERE nombre = :nombre_carrera");
			$nombre_carrera->bindParam(':nombre_carrera', $datosModel['carrera']);
			$nombre_carrera->execute();
			$nombre_carrera = $nombre_carrera->fetchColumn();
			//se obtiene el id de la maestro segun la eleccion
			$nombre_tutor = Conexion::conectar()->prepare("SELECT id FROM MAESTROS WHERE nombre = :nombre_tutor");
			$nombre_tutor->bindParam(':nombre_tutor', $datosModel['tutor']);
			$nombre_tutor->execute();
			$nombre_tutor = $nombre_tutor->fetchColumn();


			$stmt = Conexion::conectar()->prepare("INSERT INTO ALUMNOS (matricula, nombre, carrera, tutor) VALUES (:matricula,:nombre,:carrera,:tutor)");	

			#bindParam() Vincula una variable de PHP a un parámetro de sustitución con nombre o de signo de interrogación correspondiente de la sentencia SQL que fue usada para preparar la sentencia.

			$stmt->bindParam(":matricula", $datosModel["matricula"], PDO::PARAM_INT);
			$stmt->bindParam(":nombre", $datosModel["nombre"], PDO::PARAM_STR);
			$stmt->bindParam(":carrera", $nombre_carrera, PDO::PARAM_INT);
			$stmt->bindParam(":tutor", $nombre_tutor, PDO::PARAM_INT);

			if($stmt->execute()){
				$stmt = Conexion::conectar()->prepare("INSERT INTO SESION_TUTORIA (alumno, tutor, fecha, hora, tipo, tutoria) VALUES (:alumno, :tutor, '2018-05-31', '12:00:00', 'TIPO', 'Turorias para el alumno')");	

				#bindParam() Vincula una variable de PHP a un parámetro de sustitución con nombre o de signo de interrogación correspondiente de la sentencia SQL que fue usada para preparar la sentencia.

				$stmt->bindParam(":alumno", $datosModel["matricula"], PDO::PARAM_INT);
				$stmt->bindParam(":tutor", $nombre_tutor, PDO::PARAM_INT);
				$stmt->execute();

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

	#VISTA TUTORIAS
	#-------------------------------------

	public function vistaAlumnosModel(){


		if($_SESSION['usuario']['nombre'] != "ADMINISTRADOR"){

			$id_usuario = $_SESSION['usuario']['id'];
			$stmt = Conexion::conectar()->prepare(
				"SELECT a.matricula as matricula, a.nombre as nombre, c.nombre as carrera, m.nombre as tutor
				FROM ALUMNOS as a 
				INNER JOIN CARRERAS as c ON a.carrera = c.id
				INNER JOIN MAESTROS as m ON a.tutor = m.id WHERE m.id = :id_tutor");
			$stmt->bindParam(':id_tutor',$id_usuario, PDO::PARAM_INT);
		}
		else if(isset($_GET['id'])){

			$id_alumno = $_GET['id'];


			$stmt = Conexion::conectar()->prepare(
				"SELECT a.matricula as matricula, a.nombre as nombre, c.nombre as carrera, m.nombre as tutor
				FROM ALUMNOS as a 
				INNER JOIN CARRERAS as c ON a.carrera = c.id
				INNER JOIN MAESTROS as m ON a.tutor = m.id WHERE a.matricula = :id_alumno");
			$stmt->bindParam('id_alumno', $id_alumno, PDO::PARAM_INT);
			

		}	
		else{
			$stmt = Conexion::conectar()->prepare(
				"SELECT a.matricula as matricula, a.nombre as nombre, c.nombre as carrera, m.nombre as tutor
				FROM ALUMNOS as a 
				INNER JOIN CARRERAS as c ON a.carrera = c.id
				INNER JOIN MAESTROS as m ON a.tutor = m.id");

		}
		$stmt->execute();

		#fetchAll(): Obtiene todas las filas de un conjunto de resultados asociado al objeto PDOStatement. 
		return $stmt->fetchAll();

		$stmt->close();
		

	}
	

	#EDITAR USUARIO
	#-------------------------------------

	public function editarAlumnoModel($datosModel){

		$stmt = Conexion::conectar()->prepare(
				"SELECT a.matricula as matricula, a.nombre as nombre, c.nombre as carrera, m.nombre as tutor
				FROM ALUMNOS as a 
				INNER JOIN CARRERAS as c ON a.carrera = c.id
				INNER JOIN MAESTROS as m ON a.tutor = m.id WHERE a.matricula = :id");
		$stmt->bindParam(":id", $datosModel, PDO::PARAM_INT);	
		$stmt->execute();

		return $stmt->fetchAll();

		$stmt->close();

	}

	#ACTUALIZAR USUARIO
	#-------------------------------------

	public function actualizarAlumnoModel($datosModel){

		//se obtiene el id de la tabla de carreras segun el nombre
		$nombre_carrera = Conexion::conectar()->prepare("SELECT id FROM CARRERAS WHERE nombre = :nombre_carrera");
		$nombre_carrera->bindParam(':nombre_carrera', $datosModel['carrera']);
		$nombre_carrera->execute();
		$nombre_carrera = $nombre_carrera->fetchColumn();
		//se obtiene el id de la tabla de maestros segun el nombre
		$nombre_tutor = Conexion::conectar()->prepare("SELECT id FROM MAESTROS WHERE nombre = :nombre_tutor");
		$nombre_tutor->bindParam(':nombre_tutor', $datosModel['tutor']);
		$nombre_tutor->execute();
		$nombre_tutor = $nombre_tutor->fetchColumn();

		//se hace la consulta para actualizar la tabla de alumnos
		$stmt = Conexion::conectar()->prepare("UPDATE ALUMNOS SET nombre = :nombre, carrera = :carrera, tutor = :tutor WHERE matricula = :matricula");

		$stmt->bindParam(":matricula", $datosModel["matricula"], PDO::PARAM_INT);
		$stmt->bindParam(":nombre", $datosModel["nombre"], PDO::PARAM_STR);
		$stmt->bindParam(":carrera", $nombre_carrera, PDO::PARAM_INT);
		$stmt->bindParam(":tutor", $nombre_tutor, PDO::PARAM_INT);

		if($stmt->execute()){
			//si se actualizan los datos de un alumno esto tambien debe afectar a la tabla de TUTORIAS y 
			//por eso se hace una sentencia para ello segun los datos modificados
			$stmt = Conexion::conectar()->prepare("UPDATE SESION_TUTORIA SET tutor = :tutor WHERE alumno = :matricula");
			$stmt->bindParam(":tutor", $nombre_tutor, PDO::PARAM_INT);
			$stmt->bindParam(":matricula", $datosModel["matricula"], PDO::PARAM_INT);
			$stmt->execute();

			return "success";

		}

		else{

			return "error";

		}

		$stmt->close();

	}

	#BORRAR ALUMNO
	#------------------------------------
	public function borrarAlumnoModel($datosModel){

		//como el usuario que se desea eliminar esta ligado a la tabla de TUTORIAS como clave de referencia, 
		//primero se tendrá que eliminar el registro de la tabla de TUTORIAS que coincida con la matricula que se desea eliminar
		//y posteriormente se elimina el registro de la tabla original
		
		$stmt = Conexion::conectar()->prepare("DELETE FROM SESION_TUTORIA WHERE alumno = :matricula");
		$stmt->bindParam(':matricula', $datosModel, PDO::PARAM_INT);
		$stmt->execute();

		$borra = Conexion::conectar()->prepare("DELETE FROM ALUMNOS WHERE matricula = :matricula");
		$borra->bindParam(':matricula', $datosModel, PDO::PARAM_INT);
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