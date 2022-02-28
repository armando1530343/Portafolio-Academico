import numpy as np
from sklearn import datasets
import matplotlib.pyplot as plt
    
#Funcion Sigmoidea
def Sigmo(x):
    return 1/(1+np.exp(-x))

#Derivada de la Sigmoidea
def DerSigmo(x):
    return x*(1-x)

#Funcion que Resuelve la RedNeuronal usanso BackPropagation 
def RedNeuronal(NeuOC,NeuS,Eta,Epocas,DataSet,Etiqueta):
    
    PesosO=2 * np.random.random((NeuOC,Atri)) -1    #Se proponen unos pesos aleatoreso para la capa oculta
    PesosS=2 * np.random.random((NeuS,NeuOC)) -1   #Se proponen unos pesos aleatoreso para la capa de salida
    BiasO=2 * np.random.random(NeuOC) -1                     #Aqui se inicializan los Bias de las Neuronas Ocultas
    BiasS=2 * np.random.random(NeuS) -1                   #Aqui se inicializan los Bias de las Neuronas de Salida
    
    #print('PESOS:',PesosO)   
    
    Errores=[]
    for epoc in range(Epocas):
        
        ErrorE=0
        idx = np.random.permutation(len(DataSet))

        for w in range(0,len(DataSet)):
            inst = idx[w]
            
            #Aqui se resuelve la RedNeuronal 
            SalidaO = Sigmo( np.dot(PesosO,np.transpose(DataSet[inst])) + BiasO )
            SalidaS = Sigmo( np.dot(PesosS,np.transpose(SalidaO)) + BiasS )
            #print('SIGMA',PesosO)

            #print('SalidaO\n', PesosO)
            #print('Salida', np.dot(PesosS,np.transpose(SalidaO)) + BiasS )
            
            #Se calcula el error para todas las Salidas
            ErrorS=np.zeros(NeuS)   #Errores de las neuronas de salida
            
            for i in range(NeuS):   #Para todas las capas de salida
                ErrorS[i] = ( Etiqueta[inst][i] - SalidaS[i] ) * DerSigmo(SalidaS[i])
            
            #Se calcula el error para todas las neuronas aocultas
            ErrorO=np.zeros(NeuOC)  #Error de las neuronas de la capa oculta
            
            for i in range(NeuS):
                for j in range(NeuOC):
                    ErrorO[j] += ErrorS[i] * DerSigmo(SalidaO[j]) * PesosS[i][j]

            #print('Pesos: ', PesosS)
            
            
            #Se actualizan los pesos de la capa de Salida
            for i in range(NeuS):
                for j in range(NeuOC):
                    PesosS[i][j] = PesosS[i][j] + Eta * ErrorS[i] * SalidaO[j]
                #Se actualiza el Bias   
                BiasS[i] = BiasS[i] + Eta * ErrorS[i]
            
            #Se actualizan los pesos de la CapaOculta
            for i in range(NeuOC):
                for j in range(Atri):
                    PesosO[i][j] = PesosO[i][j] + Eta * ErrorO[i] * DataSet[inst][j]
                BiasO[i] = BiasO[i] + Eta * ErrorO[i]
            
            
            #Se calcula el error CuadraticoMedio
            for i in range(NeuS):
                Error = np.power(SalidaS[i] - Etiqueta[inst][i],2)
            ErrorE += Error / NeuS
        
        Errores.append(ErrorE) 
        
    return PesosO,PesosS,BiasO,BiasS,Errores

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
    Data_Train =  data[idx[:int(P*.75)]]
    Target_Train = target[idx[:int(P*.75)]]
    
    Data_Test =data[idx[int(P*.75):]]
    Target_Test = target[idx[int(P*.75):]]
    
    return Data_Train,Target_Train,Data_Test,Target_Test  

#Aqui se tiene una funiconq ue reconstruye el etiquetado en un arreglo
def Reconstruir(Target,NumClas):
    Etiqueta=[]
    for i in range(len(Target)):
        EtiqInst=[]
        for j in range(NumClas):
            if(Target[i]==j):
                EtiqInst.append(0)
            else:
                EtiqInst.append(1)
        Etiqueta.append(EtiqInst)
    
    return Etiqueta


