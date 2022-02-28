create database EventosApp

go
use EventosApp
go


create table Administrador(
	Id_admin int primary key identity(1,1),
	Cuenta varchar(30) not null,
	Contraseña varchar(15) not null
)
create table Usuario (
	Id_usuario int primary key identity(1,1),
	Nombre varchar(30) not null,
	Apellido varchar(30) not null,
	Edad int not null,
	Nombre_Usuario varchar(50) not null,
	Contraseña varchar(15) not null,
	Id_admin int foreign key references Administrador(Id_admin)
)
create table Evento(
	Id_evento int primary key identity(1,1),
	Nombre varchar(200) not null,
	Lugar varchar(1000) not null,
	Fecha varchar(100) not null,
	Categoria varchar(30) not null,
	Descripcion varchar(5000),
	Asistentes int not null,
	URL varchar(1000) not null,
	Imagen image not null
)


create table Usuario_Evento(
	Id_usuario int foreign key references Usuario(Id_usuario),
	Id_evento int foreign key references Evento(Id_evento),
	asistir int,
	calificacion int,
	primary key(Id_usuario, Id_evento)
)

insert into Administrador (Cuenta, Contraseña) values ('Admin', 'Admin')