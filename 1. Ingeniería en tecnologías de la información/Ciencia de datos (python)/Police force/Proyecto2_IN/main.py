import csv
import pandas as pd
from pandas.plotting import scatter_matrix
import numpy as np
import matplotlib.pyplot as plt
from tabulate import tabulate
import plotly.plotly as py
import plotly.graph_objs as go
from xml.dom import minidom
from scipy.stats import spearmanr, pearsonr
from sklearn.metrics import mean_squared_error
from unipath import Path
from math import *

meses = ['Ene', 'Feb', 'Mar', 'Abr', 'May', 'Jun', 'Jul', 'Ago', 'Sep', 'Oct', 'Nov', 'Dic']
months = ['01','02','03','04','05','06','07','08','09','10','11','12']
years = ['2011','2012','2013','2014','2015','2016','2017']


#<<------IR A LA PARTE FINAL DEL SCRIPT PARA LLAMAR A LAS FUNCIONES QUE GENERAN CADA RESPUESTA------->>
#<< ---- LAS FUNCIONES ESTAN INICIALMENTE COMENTADAS ---- >>
#<< ---- SE DEBERAN DESCOMENTAR PARA GENERAR LOS RESULTADOS REQUERIDOS ---- >>



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

def read_data(file):
	dataset = []
	file = pd.read_csv(file + '.csv')
	x = []
	for f in file.columns:
		x.append(float(f))
	dataset.append(x)
	file = np.array(file)
	for f in file: dataset.append(f)
	dataset = np.array(dataset)

	return dataset


#funcion para leer archivos kml
def kml(archivo):
	from xml.dom import minidom

	doc = minidom.parse('../PoliceForce_KML/' + archivo +'.kml')
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

	coordinates = np.array(coordinates)

	return max(coordinates[:,0]), max(coordinates[:,1]), min(coordinates[:,0]), min(coordinates[:,1])


policeForce = leer_archivo('policeForce.txt', 0)

archivo = pd.read_csv('../CrimesUK_2011_2017/2017-12/2017-12-lincolnshire-street.csv')
archivo = np.array(archivo)

#funcion que crea un arreglo con los nombres de los tipos de crimenes
def tiposCrimen():
	TIPOS_CRIMEN = []
	for y in years:
		print(y)
		for m in months:
			print(m)
			for p in policeForce:
				carpeta = y + '-' + m + '/' + y + '-' + m + '-' + p + '-street.csv'
				archivo = pd.read_csv('../CrimesUK_2011_2017/' + carpeta)
				archivo = np.array(archivo)

				columna_crimen = list(archivo[:,9])
				for t in columna_crimen:
					if t not in TIPOS_CRIMEN:
						TIPOS_CRIMEN.append(t)

	datos = open('tiposCrimen.txt','w')
	for t in TIPOS_CRIMEN:
		datos.write(t + '\n')

	datos.close()

tipos_crimen = leer_archivo('tiposCrimen.txt', 0)


