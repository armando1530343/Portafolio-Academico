use AeroMexico

insert into [Tipo de Avion] values (277, 3500),(198, 4000),(350, 7000),(400, 11000),(450, 11500)

insert into Avion values
	('ABC01','20050404','20060505','20170415','AeroMexico1',1),
	('ABC02','20030425','20030812','20170421','AeroMexico2',2),
	('ABC03','20101214','20110115','20170522','AeroMexico3',3),
	('ABC04','20080413','20081022','20170519','AeroMexico4',4),
	('ABC05','20071102','20110221','20170426','AeroMexico5',5),
	('ABC06','20020112','20020624','20170513','AeroMexico6',2),
	('ABC07','20031031','20040313','20170423','AeroMexico7',2),
	('ABC08','20071124','20100310','20170527','AeroMexico8',3),
	('ABC09','20120519','20130221','20170428','AeroMexico9',1),
	('ABC10','20130513','20141211','20170417','AeroMexico10',4)

insert into Empleado values
	('Gabriel Marquez','Piloto','19700613','direccion piloto 1','20100419'),
	('Javier Lopez','Sobrecargo','19800918','direccion Sobrecargo 1','20110119'),
	('Monica Guevara','Sobrecargo','19751015','direccion Sobrecargo 2','20130401'),
	('Carlos Perez','Piloto','19700613','direccion piloto 2','20100419'),
	('Perla Gomez','Sobrecargo','19791212','direccion Sobrecargo 3','20080314'),
	('Luis Sanchez','Piloto','19831120','direccion piloto 3','20090309'),
	('Angel Ruiz','Piloto','19650613','direccion piloto 4','20010823'),
	('Jose Reyes','Sobrecargo','19760717','direccion Sobrecargo 4','20060528'),
	('Daniel Castro','Piloto','19700613','direccion piloto 5','20100419'),
	('Ernesto Perez','Sobrecargo','19850613','direccion Sobrecargo 5','20131201'),
	('Daniel Quintero','Sobrecargo','19840503','direccion Sobrecargo 6','20101201'),
	('Josue Parras','Sobrecargo','19831013','direccion Sobrecargo 7','20111201'),
	('Cesar Luna','Sobrecargo','19800115','direccion Sobrecargo 8','20121201')

insert into [Experiencia Laboral de Empleado] values
	(1,'Empresa 1','Asistente personal','20051024','20090119'),
	(7,'Empresa 2','Auxiliar de servicios','19900917','19990202'),
	(3,'Empresa 3','Consultor de comunicación','20091203','20100824'),
	(2,'Empresa 4','Consultoría ambiental','20000607','20111009'),
	(4,'Empresa 5','Director comercial','20001118','20090326'),
	(5,'Empresa 6','Gestión deportiva','20041010','20080110'),
	(1,'Empresa 7','Empresario','20030118','20050907'),
	(8,'Empresa 8','Secretario (administración)','20001016','20051211'),
	(9,'Empresa 9','Asistente personal','20080101','20100330'),
	(10,'Empresa 10','Asistente personal','20070310','20121230')

insert into [Contacto Empleado] values
	(1,'Armando Hernandez','Direccion Contacto 1','armandohdz@gmail.com','8345492847','Hijo'),
	(2,'Luis Muñiz','Direccion Contacto 2','luizmuniz@gmail.com','8347389123','Padre'),
	(3,'Alejandro Hernandez','Direccion Contacto 3','alehdz@gmail.com','8347366489','Tio'),
	(4,'Yulissa Hernandez','Direccion Contacto 4','yulihdz@gmail.com','8349923471','Madre'),
	(5,'Sergio Perez','Direccion Contacto 5','sergioprz@gmail.com','8349029345','Abuelo'),
	(6,'Ricardo Martinez','Direccion Contacto 6','ricMtz@gmail.com','8347656478','Hijo'),
	(7,'Sofia Lopez','Direccion Contacto 7','sofiLopez@gmail.com','8348743434','Hermana'),
	(8,'Brenda Carreon','Direccion Contacto 8','bren_carr@gmail.com','8340101023','Tia'),
	(9,'Karina Cruz','Direccion Contacto 9','karinaCruz@gmail.com','8348456789','Mama'),
	(10,'Vanessa Guevara','Direccion Contacto 10','Vane_guev@gmail.com','8341123234','Mama')

insert into Piloto values
(1),(4),(6),(7),(9)

insert into Sobrecargo values
(2),(3),(5),(8),(10),(11),(12),(13)

insert into [Programas de Entrenamiento] values
('Programa ENT01'),('Programa ENT02'),('Programa ENT03')

