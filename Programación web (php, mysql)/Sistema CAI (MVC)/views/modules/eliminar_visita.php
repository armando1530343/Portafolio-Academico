 <?php 

  if(!isset($_SESSION['validar'])){

    echo '<script> alert("No haz iniciado sesion") </script>';
    echo '<script> window.location = "index.php"; </script>';
    //header('Location:dashboard.php');
  }

  $ingreso = new Mvc();
  $ingreso -> eliminaVisitaController();

?>