#RESPUESTA DE LA PREGUNTA 1-------------------------------------------------
def respuesta1():
	datos1 = open('respuesta1.txt','w')
	datos2 = open('respuesta2.txt','w')
	datos5 = open('respuesta5.txt','w')
	datos6 = open('respuesta6.txt','w')
	NUMERO_CRIMENES_TOTAL = 0
	
	NUMERO_CRIMENES_POLICE = []
	for i in range(42): NUMERO_CRIMENES_POLICE.append(0)

	NUMERO_CRIMENES_TIPO = []
	for i in range(len(tipos_crimen)): NUMERO_CRIMENES_TIPO.append(0)

	POLICE_FORCE_CRIME = []	

	for i in range(len(policeForce)):
		CRIME = []
		for j in range(len(tipos_crimen)):
			CRIME.append(0)
		POLICE_FORCE_CRIME.append(CRIME)

	MONTH_CRIME = []	

	for i in range(84):
		CRIME = []
		for j in range(len(tipos_crimen)):
			CRIME.append(0)
		MONTH_CRIME.append(CRIME)

	label_month = []

	FUERA_COBERTURA_FORCE = []
	for i in range(len(policeForce)):
		FUERA_COBERTURA_FORCE.append(0)

	CRIME_FORCE_MONTH = []
	for i in range(len(policeForce)):
		CRIME = []
		CRIME_FORCE_MONTH.append(CRIME)


	month = 0
	for y in years:
		NUMERO_CRIMENES_ANUAL = 0
		print(y)
		for m in months:
			NUMERO_CRIMENES_MENSUAL = 0
			#label_month.append(y + '_' + m)
			print(m)
			i = 0
			for p in policeForce:
				# 2011-01/2011-01-nombre-
				carpeta = y + '-' + m + '/' + y + '-' + m + '-' + p + '-street.csv'
				
				archivo = pd.read_csv('../CrimesUK_2011_2017/' + carpeta)
				archivo = np.array(archivo)

				columna_crimen = list(archivo[:,9])
				longitud = list(archivo[:,4])
				latitud = list(archivo[:,5])

				longitud_max, latitud_max, longitud_min, latitud_min = kml(p)

				for x in range(len(longitud)):
					if longitud[x] > longitud_max or longitud[x] < longitud_min or latitud[x] > latitud_max or latitud[x] < latitud_min:
						FUERA_COBERTURA_FORCE[i] += 1


				
				for n in range(len(columna_crimen)):
					for k in range(len(tipos_crimen)):
						if columna_crimen[n] == tipos_crimen[k]:
							POLICE_FORCE_CRIME[i][k] += 1
							MONTH_CRIME[month][k] += 1

				j = 0
				for c in tipos_crimen:
					NUMERO_CRIMENES_TIPO[j] += columna_crimen.count(c)
					j += 1


				NUMERO_CRIMENES_POLICE[i] += len(archivo[:,0])
				NUMERO_CRIMENES_MENSUAL += len(archivo[:,0])
				
				CRIME_FORCE_MONTH[i].append(len(archivo[:,0]))

				i += 1

			month += 1

			datos2.write(str(NUMERO_CRIMENES_MENSUAL) + '\n')
			NUMERO_CRIMENES_ANUAL += NUMERO_CRIMENES_MENSUAL
		
		datos1.write(str(NUMERO_CRIMENES_ANUAL) + '\n')
		NUMERO_CRIMENES_TOTAL += NUMERO_CRIMENES_ANUAL

	for i in range(len(policeForce)):
		file = open('respuesta7/' + policeForce[i], 'w')
		for j in range(len(tipos_crimen)):
			file.write(str(POLICE_FORCE_CRIME[i][j]) + '\n')
		file.close()

	for i in range(84):
		file = open('respuesta8/' + label_month[i] + '_TIPO-CRIMEN', 'w')
		for j in range(len(tipos_crimen)):
			file.write(str(MONTH_CRIME[i][j]) + '\n')
		file.close()

	for i in range(len(policeForce)):
		file = open('respuesta10/' + policeForce[i] + '_FUERA-COBERTURA', 'w')
		file.write(str(FUERA_COBERTURA_FORCE[i]))	
		file.close()

	for i in range(len(policeForce)):
		file = open('respuesta11/' + policeForce[i] + '_CRIMEN-MENSUAL', 'w')
		for j in range(84):			
			file.write(str(CRIME_FORCE_MONTH[i][j]) + '\n')

		file.close()

	for i in range(42):
		datos5.write(str(NUMERO_CRIMENES_POLICE[i]) + '\n')

	for i in range(len(tipos_crimen)):
		datos6.write(str(NUMERO_CRIMENES_TIPO[i]) + '\n')

	datos1.close()
	datos2.close()
	datos5.close()
	datos6.close()

	#se imprime el total de crimenes
	#print(NUMERO_CRIMENES_TOTAL)
#---------------------------------------------------------------------------

#RESPUESTA DE LA PREGUNTA 2-------------------------------------------------
def respuesta2():
	posicion_y = np.arange(len(years))
	total_crimen_anual = leer_archivo('respuesta1.txt', 1)
	
	posicion_y = np.arange(len(years))
	#plt.barh(posicion_y, total_crimen_anual, align = "center")
	plt.bar(posicion_y, total_crimen_anual, color = "b", width = .8)
	plt.xticks(posicion_y, years)
	
	plt.xlabel('Years')
	plt.ylabel('Numero de Crimenes')
	plt.title("Total de Crimenes por Anio")
	plt.show()
	
#---------------------------------------------------------------------------

#RESPUESTA DE LA PREGUNTA 3-------------------------------------------------
def respuesta3():
	posicion_y = np.arange(len(years)*len(months))
	total_crimen_mensual = leer_archivo('respuesta2.txt', 1)
	mes = []
	for i in range(84):mes.append('')

	plt.xticks(posicion_y, mes)  
	#plt.yticks(np.arange(0,51,10))
	plt.plot(total_crimen_mensual)
	
	plt.xlabel('84 Meses totales (Enero de 2011 - Diciembre de 2017)')
	plt.ylabel('Numero de Crimenes')
	plt.title("Total de Crimenes por Mes")
	mng = plt.get_current_fig_manager()
	mng.window.showMaximized()
	plt.show()

#---------------------------------------------------------------------------

