from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
from math import *
from random import *
import sys

width = 0.0 #ancho de la pantalla
height = 0.0 #alto de la pantalla

retardo1 = 100 #tiempo que tarda en ejecutar la funcion juego()
retardo2 = 5000 #tiempo que tarda en ejecutar la funcion timer()

pantalla = 1 #define el numero de pantalla del juego (1-3)

FAST = False #nivel rapido desactivado
SLOW = False #nivel lento desactivado

SCORE = 0 #valor del score
HITS = 0 #numero de clics en pantalla
MISS = 0 #numero de errores

posicionFiguras = [range (8) for i in range(10)] #es una matriz que cada fila representa una figura
#esta tiene 10 filas que representan la cantidad de figuras y 8 columnas que representan sus caracteristicas.
#Valor de las Columnas:
#[0] = coordenada X
#[1] = coordenada Y
#[2] = numero de figura (0 = circulo, 1 = triangulo, 2 = cuadrado, 3 = rectangulo)
#[3] = nivel de rojo
#[4] = nivel de verde
#[5] = nivel de azul
#[6] = numero de direccionamiento (1-4)
#[7] = activo o desactivo (1-0)



radio = 40 # distancia entre el centro y el perimetro de cada figura
rojo = 1; verde = 1; azul = 1 #se definen los colores para las figuras
turnoFigura = '' #cambio de figura a cliquear
desactivas = 0 # cantidad de figuras desactivadas al dar clic

#funcion que imprime los numeros en la ruleta
def writeBitmapString(font, string):
	for c in string:
		glutBitmapCharacter(font, ord(c))


def menu():

	glColor3f(1,0,0)
	glRasterPos2f(350, 500)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "SHAPES SPLAT")

	#botones de menu
	glPointSize(100)
	glBegin(GL_POINTS)
	
	glColor3f(0,0,1)
	#boton FAST
	glVertex(300,300)

	glColor3f(0,1,0)
	#boton SLOW
	glVertex(500,300)

	glEnd()

	glColor3f(1,1,1)
	glRasterPos2f(290, 300)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "FAST") #nivel rapido
	glRasterPos2f(490, 300)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "SLOW") #nivel lento


#funcion que define los colores aleatorios para cada figura
def color():
	global rojo, verde, azul
	rojo = 1; verde = 1; azul = 1
	while (rojo==1 and verde==1 and azul==1):
		rojo = randint(0,1)
		verde = randint(0,1)
		azul = randint(0,1)

#funcion ue define que fugura se va a dibujar
def figura(shape):
	global radio

	glBegin(GL_POLYGON)

	glColor3f(shape[3], shape[4], shape[5])

	if shape[2] == 0: #circulo		
		for i in range(361):
			x = cos(radians(i))*radio + shape[0]
			y = sin(radians(i))*radio + shape[1]
			glVertex2f(x, y)

	elif shape[2] == 1: #triangulo
		glVertex2f(shape[0], shape[1]+radio)
		glVertex2f(shape[0]-radio, shape[1]-radio)
		glVertex2f(shape[0]+radio, shape[1]-radio)

	elif shape[2] == 2: #cuadrado
		glVertex2f(shape[0]-radio, shape[1]+radio)
		glVertex2f(shape[0]+radio, shape[1]+radio)
		glVertex2f(shape[0]+radio, shape[1]-radio)
		glVertex2f(shape[0]-radio, shape[1]-radio)

	elif shape[2] == 3: #rectangulo
		glVertex2f(shape[0]-radio, shape[1]+radio*2)
		glVertex2f(shape[0]+radio, shape[1]+radio*2)
		glVertex2f(shape[0]+radio, shape[1]-radio*2)
		glVertex2f(shape[0]-radio, shape[1]-radio*2)

	glEnd()


acum = 0 #velocidad en las que se mueven las figuras segun el nivel