insert into [Sobrecargo-Entrenamiento] values 
(2,1,'20100110','20101030'),(2,3,'20100110','20101030'),
(3,1,'20100516','20111130'),(3,2,'20100516','20111130'),(3,3,'20100516','20111130'),
(5,2,'20060419','20080130'),
(8,2,'20041010','20060420'),(8,3,'20041010','20060420'),
(10,1,'20110504','20130925'),
(11,3,'20110310','20120415'),
(12,1,'20120504','20120925'),(12,2,'20120504','20120925'),
(13,2,'20130504','20140821')


insert into Ciudad values
('Monterrey','Nuevo Leon'),('Cd. de Mexico','Mexico'),('Guadalajara','Jalisco'),('Cancun','Quintana Roo'),('Puerto Vallarta','Jalisco'),
('Acapulco','Guerrero'),('Mérida','Yucatán'),('Tijuana','Baja California'),('Aguascalientes','Aguascalientes'),('Chihuahua','Chihuahua')

insert into Vuelo values
('AC01', 200, 'Lunes', '09:00',3,'12:20',2,'10:40',1,2,9),
('AC02', 150, 'Martes', '10:20',4,'12:50',3,'11:30',3,7,6)
insert into Vuelo (id, duracion_minutos, dia_semana, hora_salida, tiempo_minutos_salida, hora_llegada, tiempo_minutos_arrivo, id_origen, id_destino) values
('AC03', 75, 'Jueves', '08:30', 5, '9:45', 6, 9, 6),
('AC04', 124, 'Lunes', '17:00',4, '19:04',3, 10, 8),
('AC05', 146, 'Viernes', '16:35',2, '19:01',2, 4, 3)
insert into Vuelo values
('AC06', 137, 'Domingo', '13:00',2,'15:17',3,'14:00',5,8,10)
insert into Vuelo (id, duracion_minutos, dia_semana, hora_salida, tiempo_minutos_salida, hora_llegada, tiempo_minutos_arrivo, id_origen, id_destino) values
('AC07', 100, 'Sabado', '20:15',3, '21:55',5, 6, 9)
insert into Vuelo (id, duracion_minutos, dia_semana, hora_salida, tiempo_minutos_salida, hora_llegada, tiempo_minutos_arrivo, id_origen, id_destino) values
('AC08', 123, 'Jueves', '09:00', 5, '11:03', 6, 1, 2),
('AC09', 120, 'Lunes', '17:00',4, '19:00',3, 4, 3)

insert into Tripulacion values
('AC01','ABC02'),('AC01','ABC05'),('AC02','ABC02'),('AC02','ABC04'),
('AC03','ABC03'),('AC04','ABC01'),('AC05','ABC05')

insert into Viaje values 
('AC01', '20170420', 'Programado', 'ABC02', 1),
('AC02', '20170419', 'Demorado', 'ABC02', 3),
('AC03', '20170418', 'Por Despegar', 'ABC03', 5),
('AC04', '20170416', 'En Transito', 'ABC01', 6),
('AC05', '20170416', 'Concluido', 'ABC05', 7), 
('AC06', '20170420', 'En Transito', 'ABC04', 2),
('AC07', '20170422', 'Programado', 'ABC03', 4),
('AC08', '20170420', 'En Transito', 'ABC05', 3),
('AC09', '20170421', 'Programado', 'ABC01', 6)

insert into Pasajeros values
('Armando Hernandez','Masculino','Direccion Pasajero 1','8344563791','armhdz@gmail.com','Mexicana','Credencial','9238749821','19970708'),
('Cristian Echartea','Masculino','Direccion Pasajero 2','8349843576','criech@gmail.com','Mexicana','Pasaporte','78263482','19960412'),
('Angela Carrizales','Femenino','Direccion Pasajero 3','8347263123','angcarr@gmail.com','Mexicana','Credencial','09283048','19900323'),
('Brian Becerra','Masculino','Direccion Pasajero 4','8348787453','bribec@gmail.com','Mexicana','Pasaporte','028304980','19921223'),
('Isamar Moreno','Femenino','Direccion Pasajero 5','8349012110','isamor@gmail.com','Mexicana','Pasaporte','179238791','19940102'),
('David Tovias','Masculino','Direccion Pasajero 6','8349345109','davtov@gmail.com','Mexicana','Credencial','20830498','19950908'),
('Josue Coronado','Masculino','Direccion Pasajero 7','8340909435','joscor@gmail.com','Mexicana','Pasaporte','82638746','19901130'),
('Linda Teran','Femenino','Direccion Pasajero 8','8347345123','linter@gmail.com','Mexicana','Credencial','91782739','19970325'),
('Ariana Hernandez','Femenino','Direccion Pasajero 9','8349876768','ariher@gmail.com','Mexicana','Credencial','76571523','19920618'),
('Gabriela Robles','Femenino','Direccion Pasajero 10','8340012014','gabrob@gmail.com','Mexicana','Pasaporte','0982093840','19990515'),
('Luis Torres','Masculino','Direccion Pasajero 11','8341890198','luistor@gmail.com','Mexicana','Pasaporte','91279398','19921209'),
('Jessica Sanchez','Femenino','Direccion Pasajero 12','8341231200','jessan@gmail.com','Mexicana','Pasaporte','68127638','19970405'),
('Rodrigo Rojas','Masculino','Direccion Pasajero 13','8346412068','rorro@gmail.com','Mexicana','Credencial','927934879','19931031'),
('Diego Lumbreras','Masculino','Direccion Pasajero 14','8349894509','padilla@gmail.com','Mexicana','Pasaporte','6634762534','19980413'),
('Alejandra Carrizales','Femenino','Direccion Pasajero 15','8345468712','ascar@gmail.com','Mexicana','Credencial','09802384','19960728')


