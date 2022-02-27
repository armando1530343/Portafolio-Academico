use AeroMexico

create procedure _Ciudad 
	@ciudad varchar(30) 
as begin

	select */*v.id as Salir,
		   v2.id as Arivar*/
	from Ciudad as c
		inner join Vuelo as v on c.id = v.id_origen
	where c.nombre = 'Guadalajara'

end

select * from Vuelo
select * from Ciudad
select * from Viaje

