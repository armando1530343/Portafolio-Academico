 <?php 

 	if(!isset($_SESSION['validar'])){

		echo '<script> alert("No haz iniciado sesion") </script>';
		echo '<script> window.location = "index.php"; </script>';
 		//header('Location:dashboard.php');
 	}

	$mvc = new MvcController();


  ?>

  <section class="content">
    <div class="container-fluid">
    	<?php 
    	if(isset($_GET['modifica'])){
    		if($_GET['modifica'] == 'success'){
    			echo '	<div class="alert alert-success alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-check"></i>Correcto !</h5>
		                  Se modificó el producto correctamente
		                </div>';
    		}
    		else if($_GET['modifica'] == 'error'){
    			echo '	<div class="alert alert-danger alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-ban"></i> Error!</h5>
		                  No se pudo guardar el producto
		                </div>';
    		}
    		else{
    			echo '	<div class="alert alert-warning alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-warning"></i> Incorrecto!</h5>
		                  El codigo de producto ingresado ya existe en la tienda.
		                </div>';
    		}
    	}
    	if(isset($_GET['agrega_stock'])){
    		if($_GET['agrega_stock'] == 'success' || $_GET['elimina_stock'] == 'success'){
    			echo '	<div class="alert alert-success alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-check"></i>Correcto !</h5>
		                  Se actualizo el stock del producto
		                </div>';
    		}
    		else if($_GET['agrega_stock'] == 'error'){
    			echo '	<div class="alert alert-danger alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-ban"></i> Error!</h5>
		                  No se pudo actualizar el stock
		                </div>';
    		}
    	}
    	if(isset($_GET['elimina_stock'])){
    		if($_GET['elimina_stock'] == 'success'){
    			echo '	<div class="alert alert-success alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-check"></i>Correcto !</h5>
		                  Se actualizo el stock del producto
		                </div>';
    		}
    		else if($_GET['elimina_stock'] == 'error'){
    			echo '	<div class="alert alert-danger alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-ban"></i> Error!</h5>
		                  No se pudo actualizar el stock
		                </div>';
    		}
    		else{
    			echo '	<div class="alert alert-warning alert-dismissible">
		                  <button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>
		                  <h5><i class="icon fa fa-warning"></i> Incorrecto!</h5>
		                  La cantidad de stock a eliminar sobrepasa el limite.
		                </div>';
    		}
    	}


    	if(isset($_POST['elimina_stock'])){
    		echo '<script> window.location = "index.php?action=detalles_producto&id='.$_GET['id'].'&codigo='.$_GET['codigo'].'&form=elimina_stock&cantidad='.$_POST['cantidad'].'&ref='.$_POST['referencia'].'"; </script>';
    	}

    	?>
    	<div class="row">
    		<div class="col-sm-12">
			  	<div class="card card-info">	
		          <div class="card-header">
		            <h3 class="card-title">Detalles de Producto</h3>
		          </div>
		          <div class="row">
		          	  <div class="col-sm-5" align="center">
		          	  	<div class="row" style="padding: 30px;">
		          	  		<div class="col-sm-6">
		          	  			<img src="package.jpg" width="150">	
		          	  		</div>
		          	  		<div class="col-sm-6" style="padding: 20px;">
		          	  			<a href="index.php?action=detalles_producto&id=<?php echo $_GET['id']; ?>&codigo=<?php echo $_GET['codigo']; ?>&form=stock"><button <?php if(isset($_GET['form'])){echo 'disabled';}?> class="btn btn-success">Agregar a Stock</button></a>
		          	  			<br><br>
				              	<a href="index.php?action=detalles_producto&id=<?php echo $_GET['id']; ?>&codigo=<?php echo $_GET['codigo']; ?>&form=elimina_stock"><button <?php if(isset($_GET['form'])){echo 'disabled';}?> class="btn btn-danger">Eliminar de Stock</button></a>	
		          	  		</div>
		          	  		
		          	  	</div>

			            <br>      
			              
			            <div class="card card-info" style="width: 80%;">
			             	<?php 
				            if(isset($_GET['form'])){
				            	if($_GET['form'] == 'stock'){?>
				            		<div class="card-header" style="background-color: gray;">
							            <h3 class="card-title">Agregar Stock</h3>
							        </div>
						            <form method="post">
						            	<?php 
						            	$mvc -> agregarStockController();
						            	$mvc -> registroStockController();
						            	 ?>
						            </form><?php
				            	}
				            	else if($_GET['form'] == 'elimina_stock' && !isset($_GET['cantidad'])){?>
				            		<div class="card-header" style="background-color: gray;">
							            <h3 class="card-title">Eliminar Stock</h3>
							        </div>
						            <form method="post">
						            	<?php 
						            	$mvc -> formEliminaStockController();
						            	//$mvc -> registroStockController();
						            	 ?>
						            </form><?php
				            	}
				            	else if($_GET['form'] == 'elimina_producto' || isset($_GET['cantidad'])){?>
				            		<div class="card-header" style="background-color: red;">
							            <h3 class="card-title">Confirmar Contraseña de Usuario</h3>
							        </div>
						            <form method="post">
						            	<?php 
						            	$mvc -> confirmaEliminarController();
						            	if($_GET['form'] == 'elimina_producto'){
						            		$mvc -> borrarProductoController();
						            	}
						            	else if(isset($_GET['cantidad'])){
						            		$mvc -> eliminaStockController();
						            	}

						            	 ?>
						            </form><?php
				            	}

				            }
				            ?>	  	
					        
				        </div>
				        
					  </div>
			          <div class="col-sm-7">
				          <!-- /.card-header -->
				          <!-- form start -->
				          <form class="form-horizontal" style="text-align: center;" method="post">
				            <?php 

				            	$mvc -> detallesProductosController();
				            	

				             ?>
				            <!-- /.card-footer -->
				          </form>
				      </div>

				  </div>
			    </div>
		    </div>
		</div>
		<div class="card-info">
			<div class="card-header" style="background-color: black;">
				<h3 class="card-title">Historial de Inventario</h3>
			</div>
			<div class="card-body">
		        <table id="example1" class="table table-bordered table-striped">
		          <thead>
		          <tr>
		          	<th>Fecha</th>
		          	<th>Hora</th>
		            <th>Descripcion</th>
		            <th>Referencia</th>
		            <th>Total</th>
		          </tr>
		          </thead>
		          <tbody>
		          <?php 

		          $mvc -> vistaHistorialController(); 

		         ?> 
		          
		          </tbody>
		          
		        </table>
		      </div>
		</div>
	  <!-- /.row -->
      <!-- Main row -->
      <!-- /.row (main row) -->
    </div><!-- /.container-fluid -->
  </section>