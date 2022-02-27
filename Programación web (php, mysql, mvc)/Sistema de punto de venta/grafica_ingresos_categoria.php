
/**
* Theme: SimpleAdmin Admin Template
* Author: Coderthemes
* Morris Chart
*/

<?php
            include('conexion.php');

            //ventas por empleado
            $numEmpleados = current($conexion->query("SELECT COUNT(*) from empleado")->fetch_assoc());
            $empleado = $conexion->query("SELECT * from empleado");

            
        ?>
<script>

!function($) {
    "use strict";

    var Dashboard = function() {};

    //creates Stacked chart
    Dashboard.prototype.createStackedChart  = function(element, data, xkey, ykeys, labels, lineColors) {
        Morris.Bar({
            element: element,
            data: data,
            xkey: xkey,
            ykeys: ykeys,
            stacked: true,
            labels: labels,
            hideHover: 'auto',
            resize: true, //defaulted to true
            gridLineColor: '#eeeeee',
            barColors: lineColors
        });
    },
    Dashboard.prototype.init = function() {

        //creating Stacked chart
        var $stckedData1  = [

            <?php
                $con = $conexion->query("SELECT categoria.nombre as categoria, SUM(venta.total) as ingresos
                                        from categoria INNER JOIN inventario on categoria.id = inventario.id_categoria
                                        INNER JOIN venta on venta.id_producto = inventario.id_producto GROUP BY categoria.nombre");

                while($i = $con->fetch_assoc()){
                    //$num = current($conexion->query("SELECT COUNT(*) from inventario where id_categoria = ".$i['Id'])->fetch_assoc());
            ?>

                { y: <?php echo "'".$i['categoria']."'"; ?>, a: <?php echo $i['ingresos']; ?> },
            
            <?php } ?>
            
            
        ];
        this.createStackedChart('ingresos-categoria', $stckedData1, 'y', ['a'], ['Ingreso total'], ['#477605']);
            

    },
    //init
    $.Dashboard = new Dashboard, $.Dashboard.Constructor = Dashboard
}(window.jQuery),

//initializing
function($) {
    "use strict";
    $.Dashboard.init();
}(window.jQuery);
</script>