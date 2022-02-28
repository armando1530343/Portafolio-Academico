<br><br><br>
<div class="modal-dialog">
	<div class="loginmodal-container">
		<h1>CONTROL DE TUTORIAS</h1><br>
		<h3>Ingresar</h3>
		<form method="post">
			
			<input type="text" placeholder="Usuario" name="usuarioIngreso" required>

			<input type="password" placeholder="Contraseña" name="passwordIngreso" required>

			<input type="submit" class="login loginmodal-submit" value="Enviar">

		</form>
	</div>
</div>

<?php

$ingreso = new MvcController();
$ingreso -> ingresoUsuarioController();

if(isset($_GET["action"])){

	if($_GET["action"] == "fallo"){

		echo "Fallo al ingresar";
	
	}

}

?>