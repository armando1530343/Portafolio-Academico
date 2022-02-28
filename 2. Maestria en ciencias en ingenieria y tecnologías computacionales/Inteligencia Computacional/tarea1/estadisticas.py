from math import *


real = open("real.txt")
binario = open("binario.txt")


fit_b = []
fit_r = []
for b in binario:
	fit_b.append(float(b))
for r in real:
	fit_r.append(float(r))


prom_b = sum(fit_b) / len(fit_b)
prom_r = sum(fit_r) / len(fit_r)

def sd(vector, prom):
	n = len(vector)
	plus = 0.0
	for x in vector:
		plus += abs(x - prom)**2

	return sqrt(float(plus) / n)



print fit_b, '\nPromedio: ', prom_b, '\nds:', sd(fit_b, prom_b) ,'\nbest:', max(fit_b), ' \n\n'
print fit_r, '\nPromedio: ', prom_r, '\nds:', sd(fit_r, prom_r) ,'\nbest:', min(fit_r), ' \n\n'