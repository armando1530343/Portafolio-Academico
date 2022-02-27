use AeroMexico

create function ViajesDePiloto(@idPiloto int)
returns @tabla table(piloto int, vuelo char(4), fecha date, serie_avion char(5))
as begin
	insert into @tabla
	select tp.id_piloto as [Id Piloto],
		   v.id_vuelo as Vuelo,
		   v.fecha as Fecha,
		   v.id_avion as [Serie de Avion]
	from Viaje as v
		inner join [Tripulacion-Piloto] as tp on v.id_tripulacion = tp.id_tripulacion
	where tp.id_piloto = @idPiloto
	return
end

select * from ViajesDePiloto(1)
select * from ViajesDePiloto(4)
select * from ViajesDePiloto(7)