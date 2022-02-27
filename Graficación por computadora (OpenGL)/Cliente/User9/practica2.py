from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
from math import *
import sys

#coordenadas de los vertices del triangulo
vertices_triangulo = [[0,0,90],[0,0,330],[0,210]]

#angulo de posicion de los vertices
angulo_vertices = [90, 30, 330, 270, 210, 150]

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

def nuevo_circulo(coordenadaX, coordenadaY, radio):
    glBegin(GL_LINE_STRIP)
    for a in range(361):
        x = radio * cos(radians(a)) + coordenadaX
        y = radio * sin(radians(a)) + coordenadaY
        glVertex2f(x,y)

    glEnd()

def drawScene():
    glClearColor(1,1,1,0)
    glClear(GL_COLOR_BUFFER_BIT)
    glColor3f(0,0,0)
    nuevo_circulo(300,300,280)    
    
    glFlush()


def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
    glutInitWindowSize(600, 600)
    glutInitWindowPosition(100, 0) 
    glutCreateWindow("practica 2")
    glutDisplayFunc(drawScene)
    glutReshapeFunc(resize)
    glutMainLoop()
main()
