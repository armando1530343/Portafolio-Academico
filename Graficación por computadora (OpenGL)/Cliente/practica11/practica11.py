from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
from math import *
import sys

def circulo(posx, posy, radio):
	glBegin(GL_LINE_STRIP)
	#glColor3f(0,0,0)
	for ang in range(361):
		x = radio * cos(radians(ang)) + posx
		y = radio * sin(radians(ang)) + posy
		glVertex2f(x,y)

	glEnd()

def drawScene():
	glClearColor(1,1,1,0)
	glClear(GL_COLOR_BUFFER_BIT)
	glColor3f(0,0,0)

	circulo(200, 200, 50)


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
	#glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
	glutInitWindowSize(500, 500)
	glutInitWindowPosition(100, 100) 
	glutCreateWindow("circulo")
	glutDisplayFunc(drawScene)
	glutReshapeFunc(resize)
	glutMainLoop()
main()
