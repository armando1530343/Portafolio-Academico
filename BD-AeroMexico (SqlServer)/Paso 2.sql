use AeroMexico

--2
create function DatosPiloto(@idPiloto int) 
returns @tabla table(nombre varchar(30), tipo_avion int, certificacion date)
as begin
	insert into @tabla 
	select e.nombre as [Nombre Piloto],
		   pta.tipo_avion as [Tipo de Avion],
		   pta.fecha_certificacion as Certificacion
	from Piloto as p
		inner join [Piloto-TipoAvion] as pta on p.id_empleado = pta.id_piloto
		inner join Empleado as e on p.id_empleado = e.id
	where pta.id_piloto = @idPiloto
	return
end
select * from DatosPiloto(1)
select * from DatosPiloto(4)