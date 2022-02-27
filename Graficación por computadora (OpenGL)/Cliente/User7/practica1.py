from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
from math import *
import sys

width = 0
height = 0

#punto central (negro)
centro_x = 500
centro_y = 100
#punto central (rojo)
rojo_x = 400
rojo_y = 300
#punto central (azul)
azul_x = 600
azul_y = 300

#preciona puntos
punto_centro = False
punto_rojo = False
punto_azul = False

#angulos
angulo_rojo = 0
angulo_azul = 0

#variables de control
b = 0.0
c = 0.0

#lineas rectangulo
rojo_x2 = 0
rojo_y2 = 0
azul_x2 = 0
azul_y2 = 0

rojo_x3 = 0
rojo_y3 = 0
azul_x3 = 0
azul_y3 = 0

esquina_x = 0
esquina_y = 0

#longitudes
long_rojo = 0
long_azul = 0
long_negro = 0

long_rojo2 = 0
long_azul2 = 0

def writeBitmapString(font, string):
##esta funcion imprime texto en pantalla
   for c in string:
       glutBitmapCharacter(font, ord(c))

#funcion que dibuja toda la camioneta
def drawScene():
	global angulo_azul, angulo_rojo, long_rojo, long_azul, long_rojo2, long_azul2, rojo_x2, rojo_y2, azul_x2, azul_y2

	angulo_rojo = atan2(rojo_y - centro_y, rojo_x - centro_x) * 180 / pi
	angulo_azul = atan2(azul_y - centro_y, azul_x - centro_x) * 180 / pi

	long_rojo = sqrt((rojo_x - centro_x)**2 + (rojo_y - centro_y)**2)
	long_azul = sqrt((azul_x - centro_x)**2 + (azul_y - centro_y)**2)

	long_rojo2 = long_rojo * b
	long_azul2 = long_azul * c

	rojo_x2 = long_rojo2 * cos(radians(angulo_rojo)) + centro_x
	rojo_y2 = long_rojo2 * sin(radians(angulo_rojo)) + centro_y

	azul_x2 = long_azul2 * cos(radians(angulo_azul)) + centro_x
	azul_y2 = long_azul2 * sin(radians(angulo_azul)) + centro_y

	rojo_x3 = long_azul2 * cos(radians(angulo_azul)) + rojo_x2
	rojo_y3 = long_azul2 * sin(radians(angulo_azul)) + rojo_y2

	azul_x3 = long_rojo2 * cos(radians(angulo_rojo)) + azul_x2
	azul_y3 = long_rojo2 * sin(radians(angulo_rojo)) + azul_y2

	esquina_x = long_rojo2 * cos(radians(angulo_azul)) + rojo_x2
	esquina_y = long_rojo2 * sin(radians(angulo_azul)) + rojo_y2

	glClearColor(1,1,1,0)
	glClear(GL_COLOR_BUFFER_BIT)

	#rectangulo
	glColor3f(.7,1,.7)
	glBegin(GL_POLYGON)
	glVertex2f(centro_x, centro_y)
	glVertex2f(rojo_x2, rojo_y2)
	glVertex2f(rojo_x3, rojo_y3)
	glVertex2f(azul_x3, azul_y3)
	glVertex2f(azul_x2, azul_y2)
	glEnd()
	
	glBegin(GL_LINES)	
	#linea roja	
	glColor3f(1,0,0)
	glVertex2f(centro_x, centro_y)
	glVertex2f(rojo_x, rojo_y)	

	#linea azul	
	glColor3f(0,0,1)
	glVertex2f(centro_x, centro_y)
	glVertex2f(azul_x, azul_y)

	#linea negro	
	glColor3f(0,0,0)
	glVertex2f(centro_x, centro_y)
	glVertex2f(azul_x3, azul_y3)

	glEnd()

	glColor3f(0,0,0)
	glPointSize(10)
	glBegin(GL_POINTS)
	#punto negro
	glVertex2f(centro_x, centro_y)
	#punto rojo
	glColor3f(1,0,0)
	glVertex2f(rojo_x, rojo_y)
	#punto azul
	glColor3f(0,0,1)
	glVertex2f(azul_x, azul_y)
	glEnd()

	glColor3f(0,0,0)
	glRasterPos2f(10, 100)
	writeBitmapString(GLUT_BITMAP_HELVETICA_18,"b = ")
	glRasterPos2f(40, 100)
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, str(b))

	glRasterPos2f(10, 80)
	writeBitmapString(GLUT_BITMAP_HELVETICA_18,"c = ")
	glRasterPos2f(40, 80)
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, str(c))

	glRasterPos2f(10, 60)
	writeBitmapString(GLUT_BITMAP_HELVETICA_18,"Tecla B = b++, Tecla b = b--")
	glRasterPos2f(10, 40)
	writeBitmapString(GLUT_BITMAP_HELVETICA_18,"Tecla C = c++, Tecla c = c--")
	glRasterPos2f(10, 20)
	writeBitmapString(GLUT_BITMAP_HELVETICA_18,"Mover los vertices con clic del mouse")

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

