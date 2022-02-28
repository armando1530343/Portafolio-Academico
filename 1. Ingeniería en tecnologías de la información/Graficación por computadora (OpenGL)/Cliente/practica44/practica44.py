from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
from math import *
import sys
#coordenadas del punto que rodea la circunferencia
puntoCirculoX = 300
puntoCirculoY = 300
#coordenadas del punto que recorre el eje X de la grafica
puntoGraficaX = 400
puntoGraficaY = 300
#coordenadas del punto que indica el valor del angulo el cual se mueve con el mouse
puntoAnguloX = 30.0
puntoAnguloY = 550.0
#coordenadas del punto que recorre la funcion del seno en la grafica
puntoSenX = -10
puntoSenY = -10
#coordenadas del punto que indica la funcion del seno en la circunferencia
puntoSen2X = -10
puntoSen2Y = -10
#coordenadas del punto que recorre la funcion del coseno en la grafica
puntoCosX = -10
puntoCosY = -10
#coordenadas de los puntos que indican la funcion del coseno en la circunferencia
puntoCos2X = -10
puntoCos2Y = -10
puntoCos3X = -10
puntoCos3Y = -10
#coordenadas del punto que recorre la funcion de la tangente en la grafica
puntoTgX = -10
puntoTgY = -10
#coordenadas de los puntos que indican la funcion de la tangente en la circunferencia
puntoTg2X = -10
puntoTg2Y = -10
puntoTg3X = -10
puntoTg3Y = -10
#coordenadas del punto que recorre la funcion del valor de X en la grafica
puntoxX = -10
puntoxY = -10
#coordenadas del punto que recorre la funcion del valor de la ecuacion en la grafica
puntoEcuX = -10
puntoEcuY = -10
#coordenadas del centro de la circunferencia
centroX = 350
centroY = 300

PIx2 = 800 # valor de 2PI escalado (PI = 400)
valorX = 0 #valor de x (valor en radianes del angulo)
RADIO = PIx2/(pi*2) # Valor del radio = 1 con respecto a la escala de PI

puntoAngulo = False #define si el boton del angulo es precionado

inicioGrafica = 0 #coordenada en X del inicio de la grafica

angulo = 1 #valor del angulo obtenido

height = 0
width = 0

#colores de los botones oprimidos (identifican que funcion esta activa para graficarla)
color1 = 0; color2 = 0; color3 = 0; color4 = 0; color5 = 0

#funcion que dibuja la circunferencia
def circulo():
	global RADIO
	glBegin(GL_LINE_STRIP)
	glColor3f(0,0,0)	
	for i in range(361):
		x = sin(radians(i)) * RADIO + centroX
		y = cos(radians(i)) * RADIO + centroY

		glVertex2f(x, y)

	glEnd()

#funcion que imprime los numeros en la ruleta
def writeBitmapString(font, string):
	for c in string:
		glutBitmapCharacter(font, ord(c))


#funcion que grafica las funciones activas con los botones
def graficaFunciones():

	global color1, color2, color3, color4, color5, PIx2, inicioGrafica

	if color1 == 1: # se grafica la funcion del seno
		glBegin(GL_LINE_STRIP)
		glColor3f(1,0,0)
		for i in range(361):
			x = (PIx2/(pi*2)) * radians(i)
			y = (PIx2/(pi*2)) * sin(radians(i))
			glVertex2f(x+inicioGrafica, y+300)

		glEnd()

	if color2 == 1:#se grafica la funcion del coseno
		glBegin(GL_LINE_STRIP)
		glColor3f(0,0,1)
		for i in range(361):
			x = (PIx2/(pi*2)) * radians(i)
			y = (PIx2/(pi*2)) * cos(radians(i))
			glVertex2f(x+inicioGrafica, y+300)

		glEnd()

	if color3 == 1:#se grafica la funcion de la tangente
		glBegin(GL_LINE_STRIP)
		glColor3f(0,1,0)
		for i in range(361):
			x = (PIx2/(pi*2)) * radians(i)
			y = (PIx2/(pi*2)) * tan(radians(i))
			glVertex2f(x+inicioGrafica, y+300)

		glEnd()

	if color4 == 1: #se grafica el valor de X
		glBegin(GL_LINE_STRIP)
		glColor3f(1,.8,0)
		for i in range(361):
			x = (PIx2/(pi*2)) * radians(i)
			y = (PIx2/(pi*2)) * radians(i)
			glVertex2f(x+inicioGrafica, y+300)

		glEnd()

	if color5 == 1:# se grafica la ecuacion
		glBegin(GL_LINE_STRIP)
		glColor3f(1,0,1)
		for i in range(361):
			x = (PIx2/(pi*2)) * radians(i)
			y = (PIx2/(pi*2)) - (x*x)/((PIx2/(pi*2))*2)
			glVertex2f(x+inicioGrafica, y+300)

		glEnd()

	glutPostRedisplay()
	return


