import matplotlib.pyplot as plt
import numpy as np
import math

rnd = []
gr1 = []
gr2 = []
gr3 = []
ag1 = []
ag2 = []

_rnd = []
_gr1 = []
_gr2 = []
_gr3 = []
_ag1 = []
_ag2 = []

file1 = open('Resultados/ESTADISTICAS_RND.txt')
file2 = open('Resultados/ESTADISTICAS_GR1.txt')
file3 = open('Resultados/ESTADISTICAS_GR2.txt')
file4 = open('Resultados/ESTADISTICAS_GR3.txt')
file5 = open('Resultados/ESTADISTICAS_AG1.txt')
file6 = open('Resultados/ESTADISTICAS_AG2.txt')

for f in file1.readlines():rnd.append(int(f))

for f in file2.readlines():gr1.append(int(f))

for f in file3.readlines():gr2.append(int(f))

for f in file4.readlines():gr3.append(int(f))

for f in file5.readlines():ag1.append(int(f))

for f in file6.readlines():ag2.append(int(f))

promedio_rnd = round(sum(rnd)/len(rnd), 2)
for a in rnd:_rnd.append((a - promedio_rnd)**2)
desviacion_rnd = round(math.sqrt(sum(_rnd)/len(_rnd)), 2)

promedio_gr1 = round(sum(gr1)/len(gr1), 2)
for a in gr1:_gr1.append((a - promedio_gr1)**2)
desviacion_gr1 = round(math.sqrt(sum(_gr1)/len(_gr1)), 2)

promedio_gr2 = round(sum(gr2)/len(gr2), 2)
for a in rnd:_gr2.append((a - promedio_gr2)**2)
desviacion_gr2 = round(math.sqrt(sum(_gr2)/len(_gr2)), 2)

promedio_gr3 = round(sum(gr3)/len(gr3), 2)
for a in gr3:_gr3.append((a - promedio_gr3)**2)
desviacion_gr3 = round(math.sqrt(sum(_gr3)/len(_gr3)), 2)

promedio_ag1 = round(sum(ag1)/len(ag1), 2)
for a in ag1:_ag1.append((a - promedio_ag1)**2)
desviacion_ag1 = round(math.sqrt(sum(_ag1)/len(_ag1)), 2)

promedio_ag2 = round(sum(ag2)/len(ag2), 2)
for a in ag2:_ag2.append((a - promedio_ag2)**2)
desviacion_ag2 = round(math.sqrt(sum(_ag2)/len(_ag2)), 2)

for i in range(len(rnd)):
	rnd[i] = (rnd[i]-promedio_rnd) / desviacion_rnd

for i in range(len(gr1)):
	gr1[i] = (gr1[i]-promedio_gr1) / desviacion_gr1

for i in range(len(gr2)):
	gr2[i] = (gr2[i]-promedio_gr2) / desviacion_gr2

for i in range(len(gr3)):
	gr3[i] = (gr3[i]-promedio_gr3) / desviacion_gr3

for i in range(len(ag1)):
	ag1[i] = (ag1[i]-promedio_ag1) / desviacion_ag1

for i in range(len(ag2)):
	ag2[i] = (ag2[i]-promedio_ag2) / desviacion_ag2

print(rnd)
print(gr1)
print(gr2)
print(gr3)
print(ag1)
print(ag2)

# Random test data
np.random.seed(123)
##all_data = [np.random.normal(12,23,23) for std in range(1, 7)]
all_data = [rnd, gr1, gr2, gr3, ag1, ag2]
fig, ax = plt.subplots(figsize=(9, 4))

# rectangular box plot
bplot1 = ax.boxplot(all_data,
                         vert=True,   # vertical box aligmnent
                         patch_artist=True)   # fill with color


ax.set_xticklabels( ['RND', 'GR1', 'GR2', 'GR3', 'AG1', 'AG2'] )
ax.set_ylabel('Desempeño General')

plt.show()