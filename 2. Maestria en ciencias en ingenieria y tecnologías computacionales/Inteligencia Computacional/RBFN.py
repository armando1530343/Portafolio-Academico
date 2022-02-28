import numpy as np
from scipy.cluster.vq import kmeans2
from sklearn import datasets
from math import *

def get_centroide(x, centroides):
	#se recorren los centroides
	distancias = np.zeros(h)
	for i in range(h):
		#se calcula la distancia de x con el centroide actual
		distancias[i] = np.sqrt(np.sum((x - centroides[i])**2))

	#se retorna el cluster al que pertenece x
	return np.argmin(distancias)


#se calcula la distancia de un patron con todos los centroides
def clasificacion(X, centroides):
	clases = np.array([])
	for x in X:
		#se calcula el cluster al que pertenece x
		centro = get_centroide(x, centroides)
		clases = np.append(clases, centro)
	
	return clases

def func_gaussiana(x):
	return exp(-(x*x)/2.0)

#se calculas las distancias euclidianas entre cada centroide
def dispersion_centroides(centroides):
	
	distancias = np.array([])

	h = len(centroides)

	for i in range(h):
		#vector que guarda las distancias con del cluster:i al cluster:j sin contar a i
		#print('center ',i)
		dist = np.array([])
		for j in range(h):
			if i != j: 
				#se almacena la distancia de Ci a Cj
				dist = np.append(dist, sqrt(np.sum((centroides[i] - centroides[j])**2)))
		distancias = np.append(distancias, np.min(dist)/2.0)

	return distancias

def capa_oculta(datos_e, centroides, h):

	#dispercion de los centroides
	D = dispersion_centroides(centroides)
	
	#matriz de salida de la capa oculta
	output = np.zeros((len(datos_e), h + 1))

	i=0
	for dato in datos_e:
		output[i,0] = 1 #valor reservado para el calculo del bias
		j=1
		for neurona in centroides:
			input_ = sqrt(np.sum(dato - neurona)**2 / D[j-1])
			#print(func_gaussiana(input_))
			output[i, j] = func_gaussiana(input_)
			j+=1
		i+=1

	return output


def capa_salida(output, clases_e,h):

	#clases_e: vector de salidas deseadas de cada patron de entrenamiento
	
	#se obtiene la matriz pseudoinversa de los datos de salida
	output_ = np.linalg.pinv(output)

	out_y = []
	clases = list(range(h))
	for i in range(len(clases_e)):
		y = np.zeros(len(clases))
		
		for j in range(len(clases)):
			if clases_e[i] == clases[j]:
				y[j] = 1.0
		#print(y)
		out_y.append(y)

	#print('Y:',out_y)


	pesos = np.matmul(output_, out_y)
	#print('pesosT:',pesos.T)

	#se obtienen los pesos multiplicando la matriz inversa por el vector de salidas deseadas
	return pesos

def prediccion(datos_p, pesos, centroides):
	
	#dispercion de los centroides
	D = dispersion_centroides(centroides)
	
	output = []

	#print('datos_p:',datos_p)

	#print(pesos)

	i=0
	for dato in datos_p:
		#matriz de salida de la capa oculta
		predict = [1]
		j=1
		for neurona in centroides:
			input_ = sqrt(np.sum(dato - neurona)**2 / D[j-1])
			predict.append(func_gaussiana(input_))
			j+=1
		z = np.matmul(pesos.T, predict)
		#print('z:',z)
		output.append(np.argmax(z))
		i+=1

	#print(output)

	return output

#calculo del error cuadratico medio
def MSE(predict, clases_p):
	return np.sum((predict - clases_p)**2) / len(predict)

def exactitud(predict, clases_p):

	#se mide la exactitud de la clasificacion

	VP, VN, FP, FN = [0.0]*4

	

	for c in range(len(clases_p)):
		#salida deseada
		if clases_p[c] == 1:
			#salida predicha
			if predict[c] == 1: 
				VP+=1 
			else: 
				FN+=1
		
		#salida no deseada
		else:
			#salida predicha
			if predict[c] == 1: 
				FP+=1 
			else: 
				VN+=1

	#print(VP,',', VN,',', FP,',', FN)


	return (VP + VN)/(VP + VN + FP + FN)



def rbfn(datos_e, clases_e, datos_p, clases_p, h):
	#se seleccionan los centroides a utilizar usando Kmeans
	centroides, clases = kmeans2(datos_e, h)
	#print('Centroides: \n' centroides)
	#print('Clases:\n', clases)

	output = capa_oculta(datos_e, centroides, h)
	pesos = capa_salida(output, clases_e, h)
	predict = prediccion(datos_p, pesos, centroides)

	return centroides, output, pesos, predict


def run():
	iris = datasets.load_iris()

	#se cargan los datos de IRIS
	datos = iris.data[:100]
	#se normalizan los datos
	datos = (datos - datos.min(axis=0))/(datos.max(axis=0)-datos.min(axis=0))
	#se obtienen las clases de cada entrada
	clases = iris.target[:100]
	#tamaño de poblacion
	P = len(datos)
	#longitud de cada entrada
	d = len(datos[0])
	#numero de capas ocultas (centroides)
	h = 2


	idx = np.random.permutation(P)
	#conjunto de datos de entrenamiento
	datos_e = datos[idx[:int(P*.75)]]
	clases_e = clases[idx[:int(P*.75)]]


	#conjunto de datos de prueba
	datos_p = datos[idx[int(P*.75):]]
	clases_p = clases[idx[int(P*.75):]]
	

	centroides, output, pesos, predict = rbfn(datos_e, clases_e, datos_p, clases_p, h)
	error = MSE(predict, clases_p)

	exact = exactitud(predict, clases_p)

	#print('\nCentroides: \n', centroides)
	#print('\nSalida de la capa oculta: \n', output)
	#print('\nPesos: \n', pesos)
	#print('\nPrediccion:\n', predict)
	#print('\nDeseado:\n', np.array(clases_p))
	print('Error Cuadratico Medio:\t', error, '\t\tExactitud de clasificacion:\t', exact)
	#print('Exactitud de clasificacion:\t', exact)


for i in range(30):
	run()