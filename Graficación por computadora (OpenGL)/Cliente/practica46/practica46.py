from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
from math import *
import sys



width = 0 #valor inicial en x del mouse
height = 0 #valor inicial en y del mouse
size = 10.0 


angulo = 0 #angulo de inclinacion de la linea
radio = 150 #radio de la circunferencia

#coordenadas del centro de la circunferencia
xCentro = 200 
yCentro = 350

#coordenadas del boton angular
xBoton = xCentro
yBoton = yCentro+50

#coordenadas del punto movil de la grafica de funciones
xPunto = 0
yPunto = 0

centroGrafica = 600 #coordenada x del inicio de la grafica

presiona = False #indica si el boton angular ha sido presionado

escalaPI = 80 #se escala el valor de PI en base a las coordenadas reales de la ventana

funcion = 'sen' #funcion que se esta graficando


#funcion que imprime los numeros en la ruleta
def writeBitmapString(font, string):
	for c in string:
		glutBitmapCharacter(font, ord(c))


# funcion que dibuja la circunferencia
def circunferencia(ang):

	global xCentro, yCentro

	x = cos(radians(ang)) * radio + xCentro
	y = sin(radians(ang)) * radio + yCentro

	#se dibujan los angulos de 10 en 10 en la circunferencia

	glPointSize(5)
	glBegin(GL_POINTS)
	glColor3f(1,0,0)
	glVertex2f(x,y)
	glEnd()

	glColor3f(0,0,0)
	glRasterPos2f(x, y)
	writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, str(ang))


#funcion que grafica la funcion del seno, coseno, tangente y cotangente
def grafica(fun):
	
	glBegin(GL_LINE_STRIP)
	
	#inicia de -90 grados hasta 450 grados
	i = -90
	while i <= 450:

		a = radians(i)*escalaPI

		if fun == 'sen':			
			b = sin(radians(i))*escalaPI; rojo=1;verde=0;azul=0
		elif fun == 'cos':
			b = cos(radians(i))*escalaPI; rojo=0;verde=1;azul=0
		elif fun == 'tan':
			b = tan(radians(i))*escalaPI; rojo=0;verde=0;azul=1
		else:
			if i != 0:# or i != 90 or i != 180 or i != 315
				b = 1/tan(radians(i))*escalaPI;rojo=0;verde=1;azul=1

		glColor3f(rojo, verde, azul)

		glVertex2f(a+centroGrafica, b+350)
		i=i+1

	glEnd()



