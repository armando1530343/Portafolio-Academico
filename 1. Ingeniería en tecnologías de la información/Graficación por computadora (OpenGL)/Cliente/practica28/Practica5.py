from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
import sys
from math import *

WIDTH = 600
HEIGHT = 600
retardo = 70


def init():
    glEnable(GL_DEPTH_TEST)

def writeBitmapString(font, string):
##esta funcion imprime texto en pantalla
    for c in string:
       glutBitmapCharacter(font, ord(c))

def reShapeCallbackProc(w, h):
    
    global SIZE

    if w<WIDTH or h<HEIGHT:
        glutReshapeWindow(WIDTH,HEIGHT)
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(100.0, w/h, 1.0, 500.0)
    glMatrixMode(GL_MODELVIEW)

def triangulo(x, y, color):
    #se calcula la altura del triangulo segun la medida de sus lados
    altura = sqrt((lado**2) - ((lado/2)**2))

    glBegin(GL_POLYGON)
    glColor3f(color,0,0)
    glVertex2f(x,y)
    glVertex2f(x+lado,y)
    glVertex2f(x+(lado/2),y+altura)
    glEnd()



    for i in range(2):
        if i == 0: z = .1 
        else: z = -.1
        glBegin(GL_LINE_LOOP)
        glColor3f(1,1,1)
        glVertex3f(x,y,z)
        glVertex3f(x+lado,y,z)
        glVertex3f(x+(lado/2),y+altura,z)
        glEnd()

def rectangulo(x, y, color):
    glBegin(GL_POLYGON)
    glColor3f(color,0,0)
    glVertex2f(x, y)
    glVertex2f(x+lado, y)
    glVertex2f(x+lado, y+ancho)
    glVertex2f(x, y+ancho)
    glEnd()
    for i in range(2):
        if i == 0: z = .1 
        else: z = -.1
        glBegin(GL_LINE_LOOP)
        glColor3f(1,1,1)
        glVertex3f(x, y, z)
        glVertex3f(x+lado, y, z)
        glVertex3f(x+lado, y+ancho, z)
        glVertex3f(x, y+ancho, z)
        glEnd()

def boton(x, y, texto):
    glBegin(GL_POLYGON)
    glColor3f(1,1,1)
    glVertex2f(x-17, y-10)
    glVertex2f(x+17, y-10)
    glVertex2f(x+17, y+10)
    glVertex2f(x-17, y+10)
    glEnd()
    glColor3f(0,0,0)
    glRasterPos2f(x-10, y-2)
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, texto)


zoom = 0.5 # zoom de la camara
AngleX = 0 # angulo x de la camara
AngleY = 0 # angulo Y de la camara
AngleZ = 0 # angulo Z de la camara

lado = 35.0
ancho = 25.0

angulo_triangulo1 = 0
angulo_triangulo2 = 180
angulo_rectangulo_der = 0
angulo_rectangulo_izq = -180

colores = [1.0, 1.0, 1.0, 1.0, 1.0]

caras = [True, False, False, False]
retorno = False

def displayCallbackProc():
    global AngleX, AngleY, AngleZ, zoom, colores
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glTranslatef(0, 0, -50)          #Posicion de iniciado        
    glRotatef(AngleX, 1.0, 0.0, 0.0)   #Controla la vista de la camara en X
    glRotatef(AngleY, 0.0, 1.0, 0.0)   #Controla la vista de la camara en Y
    glRotatef(AngleZ, 0.0, 0.0, 1.0)   #Controla la vista de la camara en Z
    glScalef(zoom, zoom, zoom)    #Controla el Zoom

    #boton(0, -70, "Prisma")
    
    #--------cara inferior del prisma (origen de rotacion de todas las caras)---------
    glPushMatrix()# ////////////////
    
    glTranslatef(-lado/2,10,0)
    glRotatef(-50,1,0,0)
    glRotatef(-30,0,0,1)
    rectangulo(0,-ancho, colores[0])
    
    #--------triangulo 1 del prisma
    glPushMatrix()
    glTranslatef(0,0,0)
    glRotatef(angulo_triangulo1,1,0,0)
    triangulo(0,0, colores[1])
    glPopMatrix()
    #--------triangulo 2 del prisma
    glPushMatrix()
    glTranslatef(0,-ancho,0)
    glRotatef(angulo_triangulo2,1,0,0)
    triangulo(0,0, colores[2])
    glPopMatrix()
    #--------rectangulo derecho del prisma
    glPushMatrix()
    glTranslatef(0,-ancho,0)
    glRotatef(angulo_rectangulo_izq,0,1,0)
    rectangulo(0,0, colores[3])
    glPopMatrix()    
    #--------rectangulo derecho del prisma
    glPushMatrix()
    glTranslatef(lado,-ancho,0)
    glRotatef(angulo_rectangulo_der,0,1,0)
    rectangulo(0,0, colores[4])
    glPopMatrix()
    
    
    glPopMatrix()# /////////////////
    
    glutSwapBuffers()

def timer(value):
    global angulo_triangulo1, angulo_triangulo2, angulo_rectangulo_der, angulo_rectangulo_izq, caras, retorno, colores

    n = .5

    if retorno == False:
        if angulo_triangulo1 < 90 and caras[0]: 
            angulo_triangulo1 += 6            
            colores[1] -= (n/90)*6
        elif caras[0]: caras = [False, True, False, False]
        
        if angulo_triangulo2 > 90 and caras[1]: 
            angulo_triangulo2 -= 6
            colores[2] -= (n/90)*6
            colores[0] -= (n/90)*6
        elif caras[1]: caras = [False, False, True, False]

        if angulo_rectangulo_izq < -60 and caras[2]:
            angulo_rectangulo_izq += 7.5
            colores[3] -= (n/90)*7.5
        elif caras[2]: caras = [False, False, False, True]

        if angulo_rectangulo_der > -120 and caras[3]:
            angulo_rectangulo_der -= 7.5 
            colores[4] -= (n/90)*7.5
        elif caras[3]: 
            retorno = True
    else:
        if angulo_rectangulo_der < 0 and caras[3]:
            angulo_rectangulo_der += 7.5 
            colores[4] += (n/90)*7.5
        elif caras[3]: caras = [False, False, True, False] 

        if angulo_rectangulo_izq > -180 and caras[2]:
            angulo_rectangulo_izq -= 7.5
            colores[3] += (n/90)*7.5
        elif caras[2]: caras = [False, True, False, False]

        if angulo_triangulo2 < 180 and caras[1]: 
            angulo_triangulo2 += 6
            colores[2] += (n/90)*6
            colores[0] += (n/90)*6
        elif caras[1]: caras = [True, False, False, False]

        if angulo_triangulo1 > 0 and caras[0]: 
            angulo_triangulo1 -= 6
            colores[1] += (n/90)*6            
        elif caras[0]: retorno = False

    glutPostRedisplay()
    glutTimerFunc(retardo, timer, 1)

def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
    glutInitWindowSize(WIDTH, HEIGHT)
    glutInitWindowPosition(50, 10)
    glutCreateWindow(" Practica 5")
    init()
    glutDisplayFunc(displayCallbackProc)
    glutReshapeFunc(reShapeCallbackProc)
    glutTimerFunc(retardo,timer, 1)
    glutMainLoop()

main()