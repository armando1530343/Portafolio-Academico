<?php

//Se invocan los archivos que tienen los metodos:
require_once "models/enlaces.php";
require_once "models/crud.php";
require_once "controllers/controller.php";
//Para poder ver el template se hace la petición mediante un controlador.

//creamos el objeto:
$mvc = new Mvc();

//muestra la función "pagina" que se encuentra en controlles/controller.php
$mvc -> pagina();

?>