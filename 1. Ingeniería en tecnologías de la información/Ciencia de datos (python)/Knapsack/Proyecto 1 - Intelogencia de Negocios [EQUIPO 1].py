import numpy as np
import matplotlib.pyplot as plt
from random import *
import itertools
import math




#se crea la clase que contiene cada uno de los algoritmos como funciones
class Knapsack:
	#guarda los mejores objetos
	mejor_solucion = []
	num_individuos = 100#tamaño de la poblacion|
	criterio_terminacion = 100
	activos_solucion = 0

	valores_solucion = []
	def __init__(self):
		print ('Knapsack\n')

	def read(self, instancia):
		self.objetos = [] #guarda la objetos de cada uno de los archivos que se leen
		self.num_objetos = 0
		self.capacidad_mochila = 0
		#nombre del archivo
		text = 'Knapsack_Problem_Instances/' + instancia + '.txt'
		#se lee el archivo de prueba
		#'instancia' se refiere al nombre del archivo que se encuantra dentro de la carpeta 'Knapsack_Problem_Instances/'
		archivo = open(text,'r')
		numChars = 0
		i = 0
		for lin in archivo:
			if i > 2:
				for c in lin: numChars += 1
			i += 1

		#print(numChars)
		archivo.close()

		archivo = open(text,'r')
		i = 0
		n = 0
		chars = 0
		for linea in archivo:
			if i == 0: self.num_objetos = int(linea)
			if i == 1: self.capacidad_mochila = int(linea)
			if i > 2: # empieza a guardar los datos leidos a partir de la cuarta linea de cada instancia
				nvalinea = ''
				obj = []
				#se recorreon los caracteres de cada linea del archivo
				for car in linea:
					#print(car)
					chars += 1
					#ignora los espacios y los saltos de linea
					if car != '\t' and car != '\n':
						#se suma a la variable solo los caracteres numericos
						nvalinea += car
						if chars < numChars: continue
					obj.append(int(nvalinea))
					nvalinea = ''
				self.objetos.append(obj)
			i+=1
		#self.objetos = np.array(self.objetos);

		archivo.close()
		print("<<ARCHIVO: ", instancia, ">>")
		print ('NUMERO DE OBJETOS = ',self.num_objetos)
		print ('CAPACIDAD MOCHILA = ',self.capacidad_mochila)
		print ('\nOBJETOS [VALOR, COSTO]:\n', self.objetos)
		return self.capacidad_mochila

	#DESORDENAMIENTO DE INDICES DE LOS OBJETOS
	def permutacion(self, numero):
		#variable que guardara la objetos en orden aleatorio
		rnd_objetos = []
		#se inicializan los valores de la nueva objetos solo para la generacion de los indices del vector
		for i in range(numero):
			rnd_objetos.append(0)

		i = 0
		#proceso de ordenamiento de indices de la objetos
		#se recorre el vector de objetos el cual cada indice contiene dos valores que indican el valor
		#y el peso del objeto
		for p in range(numero):
			indice = 0 #se inicializa una nueva variable
			if i == 0:
				#se hace la primera generacion aleatoria de los indices para el que sera guardado el objeto
				indice = randint(0,numero-1)
				rnd_objetos[indice] = p
			else:
				while True:
					indice = randint(0,numero-1)
					if rnd_objetos[indice] == 0:
						break
			rnd_objetos[indice] = p
			i += 1
		return rnd_objetos

	#funcion que desordena los indices de cada objeto de una instancia
	def RND(self):
		self.mejor_solucion = np.zeros(self.num_objetos)
		#variable que guardara la objetos en orden aleatorio
		rnd_objetos = self.permutacion(self.num_objetos)

		costo = 0

		for i in rnd_objetos:
			aux = costo
			costo += self.objetos[i][0]
			if costo < self.capacidad_mochila:
				self.mejor_solucion[i] = 1
			else:
				costo = aux 
				break

		valores = []
		activos = 0
		for i in range(self.num_objetos):
			if self.mejor_solucion[i] == 1:
				valores.append(self.objetos[i][0]) 
				activos += 1

		self.activos_solucion = activos 
		#print('-----------------------------------------------------------------')
		#print ('\nRND\n',rnd_objetos)
		#print ('\nRND: SOLUCION: ',self.mejor_solucion)
		self.valores_solucion = valores

		if len(self.valores_solucion) == 0: divisor = 1
		else: divisor = len(self.valores_solucion)

		num = []
		promedio = round(sum(self.valores_solucion) / divisor, 2)
		for v in self.valores_solucion:
			num.append((v - promedio)**2)

		if len(num) == 0: divisor = 1
		else: divisor = len(num)

		desviacion = round(math.sqrt(sum(num) / divisor), 2)

		return costo, promedio, desviacion

	"""
	valor[1], costo[1]
	valor[2], costo[2]
	valor[N], costo[N]
	"""
	#funcion que organiza la objetos por orden decreciente por valor
	#funcion que organiza la objetos por orden asencente por valor o objetos
	#funcion que organiza la objetos por orden decreciente por valor/costo
	def GR(self, numGR):
		gr = False
		string = ''
		self.mejor_solucion = []
		for i in range(self.num_objetos): self.mejor_solucion.append(0)
		auxObjetos = [x[:] for x in self.objetos]
		indices_objetos = []
		for i in range(self.num_objetos): indices_objetos.append(i)

		indice = 0

		for j in range(self.num_objetos):
			for i in range(self.num_objetos):
				if i > 0:
					if numGR == 1:
						gr = auxObjetos[i][0] > auxObjetos[i-1][0]
						string = '\nGR1 (VALOR -)\n'
						indice = 0
					elif numGR == 2:
						gr = auxObjetos[i][1] < auxObjetos[i-1][1]
						string = '\nGR2 (COSTO +)\n'
						indice = 1
					elif numGR == 3:
						gr = (auxObjetos[i][0]/auxObjetos[i][1]) > (auxObjetos[i-1][0]/auxObjetos[i-1][1])
						string = '\nGR3 (VALOR/COSTO -)\n'
						indice = 2

					if gr:
						aux = indices_objetos[i-1] 
						indices_objetos[i-1] = indices_objetos[i]
						indices_objetos[i] = aux
						aux = auxObjetos[i-1]
						auxObjetos[i-1] = auxObjetos[i]
						auxObjetos[i] = aux
				i += 1
			j+=1

		#print(auxObjetos)
		#a = input()

		valor = 0
		for i in indices_objetos:
			aux = valor
			if indice != 2:
				valor += self.objetos[i][1]
			else:
				valor += (self.objetos[i][0])
			
			if valor < self.capacidad_mochila:
				self.mejor_solucion[i] = 1
			else:
				valor = aux
				break

		return self.mejor_solucion, valor

	def AG(self, num_genetico, semilla):
		#semilla generadora de numeros aleatorios
		seed(semilla)
		promedios = []
		aptitudes = []

		self.genetico = num_genetico


		self.poblacion = self.inicializacion(num_genetico)
		#print('\nPOBLACION DE INDIVIDUOS PADRES\n', np.array(self.poblacion))
		#self.mejor_solucion = []
		auxPoblacion1 = [x[:] for x in self.poblacion]

		basura, apt, prom_apt = self.fitness_evaluation(auxPoblacion1, self.num_individuos)
		#aptitudes.append(apt)
		#promedios.append(prom_apt)

		#print('\nPOBLACION DE INDIVIDUOS PADRES\n', np.array(self.poblacion))
		print('comienza AG',num_genetico)

		for criterio in range(99):
			#print('Poblacion:\n', np.array(self.poblacion))

			#self.poblacion_hijos = []
			#for i in range(self.num_individuos): self.poblacion_hijos.append(0)
			self.poblacion_hijos = self.mating_selection()


			#a = input()

			auxPoblacion2 = [x[:] for x in self.poblacion_hijos]

			i = 0
			while i < self.num_individuos-1:
				self.poblacion_hijos[i], self.poblacion_hijos[i+1] = self.operador_cruza(auxPoblacion2[i], auxPoblacion2[i+1],1)
				i += 2
			#self.poblacion_hijos = np.array(self.poblacion_hijos)

			#print("Padres:\n",np.array(self.poblacion))
			#print("hijos:\n",np.array(self.poblacion_hijos))
			#print("\nPOBLACION DE HIJOS (CRUZA)\n", self.poblacion_hijos)
			#a = input()
			
			self.mutacion()
			#a = input()
			#print("Padres:\n",np.array(self.poblacion))

			promedio_aptitudes = self.supervivencia(1)

			#print('Valores_solucion: ',self.valores_solucion)
			#a = input()

			#print('PROMEDIO: ', promedio_aptitudes)
			promedios.append(promedio_aptitudes)

			
			#a = input()
			#print("\nNUEVA POBLACION DE PADRES\n", np.array(self.poblacion))
			#print(self.aptitud)

			#print ('AQUI COMIENZA LAS SOLUCIONES')

			#print(np.array(self.nvapoblacion))
			self.mejor_solucion, self._aptitud, promedio_aptitudes = self.fitness_evaluation(self.poblacion, 1)
			#print(promedio_aptitudes)
			aptitudes.append(self._aptitud)
			#print(self._aptitud)
			#print('Promedio Aptitudes: ',promedio_aptitudes)
			#a=input()
			

		#print('\nMEJOR SOLUCION: ', self.mejor_solucion, ' APTITUD: ', self._aptitud)
		num = []
		promedio = round(sum(self.valores_solucion) / len(self.valores_solucion), 2)
		for v in self.valores_solucion:
			num.append((v - promedio)**2)

		desviacion = round(math.sqrt(sum(num) / len(num)), 2)

		"""
		print("\nSolucion: ", self.mejor_solucion)
		print("Valores: ", self.valores_solucion)
		print('Promedio: ',promedio)
		print("Numeros: ", num)
		print('Desviacion: ',desviacion)
		"""

		return self._aptitud, promedio, desviacion, aptitudes, promedios

	
	
	def inicializacion(self, tipo):
		P = [] #poblacion

		for p in range(self.num_individuos):
			individuo = [] #cadena binaria que representa el numero de objetos
			for p in range(self.num_objetos):individuo.append(0)
			#print(individuo)
			if tipo == 1:
				if p == 0:
					#if tipo == 1:
					for i in range(self.num_objetos):
						individuo[i] = randint(0,1)
					#else:
						#individuo, basura = self.GR(1)
				else:
					while True:
						#if tipo == 1:						
						for i in range(self.num_objetos):
							individuo[i] = randint(0,1)
						#else:
							#individuo, basura = self.GR(1)

						if not individuo in P:
							break
			else:
				individuo, basura = self.GR(1)					

			P.append(individuo)
			#print('P: ',np.array(P))
			#print('individuo: ', individuo)
			
		#print('\nPOBLACION DE INDIVIDUOS PADRES\n', np.array(P))

		return P

	#APAREAMIENTO / VARIACION
	def mating_selection(self):

		#se crea el arreglo de poblacion de hijos y se inicializa con un ciclo for
		poblacion_hijos = []
		for p in range(self.num_individuos): poblacion_hijos.append(0)

		#se hace una permutacion de los indices de los objetos
		variacion = self.permutacion(self.num_individuos)
		#print('\nSELECCION DE APAREAMIENTO\n', variacion)
		auxPoblacion = [x[:] for x in self.poblacion]
		i = 0
		while i < self.num_individuos-1:
			poblacion_hijos[i] = auxPoblacion[variacion[i+1]]
			poblacion_hijos[i+1] = auxPoblacion[variacion[i]]
			i+=2

		#poblacion_hijos = np.array(poblacion_hijos)


		#print('\nPOBLACION DE HIJOS (APAREAMIENTO/VARIACION)\n', poblacion_hijos)
		return poblacion_hijos

	def operador_cruza(self, padre1, padre2, tipo):
		
		#Operador de Cruza: 1 Punto
		if tipo == 1:
			p = randint(0, self.num_objetos-1)
			#print('Punto de cruza: ',p)
			while p < self.num_objetos:
				Pc = random()
				
				if Pc >= .8:
					#print('Prob: ', Pc)
					aux = padre1[p]
					padre1[p] = padre2[p]
					padre2[p] = aux
				p += 1

		#Operador de Cruza: 2 Puntos
		elif tipo == 2:
			p1 = randint(0, self.num_objetos-1)
			p2 = 0
			while p2 < p1:
				p2 = randint(0, self.num_objetos-1)

			#print('Punto1: ',p1, ' Punto2: ',p2)
			while p1 <= p2:
				Pc = random()
				if Pc >= .8:
					#print('Prob: ', Pc)
					aux = padre1[p1]
					padre1[p1] = padre2[p1]
					padre2[p1] = aux
				p1 += 1

		#Operador de Cruza: Uniforme
		else:
			for i in range(self.num_objetos):
				Pc = random()
				if Pc >= .5:
					#print('Prob: ', Pc)
					aux = padre1[i]
					padre1[i] = padre2[i]
					padre2[i] = aux

		return padre1, padre2

	def mutacion(self):
		i = 0
		for hijos in self.poblacion_hijos:
			for bit in range(len(hijos)):				
				Pm = 1/self.num_objetos
				Pc = random()
				if Pc <= Pm:
					#print('Proba[',i,'][',bit,']: ',Pc)
					if hijos[bit] == 1: hijos[bit] = 0
					else: hijos[bit] = 1
			i += 1

		#print('\nMUTACION\n',self.poblacion_hijos)
		
	def aptitud(self, solucion):
		valor_total = 0
		peso_total = 0
		apt_sum = 0


		
		for s in range(self.num_objetos):
			if solucion[s] == 1:
				valor_total += self.objetos[s][0]
				apt_sum = valor_total
				peso_total += self.objetos[s][1]

		if peso_total <= self.capacidad_mochila:
			apt = valor_total
		else:
			apt = 0

		#print('capacidad: ', self.capacidad_mochila)
		#print('valor: ', apt)
		#a = input()

		#print('solucion: ',solucion, 'total: ',apt_sum)

		#print('Valor total:', valor_total, ' -- Peso Total:', peso_total, ' -- Aptitud:', apt)
		#a = input()

		return apt, apt_sum

	def fitness_evaluation(self, _poblacion, num_mejores):
		#print('\nAPTITUDES DE POBLACION')
		aptitudes = []
		suma_aptitudes = []
		best_aptitudes = []
		best_individuos = []
		for i in range(len(_poblacion)):
			apt, suma = self.aptitud(_poblacion[i])
			#print(_poblacion[i])
			aptitudes.append(apt)
			suma_aptitudes.append(suma)

		#promedio_aptitudes = sum(suma_aptitudes)/self.num_individuos
		#print (sum(suma_aptitudes))


		#aptitudes = np.array(aptitudes)
		aux_aptitudes = []
		new_poblacion = []
		indices = []

		#print((_poblacion))
		#print(aptitudes)

		i = 0
		while(len(aux_aptitudes) <= len(aptitudes)):
			x = max(aptitudes)
			aux_aptitudes.append(x)
			indices.append(aptitudes.index(x))
			aptitudes[aptitudes.index(x)] = 0

		#print(aux_aptitudes)
		#print(indices)


		#promedio_aptitudes = sum(aux_aptitudes)/self.num_individuos

		"""
		for i in range(self.num_individuos):
			for j in range(self.num_individuos):
				if j > 0:
					if aptitudes[j] > aptitudes[j-1]:
						aux = aptitudes[j]
						aptitudes[j] = aptitudes[j-1]
						aptitudes[j-1] = aux
						aux = _poblacion[j]
						_poblacion[j] = _poblacion[j-1]
						_poblacion[j-1] = aux
		"""
		##print('Objetos: ', self.objetos)
		#print('Aptitudes: ', aux_aptitudes)
		"""
		if len(_poblacion) > self.num_individuos and self.genetico == 1:
			#print('Len: ', len(indices))

			i = 0
			while len(best_individuos) < num_mejores:
				#print(_poblacion[indices[i]])
				
				if not _poblacion[indices[i]] in best_individuos:
					best_aptitudes.append(aux_aptitudes[i])
					best_individuos.append(_poblacion[indices[i]])
				i+=1
		else:"""	

		for i in range(num_mejores):
			best_aptitudes.append(aux_aptitudes[i])
			best_individuos.append(_poblacion[indices[i]])

		promedio_aptitudes = sum(aux_aptitudes)/len(aux_aptitudes)
			

		activos = 0	
		valores = []
		#if num_mejores == 1:			
		for i in best_individuos:
			for j in range(self.num_objetos):
				if i[j] == 1:
					valores.append(self.objetos[j][0])
					activos += 1

		self.valores_solucion = valores

		self.activos_solucion = activos 

		#best_individuos = np.array(best_individuos)

		#print('\nMEJORES APTITUDES DE POBLACION\n',best_aptitudes)
		#print('\nMEJORES ',num_mejores,' INDIVIDUOS DE POBLACION\n',best_individuos)

		return best_individuos, best_aptitudes, promedio_aptitudes

	def supervivencia(self, num):
		#SELECCION PARA SUPERVIVENCIA----------------------------------------------------
		#print("Padres:\n",np.array(self.poblacion))
		#print("hijos:\n",np.array(self.poblacion_hijos))


		union_poblacion = []
		mejor_mitad = []

		if num == 1:
			#-------Seleccion "+"
			for i in range(self.num_individuos):
				union_poblacion.append(self.poblacion[i])



			for i in range(self.num_individuos):
				union_poblacion.append(self.poblacion_hijos[i])

			auxUnion = [x[:] for x in union_poblacion]


			#print('Poblacionnn: ',auxUnion)


			mejor_mitad, basura1, promedio = self.fitness_evaluation(auxUnion, self.num_individuos)
			#print("\nNUEVA POBLACION DE PADRES\n", np.array(mejor_mitad))
			#print(max(basura1))
			
			"""
			padres, basura1, basura2 = self.fitness_evaluation(self.poblacion, int(self.num_individuos/2))
			hijos, basura1, basura2 = self.fitness_evaluation(self.poblacion_hijos, int(self.num_individuos/2))

			self.nvapoblacion = []

			for i in range(int(self.num_individuos/2)):
				self.nvapoblacion.append(padres[i])

			for i in range(int(self.num_individuos/2)):
				self.nvapoblacion.append(hijos[i])
			

		elif num == 2:

			#--------Seleccion ","

			padres, basura1, basura2 = self.fitness_evaluation(self.poblacion, 1)
			hijos, basura1, basura2 = self.fitness_evaluation(self.poblacion_hijos, self.num_individuos-1)

			self.nvapoblacion = []

			self.nvapoblacion.append(padres)

			for i in range(int(self.num_individuos-1)):
				self.nvapoblacion.append(hijos[i])
			"""

		self.poblacion = [x[:] for x in mejor_mitad]
		return promedio








