import numpy as np
from scipy.cluster.vq import kmeans2
from sklearn import datasets
from math import *

def sigmoide(x, d=False):
	if d == True:
		return x * (1.0 - x)
	return 1.0/(1.0 + np.exp(-x))

#proceso de la capa oculta
def hidden(datos_e, h, pesos=None):

	if pesos is None:
		#se generan los pesos aleatorios para las entradas
		pesos = np.random.rand(h, len(datos_e))-1
	
	#print('pesos:',pesos)

	#se multiplican mas entradas por los pesos
	z = np.dot(pesos, datos_e.T)
	return sigmoide(z), pesos, z
	
#proceso de la capa oculta
def output(hidden_, h, pesos=None, predict=False):

	if pesos is None:
		#se generan los pesos aleatorios para las entradas
		pesos = np.random.rand(h, len(hidden_))-1
	#se multiplican mas entradas por los pesos
	z = np.dot(pesos,hidden_.T)

	#print('pesos:',pesos)

	activacion = sigmoide(z)

	#print(activacion)

	if predict == True:
		targets = []
		for a in activacion:
			targets.append(0.0 if a > .5 else 1.0)

		return np.array(targets) 

	return activacion, pesos

def back_propagation(data, hidden_neurons, output_neurons, target, hidden_, output_, pesos_hidden, pesos_output):
	#Se calcula el error para todas las output_
	output_error=np.zeros(output_neurons)
	hidden_error=np.zeros(hidden_neurons)

	#print((target))

	for i in range(output_neurons):
		output_error[i] = (target[i] - output_[i] ) * sigmoide(output_[i], d=True)
    
	
	for i in range(output_neurons):
		for j in range(hidden_neurons):
			hidden_error[j] += output_error[i] * pesos_output[i][j] * sigmoide(hidden_[j], d=True)


	#Se actualizan los pesos de la capa de Salida
	for i in range(output_neurons):
		for j in range(hidden_neurons):
			pesos_output[i][j] = pesos_output[i][j] + output_error[i] * hidden_[j] *.7

	#Se actualizan los pesos de la CapaOculta
	for i in range(hidden_neurons):
		for j in range(len(data)):
			pesos_hidden[i][j] = pesos_hidden[i][j] + hidden_error[i] * data[j] * .7
	
	return pesos_hidden, pesos_output


#se realiza la prediccion del conjunto de datos de prueba
def prediccion(datos_p, hidden_neurons, output_neurons, pesos_hidden, pesos_output):


	#vector de etiquetas predichas
	predict = []

	#print(pesos_hidden)

	for i in range(len(datos_p)):
		#se generan los datos de la capa oculta
		hidden_, pesos_hidden, z 	= hidden(datos_p[i], hidden_neurons, pesos=pesos_hidden)
		#se generan los datos de las neuronas de salida
		targets 					= output(hidden_, output_neurons, pesos=pesos_output, predict=True)

		predict.append(targets)

	return np.array(predict)

#calculo del error cuadratico medio
def MSE(predict, clases_p):
	return np.sum((predict - clases_p)**2) / len(predict)

def exactitud(predict, clases_p):

	#se mide la exactitud de la clasificacion
	'''
	se calculas los contadores de acuerdo al vector de salidas : 

	VP=verdadero positivo
	VN=verdadero necativo
	FP=falso positivo
	FN=falso negativo
	'''

	#print('p:',predict)

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
	return (VP + VN)/(VP + VN + FP + FN)

def FFNN(datos_e, clases_e, datos_p, clases_p, hidden_neurons, output_neurons, it):

	#se definen las etiquetas para cada salida de la neurona
	target_neuron = np.zeros((len(datos_e), output_neurons))

	#print(len(datos_e))

	for g in range(50):
	#error = 0.0

		for i in range(len(datos_e)):

			#etiqueta deseada
			for j in range(output_neurons):
				if clases_e[i] == j:
					target_neuron[i,j] = 1.0

			target = target_neuron[i]

			#se generan los datos de la capa oculta
			hidden_, pesos_hidden, z = hidden(datos_e[i], hidden_neurons, pesos=pesos_hidden if i>0 or g>0 else None )
			
			#se generan los datos de las neuronas de salida
			output_, pesos_output = output(hidden_, output_neurons, pesos=pesos_output if i>0 or g>0 else None)

			#print('Pesos hidden:')
			#print(pesos_hidden)
			#print('Pesos output:')
			#print(pesos_output)

			pesos_hidden, pesos_output = back_propagation(datos_e[i], hidden_neurons, output_neurons, 
															target, hidden_, output_, pesos_hidden, pesos_output)


	predict = prediccion(datos_p, hidden_neurons, output_neurons, pesos_hidden, pesos_output)
	#print(predict)

	error = np.zeros(output_neurons)
	exact = np.zeros(output_neurons)

	for i in range(output_neurons):
		error[i] += MSE(predict.T[i], clases_p)
		exact[i] += exactitud(predict.T[i], clases_p)
	print(it+1,'. MSE:\t', error, '\t\tExactitud:\t', exact)

	return error, exact

def run(hidden_neurons, output_neurons, it):
	iris = datasets.load_iris()
	#se cargan los datos de IRIS
	datos = iris.data[:50*hidden_neurons ]
	#se normalizan los datos
	datos = (datos - datos.min(axis=0))/(datos.max(axis=0)-datos.min(axis=0))
	#se obtienen las clases de cada entrada
	clases = iris.target[:50*hidden_neurons]
	#tamaño de poblacion
	P = len(datos)
	#longitud de cada entrada
	d = len(datos[0])
	idx = np.random.permutation(P)
	#conjunto de datos de entrenamiento
	datos_e = np.array(datos[idx[:int(P*.75)]])
	clases_e = np.array(clases[idx[:int(P*.75)]])

	#conjunto de datos de prueba
	datos_p = np.array(datos[idx[int(P*.75):]])
	clases_p = np.array(clases[idx[int(P*.75):]])


	return FFNN(datos_e, clases_e, datos_p, clases_p, hidden_neurons, output_neurons, it)



error_ = []
exact_ = []
#experimentacion: dos clases : neurona de salida
print('\nexperimentacion: dos clases : neurona de salida')
for i in range(30):
	error, exact = run(2,1, i)
	error_.append(error)
	exact_.append(exact)
print('\n\tError Cuadratico Medio Promedio:\t', sum(error)/4.0, '\n\tExactitud de clasificacion Promedio:\t', sum(exact)/4.0)



error_ = []
exact_ = []
#experimentacion: multiples clases : multiples neuronas de salida
print('\nexperimentacion: multiples clases : multiples neuronas de salida')
for i in range(30):
	error, exact = run(3,2, i) #3 clases : 2 neuronas