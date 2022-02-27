
/**
* Theme: SimpleAdmin Admin Template
* Author: Coderthemes
* Morris Chart
*/

<?php
            include('conexion.php');

            //$dias = array('domingo','Lunes','Martes','Miercoles', 'Jueves', 'Viernes', 'Sabado');
            $meses = array('Enero','Febrero','Marzo','Abril', 'Mayo', 'Junio', 'Julio','Agosto','Septiembre','Octubre','Noviembre', 'Diciembre');

            $mes = date('m')-1;
            $ventasMes = array();

            //total de ventas mensuales
            $nov = current($conexion->query("SELECT COUNT(*) FROM venta Where MONTH(fecha) = 11")->fetch_assoc());
            $oct = current($conexion->query("SELECT COUNT(*) FROM venta Where MONTH(fecha) = 10")->fetch_assoc());
            $sep = current($conexion->query("SELECT COUNT(*) FROM venta Where MONTH(fecha) = 9")->fetch_assoc());
            $ago = current($conexion->query("SELECT COUNT(*) FROM venta Where MONTH(fecha) = 8")->fetch_assoc());
            $jul = current($conexion->query("SELECT COUNT(*) FROM venta Where MONTH(fecha) = 7")->fetch_assoc());
            $jun = current($conexion->query("SELECT COUNT(*) FROM venta Where MONTH(fecha) = 6")->fetch_assoc());

            //total de ingresos por mes validando que no regrese un valor nulo
            $nov2 = current($conexion->query("SELECT SUM(total) FROM venta Where MONTH(fecha) = 11")->fetch_assoc());
            if($nov2 == NULL){$nov2 = 0;}
            $oct2 = current($conexion->query("SELECT SUM(total) FROM venta Where MONTH(fecha) = 10")->fetch_assoc());
            if($oct2 == NULL){$oct2 = 0;}
            $sep2 = current($conexion->query("SELECT SUM(total) FROM venta Where MONTH(fecha) = 9")->fetch_assoc());
            if($sep2 == NULL){$sep2 = 0;}
            $ago2 = current($conexion->query("SELECT SUM(total) FROM venta Where MONTH(fecha) = 8")->fetch_assoc());
            if($ago2 == NULL){$ago2 = 0;}
            $jul2 = current($conexion->query("SELECT SUM(total) FROM venta Where MONTH(fecha) = 7")->fetch_assoc());
            if($jul2 == NULL){$jul2 = 0;}
            $jun2 = current($conexion->query("SELECT SUM(total) FROM venta Where MONTH(fecha) = 6")->fetch_assoc());
            if($jun2 == NULL){$jun2 = 0;}

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

        //var  dias = ['Domingo', 'Lunes', 'Martes', 'Miercoles', 'Jueves', 'Vienes', 'Sabado'];
        //var  Meses = ['Domingo', 'Lunes', 'Martes', 'Miercoles', 'Jueves', 'Vienes', 'Sabado'];
        

        //creating Stacked chart
        var $stckedData1  = [
            { y: 'Junio', a: <?php echo $jun; ?> },
            { y: 'Julio', a: <?php echo $jul; ?> },
            { y: 'Agosto', a: <?php echo $ago; ?> },
            { y: 'Septiembre', a: <?php echo $sep; ?> },
            { y: 'Octubre', a: <?php echo $oct; ?> },
            { y: 'Noviembre', a: <?php echo $nov; ?> }
        ];
        this.createStackedChart('ventas-mes', $stckedData1, 'y', ['a'], ['Ventas'], ['#358047']);
        
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