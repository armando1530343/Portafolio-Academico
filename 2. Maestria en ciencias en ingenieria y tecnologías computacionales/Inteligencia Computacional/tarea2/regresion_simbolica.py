import numpy as np

#----------------- PROGRAMACION GENETICA CARTESIANA ------------------ #
#------------------------- REGRESION SIMBOLICA ----------------------- #


#----------entradas del grafo-------

filas = 3		#numero de filas del grafo
columnas = 5	#numero de columnas del grafo
entradas = 2	#cantidad de entradas a operar
salidas = 1		#cantidad de posibles resultados
operadores = 7	#cantidad de operadores a utilizar
nodos = entradas + (filas*columnas) + salidas #total de nodos del grafo

#salida de todos los nodos (genes) + el nodo de salida (resultado)
output_nodes = np.zeros(nodos)

#----------------------------------

def get_gen(id_columna=1):
	#el primer elemento del gen se refiere al operador
	'''
	valores de operadores:
	0 : suma
	1 : resta
	2 : multiplicacion
	3 : division
	4 : potencia
	5 : seno
	6 : coseno
	'''

	#se define el operador aleatorio
	operador = np.random.randint(0,operadores)

	#en caso de que el operador sea unitario (seno o coseno) la longitud del gen seria 2 (operador y numero)
	entradas_nodo = 0

	if(operador > 4):#operadores binarios
		entradas_nodo = 1
	else:
		entradas_nodo = entradas

	#print('operador:', operador, ' entradas:', entradas_nodo)

	#la longitud del seria el numero de entradas mas el valor del operador
	gen = np.zeros(entradas_nodo + 1)
	gen[0] += operador

	#se rellenan los elementos restantes con valores aleatorios(numero de nodo)
	
	gen[1] = np.random.randint(0, filas*id_columna) #primer operando

	#caso de operadores binarios
	if gen[0] <= 3:
		
		gen[2] = np.random.randint(0, filas*id_columna) #segundo operando

		#restriccion: caso de division por cero
		if gen[0] == 3: #caso de division (id:3)
			gen[2] = np.random.randint(1, filas*id_columna)	
		else:
			gen[2] = np.random.randint(0, filas*id_columna)

	return gen

def get_cromosoma():

	#se crea el arreglo del cromosoma
	chrom = []
	#se crean la cantidad de genes como nodos existan sin contar los nodos de entrada
	col = 1
	#print('nodos:', nodos-entradas)
	for i in range(nodos-entradas-salidas):
		#se almacena un gen de forma aleatoria al cromosoma
		chrom.append(get_gen(id_columna=col))
		if i % filas-1 == 0:
			col += 1

	#se genera un nodo aleatorio el cual recibe el resultado de la ecuacion
	output_nodes[nodos-1] = np.random.randint(nodos-1)

	return np.array(chrom)

def execute_gen(id_gen, cromosoma, f=True):
	global output_nodes
	#print('id_gen:',len(cromosoma))
	operador_signo = ['+','-','*','/','^','sen ','cos ']
	operador = cromosoma[id_gen][0]


	salida_gen = 0
	ecuacion = ''
	operandos = []

	for i in range(1, len(cromosoma[id_gen])):
		#se almacenan los operandos del gen actual (posiciones 1 y 2 del gen)
		operandos.append(output_nodes[int(cromosoma[id_gen][i])])
		if i == 1:
			if len(cromosoma[id_gen]) == 2:
				ecuacion += (operador_signo[int(operador)] + str(output_nodes[int(cromosoma[id_gen][i])]))
			else:
				ecuacion += str(output_nodes[int(cromosoma[id_gen][i])])
		else:
			ecuacion += (operador_signo[int(operador)] + str(output_nodes[int(cromosoma[id_gen][i])]))

	if operador == 0: #suma
		salida_gen = operandos[0] + operandos[1]

	elif operador == 1: #resta
		salida_gen = operandos[0] - operandos[1]

	elif operador == 2: #multiplicacion
		salida_gen = operandos[0] * operandos[1]

	elif operador == 3: #division
		if operandos[1] == 0: salida_gen = 0
		else: salida_gen = operandos[0]/operandos[1]

	elif operador == 4: #potencia
		salida_gen = pow(operandos[0], 2)

	elif operador == 5:#seno
		salida_gen = np.sin(operandos[0])

	elif operador == 6:#coseno
		salida_gen = np.cos(operandos[0])


	if f == True:
		output_nodes[entradas + id_gen] = salida_gen

	return ecuacion


