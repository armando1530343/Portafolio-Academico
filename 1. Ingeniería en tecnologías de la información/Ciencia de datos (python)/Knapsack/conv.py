import os, sys
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc

filename = 'COMPETENCIA'

file1 = open('Resultados/' + filename +'_PROMEDIOS_CONVERGENCIA_AG1.txt')
file2 = open('Resultados/' + filename +'_APTITUDES_CONVERGENCIA_AG1.txt')
file3 = open('Resultados/' + filename +'_PROMEDIOS_CONVERGENCIA_AG2.txt')
file4 = open('Resultados/' + filename +'_APTITUDES_CONVERGENCIA_AG2.txt')
promedios1 = []
aptitudes1 = []
promedios2 = []
aptitudes2 = []

for f in file1.readlines():
	promedios1.append(int(f))

for f in file2.readlines():
	aptitudes1.append(int(f))

for f in file3.readlines():
	promedios2.append(int(f))

for f in file4.readlines():
	aptitudes2.append(int(f))

file1.close()
file2.close()
file3.close()
file4.close()

print(np.array(aptitudes1))

plt.title("Grafica de Convergencia Problema PKx")
plt.xlabel("Generacion")
plt.ylabel("Aptitud")

p1=plt.plot(aptitudes1,label="AG1 (Aptitud)")
p2=plt.plot(promedios1,label="AG1 (Promedio)")
p1=plt.plot(aptitudes2,label="AG2 (Aptitud)")
p2=plt.plot(promedios2,label="AG2 (Promedio)")
plt.legend() 

plt.show()