#funcion que grafica el escenario
def drawScene():
	global puntoCirculoX, puntoCirculoY, puntoGraficaX, puntoGraficaY, \
			puntoAnguloX, puntoAnguloY, angulo, RADIO, centroX, centroY, PIx2,\
			color1, color2, color3, color4, color5, valorX, inicioGrafica,\
			puntoSenX, puntoSenY, puntoSen2X, puntoSen2Y,\
			puntoCosX, puntoCosY, puntoCos2X, puntoCos2Y, puntoCos3X, puntoCos3Y,\
			puntoTgX, puntoTgY, puntoTg2X, puntoTg2Y, puntoTg3X, puntoTg3Y,\
			puntoxX, puntoxY, puntoEcuX, puntoEcuY

	glClearColor(1,1,1,0)
	glClear(GL_COLOR_BUFFER_BIT)

	glBegin(GL_LINES)
	glColor3f(1,0,0)
	#linea que divide al menu de lo grafico
	glVertex2f(200,600)
	glVertex2f(200,0)

	inicioGrafica = centroX+RADIO

	glColor3f(0,0,0)
	#eje Y de la circunferencia
	glVertex2f(centroX,centroY+RADIO)
	glVertex2f(centroX,centroY-RADIO)
	#eje X
	glVertex2f(200,300)
	glVertex2f(inicioGrafica+800,300)
	#eje Y de la Grafica
	glVertex2f(inicioGrafica,600)
	glVertex2f(inicioGrafica,0)
	#linea del centro de la circunferencia al punto del angulo
	glVertex2f(centroX, centroY)
	glVertex2f(puntoCirculoX, puntoCirculoY)

	#representa la linea de modificacion del angulo
	glVertex2f(20, 550)
	glVertex2f(180, 550)

	glEnd()

	circulo() # se grafica la circunferencia

	glPointSize(20)
	glBegin(GL_POINTS)
	glColor3f(0,0,0)
	glVertex2f(puntoAnguloX, puntoAnguloY) #punto del angulo que se mueve en la linea con el mouse
	glEnd()

	
	angulo2 = 90 - angulo
	valorX = radians(angulo) #valor del angulo en radianes

	#se calcula las coordenadas del punto que recorre la circunferencia con respecto al angulo
	puntoCirculoX = sin(radians(angulo2))*RADIO + centroX
	puntoCirculoY = cos(radians(angulo2))*RADIO + centroY
	#se calcula las coordenadas del punto que recorre el eje X de la grafica con respecto al angulo
	puntoGraficaX = (PIx2/(pi*2)) * radians(angulo) + inicioGrafica



	glPointSize(10)
	glBegin(GL_POINTS)
	glColor3f(0,0,0)
	glVertex2f(centroX, centroY) #punto central de la circunferencia
	glVertex2f(puntoCirculoX, puntoCirculoY) #representa al punto de la circunferencia
	glVertex2f(puntoGraficaX, puntoGraficaY) #representa al punto de la grafica
	glEnd()

	glPointSize(5)
	glBegin(GL_POINTS) # puntos que representan la division del eje X de la grafica
	glColor3f(0,0,0)
	glVertex2f(inicioGrafica+200, 300)
	glVertex2f(inicioGrafica+400, 300)
	glVertex2f(inicioGrafica+600, 300)
	glVertex2f(inicioGrafica+800, 300)
	glEnd()

	#linea curva de color verde que se grafica dentro de la circunferencia que muestra el angulo que se forma
	glBegin(GL_LINE_STRIP)
	glColor3f(0,1,0)
	for i in range(angulo+1):
		x = sin(radians(90-i))*40 + centroX
		y = cos(radians(90-i))*40 + centroY
		glVertex2f(x, y)

	glEnd()

	#botones	
	glBegin(GL_QUADS)
	#boton sen(x)
	glColor3f(color1, 0,0)
	glVertex2f(20, 500)
	glVertex2f(20, 470)
	glVertex2f(150, 470)
	glVertex2f(150, 500)
	#boton cos(x)
	glColor3f(color2, 0,0)
	glVertex2f(20, 450)
	glVertex2f(20, 420)
	glVertex2f(150, 420)
	glVertex2f(150, 450)
	#boton Tg(x)
	glColor3f(color3, 0,0)
	glVertex2f(20, 400)
	glVertex2f(20, 370)
	glVertex2f(150, 370)
	glVertex2f(150, 400)
	#boton (x)
	glColor3f(color4, 0,0)
	glVertex2f(20, 350)
	glVertex2f(20, 320)
	glVertex2f(150, 320)
	glVertex2f(150, 350)
	#boton ecuacion
	glColor3f(color5, 0,0)
	glVertex2f(20, 300)
	glVertex2f(20, 270)
	glVertex2f(150, 270)
	glVertex2f(150, 300)

	glEnd()


	glColor3f(0,0,0)
	glRasterPos2f(puntoAnguloX, puntoAnguloY+30)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "a = "+ str(angulo))
	glRasterPos2f(40, puntoAnguloY-30)
	writeBitmapString(GLUT_BITMAP_8_BY_13, "x = "+ str(valorX))
	glRasterPos2f(inicioGrafica+200, 280)
	writeBitmapString(GLUT_BITMAP_8_BY_13, 'PI/2')
	glRasterPos2f(inicioGrafica+400, 280)
	writeBitmapString(GLUT_BITMAP_8_BY_13, 'PI')
	glRasterPos2f(inicioGrafica+600, 280)
	writeBitmapString(GLUT_BITMAP_8_BY_13, '3/2 PI')
	glRasterPos2f(inicioGrafica+790, 280)
	writeBitmapString(GLUT_BITMAP_8_BY_13, '2 PI')

	glColor3f(1,1,1)
	glRasterPos2f(40, 480)
	writeBitmapString(GLUT_BITMAP_8_BY_13, 'Sen(x)')
	glRasterPos2f(40, 430)
	writeBitmapString(GLUT_BITMAP_8_BY_13, 'Cos(x)')
	glRasterPos2f(40, 380)
	writeBitmapString(GLUT_BITMAP_8_BY_13, 'Tg(x)')
	glRasterPos2f(40, 330)
	writeBitmapString(GLUT_BITMAP_8_BY_13, '(x)')
	glRasterPos2f(40, 280)
	writeBitmapString(GLUT_BITMAP_8_BY_13, '1-(x*x)/2')

	glPointSize(10)
	glBegin(GL_POINTS)

	#se grafican los puntos dentro de la grafica con respecto a la funcion que es activada	
	if color1 == 1:
		glColor3f(1,0,0)
		puntoSenX = (PIx2/(pi*2)) * valorX + inicioGrafica
		puntoSenY = (PIx2/(pi*2)) * sin(valorX) + 300
		puntoSen2X = puntoCirculoX
		puntoSen2Y = centroY
		glVertex2f(puntoSenX, puntoSenY)
		glVertex2f(puntoSen2X, puntoSen2Y)
	if color2 == 1:
		glColor3f(0,0,1)
		puntoCosX = (PIx2/(pi*2)) * valorX + inicioGrafica
		puntoCosY = (PIx2/(pi*2)) * cos(valorX) + 300
		puntoCos2X = centroX
		puntoCos2Y = puntoCosY
		puntoCos3X = puntoCirculoX
		puntoCos3Y = centroY
		glVertex2f(puntoCosX, puntoCosY)
		glVertex2f(puntoCos2X, puntoCos2Y)
		glVertex2f(puntoCos3X, puntoCos3Y)
	if color3 == 1:
		glColor3f(0,1,0)
		puntoTgX = (PIx2/(pi*2)) * valorX + inicioGrafica
		puntoTgY = (PIx2/(pi*2)) * tan(valorX) + 300
		puntoTg2X = inicioGrafica
		puntoTg2Y = puntoTgY
		puntoTg3X = inicioGrafica
		puntoTg3Y = centroY
		glVertex2f(puntoTgX, puntoTgY)
		glVertex2f(puntoTg2X, puntoTg2Y)
		glVertex2f(puntoTg3X, puntoTg3Y)
	if color4 == 1:
		glColor3f(1,.8,0)
		puntoxX = (PIx2/(pi*2)) * valorX + inicioGrafica
		puntoxY = (PIx2/(pi*2)) * valorX + 300
		glVertex2f(puntoxX, puntoxY)
	if color5 == 1:
		glColor3f(1,0,1)
		puntoEcuX = (PIx2/(pi*2)) * valorX
		puntoEcuY = (PIx2/(pi*2)) - (puntoEcuX*puntoEcuX)/((PIx2/(pi*2))*2)
		glVertex2f(puntoEcuX+inicioGrafica, puntoEcuY + 300)

	glEnd()

	#se grafican las lineas que unen los pnutos dentro de la grafica con respecto a la funcion que es activada
	glBegin(GL_LINES)	
	if color1 == 1:
		glColor3f(1,0,0)
		glVertex2f(puntoCirculoX, puntoCirculoY)
		glVertex2f(puntoSen2X, puntoSen2Y)
		glVertex2f(puntoSenX, puntoSenY)
		glVertex2f(puntoCirculoX, puntoCirculoY)
		glVertex2f(puntoSenX, puntoSenY)
		glVertex2f(puntoGraficaX, puntoGraficaY)
	if color2 == 1:
		glColor3f(0,0,1)
		glVertex2f(centroX, centroY)
		glVertex2f(puntoCos2X, puntoCos2Y)
		glVertex2f(centroX, centroY)
		glVertex2f(puntoCos3X, puntoCos3Y)
		glVertex2f(puntoCirculoX, puntoCirculoY)
		glVertex2f(puntoCos3X, puntoCos3Y)
		glVertex2f(puntoCosX, puntoCosY)
		glVertex2f(puntoCos2X, puntoCos2Y)
		glVertex2f(puntoCosX, puntoCosY)
		glVertex2f(puntoGraficaX, puntoGraficaY)
	if color3 == 1:
		glColor3f(0,1,0)
		glVertex2f(puntoTgX, puntoTgY)
		glVertex2f(puntoGraficaX, puntoGraficaY)
		glVertex2f(puntoTgX, puntoTgY)
		glVertex2f(puntoTg2X, puntoTg2Y)
		glVertex2f(puntoTg2X, puntoTg2Y)
		glVertex2f(puntoTg3X, puntoTg3Y)
		glColor3f(0,0,0)
		glVertex2f(puntoTg2X, puntoTg2Y)
		glVertex2f(puntoCirculoX, puntoCirculoY)
	if color4 == 1:
		glColor3f(1,.8,0)
		glVertex2f(puntoxX, puntoxY)
		glVertex2f(puntoGraficaX, puntoGraficaY)
	if color5 == 1:
		glColor3f(1,0,1)
		glVertex2f(puntoEcuX + inicioGrafica, puntoEcuY + 300)
		glVertex2f(puntoGraficaX, puntoGraficaY)
		

	glEnd()

	if color2 == 1:
		#se grafica la curva que se forma en la circunferencia de acuerdo a la funcion del coseno
		menor = 0; mayor = 90	
		if angulo > 90 and angulo < 270:
			menor = 180; mayor = 270

		radio2 = puntoCos2Y-centroY
		if radio2 < 0: radio2 = -radio2

		glBegin(GL_LINE_STRIP)
		glColor3f(0,0,1)
		for i in range(menor, mayor):
			x = sin(radians(90-i))*radio2 + centroX
			y = cos(radians(90-i))*radio2 + centroY
			glVertex2f(x, y)
		glEnd()

	if color4 == 1:
		#se grafica la curva que se forma en la circunferencia de acuerdo a la funcion de X
		glBegin(GL_LINE_STRIP)
		glColor3f(1,.8,0)
		for i in range(angulo+1):
			x = sin(radians(90-i))*RADIO + centroX
			y = cos(radians(90-i))*RADIO + centroY
			glVertex2f(x, y)
		glEnd()


	graficaFunciones()

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
	global puntoAnguloX, puntoAnguloY, puntoAngulo,\
			color1, color2, color3, color4, color5

	y = height - y; puntoAngulo = False

	if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
		#se verifica si el boton de la linea es presionado para moverlo
		if x > puntoAnguloX-10 and x < puntoAnguloX+10 and y > puntoAnguloY-10 and y < puntoAnguloY+10:
			if puntoAnguloX >= 20 and puntoAnguloX <= 180: puntoAngulo = True

		#se verifica que los botones del menu son presionados para activarlos cambiando el color del boton
		if x > 20 and x < 150 and y > 470 and y < 500:
			if color1 == 0: color1 = 1
			else: color1 = 0 
		if x > 20 and x < 150 and y > 420 and y < 450:
			if color2 == 0: color2 = 1
			else: color2 = 0 
		if x > 20 and x < 150 and y > 370 and y < 400:
			if color3 == 0: color3 = 1
			else: color3 = 0 
		if x > 20 and x < 150 and y > 320 and y < 350:
			if color4 == 0: color4 = 1
			else: color4 = 0 
		if x > 20 and x < 150 and y > 270 and y < 300:
			if color5 == 0: color5 = 1
			else: color5 = 0 

	
	if button == GLUT_LEFT_BUTTON and state == GLUT_UP:
		puntoAngulo = False
		if puntoAnguloX < 20: puntoAnguloX = 20
		if puntoAnguloX > 180: puntoAnguloX = 180

	
	
	glutPostRedisplay()
	return

