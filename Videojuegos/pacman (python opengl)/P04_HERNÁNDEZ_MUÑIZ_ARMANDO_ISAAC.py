from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
import sys
import random


#instrucciones del juego
print "<<Instrucciones>>"
print "1. El punto grande amarillo es el Pacman y los de colores son los fantasmas"
print "2. Teclas de control: w(arriba), s(abajo), a(izquierda), d(derecha)"
print "3. Al precionar una tecla puede soltarla y el pacman se mueve solo"
print "4. Cada que cuando el pacman llega a una esquina, este se detendra"


#coordenadas iniciales del pacman
pacX = 10
pacY = 10

#coordenadas iniciales de los fantasmas

fan1x = 36
fan1y = 50
fan2x = 62
fan2y = 95
fan3x = 62
fan3y = 5

#direcciones del recorrido del pacman
arriba = False
abajo = False
izquierda = False
derecha = False

retardo = 35 #duracion de los timer

#Coordenadas de los vertices

ver1 = [[10,5,False],[10,10,False],[10,15,False],[10,20,False],[10,25,False],[10,30,False],
        [10,35,False],[10,40,False],[10,45,False],[10,50,False],[10,55,False],[10,60,False],
        [10,65,False],[10,70,False],[10,75,False],[10,80,False],[10,85,False],[10,90,False],[10,95,False]]

ver2 = [[36,5,False],[36,10,False],[36,15,False],[36,20,False],[36,25,False],[36,30,False],
        [36,35,False],[36,40,False],[36,45,False],[36,50,False],[36,55,False],[36,60,False],
        [36,65,False],[36,70,False],[36,75,False],[36,80,False],[36,85,False],[36,90,False],[36,95,False]]

ver3 = [[62,5,False],[62,10,False],[62,15,False],[62,20,False],[62,25,False],[62,30,False],
        [62,35,False],[62,40,False],[62,45,False],[62,50,False],[62,55,False],[62,60,False],
        [62,65,False],[62,70,False],[62,75,False],[62,80,False],[62,85,False],[62,90,False],[62,95,False]]

ver4 = [[88,5,False],[88,10,False],[88,15,False],[88,20,False],[88,25,False],[88,30,False],
        [88,35,False],[88,40,False],[88,45,False],[88,50,False],[88,55,False],[88,60,False],
        [88,65,False],[88,70,False],[88,75,False],[88,80,False],[88,85,False],[88,90,False],[88,95,False]]

hor1 = [[10,5,False],[14,5,False],[18,5,False],[22,5,False],[26,5,False],[30,5,False],
        [34,5,False],[38,5,False],[42,5,False],[46,5,False],[50,5,False],[54,5,False],
        [58,5,False],[62,5,False],[66,5,False],[70,5,False],[74,5,False],[78,5,False],
        [82,5,False],[86,5,False],[88,5,False]]

hor2 = [[10,50,False],[14,50,False],[18,50,False],[22,50,False],[26,50,False],[30,50,False],
        [34,50,False],[38,50,False],[42,50,False],[46,50,False],[50,50,False],[54,50,False],
        [58,50,False],[62,50,False],[66,50,False],[70,50,False],[74,50,False],[78,50,False],
        [82,50,False],[86,50,False],[88,50,False]]

hor3 = [[10,95,False],[14,95,False],[18,95,False],[22,95,False],[26,95,False],[30,95,False],
        [34,95,False],[38,95,False],[42,95,False],[46,95,False],[50,95,False],[54,95,False],
        [58,95,False],[62,95,False],[66,95,False],[70,95,False],[74,95,False],[78,95,False],
        [82,95,False],[86,95,False],[88,95,False]]

numBolas = 139

#direcciones de los fantasmas
#arriba, abajo, izquierda, derecha
dirFan1=[False, True, False, False]
dirFan2=[False, False, True, False]
dirFan3=[True, False, False, False]


esquinas = [[10,5],[10,50],[10,95],[36,5],[36,50],[36,95],[62,5],[62,50],[62,95],
            [88,5],[88,50],[88,95]]


Pierde = False
gana = False


def writeBitmapString(font, string):
##esta funcion imprime texto en pantalla
   for c in string:
       glutBitmapCharacter(font, ord(c))

