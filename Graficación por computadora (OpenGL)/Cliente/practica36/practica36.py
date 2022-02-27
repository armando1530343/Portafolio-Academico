from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
from math import *
import sys

retardo = 1 #retardo timer
width = 0
height = 0
#coordenadas centro del circulo mayor
centro_x = 300
centro_y = 300
#angulo del radio mayor
angulo1 = 0
#angulo del radio menor
angulo2 = 0

#rotacion del triangulo de parabolas
ang1 = 0

#coordenadas de las posiciones del triangulo de parabolas
coords = []

#indica la pausa del gif
pause = False

#indica el reinicio del gif
reinicio = False

cerrar = False

vista1 = True
vista2 = False

menu = False

def writeBitmapString(font, string):
##esta funcion imprime texto en pantalla
   for c in string:
       glutBitmapCharacter(font, ord(c))

#dibuja un circulo de acuerdo a las coordenadas y radio
def circulo(radio, X, Y):
	glColor3f(1,1,1)
	glBegin(GL_LINE_STRIP)
	for ang in range(360):
		x = radio * cos(radians(ang)) + X
		y = radio * sin(radians(ang)) + Y
		glVertex2f(x, y)
	glEnd()


def drawScene():

	global vertices, recorrido, vertice1, coordenadas1, coordenadas2, coordenadas3

	glClearColor(0,0,0,0)
	glClear(GL_COLOR_BUFFER_BIT)

	
	#Circulo mayor
	if vista1:
		circulo(300, centro_x, centro_y)
	#-------radio mayor------
	glColor3f(.5, 1, .5)
	glBegin(GL_LINES)	
	extremo_x = 225 * cos(radians(angulo1)) + centro_x
	extremo_y = 225 * sin(radians(angulo1)) + centro_y
	if vista1:
		glVertex2f(centro_x, centro_y)
		glVertex2f(extremo_x, extremo_y)
	glEnd()
	
	#Circulo mediano
	if vista1:
		circulo(75, extremo_x, extremo_y)

	#-------radio menor------
	glColor3f(1, .5, .5)
	glBegin(GL_LINES)	
	extremo_x2 = 25 * cos(radians(angulo2)) + extremo_x
	extremo_y2 = 25 * sin(radians(angulo2)) + extremo_y
	#coordenadas.append([extremo_x2, extremo_y2])
	if vista1:
		glVertex2f(extremo_x, extremo_y)
		glVertex2f(extremo_x2, extremo_y2)
	glEnd()

	#Circulo chico
	if vista1:
		circulo(50, extremo_x2, extremo_y2)

	r = 145
	r2 = 125

	##-------TRIANGULO DE PARABOLAS DENTRO DEL CIRCULO MEDIANO--------------

	if vista2:
		glPushMatrix()
		glTranslatef(extremo_x,extremo_y,0)
		glRotatef(ang1,0,0,1)
		#parabola1
		_x = r * cos(radians(60))
		_y = r * sin(radians(60))
		glColor3f(0,0,1)
		glBegin(GL_LINE_STRIP)
		for i in range(210,271):
			__x = r2 * cos(radians(i)) + _x
			__y = r2 * sin(radians(i)) + _y
			glVertex2f(__x, __y)
		glEnd()
		#parabola2
		_x = r * cos(radians(180))
		_y = r * sin(radians(180))
		glColor3f(0,0,1)
		glBegin(GL_LINE_STRIP)
		for i in range(330,391):
			__x = r2 * cos(radians(i)) + _x
			__y = r2 * sin(radians(i)) + _y
			glVertex2f(__x, __y)
		glEnd()
		#parabola3
		_x = r * cos(radians(300))
		_y = r * sin(radians(300))
		glColor3f(0,0,1)
		glBegin(GL_LINE_STRIP)
		for i in range(90,151):
			__x = r2 * cos(radians(i)) + _x
			__y = r2 * sin(radians(i)) + _y
			glVertex2f(__x, __y)
		glEnd()
		

		glPopMatrix()

		#se guardan las posiciones actuales del triangulo de parabolas
		coords.append([extremo_x, extremo_y, ang1])

		#se dibuja el recorrido de las parabolas con ayuda de las pociciones respaldadas en coords
		glColor3f(0,1,0)
		n = 0
		for c in coords:
			if n % 3 == 0:
				glPushMatrix()
				glTranslatef(c[0],c[1],0)
				glRotatef(c[2],0,0,1)
				#parabola1
				_x = r * cos(radians(60))
				_y = r * sin(radians(60))
				glColor3f(0,0,1)
				glBegin(GL_LINE_STRIP)
				for i in range(210,271):
					__x = r2 * cos(radians(i)) + _x
					__y = r2 * sin(radians(i)) + _y
					glVertex2f(__x, __y)
				glEnd()
				#parabola2
				_x = r * cos(radians(180))
				_y = r * sin(radians(180))
				glColor3f(0,0,1)
				glBegin(GL_LINE_STRIP)
				for i in range(330,391):
					__x = r2 * cos(radians(i)) + _x
					__y = r2 * sin(radians(i)) + _y
					glVertex2f(__x, __y)
				glEnd()
				#parabola3
				_x = r * cos(radians(300))
				_y = r * sin(radians(300))
				glColor3f(0,0,1)
				glBegin(GL_LINE_STRIP)
				for i in range(90,151):
					__x = r2 * cos(radians(i)) + _x
					__y = r2 * sin(radians(i)) + _y
					glVertex2f(__x, __y)
				glEnd()
				glPopMatrix()
			n+=1

	##--------------------------------------------

	if menu:
		#botones pausar
		glColor3f(1,1,1)
		glBegin(GL_POLYGON)
		glVertex2f(300, 300)
		glVertex2f(300, 320)
		glVertex2f(380, 320)
		glVertex2f(380, 300)
		glEnd()
		glColor3f(0,0,0)
		glRasterPos2f(310,305)
		writeBitmapString(GLUT_BITMAP_HELVETICA_12,"Pausar")
		#botones cerrar
		glColor3f(1,1,1)
		glBegin(GL_POLYGON)
		glVertex2f(300, 275)
		glVertex2f(300, 295)
		glVertex2f(380, 295)
		glVertex2f(380, 275)
		glEnd()
		glColor3f(0,0,0)
		glRasterPos2f(310,280)
		writeBitmapString(GLUT_BITMAP_HELVETICA_12,"Vista 1")
		#botones cerrar
		glColor3f(1,1,1)
		glBegin(GL_POLYGON)
		glVertex2f(300, 250)
		glVertex2f(300, 270)
		glVertex2f(380, 270)
		glVertex2f(380, 250)
		glEnd()
		glColor3f(0,0,0)
		glRasterPos2f(310,255)
		writeBitmapString(GLUT_BITMAP_HELVETICA_12,"Vista 2")
		#botones cerrar
		glColor3f(1,1,1)
		glBegin(GL_POLYGON)
		glVertex2f(300, 225)
		glVertex2f(300, 245)
		glVertex2f(380, 245)
		glVertex2f(380, 225)
		glEnd()
		glColor3f(0,0,0)
		glRasterPos2f(310,230)
		writeBitmapString(GLUT_BITMAP_HELVETICA_12,"Cerrar")

	glColor3f(1,1,1)
	glRasterPos2f(10,10)
	writeBitmapString(GLUT_BITMAP_HELVETICA_12,"Clic Derecho: Menu")
	
	glFlush()

