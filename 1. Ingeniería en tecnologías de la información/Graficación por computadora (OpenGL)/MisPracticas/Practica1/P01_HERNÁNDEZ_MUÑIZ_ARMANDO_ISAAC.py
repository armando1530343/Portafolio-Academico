from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
import sys
import math
#ecu = "2x^2-4x+7"
#ecu = "4x^3-10+3x-2x^2"
#ecu = "x^3-x^2-3x-2"

ecu = raw_input("Ingresa una ecuacion: ")



rango = [-5,-4,-3,-2,-1,0,1,2,3,4,5]

#print len(ecu)

def ecuacion(x):
    cad=""
    pot = 0
    potencia = 0
    equis = False
    i=0
    y = 0
    while i < len(ecu):
        #print i 
        
        if ecu[i] != 'x' and ecu[i] != 'X' and ecu[i] != '^' and pot == 0:
            cad += ecu[i]            
                  
        if ecu[i] == '-' or ecu[i] == '+':
            cad = ecu[i]
            equis = False

        if ecu[i] == 'x' or ecu[i] == 'X':
            equis = True
            
        if ecu[i] == '^':
            pot = 1
            i+=1
            continue

        if pot == 1:
            potencia = int(ecu[i])
            pot = 0
            if cad == '+' or cad == '-': cad += "1"
            y += int(cad)* (pow(x,potencia))                        
            #print cad + "("+ str(x)+")" + "^" + str(potencia)+" = "+str(y)
            if i == len(ecu)-1: break
            
        if i < len(ecu)-1:
            if ecu[i+1] != '^' and (ecu[i] == 'x' or ecu[i] == 'X'):
                if cad == '+' or cad == '-': cad += "1"
                y += int(cad)* x                
                #print cad + "("+ str(x)+") = "+str(y)
            if equis == False and pot == 0 and (ecu[i+1] == '+' or ecu[i+1] == '-'):
                if cad == '+' or cad == '-': cad += "1"
                y += int(cad)                
                #print cad +" = "+str(y)
        else:
            if ecu[i]=='x' or ecu[i]=='X':
                if cad == '+' or cad == '-': cad += "1"
                y += int(cad)* x                
                #print cad + "("+ str(x)+") = "+str(y)
            else:
                if cad == '+' or cad == '-': cad += "1"
                y += int(cad) 
                #print cad +" = "+str(y)
                
        if i == 0 and cad == "": cad = "1"                
          
        i += 1
            
        #print cad
    return y

def drawScene():
   glClearColor(1.0, 1.0, 1.0, 0.0)
   glClear(GL_COLOR_BUFFER_BIT)
   
   glColor3f(0.0, 0.0, 0.0)

   glBegin(GL_LINES)
   glVertex2f(50.0, 0.0)
   glVertex2f(50.0, 100.0)
   glVertex2f(0.0, 50.0)
   glVertex2f(100.0, 50.0)
   glEnd()

   glBegin(GL_LINE_STRIP)
   glColor3f(1.0, 0.0, 0.0)
   for v in rango:
       #print v
       glVertex2f(50.0+v, 50.0+ecuacion(v))

   glEnd() 

   glFlush() 

def resize(w, h):
   glMatrixMode(GL_PROJECTION)

   glLoadIdentity()

   glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0)

   glMatrixMode(GL_MODELVIEW)

   glLoadIdentity()

def main():
   glutInit(sys.argv)
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)   
   glutInitWindowSize(900, 500)
   glutInitWindowPosition(200, 200)    
   glutCreateWindow("PRACTICA 1")   
   glutDisplayFunc(drawScene)
   
   glutReshapeFunc(resize)
   glutMainLoop()

main()