#RESPUESTA DE LA PREGUNTA 4-------------------------------------------------
def respuesta4():
	posicion_y = np.arange(len(months))
	total_crimen_mensual = leer_archivo('respuesta2.txt', 1)
	mes = []
	aux = []
	for i in range(len(total_crimen_mensual)):
		aux.append(total_crimen_mensual[i])
		if (i+1) % 12 == 0:
			mes.append(aux)
			aux = []

	df = pd.DataFrame(np.array(mes), columns=months)
	scatter_matrix(df, alpha=0.2, figsize=(6, 6), diagonal='hist')

	MATRIZ_CORRELACION = []

	for i in range(len(years)):datos = []; MATRIZ_CORRELACION.append(datos)

	for i in range(len(years)):
		for j in range(len(years)):
			"""
			if j > i:
				colors = [0,0,1]
				area = np.pi*50
				 
				# Plot
				plt.scatter(mes[i], mes[j], s=area, c=colors, alpha=0.5)
				plt.title('Grafica de Dispersion Crimenes-Anio')
				plt.xlabel(years[i])
				plt.ylabel(years[j])
				#mng = plt.get_current_fig_manager()
				#mng.window.showMaximized()
				plt.show()
			"""
			correlacion = spearmanr(mes[i], mes[j])[0]
			MATRIZ_CORRELACION[i].append(round(correlacion, 2))

	
	TABLA = []
	for i in range(len(years)):datos = []; TABLA.append(datos)

	for i in range(len(years)):
		for j in range(len(years) + 1):
			if j == 0:
				TABLA[i].append(years[i])
			else:
				TABLA[i].append(MATRIZ_CORRELACION[i][j-1])

	header = [''];
	header.extend(years)
	
	with open('respuesta4_correlacion-spearman.csv', 'w', newline='', encoding='utf-8') as csvfile:
	    writer = csv.writer(csvfile)
	    writer.writerow(header)
	    writer.writerows(TABLA)
	
	plt.xticks(posicion_y, meses)  
	#plt.yticks(np.arange(0,51,10))
	i = 0
	for m in mes:
		plt.plot(m, label=years[i])
		plt.legend()
		i += 1
	
	plt.xlabel('Meses')
	plt.ylabel('Numero de Crimenes')
	plt.title("Total de Crimenes por cada Anio")
	mng = plt.get_current_fig_manager()
	mng.window.showMaximized()
	plt.show()

	# Plot the heatmap, customize and label the ticks
	fig = plt.figure(figsize=(10,10))

	ax = fig.add_subplot(1,1,1)
	im = ax.imshow(MATRIZ_CORRELACION, interpolation='nearest')
	ax.set_yticks(range(len(years)))
	ax.set_yticklabels(years)
	ax.set_xticks(range(len(years)))
	ax.set_xticklabels(years)
	ax.set_xlabel('Years')
	ax.set_ylabel('Years')
	ax.set_title('Correlacion de Spearman')

	# Add a colour bar along the bottom and label it
	cbar = fig.colorbar(ax=ax, mappable=im, orientation='vertical')
	cbar.set_label('Correlacion')

	plt.show()


	# Create data
	N = 500
	x = np.random.rand(N)
	y = np.random.rand(N)
	
#---------------------------------------------------------------------------

#RESPUESTA DE LA PREGUNTA 5-------------------------------------------------
def respuesta5():
	total_crimen_police = leer_archivo('respuesta5.txt', 1)

	total = sum(total_crimen_police)
	#print(total)

	porcentaje = []
	for t in total_crimen_police:
		porcentaje.append(round(t/(total/100), 2))
		print(t/(total/100))


	label = []
	j = 0
	for i in policeForce:
		label.append(i + '  (' + str(total_crimen_police[j]) + ' = ' + str(porcentaje[j]) + ' %)')
		j += 1


	posicion_y = np.arange(len(policeForce))	
	plt.barh(posicion_y, total_crimen_police, align = "center")
	plt.yticks(posicion_y, label)

	plt.ylabel('Police Force')
	plt.xlabel('Numero de Crimenes')
	plt.title("Total de Crimenes por Fuerza Policiaca")	
	
	#mng = plt.get_current_fig_manager()
	#mng.window.showMaximized()
	plt.show()

#---------------------------------------------------------------------------

#RESPUESTA DE LA PREGUNTA 6-------------------------------------------------
def respuesta6():
	total_crimen_tipo = leer_archivo('respuesta6.txt', 1)

	print(total_crimen_tipo)

	total = sum(total_crimen_tipo)
	print(total)

	porcentaje = []
	for t in total_crimen_tipo:
		porcentaje.append(round(t/(total/100), 2))
		print(t/(total/100))


	label = []
	j = 0
	for i in tipos_crimen:
		label.append(i + '  (' + str(total_crimen_tipo[j]) + ' = ' + str(porcentaje[j]) + ' %)')
		j += 1

	posicion_y = np.arange(len(tipos_crimen))	
	plt.barh(posicion_y, total_crimen_tipo, align = "center")
	plt.yticks(posicion_y, label)

	plt.ylabel('Tipo de Crimen')
	plt.xlabel('Numero de Crimenes')
	plt.title("Total de Crimenes por Tipo")	
	
	#mng = plt.get_current_fig_manager()
	#mng.window.showMaximized()
	plt.show()

#---------------------------------------------------------------------------

