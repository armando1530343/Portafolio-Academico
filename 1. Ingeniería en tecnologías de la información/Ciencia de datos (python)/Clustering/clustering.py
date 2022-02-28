from sklearn.cluster import KMeans, AgglomerativeClustering
from scipy.cluster.hierarchy import dendrogram, linkage, fcluster
from sklearn.metrics.cluster import adjusted_rand_score
from sklearn.preprocessing import StandardScaler
from sklearn.datasets.samples_generator import make_blobs
import matplotlib.pyplot as plt
import numpy as np

datasets_names = [
'Aggregation',  #indice 0
'Compound',     #indice 1
'D31',          #indice 2
'Flame',        #indice 3
'Glass',        #indice 4
'Iris',         #indice 5
'Jain',         #indice 6
'Long3',        #indice 7
'Pathbased',    #indice 8
'R15',          #indice 9
'S4',           #indice 10
'Smile',        #indice 11
'Spiral2',      #indice 12
'Spiral3',      #indice 13
'Tevc1',        #indice 14
'Tevc2',        #indice 15
'Triangle',     #indice 16
'UKC1',         #indice 17
'UKC2',         #indice 18
'UKC3',         #indice 19
'UKC4',         #indice 20
'UKC5',         #indice 21
'UKC6',         #indice 22
'UKC7',         #indice 23
'UKC8'          #indice 24
]

#para imprimir los resultados de un dataset se debe cambiar el valor del INDICE para acceder a cada nombre del dataset
INDICE = 0 # se accede al indice del nombre del dataset

#funcion que lee un archivo de texto y crea una lista con sus respectivos datos ya sean cadenas o numeros
def leer_archivo(archivo):
	datos = []
	file = open('Clustering_Datasets/' + archivo + '.txt', 'r')
	for line in file:
		columnas = []
		dato = ''
		for c in line:
			if c != '\t' and c != '\n':
				dato += c
			elif c == '\n':
				columnas.append(float(dato))
				break
			else:
				columnas.append(float(dato))
				dato = ''
		datos.append(columnas)
	return datos

dataset = leer_archivo(datasets_names[INDICE])
#print(np.array(dataset))
N = len(dataset)
D = len(np.array(dataset[0])) - 1
labels_true = np.array(dataset)[:,D]
K = len(list(set(np.array(dataset)[:,D])))

for dat in dataset:dat.pop()

print('Dataset:', datasets_names[INDICE])
print('Tamaño:', N)
print('Dimension:', D)
print('Clusters:', K, '\n')

dataset = StandardScaler().fit_transform(dataset)

kmeans = KMeans(n_clusters=K).fit(dataset)
kmeans_predict = kmeans.predict(dataset)
centroides = kmeans.cluster_centers_

single = linkage(dataset, 'single')
single_predict = fcluster(single, K, criterion='maxclust')

average = AgglomerativeClustering(n_clusters=K, linkage='average').fit(dataset)
average_predict = average.fit_predict(dataset)

complete = AgglomerativeClustering(n_clusters=K, linkage='complete').fit(dataset)
complete_predict = complete.fit_predict(dataset)


kmeans_ari = round(adjusted_rand_score(labels_true,kmeans_predict),2)
single_ari = round(adjusted_rand_score(labels_true,single_predict),2)
average_ari = round(adjusted_rand_score(labels_true,average_predict),2)
complete_ari = round(adjusted_rand_score(labels_true,complete_predict),2)

print('KMeans ARI:', kmeans_ari)
print('Agglometative(Average) ARI:', average_ari)
print('Agglometative(Single) ARI:', single_ari)
print('Agglometative(Complete) ARI:', complete_ari)

if D == 2:
	plt.scatter(dataset[:, 0], dataset[:, 1], c=kmeans_predict, s=10, cmap='viridis')
	plt.title(datasets_names[INDICE] + ': Algoritmo de Kmeans')
	plt.show()

	plt.scatter(dataset[:, 0], dataset[:, 1], c=single_predict, s=10, cmap='viridis')
	plt.title(datasets_names[INDICE] + ': Clustering Jerarquico Aglomerativo (Single)')
	plt.show()

	plt.scatter(dataset[:, 0], dataset[:, 1], c=average_predict, s=10, cmap='viridis')
	plt.title(datasets_names[INDICE] + ': Clustering Jerarquico Aglomerativo (Average)')
	plt.show()

	plt.scatter(dataset[:, 0], dataset[:, 1], c=complete_predict, s=10, cmap='viridis')
	plt.title(datasets_names[INDICE] + ': Clustering Jerarquico Aglomerativo (Complete)')
	plt.show()