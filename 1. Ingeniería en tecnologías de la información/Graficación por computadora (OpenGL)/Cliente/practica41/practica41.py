from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
import sys


boton = 0 #indica la opcion que tecleo
longHash = 0  #longitud del hash ingresado
insertar = -1 #valor que se ingresa al hash
buscar = -1 #valor que se busca
eliminar = -1 #valor que se eliminara del hash
posicionX = 0 #posicion inicial
dist = 52 #distancia entre filas de cada valor
hashTable = [range(15) for i in range(15)] #matriz del hash table (15x15 como dimension maxima)

#en cada posicion del hash se guardara un arreglo que representan las caracteristicas de cada nodo graficado
for i in range(15):
	for j in range(15):
		hashTable[i][j] = [-1,0,0,0,1,0,0] #se asigna el arreglo
		if i > 0:
			hashTable[i][j] = [-1,0,0,0,0,0,0] # se asigna el arreglo

width = 0; height = 0 #dimensiones de la ventana

def writeBitmapString(font, string):
	for c in string:
		glutBitmapCharacter(font, ord(c))

#funcion que muestra el comportamiento del hashTable segun la accion de cada tecla presionada
def escenario():

	global boton, longHash, insertar, buscar, eliminar, posicionX, dist, hashTable, Nodo


	if boton == 1: #se presiono la tecla n
		longHash = 0

		#se crea un nuevo hash  con dimensiones iguales o menores a 15x15
		for i in range(15):
			for j in range(15):
				hashTable[i][j] = [-1,0,0,0,1,0,0] #se inicializan los valores de cada nodo
				if i > 0:
					hashTable[i][j] = [-1,0,0,0,0,0,0]


		while longHash < 1 or longHash > 15:
			longHash = input('Crear un HasTable (ingresa longitud de Hash):') #se pide la longitud del hash
		boton = 0
		glutPostRedisplay()

	elif boton == 2 and longHash > 0: #se presiono la tecla b
		buscar = -1
		while buscar < 0 or buscar > 99:
			buscar = input('Buscar Valor:') # se ingresa el valor que se desea buscar

		columnaHash = buscar % longHash #se obtiene la posicion de la columna que sera buscado
		encontrado = False

		for i in range(15):
			for j in range(longHash):
				if i == 0: #accede a las cabeceras del hash
					hashTable[i][j][4] = 1 #se le cambia el color para las cabeceras

				hashTable[i][j][3] = 0 #se cambia el color para los nodos numericos

		#se recorre la columna obtenida para buscar el valor
		for i in range(15):
			if hashTable[i][columnaHash][0] == buscar:
				hashTable[i][columnaHash][3] = 1 #cambia de color para identificar el valor encontrado
				encontrado = True
				break #sale del ciclo

		#sino encuentra el valor se colorea el nodo cabeza
		if encontrado == False:
			hashTable[0][columnaHash][3] = 1
			hashTable[0][columnaHash][4] = 0

		boton = 0

		glutPostRedisplay()


	elif boton == 3 and longHash > 0: #se presiono la tecla i
		insertar = -1
		for i in range(15):
			for j in range(longHash):
				if i == 0:
					hashTable[i][j][4] = 1

				hashTable[i][j][3] = 0 

		while insertar < 0 or insertar > 99:
			insertar = input('Insertar valor:') # se pide el valor a ingresar

		columnaHash = insertar % longHash # se obtiene en que columna sera insertado

		for i in range(1,15):
			if hashTable[i][columnaHash][0] == insertar: break #si el valor ya existe se cancela la insercion
			
			if hashTable[i][columnaHash][6] == 0: # el cero indica que el nodo esta desocupado y puede utilizarse 
				hashTable[i][columnaHash][0] = insertar # se asigna el valor
				hashTable[i][columnaHash][1] = hashTable[0][columnaHash][1] #se asigna la posicion en x
				hashTable[i][columnaHash][2] = hashTable[i-1][columnaHash][2]-dist # se asigna la posicion en y
				hashTable[i][columnaHash][6] = 1 # indica que el valor ya esta ocupado

				break
		boton = 0
		glutPostRedisplay()

	elif boton == 4 and longHash > 0:
		eliminar = -1
		while eliminar < 0 or eliminar > 99:
			eliminar = input('Eliminar Valor:') # se pide el valor que eliminara del hash

		columnaHash = eliminar % longHash # se obtiene la columna en donde pertenece ese numero
		encontrado = False

		for i in range(15):
			for j in range(longHash):
				if i == 0:
					hashTable[i][j][4] = 1

				hashTable[i][j][3] = 0 

		#se recorre la columna para verificar la existencia del valor ingresado
		for i in range(15):
			if hashTable[i][columnaHash][0] == eliminar: # se encuentra el valor				
				j = i
				#se hace un recorrido de los valores de los nodos siguientes y se sustituyen los valores
				#con el objetivo de desaparecer el nodo con el valor que se debe eliminar
				while j < 14 :
					if hashTable[j+1][columnaHash][6] == 0:
						hashTable[j][columnaHash][0] = -1
						hashTable[j][columnaHash][6] = 0
						break

					hashTable[j][columnaHash][0] = hashTable[j+1][columnaHash][0] 
					j = j + 1

				encontrado = True
				break


		if encontrado == False:
			hashTable[0][columnaHash][3] = 1
			hashTable[0][columnaHash][4] = 0

		boton = 0

		glutPostRedisplay()





	




