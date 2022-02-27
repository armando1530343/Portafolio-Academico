use AeroMexico

create view VistaViaje as
select v.id_vuelo,
	   t.id_pasajero,
	   p.nombre,
	   p.fecha_nacimiento,
	   p.folio_identificacion,
	   p.genero,
	   p.direccion,
	   p.nacionalidad,
	   p.correo 
from Pasajeros p
	inner join [Tripuacion-Pasajero] t on t.id_pasajero=p.id
	inner join viaje v on v.id_tripulacion=t.id_tripulacion
 
select * from VistaViaje
