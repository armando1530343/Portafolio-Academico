from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
from math import *
import sys
import time

circuloMes = [range(2) for i in range(12)]

# %d dia del mes
# 

anio = time.strftime("%Y")

radio = 350

diaMes = [31,28,31,30,31,30,31,31,30,31,30,31]
mes = ['Ene','Feb','Mar','Abr','May','Jun','Jul','Ago','Sep','Oct','Nov','Dic']



#funcion que imprime los numeros en la ruleta
def writeBitmapString(font, string):
   for c in string:
       glutBitmapCharacter(font, ord(c))



def drawScene():
	global anio, diaMes, mes
	glClearColor(1,1,1,0)
	glClear(GL_COLOR_BUFFER_BIT)

	glBegin(GL_POLYGON)
	glColor3f(0,.1,1)

	for ang in range(361):
		x = radio * cos(radians(ang)) + 350
		y = radio * sin(radians(ang)) + 350
		glVertex2f(x,y)

	glEnd()

	glColor3f(0,0,0)
	glRasterPos2f(350, 350)
	writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, str(anio))

	i = 0

	glPointSize(5)
	glBegin(GL_POINTS)
	glColor3f(0,1,0)
	for ang in range(361):
		if ang%30 == 0 and ang != 0:			
			x = (radio * cos(radians(ang))*.75 + 350)
			y = (radio * sin(radians(ang))*.75 + 350)
			glVertex2f(x,y)
			circuloMes[i][0] = x
			circuloMes[i][1] = y
			i = i + 1

	glEnd()

	radio2 = 68

	for i in range(12):
		glBegin(GL_POLYGON)

		if i < 3: glColor3f(1,0,0)
		elif i < 6: glColor3f(0,1,0)
		elif i < 9: glColor3f(1,0,1)
		elif i < 12: glColor3f(1,1,0)

		for ang in range(361):

			x = radio2 * cos(radians(ang)) + circuloMes[i][0]
			y = radio2 * sin(radians(ang)) + circuloMes[i][1]
			glVertex2f(x,y)

		glEnd()

		glColor3f(0,0,0)
		glRasterPos2f(circuloMes[i][0], circuloMes[i][1])
		writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, mes[i])

	#i = 0
	

	for i in range(12):
		ang=1.0
		dia = 1
		while ang <= 360:#in range(361):
			if ang > 90 and ang < 270: n = 1
			else: n = .9 
			if ang%11.25 == 0:			
				x = ((radio2-10) * cos(radians(ang)) + circuloMes[i][0])
				y = ((radio2-10) * sin(radians(ang)) + circuloMes[i][1])
				
				
				if dia < diaMes[i]+1:
					glColor3f(0,0,0)
					glRasterPos2f(x, y)
					writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, str(dia))
					
				dia = dia + 1
			ang = ang + .25
	

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
	glutDisplayFunc(drawScene)
	glutReshapeFunc(resize)
	glutMainLoop()

main()