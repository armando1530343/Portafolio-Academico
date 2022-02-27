create database AeroMexico
go
use AeroMexico
go

create table [Tipo de Avion](
	id int primary key identity(1,1),
	capacidad int not null,
	distancia_limite_KM int not null 
)
create table Avion(
	serie char(5) primary key,
	fecha_fabricacion date,
	fecha_compra date,
	fecha_sigServicio date,
	descripcion varchar(50),
	tipo_avion int foreign key references [Tipo de Avion](id) not null
)
create table Empleado(
	id int primary key identity(1,1),
	nombre varchar(30) not null,
	cargo varchar(15) not null,
	fecha_nacimiento date,
	direccion varchar(30),
	fecha_incorporacion date not null
)
create table [Experiencia Laboral de Empleado](
	id int identity(1,1),
	id_empleado int foreign key references Empleado(id) not null,
	primary key(id,id_empleado),
	compañia varchar(30) not null,
	puesto varchar(40) not null,
	fecha_inicio date,
	fecha_termino date
)

create table [Contacto Empleado](
	id int identity(1,1),
	id_empleado int foreign key references Empleado(id) not null,
	primary key(id,id_empleado),
	nombre varchar(30) not null,
	direccion varchar(30),
	correo varchar(30),
	telefono varchar(10),
	parentesco varchar(20)
)
create table Piloto(
	id_empleado int foreign key references Empleado(id) not null,
	primary key(id_empleado)
)
create table Sobrecargo(
	id_empleado int foreign key references Empleado(id) not null,
	primary key(id_empleado)
)
create Table [Programas de Entrenamiento](
	id int primary key identity(1,1),
	nombre varchar(30) not null
)
create table Vuelo(
	id char(4) primary key,
	duracion_minutos int not null,
	dia_semana varchar(10),
	hora_salida time not null,
	tiempo_minutos_salida int,
	hora_llegada time not null,
	tiempo_minutos_arrivo int,
	hora_escala time
)

create table Viaje(
	id_vuelo char(4) foreign key references Vuelo(id) not null,
	fecha date not null,
	estado varchar(30) not null,
	id_avion char(5) foreign key references Avion(serie) not null,
	primary key(id_vuelo, fecha)
)
create table Tripulacion(
	id int primary key identity(1,1),
	id_vuelo char(4) foreign key references Vuelo(id),
	id_avion char(5) foreign key references Avion(serie)
)
alter table Viaje add id_tripulacion int foreign key references Tripulacion(id) not null


create table Pasajeros(
	id int primary key identity(1,1),
	nombre varchar(30) not null,
	genero varchar(10) not null,
	direccion varchar(30) not null,
	telefono varchar(10),
	correo varchar(30),
	nacionalidad varchar(30) not null,
	identificacion varchar(30) not null,
	folio_identificacion varchar(10) not null,
	fecha_nacimiento date
)
create table [Tipo de Boleto](
	id int primary key identity(1,1),
	clase varchar(20) not null,
	precio money not null 
)
create table Boleto(
	id int primary key identity(1,1),
	fecha_compra date not null,
	forma_pago varchar(20) not null,
	tipo_boleto int foreign key references [Tipo de Boleto](id) not null,
	id_vuelo char(4) foreign key references Vuelo(id) not null,
	id_pasajero int foreign key references Pasajeros(id) not null
)
create table Ciudad(
	id int primary key identity(1,1),
	nombre varchar(30) not null,
	estado varchar(30) not null
)

alter table Vuelo add id_origen int foreign key references Ciudad(id) not null,
					  id_destino int foreign key references Ciudad(id) not null,
					  id_escala int foreign key references Ciudad(id)

create table Aeropuerto(
	id int identity(1,1),
	id_ciudad int foreign key references Ciudad(id),
	primary key (id, id_ciudad),
	nombre varchar(40) not null
)
--alter table Aeropuerto alter column nombre varchar(40)
----- N : N ------

create table [Sobrecargo-Entrenamiento](
	id_sobrecargo int foreign key references Sobrecargo(id_empleado) not null,
	id_programa int foreign key references [Programas de Entrenamiento](id) not null,
	primary key (id_sobrecargo, id_programa),
	fecha_inicio date not null,
	fecha_termino date not null
)

create table [Avion-Vuelo](
	id_avion char(5) foreign key references Avion(serie) not null,
	id_vuelo char(4) foreign key references Vuelo(id) not null,
	primary key(id_avion, id_vuelo)
)
create table [Piloto-TipoAvion](
	id_piloto int foreign key references Piloto(id_empleado) not null,
	tipo_avion int foreign key references [Tipo de Avion](id) not null,
	fecha_certificacion date not null,
	primary key(id_piloto, tipo_avion)
)
create table [Tripulacion-Piloto](
	id_tripulacion int foreign key references Tripulacion(id) not null,
	id_piloto int foreign key references Piloto(id_empleado) not null,
	primary key(id_tripulacion, id_piloto),
	cargo varchar(10) not null
)
create table [Tripulacion-Sobrecargo](
	id_tripulacion int foreign key references Tripulacion(id) not null,
	id_sobrecargo int foreign key references Sobrecargo(id_empleado) not null,
	primary key(id_tripulacion, id_sobrecargo)
)
create table [Tripuacion-Pasajero](
	id_tripulacion int foreign key references Tripulacion(id) not null,
	id_pasajero int foreign key references Pasajeros(id) not null,
	primary key(id_tripulacion, id_pasajero)
)