def drawScene():

	global xCentro, yCentro, xBoton, yBoton, funcion

	glClearColor(1,1,1,0)
	glClear(GL_COLOR_BUFFER_BIT)

	glBegin(GL_LINES)
	glColor3f(0,0,0)

	#plano cartesiano
	glVertex2f(50,350)
	glVertex2f(350,350)
	glVertex2f(200,500)
	glVertex2f(200,200)

	#linea del angulo
	glVertex2f(xCentro, yCentro)
	glVertex2f(xBoton, yBoton)

	#lineas de la grafica
	glVertex2f(centroGrafica-escalaPI*pi*.5, 350)
	glVertex2f(width, 350)

	#linea de -90 grados
	glVertex2f(centroGrafica-escalaPI*pi*.5, height)
	glVertex2f(centroGrafica-escalaPI*pi*.5, 0)

	#linea de 0 grados
	glVertex2f(centroGrafica, height)
	glVertex2f(centroGrafica, 0)

	#linea de 90 grados
	glVertex2f(centroGrafica+escalaPI*pi*.5, height)
	glVertex2f(centroGrafica+escalaPI*pi*.5, 0)

	#linea de 180 grados
	glVertex2f(centroGrafica+escalaPI*pi, height)
	glVertex2f(centroGrafica+escalaPI*pi, 0)

	#linea de 270 grados
	glVertex2f(centroGrafica+escalaPI*pi*1.5, height)
	glVertex2f(centroGrafica+escalaPI*pi*1.5, 0)

	#linea de 360 grados
	glVertex2f(centroGrafica+escalaPI*2*pi, height)
	glVertex2f(centroGrafica+escalaPI*2*pi, 0)
	

	glEnd()



	#se manda a llamar a la funcion de circunferencia tantas veces como el total de grados, para graficar cada punto(grado)
	i = 10
	while i <= 360:
		circunferencia(i)
		i = i+10

	#se calculan la distancia de los lados del triangulo que forma en base al punto angular

	a = round(sqrt(pow(350-xBoton,2)+pow(350-yBoton,2)),2)
	b = sqrt(pow(350-xCentro,2)+pow(350-yCentro,2))
	c = round(sqrt(pow(xBoton-xCentro,2)+pow(yBoton-yCentro,2)),2)

	#formula para obtener el angulo del centro
	coss = (pow(b,2)+pow(c,2)-pow(a,2))/(2*b*c)
	angulo = acos((coss))*180/pi

	if yBoton < yCentro:
		angulo = 360 - angulo


	#valores de cada funcion con base al angulo calculado
	angulo = round((angulo),2)
	seno = round(sin(radians(angulo)),2)
	coseno = round(cos(radians(angulo)),2)
	tangente = round(tan(radians(angulo)),2)
	cotg = round(1/tangente,2)
	radianes = round(radians(angulo),2)

	#se grafica el punto angular
	glPointSize(30)
	glBegin(GL_POINTS)
	glColor3f(1,0,0)
	glVertex2f(xBoton, yBoton)
	glEnd()

	grafica(funcion)#se manda a llamar la funcion para graficar

	#se grafica el punto movil de la grafica
	glPointSize(10)
	glBegin(GL_POINTS)
	glColor3f(1,0,0)

	#se muestra el comportamiento del punto movil de la grafica con base al angulo que forma el punto en la circunferencia

	if funcion == 'sen':
		glVertex2f(radians(angulo)*escalaPI+centroGrafica, seno*escalaPI+350)
	if funcion == 'cos':
		glVertex2f(radians(angulo)*escalaPI+centroGrafica, coseno*escalaPI+350)
	if funcion == 'tan':
		glVertex2f(radians(angulo)*escalaPI+centroGrafica, tangente*escalaPI+350)
	if funcion == 'cot':
		glVertex2f(radians(angulo)*escalaPI+centroGrafica, cotg*escalaPI+350)

	glEnd()


	#se muestran en ventana los valores correspondientes

	glColor3f(1,0,0)
	glRasterPos2f(50, 100)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "Seno: Tecla S")
	glColor3f(1,0,0)
	glRasterPos2f(250, 100)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "Coseno: Tecla C")
	glColor3f(1,0,0)
	glRasterPos2f(50, 70)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "Tangente: Tecla T")
	glColor3f(1,0,0)
	glRasterPos2f(250, 70)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "Cotangente: Tecla G")

	glColor3f(0,0,0)
	glRasterPos2f(50, 650)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "Angulo: "+str(angulo))

	glColor3f(0,0,0)
	glRasterPos2f(200, 650)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "Radianes: "+str(radianes))

	glColor3f(0,0,0)
	glRasterPos2f(500, 650)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "SenA: "+str(seno))

	glColor3f(0,0,0)
	glRasterPos2f(500, 630)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "CosA: "+str(coseno))

	glColor3f(0,0,0)
	glRasterPos2f(750, 650)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "TanA: "+str(tangente))

	glColor3f(0,0,0)
	glRasterPos2f(750, 630)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "CotgA: "+str(cotg))

	glColor3f(0,0,0)
	glRasterPos2f(centroGrafica-escalaPI*pi*.5, 335)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "-90 o")

	glColor3f(0,0,0)
	glRasterPos2f(centroGrafica, 335)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "0")

	glColor3f(0,0,0)
	glRasterPos2f(centroGrafica+escalaPI*pi*.5, 335)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "90 o")

	glColor3f(0,0,0)
	glRasterPos2f(centroGrafica+escalaPI*pi, 335)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "180 o")

	glColor3f(0,0,0)
	glRasterPos2f(centroGrafica+escalaPI*pi*1.5, 335)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "270 o")

	glColor3f(0,0,0)
	glRasterPos2f(centroGrafica+escalaPI*pi*2, 335)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "360 o")

	glPointSize(10)
	glBegin(GL_POINTS)
	glVertex2f(centroGrafica, 350 - escalaPI)
	glVertex2f(centroGrafica, 350 + escalaPI)
	glEnd()

	glColor3f(0,0,0)
	glRasterPos2f(centroGrafica-25, 350 - escalaPI)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "-1")

	glColor3f(0,0,0)
	glRasterPos2f(centroGrafica-20, 350 + escalaPI)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "1")

	

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

def mouseControl(button, state, x, y):

	global presiona, xBoton, yBoton

	y = height - y

	#acciones de click del mouse
	#
	#verifica si el boton es presionado dependiendo a las coordenadas del cursor
	if(button == GLUT_LEFT_BUTTON and state == GLUT_DOWN):
		#if(x >= xBoton-15 and x <= xBoton+15 and y >= yBoton-15 and y <= yBoton+15):
		presiona = True

	if(button == GLUT_LEFT_BUTTON and state == GLUT_UP):
		presiona = False

	glutPostRedisplay()
	return

def mouseMotion(x,y):

	global presiona, xBoton, yBoton

	y = height - y

	#Si el boton es presionado se mueve en base al movimiento del mouse

	if presiona == True:
		xBoton = x
		yBoton = y

	glutPostRedisplay()
	return


def keyInput(key, x, y):

	global funcion

	#teclas que activan la funcion a graficar

	if key == 's':
		funcion = 'sen'
	elif key == 'c':
		funcion = 'cos'
	elif key == 't':
		funcion = 'tan'
	elif key == 'g':
		funcion = 'cot'


	glutPostRedisplay()
	return   

def main():

	glutInit(sys.argv)
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
	glutInitWindowSize(1200, 700)
	glutInitWindowPosition(100, 10)
	glutCreateWindow("Practica 02")
	glutDisplayFunc(drawScene)
	glutReshapeFunc(resize)
	glutMotionFunc(mouseMotion)
	glutMouseFunc(mouseControl)
	glutKeyboardFunc(keyInput)
	glutMainLoop()

main()