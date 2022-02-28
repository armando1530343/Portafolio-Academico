<?php

#EXTENSIÓN DE CLASES: Los objetos pueden ser extendidos, y pueden heredar propiedades y métodos. Para definir una clase como extensión, debo definir una clase padre, y se utiliza dentro de una clase hija.

require_once "conexion.php";

//heredar la clase conexion de conexion.php para poder utilizar "Conexion" del archivo conexion.php.
// Se extiende cuando se requiere manipuar una funcion, en este caso se va a  manipular la función "conectar" del models/conexion.php:
class Datos extends Conexion{

	#INGRESO USUARIO
	#-------------------------------------
	public function ingresoUsuarioModel($datosModel){
		/*Se realiza la consulta a la tabla de usuarios para verificar si existen los datos del usuario ingresado*/
		$stmt = Conexion::conectar()->prepare("SELECT * FROM users WHERE user_name = :username and user_password_hash = :password");	
		$stmt->bindParam(":username", $datosModel["username"], PDO::PARAM_STR);
		$stmt->bindParam(":password", $datosModel["password"], PDO::PARAM_STR);
		$stmt->execute();
		
		return $stmt->fetch();

		$stmt->close();

	}

	public function getTiendaModel($id_tienda){
		$stmt = Conexion::conectar()->prepare('SELECT * FROM tiendas WHERE id_tienda = :id');
		$stmt->bindParam(':id', $id_tienda, PDO::PARAM_INT);
		$stmt->execute();

		return $stmt->fetchAll();
	}

