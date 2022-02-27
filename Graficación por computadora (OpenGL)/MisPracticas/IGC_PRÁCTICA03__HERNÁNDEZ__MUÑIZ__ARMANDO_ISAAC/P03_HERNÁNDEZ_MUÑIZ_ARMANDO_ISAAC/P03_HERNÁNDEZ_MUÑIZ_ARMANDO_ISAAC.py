from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
import sys


angle = 0.0
refreshMills = 30 # 
Retardo = 100

pesoIzq = 0.0 # peso acumulado en el lado izquierdo de la balanza
pesoDer = 0.0 #peso acumulado en el lado derecho de la balanza

width = 0.0 #ancho de la pantalla
height = 0.0 #alto de la pantalla

mouseX= 0.0 #coordenadas del mouse en X
mosueY= 0.0 #coordenadas del mouse en Y


#Coordenadas de los vertices de la recta
x1 = 5.0  
y1 = 25.0
x2 = 65.0
y2 = 25.0

pmx = 35.0
pmy = 25.0


#coordenadas de los objetos con peso
p1x = 70.0
p1y = 15.0
p2x = 80.0
p2y = 15.0
p3x = 90.0
p3y = 15.0

#colores en los nuveles de la recta
r = [0,0,0,0,0,0,0,0,0,0,0]
v = [0,0,0,0,0,0,0,0,0,0,0]
a = [1,1,1,1,1,1,1,1,1,1,1]
# coordenadas en X de los puntos de nivel
dist = [11,17,23,29,41,47,53,59,70,80,90]

ocupado1 = [0,0,0,0,0,0,0,0]
ocupado2 = [0,0,0,0,0,0,0,0]
ocupado3 = [0,0,0,0,0,0,0,0]

#muestra si un objeto esta situado en un nivel
verde = [False, False, False]

pos1 = 0.0
pos2 = 0.0
pos3 = 0.0

pos1_ant = 0.0
pos2_ant = 0.0
pos3_ant = 0.0

ind1=0
ind2=0
ind3=0

peso1=0.0; peso2=0.0; peso3=0.0

izq1 = 0; izq2 = 0 ; izq3 = 0
der1 = 0; der2 = 0 ; der3 = 0



#esta funcion calcula las coordenadas de los puntos de los niveles cada que la recta
#se inclina para que estos no se pierdan de lugaar
def ecuacionRecta(x):
    #
    m = (y2-y1)/(x2-x1)
    y = y1 + m*x - m*x1
    return y


def initGL():
   glClearColor(0.0, 0.0, 0.0, 1.0)


# Esta funcion muestra en tiempo real el movimiento de los objetos a traves del mouse
# y los puntos de colocacion en la recta 

