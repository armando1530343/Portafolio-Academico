use AeroMexico

create view Informacion_Contacto as
select e.nombre as Empleado,
	   e.cargo as Cargo,
	   ce.nombre as Contacto,
	   ce.direccion as Direccion_Contacto,
	   ce.correo as Correo_Contacto,
	   ce.telefono as Telefono_Contacto,
	   ce.parentesco as Parentesco_Contacto
from Empleado as e
	inner join [Contacto Empleado] as ce on e.id = ce.id_empleado

select * from Informacion_Contacto
