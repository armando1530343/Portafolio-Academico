use AeroMexico

create view VistaSobrecargo as 
select s.id_empleado as Id_sobrecargo,
	   ex.compañia as [Experiencia Laboral],
	   ex.puesto as Puesto,
	   ex.fecha_inicio as [Inicio Labor],
	   ex.fecha_termino as [Termino Labor],
	   pe.nombre as Programa,
	   se.fecha_inicio as [Inicio Programa],
	   se.fecha_termino as [Termino Programa]
from Empleado as e
	inner join Sobrecargo as s on e.id = s.id_empleado
	inner join [Experiencia Laboral de Empleado] as ex on s.id_empleado = ex.id_empleado
	inner join [Sobrecargo-Entrenamiento] as se on ex.id_empleado = se.id_sobrecargo
	inner join [Programas de Entrenamiento] as pe on se.id_programa = pe.id 

select * from VistaSobrecargo

select * from [Experiencia Laboral de Empleado]
select * from [Programas de Entrenamiento]
select * from [Sobrecargo-Entrenamiento]
select * from Sobrecargo