kp = 20
f = 1
"""
problema = []
rnd = []
gr1 = []
gr2 = []
gr3 = []
ag1 = []
ag2 = []
"""
conjunto_datos = []
for p in range(1):

	datos = Knapsack()

	if p > 11: kp = 50
	file = ''
	if f <= 9: file = 'KP'+ str(kp) + '_0' + str(f)
	else: file = 'KP'+ str(kp) + '_' + str(f)
	print(file)
	f+=1

	if f > 12: f = 1

	file = 'KP20_01'
	capacidad = datos.read(file)
	filename = 'CAPACIDAD: ' + str(capacidad)
	a, p, d = datos.RND()
	basura, gr1 = datos.GR(1)
	basura, gr2 = datos.GR(2)
	basura, gr3 = datos.GR(3)
	ag1 = []
	ag2 = []
	
	valores = []
	aptitud = []
	for i in range(10):
		apt, promedio, desviacion, best_apt, prom = datos.AG(1,23)
		ag1 = [['Aptitud: ' + str(apt)],['Promedio: ' + str(promedio)], ['Desviacion: ' + str(desviacion)]]

		apt2, promedio2, desviacion2, best_apt2, prom2 = datos.AG(2,i)
		ag2 = [['Aptitud: ' + str(apt2)],['Promedio: ' + str(promedio2)], ['Desviacion: ' + str(desviacion2)]]

		##print(prom)
		##print(prom2)

		if file == 'KP50_12' and i == 0:
			print ("GRAFICA")
			
			plt.title("Grafica de Convergencia Problema PKx")
			plt.xlabel("Generacion")
			plt.ylabel("Aptitud")

			p1=plt.plot(best_apt,label="AG1 (Aptitud)")
			p2=plt.plot(prom,label="AG1 (Promedio)")
			p3=plt.plot(best_apt2,label="AG2 (Aptitud)")
			p4=plt.plot(prom2,label="AG2 (Promedio)")
			plt.legend() 

			plt.show()
			
						

	conjunto_datos.append([filename, ['Aptitud: ' + str(a), 'Promedio: ' + str(p), 'Desviacion: ' + str(d)], gr1, gr2, gr3, ag1, ag2])


print("<< RESULTADOS >>\n")

for i in range(len(conjunto_datos)):
	print('------------------------------------------')
	print('PROBLEMA: ', conjunto_datos[i][0])
	print('RND: ', conjunto_datos[i][1])
	print('GR1: ', conjunto_datos[i][2])
	print('GR2: ', conjunto_datos[i][3])
	print('GR3: ', conjunto_datos[i][4])
	print('AG1: ', conjunto_datos[i][5])
	print('AG2: ', conjunto_datos[i][6])
