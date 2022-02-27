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

menu = False
pausa = False
vista_circulo = False

colores = [0,0,0,0]


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

	#vista de circulos repetidos
	if not vista_circulo:

		for cir in CIRCULOS:
			glColor3f(1,1,1)
			glBegin(GL_LINE_STRIP)
			for ang in range(361):
				x = cir[2] * cos(radians(ang)) + cir[0]
				y = cir[2] * sin(radians(ang)) + cir[1]
				glVertex2f(x, y)

			glEnd()

	#vista al menu de opciones
	if menu:		
		#pausa
		glColor3f(1,colores[0],0)
		glBegin(GL_QUADS)
		glVertex2f(210, 350)
		glVertex2f(290, 350)
		glVertex2f(290, 330)
		glVertex2f(210, 330)
		glEnd()
		glColor3f(0,0,0)
		if pausa:
			glRasterPos2f(215,335)
			writeBitmapString(GLUT_BITMAP_HELVETICA_12,"Reanudar")
		else:
			glRasterPos2f(215,335)
			writeBitmapString(GLUT_BITMAP_HELVETICA_12,"Pausa")

		#Opciones de vista
		glColor3f(1,colores[1],0)
		glBegin(GL_QUADS)
		glVertex2f(210, 320)
		glVertex2f(290, 320)
		glVertex2f(290, 300)
		glVertex2f(210, 300)
		glEnd()
		glColor3f(0,0,0)
		if not vista_circulo:
			glRasterPos2f(215,305)
			writeBitmapString(GLUT_BITMAP_HELVETICA_12,"Circulo")
		else:
			glRasterPos2f(215,305)
			writeBitmapString(GLUT_BITMAP_HELVETICA_12,"Repeticion")

		#aumentar velocidad
		glColor3f(1,colores[2],0)
		glBegin(GL_QUADS)
		glVertex2f(210, 290)
		glVertex2f(290, 290)
		glVertex2f(290, 270)
		glVertex2f(210, 270)
		glEnd()
		glColor3f(0,0,0)
		glRasterPos2f(215,275)
		writeBitmapString(GLUT_BITMAP_HELVETICA_12,"Vel. +")

		glColor3f(1,colores[3],0)
		glBegin(GL_QUADS)
		glVertex2f(210, 260)
		glVertex2f(290, 260)
		glVertex2f(290, 240)
		glVertex2f(210, 240)
		glEnd()
		glColor3f(0,0,0)
		glRasterPos2f(215,245)
		writeBitmapString(GLUT_BITMAP_HELVETICA_12,"Vel. -")
		

	glFlush()

def timerFunc(value):
	global ANGULO, CIRCULOS

	if not pausa:

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

def mouseControl(button, state, x, y):  

	global menu, pausa, vista_circulo, retardo, colores

	y = height - y
	
	if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:

		#posicion del boton pausa
		if x > 210 and x < 290 and y > 330 and y < 350:
			pausa = not pausa
			colores[0] = 1

		#posicion del boton vista
		if x > 210 and x < 290 and y > 300 and y < 320:
			vista_circulo = not vista_circulo
			colores[1] = 1

		#posicion del boton vel. +
		if x > 210 and x < 290 and y > 270 and y < 290:
			if retardo > 20:retardo -= 20
			colores[2] = 1

		#posicion del boton vel. -
		if x > 210 and x < 290 and y > 240 and y < 260:
			if retardo > 0:retardo += 20
			colores[3] = 1


	if button == GLUT_LEFT_BUTTON and state == GLUT_UP:
		colores = [0,0,0,0]

	#boton derecho menu
	if button == GLUT_RIGHT_BUTTON and state == GLUT_DOWN:
		menu = not menu

	glutPostRedisplay()

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

def keyInput(key, x, y):
	glutPostRedisplay()

def main():
	glutInit(sys.argv)
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
	glutInitWindowSize(500, 500)
	glutInitWindowPosition(100, 100) 
	glutCreateWindow("Practica 2")
	glutDisplayFunc(drawScene)
	glutReshapeFunc(resize)
	glutKeyboardFunc(keyInput)
	glutMouseFunc(mouseControl)
	glutTimerFunc(retardo,timerFunc, 1)
	glutMainLoop()
main()