def mouseControl(button, state, x, y):

	global punto_centro, punto_rojo, punto_azul

	y = height - y

	if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
		if x >= centro_x - 5 and x <= centro_x + 5 and y >= centro_y - 5 and y <= centro_y + 5:
			punto_centro = True
	else:
		punto_centro = False
	
	if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
		if x >= rojo_x - 5 and x <= rojo_x + 5 and y >= rojo_y - 5 and y <= rojo_y + 5:
			punto_rojo = True
	else:
		punto_rojo = False
	
	if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
		if x >= azul_x - 5 and x <= azul_x + 5 and y >= azul_y - 5 and y <= azul_y + 5:
			punto_azul = True
	else:
		punto_azul = False

	glutPostRedisplay()

def mouseMotion(x, y):

	global centro_x, centro_y, rojo_x, rojo_y, azul_x, azul_y

	y = height - y

	if punto_centro == True:
		centro_x = x
		centro_y = y
	
	if punto_rojo == True:
		rojo_x = x
		rojo_y = y
	
	if punto_azul == True:
		azul_x = x
		azul_y = y
	
	glutPostRedisplay()

def keyInput(key, x, y):

	global b, c

	if (key == 'B'):
		if (b < 5.0): 
			b += .1
	if (key == 'b'):
		if (b > -5.0): 
			b -= .1
		#if b > -5: b -= 1
	
	if (key == 'C'):
		if (c < 5.0): 
			c += .1
	
	if (key == 'c'):
		if (c > -5.0): 
			c -= .1
		#if c > -5: c -= 1
	
	glutPostRedisplay()

def main():
	glutInit(sys.argv)
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
	glutInitWindowSize(1000, 600)
	glutInitWindowPosition(100, 100) 
	glutCreateWindow("Practica 1")
	glutDisplayFunc(drawScene)
	glutReshapeFunc(resize)

	glutKeyboardFunc(keyInput)   
	glutMouseFunc(mouseControl)
	glutMotionFunc(mouseMotion)

	glutMainLoop()
main()

"""

Desarrollo experimental:

Primero se declararon las coordenadas X y Y de cada vertice dandole un valor asignado por defecto. Para graficar los vertices se utilizo la funcion de Opengl GL_POINTS con un tamano de 10, para cada punto se asignaron dos coordenadas con glVertex2f(x, y). Tambien se utilizo la funcion de mouse control en la cual se hicieron las validaciones para verificar que se selecciono correctamente las posiciones de cada vertice y de ser asi, moverlo con respecto a la posicion del cursor del mouse, esto con la ayuda de la funcion de mouse motion. Para verificar que un vertice fue seleccionado, se crearon tres variables booleanas correspondientes a cada uno de los vertices, que, cambiaran su valor a true cada que el clic corresponda dentro del area de posicion del vertice.
La variable 'b' incrementa 0.1 o decrementa -0.1 con respecto al vector rojo, y su longitud es igual al producto del valor de 'b' por la longitud del vector, al igual, la variable 'c' hace lo mismo pero con respecto al vector azul. Al manupular los valores se forma un poligono entre los vectores.
"""
