<?php 

class Paginas{
	
	public function enlacesPaginasModel($enlaces){


		if($enlaces == "alumnos" || $enlaces == "sesion_tutorias" || $enlaces == "perfil_tutor" || $enlaces == "salir" ||
		   $enlaces == "maestros" || $enlaces == "alumno_editar" || $enlaces == "alumno_borrar" || $enlaces == "alumno_agregar" ||
		   $enlaces == "tutorias_borrar" || $enlaces == "tutorias_agregar" || $enlaces == "maestro_borrar" || 
		   $enlaces == "maestro_agregar" || $enlaces == "maestro_editar" || $enlaces == "carreras" || $enlaces == "carrera_agregar" ||
		   $enlaces == "carrera_editar" || $enlaces == "carrera_borrar"){

			$module =  "views/modules/".$enlaces.".php";
		
		}
		else if($enlaces == "ok"){

			$module =  "views/modules/registro.php";
		
		}

		else{

			$module =  "views/modules/ingresar.php";
		
		}/*

		else if($enlaces == "ok"){

			$module =  "views/modules/registro.php";
		
		}

		else if($enlaces == "fallo"){

			$module =  "views/modules/ingresar.php";
		
		}

		else if($enlaces == "cambio"){

			$module =  "views/modules/index.php";
		
		}

		else{

			$module =  "views/modules/registro.php";

		}*/
		
		return $module;

	}

}

?>