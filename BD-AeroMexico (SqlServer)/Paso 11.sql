use AeroMexico

create procedure ViajesPasajeros
	@documento varchar(30),
	@folio varchar(10)
as begin
	
	select p.id as Id_pasajero,
		   p.nombre as Pasajero,
		   v.id as Vuelo,
		   c1.nombre as Origen,
		   c2.nombre as Destino,
		   v.hora_salida as Salida,
		   v.hora_llegada as Llegada
	from Vuelo as v
		inner join Viaje as vi on v.id = vi.id_vuelo
		inner join [Tripuacion-Pasajero] as tp on vi.id_tripulacion = tp.id_tripulacion
		inner join Pasajeros as p on tp.id_pasajero = p.id
		inner join Ciudad as c1 on v.id_origen = c1.id
		inner join Ciudad as c2 on v.id_destino = c2.id
	where p.identificacion = @documento and p.folio_identificacion = @folio

end

exec ViajesPasajeros 'Pasaporte','028304980'

select * from Pasajeros
select * from Vuelo