#funcion que trabaja el movimiento dinamico de las figuras y la direccion en que se mueven en pantalla
def juego(value):
	global posicionFiguras, acum

	for i in range(10):
		if posicionFiguras[i][7] == 1: # siempre y cuando la figura este activa
			
			if posicionFiguras[i][6] == 1:#direccion 1
				posicionFiguras[i][0] = posicionFiguras[i][0] - acum
				posicionFiguras[i][1] = posicionFiguras[i][1] + acum
				if posicionFiguras[i][0] <= 0 or posicionFiguras[i][1] >= 650:
					while posicionFiguras[i][6] == 1:
						posicionFiguras[i][6] = randint(1,4)

			if posicionFiguras[i][6] == 2:#direccion 2
				posicionFiguras[i][0] = posicionFiguras[i][0] + acum
				posicionFiguras[i][1] = posicionFiguras[i][1] + acum
				if posicionFiguras[i][0] >= 800 or posicionFiguras[i][1] >= 650:
					while posicionFiguras[i][6] == 2:
						posicionFiguras[i][6] = randint(1,4)

			if posicionFiguras[i][6] == 3: #direccion 3
				posicionFiguras[i][0] = posicionFiguras[i][0] - acum
				posicionFiguras[i][1] = posicionFiguras[i][1] - acum
				if posicionFiguras[i][0] <= 0 or posicionFiguras[i][1] <= 0:
					while posicionFiguras[i][6] == 3:
						posicionFiguras[i][6] = randint(1,4)

			if posicionFiguras[i][6] == 4: #direccion 4
				posicionFiguras[i][0] = posicionFiguras[i][0] + acum
				posicionFiguras[i][1] = posicionFiguras[i][1] - acum
				if posicionFiguras[i][0] >= 800 or posicionFiguras[i][1] <= 0:
					while posicionFiguras[i][6] == 4:
						posicionFiguras[i][6] = randint(1,4)

	glutPostRedisplay()
	glutTimerFunc(retardo1,juego, 1)


#funcion que cambia cada 3 segundos las direcciones de cada figura
def timer(value):
	global posicionFiguras

	for i in range(10):
		posicionFiguras[i][6] = randint(1,4)
		
	
	glutPostRedisplay()
	glutTimerFunc(retardo2,timer, 1)


#funcion que dibuja el escenario del juego
def drawScene():

	global pantalla, posicionFiguras, rojo, verde, azul, turnoFigura, HITS, SCORE, MISS

	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT)

	#interfaz de la primera pantalla
	if pantalla == 1: 
		menu() # se muestra el menu

		#se definen los valores de las figuras
		for i in range(10):
			posicionFiguras[i][0] = randint(50,750)
			posicionFiguras[i][1] = randint(50,600)
			fig = randint(0,3)			
			posicionFiguras[i][2] = fig
			color()
			posicionFiguras[i][3] = rojo
			posicionFiguras[i][4] = verde
			posicionFiguras[i][5] = azul
			posicionFiguras[i][6] = randint(1,4) #direccion inicial
			posicionFiguras[i][7] = 1

		#se define la primera figura que se debe cliquear
		turnoFigura = posicionFiguras[randint(0,9)][2]

	elif pantalla == 2: #interfaz de la segunda pantalla

		#se grafican las figuras
		for i in range(10):

			figura(posicionFiguras[i])
		

		#se muestran los datos del juego
		glColor3f(0,0,0)
		glRasterPos2f(650, 100)
		writeBitmapString(GLUT_BITMAP_8_BY_13, "SCORE: "+str(SCORE))
		glRasterPos2f(650, 70)
		writeBitmapString(GLUT_BITMAP_8_BY_13, "HITS: "+str(HITS))
		glRasterPos2f(650, 40)
		writeBitmapString(GLUT_BITMAP_8_BY_13, "MISS: "+str(MISS))

		nombre = ''

		#se define el nombre de la figura de acuerdo al numero

		if turnoFigura == 0: nombre = 'CIRCULO'
		if turnoFigura == 1: nombre = 'TRIANGULO'
		if turnoFigura == 2: nombre = 'CUADRADO'
		if turnoFigura == 3: nombre = 'RECTANGULO'

		glRasterPos2f(20, 40)
		writeBitmapString(GLUT_BITMAP_8_BY_13, 'SHAPE: '+nombre)

	elif pantalla == 3: # interfaz de la pantalla 3
		glColor3f(1,0,0)
		glRasterPos2f(350, 500)
		writeBitmapString(GLUT_BITMAP_8_BY_13, "SCORE: " + str(SCORE))

		glPointSize(100)
		glBegin(GL_POINTS)
		glColor3f(0,0,0)
		glVertex2f(400,300)
		glEnd()

		glColor3f(1,1,1)
		glRasterPos2f(360, 300)
		writeBitmapString(GLUT_BITMAP_8_BY_13, "PLAY AGAIN")

	glFlush()
	


