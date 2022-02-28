from math import *

x = [95.0, 85.0, 80.0, 70.0, 60.0, 65.0, 75.0, 70.0]
y = [85.0, 95.0, '?', 65.0, 70.0, 60.0, 100.0, '?']


print "X: ", x
print "Y: ", y


#Medias aritmeticas
_x = 0.0
_y = 0.0

#sumatoria de los cuadrados de los valores de cada arreglo
sum_x_cuadrada = 0.0
sum_y_cuadrada = 0.0

sum_xy = 0.0
datos_faltantes = 0

ind = []

for i in range(len(x)):
	if y[i] != '?':
		_x += x[i]
		_y += y[i]

		sum_x_cuadrada += x[i]**2
		sum_y_cuadrada += y[i]**2

		sum_xy += x[i]*y[i]
	else:
		datos_faltantes += 1
		ind.append(i)

datos_contables = len(y) - datos_faltantes

#MEDIAS ARITMETICAS
_x = _x / datos_contables
_y = _y / datos_contables

#CALCULO DE VARIANZAS
var_x_cuadrada = (sum_x_cuadrada / datos_contables) - _x**2
var_x = sqrt(var_x_cuadrada)
var_y_cuadrada = (sum_y_cuadrada / datos_contables) - _y**2 
var_y = sqrt(var_y_cuadrada)
var_xy = (sum_xy / datos_contables) - _x*_y

#COEFICIENTE DE CORRELACION LINEAL
coeficiente_correlacion = var_xy / (var_x*var_y)

print "Coeficiente de correlacion lineal: ", coeficiente_correlacion

datos_faltantes_y = []


print "\nFaltantes de Y"
for i in range(len(ind)):
	y[ind[i]] = _y + (var_xy / var_x_cuadrada) * (x[ind[i]] - _x)
	print "y[",ind[i],"] = ", y[ind[i]]


print "Y: ", y