#funcion que dibuja el escenario del juego del Pacman
def escenario():



   glClearColor(0.0, 0.0, 0.0, 0.0)
   glClear(GL_COLOR_BUFFER_BIT)

   #tablero del pacman
   
   glBegin(GL_QUADS)
   glColor3f(0,0,1)
   
   glVertex2f(0,100)
   glVertex2f(0,55)
   glVertex2f(5,55)
   glVertex2f(5,100)

   glVertex2f(0,45)
   glVertex2f(0,0)
   glVertex2f(5,0)
   glVertex2f(5,45)

   glVertex2f(93,100)
   glVertex2f(93,55)
   glVertex2f(100,55)
   glVertex2f(100,100)

   glVertex2f(93,45)
   glVertex2f(93,0)
   glVertex2f(100,0)
   glVertex2f(100,45)

   glVertex2f(15,90)
   glVertex2f(15,55)
   glVertex2f(31,55)
   glVertex2f(31,90)

   glVertex2f(41,90)
   glVertex2f(41,55)
   glVertex2f(57,55)
   glVertex2f(57,90)

   glVertex2f(67,90)
   glVertex2f(67,55)
   glVertex2f(83,55)
   glVertex2f(83,90)

   glVertex2f(15,45)
   glVertex2f(15,10)
   glVertex2f(31,10)
   glVertex2f(31,45)

   glVertex2f(41,45)
   glVertex2f(41,10)
   glVertex2f(57,10)
   glVertex2f(57,45)

   glVertex2f(67,45)
   glVertex2f(67,10)
   glVertex2f(83,10)
   glVertex2f(83,45)

   glEnd()   


   glPointSize(5)
   glBegin(GL_POINTS)
   glColor3f(1,1,0) 

   #en los siguientes ciclos se dibujas las bolitas amarillas en el laberinto

   i=0
   while i < 19:
      glVertex2f(ver1[i][0], ver1[i][1])
      
      i+=1

   i=0
   while i < 19:
      glVertex2f(ver2[i][0], ver2[i][1])
      
      i+=1

   i=0
   while i < 19:
      glVertex2f(ver3[i][0], ver3[i][1])
      
      i+=1

   i=0
   while i < 19:
      glVertex2f(ver4[i][0], ver4[i][1])
      
      i+=1

   i=0
   while i < 21:
      glVertex2f(hor1[i][0], hor1[i][1])
      
      i+=1

   i=0
   while i < 21:
      glVertex2f(hor2[i][0], hor2[i][1])
      
      i+=1

   i=0
   while i < 21:
      glVertex2f(hor3[i][0], hor3[i][1])
      
      i+=1

   glEnd()



   
   glPointSize(30)
   glBegin(GL_POINTS)
   glColor3f(1,1,0) 
   #PACMAN  
   glVertex2f(pacX, pacY)

   glColor3f(1,0,0)
   glVertex2f(fan1x, fan1y)
   
   glColor3f(1,0,1)
   glVertex2f(fan2x, fan2y)
   
   glColor3f(0,1,1)
   glVertex2f(fan3x, fan3y)

   glEnd()

   glColor3f(1,1,1)
   glRasterPos2f(43, 75)
   writeBitmapString(GLUT_BITMAP_HELVETICA_18,"Score:")
   glRasterPos2f(46, 70)
   writeBitmapString(GLUT_BITMAP_HELVETICA_18, str((138-numBolas)*10))

   if(Pierde == True):
      glColor3f(1,1,1)
      glRasterPos2f(40, 50)
      writeBitmapString(GLUT_BITMAP_HELVETICA_18,"HAS PERDIDO")

   if(numBolas == 0):
      glColor3f(1,1,1)
      glRasterPos2f(40, 50)
      writeBitmapString(GLUT_BITMAP_HELVETICA_18,"HAS GANADO")



   glFlush()



def setup(void):
   glClearColor(1.0, 1.0, 1.0, 0.0)


def resize(w, h):
   glViewport(0, 0, w, h)
  
   glMatrixMode(GL_PROJECTION)

   glLoadIdentity()

   glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0)

   glMatrixMode(GL_MODELVIEW)

   glLoadIdentity()




