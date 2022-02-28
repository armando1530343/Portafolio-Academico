
<?php

/*Se crea una clase Conexion que contiene una funcion que retorna un nuevo objeto, el cual contiene los datos de conexion a la base de datos desde phpmyadmin de manera local que se utiliza para realizar las consultas*/

class Conexion{

	public function conectar(){

		return new PDO("mysql:host=localhost;dbname=BD_CAI","root",""); 

	}

}

?>
