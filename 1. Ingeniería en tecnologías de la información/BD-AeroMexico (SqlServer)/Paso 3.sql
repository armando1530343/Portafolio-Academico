use AeroMexico

create view Vista_Avion as
select a.serie as Serie_Avion,
	   T.id as [Tipo de Avion],
	   a.descripcion as Descripcion,
	   T.capacidad as Capacidad,
	   T.distancia_limite_KM as [Distancia Limite],
	   a.fecha_fabricacion as [Fecha de Fabricacion],
	   a.fecha_compra as [Fecha de Compra],
	   a.fecha_sigServicio as [Siguiente Servicio]
from Avion a
inner join [Tipo de Avion] T on T.id=a.tipo_avion

select * from Vista_Avion