insert into [Tipo de Boleto] values
('Primera',5500),('Económica',4500),('Premium',3900),('Negocios',4200),('Turista',2300)

insert into Boleto values
('20170419','Tarjeta de Credito',2,'AC01',1),
('20170419','Tarjeta de Credito',5,'AC01',2),
('20170419','Tarjeta de Credito',1,'AC01',3),
('20170418','Tarjeta de Credito',3,'AC02',4),
('20170418','Tarjeta de Credito',3,'AC02',5),
('20170418','Tarjeta de Credito',4,'AC02',6),
('20170417','Tarjeta de Credito',2,'AC03',7),
('20170417','Tarjeta de Credito',3,'AC03',8),
('20170417','Tarjeta de Credito',5,'AC03',9),
('20170415','Tarjeta de Credito',1,'AC04',10),
('20170415','Tarjeta de Credito',1,'AC04',11),
('20170415','Tarjeta de Credito',3,'AC04',12),
('20170415','Tarjeta de Credito',4,'AC05',13),
('20170415','Tarjeta de Credito',1,'AC05',14),
('20170415','Tarjeta de Credito',5,'AC05',15)

insert into Aeropuerto values
(1,'Aeropuerto 1 Monterrey'),
(1,'Aeropuerto 2 Monterrey'),
(2,'Aeropuerto 1 Cd. de Mexico'),
(2,'Aeropuerto 2 Cd. de Mexico'),
(3,'Aeropuerto 1 Guadalajara'),
(3,'Aeropuerto 2 Guadalajara'),
(4,'Aeropuerto 1 Cancun'),
(4,'Aeropuerto 2 Cancun'),
(5,'Aeropuerto 1 Puerto Vallarta'),
(5,'Aeropuerto 2 Puerto Vallarta'),
(6,'Aeropuerto 1 Acapulco'),
(6,'Aeropuerto 2 Acapulco'),
(7,'Aeropuerto 1 Mérida'),
(7,'Aeropuerto 2 Mérida'),
(8,'Aeropuerto 1 Tijuana'),
(8,'Aeropuerto 2 Tijuana'),
(9,'Aeropuerto 1 Aguascalietes'),
(9,'Aeropuerto 2 Aguascalietes'),
(10,'Aeropuerto 1 Chihuahua'),
(10,'Aeropuerto 2 Chihuahua')

insert into [Avion-Vuelo] values
('ABC01','AC04'),
('ABC02','AC01'),
('ABC02','AC02'),
('ABC03','AC03'),
('ABC05','AC05')

insert into [Piloto-TipoAvion] values
(1,2,'20100520'),
(1,4,'20100723'),
(4,5,'20101021'),
(4,3,'20100614'),
(4,1,'20100824'),
(7,1,'20010920'),
(9,4,'20110518'),
(9,5,'20100915')


insert into [Tripulacion-Piloto] values
(1,4,'Capitan'), (1,9,'Co-Piloto'),
(2,6,'Capitan'), (2,7,'Co-Piloto'),
(3,1,'Capitan'), (3,7,'Co-Piloto'),
(4,1,'Capitan'), (4,6,'Co-Piloto'),
(5,6,'Capitan'), (5,9,'Co-Piloto'),
(6,7,'Capitan'), (6,1,'Co-Piloto'),
(7,4,'Capitan'), (7,6,'Co-Piloto')

insert into [Tripulacion-Sobrecargo] values
(1,2),(1,3),(1,10),(1,8),(1,12),
(2,3),(2,5),(2,11),(2,13),
(3,2),(3,5),(3,8),(3,10),(3,11),(3,12),
(4,3),(4,5),(4,8),
(5,2),(5,3),(5,5),(5,8),(5,10),(5,11),(5,12),(5,13),
(6,10),(6,3),(6,8),(6,11),
(7,2),(7,3),(7,11),(7,12),(7,13),(7,8),(7,10)

insert into [Tripuacion-Pasajero] values
(1,1),(1,2),
(2,3),
(3,4),(3,5),(3,6),
(5,7),(5,8),(5,9),
(6,10),(6,11),(6,12),
(7,13),(7,14),(7,15)
