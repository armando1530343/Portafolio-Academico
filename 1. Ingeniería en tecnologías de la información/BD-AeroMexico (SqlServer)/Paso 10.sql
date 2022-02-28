use AeroMexico

create procedure [Viajes Programados]
	@origen int,
	@destino int,
	@fecha date
as begin
	declare @pasajeros int

	select max(t.vuelo) as Vuelo, 
		   max(t.fecha) as Fecha,
		   max(t.avion) as Avion, 
		   max(t.origen) as Origen,
		   max(t.destino) as Destino, 
		   max(t.salida) as Hra_Salida, 
		   max(t.llegada) as Hra_Llegada,
		   max(t.capacidad) as Capacidad_avion,
		   count(t.vuelo) [Numero de Pasajeros],
		   (max(t.capacidad)-count(t.vuelo)) as [Asientos Disponibles] from
	(select vi.id_vuelo as vuelo, vi.fecha as fecha, vi.id_avion as avion, vu.id_origen as origen, vu.id_destino as destino,
		    vu.hora_salida as salida, vu.hora_llegada as llegada, ta.capacidad as capacidad, tp.id_pasajero as pasajero
	from Viaje as vi
		inner join Vuelo as vu on vi.id_vuelo = vu.id
		inner join Avion as av on vi.id_avion = av.serie
		inner join [Tipo de Avion] as ta on av.tipo_avion = ta.id
		inner join [Tripuacion-Pasajero] as tp on vi.id_tripulacion = tp.id_tripulacion
	where vu.id_origen=@origen and vu.id_destino=@destino and vi.fecha=@fecha) as t
	group by t.vuelo

end

exec [Viajes Programados] 3,7,'2017-04-19'

select * from Viaje
select * from Vuelo
select * from [Tipo de Avion]
select * from Avion
select * from [Tripuacion-Pasajero]