def mouseMotion(x,y):
	global puntoAnguloX, puntoAngulo, angulo
	
	y = height - y

	if puntoAngulo == True and puntoAnguloX >= 20 and puntoAnguloX <= 180:
		puntoAnguloX = x
		angulo = ((puntoAnguloX-20)*360)/160

	glutPostRedisplay()
	return


def keyInput(key, x, y):

	glutPostRedisplay()
	return   

def main():

	print 'Instrucciones:\
	\n * Modificar el angulo moviendo el punto de arriba\
	\n * Graficar las funciones activando los botones del menu\
	\n * El boton esta activo cuando el boton esta en color rojo\
	\n * Se pueden activar varios botones a la vez\
	\nFunciones:\
	\n *     Seno:  linea roja\
	\n *   Coseno:  linea azul\
	\n * Tangente:  linea verde\
	\n *  Valor x:  linea amarilla\
	\n * Ecuacion:  linea rosa'

	glutInit(sys.argv)
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
	glutInitWindowSize(1300, 600)
	glutInitWindowPosition(10, 10)
	glutCreateWindow("Practica 03")
	glutDisplayFunc(drawScene)
	glutReshapeFunc(resize)
	glutMotionFunc(mouseMotion)
	glutMouseFunc(mouseControl)
	glutKeyboardFunc(keyInput)
	glutMainLoop()

main()