def timer(value):
	global angulo1, angulo2, ang1, coords, pause

	#si el gif no esta pausado se cumple lo siguiente
	if pause == False:

		#se incrementan los angulos de rotacion de los radios
		angulo1 -= 2
		angulo2 += 22

		if angulo1 % 360 == 0:
			coords = []

		ang1 += 6

	#los datos se reinician a los valores predeterminados
	if reinicio:
		angulo1 = 0
		angulo2 = 0
		coords = []
		ang1 = 0
		pause = False

	#pausa = False

	glutPostRedisplay()
	glutTimerFunc(retardo ,timer, 1)

def mouseControl(button, state, x, y): 
	global pause, reinicio , menu, cerrar, vista1, vista2
	y = height - y

	##se da clic izquierdo para pausar
	if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
		#coordenadas del boton de pause
		if x >= 300 and x <= 380 and y >= 300 and y <= 320:
			pause = not pause
		#coordenadas del boton de vista1
		if x >= 300 and x <= 380 and y >= 275 and y <= 295:
			vista1 = not vista1
		#coordenadas del boton de vista2
		if x >= 300 and x <= 380 and y >= 250 and y <= 270:
			vista2 = not vista2
		#coordenadas del boton de cerrar
		if x >= 300 and x <= 380 and y >= 225 and y <= 245:
			exit(0)

	##se da clic derecho para reinicio
	if button == GLUT_RIGHT_BUTTON and state == GLUT_DOWN:
		menu = not menu

	glutPostRedisplay()

def mouseMotion(x, y):
	y = height - y
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
	glutInitWindowSize(600, 600)
	glutInitWindowPosition(100, 100) 
	glutCreateWindow("Practica 2")
	glutDisplayFunc(drawScene)
	glutReshapeFunc(resize)
	glutKeyboardFunc(keyInput)
	glutMouseFunc(mouseControl)
	glutMotionFunc(mouseMotion)
	glutTimerFunc(retardo,timer, 1)
	glutMainLoop()
main()