def Timer(value):
    global a, v, p1x, p1y, pos1, pos2, pos3, verde
    

    if (p1x == dist[0]):            
        a[0]=0
        v[0]=1
        verde[0] = True      
        pos1 = dist[0]
        #ind1 = 0
    else:
        a[0]=1
        v[0]=0
        verde[0] = False        
    if (p1x == dist[1]):            
        a[1]=0
        v[1]=1
        verde[0] = True    
        pos1 = dist[1]
    else:
        a[1]=1
        v[1]=0
        verde[0] = True
        
    if (p1x == dist[2]):            
        a[2]=0
        v[2]=1
        verde[0] = True    
        pos1 = dist[2]
    else:
        a[2]=1
        v[2]=0
        verde[0] = True
        
    if (p1x == dist[3]):            
        a[3]=0
        v[3]=1
        verde[0] = True    
        pos1 = dist[3]
    else:
        a[3]=1
        v[3]=0
        verde[0] = True
        
    if (p1x == dist[4]):            
        a[4]=0
        v[4]=1
        verde[0] = True    
        pos1 = dist[4]
    else:
        a[4]=1
        v[4]=0
        verde[0] = True
        
    if (p1x == dist[5]):            
        a[5]=0
        v[5]=1
        verde[0] = True    
        pos1 = dist[5]
    else:
        a[5]=1
        v[5]=0
        verde[0] = True
        
    if (p1x == dist[6]):            
        a[6]=0
        v[6]=1
        verde[0] = True    
        pos1 = dist[6]
    else:
        a[6]=1
        v[6]=0
        verde[0] = True
        
    if (p1x == dist[7]):            
        a[7]=0
        v[7]=1
        verde[0] = True    
        pos1 = dist[7]
    else:
        a[7]=1
        v[7]=0
        verde[0] = True
        
    if (p1x == dist[8]):            
        a[8]=0
        v[8]=1
        verde[0] = True    
        pos1 = dist[8]
    else:
        a[8]=1
        v[8]=0
        verde[0] = True
    if (p1x == dist[9]):            
        a[9]=0
        v[9]=1
        verde[0] = True    
        pos1 = dist[9]
    else:
        a[9]=1
        v[9]=0
        verde[0] = True
    if (p1x == dist[10]):            
        a[10]=0
        v[10]=1
        verde[0] = True    
        pos1 = dist[10]
    else:
        a[10]=1
        v[10]=0
        verde[0] = True

    if (p2x == dist[0]):            
        a[0]=0
        v[0]=1
        verde[1] = True      
        pos2 = dist[0]
    else:
        a[0]=1
        v[0]=0
        verde[1] = True
    if (p2x == dist[1]):            
        a[1]=0
        v[1]=1
        verde[1] = True      
        pos2 = dist[1]
    else:
        a[1]=1
        v[1]=0
        verde[1] = True
    if (p2x == dist[2]):            
        a[2]=0
        v[2]=1
        verde[1] = True      
        pos2 = dist[2]
    else:
        a[2]=1
        v[2]=0
        verde[1] = True
    if (p2x == dist[3]):            
        a[3]=0
        v[3]=1
        verde[1] = True      
        pos2 = dist[3]
    else:
        a[3]=1
        v[3]=0
        verde[1] = True
    if (p2x == dist[4]):            
        a[4]=0
        v[4]=1
        verde[1] = True      
        pos2 = dist[4]
    else:
        a[4]=1
        v[4]=0
        verde[1] = True
    if (p2x == dist[5]):            
        a[5]=0
        v[5]=1
        verde[1] = True      
        pos2 = dist[5]
    else:
        a[5]=1
        v[5]=0
        verde[1] = True
    if (p2x == dist[6]):            
        a[6]=0
        v[6]=1
        verde[1] = True      
        pos2 = dist[6]
    else:
        a[6]=1
        v[6]=0
        verde[1] = True
    if (p2x == dist[7]):            
        a[7]=0
        v[7]=1
        verde[1] = True      
        pos2 = dist[7]
    else:
        a[7]=1
        v[7]=0
        verde[1] = True
    if (p2x == dist[8]):            
        a[8]=0
        v[8]=1
        verde[1] = True      
        pos2 = dist[8]
    else:
        a[8]=1
        v[8]=0
        verde[1] = True
    if (p2x == dist[9]):            
        a[9]=0
        v[9]=1
        verde[1] = True      
        pos2 = dist[9]
    else:
        a[9]=1
        v[9]=0
        verde[1] = True
    if (p2x == dist[10]):            
        a[10]=0
        v[10]=1
        verde[1] = True      
        pos2 = dist[10]
    else:
        a[10]=1
        v[10]=0
        verde[1] = True

    if (p3x == dist[0]):            
        a[0]=0
        v[0]=1
        verde[2] = True      
        pos3 = dist[0]
    else:
        a[0]=1
        v[0]=0
        verde[2] = True
    if (p3x == dist[1]):            
        a[1]=0
        v[1]=1
        verde[2] = True      
        pos3 = dist[1]
    else:
        a[1]=1
        v[1]=0
        verde[2] = True
    if (p3x == dist[2]):            
        a[2]=0
        v[2]=1
        verde[2] = True      
        pos3 = dist[2]
    else:
        a[2]=1
        v[2]=0
        verde[2] = True
    if (p3x == dist[3]):            
        a[3]=0
        v[3]=1
        verde[2] = True      
        pos3 = dist[3]
    else:
        a[3]=1
        v[3]=0
        verde[2] = True
    if (p3x == dist[4]):            
        a[4]=0
        v[4]=1
        verde[2] = True      
        pos3 = dist[4]
    else:
        a[4]=1
        v[4]=0
        verde[2] = True
    if (p3x == dist[5]):            
        a[5]=0
        v[5]=1
        verde[2] = True      
        pos3 = dist[5]
    else:
        a[5]=1
        v[5]=0
        verde[2] = True
    if (p3x == dist[6]):            
        a[6]=0
        v[6]=1
        verde[2] = True      
        pos3 = dist[6]
    else:
        a[6]=1
        v[6]=0
        verde[2] = True
    if (p3x == dist[7]):            
        a[7]=0
        v[7]=1
        verde[2] = True      
        pos3 = dist[7]
    else:
        a[7]=1
        v[7]=0
        verde[2] = True
    if (p3x == dist[8]):            
        a[8]=0
        v[8]=1
        verde[2] = True      
        pos3 = dist[8]
    else:
        a[8]=1
        v[8]=0
        verde[2] = True
    if (p3x == dist[9]):            
        a[9]=0
        v[9]=1
        verde[2] = True      
        pos3 = dist[9]
    else:
        a[9]=1
        v[9]=0
        verde[2] = True
    if (p3x == dist[10]):            
        a[10]=0
        v[10]=1
        verde[2] = True      
        pos3 = dist[10]
    else:
        a[10]=1
        v[10]=0
        verde[2] = True
   
    glutTimerFunc(refreshMills, Timer, 0)



