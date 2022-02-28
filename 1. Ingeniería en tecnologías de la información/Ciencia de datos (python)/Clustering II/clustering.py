import pandas as pd
import numpy as np
from sklearn.cluster import KMeans, AgglomerativeClustering
from sklearn.metrics import silhouette_score
from scipy.cluster.hierarchy import linkage, fcluster
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

data_names = ['UBICACIONES','CRIMENES_AREAS','UBICACIONES_AREAS','REPORTES_TIPOS_CRIMEN','REPORTES_ANUALES','REPORTES_MENSUALES']

title_plots = [
'Ubicacion de las fuerzas policiacas',
'Total de crimenes y area de la fuerza policiacas',
'Ubicacion y area de las fuerzas policiacas',
'Total de reportes para cada tipo de crimen',
'Total de reportes anuales',
'Total de reportes mensuales'
]


def read_data(file):
	dataset = []
	file = pd.read_csv('datasets/' + file + '.csv')
	x = []
	for f in file.columns:
		x.append(float(f))
	dataset.append(x)
	file = np.array(file)
	for f in file: dataset.append(f)
	dataset = np.array(dataset)

	return dataset


#SE OBTIENE EL DATASET 1
#--------------------------------------------------------------------------------
DATASETS = []
for data in data_names:
	DATASETS.append(read_data(data))

#DATASETS = np.array(DATASETS)

kmeans_silhouette_coefficient = [[],[],[],[],[],[]]
single_silhouette_coefficient = [[],[],[],[],[],[]]
average_silhouette_coefficient = [[],[],[],[],[],[]]
complete_silhouette_coefficient = [[],[],[],[],[],[]]

mejor_kmeans = [[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0]]
mejor_single = [[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0]]
mejor_average = [[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0]]
mejor_complete = [[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0]]

d = 0
data = DATASETS[2]
for data in DATASETS:
	print('\nDataset: ', title_plots[d])
	data = StandardScaler().fit_transform(data)

	for k in range(2,42):
		print('  k =', k)

		kmeans = KMeans(n_clusters=k).fit(data)
		kmeans_predict = kmeans.predict(data)
		silhouette = silhouette_score(data, kmeans_predict)
		kmeans_silhouette_coefficient[d].append(silhouette)
		if silhouette > mejor_kmeans[d][0]:
			mejor_kmeans[d][0] = silhouette
			mejor_kmeans[d][1] = kmeans_predict
			mejor_kmeans[d][2] = k

		single = linkage(data, 'single')
		single_predict = fcluster(single, k, criterion='maxclust')
		silhouette = silhouette_score(data, single_predict)
		single_silhouette_coefficient[d].append(silhouette)
		if silhouette > mejor_single[d][0]:
			mejor_single[d][0] = silhouette
			mejor_single[d][1] = single_predict
			mejor_single[d][2] = k

		average = AgglomerativeClustering(n_clusters=k, linkage='average').fit(data)
		average_predict = average.fit_predict(data)
		silhouette = silhouette_score(data, average_predict)
		average_silhouette_coefficient[d].append(silhouette)
		if silhouette > mejor_average[d][0]:
			mejor_average[d][0] = silhouette
			mejor_average[d][1] = average_predict
			mejor_average[d][2] = k

		complete = AgglomerativeClustering(n_clusters=k, linkage='complete').fit(data)
		complete_predict = complete.fit_predict(data)
		silhouette = silhouette_score(data, complete_predict)
		complete_silhouette_coefficient[d].append(silhouette)
		if silhouette > mejor_complete[d][0]:
			mejor_complete[d][0] = silhouette
			mejor_complete[d][1] = complete_predict
			mejor_complete[d][2] = k

	plt.title(title_plots[d])
	plt.xlabel("Numero de Clusters (k)")
	plt.ylabel("Coeficiente de silueta promedio")

	p1=plt.plot(kmeans_silhouette_coefficient[d],label="K-means")
	p2=plt.plot(single_silhouette_coefficient[d],label="Single Linkage")
	p3=plt.plot(average_silhouette_coefficient[d],label="Average Linkage")
	p4=plt.plot(complete_silhouette_coefficient[d],label="Complete Linkage")
	plt.legend()
	plt.show()

	algoritms = [mejor_kmeans[d], mejor_single[d], mejor_average[d], mejor_complete[d]]
	alg_name = ['Kmeans', 'Single Linkage', 'Average Linkage', 'Complete Linkage']

	if d == 0 or d == 1:
		if d==0:
			xlab = 'Longitud'
			ylab = 'Latitud'
		else:
			xlab = 'Numero de Crimenes'
			ylab = 'Areas de Fuerza Policiaca'

		x=0
		for algorithm in algoritms:

			print('  ', alg_name[x],' - Mejor K:', algorithm[2], ' Silueta:', algorithm[0])
			plt.scatter(data[:, 0], data[:, 1], c=algorithm[1], s=60, cmap='viridis')
			plt.title(title_plots[d] + ': ' + alg_name[x])
			plt.xlabel(xlab)
			plt.ylabel(ylab)
			plt.show()
			x += 1

	if d == 2:
		x=0
		for algorithm in algoritms:			
			print('  ', alg_name[x],' - Mejor K:', algorithm[2], ' Silueta:', algorithm[0])
			fig = plt.figure()
			ax = Axes3D(fig)
			ax.scatter(data[:, 0], data[:, 1], data[:, 2], c=algorithm[1], s=60)
			ax.w_xaxis.set_ticklabels([])
			ax.w_yaxis.set_ticklabels([])
			ax.w_zaxis.set_ticklabels([])
			ax.set_xlabel('Longitud')
			ax.set_ylabel('Latitud')
			ax.set_zlabel('Area')
			ax.set_title(title_plots[d] + ': ' + alg_name[x])
			plt.show()
			x += 1
	d+=1