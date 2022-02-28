import pandas as pd
import numpy as np
import math
from sklearn import datasets
from sklearn.cluster import KMeans


#Esta funcion realiza la adquisisicon del IRIS para 2 y 3 clases
def Adquisicion(NumClas):
    
    if (NumClas==2): large = 100    #Con 2 etiquetas, se toman los primeros 100 elementos del dataset
    if (NumClas==3): large = 150    #Con 3 etiquetas, se toman los 150 datos del dataset
    
    
    iris = datasets.load_iris()
    data = iris.data[:large]       #Se cargan los datos referentes al IRIS
    target = iris.target[:large]   #Se cargan las clases de los primeros 100 elementos
    
    #Se normalizan los datos del DataSet
    data = (data - data.min(axis=0))/(data.max(axis=0)-data.min(axis=0))
    
    #Se genera una permutacion aleatoria
    P =len(data)  
    idx = np.random.permutation(P)
    
    #Se separa el dataset para hacer el entrenamiento y la evaluacion
    Data_Train =  pd.DataFrame(data[idx[:int(P*.75)]])
    Target_Train = target[idx[:int(P*.75)]]

    print(Target_Train)

    #Target_Train = pd.DataFrame(target[idx[:int(P*.75)]])
    
    Data_Test = pd.DataFrame(data[idx[int(P*.75):]])
    Target_Test = target[idx[int(P*.75):]]
    #Target_Test = pd.DataFrame(target[idx[int(P*.75):]])
    
    return Data_Train,Target_Train,Data_Test,Target_Test   

#Aqui se desarolla la funcion de base radia GAUSIANA
def BaseRadGAUS(x):
    return math.exp(-x*x*0.5)
   
#Aqui se tine una funcion que calcula la distnacia entre centros 
def DisCentro(Centros):
    #Se idetifica la distancia al centro mas cercano y se divide entre 2
    DisMin=[]
    for i in range(len(Centros)):
        mini=-1
        for j in range(len(Centros)):
            if(i!=j):
                aux=np.power(np.sum(np.power(Centros[i]-Centros[j],2)),0.5)
                if(mini==-1 or mini>aux):
                    mini=aux
        DisMin.append(mini/2)
        
    return DisMin

#Aqui se desarrolla la funcion que resuleve la capa Opculata
def NOSupervisado(Instancias,Centros,D):
    #Aqui se calcula las salidas de la capa oculata, con la funcion de base radia entre las instancias y los centros
    TotSalO=[]
    for j in range(len(Instancias)):
        SalidaO=[]
        for i in range(len(Centros)):
            aux=((np.power(np.sum(np.power(Instancias.iloc[j]-Centros[i],2)),0.5))/D[i])
            SalidaO.append(BaseRadGAUS(aux))
        #SalidaO.append(-1)   #Se le agrega el Bias 
        TotSalO.append(SalidaO)
    
    return pd.DataFrame(TotSalO)

#Aqui se tiene un umbral de activacion de valores
def Umbral(VecB,PesosB):
    Res = PesosB[0]
    Res += np.dot(PesosB[1:], VecB)
    
    if (Res>=0): return 1
    else: return 0

#Aqui realizo el entrenamiento del perpectron
def Supervisado(XEntrA,YEntrA,EpocasA,nA):

    #Inicializzo un vector de pesos aleatorio
    Pesos=np.random.rand(len(XEntrA.iloc[0])+1)

    #Para todas las pocas
    for epoc in range(EpocasA):
        #Para todos los valores de entrenamiento
        for i in range(len(XEntrA)):
            Vec=XEntrA.iloc[i]
            Predecido=Umbral(Vec,Pesos)

            #Se revisa si se predijo correctamente
            if(YEntrA[i]!=Predecido):
                
                #Se calcula el valor del error
                error=YEntrA[i]-Predecido
                Pesos[0]=Pesos[0]+nA*error
                #Se corrije el error para cada elemento
                for j in range(len(Vec)):
                    Pesos[j+1]=Pesos[j+1]+nA*error*Vec[j]
                    
    #Se regresan los pesos balanceados
    return Pesos

#Esta funcion predice una clasificacion para los datos y califica la prediccion
def Prediccion(Data_Test,Centros,YEvaB,PesosB): 
    D=DisCentro(Centros)                                  #Aqui se calcula el valor de la distancia o la Sigma
    XEvaB=NOSupervisado(Data_Test,Centros,D)     
    #Contadores
    VP=0
    VN=0
    FP=0
    FN=0
    for i in range(len(XEvaB)):
        if(YEvaB[i]==1):
            if(Umbral(XEvaB.iloc[i],PesosB)==1): VP+=1
            else: VN+=1
        else:
            if(Umbral(XEvaB.iloc[i],PesosB)==0): FP+=1
            else:FN+=1 
            
    return 100*(VP+FP)/(VP+VN+FP+FN)
    
#Esta funcion tiene la RFBNN para 2 clases regresando los pesos 
def RBFNN(NumCO,NumClas,Data_Train,Target_Train,Epocas):
    
    #Se realiza primero la ejecucion de la Parte NO SUPERVISADA    
    KMEANS= KMeans(n_clusters=NumCO, random_state=0).fit(Data_Train)      #Aqui se utiliza kmeans para encontrar los centros que se utilizaran
    D=DisCentro(KMEANS.cluster_centers_)                                  #Aqui se calcula el valor de la distancia o la Sigma
    
    
    SalidaCapaO=NOSupervisado(Data_Train,KMEANS.cluster_centers_,D)       #Se realiza la parte NO SUPERVISADA 
    Pesos=Supervisado(SalidaCapaO,Target_Train,Epocas,0.1)              #Aqui se obtiene la salida de la parte Supervisada

    print('salida: \n', SalidaCapaO)
    print('pesos:\n', Pesos)
    #Los pesos entrenados se regresan
    return KMEANS.cluster_centers_,Pesos


################################################################################################
    #Aqui empizan las declaraciones
 ############################################################################################33   

#Adquisicion y division de la informacion del DataSet
Data_Train,Target_Train,Data_Test,Target_Test=Adquisicion(2)    

NumClas=2         #Numero de Clases en las que separare el DATASET
NumCO=6           #Numero de Capas Ocultas con la que se trabajara   


#Se experimenta para 30 casos
for NumCO in range(2,10):
    resultados=[]
    for i in range(1):
        Centros,Pesos=RBFNN(NumCO,NumClas,Data_Train,Target_Train,1)   
        print('pesos:',Pesos[1:])           
        resultados.append(Prediccion(Data_Test,Centros,Target_Test,Pesos))
    print(np.mean(resultados))
    print(np.std(resultados))