#este timer muestra cuando un objeto es colocado en un nivel de la recta y como esta 
#simula su inclinacion 
def timerPesos(value):
	global y1, y2, p1y, p2y, p3y

    if pesoIzq > pesoDer:
		y1 -= pesoIzq
		y2 += pesoIzq
		if y1 < 10:
			y1 = 10
			y2 = 40

	elif pesoDer > pesoIzq:
		y1 += pesoDer
		y2 -= pesoDer
		if y2 < 10:
			y2 = 10
			y1 = 40
	elif pesoIzq == pesoDer:
		#y1 += 1.0
		if y1 < 25.0 and y2 > 25.0:
			y1 += 1.0
			y2 -= 1.0
		elif y1 > 25.0 and y2 < 25.0:
			y1 -= 1.0
			y2 += 1.0
	if(p1x != 70 and p1x != 80 and p1x != 90):
		p1y = ecuacionRecta(pos1)
	if(p2x != 70 and p2x != 80 and p2x != 90): 
		p2y = ecuacionRecta(pos2)
	if(p3x != 70 and p3x != 80 and p3x != 90): 
		p3y = ecuacionRecta(pos3)

	
	glutPostRedisplay()
	glutTimerFunc(Retardo, timerPesos, 1)

    
 # dibuja los objetos en la pantalla 
