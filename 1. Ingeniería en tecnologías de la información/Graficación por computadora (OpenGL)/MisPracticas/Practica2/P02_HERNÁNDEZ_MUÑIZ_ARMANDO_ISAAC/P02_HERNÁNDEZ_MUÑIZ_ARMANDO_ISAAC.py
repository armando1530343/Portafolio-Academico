from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
from math import *
import sys

width = 0 #valor inicial en x del mouse
height = 0 #valor inicial en y del mouse
size = 10.0 

#Coordenadas de los lados del triangulo
ax = 300 
ay = 100
bx = 300.0
by = 300.0
cx = 500
cy = 100
#Variables para el teorema de pitagoras
hip = 1
ca = 1
co = 1

altura = 0

#angulos internos del triangulo
A = 90
B = 60
C = 30

#lados del triangulo
a=0
b=0
c=0


def lineas():
    #se dibuja el vertice del triangulo que se movera
    glPointSize(size)
    glBegin(GL_POINTS)
    glVertex3f(bx, by, 0.0)
    glEnd()

    #se dibujan las lineas que forman el triangulo    
    glBegin(GL_LINE_LOOP)
    glVertex3f(ax, ay, 0.0)
    glVertex3f(bx, by, 0.0)
    glVertex3f(cx, cy, 0.0)
    glEnd()
    ##se dibuja el eje X
    glBegin(GL_LINES)
    glColor3f(1.0,0.0,0.0)
    glVertex3f(150.0, by, 0.0)
    glVertex3f(650.0, by, 0.0)
    
    glEnd()
    
    angulos()

def angulos():
    global hip, ca, co, altura, A, B, C, a, b, c

    glRasterPos3f(50.0, 470.0, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "TECLAS: '+', '-', 'w', 's'")

    glRasterPos3f(50.0, 10.0, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "ARMANDO HERNANDEZ")

    ##se calculan la medida de los lados del triangulo
    ##utilizando el teorema de pitagoras
    a =  sqrt(pow(bx - cx, 2) + pow(by - cy, 2))
    b =  sqrt(pow(ax - cx, 2) + pow(ay - cy, 2))
    c =  sqrt(pow(ax - bx, 2) + pow(ay - by, 2))

    if a > b and b > c or a > c and c > b:
        hip = a
        co = c
        ca = b
        
    if b > a and a > c or b > c and c > a:
        hip = b
        co = a
        ca = c
    if c > a and a > b or c > b and b > a:
        hip = c
        co = a
        ca = b

    ##se sacan los angulos internos con ley de senos y cosenos
    C = acos(ca / hip) * 180 / pi
    B = 180 - (A + C)

    ##Se mostrara en ejecucion las medidas de los lados del triangulo
    glColor3f(0.0,0.0,0.0)
    glRasterPos3f(50.0, 430.0, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "lado a: " + str(round(a)))
    glRasterPos3f(50.0, 410.0, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "lado b: " + str(round(b)))
    glRasterPos3f(50.0, 390.0, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "lado c: " + str(round(c)))

    sup1 = A
    sup2 = 180 - A - B

    glRasterPos3f(bx - 50, by - 20, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, str(round(sup1)) + chr(248))
    glRasterPos3f(bx + 40, by - 20, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, str(round(sup2)) + chr(248))

    glRasterPos3f(ax - 10, ay - 10, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "A")
    glRasterPos3f(bx, by + 10, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "B")
    glRasterPos3f(cx + 5, cy - 10, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "C")
    
    glColor3f(1.0,0.0,0.0)
    glRasterPos3f(ax + 5, ay + 5, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, str(round(A)) + chr(248))
    glRasterPos3f(bx, by - 30, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, str(round(B)) + chr(248))
    glRasterPos3f(cx - 30, cy + 5, 0.0)
    writeBitmapString(GLUT_BITMAP_8_BY_13, str(round(C)) + chr(248))


    

    

def writeBitmapString(font, string):
##esta funcion imprime texto en pantalla
   for c in string:
       glutBitmapCharacter(font, ord(c))

def drawScene():
    global bx, by
    glClearColor(1.0, 1.0, 1.0, 0.0)
    glClear(GL_COLOR_BUFFER_BIT)
    glColor3f(0.0, 0.0, 0.0)   
    lineas()
    glFlush()

def mouseControl(button, state, x, y):
    global bx, by

    ##condiciones para el movimiento del mouse
    if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN):
        bx = x
        by = y
        print x , " " , y
    glutPostRedisplay()
    return

def mouseMotion(x, y):
   global bx, by, A, a, b, c

   xp = bx + bx/by
   yp = by + by/bx
   
   if height - y >= ay + 100:      
       
       bx = xp
       by = height - yp
       
       glutPostRedisplay()
       return

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


altura = by - ay
altura = altura / A
xp = bx/by
yp = by/bx

def keyInput(key, x, y):
    global A, B, C,  bx, by, altura    
    
    print altura

    if key == '+' and A <= 89.0: ##
        by += float(altura)
        bx -= 2
        A+=1
    if key == '-' and A > 40:
        by -= float(altura)
        bx += 2
        A -= 1
    if key == 'w' and A == 90 and by < 320:
        #bx += bx/by
        by *= 1.01
    if key == 'w' and A < 90 and by < 320:
        bx *= 1.01 
        by *= 1.025
    if key == 's' and A == 90 and by > ay + 100:
        #bx += bx/by
        by /= 1.01
    if key == 's' and A < 90 and by > ay + 100:
        bx /= 1.01 
        by /= 1.025
        
        
    glutPostRedisplay() 
    
    return      

    

def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
    #glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
    glutInitWindowSize(800, 500)
    glutInitWindowPosition(100, 100) 
    glutCreateWindow("Triangle Sum Theorem")
    glutDisplayFunc(drawScene)
    glutReshapeFunc(resize)
    #glutMouseFunc(mouseControl) 
    #glutMotionFunc(mouseMotion)
    glutKeyboardFunc(keyInput)
    #setup()
    glutMainLoop()
main()
