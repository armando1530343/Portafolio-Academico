import matplotlib
import matplotlib.pyplot as plt
import numpy as np

def getData(file):
	file = open(file)
	datos = []
	for f in file:
		x = f.split(' ')
		#print(x)
		datos.append([int(x[0]), int(x[1]), int(x[2]), int(x[3])])
	datos = np.array(datos)
	return datos #datos[:,0], datos[:,1], datos[:,2], datos[:,3]

tit = 'Operadores de Mutacion: Instancia3 N=50 Q=800 CENTER=30'
instancia = 1

ga_data = []

for i in range(1, 11):
	ga_data.append(getData('data'+ str(i) +'.txt'))

print('\nGenetico/')
#print(ga_data)



fig, ax = plt.subplots()
for i in range(10):
	ax.plot(ga_data[i][:,0], ga_data[i][:,1], label='Instancia ' + str(i+1))
ax.legend()
ax.set(xlabel='Iteraciones', ylabel='Evaluacion(Costo)', 
	title='CMST Instances: Implementation with Genetic Algorithm')
ax.grid()
plt.show()