#Esta funcion predice una clasificacion para los datos y califica la prediccion
def PrediccionZ(Data,Etiqueta,PesosO,PesosS,BiasO,BiasS): 
    #Contadores
    VP=0
    VN=0
    FP=0
    FN=0   
    pred=[] 
    print('PESOS:',PesosO)
    for i in range(len(Data_Test)):
        SalidaO = Sigmo( np.dot(PesosO,np.transpose(Data[i])) + BiasO )
        SalidaS = Sigmo( np.dot(PesosS,np.transpose(SalidaO)) + BiasS )  
        #print('salida:',SalidaS)
        
        Aux=[]
        for j in range(len(SalidaS)):
            if(SalidaS[j]>0.5): Aux.append(1)
            else: Aux.append(0) 
        
        
        for j in range(len(SalidaS)):
            if(Etiqueta[i][j]==1): 
                if(Aux[j] == 1): VP+=1
                else: VN+=1
            else:
                if(Aux[j] == 0): FP+=1
                else: FN+=1

        pred.append(Aux)

    print('predict: ', pred)
                
            
    return 100*(VP+FP)/(VP+VN+FP+FN)

################################################################################################################
    #Aqui empiezan las Delcaraciones
################################################################################################################
    
#Definir el problema con el que se Trabajara
    #     1     DataSet de 100 con 2 Clases
    #     2     DataSet de 150 con 3 Clases

Problema=1

if(Problema==2):
    NeuS=3                            #Numero de Neuronas en la capa de Salida
if(Problema==1):
    NeuS=1                            #Numero de Neuronas en la capa de Salida


#Adquisicion y division de la informacion del DataSet
DataSet,Target_Train,Data_Test,Target_Test=Adquisicion(2)    


NeuOC=2                           #Numero de neuronas en la capa Oculata
Atri=len(DataSet[0])              #Numero de Atributos del dataset, Numero de NEURONAS CAPA ENTRADA
Eta=0.7                           #Factor de Aprendizaje
Epocas=100                       #Esta son las epocas en las que se ajustaran los pesos

#Empieza el entrenamiento de la red para obtener los pesos y las Bias
Etiqueta=Reconstruir(Target_Train,NeuS)
PesosO,PesosS,BiasO,BiasS,Errores = RedNeuronal(NeuOC,NeuS,Eta,Epocas,DataSet,Etiqueta)

"""
#Grafico El Error cuadratico Medio
print("\nEl error cuadratico medio se comporto de la siguiente manera en el entrenamiento")
plt.scatter(range(0,Epocas),Errores)
plt.xlabel("Epocas")
plt.ylabel("Error Cuadratico Medio")
plt.show()
"""

print('esperado:', Target_Test)

#Cuento la acertividad de la clasificacion
Etiqueta=Reconstruir(Target_Test,NeuS)
Acierto = PrediccionZ(Data_Test,Etiqueta,PesosO,PesosS,BiasO,BiasS)
print("\nLa acertividad de classificacion del set de Testing es el siguiente")
print(Acierto) 
"""

#Aqui realizo la Experimentacion
Exp=[]
for i in range(30):
    Etiqueta=Reconstruir(Target_Train,NeuS)
    PesosO,PesosS,BiasO,BiasS,Errores = RedNeuronal(NeuOC,NeuS,Eta,Epocas,DataSet,Etiqueta)
    Etiqueta=Reconstruir(Target_Test,NeuS)
    Exp.append( PrediccionZ(Data_Test,Etiqueta,PesosO,PesosS,BiasO,BiasS))
    
print("\nEl promedio de Acertividad de las 30 Iteraciones es")
print(np.mean(Exp))
print("\nLa desviacion Estandar de la Experimentacion")
print(np.std(Exp))
"""   

'''
#Comprobacion de los primeras 10 clasificaciones 
print("\nLa prediccion para los 10 primeros elementos elementos es")
print("Etiqueta   Prediccion")
Etiqueta=Reconstruir(Target_Test,NeuS)
for inst in range(10):
    SalidaO = Sigmo( np.dot(PesosO,np.transpose(Data_Test[inst])) + BiasO )
    SalidaS = Sigmo( np.dot(PesosS,np.transpose(SalidaO)) + BiasS )
    print(str(Etiqueta[inst][0]) + " " + str(SalidaS[0]))
    if(Problema==2): print(str(Etiqueta[inst][1]) + " " + str(SalidaS[1]))   
    if(Problema==2): print(str(Etiqueta[inst][2]) + " " + str(SalidaS[2]))
    print("\n")
'''    
    

