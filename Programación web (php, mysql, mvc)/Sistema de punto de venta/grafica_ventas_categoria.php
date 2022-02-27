
/**
* Theme: SimpleAdmin Admin Template
* Author: Coderthemes
* Morris Chart
*/

<?php
    include('conexion.php');
    
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
                $con = $conexion->query("SELECT categoria.nombre as categoria, COUNT(*) as numVentas
                                        from categoria INNER JOIN inventario on categoria.id = inventario.id_categoria
                                        INNER JOIN venta on venta.id_producto = inventario.id_producto GROUP BY categoria.nombre");

                while($i = $con->fetch_assoc()){
                    //$num = current($conexion->query("SELECT COUNT(*) from inventario where id_categoria = ".$i['Id'])->fetch_assoc());
            ?>

                { y: <?php echo "'".$i['categoria']."'"; ?>, a: <?php echo $i['numVentas']; ?> },
            
            <?php } ?>
            
            
        ];
        this.createStackedChart('ventas-categoria', $stckedData1, 'y', ['a'], ['Ventas'], ['#BB36CF']);
            

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