#funcion que lleva a cabo las acciones con el mouse
def mouseControl(button, state, x, y):
	global height, FAST, SLOW, pantalla, turnoFigura, posicionFiguras, desactivas, HITS, SCORE, MISS, acum

	y = height - y

	nueva = turnoFigura
	correcto = False # se determina si cliqueo la figura correcta

	if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN):
		
		if pantalla == 1: # acciones de la pantalla 1
			if  x > 250 and x < 350 and y > 250 and y < 350:
				FAST = True; pantalla = 2; acum = 12 # se define el nivel rapido y la velocidad
			if  x > 450 and x < 550 and y > 250 and y < 350:
				SLOW = True; pantalla = 2; acum = 2 # se define el nivel lento y la velocidad

		elif pantalla == 2: # acciones de la pantalla 2

			j = 0
	
			for i in range(10):
				#se verifica que se toca cualquier figura
				if x > posicionFiguras[i][0]-radio and x < posicionFiguras[i][0]+radio and \
					y > posicionFiguras[i][1]-radio and y < posicionFiguras[i][1]+radio:

					#acciones al cliquear la figura correcta
					if turnoFigura == posicionFiguras[i][2]:
						posicionFiguras[i][1] = 1000
						posicionFiguras[i][7] = 0
						desactivas = desactivas + 1
						SCORE = SCORE + 1
						correcto = True
						j = i
						break
					else: # acciones al cliquear la figura incorrecta
						if SCORE > 0: SCORE = SCORE - 1
						MISS = MISS + 1
						break
			
			if desactivas == 10: # si se terminan las figuras pasa a la pantalla 3
				pantalla = 3

			if correcto == True:#si la figura es correcta se cambia la figura
				i = 0
				while i < 10:
					if posicionFiguras[i][7] == 1:
						turnoFigura = posicionFiguras[i][2]
					i = i + 1
					if i > 9: break

			HITS = HITS + 1

		elif pantalla == 3: #acciones de la pantalla 3
			if x > 350 and x < 450 and y > 250 and y < 350: # se cliquea el boton
				# se ponen los valores de inicio de juego
				pantalla = 1
				SCORE = 0
				HITS = 0
				MISS = 0
				desactivas = 0

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

def main():

	print '<< PROYECTO GRUPAL 1. INTRODUCCION A LA GRAFICACION POR COMPUTADORA >>\
	\nINTEGRANTES:\
	\n -MIKE\
	\n -ALEJANDRA\
	\n -?\
	\n<< INSTRUCCIONES >>\
	\n1. LA PRIMERA PANTALLA ES EL MENU PARA ELEGIR EL NIVEL DEL JUEGO: FAST(RAPIDO) O SLOW(LENTO)\
	\n2. LA SEGUNDA PANTALLA MUESTRA EL JUEGO CON EL MOVIMIENTO DE LAS FIGURAS\
	\n3. LA TERCERA PANTALLA MUESTRA LOS RESULTADOS DEL JUEGO\
	\n4. EL JUEGO COMPRENDE EN SELECCIONAR LAS FIGURAS SEGUN EL NOMBRE QUE SE MUESTRA EN PANTALLA\
	\n5. EL SCORE INCREMENTA CADA VEZ QUE SELECCIONA LA FIGURA CORRECTA Y DECREMENTA CUANDO ES INCORRECTA\
	\n6. HITS MUESTRA EL NUMERO DE CLICS QUE SE HACEN EN PANTALLA\
	\n7. MISS MUESTRA EN NUMERO DE EQUIVOCACIONES'

	glutInit(sys.argv)
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
	glutInitWindowSize(800, 650)
	glutInitWindowPosition(10, 10)
	glutCreateWindow("Practica 02")
	glutDisplayFunc(drawScene)
	glutReshapeFunc(resize)
	glutMouseFunc(mouseControl)
	glutTimerFunc(retardo1,juego, 1);
	glutTimerFunc(retardo2,timer, 1);
	glutMainLoop()

main()
