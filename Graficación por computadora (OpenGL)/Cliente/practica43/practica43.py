from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
import sys

width = 0 #valor inicial en x del mouse
height = 0 #valor inicial en y del mouse

nodos = [] #guarda la cantidad de nodos leidos desde el archivo

pointSize = 50 #tamano del nodo dibujado

#coordenadas en las que se grafican los nodos
coordenadas = [[250,450],[350,450],[450,450],
			   [250,350],[350,350],[450,350],
			   [250,250],[350,250],[450,250]]

conexion1 = [] #guarda las posiciones del nodo origen
conexion2 = [] #guarda las posiciones del nodo destino


archivo = open('nodos.txt', 'r') #abre el archivo en forma de lectura

#ciclo que see cada linea del archivo y guarda los los nodos que encuentra
for linea in archivo.readlines(): 
	nod = ''
	if linea[0] == '{': break 
	for i in linea:
		if i != '\n' and i != '&':
			nod = nod + i
		else:
			nodos.append(nod)
			nod = ''

archivo.close() # se cierra el archivo

archivo = open('nodos.txt', 'r') #

#ciclo que see cada linea del archivo y guarda las conexiones de cada nodo
for linea in archivo.readlines(): 
	if linea[0] == '{':
		if int(linea[1]) == 1:
			conexion1.append(int(linea[3])-1)

		elif int(linea[1]) == 2:
			conexion1.append(2+int(linea[3]))
		else:
			conexion1.append(5+int(linea[3]))


		if int(linea[6]) == 1:
			conexion2.append(int(linea[8])-1)
			
		elif int(linea[6]) == 2:
			conexion2.append(2+int(linea[8]))
		else:
			conexion2.append(5+int(linea[8]))
		

archivo.close() 

print conexion1
print conexion2

#print nodos

#funcion que imprime los numeros en la ruleta
def writeBitmapString(font, string):
   for c in string:
       glutBitmapCharacter(font, ord(c))


# funcion que dibuja las flechas de las conexiones
def conexiones():
	global coordenadas
	
	i = 0
	while i < len(conexion1):
		glBegin(GL_LINES) #se dibujan las lineas 
		glColor3f(0,0,0)
		glVertex2f(coordenadas[conexion1[i]][0], coordenadas[conexion1[i]][1])
		glVertex2f(coordenadas[conexion2[i]][0], coordenadas[conexion2[i]][1])
		glEnd()
		glPointSize(5)
		glBegin(GL_POINTS)
		glVertex2f(coordenadas[conexion2[i]][0], coordenadas[conexion2[i]][1])
		glEnd()
		i = i + 1


# dibujan los nodos en la pantalla
def dibuja_nodos():
	glClearColor(1,1,1,0)
	glClear(GL_COLOR_BUFFER_BIT)

	glPointSize(pointSize)

	for i in range(0,9):
		glBegin(GL_POINTS)
		glColor3f(1,0,0)
		glVertex2f(coordenadas[i][0], coordenadas[i][1])
		glEnd()

		glColor3f(1,1,1)
		glRasterPos2f(coordenadas[i][0]-10, coordenadas[i][1])
		writeBitmapString(GLUT_BITMAP_8_BY_13, nodos[i])

	print coordenadas
	conexiones()


	glFlush()


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
	glutInitWindowSize(700, 700)
	glutInitWindowPosition(100, 10)
	glutCreateWindow("Practica 01")
	glutDisplayFunc(dibuja_nodos)
	glutReshapeFunc(resize)
	glutMainLoop()

main()