import numpy as np
def function(x):
	return np.sum(x*x, axis=1)

def ackley(x):
 return -20 * np.exp(-0.2* np.sqrt(0.5 * (x[:,0]*x[:,0] + x[:,1]*x[:,1] ))) - np.exp(0.5 * (np.cos(2.0 * np.pi * x[:,0]) +   np.cos(2 * np.pi * x[:,1]))) + np.exp(1) + 20.0


def pso(N, n, lb, ub, G, W, C1, C2, function):	
	x = lb + np.random.random((N,n)) * (ub -lb)
	v = np.zeros((N,n))
	fx = function(x)
	y = x.copy()
	fy = fx.copy()
	idx = np.argmin(fy)
	fy_hat = fy[idx]
	y_hat = y[idx]
	
	g = 0
	while g < G:
		v  = W*v + C1*np.random.random((N,n))*(y-x) + C2 * np.random.random((N,n))*(y_hat-x)
		x = x + v
		fx  = function(x)
		idx = fx < fy
		y[idx] = x[idx]
		fy[idx] = fx[idx]
		idx = np.argmin(fy)
		y_hat = y[idx]
		fy_hat = fy[idx]
		print(fy_hat)
		g += 1
	
	return [fy_hat, y_hat]
	
N = 10
n = 4
lb = -1.5
ub = 2.0
G = 70
W = 0.7
C1 = C2 = 1.4
my_funcs = {'sphere':[-1.5, 2.0, function],'ackley':[-32.768, 32.768, ackley] }

lb, ub, my_function = my_funcs['ackley']
fx, x = pso(N, n, lb, ub, G, W, C1, C2, my_function)
