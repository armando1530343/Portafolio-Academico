use AeroMexico

create procedure TripulacionViaje
	@id_vuelo char(4),
	@fecha date 
as begin
	declare @serie char(5)
	declare @capitan varchar(30)
	declare @copiloto varchar(30)
	declare @sob1 varchar(30)
	declare @sob2 varchar(30)
	declare @sob3 varchar(30)
	declare @sob4 varchar(30)
	declare @sob5 varchar(30)
	declare @sob6 varchar(30)
	declare @sob7 varchar(30)
	declare @sob8 varchar(30)
	--declare @sobrecargos table
	set @serie = (select id_avion from Viaje where id_vuelo=@id_vuelo and fecha=@fecha)
	
	set @capitan = (select e.nombre
		from Viaje as v inner join [Tripulacion-Piloto] as tp on v.id_tripulacion=tp.id_tripulacion
						inner join Empleado as e on tp.id_piloto = e.id
		where tp.cargo='Capitan' and v.id_vuelo=@id_vuelo and v.fecha=@fecha)
	
	set @copiloto = (select e.nombre
		from Viaje as v inner join [Tripulacion-Piloto] as tp on v.id_tripulacion=tp.id_tripulacion
						inner join Empleado as e on tp.id_piloto = e.id
		where tp.cargo='Co-Piloto' and v.id_vuelo=@id_vuelo and v.fecha=@fecha)

	set @sob1 = (select t.nombre from
		(select e.nombre as nombre,ROW_NUMBER() over(order by ts.id_tripulacion) as fila
		from Viaje as v inner join [Tripulacion-Sobrecargo] as ts on v.id_tripulacion=ts.id_tripulacion
						inner join Empleado as e on ts.id_sobrecargo = e.id
		where v.id_vuelo=@id_vuelo and v.fecha=@fecha) as t where t.fila=1)
	set @sob2 = (select t.nombre from
		(select e.nombre as nombre,ROW_NUMBER() over(order by ts.id_tripulacion) as fila
		from Viaje as v inner join [Tripulacion-Sobrecargo] as ts on v.id_tripulacion=ts.id_tripulacion
						inner join Empleado as e on ts.id_sobrecargo = e.id
		where v.id_vuelo=@id_vuelo and v.fecha=@fecha) as t where t.fila=2)
	set @sob3 = (select t.nombre from
		(select e.nombre as nombre,ROW_NUMBER() over(order by ts.id_tripulacion) as fila
		from Viaje as v inner join [Tripulacion-Sobrecargo] as ts on v.id_tripulacion=ts.id_tripulacion
						inner join Empleado as e on ts.id_sobrecargo = e.id
		where v.id_vuelo=@id_vuelo and v.fecha=@fecha) as t where t.fila=3)
	set @sob4 = (select t.nombre from
		(select e.nombre as nombre,ROW_NUMBER() over(order by ts.id_tripulacion) as fila
		from Viaje as v inner join [Tripulacion-Sobrecargo] as ts on v.id_tripulacion=ts.id_tripulacion
						inner join Empleado as e on ts.id_sobrecargo = e.id
		where v.id_vuelo=@id_vuelo and v.fecha=@fecha) as t where t.fila=4)
	set @sob5 = (select t.nombre from
		(select e.nombre as nombre,ROW_NUMBER() over(order by ts.id_tripulacion) as fila
		from Viaje as v inner join [Tripulacion-Sobrecargo] as ts on v.id_tripulacion=ts.id_tripulacion
						inner join Empleado as e on ts.id_sobrecargo = e.id
		where v.id_vuelo=@id_vuelo and v.fecha=@fecha) as t where t.fila=5)
	set @sob6 = (select t.nombre from
		(select e.nombre as nombre,ROW_NUMBER() over(order by ts.id_tripulacion) as fila
		from Viaje as v inner join [Tripulacion-Sobrecargo] as ts on v.id_tripulacion=ts.id_tripulacion
						inner join Empleado as e on ts.id_sobrecargo = e.id
		where v.id_vuelo=@id_vuelo and v.fecha=@fecha) as t where t.fila=6)
	set @sob7 = (select t.nombre from
		(select e.nombre as nombre,ROW_NUMBER() over(order by ts.id_tripulacion) as fila
		from Viaje as v inner join [Tripulacion-Sobrecargo] as ts on v.id_tripulacion=ts.id_tripulacion
						inner join Empleado as e on ts.id_sobrecargo = e.id
		where v.id_vuelo=@id_vuelo and v.fecha=@fecha) as t where t.fila=7)
	set @sob8 = (select t.nombre from
		(select e.nombre as nombre,ROW_NUMBER() over(order by ts.id_tripulacion) as fila
		from Viaje as v inner join [Tripulacion-Sobrecargo] as ts on v.id_tripulacion=ts.id_tripulacion
						inner join Empleado as e on ts.id_sobrecargo = e.id
		where v.id_vuelo=@id_vuelo and v.fecha=@fecha) as t where t.fila=8)
	
	select @capitan as Capitan,
		   @copiloto as [Co-Piloto],
		   @sob1 as Sobrecargo1,
		   @sob2 as Sobrecargo2,
		   @sob3 as Sobrecargo3,
		   @sob4 as Sobrecargo4,
		   @sob5 as Sobrecargo5,
		   @sob6 as Sobrecargo6,
		   @sob7 as Sobrecargo7,
		   @sob8 as Sobrecargo8,
		   @serie as [Serie de Avion]

end


exec TripulacionViaje 'AC05','2017-04-16'
exec TripulacionViaje 'AC01','2017-04-20'