def drawScene():

	global longHash, width, hashTable, posicionX

	glClearColor(1,1,1,0)
	glClear(GL_COLOR_BUFFER_BIT)	

	posicionX = width / (longHash+1) # se obtiene la posicion central
	auxiliarX = posicionX

	#se grafican los nodos principales
	for i in range(0,longHash):
		glPointSize(50)
		glBegin(GL_POINTS)

		glColor3f(hashTable[0][i][3], hashTable[0][i][4], hashTable[0][i][5])
		glVertex2f(auxiliarX, 500)
		glEnd()

		#se guardan las posiciones de cada nodo en la matriz del hashTable
		hashTable[0][i][1] = auxiliarX
		hashTable[0][i][2] = 500
		hashTable[0][i][6] = 1 # indica que esta ocupado


		glColor3f(1,1,1)
		glRasterPos2f(auxiliarX-5, 495) 	
   		writeBitmapString(GLUT_BITMAP_HELVETICA_18, 'H')

   		auxiliarX = auxiliarX + posicionX

   	escenario() # se llama a la funcion de acciones de las teclas

   	#se muestran las instrucciones
   	ins1 = 'Teclas de accion (para que el tecleo haga efecto, debe permanecer en esta ventana):'
	ins2 = '(tecla n: crear un nuevo hash table)\
			(tecla b: buscar un valor)\
			(tecla i: insertar un valor)\
			(tecla e: eliminar un valor)'
	ins3 = 'Al teclear una de estas, dirigirse a la terminal para ingresar los valores'

	#se escriben las instrucciones en la ventana
	glColor3f(0,0,0)
	glRasterPos2f(10, 630) 	
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, ins1)
	glRasterPos2f(10, 610) 	
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, ins2)
	glRasterPos2f(10, 590) 	
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, ins3)

	#se recorre la matriz del hash table actualizada para grafical todos los nodos con los valores numericos
   	for i in range(1,15):
   		for j in range(longHash):
   			if hashTable[i][j][6] == 1:
	   			glPointSize(50)
				glBegin(GL_POINTS)
				glColor3f(hashTable[i][j][3], hashTable[i][j][4], hashTable[i][j][5])
				glVertex2f(hashTable[i][j][1], hashTable[i][j][2])
				glEnd()

				glColor3f(1,1,1)
				glRasterPos2f(hashTable[i][j][1]-5, hashTable[i][j][2]-5) 	
		   		writeBitmapString(GLUT_BITMAP_HELVETICA_18, str(hashTable[i][j][0]))  	

   	glFlush()


#acciones del teclado
def keyInput(key, x, y):
	global boton
	if key == 'n': # acciones de la tecla n
		boton = 1 
	if key == 'b': # acciones de la tecla b
		boton = 2
	if key == 'i': # acciones de la tecla i
		boton = 3
	if key == 'e': # acciones de la tecla e
		boton = 4

	glutPostRedisplay()
	return 

def resize(w, h):
	global height, width
	glViewport (0, 0, w, h)
	glMatrixMode(GL_PROJECTION)
	glLoadIdentity()

	glOrtho(0.0, w, 0.0, h, -1.0, 1.0)

	width = w
	height = h 

	glMatrixMode(GL_MODELVIEW)
	glLoadIdentity()  

def main():

	glutInit(sys.argv)
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
	glutInitWindowSize(1000, 650)
	glutInitWindowPosition(10, 10)
	glutCreateWindow("Practica 03")
	glutDisplayFunc(drawScene)
	glutReshapeFunc(resize)
	glutKeyboardFunc(keyInput)
	glutMainLoop()

main()