#RESPUESTA DE LA PREGUNTA 7-------------------------------------------------
def respuesta7():

	POLICE_FORCE_CRIME = []	
	for i in range(len(policeForce)):
		file = leer_archivo('respuesta7/' + policeForce[i], 1)
		POLICE_FORCE_CRIME.append(file)


	POLICE_FORCE_CRIME = np.array(POLICE_FORCE_CRIME)


	total_columnas = []

	for i in range(len(tipos_crimen)):
		total_columnas.append(sum(POLICE_FORCE_CRIME[:,i]))

	#print(list(POLICE_FORCE_CRIME))

	TABLA = []
	for i in range(len(policeForce)):
		columns = []
		k = 0
		for j in range(len(tipos_crimen) + 2):
			if j == 0:
				columns.append(policeForce[i])
			elif j < len(tipos_crimen) + 1:
				columns.append(POLICE_FORCE_CRIME[i][k])
				k += 1
			else:
				columns.append(sum(POLICE_FORCE_CRIME[i]))
		TABLA.append(columns)
	
	header = []
	footer = []
	k = 0
	for i in range(len(tipos_crimen)+2):
		if i == 0:
			header.append('POLICE / CRIME')
			footer.append('TOTAL')
		elif i < len(tipos_crimen) + 1:
			header.append(tipos_crimen[k])
			footer.append(total_columnas[k])
			k += 1
		else:
			header.append('TOTAL')
			footer.append(sum(total_columnas))

	TABLA.append(footer)
	footer = np.array(footer)

	with open('respuesta7/contingencia.csv', 'w', newline='', encoding='utf-8') as csvfile:
	    writer = csv.writer(csvfile)
	    writer.writerow(header)
	    writer.writerows(TABLA)

	# Plot the heatmap, customize and label the ticks
	fig = plt.figure(figsize=(10,10))

	ax = fig.add_subplot(1,1,1)
	im = ax.imshow(POLICE_FORCE_CRIME, interpolation='nearest')
	ax.set_yticks(range(len(policeForce)))
	ax.set_yticklabels(policeForce)
	ax.set_xticks(range(len(tipos_crimen)))
	ax.set_xticklabels('')
	ax.set_xlabel('Tipo de Crimen')
	ax.set_ylabel('Fuerza Policiaca')
	ax.set_title('Reporte de Crimenes en funcion de Fuerza Policiaca/Tipo de Crimen')

	# Add a colour bar along the bottom and label it
	cbar = fig.colorbar(ax=ax, mappable=im, orientation='vertical')
	cbar.set_label('Numero de Crimenes')

	plt.show()


	
#---------------------------------------------------------------------------

#RESPUESTA DE LA PREGUNTA 8-------------------------------------------------
def respuesta8():
	label_month = []

	for y in years:
		for m in months:
			label_month.append(y + '_' + m)

	MONTH_CRIME = []	
	for i in range(84):
		file = leer_archivo('respuesta8/' + label_month[i] + '_TIPO-CRIMEN', 1)
		MONTH_CRIME.append(file)


	MONTH_CRIME = np.array(MONTH_CRIME)


	total_columnas = []

	for i in range(len(tipos_crimen)):
		total_columnas.append(sum(MONTH_CRIME[:,i]))

	#print(list(POLICE_FORCE_CRIME))

	TABLA = []
	for i in range(84):
		columns = []
		k = 0
		for j in range(len(tipos_crimen) + 2):
			if j == 0:
				columns.append(label_month[i])
			elif j < len(tipos_crimen) + 1:
				columns.append(MONTH_CRIME[i][k])
				k += 1
			else:
				columns.append(sum(MONTH_CRIME[i]))
		TABLA.append(columns)
	
	header = []
	footer = []
	k = 0
	for i in range(len(tipos_crimen)+2):
		if i == 0:
			header.append('MONTH_CRIME / CRIME')
			footer.append('TOTAL')
		elif i < len(tipos_crimen) + 1:
			header.append(tipos_crimen[k])
			footer.append(total_columnas[k])
			k += 1
		else:
			header.append('TOTAL')
			footer.append(sum(total_columnas))

	TABLA.append(footer)
	footer = np.array(footer)

	with open('respuesta8/contingencia.csv', 'w', newline='', encoding='utf-8') as csvfile:
	    writer = csv.writer(csvfile)
	    writer.writerow(header)
	    writer.writerows(TABLA)

	# Plot the heatmap, customize and label the ticks
	fig = plt.figure(figsize=(10,10))

	ax = fig.add_subplot(1,1,1)
	im = ax.imshow(MONTH_CRIME, interpolation='nearest')
	ax.set_yticks(range(84))
	ax.set_yticklabels(label_month)
	ax.set_xticks(range(len(tipos_crimen)))
	ax.set_xticklabels('')
	ax.set_xlabel('Tipo de Crimen')
	ax.set_ylabel('Meses de cada Anio')
	ax.set_title('Reporte de Crimenes en funcion de: Mes del Anio/Tipo de Crimen')

	# Add a colour bar along the bottom and label it
	cbar = fig.colorbar(ax=ax, mappable=im, orientation='vertical')
	cbar.set_label('Numero de Crimenes')

	plt.show()

#---------------------------------------------------------------------------