def drawScene():
    global ax, ay, bx, by

    
    glClearColor(1.0, 1.0, 1.0, 0.0)
    glClear(GL_COLOR_BUFFER_BIT)


    #Barra de Soporte
    glBegin(GL_TRIANGLES)
    glColor3f(0,0,1)
    glVertex3f(37, 10,0)
    glVertex3f(33, 10,0)
    glVertex3f(35, 25,0)
    glEnd()

    #balanza
    glBegin(GL_LINES)
    glColor3f(0,0,1)
    glVertex2f(x1, y1)
    glVertex2f(x2, y2)
    glEnd()

    #distancias de los puntos de nivel
    glPointSize(5.0)
    glBegin(GL_POINTS)

    glColor3f(r[0],v[0],a[0])
    glVertex2f(dist[0], ecuacionRecta(dist[0]))
    glColor3f(r[1],v[1],a[1])
    glVertex2f(dist[1], ecuacionRecta(dist[1]))
    glColor3f(r[2],v[2],a[2])
    glVertex2f(dist[2], ecuacionRecta(dist[2]))
    glColor3f(r[3],v[3],a[3])
    glVertex2f(dist[3], ecuacionRecta(dist[3]))

    glColor3f(r[4],v[4],a[4])
    glVertex2f(dist[4], ecuacionRecta(dist[4]))
    glColor3f(r[5],v[5],a[5])
    glVertex2f(dist[5], ecuacionRecta(dist[5]))
    glColor3f(r[6],v[6],a[6])
    glVertex2f(dist[6], ecuacionRecta(dist[6]))
    glColor3f(r[7],v[7],a[7])
    glVertex2f(dist[7], ecuacionRecta(dist[7]))

    glColor3f(r[8],v[8],a[8])
    glVertex2f(dist[8], 15)
    glColor3f(r[9],v[9],a[9])
    glVertex2f(dist[9], 15)
    glColor3f(r[10],v[10],a[10])
    glVertex2f(dist[10], 15)
    glEnd()

    #Pesos
    
    glPointSize(50.0)
    glBegin(GL_POINTS)
    glColor3f(1,0,0)
    glVertex2f(p1x, p1y)
    glEnd()
    glColor3f(0.0,0.0,0.0)
    glRasterPos2f(p1x-1, p1y)
    writeBitmapString(GLUT_BITMAP_8_BY_13,"5kg")

    glPointSize(50.0)
    glBegin(GL_POINTS)
    glColor3f(1,0,0)
    glVertex2f(p2x, p2y)
    glEnd()
    glColor3f(0.0,0.0,0.0)
    glRasterPos2f(p2x-1, p2y)
    writeBitmapString(GLUT_BITMAP_8_BY_13,"5kg")

    glPointSize(80.0)
    glBegin(GL_POINTS)
    glColor3f(1,0,0)
    glVertex2f(p3x, p3y)
    glEnd()
    glColor3f(0.0,0.0,0.0)
    glRasterPos2f(p3x-1, p3y)
    writeBitmapString(GLUT_BITMAP_8_BY_13, "10kg")

    glRasterPos2f(5, 95)
    writeBitmapString(GLUT_BITMAP_8_BY_13,"<<DESCRIPCION>>")
    glRasterPos2f(5, 92)
    writeBitmapString(GLUT_BITMAP_8_BY_13,"Simulador de Balance. Se muestra una Balanza de 4 niveles por cada lado.")
    glRasterPos2f(5, 85)
    writeBitmapString(GLUT_BITMAP_8_BY_13,"<<INSTRUCCIONES>>")
    glRasterPos2f(5, 82)
    writeBitmapString(GLUT_BITMAP_8_BY_13," -Mover una pesa con el mouse e introducirla en un punto de la balanza.")
    glRasterPos2f(5, 79)
    writeBitmapString(GLUT_BITMAP_8_BY_13," -No sueltes una pesa en un punto antes de que la balanza deje de moverse.")
    glRasterPos2f(5, 76)
    writeBitmapString(GLUT_BITMAP_8_BY_13," -Si desea quitar una pesa de la balanza, coloquela en su punto original.")
    
    
    glFlush()
    

def writeBitmapString(font, string):
##esta funcion imprime texto en pantalla
   for c in string:
       glutBitmapCharacter(font, ord(c))


mover = 0
suelta = False

# control de agarre de los objetos

