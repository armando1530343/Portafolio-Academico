from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
from math import *
import sys

width = 0
height = 0

X = 300 #centro X
Y = 150 #centro Y

constante = 0.0 #constante de la ecuacion

def writeBitmapString(font, string):
##esta funcion imprime texto en pantalla
   for c in string:
       glutBitmapCharacter(font, ord(c))

def drawScene():

	global constante

	glClearColor(1,1,1,0)
	glClear(GL_COLOR_BUFFER_BIT)

	#se dibuja la curva de la ecuacion y = x*x - 8x + 19
	glBegin(GL_LINE_STRIP)
	glColor3f(1,0,0)
	for x in range(-500, 500):
		y = (constante * x) - 5;
		glVertex2f(x*4 + X, y*4 + Y)
	glEnd()
	glColor3f(1,0,0)
	glRasterPos2f(400,100)
	writeBitmapString(GLUT_BITMAP_HELVETICA_18,"y = " + str(constante) + "x - 5")


	#se dibuja la ecuacion de la recta variable
	glBegin(GL_LINE_STRIP)
	glColor3f(1,0,1)
	for x in range(-500, 500):
		y = x*x - 8*x + 19;
		glVertex2f(x*4 + X, y*4 + Y)
	glEnd()
	glColor3f(1,0,1)
	glRasterPos2f(320,250)
	writeBitmapString(GLUT_BITMAP_HELVETICA_18,"y = x*x - 8x + 19")

	print constante

	#Ejes del plano
	glBegin(GL_LINES)
	glColor3f(0,0,1)
	#eje X
	glVertex2f(0, Y)
	glVertex2f(600, Y)
	#eje Y
	glVertex2f(X, 0)
	glVertex2f(X, 600)
	glEnd()

	#se dibujan los numeros del eje X
	for i in range(-15,15):
		glPointSize(5)
		glBegin(GL_POINTS)
		glVertex2f(X, 40*i + Y)
		glEnd()
		glColor3f(0,0,0)
		glRasterPos2f(X - 30, 40*i + Y)
		writeBitmapString(GLUT_BITMAP_HELVETICA_12,str(10*i))

	#se dibujan los numeros del eje Y
	for i in range(-15,15):
		glPointSize(5)
		glBegin(GL_POINTS)
		glVertex2f(40*i + X, Y)
		glEnd()
		glColor3f(0,0,0)
		glRasterPos2f(40*i + X, Y - 20)
		writeBitmapString(GLUT_BITMAP_HELVETICA_12,str(10*i))

	#----INSTRUCCIONES--
	glColor3f(0,0,0)
	glRasterPos2f(480,580)
	writeBitmapString(GLUT_BITMAP_HELVETICA_12,"Tecla 'a': + 0.5")
	glRasterPos2f(480,560)
	writeBitmapString(GLUT_BITMAP_HELVETICA_12,"Tecla 's': - 0.5")
	glRasterPos2f(480,540)
	writeBitmapString(GLUT_BITMAP_HELVETICA_12,"Tecla 'd': + 0.05")
	glRasterPos2f(480,520)
	writeBitmapString(GLUT_BITMAP_HELVETICA_12,"Tecla 'f': - 0.05")
	glRasterPos2f(480,500)
	writeBitmapString(GLUT_BITMAP_HELVETICA_12,"Tecla 'z': + 0.005")
	glRasterPos2f(480,480)
	writeBitmapString(GLUT_BITMAP_HELVETICA_12,"Tecla 'x': - 0.005")

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

def keyInput(key, x, y):
	global constante

	#conjunto de teclas para modificar el valor de la constante
	if key == 'a':
		constante -= .5
	if key == 's':
		constante += .5
	if key == 'd':
		constante -= .05
	if key == 'f':
		constante += .05
	if key == 'z':
		constante -= .005
	if key == 'x':
		constante += .005
	
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

	glutMainLoop()
main()
"""
Desarrollo experimental:
Se utilizo el lenguage de python y opengl para esta practica. Para dibujar los ejes del plano se uso la funcion GL_LINES trazando una linea vertical en la mitad de la ventana para el eje Y y otra horizontal por debajo para el eje X, cada una dividida en coordenadas de diez en diez,
las cuales son dibujadas con GL_POINTS dentro de un ciclo for para cada eje de -150 a 150. Despues se grafico la funcion x*x - 8x + 19 con GL_LINE_STRIP dando valor a x en un rango de -500 > x > 500.
Por ultimo se grafica la funcion con la variante y = constante*x - 5, dando a 'constante' un valor dependiente del usuario el cual puede incrementarse en valores de +0.5, +0.05 y + 0.005, y de esa forma la ecuacion de la recta se refleja en la grafica de distintas maneras.
Los valores de incremento se pueden modificar con las teclas a,s,d,f,z,x.  
"""