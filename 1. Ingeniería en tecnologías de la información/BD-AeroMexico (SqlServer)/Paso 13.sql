use AeroMexico

create procedure [Vuelos por fecha] 
	@fecha date
as begin 
	select v.id_avion as Avion,
		   v.fecha as Fecha,
		   vu.id as Vuelo,
		   c1.nombre as Origen,
		   c2.nombre as Destino
	from Avion as a
		left join Viaje as v on a.serie = v.id_avion
		left join Vuelo as vu on v.id_vuelo = vu.id
		left join Ciudad as c1 on vu.id_origen = c1.id
		left join Ciudad as c2 on vu.id_destino = c2.id	
	where v.fecha = @fecha 
end

exec [Vuelos por fecha] '2017-04-16'

select * from Avion