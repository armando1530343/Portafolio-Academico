from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
from math import *
import sys


#funcion que dibuja un circulo
def llanta(posx, posy, radio):
	glBegin(GL_LINE_STRIP)
	for ang in range(361):
		x = radio * cos(radians(ang)) + posx
		y = radio * sin(radians(ang)) + posy
		glVertex2f(x,y)

	glEnd()

#funcion que dibuja la mitad de arriba de un circulo
def curva(posx, posy, radio):
	glBegin(GL_LINES)
	
	for ang in range(181):
		x = radio * cos(radians(ang)) + posx
		y = radio * sin(radians(ang)) + posy
		glVertex2f(x,y)

	glEnd()

#funcion que dibuja toda la camioneta
def drawScene():
	glClearColor(0,0,0,0)
	glClear(GL_COLOR_BUFFER_BIT)
	glColor3f(1,1,1)

	curva(300,100,70)
	curva(300,100,75)
	curva(300,100,80)

	#parte trasera
	glBegin(GL_LINE_STRIP)
	glVertex2f(370, 100)
	glVertex2f(450, 100)
	glVertex2f(450, 220)
	glVertex2f(140, 220)
	glVertex2f(140, 205)
	glVertex2f(450, 205)
	glVertex2f(140, 205)
	glVertex2f(160, 205)
	glVertex2f(165, 190)
	glVertex2f(165, 170)
	glVertex2f(135, 170)
	glVertex2f(135, 173)
	glVertex2f(162, 173)
	glVertex2f(162, 187)
	glVertex2f(157, 202)
	glVertex2f(140, 202)
	glVertex2f(140, 205)
	glVertex2f(140, 202)
	glVertex2f(137, 190)
	glVertex2f(137, 170)
	glVertex2f(145, 140)
	glVertex2f(230, 140)
	glVertex2f(140, 140)
	glVertex2f(140, 125)
	glVertex2f(155, 100)
	glVertex2f(230, 100)
	glEnd()

	llanta(300,100,60)
	llanta(300,100,35)

	#Cabina
	glBegin(GL_LINE_STRIP)
	glVertex2f(730, 100)
	glVertex2f(450, 100)
	glVertex2f(450, 220)
	glVertex2f(465, 300)
	glVertex2f(650, 300)
	glVertex2f(750, 220)
	glVertex2f(920, 200)
	glVertex2f(930, 185)
	glVertex2f(910, 185)
	glVertex2f(900, 150)
	glVertex2f(930, 150)
	glVertex2f(930, 153)
	glVertex2f(903, 153)
	glVertex2f(913, 182)
	glVertex2f(930, 182)
	glVertex2f(930, 185)
	glVertex2f(930, 150)
	glVertex2f(860, 150)
	glVertex2f(950, 150)
	glVertex2f(950, 130)
	glVertex2f(930, 100)
	glVertex2f(870, 100)
	glEnd()

	curva(800,100,70)
	curva(800,100,75)
	curva(800,100,80)
	llanta(800,100,60)
	llanta(800,100,35)

	#puertas
	glBegin(GL_LINE_STRIP)
	glVertex2f(465,120)
	glVertex2f(475,290)
	glVertex2f(650,290)
	glVertex2f(655,295)
	glVertex2f(660,292)
	glVertex2f(657,287)
	glVertex2f(730,225)
	glVertex2f(745,225)
	glVertex2f(750,220)
	glVertex2f(730,220)
	glVertex2f(650,290)
	glVertex2f(730,220)
	glVertex2f(730,150)
	glVertex2f(715,120)
	glVertex2f(465,120)
	glVertex2f(540,120)
	glVertex2f(545,290)
	glVertex2f(545,285)
	glVertex2f(490,285)
	glVertex2f(487,215)
	glVertex2f(542,215)
	glVertex2f(542,220)
	glVertex2f(492,220)
	glVertex2f(495,280)
	glVertex2f(545,280)
	glEnd()

	#ventana
	glBegin(GL_LINE_STRIP)
	glVertex2f(550,215)
	glVertex2f(552,285)
	glVertex2f(645,285)
	glVertex2f(715,215)
	glVertex2f(675,215)
	glVertex2f(675,255)
	glVertex2f(675,250)
	glVertex2f(645,280)
	glVertex2f(557,280)
	glVertex2f(555,220)
	glVertex2f(675,220)
	glVertex2f(675,215)
	glVertex2f(550,215)
	glEnd()

	#lineas
	glBegin(GL_LINE_STRIP)
	glVertex2f(450,205)
	glVertex2f(750,205)
	glVertex2f(910,185)
	glEnd()
	glBegin(GL_LINES)
	glVertex2f(370,140)
	glVertex2f(730,140)
	glVertex2f(370,135)
	glVertex2f(730,135)
	glVertex2f(380,110)
	glVertex2f(720,110)
	glVertex2f(380,105)
	glVertex2f(720,105)
	glEnd()
	glBegin(GL_LINE_LOOP)
	glVertex2f(550,200)
	glVertex2f(580,200)
	glVertex2f(580,186)
	glVertex2f(550,186)
	glEnd()
	glBegin(GL_LINE_LOOP)
	glVertex2f(553,197)
	glVertex2f(577,197)
	glVertex2f(577,189)
	glVertex2f(553,189)
	glEnd()


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
	glutInitWindowSize(1100, 500)
	glutInitWindowPosition(100, 100) 
	glutCreateWindow("Troca")
	glutDisplayFunc(drawScene)
	glutReshapeFunc(resize)
	glutMainLoop()
main()