	public function dashboardStockModel($fecha, $id_tienda){
		$stmt = Conexion::conectar()->prepare(
			'SELECT COUNT(*) as stock_hoy
				FROM historial as h
				INNER JOIN products as p on h.id_producto = p.id_producto
				INNER JOIN categorias as c on p.id_categoria = c.id_categoria
				WHERE c.id_tienda = :tienda and date(h.fecha) = :fecha');
		$stmt->bindParam(':fecha', $fecha, PDO::PARAM_STR);
		$stmt->bindParam(':tienda', $id_tienda, PDO::PARAM_INT);
		$stmt->execute();

		return $stmt->fetchColumn();
	}

	public function dashboardProductosModel($id_tienda){
		$stmt = Conexion::conectar()->prepare(
			'SELECT COUNT(*) as productos
				FROM products as p 
				INNER JOIN categorias as c on p.id_categoria = c.id_categoria
				WHERE c.id_tienda = :tienda');
		$stmt->bindParam(':tienda', $id_tienda, PDO::PARAM_INT);
		$stmt->execute();

		return $stmt->fetchColumn();

	}
	public function dashboardUsuariosModel($id_tienda){
		$stmt = Conexion::conectar()->prepare(
			'SELECT COUNT(*) as usuarios FROM users WHERE id_tienda = :tienda');
		$stmt->bindParam(':tienda', $id_tienda, PDO::PARAM_INT);
		$stmt->execute();

		return $stmt->fetchColumn();

	}
	public function dashboardCategoriasModel($id_tienda){
		$stmt = Conexion::conectar()->prepare(
			'SELECT COUNT(*) as categorias FROM categorias WHERE id_tienda = :tienda');
		$stmt->bindParam(':tienda', $id_tienda, PDO::PARAM_INT);
		$stmt->execute();

		return $stmt->fetchColumn();

	}

	public function estadoTiendaModel($estado, $id){
		$stmt = Conexion::conectar()->prepare('UPDATE tiendas SET estado = :estado WHERE id_tienda = :id');
		$stmt->bindParam(':estado', $estado, PDO::PARAM_STR);
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->execute();
	}


	#<<<<<<------------CRUD DE PRODUCTOS------------>>>>>>>>>>>>

	#REGISTRO DE PRODUCTOS
	#----------------------------------------
	public function registroProductosModel($datos, $id_tienda){

		#primero se hace una consulta para verificar si existe el codigo de producto

		$stmt = Conexion::conectar()->prepare(
			"SELECT COUNT(*) FROM products as p 
			INNER JOIN categorias as c on p.id_categoria = c.id_categoria
			WHERE p.codigo_producto = :codigo and c.id_tienda = :tienda");
		$stmt->bindParam(':codigo', $datos['codigo'], PDO::PARAM_STR);
		$stmt->bindParam(':tienda', $id_tienda, PDO::PARAM_INT);
		$stmt->execute();
		$numero = $stmt->fetchColumn();

		$stmt = Conexion::conectar()->prepare("SELECT id_categoria FROM categorias WHERE nombre_categoria = :nombre and id_tienda = :tienda");
		$stmt->bindParam(':nombre', $datos['categoria'], PDO::PARAM_STR);
		$stmt->bindParam(':tienda', $id_tienda, PDO::PARAM_INT);
		$stmt->execute();
		$id_categoria = $stmt->fetchColumn();

		$stmt = Conexion::conectar()->prepare("INSERT INTO products(codigo_producto, nombre_producto, data_added, precio_producto, stock, id_categoria) VALUES (:codigo, :nombre, :fecha, :precio, :stock, :categoria)");
		$stmt->bindParam(':codigo', $datos['codigo'], PDO::PARAM_STR);
		$stmt->bindParam(':nombre', $datos['nombre'], PDO::PARAM_STR);
		$stmt->bindParam(':fecha', $datos['fecha'], PDO::PARAM_STR);
		$stmt->bindParam(':precio', $datos['precio'], PDO::PARAM_INT);
		$stmt->bindParam(':stock', $datos['stock'], PDO::PARAM_INT);
		$stmt->bindParam(':categoria', $id_categoria, PDO::PARAM_INT);

		if($numero > 0){
			return 'existe';
		}
		else if($stmt->execute()){
			return 'success';
		}
		else{
			return 'error';
		}


	}

	#OBTENCION DEL ID DEL ULTIMO PRODUCTO REGISTRADO
	#_-------------------------------------------------
	public function getLastIdModel(){
		$stmt = Conexion::conectar()->prepare("SELECT MAX(id_producto) FROM products");
		$stmt->execute();
		return $stmt->fetchColumn();
	}

	#VISTA PRODUCTOS (INVENTARIO)
	#-------------------------------------
	public function vistaProductosModel($id_tienda){

		$stmt = Conexion::conectar()->prepare(
			"SELECT p.id_producto as id,
			       p.codigo_producto as codigo,
			       p.nombre_producto as nombre,
			       date(p.data_added) as fecha,
			       p.precio_producto as precio,
			       p.stock as stock,
			       c.nombre_categoria as categoria       
			FROM products as p INNER JOIN categorias as c on p.id_categoria = c.id_categoria WHERE c.id_tienda = :id");
		$stmt->bindParam(':id', $id_tienda, PDO::PARAM_INT);	
		$stmt->execute();

		return $stmt->fetchAll();

		$stmt->close();

	}
	#MUESTRA LOS DETALLES DE UN SOLO PRODUCTO
	#-------------------------------------
	public function detallesProductosModel($idProd){

		$stmt = Conexion::conectar()->prepare(
			"SELECT p.id_producto as id,
			       p.codigo_producto as codigo,
			       p.nombre_producto as nombre,
			       date(p.data_added) as fecha,
			       p.precio_producto as precio,
			       p.stock as stock,
			       c.nombre_categoria as categoria       
			FROM products as p INNER JOIN categorias as c on p.id_categoria = c.id_categoria WHERE id_producto = :id");
		$stmt->bindParam(':id',$idProd,PDO::PARAM_INT);	
		$stmt->execute();

		#fetchAll(): Obtiene todas las filas de un conjunto de resultados asociado al objeto PDOStatement. 
		return $stmt->fetchAll();

		$stmt->close();

	}
	#VISTA DE LAS CATEGORIAS QUE EXISTEN
	#-------------------------------------
	public function getCategoriasModel($id_tienda){
		$stmt = Conexion::conectar()->prepare("SELECT id_categoria as id, nombre_categoria as nombre, descripcion_categoria as descripcion, date(data_added) as agregado FROM categorias WHERE id_tienda = :tienda");
		$stmt->bindParam(':tienda', $id_tienda, PDO::PARAM_INT);
		$stmt->execute();

		return $stmt->fetchAll();

		$stmt->close();
	}

	#BORRAR PRODUCTOS
	#-------------------------------------
	public function borrarProductoModel($id){
		
		$stmt = Conexion::conectar()->prepare("DELETE FROM historial WHERE id_producto = :id");
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->execute();

		$stmt = Conexion::conectar()->prepare("DELETE FROM products WHERE id_producto = :id");
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		
		if($stmt->execute()){

			return "success";

		}

		else{

			return "error";

		}

		$stmt->close();

	}
	#ACTUALIZAR RODUCTO
	#-------------------------------------

	public function actualizarProductoModel($datos, $codigo){
		$stmt = Conexion::conectar()->prepare("SELECT COUNT(*) FROM products WHERE codigo_producto = :codigo");
		$stmt->bindParam(':codigo', $datos['codigo'], PDO::PARAM_STR);
		$stmt->execute();
		$numero = $stmt->fetchColumn();

		$stmt = Conexion::conectar()->prepare("SELECT id_categoria FROM categorias WHERE nombre_categoria = :nombre");
		$stmt->bindParam(':nombre', $datos['categoria'], PDO::PARAM_STR);
		$stmt->execute();
		$id_categoria = $stmt->fetchColumn();

		$stmt = Conexion::conectar()->prepare("UPDATE products SET codigo_producto = :codigo, nombre_producto = :nombre, data_added = :fecha, precio_producto = :precio, id_categoria = :categoria WHERE id_producto = :id");


		$stmt->bindParam(":codigo", $datos["codigo"], PDO::PARAM_STR);
		$stmt->bindParam(":nombre", $datos["nombre"], PDO::PARAM_STR);
		$stmt->bindParam(":fecha", $datos["fecha"], PDO::PARAM_STR);
		$stmt->bindParam(":precio", $datos["precio"], PDO::PARAM_INT);
		$stmt->bindParam(":id", $datos["id"], PDO::PARAM_INT);
		$stmt->bindParam(":categoria", $id_categoria, PDO::PARAM_INT);

		if($numero > 0 && $codigo != $datos['codigo']){
			return 'existe';
		}
		else if($stmt->execute()){
			return 'success';
		}
		else{
			return 'error';
		}

		$stmt->close();

	}




	public function registroHistorialModel($datos){
		$stmt = Conexion::conectar()->prepare("INSERT INTO historial (id_producto, user_id, fecha, descripcion, referencia, cantidad) VALUES (:id_producto, :user_id, :fecha, :descripcion, :referencia, :cantidad)");
		$stmt->bindParam(':id_producto', $datos['id_producto'], PDO::PARAM_INT);
		$stmt->bindParam(':user_id', $datos['id_user'], PDO::PARAM_INT);
		$stmt->bindParam(':fecha', $datos['fecha'], PDO::PARAM_STR);
		$stmt->bindParam(':descripcion', $datos['descripcion'], PDO::PARAM_STR);
		$stmt->bindParam(':referencia', $datos['referencia'], PDO::PARAM_STR);
		$stmt->bindParam(':cantidad', $datos['cantidad'], PDO::PARAM_INT);

		if($stmt->execute()){
			return 'success';
		}
		else{
			return 'error';
		}
	}
	public function eliminaStockModel($cantidad, $id){
		$stmt = Conexion::conectar()->prepare("SELECT stock FROM products WHERE id_producto = :id");
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->execute();
		$numero = $stmt->fetchColumn();

		$stmt = Conexion::conectar()->prepare("UPDATE products SET stock = stock - :cantidad WHERE id_producto = :id");
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->bindParam(':cantidad', $cantidad, PDO::PARAM_INT);
		
		if($cantidad > $numero){
			return 'incorrecto';
		}
		else if($stmt->execute()){
			return 'success';
		}
		else{
			return 'error';
		}
	}

	public function actualizaStockModel($cantidad, $id){
		$stmt = Conexion::conectar()->prepare("UPDATE products SET stock = stock + :cantidad WHERE id_producto = :id");
		$stmt->bindParam(':cantidad', $cantidad, PDO::PARAM_INT);
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->execute();
	}

	
	public function vistaHistorialModel($id_producto){

		$stmt = Conexion::conectar()->prepare(
			"SELECT date(h.fecha) as fecha,
					time(h.fecha) as hora,
			        h.descripcion as descripcion,
			        h.referencia as referencia,
			        h.cantidad*p.precio_producto as total
			FROM historial as h INNER JOIN products as p on h.id_producto = p.id_producto WHERE h.id_producto = :id_producto");
		$stmt->bindParam(':id_producto', $id_producto, PDO::PARAM_INT);	
		$stmt->execute();

		#fetchAll(): Obtiene todas las filas de un conjunto de resultados asociado al objeto PDOStatement. 
		return $stmt->fetchAll();

		$stmt->close();

	}
	#VISTA DE VENTAS
	public function vistaVentasModel($id){

		$stmt = Conexion::conectar()->prepare("SELECT * FROM ventas WHERE id_tienda = :id");
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);	
		$stmt->execute();

		#fetchAll(): Obtiene todas las filas de un conjunto de resultados asociado al objeto PDOStatement. 
		return $stmt->fetchAll();

		$stmt->close();

	}
	#VISTA DE VENTAS
	public function getProductosVentaModel($id_venta){

		$stmt = Conexion::conectar()->prepare(
			"SELECT DISTINCT p.codigo_producto as codigo, p.nombre_producto as nombre, p.precio_producto as precio, (SELECT COUNT(*) FROM venta_productos WHERE id_producto = p.id_producto and id_venta = v.id_venta) as cantidad
			FROM products as p 
			INNER JOIN venta_productos as vp on p.id_producto = vp.id_producto
			INNER JOIN ventas as v on vp.id_venta = v.id_venta WHERE v.id_venta = :id");
		$stmt->bindParam(':id', $id_venta, PDO::PARAM_INT);	
		$stmt->execute();

		#fetchAll(): Obtiene todas las filas de un conjunto de resultados asociado al objeto PDOStatement. 
		return $stmt->fetchAll();

		$stmt->close();

	}
	#VISTA DE VENTAS
	public function productoVenderModel($codigo_producto, $id_tienda){

		$stmt = Conexion::conectar()->prepare(
			"SELECT p.id_producto as id, p.nombre_producto as nombre, p.precio_producto as precio
			FROM products as p
			INNER JOIN categorias as c on p.id_categoria = c.id_categoria WHERE c.id_tienda = :id_tienda and p.codigo_producto = :codigo_producto");
		$stmt->bindParam(':codigo_producto', $codigo_producto, PDO::PARAM_STR);
		$stmt->bindParam(':id_tienda', $id_tienda, PDO::PARAM_INT);	
		$stmt->execute();

		#fetchAll(): Obtiene todas las filas de un conjunto de resultados asociado al objeto PDOStatement. 
		return $stmt->fetchAll();

		$stmt->close();

	}
	#OBTENER CODIGOS DE PRODUCTOS
	public function getCodigoProductoModel($id_tienda){

		$stmt = Conexion::conectar()->prepare(
			"SELECT p.codigo_producto as codigo
			FROM products as p
			INNER JOIN categorias as c on p.id_categoria = c.id_categoria WHERE c.id_tienda = :id");
		$stmt->bindParam(':id', $id_tienda, PDO::PARAM_INT);	
		$stmt->execute();

		#fetchAll(): Obtiene todas las filas de un conjunto de resultados asociado al objeto PDOStatement. 
		return $stmt->fetchAll();

		$stmt->close();

	}

	public function cargarProductoModel($codigo, $tienda, $cant){

		$stmt = Conexion::conectar()->prepare(
			"SELECT * FROM products as p
			INNER JOIN categorias as c on p.id_categoria = c.id_categoria WHERE p.codigo_producto = :codigo and c.id_tienda = :tienda");
		$stmt->bindParam(':codigo', $codigo, PDO::PARAM_STR);
		$stmt->bindParam(':tienda', $tienda, PDO::PARAM_STR);
		$stmt->execute();
		$producto = $stmt->fetchAll();

		
		if($cant <= $producto[0]['stock']){


			$stmt = Conexion::conectar()->prepare("SELECT COUNT(cantidad) FROM carga_producto WHERE codigo = :codigo");
			$stmt->bindParam(':codigo', $codigo, PDO::PARAM_STR);
			$stmt->execute();


			if($stmt->fetchColumn() > 0){
				$stmt = Conexion::conectar()->prepare("SELECT cantidad FROM carga_producto WHERE codigo = :codigo");
				$stmt->bindParam(':codigo', $codigo, PDO::PARAM_STR);
				$stmt->execute();
				$cantidad = $stmt->fetchColumn();

				if($cantidad >= 1){
					$stmt = Conexion::conectar()->prepare("UPDATE carga_producto SET cantidad = cantidad + :cant, total = precio*cantidad WHERE codigo = :codigo");
					$stmt->bindParam(':cant', $cant, PDO::PARAM_INT);
					$stmt->bindParam(':codigo', $codigo, PDO::PARAM_STR);
					$stmt->execute();
				}
				else{
					$stmt = Conexion::conectar()->prepare("INSERT INTO carga_producto(id, codigo, descripcion, precio, cantidad, total) VALUES(:id, :codigo, :descripcion, :precio_producto, 1, :total)");
					$stmt->bindParam(':id', $producto[0]['id_producto'], PDO::PARAM_INT);
					$stmt->bindParam(':codigo', $codigo, PDO::PARAM_STR);
					$stmt->bindParam(':descripcion', $producto[0]['nombre_producto'], PDO::PARAM_STR);
					$stmt->bindParam(':precio', $producto[0]['precio_producto'], PDO::PARAM_INT);
					$stmt->bindParam(':total', $producto[0]['precio_producto'], PDO::PARAM_INT);
					$stmt->execute();
				}
			}
			else{
				$stmt2 = Conexion::conectar()->prepare("INSERT INTO carga_producto(id, codigo, descripcion, precio, cantidad, total) VALUES(:id, :codigo, :descripcion, :precio, :cantidad, :precio, :total)");
				$stmt2->bindParam(':id', $producto[0]['id_producto'], PDO::PARAM_INT);
				$stmt2->bindParam(':codigo', $codigo, PDO::PARAM_STR);
				$stmt2->bindParam(':descripcion', $producto[0]['nombre_producto'], PDO::PARAM_STR);
				$stmt2->bindParam(':precio', $producto[0]['precio_producto'], PDO::PARAM_INT);
				$stmt2->bindParam(':cantidad', $cant, PDO::PARAM_INT);
				$stmt2->bindParam(':total', $producto[0]['precio_producto'], PDO::PARAM_INT);
				$stmt2->execute();

				
			}
		}
		else{
			return "fallo";
		}

		return "success";


	}
	#VISTA PRODUCTOS CARGADOS
	#-------------------------------------
	public function vistaProductosCargadosModel(){

		$stmt = Conexion::conectar()->prepare("SELECT id, codigo, descripcion, precio, cantidad, total FROM carga_producto");
		$stmt->execute();

		return $stmt->fetchAll();

		$stmt->close();

	}
	public function quitarProductosCargadosModel(){

		$stmt = Conexion::conectar()->prepare("DELETE FROM carga_producto");
		$stmt->execute();

	}
	public function totalVentaModel(){

		$stmt = Conexion::conectar()->prepare("SELECT SUM(total) FROM carga_producto");
		$stmt->execute();
		return $stmt->fetchColumn();

	}

	public function registroVentaModel($fecha, $tienda, $datos){

		$stmt = Conexion::conectar()->prepare("INSERT INTO ventas(fecha, total, id_tienda) VALUES(:fecha, 1, :id_tienda)");
		$stmt->bindParam(':fecha', $fecha, PDO::PARAM_STR);
		//$stmt->bindParam(':total', $total, PDO::PARAM_INT);
		$stmt->bindParam(':id_tienda', $tienda, PDO::PARAM_INT);
		$stmt->execute();

		$stmt = Conexion::conectar()->prepare("SELECT MAX(id_venta) FROM ventas WHERE id_tienda = :id_tienda");
		$stmt->bindParam(':id_tienda', $tienda, PDO::PARAM_INT);
		$stmt->execute();
		$id_venta = $stmt->fetchColumn();

		$total = 0;

		foreach ($datos as $key => $value) {

			for($i = 1; $i <= $value['cantidad']; $i++){
				$stmt = Conexion::conectar()->prepare("INSERT INTO venta_productos(id_venta, id_producto) VALUES(:id_venta, :id_producto)");
				$stmt->bindParam(':id_venta', $id_venta, PDO::PARAM_INT);
				$stmt->bindParam(':id_producto', $value['id'], PDO::PARAM_INT);				
				$stmt->execute();

				$stmt = Conexion::conectar()->prepare("UPDATE products SET stock = stock-1 WHERE id_producto = :id_producto");
				$stmt->bindParam(':id_producto', $value['id'], PDO::PARAM_INT);				
				$stmt->execute();
			}
			$total += $value['total'];
		}

		$stmt = Conexion::conectar()->prepare("UPDATE ventas SET total = :total WHERE id_tienda = :id_tienda and id_venta = :id_venta");
		$stmt->bindParam(':id_venta', $id_venta, PDO::PARAM_INT);
		$stmt->bindParam(':total', $total, PDO::PARAM_INT);
		$stmt->bindParam(':id_tienda', $tienda, PDO::PARAM_INT);
		$stmt->execute();

		return "registrado";

	}



	#VISTA USUARIOS
	#-------------------------------------
	public function vistaUsuariosModel($id_tienda){

		$stmt = Conexion::conectar()->prepare(
			"SELECT user_id as id, 
					firstname as nombre,
					lastname as apellido,
					user_name as usuario,
			        user_email as email,
			        date(data_added) as agregado FROM users WHERE user_name != 'admin' and id_tienda = :tienda");
		$stmt->bindParam(':tienda', $id_tienda, PDO::PARAM_INT);	
		$stmt->execute();

		return $stmt->fetchAll();

		$stmt->close();

	}

	#VISTA TIENDAS
	#-------------------------------------
	public function vistaTiendasModel(){

		$stmt = Conexion::conectar()->prepare(
			"SELECT * FROM tiendas");	
		$stmt->execute();

		return $stmt->fetchAll();

		$stmt->close();

	}
	#VISTA PERFIL
	#-------------------------------------
	public function vistaPerfilModel($id){

		$stmt = Conexion::conectar()->prepare("SELECT * FROM users WHERE user_id = :id");
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);	
		$stmt->execute();

		return $stmt->fetchAll();

		$stmt->close();

	}
	#MUESTRA LOS DETALLES DE UN SOLO USUARIO
	#-------------------------------------
	public function detallesUsuariosModel($idProd){

		$stmt = Conexion::conectar()->prepare(
			"SELECT user_id as id,
					firstname as nombre,
					lastname as apellido,
					user_name as usuario,
			        user_email as email FROM users WHERE user_id = :id");
		$stmt->bindParam(':id',$idProd,PDO::PARAM_INT);	
		$stmt->execute();

		#fetchAll(): Obtiene todas las filas de un conjunto de resultados asociado al objeto PDOStatement. 
		return $stmt->fetchAll();

		$stmt->close();

	}

	public function actualizarUsuarioModel($datos, $usuario, $e_mail){
		$stmt = Conexion::conectar()->prepare("SELECT COUNT(*) FROM users WHERE user_name = :user");
		$stmt->bindParam(':user', $datos['usuario'], PDO::PARAM_STR);
		$stmt->execute();
		$users = $stmt->fetchColumn();

		$stmt = Conexion::conectar()->prepare("SELECT COUNT(*) FROM users WHERE user_email = :email");
		$stmt->bindParam(':email', $datos['email'], PDO::PARAM_STR);
		$stmt->execute();
		$email = $stmt->fetchColumn();

		$stmt = Conexion::conectar()->prepare("UPDATE users SET firstname = :nombre, lastname = :apellido, user_name = :usuario, user_email = :email WHERE user_id = :id");
		$stmt->bindParam(":nombre", $datos["nombre"], PDO::PARAM_STR);
		$stmt->bindParam(":apellido", $datos["apellido"], PDO::PARAM_STR);
		$stmt->bindParam(":usuario", $datos["usuario"], PDO::PARAM_STR);
		$stmt->bindParam(":email", $datos["email"], PDO::PARAM_STR);
		$stmt->bindParam(":id", $datos["id"], PDO::PARAM_INT);

		if(($users > 0 && $usuario!=$datos['usuario']) || ($email > 0 && $e_mail!=$datos['email'])){
			return 'existe';
		}
		else if($stmt->execute()){
			return 'actualizado';
		}
		else{
			return 'error';
		}

		$stmt->close();

	}

	public function cambiarPasswordModel($id, $password){
		$stmt = Conexion::conectar()->prepare('UPDATE users SET user_password_hash = :password WHERE user_id = :id');
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->bindParam(':password', $password, PDO::PARAM_STR);
		$stmt->execute();

		return 'new_password';
	}

	public function eliminaUsuarioModel($id){


		$stmt = Conexion::conectar()->prepare('DELETE FROM users WHERE user_id = :id');
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->execute();
	}
	#REGISTRO DE PRODUCTOS
	#----------------------------------------
	public function registroUsuarioModel($datos, $id_tienda){

		#primero se hace una consulta para verificar si existe el codigo de producto

		$stmt = Conexion::conectar()->prepare("SELECT COUNT(*) FROM users WHERE user_name = :user");
		$stmt->bindParam(':user', $datos['usuario'], PDO::PARAM_STR);
		$stmt->execute();
		$users = $stmt->fetchColumn();

		$stmt = Conexion::conectar()->prepare("SELECT COUNT(*) FROM users WHERE user_email = :email");
		$stmt->bindParam(':email', $datos['email'], PDO::PARAM_STR);
		$stmt->execute();
		$email = $stmt->fetchColumn();

		$stmt = Conexion::conectar()->prepare("INSERT INTO users(firstname, lastname, user_name, user_password_hash, user_email, data_added, id_tienda) VALUES (:nombre, :apellido, :usuario, :password, :email, :fecha, :tienda)");
		$stmt->bindParam(':nombre', $datos['nombre'], PDO::PARAM_STR);
		$stmt->bindParam(':apellido', $datos['apellido'], PDO::PARAM_STR);
		$stmt->bindParam(':usuario', $datos['usuario'], PDO::PARAM_STR);
		$stmt->bindParam(':password', $datos['password'], PDO::PARAM_STR);
		$stmt->bindParam(':email', $datos['email'], PDO::PARAM_STR);
		$stmt->bindParam(':fecha', $datos['fecha'], PDO::PARAM_STR);
		$stmt->bindParam(':tienda', $id_tienda, PDO::PARAM_INT);

		if($users > 0 || $email > 0){
			return 'existe';
		}
		else if($stmt->execute()){
			return 'registrado';
		}
		else{
			return 'error';
		}


	}
	#MUESTRA LOS DETALLES DE UN SOLO PRODUCTO
	#-------------------------------------
	public function detallesCategoriaModel($id){

		$stmt = Conexion::conectar()->prepare("SELECT id_categoria as id, nombre_categoria as nombre, descripcion_categoria as descripcion, date(data_added) as agregado FROM categorias WHERE id_categoria = :id");
		$stmt->bindParam(':id',$id,PDO::PARAM_INT);	
		$stmt->execute();

		#fetchAll(): Obtiene todas las filas de un conjunto de resultados asociado al objeto PDOStatement. 
		return $stmt->fetchAll();

		$stmt->close();

	}
	public function actualizarCategoriaModel($datos, $nombre, $id_tienda){
		$stmt = Conexion::conectar()->prepare("SELECT COUNT(*) FROM categorias WHERE nombre_categoria = :nombre and id_tienda = :tienda");
		$stmt->bindParam(':nombre', $datos['nombre'], PDO::PARAM_STR);
		$stmt->bindParam(':tienda', $id_tienda, PDO::PARAM_INT);
		$stmt->execute();
		$categorias = $stmt->fetchColumn();


		$stmt = Conexion::conectar()->prepare("UPDATE categorias SET nombre_categoria = :nombre, descripcion_categoria = :descripcion WHERE id_categoria = :id");
		$stmt->bindParam(":nombre", $datos["nombre"], PDO::PARAM_STR);
		$stmt->bindParam(":descripcion", $datos["descripcion"], PDO::PARAM_STR);
		$stmt->bindParam(":id", $datos["id"], PDO::PARAM_INT);

		if(($categorias > 0 && $nombre!=$datos['nombre'])){
			return 'existe';
		}
		else if($stmt->execute()){
			return 'actualizado';
		}
		else{
			return 'error';
		}

		$stmt->close();

	}
	public function eliminaTiendaModel($id){

		$stmt = Conexion::conectar()->prepare('SELECT id_categoria FROM categorias  WHERE id_tienda = :id');
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->execute();
		$categorias = $stmt->fetchAll();

		foreach ($categorias as $key => $value1) {
			$stmt = Conexion::conectar()->prepare('SELECT id_producto FROM products  WHERE id_categoria = :id');
			$stmt->bindParam(':id', $value1['id_categoria'], PDO::PARAM_INT);
			$stmt->execute();
			$productos = $stmt->fetchAll();

			foreach ($productos as $key => $value2) {
				$stmt = Conexion::conectar()->prepare('DELETE FROM historial WHERE id_producto = :id');
				$stmt->bindParam(':id', $value2['id_producto'], PDO::PARAM_INT);
				$stmt->execute();
			}

			$stmt = Conexion::conectar()->prepare('DELETE FROM products WHERE id_categoria = :id');
			$stmt->bindParam(':id', $value1['id_categoria'], PDO::PARAM_INT);
			$stmt->execute();

			
		}

		$stmt = Conexion::conectar()->prepare('SELECT user_id FROM users  WHERE id_tienda = :id');
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->execute();
		$users = $stmt->fetchAll();

		foreach ($users as $key => $value) {
			$stmt = Conexion::conectar()->prepare('DELETE FROM historial WHERE user_id = :id');
			$stmt->bindParam(':id', $value['user_id'], PDO::PARAM_INT);
			$stmt->execute();

			
		}

		$stmt = Conexion::conectar()->prepare('DELETE FROM users WHERE id_tienda = :id');
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->execute();

		$stmt = Conexion::conectar()->prepare('DELETE FROM categorias WHERE id_tienda = :id');
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->execute();

		$stmt = Conexion::conectar()->prepare('DELETE FROM tiendas WHERE id_tienda = :id');
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->execute();
	}
	public function eliminaVentaModel($id){
		$stmt = Conexion::conectar()->prepare('DELETE FROM venta_productos WHERE id_venta = :id');
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->execute();

		$stmt = Conexion::conectar()->prepare('DELETE FROM ventas WHERE id_venta = :id');
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->execute();
	}
	public function eliminaCategoriaModel($id){

		$stmt = Conexion::conectar()->prepare('SELECT id_producto FROM products  WHERE id_categoria = :id');
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->execute();
		$ids = $stmt->fetchAll();

		foreach ($ids as $key => $value) {
			$stmt = Conexion::conectar()->prepare('DELETE FROM historial WHERE id_producto = :id');
			$stmt->bindParam(':id', $value['id_producto'], PDO::PARAM_INT);
			$stmt->execute();
		}

		$stmt = Conexion::conectar()->prepare('DELETE FROM products WHERE id_categoria = :id');
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->execute();

		$stmt = Conexion::conectar()->prepare('DELETE FROM categorias WHERE id_categoria = :id');
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->execute();
	}
	#REGISTRO DE PRODUCTOS
	#----------------------------------------
	public function registroCategoriaModel($datos, $id_tienda){

		#primero se hace una consulta para verificar si existe el codigo de producto

		$stmt = Conexion::conectar()->prepare("SELECT COUNT(*) FROM categorias WHERE nombre_categoria = :nombre and id_tienda = :tienda");
		$stmt->bindParam(':nombre', $datos['nombre'], PDO::PARAM_STR);
		$stmt->bindParam(':tienda', $id_tienda, PDO::PARAM_INT);
		$stmt->execute();
		$categorias = $stmt->fetchColumn();

		
		$stmt = Conexion::conectar()->prepare("INSERT INTO categorias(nombre_categoria, descripcion_categoria, data_added, id_tienda) VALUES (:nombre, :descripcion, :agregado, :tienda)");
		$stmt->bindParam(':nombre', $datos['nombre'], PDO::PARAM_STR);
		$stmt->bindParam(':descripcion', $datos['descripcion'], PDO::PARAM_STR);
		$stmt->bindParam(':agregado', $datos['agregado'], PDO::PARAM_STR);
		$stmt->bindParam(':tienda', $datos['tienda'], PDO::PARAM_STR);

		if($categorias > 0){
			return 'existe';
		}
		else if($stmt->execute()){
			return 'registrado';
		}
		else{
			return 'error';
		}


	}
	#REGISTRO DE TIENDAS
	#----------------------------------------
	public function registroTiendaModel($datos){

		#primero se hace una consulta para verificar si existe el codigo de producto

		$stmt = Conexion::conectar()->prepare("SELECT COUNT(*) FROM tiendas WHERE nombre = :nombre");
		$stmt->bindParam(':nombre', $datos['nombre'], PDO::PARAM_STR);
		$stmt->execute();
		$tiendas = $stmt->fetchColumn();
		
		$stmt = Conexion::conectar()->prepare("INSERT INTO tiendas(nombre, estado, fecha_add, fecha_mod, autor) VALUES (:nombre, :estado, :fecha_add, :fecha_mod, :autor)");
		$stmt->bindParam(':nombre', $datos['nombre'], PDO::PARAM_STR);
		$stmt->bindParam(':estado', $datos['estado'], PDO::PARAM_STR);
		$stmt->bindParam(':fecha_add', $datos['fecha_add'], PDO::PARAM_STR);
		$stmt->bindParam(':fecha_mod', $datos['fecha_mod'], PDO::PARAM_STR);
		$stmt->bindParam(':autor', $datos['autor'], PDO::PARAM_STR);

		if($tiendas > 0){
			return 'existe';
		}
		else if($stmt->execute()){
			return 'registrado';
		}
		else{
			return 'error';
		}


	}


	
}

?>