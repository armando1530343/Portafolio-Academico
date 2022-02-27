from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
from math import *
import sys

def writeBitmapString(font, string):
    ##esta funcion imprime texto en pantalla
    for c in string:
        glutBitmapCharacter(font, ord(c))

#funcion que grafica partes de un circulo dependiento del rango de angulos que se dibujara
def circulo(posx, posy, radio, rango1, rango2, color, n):
    #dibuja el polygono con relleno de color
    glBegin(GL_POLYGON)
    glColor3f(color[0], color[1], color[2])
    glVertex2f(posx, posy)
    for ang in range(rango1, rango2):
        x = radio * cos(radians(ang)) + posx
        y = radio * sin(radians(ang)) + posy
        glVertex2f(x,y)

    glEnd()

    #dibuja el contorno del poligono dibujado de color blanco
    glBegin(GL_LINE_LOOP)
    glColor3f(1,1,1)
    if n == 0: 
        glVertex2f(posx, posy)
    for ang in range(rango1, rango2):
        x = radio * cos(radians(ang)) + posx
        y = radio * sin(radians(ang)) + posy
        glVertex2f(x,y)

    glEnd()

def drawScene():
    glClearColor(0,0,0,0)
    glClear(GL_COLOR_BUFFER_BIT)

    circulo(325,325,300,125,181,[.7,.6,0],0)
    glColor3f(0,0,0)
    glRasterPos3f(60, 430, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "Templates")

    circulo(325,325,300,107,126,[.5,0,.6],0)
    glColor3f(0,0,0)
    glRasterPos3f(200, 550, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "JSP")

    circulo(325,325,300,83,108,[.5,0,.6],0)
    glColor3f(0,0,0)
    glRasterPos3f(290, 570, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "RoR")

    circulo(325,325,300,45,84,[.5,0,.6],0)
    glColor3f(0,0,0)
    glRasterPos3f(390, 550, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "ASP.NET")

    circulo(325,325,300,0,46,[.5,0,.6],0)
    glColor3f(0,0,0)
    glRasterPos3f(530, 420, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "PHP")

    circulo(325,325,300,180,261,[.7,.6,0],0)
    glColor3f(0,0,0)
    glRasterPos3f(80, 180, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "Banners")

    circulo(325,325,300,260,287,[.7,.6,0],0)
    glColor3f(0,0,0)
    glRasterPos3f(300, 70, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "Brochures")

    circulo(325,325,300,286,341,[0,.8,.2],0)
    glColor3f(0,0,0)
    glRasterPos3f(480, 130, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "SEO")

    circulo(325,325,300,340,361,[0,.8,.2],0)
    glColor3f(0,0,0)
    glRasterPos3f(550, 280, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "PRs")

    circulo(325,325,200,0,126,[.5,0,.6],0)
    glColor3f(0,0,0)
    glRasterPos3f(340, 450, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "Development")

    circulo(325,325,200,125,287,[.7,.6,0],0)
    glColor3f(0,0,0)
    glRasterPos3f(150, 280, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "Design")

    circulo(325,325,200,286,361,[0,.8,.2],0)
    glColor3f(0,0,0)
    glRasterPos3f(400, 230, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "Marketing")

    circulo(325,325,100,0,361,[.7,.7,.7],1)
    glColor3f(0,0,0)
    glRasterPos3f(270, 325, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "Adwords Clicks")
    
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
    glutInitWindowSize(650, 650)
    glutInitWindowPosition(100, 0) 
    glutCreateWindow("practica 2")
    glutDisplayFunc(drawScene)
    glutReshapeFunc(resize)
    glutMainLoop()
main()
