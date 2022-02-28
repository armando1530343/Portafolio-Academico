<?php

#EXTENSIÓN DE CLASES: Los objetos pueden ser extendidos, y pueden heredar propiedades y métodos. Para definir una clase como extensión, debo definir una clase padre, y se utiliza dentro de una clase hija.

require_once "conexion.php";

//heredar la clase conexion de conexion.php para poder utilizar "Conexion" del archivo conexion.php.
// Se extiende cuando se requiere manipuar una funcion, en este caso se va a  manipular la función "conectar" del models/conexion.php:
class Tutorias extends Conexion{

	#REGISTRO DE USUARIOS
	#-------------------------------------
	public function registroUsuarioModel($datosModel){

		#prepare() Prepara una sentencia SQL para ser ejecutada por el método PDOStatement::execute(). La sentencia SQL puede contener cero o más marcadores de parámetros con nombre (:name) o signos de interrogación (?) por los cuales los valores reales serán sustituidos cuando la sentencia sea ejecutada. Ayuda a prevenir inyecciones SQL eliminando la necesidad de entrecomillar manualmente los parámetros.
		/*$nombre_alumno = Conexion::conectar()->prepare("SELECT id FROM ALUMNOS WHERE nombre = :nombre_alumno");
		$nombre_alumno->bindParam(':nombre_alumno', $datosModel['alumno']);
		$nombre_alumno->execute();
		$nombre_alumno = $nombre_alumno->fetchColumn();

		$nombre_tutor = Conexion::conectar()->prepare("SELECT id FROM MAESTROS WHERE nombre = :nombre_tutor");
		$nombre_tutor->bindParam(':nombre_tutor', $datosModel['tutor']);
		$nombre_tutor->execute();
		$nombre_tutor = $nombre_tutor->fetchColumn();*/

		$stmt = Conexion::conectar()->prepare("INSERT INTO SESION_TUTORIA (alumno, tutor, fecha, hora, tipo, tutoria) VALUES (:alumno, :tutor, :fecha, :hora, :tipo, :tutoria)");	

		#bindParam() Vincula una variable de PHP a un parámetro de sustitución con nombre o de signo de interrogación correspondiente de la sentencia SQL que fue usada para preparar la sentencia.

		$stmt->bindParam(":alumno", $datosModel["alumno"], PDO::PARAM_INT);
		$stmt->bindParam(":tutor", $datosModel["tutor"], PDO::PARAM_INT);
		$stmt->bindParam(":fecha", $datosModel["fecha"]);
		$stmt->bindParam(":hora", $datosModel["hora"]);
		$stmt->bindParam(":tipo", $datosModel["tipo"], PDO::PARAM_STR);
		$stmt->bindParam(":tutoria", $datosModel["tutoria"], PDO::PARAM_STR);
		$stmt->execute();

	}

	#INGRESO USUARIO
	#-------------------------------------
	public function ingresoUsuarioModel($datosModel, $tabla){

		//datos de super-admin
		$super_admin = array('nombre' => 'admin','email' => 'admin', 'password' => 'admin' );

		if(!($datosModel["email"] == $super_admin['email'] && $datosModel["password"] == $super_admin['password'])){
			$stmt = Conexion::conectar()->prepare("SELECT * FROM $tabla WHERE email = :email");	
			$stmt->bindParam(":email", $datosModel["email"], PDO::PARAM_STR);
			$stmt->execute();

			#fetch(): Obtiene una fila de un conjunto de resultados asociado al objeto PDOStatement. 
			return $stmt->fetch();

			$stmt->close();
		}

		return $super_admin;

	}

	#VISTA TUTORIAS
	#-------------------------------------

	public function vistaTutoriasModel(){

		
		$stmt = Conexion::conectar()->prepare(
				"SELECT s.id as id, a.nombre as alumno, m.nombre as tutor, s.fecha as fecha, s.hora as hora, s.tipo as tipo, s.tutoria as tutoria
				 FROM SESION_TUTORIA as s
				 INNER JOIN ALUMNOS as a on s.alumno = a.matricula
				 INNER JOIN MAESTROS as m on s.tutor = m.id");	
		$stmt->execute();

		#fetchAll(): Obtiene todas las filas de un conjunto de resultados asociado al objeto PDOStatement. 
		return $stmt->fetchAll();

		$stmt->close();
		

	}
	/*

	#EDITAR USUARIO
	#-------------------------------------

	public function editarUsuarioModel($datosModel, $tabla){

		$stmt = Conexion::conectar()->prepare("SELECT id, usuario, password, email FROM $tabla WHERE id = :id");
		$stmt->bindParam(":id", $datosModel, PDO::PARAM_INT);	
		$stmt->execute();

		return $stmt->fetch();

		$stmt->close();

	}

	#ACTUALIZAR USUARIO
	#-------------------------------------

	public function actualizarUsuarioModel($datosModel, $tabla){

		$stmt = Conexion::conectar()->prepare("UPDATE $tabla SET usuario = :usuario, password = :password, email = :email WHERE id = :id");

		$stmt->bindParam(":usuario", $datosModel["usuario"], PDO::PARAM_STR);
		$stmt->bindParam(":password", $datosModel["password"], PDO::PARAM_STR);
		$stmt->bindParam(":email", $datosModel["email"], PDO::PARAM_STR);
		$stmt->bindParam(":id", $datosModel["id"], PDO::PARAM_INT);

		if($stmt->execute()){

			return "success";

		}

		else{

			return "error";

		}

		$stmt->close();

	}


	#BORRAR USUARIO
	#------------------------------------
	public function borrarUsuarioModel($datosModel, $tabla){

		$stmt = Conexion::conectar()->prepare("DELETE FROM $tabla WHERE id = :id");
		$stmt->bindParam(":id", $datosModel, PDO::PARAM_INT);

		if($stmt->execute()){

			return "success";

		}

		else{

			return "error";

		}

		$stmt->close();

	}*/

}




/*

#REGISTRO DE PRODUCTOS
	#-------------------------------------
	public function registroProductosModel($datosModel, $tabla){

		#prepare() Prepara una sentencia SQL para ser ejecutada por el método PDOStatement::execute(). La sentencia SQL puede contener cero o más marcadores de parámetros con nombre (:name) o signos de interrogación (?) por los cuales los valores reales serán sustituidos cuando la sentencia sea ejecutada. Ayuda a prevenir inyecciones SQL eliminando la necesidad de entrecomillar manualmente los parámetros.

		$stmt1 = Conexion::conectar()->prepare("INSERT INTO $tabla (nombreProd, descProduc, BuyPrice,SalePrice, Proce) VALUES (:nombreProd,:descProduc,:BuyPrice,:SalePrice,:Proce)");	

		#bindParam() Vincula una variable de PHP a un parámetro de sustitución con nombre o de signo de interrogación correspondiente de la sentencia SQL que fue usada para preparar la sentencia.

		$stmt1->bindParam(":nombreProd", $datosModel["nombreProd"], PDO::PARAM_STR);
		$stmt1->bindParam(":descProduc", $datosModel["descProduc"], PDO::PARAM_STR);
		$stmt1->bindParam(":BuyPrice", $datosModel["BuyPrice"], PDO::PARAM_STR);
		$stmt1->bindParam(":SalePrice", $datosModel["SalePrice"], PDO::PARAM_STR);
		$stmt1->bindParam(":Proce", $datosModel["Proce"], PDO::PARAM_STR);
		

		if($stmt1->execute()){

			return "success";

		}

		else{

			return "error";

		}

		$stmt1->close();

	}

*/

?>