#RESPUESTA DE LA PREGUNTA 9-------------------------------------------------
def respuesta9():

	CRIMENES_AREAS = np.array(read_data('CRIMENES_AREAS'))
	#print(np.array(CRIMENES_AREAS)[0][0])
	correlacion_spearman = spearmanr(CRIMENES_AREAS[:,0], CRIMENES_AREAS[:,1])[0]
	correlacion_pearson = pearsonr(CRIMENES_AREAS[:,0], CRIMENES_AREAS[:,1])[0]

	print(CRIMENES_AREAS[:,1])

	print('Coeficiente de correlacion de Spearman: ', correlacion_spearman)
	print('Coeficiente de correlacion de Pearson: ', correlacion_pearson)

	plt.scatter(CRIMENES_AREAS[:, 0], CRIMENES_AREAS[:, 1], s=60, cmap='viridis')
	plt.title('Crímenes reportados por fuerza policiaca y su área de cobertura')
	plt.xlabel('Numero de Crimenes')
	plt.ylabel('Area de Cobertura')
	plt.show()

	#correlacion_spearman.append(spearmanr(CRIMENES_AREAS[i], CRIMENES_AREAS[j])[0])
	#correlacion_pearson.append(pearsonr(CRIMENES_AREAS[i][0], CRIMENES_AREAS[i][1]))

#---------------------------------------------------------------------------	

#RESPUESTA DE LA PREGUNTA 5-------------------------------------------------
def respuesta10():

	AREAS = []

	for i in range(len(policeForce)):
		file = open('respuesta10/' + policeForce[i] +'_FUERA-COBERTURA')
		for a in file:
			AREAS.append(int(a))

	total = sum(AREAS)

	label = []

	for i in range(len(policeForce)):

		label.append(policeForce[i] + ' (' + str(AREAS[i]) + ' = ' + str(round(AREAS[i]/(total/100), 2)) + '%)')
	

	posicion_y = np.arange(len(policeForce))	
	plt.barh(posicion_y, AREAS, align = "center")
	plt.yticks(posicion_y, label)

	plt.ylabel('Police Force')
	plt.xlabel('Numero de Crimenes')
	plt.title("Crimenes ocurridos fuera del area de cobertura")	
	
	#mng = plt.get_current_fig_manager()
	#mng.window.showMaximized()
	plt.show()

#---------------------------------------------------------------------------

#RESPUESTA DE LA PREGUNTA 11-------------------------------------------------
def respuesta11():

	CRIME_FORCE_MONTH = []
	for i in range(len(policeForce)):
		file = leer_archivo('respuesta11/' + policeForce[i] + '_CRIMEN-MENSUAL', 1)
		CRIME_FORCE_MONTH.append(file)

	total_crimes_force = leer_archivo('respuesta5.txt', 1)
	#total_crimes_force = np.array(total_crimes_force)
	mejores = []
	for i in range(10):
		x = max(total_crimes_force)
		#print(x)
		ind = total_crimes_force.index(x)
		total_crimes_force[ind] = -1
		mejores.append(ind)



	
	plt.xticks(range(84), '')  
	#plt.yticks(range(len(policeForce)), policeForce)
	labels_fuerzas = []
	i = 0
	for i in mejores:
		labels_fuerzas.append(policeForce[i])
		plt.plot(CRIME_FORCE_MONTH[i], label=policeForce[i])
		plt.legend()
		i += 1	

	plt.xlabel('Meses')
	plt.ylabel('Numero de Crimenes')
	plt.title("Crimenes por Fuerza Policiaca (Ene 2011 - Dic 2017)")
	mng = plt.get_current_fig_manager()
	mng.window.showMaximized()
	plt.show()

	RMSD = []

	x, y = 0, 0
	for i in mejores:
		RMSD.append([])
		for j in mejores:
			RMSD[x].append(sqrt(mean_squared_error(CRIME_FORCE_MONTH[i], CRIME_FORCE_MONTH[j])))
		x+=1

	print(np.array(RMSD))

	with open('distancias.csv', 'w', newline='', encoding='utf-8') as csvfile:
	    writer = csv.writer(csvfile)
	    writer.writerows(RMSD)

	fig = plt.figure(figsize=(10,10))

	ax = fig.add_subplot(1,1,1)
	im = ax.imshow(RMSD, interpolation='nearest')
	ax.set_yticks(range(len(RMSD[0])))
	ax.set_yticklabels(labels_fuerzas)
	ax.set_xticks(range(len(RMSD[0])))
	ax.set_xticklabels(labels_fuerzas)
	ax.set_xlabel('Fuerza policiaca')
	ax.set_ylabel('fuerza policiaca')
	ax.set_title('Distancias entre fuerzas - Mapa de calor')

	# Add a colour bar along the bottom and label it
	cbar = fig.colorbar(ax=ax, mappable=im, orientation='vertical')
	cbar.set_label('Correlacion')

	plt.show()


#---------------------------------------------------------------------------

