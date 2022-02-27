from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
from math import *
import sys

def drawScene():
	glClearColor(0,0,0,0)
	glClear(GL_COLOR_BUFFER_BIT)
	glColor3f(1,0,0)

	glBegin(GL_LINE_STRIP)
	
	
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