def keyInput(key, x, y):
   global arriba, abajo, izquierda, derecha, pause

   #Direcciones del pacman con las teclas
   #se enciende una bandera segun su direccion
   if(key == 'w'):
      arriba = True
      abajo = False
      izquierda = False
      derecha = False
   
   if(key == 's'):
      arriba = False
      abajo = True
      izquierda = False
      derecha = False
      
   if(key == 'a'): 
      arriba = False
      abajo = False
      izquierda = True
      derecha = False
         
   if(key == 'd'):
      arriba = False
      abajo = False
      izquierda = False
      derecha = True
      
   
   if(Pierde == False and numBolas > 0): glutPostRedisplay()

enEsquina = False

def timerPacman(value):
   global arriba, abajo, izquierda, derecha, pacX, pacY, enEsquina

   #El pacman se dentendra en cada esquina cada que realice el recorrido

   if(arriba == True):
      if(pacY < 95 and (pacX == 10 or pacX == 36 or pacX == 62 or pacX == 88)):         
         if(pacY==50-1): arriba = False           
         pacY += 1
   if(abajo == True):
      if(pacY > 5 and (pacX == 10 or pacX == 36 or pacX == 62 or pacX == 88)):
         if(pacY==50+1): abajo = False  
         pacY -= 1
   if(izquierda == True):
      if((pacX-5 > 5 or pacY == 50) and (pacY == 5 or pacY == 50 or pacY == 95)):
         if(pacX==10+1 or pacX==36+1 or pacX==62+1 or pacX==88+1): izquierda = False  
         pacX -= 1
         if(pacX < -10):pacX = 110
   if(derecha == True):
      if((pacX+5 < 93 or pacY == 50) and (pacY == 5 or pacY == 50 or pacY == 95)):
         if(pacX==10-1 or pacX==36-1 or pacX==62-1 or pacX==88-1): derecha = False
         pacX += 1
         if(pacX > 110):pacX = -10


   if(Pierde == False and numBolas > 0): glutPostRedisplay();
   glutTimerFunc(retardo, timerPacman, 1)