def operaciones(cromosoma):

	#se recorre el cromosoma
	for i in range(len(cromosoma)):
		execute_gen(i, cromosoma, f=True)
	
	#se devuelve el ultimo elemento del vector de salidas (resultado final)	
	return output_nodes[int(output_nodes[nodos-1])]

def get_ecuacion(cromosoma):

	ecuaciones = np.array([])
	#se recorre el cromosoma
	for i in range(len(cromosoma)):
		ecuaciones = np.append(ecuaciones, '(' + execute_gen(i, cromosoma, f=False) + ')')
	
	#se devuelve el ultimo elemento del vector de salidas (resultado final)	
	return ecuaciones


def mutacion(cromosoma):
	#se selecciona uno de los genes sin contar las entradas
	id_gen = np.random.randint(nodos-entradas) + entradas

	#se muta el ultimo nodo (nodo que obtiene el resultado)
	if id_gen == nodos-1:
		output_nodes[id_gen] = np.random.randint(nodos-1)

	#se muta gen con funcion de operacion
	else:

		r = int((id_gen-entradas)/filas)*filas + entradas

		#caso de gen con operacion unaria
		if len(cromosoma[id_gen - entradas]) == 2:
			#se selecciona algun elemento de los genes sin afectar el operador (primer elemento)
			id_item = np.random.randint(entradas)
			
			if id_item == 0:
				#se modifica el operador unario
				cromosoma[id_gen - entradas][id_item] = np.random.randint(5, operadores)
			else:
				#se modifica el elemento 'id_item' del gen 'id_gen' del cromosoma
				cromosoma[id_gen - entradas][id_item] = np.random.randint(0, r)
		
		#caso de gen con operacion binaria
		else:
			#se selecciona algun elemento de los genes sin afectar el operador (primer elemento)
			id_item = np.random.randint(entradas+1)

			if id_item == 0:
				#se modifica el operador binario
				cromosoma[id_gen - entradas][id_item] = np.random.randint(0, operadores-2)
			else:
				#se modifica el elemento 'id_item' del gen 'id_gen' del cromosoma
				cromosoma[id_gen - entradas][id_item] = np.random.randint(0, r)

	return cromosoma

def evaluacion(cromosoma, fit):
	result = operaciones(cromosoma)

	#se devuelve la diferencia mas cercana al resultado esperado (fit)
	if result > fit:
		return result - fit
	else:
		return fit - result

ECUACION = ''

def get_ecuacion2(cromosoma, id_gen):
	global ECUACION

	print('gen: ', cromosoma[id_gen])

	operador_signo = ['+','-','*','/','^','sin ','cos ']
	operator = operador_signo[int(cromosoma[id_gen][0])]

	#se obtienen los operandos del gen del cromosoma
	operando1 = output_nodes[ int(cromosoma[id_gen][1]) ]

	if cromosoma[id_gen][0] <= 4:	
		operando2 = output_nodes[ int(cromosoma[id_gen][2]) ]
		#se construye la ecuacion
		ECUACION += '(' + str(operando1) + operator + str(operando2) + ')'
	else:
		#se construye la ecuacion
		ECUACION += '(' + operator + '(' +str(operando1) + '))'

	if id_gen == 0 or id_gen == 1:
		print('AQUI')
		return ECUACION
	else:
		id_1 = int(cromosoma[id_gen][1])-entradas
		if len(cromosoma[id_gen]) == 3:
			id_2 = int(cromosoma[id_gen][2])-entradas
			return ECUACION + get_ecuacion2(cromosoma, id_1) + get_ecuacion2(cromosoma, id_2)
		else:
			return ECUACION + get_ecuacion2(cromosoma, id_1)


	#for i in range(1, len(cromosoma[id_gen])):
		#g = get_ecuacion(cromosoma, int(cromosoma[id_gen][i]))
	
