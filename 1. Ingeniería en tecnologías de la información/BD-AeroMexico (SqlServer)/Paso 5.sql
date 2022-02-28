use AeroMexico

create view VistaAeropuerto as
select c.nombre Ciudad,
	   c.Estado,
	   a.nombre Aeropuerto 
from Ciudad c
	inner join Aeropuerto a on a.id_ciudad=c.id 

select * from VistaAeropuerto
