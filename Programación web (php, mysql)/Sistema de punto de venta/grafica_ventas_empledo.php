
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
                $emp = $conexion->query("SELECT * from empleado");

                while($i = $emp->fetch_assoc()){
                    $num = current($conexion->query("SELECT COUNT(*) from venta where id_empleado = ".$i['Id'])->fetch_assoc());
            ?>

                { y: <?php echo "'".$i['nombre']."'"; ?>, a: <?php echo $num; ?> },
            
            <?php } ?>
            
            
        ];
        this.createStackedChart('ventas-empleado', $stckedData1, 'y', ['a'], ['Vendidos'], ['#0E6977']);
            

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