def timer(value):

   global fan1x, fan1y, fan2x, fan2y, fan3x, fan3y, Pierde, gana, numBolas

   #movimiento del fantasma 1
   #
   if(dirFan1[0]==True and fan1y < 95 and (fan1x == 10 or fan1x == 36 or fan1x == 62 or fan1x == 88)):
      fan1y += 1

   if(dirFan1[1]==True and fan1y > 5 and (fan1x == 10 or fan1x == 36 or fan1x == 62 or fan1x == 88)):
      fan1y -= 1
   
 
   if(dirFan1[2]==True and (fan1x-5 > 5 or fan1y == 50) and (fan1y == 5 or fan1y == 50 or fan1y == 95)):
      fan1x -= 1
      if(fan1x < -10):fan1x = 110
      

   if(dirFan1[3]==True and (fan1x+5 < 93 or fan1y == 50) and (fan1x == 5 or fan1x == 50 or fan1x == 95)):
      fan1x += 1
      if(fan1x > 110):fan1x = -10  

   ##deteccion cuando un fantasma llega a una de las esquinas
   if(fan1x == esquinas[0][0] and fan1y == esquinas[0][1] or
      fan1x == esquinas[1][0] and fan1y == esquinas[1][1] or
      fan1x == esquinas[2][0] and fan1y == esquinas[2][1] or
      fan1x == esquinas[3][0] and fan1y == esquinas[3][1] or
      fan1x == esquinas[4][0] and fan1y == esquinas[4][1] or 
      fan1x == esquinas[5][0] and fan1y == esquinas[5][1] or 
      fan1x == esquinas[6][0] and fan1y == esquinas[6][1] or 
      fan1x == esquinas[7][0] and fan1y == esquinas[7][1] or 
      fan1x == esquinas[8][0] and fan1y == esquinas[8][1] or 
      fan1x == esquinas[9][0] and fan1y == esquinas[9][1] or 
      fan1x == esquinas[10][0] and fan1y == esquinas[10][1] or 
      fan1x == esquinas[11][0] and fan1y == esquinas[11][1]):

      r1 = random.randint(0,3)
      dirFan1[r1] = True;
      i=0
      while i<len(dirFan1):
         if i != r1:
            dirFan1[i]=False
         i+=1

   #movimiento del fantasma 2
   #
   if(dirFan2[0]==True and fan2y < 95 and (fan2x == 10 or fan2x == 36 or fan2x == 62 or fan2x == 88)):
      fan2y += 1

   if(dirFan2[1]==True and fan2y > 5 and (fan2x == 10 or fan2x == 36 or fan2x == 62 or fan2x == 88)):
      fan2y -= 1
   
 
   if(dirFan2[2]==True and (fan2x-5 > 5 or fan2y == 50) and (fan2y == 5 or fan2y == 50 or fan2y == 95)):
      fan2x -= 1
      if(fan2x < -10):fan2x = 110
      

   if(dirFan2[3]==True and (fan2x+5 < 93 or fan2y == 50) and (fan2x == 5 or fan2x == 50 or fan2x == 95)):
      fan2x += 1
      if(fan2x > 110):fan2x = -10  

   ##deteccion cuando un fantasma llega a una de las esquinas
   if(fan2x == esquinas[0][0] and fan2y == esquinas[0][1] or
      fan2x == esquinas[1][0] and fan2y == esquinas[1][1] or
      fan2x == esquinas[2][0] and fan2y == esquinas[2][1] or
      fan2x == esquinas[3][0] and fan2y == esquinas[3][1] or
      fan2x == esquinas[4][0] and fan2y == esquinas[4][1] or 
      fan2x == esquinas[5][0] and fan2y == esquinas[5][1] or 
      fan2x == esquinas[6][0] and fan2y == esquinas[6][1] or 
      fan2x == esquinas[7][0] and fan2y == esquinas[7][1] or 
      fan2x == esquinas[8][0] and fan2y == esquinas[8][1] or 
      fan2x == esquinas[9][0] and fan2y == esquinas[9][1] or 
      fan2x == esquinas[10][0] and fan2y == esquinas[10][1] or 
      fan2x == esquinas[11][0] and fan2y == esquinas[11][1]):

      r2 = random.randint(0,3)
      dirFan2[r2] = True;
      i=0
      while i<len(dirFan2):
         if i != r2:
            dirFan2[i]=False
         i+=1

   #movimiento del fantasma 3
   #
   if(dirFan3[0]==True and fan3y < 95 and (fan3x == 10 or fan3x == 36 or fan3x == 62 or fan3x == 88)):
      fan3y += 1

   if(dirFan3[1]==True and fan3y > 5 and (fan3x == 10 or fan3x == 36 or fan3x == 62 or fan3x == 88)):
      fan3y -= 1
   
 
   if(dirFan3[2]==True and (fan3x-5 > 5 or fan3y == 50) and (fan3y == 5 or fan3y == 50 or fan3y == 95)):
      fan3x -= 1
      if(fan3x < -10):fan3x = 110
      

   if(dirFan3[3]==True and (fan3x+5 < 93 or fan3y == 50) and (fan3x == 5 or fan3x == 50 or fan3x == 95)):
      fan3x += 1
      if(fan3x > 110):fan3x = -10  

   ##deteccion cuando un fantasma llega a una de las esquinas

   if(fan3x == esquinas[0][0] and fan3y == esquinas[0][1] or
      fan3x == esquinas[1][0] and fan3y == esquinas[1][1] or
      fan3x == esquinas[2][0] and fan3y == esquinas[2][1] or
      fan3x == esquinas[3][0] and fan3y == esquinas[3][1] or
      fan3x == esquinas[4][0] and fan3y == esquinas[4][1] or 
      fan3x == esquinas[5][0] and fan3y == esquinas[5][1] or 
      fan3x == esquinas[6][0] and fan3y == esquinas[6][1] or 
      fan3x == esquinas[7][0] and fan3y == esquinas[7][1] or 
      fan3x == esquinas[8][0] and fan3y == esquinas[8][1] or 
      fan3x == esquinas[9][0] and fan3y == esquinas[9][1] or 
      fan3x == esquinas[10][0] and fan3y == esquinas[10][1] or 
      fan3x == esquinas[11][0] and fan3y == esquinas[11][1]):

      r3 = random.randint(0,3)
      dirFan3[r3] = True;
      i=0
      while i<len(dirFan3):
         if i != r3:
            dirFan3[i]=False
         i+=1

   ##se verifica que el pacman pasa por encima de las bolitas amarillas
   ##y una ves detectado estas desapareceran

   i=0
   while i < 19:
      if(ver1[i][0] < pacX+5 and ver1[i][0] > pacX-5 and ver1[i][1] < pacY+5 and ver1[i][1] > pacY-5):
         ver1[i][0]=1000
         numBolas-=1
      i+=1

   i=0
   while i < 19:
      if(ver2[i][0] < pacX+5 and ver2[i][0] > pacX-5 and ver2[i][1] < pacY+5 and ver2[i][1] > pacY-5):
         ver2[i][0]=1000
         numBolas-=1
      i+=1

   i=0
   while i < 19:
      if(ver3[i][0] < pacX+5 and ver3[i][0] > pacX-5 and ver3[i][1] < pacY+5 and ver3[i][1] > pacY-5):
         ver3[i][0]=1000
         numBolas-=1
      i+=1

   i=0
   while i < 19:
      if(ver4[i][0] < pacX+5 and ver4[i][0] > pacX-5 and ver4[i][1] < pacY+5 and ver4[i][1] > pacY-5):
         ver4[i][0]=1000
         numBolas-=1
      i+=1

   i=0
   while i < 21:
      if(hor1[i][0] < pacX+5 and hor1[i][0] > pacX-5 and hor1[i][1] < pacY+5 and hor1[i][1] > pacY-5):
         hor1[i][0]=1000
         numBolas-=1
      i+=1

   i=0
   while i < 21:
      if(hor2[i][0] < pacX+5 and hor2[i][0] > pacX-5 and hor2[i][1] < pacY+5 and hor2[i][1] > pacY-5):
         hor2[i][0]=1000
         numBolas-=1
      i+=1

   i=0
   while i < 21:
      if(hor3[i][0] < pacX+5 and hor3[i][0] > pacX-5 and hor3[i][1] < pacY+5 and hor3[i][1] > pacY-5):
         hor3[i][0]=1000
         numBolas-=1
      i+=1


   #print numBolas

   #choque de alguno de los fantasmas con el pacman
   
   #cheques con el fantasma rojo
   
   if(fan1x == pacX):
      if(fan1y > pacY):
         if(fan1y-2 <= pacY+2): Pierde = True
      else:
         if(fan1y+2 >= pacY-2): Pierde = True
   if(fan1y == pacY):
      if(fan1x > pacX):
         if(fan1x-2 <= pacX+2): Pierde = True
      else:
         if(fan1x+2 >= pacX-2): Pierde = True

   #cheques con el fantasma morado

   if(fan2x == pacX):
      if(fan2y > pacY):
         if(fan2y-2 <= pacY+2): Pierde = True
      else:
         if(fan2y+2 >= pacY-2): Pierde = True
   if(fan2y == pacY):
      if(fan2x > pacX):
         if(fan2x-2 <= pacX+2): Pierde = True
      else:
         if(fan2x+2 >= pacX-2): Pierde = True

   #cheques con el fantasma celeste

   if(fan3x == pacX):
      if(fan3y > pacY):
         if(fan3y-2 <= pacY+2): Pierde = True
      else:
         if(fan3y+2 >= pacY-2): Pierde = True
   if(fan3y == pacY):
      if(fan3x > pacX):
         if(fan3x-2 <= pacX+2): Pierde = True
      else:
         if(fan3x+2 >= pacX-2): Pierde = True
   

   #si se acaban las bolas amarillas termina el juego y gana
   if(numBolas == 0): gana = True

   glutPostRedisplay()
   
   if(Pierde == False and numBolas > 0):
      glutTimerFunc(retardo, timer, 1)

   

def main(): 
   glutInit(sys.argv)
 
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
   
   glutInitWindowSize(500, 500)

   glutInitWindowPosition(30,30)
   
   glutCreateWindow("practica 4.cpp")

   glutDisplayFunc(escenario)
   
   glutReshapeFunc(resize)

   glutKeyboardFunc(keyInput)
   glutTimerFunc(retardo, timer, 1)
   glutTimerFunc(retardo, timerPacman, 1)
   
   glutMainLoop()

main()
