from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
from math import *
import sys

PI = 3.14159 #180 grados

retardo = 20
retardo2 = 3000

DIMENSION = 500 #dimensiones de la ventana
centro = DIMENSION/2 #coordenadas del centro
division = 10 #cantidad en que se divide la ventana para filas y columnas
separacion = DIMENSION/division #separacion entre cada punto

coordenadas_puntos = []	#matriz que guarda los datos de cada punto

#se dibuja la escena principal
def drawScene():
	glClearColor(0,0,0,0)
	glClear(GL_COLOR_BUFFER_BIT)

	#se dibujan las lineas horizontales que unen a cada punto	
	for i in range(len(coordenadas_puntos)):
		glBegin(GL_LINE_STRIP)
		
		for j in range(len(coordenadas_puntos)):
			glColor3f(i*.11,0,1.0-i*.11)
			glVertex2f(coordenadas_puntos[i][j][0], coordenadas_puntos[i][j][1])
		glEnd()

	#se dibujan las lineas verticales que unen a cada punto
	for i in range(len(coordenadas_puntos)):
		glBegin(GL_LINE_STRIP)
		
		for j in range(len(coordenadas_puntos)):
			glColor3f(i*.11,0,1.0-i*.11)
			glVertex2f(coordenadas_puntos[j][i][0], coordenadas_puntos[j][i][1])
		glEnd()

	#se dibujan los puntos con las posiciones guardadas en el arreglo
	glPointSize(8)
	glBegin(GL_POINTS)
	for i in range(len(coordenadas_puntos)):
		for j in range(len(coordenadas_puntos)):
			glColor3f(i*.11,0,1.0-i*.11)
			glVertex2f(coordenadas_puntos[i][j][0], coordenadas_puntos[i][j][1])

	glEnd()

	glFlush()

#funcion que calcula la distancia entre dos puntoss dadas sus coordenadas
def distancia_puntos(x1,y1,x2,y2):
	return sqrt(pow(x2-x1,2) + pow(y2-y1,2))


pausa = False

def funcion_tiempo(value):
	global coordenadas_puntos, centro, pausa

	#condicion que indica que la escena aun no se pausa
	#la escena se pausara por cada 90 grados de rotacion de cada punto
	if pausa == False:
		for i in range(len(coordenadas_puntos)):
			for j in range(len(coordenadas_puntos)):
				#se acutalizan las coordenadas de los puntos de la matriz con respecto al nuevo angulo
				coordenadas_puntos[i][j][0] = coordenadas_puntos[i][j][2] * cos(radians(coordenadas_puntos[i][j][3])) + centro
				coordenadas_puntos[i][j][1] = coordenadas_puntos[i][j][2] * sin(radians(coordenadas_puntos[i][j][3])) + centro
				if coordenadas_puntos[i][j][3] < coordenadas_puntos[i][j][4] + 90:
					#se incrementa el valor del angulo de posicion
					coordenadas_puntos[i][j][3] += coordenadas_puntos[i][j][5]
					coordenadas_puntos[i][j][6] += .11

				if coordenadas_puntos[i][j][3] > 360: 
					coordenadas_puntos[i][j][3] = 0
					coordenadas_puntos[i][j][6] = 0.0

	if coordenadas_puntos[0][5][3] == coordenadas_puntos[0][5][4]+90:
		pausa = True
		for i in range(len(coordenadas_puntos)):
			for j in range(len(coordenadas_puntos)):
				coordenadas_puntos[i][j][3] = coordenadas_puntos[i][j][4]

	glutPostRedisplay()

	glutTimerFunc(retardo ,funcion_tiempo, 1)

def funcion_tiempo2(value):
	global pausa

	#funcion que pausa la escena cada 4 segundos
	pausa = False

	glutPostRedisplay()
	glutTimerFunc(retardo2 ,funcion_tiempo2, 1)


def resize(w, h):
	global height, width
	glViewport (0, 0, w, h)
	glMatrixMode(GL_PROJECTION)
	glLoadIdentity()

	glOrtho(0.0, w, 0.0, h, -1.0, 1.0)

	glMatrixMode(GL_MODELVIEW)
	glLoadIdentity()



def main():
	global coordenadas_puntos

	indiceI = division/2
	indiceJ = division/2

	size = division+1
	n = 0

	num = [1, 1.2, 1.5, 1.8, 2.1]
	color = 0.0

	#se inicializan las coordenadas de los puntos
	for i in range(size):
		coordenadas_puntos.append([])
		for j in range(size):
			x = separacion*i
			y = separacion*j
			#se calcula la distancia entre el punto y el centro (radio)
			radio = distancia_puntos(x, y, centro, centro);
			#se calcula el angulo del punto con respecto al centro
			angulo = atan2(y-centro, x-centro) * 180 / PI

			if i == indiceI and j == indiceJ:
				disminuye = 6

			for n in range(int(division/2)):
				if i == n or i == division-n or j == n or j == division-n:
					disminuye = num[n]
					break
			
			#se guardan los valores de cada punto en el arreglo
			coordenadas_puntos[i].append([x, y, radio, int(angulo), int(angulo), disminuye, color])


	glutInit(sys.argv)
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
	glutInitWindowSize(DIMENSION, DIMENSION)
	glutInitWindowPosition(100, 100) 
	glutCreateWindow("practica 2")
	glutDisplayFunc(drawScene)
	glutReshapeFunc(resize)
	glutTimerFunc(retardo,funcion_tiempo, 1)
	glutTimerFunc(retardo2,funcion_tiempo2, 1)
	glutMainLoop()

main()