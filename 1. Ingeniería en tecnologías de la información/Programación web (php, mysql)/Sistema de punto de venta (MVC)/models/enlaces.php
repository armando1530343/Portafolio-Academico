<?php 

class Paginas{
	
	public function enlacesPaginasModel($enlaces){


		/*muestra todos los posibles enlaces en los que navega la pagina*/

		if($enlaces == "ingresar" || $enlaces == "dashboard" || $enlaces == "dashboard_tiendas" || $enlaces == "productos" || $enlaces == "editar_producto" || $enlaces == "detalles_producto" ||  $enlaces == "salir" || $enlaces == 'borrar_producto' || $enlaces == "agregar_producto" || $enlaces == "agregar_usuario" || $enlaces == "usuarios" || $enlaces == "editar_usuario" || $enlaces == "cambiar_password" || $enlaces == "eliminar_usuario" || $enlaces == "categorias" || $enlaces == "editar_categoria" || $enlaces == "eliminar_categoria" || $enlaces == "agregar_categoria" || $enlaces == "sin_servicio" || $enlaces == "agregar_tienda" || $enlaces == "eliminar_tienda" || $enlaces == "perfil" || $enlaces == "ventas" || $enlaces == "agregar_venta" || $enlaces == "eliminar_venta" ){


			$module =  "views/modules/".$enlaces.".php";
		
		}

		else if($enlaces == "index"){

			$module =  "views/modules/ingresar.php";
		
		}

		else if($enlaces == "ok"){

			$module =  "views/modules/registro.php";
		
		}

		else if($enlaces == "fallo"){

			$module =  "views/modules/ingresar.php";
		
		}

		else if($enlaces == "cambio"){

			$module =  "views/modules/usuarios.php";
		
		}

		else{

			$module =  "views/modules/registro.php";

		}
		
		return $module;

	}

}

?>