from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
from math import *
import sys

retardo = 100 	

width = 0
height = 0


radio = 40.0 # Radio de los circulos
RADIO = 210.0 # Radio de rotacion de los circulos

X_CENTRO = 250 # posicion X del centro de la ventana
Y_CENTRO = 250 # posicion Y del centro de la ventana

origenX = 0 # coordenada X del origen del circulo en rotacion
origenY = 0 # coordenada X del origen del circulo en rotacion

ANGULO = 0 # angulo de rotacion de los circuloss

CIRCULOS = []

def writeBitmapString(font, string):
##esta funcion imprime texto en pantalla
   for c in string:
       glutBitmapCharacter(font, ord(c))

def drawScene():
	global origenX, origenY, CIRCULOS

	glClearColor(0,0,0,0)
	glClear(GL_COLOR_BUFFER_BIT)

	origenX = RADIO * cos(radians(ANGULO)) + X_CENTRO
	origenY = RADIO * sin(radians(ANGULO)) + Y_CENTRO

	#CIRCULOS
	glColor3f(1,1,1)
	glBegin(GL_LINE_STRIP)
	for ang in range(361):
		x = radio * cos(radians(ang)) + origenX
		y = radio * sin(radians(ang)) + origenY
		glVertex2f(x, y)
	glEnd()

	CIRCULOS.append([origenX, origenY, radio])

	for cir in CIRCULOS:
		glColor3f(1,1,1)
		glBegin(GL_LINE_STRIP)
		for ang in range(361):
			x = cir[2] * cos(radians(ang)) + cir[0]
			y = cir[2] * sin(radians(ang)) + cir[1]
			glVertex2f(x, y)

		glEnd()
	glFlush()

def timerFunc(value):
	global ANGULO, CIRCULOS


	#se alteran los radios de los circulos dibujados
	for cir in CIRCULOS:
		if cir[2] > 0:
			#se decrementa el valor de los radios del circulo recorrido
			cir[2]-=1.4
		else:
			#cuando el radio del circulo = 0, se remueve de la lista de circulos
			CIRCULOS.remove(cir)


	ANGULO += 11 #se incrementa el valor del angulo de rotacion

	glutPostRedisplay()
	glutTimerFunc(retardo ,timerFunc, 1)

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
	glutInitWindowSize(500, 500)
	glutInitWindowPosition(100, 100) 
	glutCreateWindow("Practica 2")
	glutDisplayFunc(drawScene)
	glutReshapeFunc(resize)
	glutTimerFunc(retardo,timerFunc, 1)
	glutMainLoop()
main()