#RESPUESTA DE LA PREGUNTA 12-------------------------------------------------
def respuesta12():

	CRIME_FORCE_MONTH = []
	for i in range(len(policeForce)):
		file = leer_archivo('respuesta11/' + policeForce[i] + '_CRIMEN-MENSUAL', 1)
		CRIME_FORCE_MONTH.append(file)

	total_crimes_force = leer_archivo('respuesta5.txt', 1)
	#total_crimes_force = np.array(total_crimes_force)
	mejores = []
	for i in range(10):
		x = max(total_crimes_force)
		#print(x)
		ind = total_crimes_force.index(x)
		total_crimes_force[ind] = -1
		mejores.append(ind)

	MATRIZ_CORRELACION = []

	for i in range(10):datos = []; MATRIZ_CORRELACION.append(datos)

	labels_fuerzas = []

	k = 0
	for i in mejores:
		labels_fuerzas.append(policeForce[i])
		for j in mejores:
			correlacion = spearmanr(CRIME_FORCE_MONTH[i], CRIME_FORCE_MONTH[j])[0]
			#print(CRIME_FORCE_MONTH[i], ',', CRIME_FORCE_MONTH[j], ' = ', correlacion)
			MATRIZ_CORRELACION[k].append(round(correlacion, 2))

		k += 1

	print(labels_fuerzas)

	TABLA = []
	for i in range(10):datos = []; TABLA.append(datos)

	for i in range(10):
		for j in range(11):
			if j == 0:
				TABLA[i].append(policeForce[mejores[i]])
			else:
				TABLA[i].append(MATRIZ_CORRELACION[i][j-1])

	header = [''];
	for i in mejores:header.append(policeForce[i])
	
	with open('respuesta12_correlacion-spearman.csv', 'w', newline='', encoding='utf-8') as csvfile:
	    writer = csv.writer(csvfile)
	    writer.writerow(header)
	    writer.writerows(TABLA)


	fuerza = []
	for i in mejores:fuerza.append(policeForce[i])

	# Plot the heatmap, customize and label the ticks
	fig = plt.figure(figsize=(10,10))

	ax = fig.add_subplot(1,1,1)
	im = ax.imshow(MATRIZ_CORRELACION, interpolation='nearest')
	ax.set_yticks(range(10))
	ax.set_yticklabels(fuerza)
	ax.set_xticks(range(10))
	ax.set_xticklabels(labels_fuerzas)
	ax.set_xlabel('TOP 10 - Police Forces')
	ax.set_ylabel('TOP 10 - Police Forces')
	ax.set_title('Correlacion de Spearman para cada pareja de Fuerza Policiaca')

	# Add a colour bar along the bottom and label it
	cbar = fig.colorbar(ax=ax, mappable=im, orientation='vertical')
	cbar.set_label('Coeficiente de Correlacion de Spearman')

	plt.show()

#---------------------------------------------------------------------------

#RESPUESTA DE LA PREGUNTA 13------------------------------------------------
def respuesta13():

	policeForce.append('btp')
	policeForce.append('city-of-london')

	person = 0
	vehicle = 0
	person_vehicle = 0
	RANGO_EDAD = ['under 10','10-17','18-24','25-34','over 34']
	FRECUENCIA_EDAD = [0,0,0,0,0]
	GRUPO_ETNICO = ['Other','White','Asian','Black']
	FRECUENCIA_GRUPO = [0,0,0,0]

	GENDER = ['Male', 'Female', 'Other']
	FRECUENCIA_GENDER = [0,0,0]

	NUM_APLICACIONES = 0
	for i in range(3, len(years)):
		for j in range(len(months)):
			carpeta = years[i] + '-' + months[j] 
			print(carpeta)
			for p in range(len(policeForce)):				
				if i == 3: j = 3
				
				archivo = Path('../StopSearch_2011_2017/' + carpeta + '/' + carpeta + '-' +  policeForce[p] +'-stop-and-search.csv')
				if archivo.exists():								
					archivo = pd.read_csv('../StopSearch_2011_2017/' + carpeta + '/' + carpeta + '-' +  policeForce[p] +'-stop-and-search.csv')
					archivo = np.array(archivo)
					NUM_APLICACIONES += len(archivo[:,0])
					for inspeccion in archivo[:,0]:
						if inspeccion == 'Person search':person += 1
						if inspeccion == 'Vehicle search':vehicle += 1
						if inspeccion == 'Person and Vehicle search':person_vehicle += 1

					for edad in archivo[:,7]:
						for r in range(len(RANGO_EDAD)):
							if edad == RANGO_EDAD[r]:
								FRECUENCIA_EDAD[r] += 1

					for grupo in archivo[:,9]:
						for g in range(len(GRUPO_ETNICO)):
							if grupo == GRUPO_ETNICO[g]:
								FRECUENCIA_GRUPO[g] += 1

					for gender in archivo[:,6]:
						for g in range(len(GENDER)):
							if gender == GENDER[g]:
								FRECUENCIA_GENDER[g] += 1

							
	impr = ["Person search: " + str(person), "Vehicle search: "  + str(vehicle), "Person and Vehicle search: " + str(person_vehicle)]
	vol = [person, vehicle, person_vehicle]
	expl =(0, 0, 0)
	plt.pie(vol, explode=expl, labels=impr, autopct='%1.1f%%', shadow=True)
	plt.title("Porcentaje de las aplicaciones de la estrategia Stop and Search", bbox={"facecolor":"0.8", "pad":5})
	plt.legend()
	plt.show()




	
	labels = []
	for i in range(len(RANGO_EDAD)):
		labels.append(RANGO_EDAD[i] + '\n' + str(FRECUENCIA_EDAD[i]))


	print(FRECUENCIA_EDAD)

	posicion_y = np.arange(len(RANGO_EDAD))
	#plt.barh(posicion_y, total_crimen_anual, align = "center")
	plt.bar(posicion_y, FRECUENCIA_EDAD, color = "b", width = .8)
	plt.xticks(posicion_y, labels)
	
	plt.xlabel('Rango de Edades')
	plt.ylabel('Numero de Aplicaciones')
	plt.title("Aplicaciones de la estrategia Stop and Search")
	plt.show()

	labels = []
	for i in range(len(GRUPO_ETNICO)):
		labels.append(GRUPO_ETNICO[i] + '\n' + str(FRECUENCIA_GRUPO[i]))


	posicion_y = np.arange(len(GRUPO_ETNICO))
	#plt.barh(posicion_y, total_crimen_anual, align = "center")
	plt.bar(posicion_y, FRECUENCIA_GRUPO, color = "b", width = .8)
	plt.xticks(posicion_y, labels)
	
	plt.xlabel('Grupos Etnicos')
	plt.ylabel('Numero de Aplicaciones')
	plt.title("Aplicaciones de la estrategia Stop and Search")
	plt.show()

	#print(GENDER)
	labels = []
	for i in range(len(GENDER)):
		labels.append(GENDER[i] + '\n' + str(FRECUENCIA_GENDER[i]))


	posicion_y = np.arange(len(GENDER))
	#plt.barh(posicion_y, total_crimen_anual, align = "center")
	plt.bar(posicion_y, FRECUENCIA_GENDER, color = "b", width = .8)
	plt.xticks(posicion_y, labels)
	
	plt.xlabel('Generos')
	plt.ylabel('Numero de Aplicaciones')
	plt.title("Aplicaciones de la estrategia Stop and Search")
	plt.show()
	
	print(NUM_APLICACIONES)
