import numpy as np
from scipy.cluster.vq import kmeans2
from sklearn import datasets
from math import *


def sigmoide(x):
	return 1.0 / (1.0 + exp(-i))


def func_gaussiana(x):
	return exp(-(i*i)/2.0)
	

def input_hidden(input_, h):
	#se generan pesos aleatorios para las entradas + 1 (bias)
	weights_input = np.random.rand(h, len(input_)+1)

	#------------operaciones de entrada------------

	print('input:', input_)
	print('pesos:', weights_input)

	output = []

	for i in range(h):
		#net_i = np.zeros(len(datos_e[0]))
		net_i = []
		for j in range(len(input_)):
			mult = input_[j]*weights_input[i][j]
			net_i.append(mult)

		net_i.append(-1*weights_input[i][len(input_)])
		output.append(sigmoide(sum(net_i)))

	output = np.array(output)

	print('pesos:',output)

	return output

def hidden_output(output_hidden, target_, h):

	#se generan pesos aleatorios de salida
	weights_output = np.random.rand(len(target_), h+1)

	output = []

	for i in range(len(target_)):
		out_h = []
		for j in range(h):
			out_h.append(output_hidden[j] * weights_output[i][j])
		out_h.append(-1*weights_output[i][len(output_hidden)])
		output.append(func_gaussiana(sum(out_h)))

	output = np.array(output)

	#print('out',len(output))

	#se obtiene la matriz pseudoinversa de los datos de salida
	

	#se obtienen los pesos multiplicando la matriz inversa por el vector de salidas deseadas
	return output

def prediccion(datos_p):
	return 0


def FFNN(input_, target_, input_test, target_test, h):

	for i in range(len(input_)):		

		#--datos de entrada a la capa oculta--
		hidden = input_hidden(input_[i], h)

		print('\nhidden:\n',hidden)

		break

		#--salida de datos de la capa oculta--
		#output = hidden_output(hidden, target_, h)

		#--prediccion
		#predict = prediccion(input_test)

	
	
	print('\noutput:\n',output)

	return output


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

	salida_neuronas = FFNN(datos_e, clases_e, datos_p, clases_p, h)

for i in range(1):
	run()