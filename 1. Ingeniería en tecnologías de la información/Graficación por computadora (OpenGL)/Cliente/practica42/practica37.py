from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
import sys
from math import *

SIZE = 650

zoom = 0.5 # zoom de la camara
AngleX = 40 # angulo x de la camara
AngleY = 0 # angulo Y de la camara
AngleZ = 0 # angulo Z de la camara


#funcion que dibuja un poligono en 3D
def DibujaCilindro(X, Y, Z, rad, anchura, LADOS, colores):
    glTranslatef(X, Y, Z)
    radio = 0.0

    Puntos = [range(500) for i in range(2)]
    for i in range(2):
        for j in range(500):
            Puntos[i][j] = [0,0,0]

    Contador = 0;
    for i in range(2):
        glBegin(GL_POLYGON)
        glColor3f(.2,.2,.2)
        radio = rad
        Contador = 0

        angle = 0.0

        while angle <= (2.0 * pi):
            Puntos[i][Contador][0] = radio * sin(angle) + X
            Puntos[i][Contador][1] = radio * cos(angle) + Y
            Puntos[i][Contador][2] = Z
            glVertex3f(Puntos[i][Contador][0], Puntos[i][Contador][1], Puntos[i][Contador][2])
            Contador = Contador + 1
            angle = angle + (2.0 * pi) / LADOS

        glEnd()
        Z = Z - anchura

    for Contador in range(LADOS):
        glBegin(GL_POLYGON)        
        glColor3f(colores[0], colores[1], colores[2])
        Temporal = 0
        if Contador == int(LADOS - 1):
            Temporal = 0
        else:
            Temporal = Contador + 1
        glVertex3f(Puntos[0][Contador][0], Puntos[0][Contador][1], Puntos[0][Contador][2])
        glVertex3f(Puntos[0][Temporal][0], Puntos[0][Temporal][1], Puntos[0][Temporal][2])
        glVertex3f(Puntos[1][Temporal][0], Puntos[1][Temporal][1], Puntos[1][Temporal][2])
        glVertex3f(Puntos[1][Contador][0], Puntos[1][Contador][1], Puntos[1][Contador][2])
        glEnd()
   

def init():
    glEnable(GL_DEPTH_TEST)


#teclas de control
def keyboardCallbackProc(key, x, y):
    global AngleX, AngleY, AngleZ, zoom

    if key == 'x': AngleX+=5 # incrementa X
    if key == 'y': AngleY+=5 #incrementa Y
    if key == 'z': AngleZ+=5 # incrementa Z
    if key == '+': zoom+=.05 #aumenta el zoom
    if key == '-': zoom-=.05 #disminuye el zoom
    glutPostRedisplay()
    return

def reShapeCallbackProc(w, h):
    
    global SIZE

    if w<SIZE or h<SIZE:
        glutReshapeWindow(SIZE,SIZE)
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(60.0, w / h, 1.0, 500.0)
    glMatrixMode(GL_MODELVIEW)

def displayCallbackProc():
    global AngleX, AngleY, AngleZ, zoom
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glTranslatef(0, -10, -60)          #Posicion de iniciado        
    glRotatef(AngleX, 1.0, 0.0, 0.0)   #Controla la vista de la camara en X
    glRotatef(AngleY, 0.0, 1.0, 0.0)   #Controla la vista de la camara en Y
    glRotatef(AngleZ, 0.0, 0.0, 1.0)   #Controla la vista de la camara en Z
    glScalef(zoom, zoom, zoom)    #Controla el Zoom

    #cabeza del tornillo
    glPushMatrix()
    glTranslatef(0, 50, 0)
    glRotatef(90, 1, 0, 0)
    DibujaCilindro(0, 0, 0, 16, 15, 6, [.4,.4,.4])
    glPopMatrix()
    glPushMatrix()
    glTranslatef(0, 65, 0)
    glRotatef(90, 1, 0, 0)
    DibujaCilindro(0, 0, 0, 8, 2, 6, [.7,.7,.7])
    glPopMatrix()

    #cuerpo del tornillo
    glPushMatrix()
    glTranslatef(0, 0, 0)
    glRotatef(90, 1, 0, 0)
    DibujaCilindro(0, 0, 0, 8, 50, 20, [.4,.4,.4])
    glPopMatrix()

    #ruedas del tornillo
    for i in range(1,15):
        glPushMatrix()
        glTranslatef(0, 4*i, 0)
        glRotatef(90, 1, 0, 0)
        DibujaCilindro(0, 0, 0, 9, 1, 20, [.7,.7,.7])
        glPopMatrix()

    glutSwapBuffers()

def main():
    print 'Teclas:'
    print ' X: angulo X de la camara'
    print ' Y: angulo Y de la camara'
    print ' Z: angulo Z de la camara'
    print ' +: aumenta zoom'
    print ' -: disminuye zoom'
    
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
    glutInitWindowSize(SIZE, SIZE)
    glutInitWindowPosition(300, 50)
    glutCreateWindow(" Practica 04_Tornillo 3D")
    init()
    glutDisplayFunc(displayCallbackProc)
    glutKeyboardFunc(keyboardCallbackProc)
    glutReshapeFunc(reShapeCallbackProc)
    glutMainLoop()

main()