#---------------------------------------------------------------------------

#RESPUESTA DE LA PREGUNTA 18-------------------------------------------------
def respuesta18():

	policeForce.append('btp')
	policeForce.append('city-of-london')

	PROMEDIO_MES = []
	MES = [0,0,0,0,0,0,0,0,0,0,0,0]
	APLICACIONES_MES = [MES, MES, MES, MES]
	APLICACIONES_MES = np.array(APLICACIONES_MES)
	#NUM_FORCES = []
	MARGEN_ERROR = []
	MIN = []
	MAX = []
	MIN_MAX = []
	n = 0
	for i in range(3, len(years)):
		r = 0
		if i == 3:
			r = 3
		for j in range(r, len(months)):
			#if i == 3: j = 3
			carpeta = years[i] + '-' + months[j] 
			print(carpeta)
			NUM_APLICACIONES = 0
			#ERROR = []
			fuerzas = 0
			for p in range(len(policeForce)):
				archivo = Path('../StopSearch_2011_2017/' + carpeta + '/' + carpeta + '-' +  policeForce[p] +'-stop-and-search.csv')
				if archivo.exists():								
					archivo = pd.read_csv('../StopSearch_2011_2017/' + carpeta + '/' + carpeta + '-' +  policeForce[p] +'-stop-and-search.csv')
					archivo = np.array(archivo)
					#NUM_APLICACIONES += len(archivo[:,0])
					#ERROR.append(len(archivo[:,0]))
					APLICACIONES_MES[n][j] += len(archivo[:,0])


					fuerzas += 1

			#print(j)
			#minimo = min(ERROR)
			#maximo = max(ERROR)

			#MARGEN_ERROR.append((maximo-minimo)/2)
			#promedio = float(NUM_APLICACIONES / fuerzas)
			#PROMEDIO_MES.append(promedio)
			#MIN.append(promedio - minimo)
			#MAX.append(maximo - promedio)

		n += 1

	print(APLICACIONES_MES)

	PROMEDIO_MES = []
	for i in range(12):
		if i < 3:
			PROMEDIO_MES.append(sum(APLICACIONES_MES[:,i])/3)
		else:
			PROMEDIO_MES.append(sum(APLICACIONES_MES[:,i])/4)

	print('\n', PROMEDIO_MES)

	APLICACIONES_MES[0][0] = APLICACIONES_MES[1][0]
	APLICACIONES_MES[0][1] = APLICACIONES_MES[1][1]
	APLICACIONES_MES[0][2] = APLICACIONES_MES[1][2]

	MAX = []
	MIN = []
	for i in range(12):
		MAX.append(max(APLICACIONES_MES[:,i]) - PROMEDIO_MES[i])
		MIN.append(PROMEDIO_MES[i] - min(APLICACIONES_MES[:,i]))

	print('\n', np.array(MAX))
	print('\n', np.array(MIN)) 

	MIN_MAX = [MIN,MAX]

	"""
	MIN_MAX.append(MIN)
	MIN_MAX.append(MAX)
	
	MARGEN_ERROR = np.array(MARGEN_ERROR)
	
	x = np.arange(0.1, 4, 0.5)
	y = np.exp(-x)
	x = np.arange(0.1, 4, 0.5)
	error = 0.1 + 0.2 * x
	
	print(error)
	print(PROMEDIO_MES)
	print(MIN_MAX)
	
	posicion_y = np.arange(len(PROMEDIO_MES))
	mes = []
	for i in range(len(PROMEDIO_MES)):mes.append('')
	error = np.zeros(len(MARGEN_ERROR))

	# example error bar values that vary with x-position
	"""
	
	plt.figure()
	plt.errorbar(range(len(PROMEDIO_MES)), PROMEDIO_MES, yerr=MIN_MAX, fmt='-o')
	plt.xlabel('Meses')
	plt.ylabel('Numero de Aplicaciones')
	plt.title('Promedio de Aplicaciones de la estrategia Stop and Search')
	plt.show()
	
	#print(NUM_APLICACIONES)
