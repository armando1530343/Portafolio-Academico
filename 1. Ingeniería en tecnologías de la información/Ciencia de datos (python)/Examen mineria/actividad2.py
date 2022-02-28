import csv
import pandas as pd
import numpy as np
from math import *

def leer_csv(path):
	file = pd.read_csv(path)	
	x = []
	for f in file.columns:
		x.append(f)

	file = np.array(file)
	y = file[0]

	aux_x = []
	for xx in x:
		if xx != 'X':
			aux_x.append(float(xx))

	aux_y = []
	for yy in y:
		if yy != 'Y':
			aux_y.append(float(yy))

	return aux_x, aux_y

def covarianza(x, y, _x, _y):
	sum_ = 0.0
	n = len(x)
	for i in range(n):
		if x[i] != '?' and y[i] != '?':
			sum_ += (x[i]-_x) * (y[i]-_y)
		else:
			n -= 1

	return sum_/n

def coeficiente_correlacion(x, y):

	_x = 0.0
	_y = 0.0
	sum_x_cuadrada = 0.0
	sum_y_cuadrada = 0.0
	sum_xy = 0.0

	len_x = len(x)
	len_y = len(y)

	for i in range(len(x)):
		if y[i] != '?':
			_x += x[i]
			_y += y[i]

			sum_x_cuadrada += x[i]**2
			sum_y_cuadrada += y[i]**2

			sum_xy += x[i]*y[i]
		else:
			len_x -= 1
			len_y -= 1
		


	_x = _x / len_x
	_y = _y / len_y

	var_x_cuad = sum_x_cuadrada/len_x - (_x**2)
	var_x = sqrt(var_x_cuad)
	var_y_cuad = sum_y_cuadrada/len_y - (_y**2) 
	var_y = sqrt(var_y_cuad)
	var_xy = sum_xy/len_x - (_x*_y)
		
	coeficiente = var_xy/(var_x*var_y)

	return coeficiente, _x, _y, var_x_cuad, var_xy

def regresion_logistica(x, _x, _y, var_x_cuad, var_xy):
	return _y + (var_xy / var_x_cuad) * (x - _x)





def main():

	print "Datos Actividad 1:\n"
	x = [95.0, 85.0, 80.0, 70.0, 60.0, 65.0, 75.0, 70.0]
	y = [85.0, 95.0, '?', 65.0, 70.0, 60.0, 100.0, '?']

	print "\tX: ", x
	print "\tY: ", y

	correlacion, _x, _y, var_x_cuad, var_xy = coeficiente_correlacion(x, y)
	print "\n\tCoeficiente de correlacion lineal: ", correlacion
	covarianza_ = covarianza(x, y, _x, _y)
	print "\n\tCovarianza: ", covarianza_
	print "\n\tRegresion logistica:"
	print "\ty[2] = ", regresion_logistica(x[2], _x, _y, var_x_cuad, var_xy)
	print "\ty[7] = ", regresion_logistica(x[7], _x, _y, var_x_cuad, var_xy)


	print "\n\nDatos archivo CSV:\n"
	x, y = leer_csv("mineria_Datos_examen_1_1.csv")

	print "\tX: ", x
	print "\tY: ", y

	correlacion, _x, _y, var_x_cuad, var_xy = coeficiente_correlacion(x, y)
	print "\n\tCoeficiente de correlacion lineal: ", correlacion

	covarianza_ = covarianza(x, y, _x, _y)
	print "\n\tCovarianza: ", covarianza_

main()





