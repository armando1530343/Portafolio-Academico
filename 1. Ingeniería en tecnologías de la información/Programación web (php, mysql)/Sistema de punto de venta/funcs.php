<?php  
	$conexion = null;
	$user = "root";
	$pass = "";
	$server = "localhost";
	$db = "cybergames";

	function conectar(){
		global $conexion, $user, $pass, $server, $db;
		
		$conexion = mysqli_connect($server, $user, $pass, $db);
		return $conexion;
	}

	function desconectar(){
		global $conexion;
		if($conexion){
			$conexion->close();
		}
		
	}

	function login ($user, $pass){
		global $conexion;
		conectar();
		
		$consulta1 = $conexion->query("SELECT * FROM administrador WHERE usuario = '$user' and clave = '$pass'");
		$consulta2 = $conexion->query("SELECT * FROM empleado WHERE usuario = '$user' and clave = '$pass'");
				
		if($consulta1->num_rows > 0){
			$_SESSION["usuario"] = "administrador";
			return true;
		}
		elseif ($consulta2->num_rows > 0){
			$_SESSION["usuario"] = "empleado";
			return true;
		}
		desconectar();
		return false;
	}

	function numVentas(){
		global $conexion;
		if(conectar()){
			$num = current($conexion->query("SELECT count(*) from venta")->fetch_assoc());
			//echo "<script>alert($num);</script>";
			desconectar();
			return $num;			
		}
	}
	function ingresosTotales(){
		global $conexion;
		if(conectar()){
			$total = current($conexion->query("SELECT SUM(total) from venta")->fetch_assoc());
			//echo "<script>alert($num);</script>";
			desconectar();
			return $total;			
		}
	}


?>