def mouseControl(button, state, x, y):
    global p1x, p1y, p2x, p2y, p3x, p3y, mover, suelta, pesoDer, pesoIzq
    global pos1_ant, pos2_ant, pos3_ant, ocupado1, ocupado2, ocupado3
    global izq1, izq2, izq3, der1, der2, der3, peso1, peso2, peso3
   
    x = x/12
    y = (height-y)/5

    # momento en que el objeto es agarrado con un clic    
    if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN
        and x >= p1x-5 and x <= p1x+5
        and y >= p1y-5 and y <= p1y+5):
        mover = 1
        suelta = False
        if pos1 < 30: pesoIzq -= peso1
        elif pos1 > 30: pesoDer -= peso1 

    #momento en que el objeto es soltado en un punto de la balanza        
    if (button == GLUT_LEFT_BUTTON and state == GLUT_UP and mover == 1):
        if(verde[0] == True):
            if(pos1 != 70 and pos1 != 80 and pos1 != 90):
            	p1x = pos1
                p1y = ecuacionRecta(pos1)
                pos1_ant = pos1                
                
                if pos1 == dist[0]:    peso1 = 1.0
                elif pos1 == dist[1] : peso1 = 0.75
                elif pos1 == dist[2] : peso1 = 0.5
                elif pos1 == dist[3] : peso1 = 0.25
                elif pos1 == dist[4] : peso1 = 0.25
                elif pos1 == dist[5] : peso1 = 0.5
                elif pos1 == dist[6] : peso1 = 0.75
                elif pos1 == dist[7] : peso1 = 1.0
                
                if pos1 < 30: pesoIzq += peso1
            	elif pos1 > 30: pesoDer += peso1 



            else:
            	#if pos1_ant == dist[0]:	pesoIzq -= 1.0
            	p1x = pos1
                p1y = 15
        suelta = True

    if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN
        and x >= p2x-5 and x <= p2x+5
        and y >= p2y-5 and y <= p2y+5):
        mover = 2
        suelta = False
        if pos2 < 30: pesoIzq -= peso2
        elif pos2 > 30: pesoDer -= peso2 
        
    if (button == GLUT_LEFT_BUTTON and state == GLUT_UP  and mover == 2):
        if(verde[1] == True):
            if(pos2 != 70 and pos2 != 80 and pos2 != 90):
                p2x = pos2
                p2y = ecuacionRecta(pos2)
                if pos2 == dist[0]: peso2 = 1.0
                elif pos2 == dist[1]: peso2 = 0.75
                elif pos2 == dist[2]: peso2 = 0.5
                elif pos2 == dist[3]: peso2 = 0.25
                elif pos2 == dist[4]: peso2 = 0.25
                elif pos2 == dist[5]: peso2 = 0.5
                elif pos2 == dist[6]: peso2 = 0.75
                elif pos2 == dist[7]: peso2 = 1.0

                if pos2 < 30: pesoIzq += peso2
            	elif pos2 > 30: pesoDer += peso2 

            else:
                p2x = pos2
                p2y = 15
        suelta = True

    if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN
        and x >= p3x-5 and x <= p3x+5
        and y >= p3y-5 and y <= p3y+5):
        mover = 3
        suelta = False
        if pos3 < 30: pesoIzq -= peso3
        elif pos3 > 30: pesoDer -= peso3 
        
    if (button == GLUT_LEFT_BUTTON and state == GLUT_UP  and mover == 3):
        if(verde[2] == True):
            if(pos3 != 70 and pos3 != 80 and pos3 != 90):
                p3x = pos3
                p3y = ecuacionRecta(pos3)
                if pos3 == dist[0]:	  peso3 = 2.0
                elif pos3 == dist[1]: peso3 = 1.5
                elif pos3 == dist[2]: peso3 = 1.0
                elif pos3 == dist[3]: peso3 = 0.5
                elif pos3 == dist[4]: peso3 = 0.5
                elif pos3 == dist[5]: peso3 = 1.0
                elif pos3 == dist[6]: peso3 = 1.5
                elif pos3 == dist[7]: peso3 = 2.0

                if pos3 < 30: pesoIzq += peso3
            	elif pos3 > 30: pesoDer += peso3 

            else:
                p3x = pos3
                p3y = 15
        suelta = True
    
        

    glutPostRedisplay()
    return

def mouseMotion(x, y):
    global width, heigth, p1x, p1y, p2x, p2y, p3x, p3y, suelta, mouseX, mosueY
    global izq1, izq2, izq3, der1, der2, der3, pesoIzq, pesoDer
    mouseX = x/12
    mouseY = (height - y)/5


    # movimiento de los objetos mientras son tomados por el mouse
    if mover == 1: #objeto 1 
        p1x = mouseX
        p1y = mouseY

    if mover == 2: # objeto 2
        p2x = mouseX
        p2y = mouseY
    if mover == 3: # objeto 3
        p3x = mouseX
        p3y = mouseY

    i
    

    glutPostRedisplay()
    return

def resize(w, h):
    global width, height
    glViewport (0, 0, w, h)
    glMatrixMode(GL_PROJECTION)

    glLoadIdentity()

    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0)
    
    glMatrixMode(GL_MODELVIEW)

    width = w
    height = h     

    glLoadIdentity()
    
def main():
    
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)   
    #glutInitDisplayMode(GLUT_DOUBLE)
    glutInitWindowSize(1200, 500)
    glutInitWindowPosition(100, 100)    
    glutCreateWindow("PRACTICA 3 - ARMANDO HERNANDEZ")   
    glutDisplayFunc(drawScene)
    glutReshapeFunc(resize)
    glutMouseFunc(mouseControl) 
    glutMotionFunc(mouseMotion)
    glutTimerFunc(0, Timer, 0)
    glutTimerFunc(Retardo, timerPesos, 0)
    #glutTimerFunc(0, Timer,0)
    initGL()
    glutMainLoop()

main()