def print_cromosoma(cromosoma):
	crom = ''
	for gen in cromosoma:
		gen_ = ''
		for g in gen:
			gen_ += str(int(g))

		crom += gen_ + ' '

	print('> Cromosoma:\n',crom)

def Estrategia_evolutiva(instancia):

	global input_nodes

	print('Entradas: {:f}  {:f}  {:f} '.format(instancia[0], instancia[1], instancia[2]))
	#print('nodo 1:',instancia[1])

	# se inicializan los nodes con los valores de entrada
	for i in range(entradas):
		output_nodes[i] = instancia[i]

	fit = instancia[2]
	#print('Objetivo:', fit)	

	#--------- Estrategia Evolutiva 1+4 ------------
	TMAX = 10000
	t = 0
	cromosoma = get_cromosoma() #se crea un individuo aleatorio
	#print('salidas:',list(output_nodes))
	#print_cromosoma(cromosoma)
	fx = evaluacion(cromosoma, fit)
	#print('salidas:',list(output_nodes))

	fit_global = fx
	
	while t < TMAX and fit_global != 0:
		#se generan 4 hijos del cromosoma original
		hijos = []
		for i in range(4):
			hijo = mutacion(cromosoma) #nuevo hijo
			fh = evaluacion(hijo, instancia[2]) #se evalua el hijo
			hijos.append([fh, hijo]) #se almacenan los dos datos
			
			if fh == 0.0:
				break

		best_hijo = min(hijos)[1] #se selecciona el mejor hijo de acuerdo al menor fit
		fu = min(hijos)[0] #se selecciona el fitness del mejor hijo
		
		#se compara el hijo con el padre para seleccionar al mejor
		if fu < fx:
			cromosoma = best_hijo.copy()	
			fx = fu
			fit_global = fu
			#print('fit: ', fu)
			
		if fu == 0:
			break

		t+=1

	result = output_nodes[int(output_nodes[nodos-1])]
	nodo_salida = output_nodes[nodos-1]

	#print('\n> fitness (distancia o diferencia entre el resultado obtenido con el objetivo):\n', fu)
	print_cromosoma(cromosoma)
	#print('\nresultados de cada gen (nodo):\n',list(output_nodes))
	print('> El nodo {:.1f} obtuvo la mejor salida: {:.5f}'.format(nodo_salida, result) )
	ecuaciones = get_ecuacion(cromosoma)
	#print('\necuaciones:\n',ecuaciones)
	#x, ecuaciones = operaciones(cromosoma)
	#node_result = output_nodes[nodos-1]
	#print('ecuacion: ',ecuaciones)
	#ecuacion = get_ecuacion(cromosoma, int(output_nodes[len(output_nodes)-1]) - entradas)
	#print(ecuacion)

	return result


#calculo del error cuadratico medio
def MSE(prediccion, salida_deseada):
	return np.sum((prediccion - salida_deseada)**2) / len(prediccion)

#corrida de un caso de prueba
def run(data):

	#columnas de resultados deseados del caso de prueba
	results = data[:,2]

	Error = [] #Error cuadratico medio de cada corrida

	#cada caso se corre 31 veces
	for i in range(30):

		output = [] #vector de salidas del algoritmo para cada entrada del caso de prueba
		#se recorren las instancias
		for j in range(len(data)):
			#cada instancia se ejecuta 30 veces
			print('\nExec.{:4d} Instancia:{:4d} '.format(i+1, j+1))
			output.append(Estrategia_evolutiva(data[j]))
			#break

		Error.append( MSE(results, output) )
		print('Error: ',Error[i])
		#break

#lectura de archivos de los casos de prueba
def get_instacia(filename):
	file = open(filename)
	data = []

	i = 0
	for f in file:
		if i >= 2:
			x = f.split(' ')
			data.append([float(x[0]),float(x[1]),float(x[2])])
		i+=1

	return np.array(data)

data1 = get_instacia('caso_prueba_1.txt')
data2 = get_instacia('caso_prueba_2.txt')
data3 = get_instacia('caso_prueba_3.txt')
data4 = get_instacia('caso_prueba_4.txt')

#SE PRUEBA EL CASO 1
run(data1)

