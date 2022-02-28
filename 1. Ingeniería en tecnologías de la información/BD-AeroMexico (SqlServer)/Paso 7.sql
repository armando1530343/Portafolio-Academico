use AeroMexico


create procedure CD_Origen
	@id_vuelo char(4)
as begin
	
	select c1.nombre as Origen,
		   c2.nombre as Destino,
		   c3.nombre as CD_Escala,
		   v.tiempo_minutos_arrivo as [Tiempo de Aterrisaje(min)],
		   v.tiempo_minutos_salida as [Tiempo de Despegue(min)]
	from Vuelo as v
		left join Ciudad as c1 on v.id_origen = c1.id
		left join Ciudad as c2 on v.id_destino = c2.id
		left join Ciudad as c3 on v.id_escala = c3.id
	where v.id = @id_vuelo

end

select * from Vuelo

exec CD_Origen 'AC07'
exec CD_Origen 'AC02'
