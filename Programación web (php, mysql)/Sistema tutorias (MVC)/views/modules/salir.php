<?php

//session_start();
session_destroy();
//se confirma el agregado y se redirecciona la pagina
echo '<script> alert("Haz cerrado Sesion") </script>';
echo '<script> window.location = "index.php"; </script>';

?>
<!--div class="modal-dialog">
	<div class="loginmodal-container">
		<h1>¡Haz salido de la aplicación!</h1>
	</div>
</div-->