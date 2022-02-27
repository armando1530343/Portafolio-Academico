use AeroMexico


create function HorasPiloto(@id int) returns int
as begin 
	declare @horas int
	
	set @horas = (select sum(vu.duracion_minutos) as Minutos
	from [Tripulacion-Piloto] as tp
		inner join Viaje as vi on tp.id_tripulacion = vi.id_tripulacion
		inner join Vuelo as vu on vi.id_vuelo = vu.id
	where tp.id_piloto = @id)
	return @horas/60
end

select dbo.HorasPiloto(1) as [Total de Horas de Vuelo]

select * from Piloto
select * from Vuelo
select * from [Tripulacion-Piloto]