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

		if(isset($_GET['action'])){
			$enlaces = $_GET['action'];
		}
		else{

			$enlaces = "index";
		}



		$respuesta = Paginas::enlacesPaginasModel($enlaces);
		include $respuesta;
	}

	public function ingresaUsuarioController(){

		if(isset($_POST['username'])){
			
			$datos = array('username' => $_POST['username'],
						   'password' => $_POST['password']);

			$respuesta = Datos::ingresoUsuarioModel($datos);

			if($respuesta['user_name'] == $_POST['username'] && $respuesta["user_password_hash"] == $_POST["password"]){
				/*$_SESSION['validar'] = true;
				$_SESSION['user'] = $respuesta['firstname'].' '.$respuesta['lastname'];
				$_SESSION['password'] = $respuesta['user_password_hash'];*/

				if($respuesta['user_name'] == 'admin'){
					$dash = 'dashboard_tiendas';
				}
				else{
					$dash = 'dashboard';
				}


				header('Location: index.php?action='.$dash.'&tienda='.$respuesta['id_tienda'].'&id_user='.$respuesta['user_id'].'&user='.$respuesta['user_name'].'&password='.$respuesta['user_password_hash'].'&validar=true');
				echo "<script>alert('entro');</script>";
				return $respuesta;
			}
			else{
				header('Location: index.php?action=fallo');
			}
		}

	}

	public function getTiendaController(){

		return Datos::getTiendaModel($_SESSION['id_tienda']);
	}

	public function dashboardStockController(){
		return Datos::dashboardStockModel($_SESSION['fecha'], $_SESSION['id_tienda']);
	}

	public function dashboardProductosController(){
		return Datos::dashboardProductosModel($_SESSION['id_tienda']);
	}

	public function dashboardUsuariosController(){
		return Datos::dashboardUsuariosModel($_SESSION['id_tienda']);
	}

	public function dashboardCategoriasController(){
		return Datos::dashboardCategoriasModel($_SESSION['id_tienda']);
	}

	public function estadoTiendaController(){
		if(isset($_GET['estado'])){
			if($_GET['estado'] == 'ACTIVA'){
				Datos::estadoTiendaModel($_GET['estado'], $_GET['id']);
			}
			else if($_GET['estado'] == 'DESACTIVA'){
				Datos::estadoTiendaModel($_GET['estado'], $_GET['id']);
			}
		}
	}

	public function agregarProductosController(){
		$categorias = Datos::getCategoriasModel($_SESSION['id_tienda']);

		echo '  <div class="card-body">
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="text" class="form-control" required name="codigo" placeholder="Codigo Producto">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="text" class="form-control" required name="nombre" placeholder="Nombre">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="date" class="form-control" required name="fecha" placeholder="Fecha">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="number" class="form-control" required name="precio" placeholder="Precio">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="number" class="form-control" required name="stock" placeholder="Stock Disponible">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <select type="text" class="form-control" name="categoria">';
	            foreach ($categorias as $key => $item) {
	            	echo '<option>'.$item['nombre'].'</option>';
	            }
	            echo '</select>
	            	</div>
	              </div>
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	              <button type="submit" class="btn btn-success">Agregar Producto</button>
	              <a href="index.php?action=productos" class="btn btn-default">Cancelar</a>
	            </div>';
	}
	public function agregarTiendaController(){
		$categorias = Datos::getCategoriasModel($_SESSION['id_tienda']);

		echo '  <div class="card-body">
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="text" class="form-control" required name="nombre" placeholder="Nombre">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <select type="text" class="form-control" name="estado">
	                  	<option>ACTIVA</option>
	                  	<option>DESACTIVA</option>
	                  </select>
	            	</div>
	              </div>
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	              <button type="submit" class="btn btn-success">Agregar Tienda</button>
	              <a href="index.php?action=dashboard_tiendas" class="btn btn-default">Cancelar</a>
	            </div>';
	}
	#REGISTRO DE TIENDAS
	#------------------------------------
	public function registroTiendaController(){
		if(isset($_POST["nombre"])){
			//Recibe a traves del método POST el name (html) de usuario, password y email, se almacenan los datos en una variable de tipo array con sus respectivas propiedades (usuario, password y email):

			$datosController = array( "nombre"=>strtoupper($_POST["nombre"]),
								      "estado"=>strtoupper($_POST["estado"]),
								  	  "fecha_add"=>$_SESSION["fecha"],
								  	  "fecha_mod"=>$_SESSION["fecha"],
								  	  "autor"=>$_SESSION['user']);

			//Se le dice al modelo models/crud.php (Datos::registroUsuarioModel),que en la clase "Datos", la funcion "registroUsuarioModel" reciba en sus 2 parametros los valores "$datosController" y el nombre de la tabla a conectarnos la cual es "usuarios":
			$respuesta = Datos::registroTiendaModel($datosController);

			echo '<script> window.location = "index.php?action=dashboard_tiendas&status='.$respuesta.'"; </script>';

		}

	}
	public function agregaHistorialController($mensaje){
		if($mensaje != 'existe' && $mensaje != 'error'){
			if(isset($_GET['action']) && isset($_POST['codigo'])){
				if($_GET['action'] == 'agregar_producto'){
					$last_id = Datos::getLastIdModel();

					$datos = array('id_producto' => $last_id,
									'id_user' => $_SESSION['id_user'],
									'fecha' => $_SESSION['fecha'].' '.$_SESSION['hora'],
									'descripcion' => $_SESSION['user'].' agregó '.$_POST['stock'].' producto(s) a la tienda',
									'referencia' => $_POST['codigo'],
									'cantidad' => $_POST['stock']);

					$respuesta = Datos::registroHistorialModel($datos);

					return $respuesta;

					//echo '<script> window.location = "index.php?action=productos&status='.$respuesta.'"; </script>';

				}
			}
		}
		return $mensaje;

	}

	public function agregarStockController(){
		echo '	<div class="card-body">
	              <div class="form-group">
	                  <input type="number" class="form-control" required name="cantidad" placeholder="Cantidad">		            
	              </div>
	              <div class="form-group">
	                  <input type="text" class="form-control" required name="referencia" placeholder="Referencia">
	              </div>
	            </div>
	            <div class="card-footer">
	              <button type="submit" class="btn btn-success">Agregar</button>
	              <a href="index.php?action=detalles_producto&id='.$_GET['id'].'&codigo='.$_GET['codigo'].'" class="btn btn-default">Cancelar</a>
	            </div>';

	}
	public function formEliminaStockController(){
		echo '	<div class="card-body">
	              <div class="form-group">
	                  <input type="number" class="form-control" required name="cantidad" placeholder="Cantidad">		            
	              </div>
	              <div class="form-group">
	                  <input type="text" class="form-control" required name="referencia" placeholder="Referencia">
	              </div>
	            </div>
	            <div class="card-footer">
	              <button type="submit" name="elimina_stock" class="btn btn-success">Eliminar</button>
	              <a href="index.php?action=detalles_producto&id='.$_GET['id'].'&codigo='.$_GET['codigo'].'" class="btn btn-default">Cancelar</a>
	            </div>';

	}
	public function registroStockController(){
		//$datos = Datos::vistaHistorialModel($_GET['id']);
		if(isset($_POST['cantidad'])){

			$datos = array('id_producto' => $_GET['id'],
							'id_user' => $_SESSION['id_user'],
							'fecha' => $_SESSION['fecha'].' '.$_SESSION['hora'],
							'descripcion' => $_SESSION['user'].' agregó '.$_POST['cantidad'].' producto(s) a la tienda',
							'referencia' => $_POST['referencia'],
							'cantidad' => $_POST['cantidad']);

			Datos::actualizaStockModel($_POST['cantidad'], $_GET['id']);

			$respuesta = Datos::registroHistorialModel($datos);

			echo '<script> window.location = "index.php?action=detalles_producto&id='.$_GET["id"].'&codigo='.$_GET["codigo"].'&agrega_stock='.$respuesta.'"; </script>';
		}

	}
	public function eliminaStockController(){
		//$datos = Datos::vistaHistorialModel($_GET['id']);
		if(isset($_POST['password'])){
			if($_POST['password'] == $_SESSION['password']){

				$datos = array('id_producto' => $_GET['id'],
								'id_user' => $_SESSION['id_user'],
								'fecha' => $_SESSION['fecha'].' '.$_SESSION['hora'],
								'descripcion' => $_SESSION['user'].' eliminó '.$_GET['cantidad'].' producto(s) de la tienda',
								'referencia' => $_GET['ref'],
								'cantidad' => $_GET['cantidad']);

				$respuesta = Datos::eliminaStockModel($_GET['cantidad'], $_GET['id']);
				if($respuesta == "success"){
					$respuesta2 = Datos::registroHistorialModel($datos);
				}

				echo '<script> window.location = "index.php?action=detalles_producto&id='.$_GET["id"].'&codigo='.$_GET["codigo"].'&elimina_stock='.$respuesta.'"; </script>';
			}
		}

	}
	public function confirmaEliminarController(){
		if(isset($_GET['confirm'])){
			if($_GET['confirm'] == 0){

				echo '	<div class="alert alert-warning alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  
		                  Contraseña Incorrecta.
		                </div>';
			}
		}
		echo '	<div class="card-body">
	              <div class="form-group">
	                  <input type="password" class="form-control" name="password" placeholder="Contraseña">		            
	              </div>
	            </div>
	            <div class="card-footer">
	              <button type="submit" class="btn btn-success">Aceptar</button>
	              <a href="index.php?action=detalles_producto&id='.$_GET['id'].'&codigo='.$_GET['codigo'].'" class="btn btn-default">Cancelar</a>
	            </div>';

	}
	public function borrarProductoController(){

		if(isset($_GET['id'])){
			if(isset($_POST['password'])){
				if($_POST['password'] == $_SESSION['password']){
					
					$respuesta = Datos::borrarProductoModel($_GET['id']);

					if($respuesta == 'success'){
						echo '<script> window.location = "index.php?action=productos&status=borrado"; </script>';
						
					}
					
				}
				else{
					echo '<script> window.location = "index.php?action=detalles_producto&id='.$_GET['id'].'&codigo='.$_GET['codigo'].'&form=elimina_producto&confirm=0";</script>';
				}
			}
			
			/*
			//}*/
		}
	}

	#REGISTRO DE USUARIOS
	#------------------------------------
	public function registroProductosController(){
		if(isset($_POST["codigo"])){
			//Recibe a traves del método POST el name (html) de usuario, password y email, se almacenan los datos en una variable de tipo array con sus respectivas propiedades (usuario, password y email):

			$datosController = array( "codigo"=>$_POST["codigo"], 
								      "nombre"=>strtoupper($_POST["nombre"]),
								      "fecha"=>strtoupper($_POST["fecha"]),
								  	  "precio"=>strtoupper($_POST["precio"]),
								  	  "stock"=>strtoupper($_POST["stock"]),
								  	  "categoria"=>strtoupper($_POST["categoria"]));

			//Se le dice al modelo models/crud.php (Datos::registroUsuarioModel),que en la clase "Datos", la funcion "registroUsuarioModel" reciba en sus 2 parametros los valores "$datosController" y el nombre de la tabla a conectarnos la cual es "usuarios":
			$respuesta = Datos::registroProductosModel($datosController, $_SESSION['id_tienda']);

			return $respuesta;

			//echo '<script> window.location = "index.php?action=productos&status='.$respuesta.'"; </script>';

		}

	}
	public function vistaVentasController(){
		$datos = Datos::vistaVentasModel($_SESSION['id_tienda']);

		foreach($datos as $row => $item){ 
			echo'<tr>
					<td>'.$item["id_venta"].'</td>					
					<td>'.$item["fecha"].'</td>
					<td>
					<table>
						<thead>
							<tr>
								<th>Codigo</th>
								<th>Descripcion</th>
								<th>Precio</th>
								<th>Cantidad</th>
							</tr>
						</thead>
						<tbody>';
						$productos = Datos::getProductosVentaModel($item['id_venta']);
						foreach ($productos as $key => $value) {
						
							echo '<tr>
									<td>'.$value['codigo'].'</td>
									<td>'.$value['nombre'].'</td>
									<td>'.$value['precio'].'</td>
									<td>'.$value['cantidad'].'</td>
								  </tr>';
						}
				  echo '</tbody>
					</table>
					<td>'.$item["total"].'</td>
					<td style="text-align: center;"><a href="index.php?action=eliminar_venta&id='.$item["id_venta"].'"><button class="btn btn-danger">Eliminar</button></a></td>';
		}
	}

	public function vistaProductosController(){
		$datos = Datos::vistaProductosModel($_SESSION['id_tienda']);

		foreach($datos as $row => $item){ 
			echo'<tr>
					<td>'.$item["id"].'</td>					
					<td>'.$item["codigo"].'</td>
					<td><img src="package.jpg" width="30">  '.$item["nombre"].'</td>
					<td>'.$item["precio"].'</td>
					<td style="text-align: center;"><a href="index.php?action=detalles_producto&id='.$item["id"].'&codigo='.$item["codigo"].'"><button class="btn btn-warning">Ver Detalles</button></a></td>';
		}
	}
	public function vistaUsuariosController(){
		$datos = Datos::vistaUsuariosModel($_SESSION['id_tienda']);

		foreach($datos as $row => $item){ 
			echo'<tr>
					<td>'.$item["id"].'</td>					
					<td>'.$item["nombre"].' '.$item['apellido'].'</td>
					<td>'.$item["usuario"].'</td>
					<td>'.$item["email"].'</td>
					<td>'.$item["agregado"].'</td>
					<td style="text-align: center;"><a href="index.php?action=editar_usuario&id='.$item["id"].'&usuario='.$item["usuario"].'&email='.$item["email"].'"><button class="btn btn-warning">Editar</button></a></td>
					<td style="text-align: center;"><a href="index.php?action=cambiar_password&id='.$item["id"].'"><button class="btn btn-info">Cambiar Contraseña</button></a></td>
					<td style="text-align: center;"><a href="index.php?action=eliminar_usuario&id='.$item["id"].'&session_id='.$_SESSION["id_user"].'"><button class="btn btn-danger">Eliminar</button></a></td>';

		}
	}
	public function vistaPerfilController(){
		$respuesta = Datos::vistaPerfilModel($_SESSION['id_user']);

		echo '  <div class="card-body">
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">ID:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" disabled name="id" placeholder="Id" value = "'.$respuesta[0]['user_id'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">NOMBRE:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" name="codigo" placeholder="Codigo Producto" value = "'.$respuesta[0]['firstname'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">APELLIDO:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" name="nombre" placeholder="Nombre" value = "'.$respuesta[0]['lastname'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">USUARIO:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" name="fecha" placeholder="Fecha" value = "'.$respuesta[0]['user_name'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">EMAIL:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" name="precio" placeholder="Precio" value = "'.$respuesta[0]['user_email'].'">
	                </div>
	              </div>
	            </div>';
	}
	public function vistaCategoriasController(){

		
		$datos = Datos::getCategoriasModel($_SESSION['id_tienda']);
	

		foreach($datos as $row => $item){ 
			echo'<tr>
					<td>'.$item["id"].'</td>					
					<td>'.$item["nombre"].'</td>
					<td>'.$item["descripcion"].'</td>
					<td>'.$item["agregado"].'</td>
					<td style="text-align: center;"><a href="index.php?action=editar_categoria&id='.$item["id"].'&nombre='.$item["nombre"].'"><button class="btn btn-warning">Editar</button></a></td>
					<td style="text-align: center;"><a href="index.php?action=eliminar_categoria&id='.$item["id"].'"><button class="btn btn-danger">Eliminar</button></a></td>';
		}
		
	}
	public function vistaHistorialController(){

		$datos = Datos::vistaHistorialModel($_GET['id']);

		foreach($datos as $row => $item){ 
			echo'<tr>
					<td>'.$item["fecha"].'</td>					
					<td>'.$item["hora"].'</td>
					<td>'.$item["descripcion"].'</td>
					<td>'.$item["referencia"].'</td>
					<td>'.$item["total"].'</td>';
		}
	}

	public function vistaTiendasController(){

		$datos = Datos::vistaTiendasModel();

		foreach($datos as $row => $item){ 
			echo'<tr>
					<td>'.$item["nombre"].'</td>					
					<td>'.$item["estado"].'</td>
					<td>'.$item["autor"].'</td>
					<td>'.$item["fecha_add"].'</td>
					<td>'.$item["fecha_mod"].'</td>
					<td style="text-align: center;"><a href="index.php?action=dashboard_tiendas&id='.$item["id_tienda"].'&estado=ACTIVA"><button class="btn btn-success">Activar</button></a></td>
					<td style="text-align: center;"><a href="index.php?action=dashboard_tiendas&id='.$item["id_tienda"].'&estado=DESACTIVA"><button class="btn btn-warning">Desactivar</button></a></td>
					<td style="text-align: center;"><a href="index.php?action=eliminar_tienda&id='.$item["id_tienda"].'&estado=eliminar"><button class="btn btn-danger">Eliminar</button></a></td>
					<td style="text-align: center;"><a href="index.php?action=dashboard&tienda='.$item["id_tienda"].'&estado=entrar"><button class="btn btn-info">Entrar</button></a></td>';
		}
	}
	public function detallesProductosController(){
		
		$respuesta = Datos::detallesProductosModel($_GET['id']);
		$categorias = Datos::getCategoriasModel($_SESSION['id_tienda']);

		if(isset($_POST['editar'])){
			echo '<script> window.location = "index.php?action=editar_producto&id='.$_GET['id'].'&codigo='.$_GET['codigo'].'"; </script>';
		}
		if(isset($_POST['eliminar'])){
			echo '<script> window.location = "index.php?action=borrar_producto&id='.$_GET['id'].'"; </script>';
		}

		echo '  <div class="card-body">
	              <div class="form-group row">	              	
              		<div class="col-sm-2" align="right">
	                  <label class="control-label">ID:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" disabled name="id" placeholder="Id" value = "'.$respuesta[0]['id'].'">
	                </div>		            
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">CODIGO:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" name="codigo" disabled placeholder="Codigo Producto" value = "'.$respuesta[0]['codigo'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">NOMBRE:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" name="nombre" disabled placeholder="Nombre" value = "'.$respuesta[0]['nombre'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">FECHA:</label>
	                </div>
	                <div class="col-sm-10" align="left">
	                  <label class="control-label">'.$respuesta[0]['fecha'].'</label>
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">PRECIO:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="number" class="form-control" name="precio" disabled placeholder="Precio" value = "'.$respuesta[0]['precio'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">STOCK DISP.:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="number" class="form-control" name="stock" disabled placeholder="Stock Disponible" value = "'.$respuesta[0]['stock'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">CATEGORIA:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" name="categoria" disabled placeholder="Categoria" value = "'.$respuesta[0]['categoria'].'">
	                </div>
	              </div>
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	            		<button type="submit" name="editar" class="btn btn-warning" ';if(isset($_GET['form'])){echo 'disabled';} echo '>Editar</button>
	              		<a href="index.php?action=detalles_producto&id='.$_GET["id"].'&codigo='.$_GET["codigo"].'&form=elimina_producto" class="btn btn-danger" ';if(isset($_GET['form'])){echo 'style="display: none;"';} echo '>Eliminar</a>
	            </div>';
	        	
	}

	public function editarProductosController(){
		$respuesta = Datos::detallesProductosModel($_GET['id']);
		$categorias = Datos::getCategoriasModel($_SESSION['id_tienda']);
		echo '  <div class="card-body">
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">ID:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" disabled name="id" placeholder="Id" value = "'.$respuesta[0]['id'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">CODIGO:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" name="codigo" placeholder="Codigo Producto" value = "'.$respuesta[0]['codigo'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">NOMBRE:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" name="nombre" placeholder="Nombre" value = "'.$respuesta[0]['nombre'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">FECHA:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="date" class="form-control" name="fecha" placeholder="Fecha" value = "'.$respuesta[0]['fecha'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">PRECIO:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="number" class="form-control" name="precio" placeholder="Precio" value = "'.$respuesta[0]['precio'].'">
	                </div>
	              </div>	              
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">CATEGORIA:</label>
	                </div>
	                <div class="col-sm-10">
	                  <select type="text" class="form-control" name="categoria">';
	            foreach ($categorias as $key => $item) {
	            	echo '<option>'.$item['nombre'].'</option>';
	            }
	            echo '</select>
	                </div>
	              </div>
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">';
	            //if(!$_POST){
	    		  echo '<button name="guardar" class="btn btn-success">Guardar Cambios</button></a>
	    		  		<button name="cancelar" class="btn btn-info">Cancelar</button></a>
	            </div>';
	}

	public function actualizarProductoController(){

		if(isset($_POST['cancelar'])){
			echo '<script> window.location = "index.php?action=detalles_producto&id='.$_GET['id'].'&codigo='.$_GET['codigo'].'"; </script>';
		}
		else if(isset($_POST['codigo'])){
			
			$datosProd = array( "id"=>$_GET['id'],
								"codigo"=>$_POST["codigo"], 
						        "nombre"=>strtoupper($_POST["nombre"]),
						        "fecha"=>strtoupper($_POST["fecha"]),
						  	    "precio"=>strtoupper($_POST["precio"]),
						  	    "categoria"=>strtoupper($_POST["categoria"]));

			$respuesta = Datos::actualizarProductoModel($datosProd, $_GET['codigo']);

			echo '<script> window.location = "index.php?action=detalles_producto&id='.$_GET['id'].'&codigo='.$_GET['codigo'].'&modifica='.$respuesta.'"; </script>';
		}
	}
	public function editarUsuariosController(){
		$respuesta = Datos::detallesUsuariosModel($_GET['id']);
		echo '  <div class="card-body">
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">ID:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" disabled name="id" placeholder="Id" value = "'.$respuesta[0]['id'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">NOMBRE:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" name="nombre" placeholder="Codigo Producto" value = "'.$respuesta[0]['nombre'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">APELLIDO:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" name="apellido" placeholder="Nombre" value = "'.$respuesta[0]['apellido'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">USUARIO:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" name="usuario" placeholder="Fecha" value = "'.$respuesta[0]['usuario'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">EMAIL:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" name="email" placeholder="Precio" value = "'.$respuesta[0]['email'].'">
	                </div>
	              </div>
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	            	<button name="guardar" class="btn btn-success">Guardar Cambios</button></a>
	    		  	<a href="index.php?action=usuarios" class="btn btn-info">Cancelar</a>
	            </div>';
	}

	public function actualizarUsuarioController(){

		if(isset($_POST['nombre'])){
			
			$datosProd = array( "id"=>$_GET['id'],
								"nombre"=>strtoupper($_POST["nombre"]), 
						        "apellido"=>strtoupper($_POST["apellido"]),
						        "usuario"=>$_POST["usuario"],
						  	    "email"=>$_POST["email"]);

			$respuesta = Datos::actualizarUsuarioModel($datosProd, $_GET['usuario'], $_GET['email']);

			echo '<script> window.location = "index.php?action=usuarios&status='.$respuesta.'"; </script>';
		}
	}

	public function cambiarPasswordController(){
		if(isset($_POST['password'])){
			if($_POST['password'] == $_POST['repit_password']){
				$respuesta = Datos::cambiarPasswordModel($_GET['id'], $_POST['password']);
				if($_GET['id'] == $_SESSION['id_user']){
					echo '<script> window.location = "index.php?action=usuarios&status='.$respuesta.'&password='.$_POST['password'].'"; </script>';
				}
				else{
					echo '<script> window.location = "index.php?action=usuarios&status='.$respuesta.'"; </script>';
				}
			}
			else{
				echo '<script> window.location = "index.php?action=cambiar_password&id='.$_GET["id"].'&status=error"; </script>';
			}
		}
	}
	public function eliminaUsuarioController(){
		if(isset($_POST['password'])){
			if($_POST['password'] == $_SESSION['password']){
				Datos::eliminaUsuarioModel($_GET['id']);
				if($_GET['id'] == $_SESSION['id_user']){
					echo '<script> window.location = "index.php?action=salir"; </script>';
				}
				else{
					echo '<script> window.location = "index.php?action=productos&status=borrado"; </script>';	
				}
				
				
			}
			else{
				echo '<script> window.location = "index.php?action=eliminar_usuario&id='.$_GET["id"].'&status=error"; </script>';
			}
		}
	}
	public function agregarUsuariosController(){

		echo '  <div class="card-body">
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="text" class="form-control" required name="nombre" placeholder="Nombre">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="text" class="form-control" required name="apellido" placeholder="Apellido">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="text" class="form-control" required name="usuario" placeholder="Usuario">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="email" class="form-control" required name="email" placeholder="Email">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="password" class="form-control" required name="password" placeholder="Contraseña">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="password" class="form-control" required name="password2" placeholder="Confirma Contraseña">
	                </div>
	              </div>	              
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	              <button type="submit" class="btn btn-success">Agregar Producto</button>
	              <a href="index.php?action=usuarios" class="btn btn-default">Cancelar</a>
	            </div>';
	}

	public function agregarVentaController(){

		$codigo = Datos::getCodigoProductoModel($_SESSION['id_tienda']);
		$cargar = Datos::vistaProductosCargadosModel();
		$total = 0;
		if(isset($_POST['agregar'])){
			if($_POST['codigo']){

				$respuesta = Datos::cargarProductoModel($_POST['codigo'], $_SESSION['id_tienda'], $_POST['cantidad']);
				if($respuesta != 'fallo'){
					$cargar = Datos::vistaProductosCargadosModel();
					
					
					
					echo '<script> window.location = "index.php?action=agregar_venta"; </script>';
				}
				else{
					echo '<script> window.location = "index.php?action=agregar_venta&status=fallo"; </script>';
				}

				
			}
		}
		$total = Datos::totalVentaModel();
		echo '  <div class="card-body">
	              <div class="form-group row">
	                <div class="col-sm-9">
	                  <select class="form-control" name="codigo">';
	                  foreach ($codigo as $key => $value) {
	                  	echo '<option>'.$value['codigo'].'</option>';
	                  }
	            echo '</select>

		              <div class="form-group">
			            <div class="col-sm-2" align="right">
		                  <label class="control-label">CANTIDAD:</label>
		                </div>
		                <div class="col-sm-12">
		                  <input type="number" class="form-control" required name="cantidad" value="1">
		                </div>
		              </div>
	                </div>
	                <div class="col-sm-3">
	                	<button type="submit" name="agregar" class="btn btn-warning">Agregar Venta</button>
	                </div>
	              </div>
	              <table id="example1" class="table table-bordered table-striped">
	              	<thead>
	              		<tr>
	              			<th>ID</th>
	              			<th>CODIGO</th>
	              			<th>DESCRIPCION</th>
	              			<th>PRECIO</th>
	              			<th>CANTIDAD</th>
	              			<th>TOTAL</th>
	              		</tr>
	              	</thead>
	              	<tbody>';
	              		foreach ($cargar as $key => $value) {
	              			echo "<tr>
	              				  <td>".$value['id']."</td>
	              				  <td>".$value['codigo']."</td>
	              				  <td>".$value['descripcion']."</td>
	              				  <td>".$value['precio']."</td>
	              				  <td>".$value['cantidad']."</td>
	              				  <td>".$value['total']."</td>
	              				  </tr>";
	              		}

	              		
	           echo '</tbody>
	              </table>	 
	              <br>
	              <div class="form-group row">
	              	<div class="col-sm-1" align="left">
	                  <label class="control-label">Total:</label>
	                </div>
	                <div class="col-sm-1">
	                  <label class="control-label" name="total">$ '.$total.'</label>
	                </div>
	              </div>                
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	              <button type="submit" name="terminar" class="btn btn-success">Terminar Venta</button>
	              <a href="index.php?action=ventas" class="btn btn-default">Cancelar</a>
	            </div>';
	}
	#REGISTRO DE USUARIOS
	#------------------------------------
	public function registroVentaController(){
		if(isset($_POST["terminar"])){
			//Recibe a traves del método POST el name (html) de usuario, password y email, se almacenan los datos en una variable de tipo array con sus respectivas propiedades (usuario, password y email):			

			//Se le dice al modelo models/crud.php (Datos::registroUsuarioModel),que en la clase "Datos", la funcion "registroUsuarioModel" reciba en sus 2 parametros los valores "$datosController" y el nombre de la tabla a conectarnos la cual es "usuarios":
			$cargar = Datos::vistaProductosCargadosModel();
			//$total = $_POST['total'];
			$respuesta = Datos::registroVentaModel($_SESSION["fecha"], $_SESSION['id_tienda'], $cargar);

			//return $respuesta;

			echo '<script> window.location = "index.php?action=ventas&status='.$respuesta.'"; </script>';

		}

	}
	public function quitarProductosController(){
		Datos::quitarProductosCargadosModel();
	}
	#REGISTRO DE USUARIOS
	#------------------------------------
	public function registroUsuarioController(){
		if(isset($_POST["nombre"])){
			//Recibe a traves del método POST el name (html) de usuario, password y email, se almacenan los datos en una variable de tipo array con sus respectivas propiedades (usuario, password y email):

			if($_POST['password'] == $_POST['password2']){

				$datosController = array( "nombre"=>strtoupper($_POST["nombre"]), 
									      "apellido"=>strtoupper($_POST["apellido"]),
									      "usuario"=>$_POST["usuario"],
									  	  "email"=>$_POST["email"],
									  	  "password"=>$_POST["password"],
									  	  "fecha"=>$_SESSION["fecha"].' '.$_SESSION['hora']);

				//Se le dice al modelo models/crud.php (Datos::registroUsuarioModel),que en la clase "Datos", la funcion "registroUsuarioModel" reciba en sus 2 parametros los valores "$datosController" y el nombre de la tabla a conectarnos la cual es "usuarios":
				$respuesta = Datos::registroUsuarioModel($datosController, $_SESSION['id_tienda']);

				//return $respuesta;

				echo '<script> window.location = "index.php?action=usuarios&status='.$respuesta.'"; </script>';
			}
			else{
				echo '<script> window.location = "index.php?action=agregar_usuario&status=passwords"; </script>';
			}

		}

	}

	public function editarCategoriaController(){
		$respuesta = Datos::detallesCategoriaModel($_GET['id']);
		echo '  <div class="card-body">
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">ID:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" disabled name="id" placeholder="Id" value = "'.$respuesta[0]['id'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">NOMBRE:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" name="nombre" placeholder="Codigo Producto" value = "'.$respuesta[0]['nombre'].'">
	                </div>
	              </div>
	              <div class="form-group row">
	              	<div class="col-sm-2" align="right">
	                  <label class="control-label">DESCRIPCION:</label>
	                </div>
	                <div class="col-sm-10">
	                  <input type="text" class="form-control" name="descripcion" placeholder="Nombre" value = "'.$respuesta[0]['descripcion'].'">
	                </div>
	              </div>	              
	            <!-- /.card-body -->
	            <div class="card-footer">
	            	<button name="guardar" class="btn btn-success">Guardar Cambios</button></a>
	    		  	<a href="index.php?action=categorias" class="btn btn-info">Cancelar</a>
	            </div>';
	}
	public function actualizarCategoriaController(){

		if(isset($_POST['nombre'])){
			
			$datosProd = array( "id"=>$_GET['id'],
								"nombre"=>strtoupper($_POST["nombre"]), 
						        "descripcion"=>$_POST["descripcion"]);

			$respuesta = Datos::actualizarCategoriaModel($datosProd, $_GET['nombre'], $_SESSION['id_tienda']);

			echo '<script> window.location = "index.php?action=categorias&status='.$respuesta.'"; </script>';
		}
	}
	public function eliminaCategoriaController(){
		if(isset($_POST['password'])){
			if($_POST['password'] == $_SESSION['password']){
				Datos::eliminaCategoriaModel($_GET['id']);
				echo '<script> window.location = "index.php?action=categorias&status=borrado"; </script>';
				
				
			}
			else{
				echo '<script> window.location = "index.php?action=eliminar_categoria&id='.$_GET["id"].'&status=error"; </script>';
			}
		}
	}
	public function eliminaTiendaController(){
		if(isset($_POST['password'])){
			if($_POST['password'] == $_SESSION['password']){
				Datos::eliminaTiendaModel($_GET['id']);
				echo '<script> window.location = "index.php?action=dashboard_tiendas&status=borrado"; </script>';				
				
			}
			else{
				echo '<script> window.location = "index.php?action=eliminar_tienda&id='.$_GET["id"].'&status=error"; </script>';
			}
		}
	}
	public function eliminaVentaController(){
		if(isset($_POST['password'])){
			if($_POST['password'] == $_SESSION['password']){
				Datos::eliminaVentaModel($_GET['id']);
				echo '<script> window.location = "index.php?action=ventas&status=borrado"; </script>';				
				
			}
			else{
				echo '<script> window.location = "index.php?action=eliminar_venta&id='.$_GET["id"].'&status=error"; </script>';
			}
		}
	}
	public function agregarCategoriaController(){
		
		echo '  <div class="card-body">
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="text" class="form-control" required name="nombre" placeholder="Nombre">
	                </div>
	              </div>
	              <div class="form-group">
	                <div class="col-sm-12">
	                  <input type="text" class="form-control" required name="descripcion" placeholder="Descripcion">
	                </div>
	              </div>	              
	            </div>
	            <!-- /.card-body -->
	            <div class="card-footer">
	              <button type="submit" class="btn btn-success">Agregar Categoria</button>
	              <a href="index.php?action=categorias" class="btn btn-default">Cancelar</a>
	            </div>';
	}
	#REGISTRO DE USUARIOS
	#------------------------------------
	public function registroCategoriaController(){
		if(isset($_POST["nombre"])){
			//Recibe a traves del método POST el name (html) de usuario, password y email, se almacenan los datos en una variable de tipo array con sus respectivas propiedades (usuario, password y email):			

			$datosController = array( "nombre"=>strtoupper($_POST["nombre"]), 
								      "descripcion"=>$_POST["descripcion"],
								      "agregado"=>$_SESSION["fecha"].' '.$_SESSION['hora'],
								  	  "tienda"=>$_SESSION["id_tienda"]);

			//Se le dice al modelo models/crud.php (Datos::registroUsuarioModel),que en la clase "Datos", la funcion "registroUsuarioModel" reciba en sus 2 parametros los valores "$datosController" y el nombre de la tabla a conectarnos la cual es "usuarios":
			$respuesta = Datos::registroCategoriaModel($datosController, $_SESSION['id_tienda']);

			//return $respuesta;

			echo '<script> window.location = "index.php?action=categorias&status='.$respuesta.'"; </script>';
			

		}

	}

}
////
?>