import numpy as np
from xml.dom import minidom
from sklearn.cluster import KMeans, AgglomerativeClustering
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
import pandas as pd
import csv
from math import *

meses = ['Ene', 'Feb', 'Mar', 'Abr', 'May', 'Jun', 'Jul', 'Ago', 'Sep', 'Oct', 'Nov', 'Dic']
months = ['01','02','03','04','05','06','07','08','09','10','11','12']
years = ['2011','2012','2013','2014','2015','2016','2017']

#funcion que lee un archivo de texto y crea una lista con sus respectivos datos ya sean cadenas o numeros
def leer_archivo(archivo, tipo):

	#Se lee el archivo con los nombres de las fuerzas policiacas
	file = open(archivo, 'r')
	i = 0
	#se guarda en un arreglo los nombres del archivo
	datos = []
	for line in file:
		nombre = ''
		for c in line:
			if c != "\n":
				nombre += c
		if tipo == 1:
			nombre = int(nombre)
		datos.append(nombre)

	return datos

def kml(archivo):

	doc = minidom.parse('PoliceForce_KML/' + archivo +'.kml')
	kml = doc.getElementsByTagName('kml')[0]
	document = kml.getElementsByTagName('Document')[0]
	placemarks = document.getElementsByTagName('Placemark')[0]
	MultiGeometry = placemarks.getElementsByTagName('MultiGeometry')[0]
	Polygon = MultiGeometry.getElementsByTagName('Polygon')[0]
	outerBoundaryIs = Polygon.getElementsByTagName('outerBoundaryIs')[0]
	LinearRing = outerBoundaryIs.getElementsByTagName('LinearRing')[0]
	coordinates = LinearRing.getElementsByTagName('coordinates')[0].firstChild.data
	coordinates = coordinates.replace(' ', '/')
	coordinates = coordinates.split('/')
	total_coord = len(coordinates)

	for i in range(total_coord):
		coordinates[i] = coordinates[i].split(',')
		coordinates[i][0] = float(coordinates[i][0])
		coordinates[i][1] = float(coordinates[i][1])
		coordinates[i][2] = float(coordinates[i][2])
		#print(coord[0])

	#coordinates = np.array(coordinates)

	return coordinates #max(coordinates[:,0]), max(coordinates[:,1]), min(coordinates[:,0]), min(coordinates[:,1])

policeForce = leer_archivo('policeForce.txt', 0)

#COORDENADAS LATITUD Y LONGITUD
#-------------------------------------------------------------
UBICACION = [] #data1
AREAS = []
i = 0

for police in policeForce:

	coordenadas = kml(police)

	for coord in coordenadas:
		coord.pop()


	coordenadas = np.array(coordenadas)

	latitud_promedio = sum(coordenadas[:,0])/len(coordenadas)
	longitud_primedio = sum(coordenadas[:,1])/len(coordenadas)
	
	UBICACION.append([latitud_promedio, longitud_primedio])


	max_latitud = max(coordenadas[:,0])
	min_latitud = min(coordenadas[:,0])
	max_longitud = max(coordenadas[:,1])
	min_longitud = min(coordenadas[:,1])

	#print(max_latitud,',',min_latitud,',',max_longitud,',',min_longitud)

	area = (max_latitud - min_latitud) * (max_longitud - min_longitud)
	#print(area)
	#print('Area: ', area)
	AREAS.append(area)

#---------------------------------------------------------------
UBICACION = np.array(UBICACION)
print('DATA 1')
total_crimenes = leer_archivo('crimenes_fuerzas.txt', 1)
CRIMENES_AREAS = [] #data2
UBICACION_AREAS = [] #data3

for i in range(len(total_crimenes)):
	CRIMENES_AREAS.append([total_crimenes[i], AREAS[i]])
	UBICACION_AREAS.append([UBICACION[i][0], UBICACION[i][1], AREAS[i]])

CRIMENES_AREAS = np.array(CRIMENES_AREAS)
print('DATA 2')
UBICACION_AREAS = np.array(UBICACION_AREAS)
print('DATA 3')

POLICE_FORCE_CRIME = [] #data4
for i in range(len(policeForce)):
	file = leer_archivo('dataset 4/' + policeForce[i], 1)
	POLICE_FORCE_CRIME.append(file)

POLICE_FORCE_CRIME = np.array(POLICE_FORCE_CRIME)
print('DATA 4')
#print(POLICE_FORCE_CRIME)

with open('datasets/UBICACIONES.csv', 'w', newline='', encoding='utf-8') as data1:
	writer = csv.writer(data1)
	writer.writerows(UBICACION)

with open('datasets/CRIMENES_AREAS.csv', 'w', newline='', encoding='utf-8') as data2:
	writer = csv.writer(data2)
	writer.writerows(CRIMENES_AREAS)

with open('datasets/UBICACIONES_AREAS.csv', 'w', newline='', encoding='utf-8') as data3:
	writer = csv.writer(data3)
	writer.writerows(UBICACION_AREAS)

with open('datasets/REPORTES_TIPOS_CRIMEN.csv', 'w', newline='', encoding='utf-8') as data4:
	writer = csv.writer(data4)
	writer.writerows(POLICE_FORCE_CRIME)

REPORTES_ANUALES = [[0]*7]*42 #data5
REPORTES_MENSUALES = [[0]*84]*42 #data6

REPORTES_ANUALES = np.array(REPORTES_ANUALES)
REPORTES_MENSUALES = np.array(REPORTES_MENSUALES)

a = 0
mes = 0
for y in years:
	for m in months:
		i = 0
		for p in policeForce:
			carpeta = y + '-' + m + '/' + y + '-' + m + '-' + p + '-street.csv'
			archivo = pd.read_csv('CrimesUK_2011_2017/' + carpeta)
			archivo = np.array(archivo)
			
			REPORTES_ANUALES[i][a] += len(archivo[:,0])
			REPORTES_MENSUALES[i][mes] += len(archivo[:,0])

			i+=1
		mes+=1
	a+=1
print('DATA 5')
print('DATA 6')

with open('datasets/REPORTES_ANUALES.csv', 'w', newline='', encoding='utf-8') as data5:
	writer = csv.writer(data5)
	writer.writerows(REPORTES_ANUALES)

with open('datasets/REPORTES_MENSUALES.csv', 'w', newline='', encoding='utf-8') as data6:
	writer = csv.writer(data6)
	writer.writerows(REPORTES_MENSUALES)
