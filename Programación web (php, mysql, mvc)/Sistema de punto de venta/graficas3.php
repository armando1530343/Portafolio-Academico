
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
                $cat = $conexion->query("SELECT * from categoria");

                while($i = $cat->fetch_assoc()){
                    $num = current($conexion->query("SELECT COUNT(*) from inventario where id_categoria = ".$i['id'])->fetch_assoc());
            ?>

                { y: <?php echo "'".$i['nombre']."'"; ?>, a: <?php echo $num; ?> },
            
            <?php } ?>
            
            
        ];
        this.createStackedChart('categoria-producto', $stckedData1, 'y', ['a'], ['Productos'], ['#C0891F']);
            

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