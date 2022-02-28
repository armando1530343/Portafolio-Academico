<?php 

	#se llama al archivo donde se encuentra la clase de conexion
	include_once "conexion.php";

	/**
	 * 
	 */
	class CRUD extends Conexion
	{
		#MODELO DE VISTA DE LA TABLA DE PAGOS EN LA PAGINA PUBLICA
		
		#Verificacion de Ingreso de usuario al sistema
		public function ingresaUsuariosModel($username, $password){
			#se verifican los datos
			$login = Conexion::conectar()->prepare(
				'SELECT tipo FROM Teacher WHERE username = :username and password = :password');
			$login->bindParam(':username', $username, PDO::PARAM_STR);
			$login->bindParam(':password', $password, PDO::PARAM_STR);

			//se ejecuta la consulta y si funciona, retornara el valor que devuelve (tipo), sino retorna un mensaje de error			
			if($login->execute())
				return $login->fetchColumn();
			else
				return 'error';
		}

		// MODELOS DE GESTION DE TEACHERS ---------------------------------------------

		public function vistaTeachersModel(){
			$teachers = Conexion::conectar()->prepare(
				'SELECT * FROM Teacher WHERE tipo = 2');
			$teachers->execute();

			return $teachers->fetchAll();
		}

		public function registroTeacherModel($datos){
			$user = Conexion::conectar()->prepare(
				'SELECT COUNT(*) FROM Teacher WHERE username = :username');
			$user->bindParam(':username', $datos['username'], PDO::PARAM_STR);
			$user->execute();

			if($user->fetchColumn() == 0){
				$nuevo = Conexion::conectar()->prepare(
				'INSERT INTO Teacher(nombre_completo, username, password, tipo) VALUES(:nombre, :username, :password, 2)');
				$nuevo->bindParam(':nombre', $datos['nombre'], PDO::PARAM_STR);
				$nuevo->bindParam(':username', $datos['username'], PDO::PARAM_STR);
				$nuevo->bindParam(':password', $datos['password'], PDO::PARAM_STR);
				if($nuevo->execute())
					return 'success';
				else
					return 'error';
			}
			else
				return 'existe';
		}

		public function getTeacherModel($id_teacher){
			$teacher = Conexion::conectar()->prepare(
				'SELECT * FROM Teacher WHERE id_teacher = :id_teacher');
			$teacher->bindParam(':id_teacher', $id_teacher, PDO::PARAM_INT);
			$teacher->execute();

			return $teacher->fetchAll();
		}

		public function getUserTeacherModel($username){
			$teacher = Conexion::conectar()->prepare(
				'SELECT * FROM Teacher WHERE username = :username');
			$teacher->bindParam(':username', $username, PDO::PARAM_STR);
			$teacher->execute();

			return $teacher->fetchAll();
		}
		public function getTeacherNameModel($grupo){
			$teacherName = Conexion::conectar()->prepare(
				'SELECT t.nombre_completo as teacher 
				FROM Grupo as g INNER JOIN Teacher as t on g.id_teacher = t.id_teacher
				WHERE g.nombre = :grupo');
			$teacherName->bindParam(':grupo', $grupo, PDO::PARAM_INT);
			$teacherName->execute();

			return $teacherName->fetchAll();
		}

		public function actualizarTeacherModel($datos, $username_){
			$user = Conexion::conectar()->prepare(
				'SELECT COUNT(*) FROM Teacher WHERE username = :username');
			$user->bindParam(':username', $datos['username'], PDO::PARAM_STR);
			$user->execute();

			if($user->fetchColumn() == 0 || $datos['username'] == $username_){
				$update = Conexion::conectar()->prepare(
				'UPDATE Teacher SET nombre_completo = :nombre, username = :username, password = :password WHERE id_teacher = :id_teacher');
				$update->bindParam(':nombre', $datos['nombre'], PDO::PARAM_STR);
				$update->bindParam(':username', $datos['username'], PDO::PARAM_STR);
				$update->bindParam(':password', $datos['password'], PDO::PARAM_STR);
				$update->bindParam(':id_teacher', $datos['id'], PDO::PARAM_INT);
				if($update->execute())
					return 'actualizado';
				else
					return 'error';
			}
			else
				return 'existe';
		}

		public function eliminaTeacherModel($id_teacher){
			$delete = Conexion::conectar()->prepare(
				'DELETE FROM Teacher WHERE id_teacher = :id_teacher');
			$delete->bindParam(':id_teacher', $id_teacher, PDO::PARAM_INT);
			if($delete->execute())
				return 'borrado';
			else
				return 'incorrecto';
		}
		// ----------------------------------------------------------------------------
		// MODELOS DE GESTION DE GRUPOS ---------------------------------------------

		public function vistaGruposModel(){
			$grupos = Conexion::conectar()->prepare(
				'SELECT g.id_grupo as id_grupo, 
					    g.id_nivel as nivel,
				        t.nombre_completo as teacher,
				        g.nombre as grupo,
				        (SELECT COUNT(*) FROM Unidades WHERE id_grupo = g.id_grupo) as unidades
				FROM Grupo as g
				INNER JOIN Teacher as t on g.id_teacher = t.id_teacher');
			$grupos->execute();

			return $grupos->fetchAll();
		}
		public function vistaGruposTeacherModel($username){
			$grupos = Conexion::conectar()->prepare(
				'SELECT g.id_grupo as id_grupo, 
					    g.id_nivel as nivel,
				        t.nombre_completo as teacher,
				        g.nombre as grupo,
				        (SELECT COUNT(*) FROM Unidades WHERE id_grupo = g.id_grupo) as unidades
				FROM Grupo as g
				INNER JOIN Teacher as t on g.id_teacher = t.id_teacher
				WHERE t.username = :username');
			$grupos->bindParam(':username', $username, PDO::PARAM_STR);
			$grupos->execute();

			return $grupos->fetchAll();
		}

		public function getNivelModel(){
			$nivel = Conexion::conectar()->prepare('SELECT id_nivel FROM Nivel');
			$nivel->execute();
			return $nivel->fetchAll();
		}

		public function registroGrupoModel($datos){
			$cantidad = Conexion::conectar()->prepare(
				'SELECT COUNT(*) FROM Grupo WHERE id_nivel = :id_nivel');
			$cantidad->bindParam(':id_nivel', $datos['nivel'], PDO::PARAM_INT);
			$cantidad->execute();
			$cantidad = $cantidad->fetchColumn();
			//echo '<script>alert("'.$cantidad.'");</script>';
			$nombre_grupo = $datos['nivel'].'-'.($cantidad + 1);

			$teacher = Conexion::conectar()->prepare(
				'SELECT max(id_teacher) FROM Teacher WHERE nombre_completo = :nombre_completo');
			$teacher->bindParam(':nombre_completo', $datos['teacher'], PDO::PARAM_STR);
			$teacher->execute();
			$teacher = $teacher->fetchColumn();

			$nuevo = Conexion::conectar()->prepare(
				'INSERT INTO Grupo(id_nivel, id_teacher, nombre) VALUES(:id_nivel, :id_teacher, :nombre)');
			$nuevo->bindParam(':id_nivel', $datos['nivel'], PDO::PARAM_INT);
			$nuevo->bindParam(':id_teacher', $teacher, PDO::PARAM_INT);
			$nuevo->bindParam(':nombre', $nombre_grupo, PDO::PARAM_STR);
			//$nuevo->bindParam(':numero_unidades', $datos['unidades'], PDO::PARAM_INT);
			//$nuevo->bindParam(':horas_unidad', $datos['horas'], PDO::PARAM_INT);
			if($nuevo->execute())
				return 'success';
			else
				return 'error';
		}

		public function getGrupoModel($id_grupo){
			$grupo = Conexion::conectar()->prepare(
				'SELECT g.id_grupo as id_grupo, 
					    g.id_nivel as nivel,
				        t.nombre_completo as teacher,
				        g.nombre as grupo,
				        (SELECT COUNT(*) FROM Unidades WHERE id_grupo = g.id_grupo) as unidades
				FROM Grupo as g
				INNER JOIN Teacher as t on g.id_teacher = t.id_teacher WHERE g.id_grupo = :id_grupo');
			$grupo->bindParam(':id_grupo', $id_grupo, PDO::PARAM_INT);
			$grupo->execute();

			return $grupo->fetchAll();
		}

		public function getGruposModel($id_nivel){
			$grupo = Conexion::conectar()->prepare(
				'SELECT g.id_grupo as id_grupo, 
					    g.id_nivel as nivel,
				        t.nombre_completo as teacher,
				        g.nombre as grupo,
				        g.numero_unidades as unidades,
				        g.horas_unidad horas_unidad
				FROM Grupo as g
				INNER JOIN Teacher as t on g.id_teacher = t.id_teacher WHERE g.id_nivel = :id_nivel');
			$grupo->bindParam(':id_nivel', $id_nivel, PDO::PARAM_INT);
			$grupo->execute();

			return $grupo->fetchAll();
		}

		public function actualizarGrupoModel($datos){
			$teacher = Conexion::conectar()->prepare(
				'SELECT max(id_teacher) FROM Teacher WHERE nombre_completo = :nombre_completo');
			$teacher->bindParam(':nombre_completo', $datos['teacher'], PDO::PARAM_STR);
			$teacher->execute();
			$teacher = $teacher->fetchColumn();
			//echo '<script>alert("'.$teacher.'");</script>';

			$update = Conexion::conectar()->prepare(
				'UPDATE Grupo SET id_teacher = :id_teacher, numero_unidades = :numero_unidades, horas_unidad = :horas_unidad WHERE id_grupo = :id_grupo');
			$update->bindParam(':id_teacher', $teacher, PDO::PARAM_INT);
			$update->bindParam(':numero_unidades', $datos['unidades'], PDO::PARAM_INT);
			$update->bindParam(':horas_unidad', $datos['horas'], PDO::PARAM_INT);
			$update->bindParam(':id_grupo', $datos['id'], PDO::PARAM_INT);
			if($update->execute())
				return 'actualizado';
			else
				return 'error';
		}

		public function eliminaGrupoModel($id_grupo){
			
			$nivel = Conexion::conectar()->prepare('SELECT id_nivel FROM Grupo WHERE id_grupo = :id_grupo');
			$nivel->bindParam(':id_grupo', $id_grupo, PDO::PARAM_INT);
			$nivel->execute();
			$nivel = $nivel->fetchColumn();

			$unidad = Conexion::conectar()->prepare(
				'DELETE FROM Unidades WHERE id_grupo = :id_grupo');
			$unidad->bindParam(':id_grupo', $id_grupo, PDO::PARAM_INT);
			$unidad->execute();


			$delete = Conexion::conectar()->prepare(
				'DELETE FROM Grupo WHERE id_grupo = :id_grupo');
			$delete->bindParam(':id_grupo', $id_grupo, PDO::PARAM_INT);			
			
			if ($delete->execute()){

				
				//echo '<script>alert("'.$nivel.'");</script>';

				$grupos = Conexion::conectar()->prepare('SELECT * FROM Grupo WHERE id_nivel = :id_nivel');
				$grupos->bindParam(':id_nivel', $nivel, PDO::PARAM_INT);
				$grupos->execute();
				$grupos = $grupos->fetchAll();

				$cont = 1;
				foreach ($grupos as $key => $value) {
					$nombre = $value['id_nivel'].'-'.$cont;
					echo '<script>alert("'.$nombre.'");</script>';
					$update = Conexion::conectar()->prepare('UPDATE Grupo SET nombre = :nombre WHERE id_grupo = :id_grupo');
					$update->bindParam(':nombre', $nombre, PDO::PARAM_STR);
					$update->bindParam(':id_grupo', $value['id_grupo'], PDO::PARAM_INT);
					$update->execute();
					$cont++;
				}
				return 'borrado';
			}
			else
				return 'incorrecto';
		}

		public function getUnidadesMatriculaModel($matricula, $fecha){
			$unidades = Conexion::conectar()->prepare(
				'SELECT a.matricula as matricula,
				       a.nombre_completo as alumno,
				       t.nombre_completo as teacher,
				       g.nombre as grupo,
				       u.unidad as unidad
				FROM Alumnos as a 
				INNER JOIN Grupo as g on a.id_grupo = g.id_grupo
				INNER JOIN Teacher as t on g.id_teacher = t.id_teacher 
				INNER JOIN Unidades as u on g.id_grupo = u.id_grupo 
				WHERE a.matricula = :matricula  and u.fecha_inicio <= :fecha and u.fecha_fin >= :fecha');

			$unidades->bindParam(':matricula', $matricula, PDO::PARAM_INT);
			$unidades->bindParam(':fecha', $fecha, PDO::PARAM_STR);
			$unidades->execute();
			if($unidades->rowCount() > 0)
				return $unidades->fetchAll();
			else
				return "error";
		}
		public function getUnidadesNombreModel($alumno, $fecha){
			$unidades = Conexion::conectar()->prepare(
				'SELECT a.matricula as matricula,
				       a.nombre_completo as alumno,
				       t.nombre_completo as teacher,
				       g.nombre as grupo,
				       u.unidad as unidad
				FROM Alumnos as a 
				INNER JOIN Grupo as g on a.id_grupo = g.id_grupo
				INNER JOIN Teacher as t on g.id_teacher = t.id_teacher 
				INNER JOIN Unidades as u on g.id_grupo = u.id_grupo 
				WHERE a.nombre_completo = :alumno  and u.fecha_inicio >= :fecha and u.fecha_fin >= :fecha');

			$unidades->bindParam(':alumno', $alumno, PDO::PARAM_STR);
			$unidades->bindParam(':fecha', $fecha, PDO::PARAM_STR);
			$unidades->execute();
			if($unidades->rowCount() > 0)
				return $unidades->fetchAll();
			else
				return "error";
		}
		// MODELOS DE GESTION DE UNIDADES ---------------------------------------------

		public function vistaUnidadesModel($id_grupo){
			$unidad = Conexion::conectar()->prepare(
				'SELECT * FROM Unidades WHERE id_grupo = :id_grupo');
			$unidad->bindParam(':id_grupo', $id_grupo, PDO::PARAM_INT);
			$unidad->execute();
			return $unidad;
		}

		public function registroUnidadModel($datos){
			$unidad = Conexion::conectar()->prepare(
				'SELECT COUNT(*) FROM Unidades WHERE id_grupo = :id_grupo');
			$unidad->bindParam(':id_grupo', $datos['id_grupo'], PDO::PARAM_INT);
			$unidad->execute();
			$unidad = $unidad->fetchColumn() + 1;

			$nuevo = Conexion::conectar()->prepare(
				"INSERT INTO Unidades (unidad, fecha_inicio, fecha_fin, horas, id_grupo) VALUES (:unidad, :fecha_inicio, :fecha_fin, :horas, :id_grupo)");
			$nuevo->bindParam(":unidad", $unidad, PDO::PARAM_INT);
			$nuevo->bindParam(":fecha_inicio", $datos['inicio'], PDO::PARAM_STR);
			$nuevo->bindParam(":fecha_fin", $datos['fin'], PDO::PARAM_STR);
			$nuevo->bindParam(":horas", $datos['horas'], PDO::PARAM_INT);
			$nuevo->bindParam(":id_grupo", $datos['id_grupo'], PDO::PARAM_INT);
			
			if($nuevo->execute())
				return "success";
			else
				return "error";
		}

		public function getUnidadModel($id_unidad){
			$actividad = Conexion::conectar()->prepare(
				'SELECT * FROM Unidades WHERE id_unidad = :id_unidad');
			$actividad->bindParam(':id_unidad', $id_unidad, PDO::PARAM_INT);
			$actividad->execute();

			return $actividad->fetchAll();
		}

		public function actualizarUnidadModel($datos){
			$update = Conexion::conectar()->prepare(
			'UPDATE Unidades SET fecha_inicio = :fecha_inicio, fecha_fin = :fecha_fin WHERE id_unidad = :id_unidad');
			$update->bindParam(':fecha_inicio', $datos['inicio'], PDO::PARAM_STR);
			$update->bindParam(':fecha_fin', $datos['fin'], PDO::PARAM_STR);
			$update->bindParam(':id_unidad', $datos['id'], PDO::PARAM_INT);
			
			if($update->execute())
				return 'actualizado';
			else
				return 'error';
		}

		public function eliminaUnidadModel($id_unidad){
			$delete = Conexion::conectar()->prepare(
				'DELETE FROM Unidades WHERE id_unidad = :id_unidad');
			$delete->bindParam(':id_unidad', $id_unidad, PDO::PARAM_INT);
			if($delete->execute())
				return 'borrado';
			else
				return 'incorrecto';
		}
		// ----------------------------------------------------------------------------
		// MODELOS DE GESTION DE ALUMNOS ---------------------------------------------

		public function vistaAlumnosModel($id_grupo, $horario){
			$alumnos = Conexion::conectar()->prepare(
				'SELECT a.matricula as matricula,
					   a.nombre_completo as nombre,
				       c.nombre as carrera,
				       (SELECT COUNT(*) FROM Visitas WHERE matricula = a.matricula and horario != :horario) as horas,
				       g.nombre as grupo
				FROM Alumnos as a
				INNER JOIN Carreras as c on a.id_carrera = c.id_carrera
				INNER JOIN Grupo as g on a.id_grupo = g.id_grupo 
				WHERE a.id_grupo = :id_grupo');
			$alumnos->bindParam(':id_grupo', $id_grupo, PDO::PARAM_INT);
			$alumnos->bindParam(':horario', $horario, PDO::PARAM_STR);
			$alumnos->execute();

			return $alumnos->fetchAll();
		}
		public function vistaHorasAlumnosModel($matricula, $horario){
			//echo '<script>alert("'.$horario.'");</script>';
			$horas = Conexion::conectar()->prepare(
				'SELECT v.horario as horario,
						a.nombre as actividad,
						v.unidad as unidad,
						v.hora_inicio as inicio
				FROM Visitas as v
				INNER JOIN Actividad as a on v.id_actividad = a.id_actividad
				WHERE v.matricula = :matricula and v.horario != :horario');
			$horas->bindParam(':matricula', $matricula, PDO::PARAM_INT);
			$horas->bindParam(':horario', $horario, PDO::PARAM_STR);
			$horas->execute();

			return $horas->fetchAll();
		}

		public function vistaAlumnosTeacherModel($id_grupo){
			$alumnos = Conexion::conectar()->prepare(
				'SELECT DISTINCT v.matricula as matricula,
					    a.nombre_completo as alumno,
				       c.nombre as carrera,
				       (SELECT COUNT(*) FROM Visitas WHERE matricula = a.matricula) as horas
				FROM Visitas as v
				INNER JOIN Alumnos as a on v.matricula = a.matricula
				INNER JOIN Carreras as c on a.id_carrera = c.id_carrera
				INNER JOIN Grupo as g on a.id_grupo = g.id_grupo WHERE a.id_grupo = :id_grupo');
			$alumnos->bindParam(':id_grupo', $id_grupo, PDO::PARAM_INT);
			$alumnos->execute();

			return $alumnos->fetchAll();
		}

		public function getUnidadesAlumnoModel($matricula, $unidad){
			$unidades = Conexion::conectar()->prepare(
				"SELECT COUNT(unidad) FROM Visitas WHERE matricula = :matricula and unidad = :unidad");
			$unidades->bindParam(':matricula', $matricula, PDO::PARAM_INT);
			$unidades->bindParam(':unidad', $unidad, PDO::PARAM_INT);
			$unidades->execute();
			return $unidades->fetchColumn();
		}

		public function getCarrerasModel(){
			$carreras = Conexion::conectar()->prepare('SELECT * FROM Carreras');
			$carreras->execute();
			return $carreras->fetchAll();
		}

		public function registroAlumnoModel($datos){
			//echo '<script>alert("'.$cantidad.'");</script>';

			$matriculas = Conexion::conectar()->prepare('SELECT COUNT(*) FROM Alumnos WHERE matricula = :matricula');
			$matriculas->bindParam(':matricula', $datos['matricula'], PDO::PARAM_INT);
			$matriculas->execute();

			if($matriculas->fetchColumn() == 0){
				$id_carrera = Conexion::conectar()->prepare(
				'SELECT id_carrera FROM Carreras WHERE nombre = :nombre');
				$id_carrera->bindParam(':nombre', $datos['carrera'], PDO::PARAM_STR);
				$id_carrera->execute();
				$id_carrera = $id_carrera->fetchColumn();

				$nuevo = Conexion::conectar()->prepare(
					'INSERT INTO Alumnos(matricula, nombre_completo, id_carrera, id_grupo) VALUES (:matricula, :nombre_completo, :id_carrera, :id_grupo)');
				$nuevo->bindParam(':matricula', $datos['matricula'], PDO::PARAM_INT);
				$nuevo->bindParam(':nombre_completo', $datos['nombre'], PDO::PARAM_STR);
				$nuevo->bindParam(':id_carrera', $id_carrera, PDO::PARAM_INT);
				$nuevo->bindParam(':id_grupo', $datos['grupo'], PDO::PARAM_INT);
				if($nuevo->execute())
					return 'success';
				else
					return 'error';
			}
			else
				return 'existe';		
			
		}

		public function getAlumnoModel($matricula, $id_grupo){
			$alumnos = Conexion::conectar()->prepare(
				'SELECT a.matricula as matricula,
					   a.nombre_completo as nombre,
				       c.nombre as carrera,
				       g.nombre as grupo
				FROM Alumnos as a
				INNER JOIN Carreras as c on a.id_carrera = c.id_carrera
				INNER JOIN Grupo as g on a.id_grupo = g.id_grupo WHERE a.id_grupo = :id_grupo and a.matricula = :matricula');
			$alumnos->bindParam(':matricula', $matricula, PDO::PARAM_INT);
			$alumnos->bindParam(':id_grupo', $id_grupo, PDO::PARAM_INT);
			$alumnos->execute();

			return $alumnos->fetchAll();
		}

		public function getAlumnosModel($grupo){
			$alumnos = Conexion::conectar()->prepare(
				'SELECT a.matricula as matricula,
					   a.nombre_completo as nombre,
				       c.nombre as carrera,
				       g.nombre as grupo
				FROM Alumnos as a
				INNER JOIN Carreras as c on a.id_carrera = c.id_carrera				
				INNER JOIN Grupo as g on a.id_grupo = g.id_grupo WHERE g.nombre = :grupo');
			$alumnos->bindParam(':grupo', $grupo, PDO::PARAM_STR);
			$alumnos->execute();

			return $alumnos->fetchAll();
		}

		public function actualizarAlumnoModel($datos){

			$carrera = Conexion::conectar()->prepare('SELECT max(id_carrera) FROM Carreras WHERE nombre = :nombre');
			$carrera->bindParam(':nombre', $datos['carrera'], PDO::PARAM_STR);
			$carrera->execute();
			$carrera = $carrera->fetchColumn();

			$grupo = Conexion::conectar()->prepare('SELECT max(id_grupo) FROM Grupo WHERE nombre = :nombre');
			$grupo->bindParam(':nombre', $datos['grupo'], PDO::PARAM_STR);
			$grupo->execute();
			$grupo = $grupo->fetchColumn();
			
			$update = Conexion::conectar()->prepare(
				'UPDATE Alumnos SET nombre_completo = :nombre_completo, id_carrera = :id_carrera, id_grupo = :id_grupo WHERE matricula = :matricula');
			$update->bindParam(':nombre_completo', $datos['nombre'], PDO::PARAM_STR);
			$update->bindParam(':id_carrera', $carrera, PDO::PARAM_INT);
			$update->bindParam(':id_grupo', $grupo, PDO::PARAM_INT);
			$update->bindParam(':matricula', $datos['matricula'], PDO::PARAM_INT);
			if($update->execute())
				return 'actualizado';
			else
				return 'error';
		}

		public function eliminaAlumnoModel($matricula){
			$delete = Conexion::conectar()->prepare(
				'DELETE FROM Visitas WHERE matricula = :matricula');
			$delete->bindParam(':matricula', $matricula, PDO::PARAM_INT);
			$delete->execute();

			$delete = Conexion::conectar()->prepare(
				'DELETE FROM Alumnos WHERE matricula = :matricula');
			$delete->bindParam(':matricula', $matricula, PDO::PARAM_INT);
			$delete->execute();
		}
		public function getMatriculas(){
			$matriculas = Conexion::conectar()->prepare('SELECT matricula, nombre_completo FROM Alumnos');
			$matriculas->execute();
			return $matriculas->fetchAll();
		}
		
		//---------------------------------------------------------------------------
		// MODELOS DE GESTION DE ACTIVIDADES ---------------------------------------------

		public function vistaActividadesModel(){
			$actividad = Conexion::conectar()->prepare(
				'SELECT * FROM Actividad');
			$actividad->execute();

			return $actividad->fetchAll();
		}

		public function registroActividadModel($datos){
			$cantidad = Conexion::conectar()->prepare(
				'SELECT COUNT(*) FROM Actividad WHERE nombre = :nombre');
			$cantidad->bindParam(':nombre', $datos['nombre'], PDO::PARAM_STR);
			$cantidad->execute();

			if($cantidad->fetchColumn() == 0){
				$nuevo = Conexion::conectar()->prepare(
				'INSERT INTO Actividad(nombre) VALUES(:nombre)');
				$nuevo->bindParam(':nombre', $datos['nombre'], PDO::PARAM_STR);
				
				if($nuevo->execute())
					return 'success';
				else
					return 'error';
			}
			else
				return 'existe';
		}

		public function getActividadModel($id_actividad){
			$actividad = Conexion::conectar()->prepare(
				'SELECT * FROM Actividad WHERE id_actividad = :id_actividad');
			$actividad->bindParam(':id_actividad', $id_actividad, PDO::PARAM_INT);
			$actividad->execute();

			return $actividad->fetchAll();
		}

		public function actualizarActividadModel($datos, $actividad_){
			$cantidad = Conexion::conectar()->prepare(
				'SELECT COUNT(*) FROM Actividad WHERE nombre = :nombre');
			$cantidad->bindParam(':nombre', $datos['nombre'], PDO::PARAM_STR);
			$cantidad->execute();

			if($cantidad->fetchColumn() == 0 || $datos['nombre'] == $actividad_){
				$update = Conexion::conectar()->prepare(
				'UPDATE Actividad SET nombre = :nombre WHERE id_actividad = :id_actividad');
				$update->bindParam(':nombre', $datos['nombre'], PDO::PARAM_STR);
				$update->bindParam(':id_actividad', $datos['id'], PDO::PARAM_INT);
				
				if($update->execute())
					return 'actualizado';
				else
					return 'error';
			}
			else
				return 'existe';
		}

		public function eliminaActividadModel($id_actividad){
			$delete = Conexion::conectar()->prepare(
				'DELETE FROM Actividad WHERE id_actividad = :id_actividad');
			$delete->bindParam(':id_actividad', $id_actividad, PDO::PARAM_INT);
			if($delete->execute())
				return 'borrado';
			else
				return 'incorrecto';
		}
		// ----------------------------------------------------------------------------
		// MODELOS DE GESTION DE VISITAS ---------------------------------------------

		public function vistaVisitasModel($horario){
			$visitas = Conexion::conectar()->prepare(
				'SELECT a.nombre_completo as alumno,
				       t.nombre_completo as teacher,
					   g.nombre as grupo,
					   v.unidad as unidad,
				       ac.nombre as actividad,
				       v.id_registro as id_visita
				FROM Visitas as v
				INNER JOIN Alumnos as a on v.matricula = a.matricula
                INNER JOIN Grupo as g on a.id_grupo = g.id_grupo
				INNER JOIN Actividad as ac on v.id_actividad = ac.id_actividad
				INNER JOIN Teacher as t on g.id_teacher = t.id_teacher WHERE v.horario = :horario
				ORDER BY v.id_registro DESC');
			$visitas->bindParam(':horario', $horario, PDO::PARAM_STR);
			$visitas->execute();

			return $visitas->fetchAll();
		}

		public function registroVisitasModel($datos){

			$actividad = Conexion::conectar()->prepare(
				'SELECT id_actividad FROM Actividad WHERE nombre = :nombre');
			$actividad->bindParam(':nombre', $datos['actividad'], PDO::PARAM_STR);
			$actividad->execute();
			$actividad = $actividad->fetchColumn();

			//echo '<script>alert("'.$datos['horario'].'");</script>';

			/*$unidad = Conexion::conectar()->prepare(
				'SELECT unidad ')*/

			$nuevo = Conexion::conectar()->prepare(
			'INSERT INTO Visitas (hora_inicio, matricula, id_actividad, unidad, horario, asistencia) VALUES (:hora_inicio, :matricula, :id_actividad, :unidad, :horario, 0)');
			$nuevo->bindParam(':hora_inicio', $datos['hora_inicio'], PDO::PARAM_STR);
			$nuevo->bindParam(':matricula', $datos['matricula'], PDO::PARAM_INT);
			$nuevo->bindParam(':id_actividad', $actividad, PDO::PARAM_INT);
			$nuevo->bindParam(':unidad', $datos['unidad'], PDO::PARAM_INT);
			$nuevo->bindParam(':horario', $datos['horario'], PDO::PARAM_STR);
			
			if($nuevo->execute())
				return 'success';
			else
				return 'error';
			
		}
		public function eliminaVisitaModel($id_visita){
			$delete = Conexion::conectar()->prepare(
				'DELETE FROM Visitas WHERE id_registro = :id_registro');
			$delete->bindParam(':id_registro', $id_visita, PDO::PARAM_INT);
			$delete->execute();
		}

		public function vistaHistorialModel($horario){
			$historial = Conexion::conectar()->prepare(
				'SELECT v.id_registro as id_visita,
					    v.hora_inicio as entrada,
					    a.nombre_completo as alumno,
				        t.nombre_completo as teacher,
					    g.nombre as grupo,
				        ac.nombre as actividad,
				        v.unidad as unidad,
				        v.horario as horario
				FROM Visitas as v
				INNER JOIN Alumnos as a on v.matricula = a.matricula
				INNER JOIN Grupo as g on a.id_grupo = g.id_grupo
				INNER JOIN Actividad as ac on v.id_actividad = ac.id_actividad
				INNER JOIN Teacher as t on g.id_teacher = t.id_teacher WHERE v.horario != :horario
				ORDER BY v.id_registro DESC');
			$historial->bindParam(':horario', $horario, PDO::PARAM_STR);
			$historial->execute();

			return $historial->fetchAll();
		}
		// ----------------------------------------------------------------------------		
	}
?>