#----------------------------------------------------------------------------

#RESPUESTA DE LA PREGUNTA 19-------------------------------------------------
def respuesta19():

	DATOS_FALTANTES = np.zeros(len(policeForce))
	COLUMNAS = []
	DATOS_FALTANTES_COLUMNA = [0,0,0,0,0,0,0,0,0,0,0,0]
	month = 0
	for y in years:
		print(y)
		for m in months:
			print(m)
			i = 0
			for p in policeForce:
				# 2011-01/2011-01-nombre-
				carpeta = y + '-' + m + '/' + y + '-' + m + '-' + p + '-street.csv'
				
				archivo = pd.read_csv('../CrimesUK_2011_2017/' + carpeta)

				archivo[archivo.columns] = archivo[archivo.columns].fillna(value='nan')
				COLUMNAS = list(archivo.columns)
				
				DATOS_FALTANTES[i] += sum((archivo == 'nan').sum())

				archivo = np.array(archivo)

				for c in range(len(COLUMNAS)):
					columna = list(archivo[:,c])
					DATOS_FALTANTES_COLUMNA[c] += columna.count('nan')


				i += 1

			month += 1

	datos1 = open('respuesta19.txt','w')
	for i in range(len(DATOS_FALTANTES)):
		datos1.write(str(int(DATOS_FALTANTES[i])) + '\n')

	datos1.close()

	datos2 = open('respuesta20.txt','w')
	for i in range(len(DATOS_FALTANTES_COLUMNA)):
		datos2.write(str(DATOS_FALTANTES_COLUMNA[i]) + '\n')

	datos2.close()

	datos = leer_archivo('respuesta19.txt', 1)

	posicion_y = np.arange(len(policeForce))	
	plt.barh(posicion_y, datos)
	plt.yticks(posicion_y, policeForce)

	plt.ylabel('Police Force')
	plt.xlabel('Numero de Datos Faltantes')
	plt.title("Datos faltantes por Fuerza Policiaca")	
	
	#mng = plt.get_current_fig_manager()
	#mng.window.showMaximized()
	plt.show()

#---------------------------------------------------------------------------

#RESPUESTA DE LA PREGUNTA 20-------------------------------------------------
def respuesta20():
	datos = leer_archivo('respuesta20.txt', 1)
	file = pd.read_csv('../CrimesUK_2011_2017/2011-01/2011-01-dyfed-powys-street.csv')
	columnas = file.columns

	total = sum(datos)

	porcentaje = []
	for t in datos:
		porcentaje.append(round(t/(total/100), 5))
		print(t/(total/100))


	label = []
	j = 0
	for i in columnas:
		label.append(i + '  (' + str(datos[j]) + ' = ' + str(porcentaje[j]) + ' %)')
		j += 1

	posicion_y = np.arange(len(datos))

	
	
	#plt.barh(posicion_y, total_crimen_anual, align = "center")
	plt.barh(posicion_y, datos)
	plt.yticks(posicion_y, label)
	
	plt.ylabel('Nombre de la columna')
	plt.xlabel('Numero de Datos Faltantes')
	plt.title("Datos faltantes por Columna")
	plt.show()
	
#---------------------------------------------------------------------------

#-------------------------------------------------
#RESULTADOS (Descomentar las funciones de las respuestas)

#tiposCrimen() #genera un arreglo con los nombres de los tipos de crimenes que se utilizan para varias respuestas
#respuesta1() #esta funcion genera datos que se utilizan para las respuestas 1 a la 12
#respuesta2() #solo grafica
#respuesta3() #solo grafica
#respuesta4() #solo grafica
#respuesta5() #solo grafica
#respuesta6() #solo grafica
#respuesta7() #solo grafica
#respuesta8() #solo grafica
#respuesta9()
#respuesta10() #solo grafica
#respuesta11() #solo grafica
#respuesta12() #solo grafica
#respuesta13() #esta funcion genera datos que se utilizan para las respuestas 13 a la 17
#respuesta18() #Genera la respuesta 18
#respuesta19() #Genera la respuesta 19
#respuesta20() #Genera la respuesta 20