import matplotlib
import matplotlib.pyplot as plt
import numpy as np

files1 = [
open('Paralelo/N130k500v5^500t2_S_1H.txt'),
open('Paralelo/N130k500v5^500t2_S_2H.txt'),
open('Paralelo/N130k500v5^500t2_S_4H.txt'),
open('Paralelo/N130k500v5^500t2_S_8H.txt'),
open('Paralelo/N130k500v5^500t2_S_16H.txt'),
open('Paralelo/N130k500v5^500t2_S_32H.txt'),
open('Paralelo/N130k500v5^500t2_S_64H.txt'),
open('Paralelo/N130k500v5^500t2_S_128H.txt')
]
files2 = [
open('Paralelo/N210k800v6^800t2_S_1H.txt'),
open('Paralelo/N210k800v6^800t2_S_2H.txt'),
open('Paralelo/N210k800v6^800t2_S_4H.txt'),
open('Paralelo/N210k800v6^800t2_S_8H.txt'),
open('Paralelo/N210k800v6^800t2_S_16H.txt'),
open('Paralelo/N210k800v6^800t2_S_32H.txt'),
open('Paralelo/N210k800v6^800t2_S_64H.txt'),
open('Paralelo/N210k800v6^800t2_S_128H.txt')
]
files3 = [
open('Paralelo/N294k1000v7^1000t2_S_1H.txt'),
open('Paralelo/N294k1000v7^1000t2_S_2H.txt'),
open('Paralelo/N294k1000v7^1000t2_S_4H.txt'),
open('Paralelo/N294k1000v7^1000t2_S_8H.txt'),
open('Paralelo/N294k1000v7^1000t2_S_16H.txt'),
open('Paralelo/N294k1000v7^1000t2_S_32H.txt'),
open('Paralelo/N294k1000v7^1000t2_S_64H.txt'),
open('Paralelo/N294k1000v7^1000t2_S_128H.txt')
]
files4 = [
open('Paralelo/N392k1500v8^1500t2_S_1H.txt'),
open('Paralelo/N392k1500v8^1500t2_S_2H.txt'),
open('Paralelo/N392k1500v8^1500t2_S_4H.txt'),
open('Paralelo/N392k1500v8^1500t2_S_8H.txt'),
open('Paralelo/N392k1500v8^1500t2_S_16H.txt'),
open('Paralelo/N392k1500v8^1500t2_S_32H.txt'),
open('Paralelo/N392k1500v8^1500t2_S_64H.txt'),
open('Paralelo/N392k1500v8^1500t2_S_128H.txt')
]
files5 = [
open('Paralelo/N540k2000v9^2000t2_S_1H.txt'),
open('Paralelo/N540k2000v9^2000t2_S_2H.txt'),
open('Paralelo/N540k2000v9^2000t2_S_4H.txt'),
open('Paralelo/N540k2000v9^2000t2_S_8H.txt'),
open('Paralelo/N540k2000v9^2000t2_S_16H.txt'),
open('Paralelo/N540k2000v9^2000t2_S_32H.txt'),
open('Paralelo/N540k2000v9^2000t2_S_64H.txt'),
open('Paralelo/N540k2000v9^2000t2_S_128H.txt')
]

secuencial = [
open('Secuencial/N130k500v5^500t2_S.txt'),
open('Secuencial/N210k800v6^800t2_S.txt'),
open('Secuencial/N294k1000v7^1000t2_S.txt'),
open('Secuencial/N392k1500v8^1500t2_S.txt'),
open('Secuencial/N540k2000v9^2000t2_S.txt')
]

def getData(file):
	datos = []
	for f in file:
		datos.append(float(f))
	datos = np.array(datos)
	return datos#, datos[:,1]

def porc(a,b,c):
	return 'Operador1:' +str(20*a) + '% - '+' Operador2:' +str(20*b) + '% - ' + 'Operador3:' +str(20*c) + '%'

tit = 'Speedup vs Problem size vs Number of threads'

i = 4
times0=[]
times1=[]
times2=[]
times3=[]
times4=[]
times5=[]

#times2.append(min(getData(files2[0])))

for i in range(5):
	times0.append(max(getData(secuencial[i])))

for i in range(8):
	times1.append(min(getData(files1[i])))
	times2.append(min(getData(files2[i])))
	times3.append(min(getData(files3[i])))
	times4.append(min(getData(files4[i])))
	times5.append(min(getData(files5[i])))



instancias=[]
speedup=[]
efficiency=[]
hilos = [1,2,4,8,16,32,64,128]

fig, ax = plt.subplots()

ax.plot([1,2,3,4,5], times0, label='')

"""
ax.plot(hilos, times1, label='N130k500v5^500t2')
ax.plot(hilos, times2, label='N210k800v6^800t2')
ax.plot(hilos, times3, label='N294k1000v7^1000t2')
ax.plot(hilos, times4, label='N392k1500v8^1500t2')
ax.plot(hilos, times5, label='N540k2000v9^2000t2')
"""

fig.set_label('10 hijos')
ax.legend()
ax.set(xlabel='Number of Threads', ylabel='Execution Time',
       title=tit)
ax.grid()

plt.show()