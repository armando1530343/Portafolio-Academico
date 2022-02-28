<?php

session_destroy();

echo '<script> alert("Haz cerrado Sesion") </script>';
echo '<script> window.location = "index.php"; </script>';

?>