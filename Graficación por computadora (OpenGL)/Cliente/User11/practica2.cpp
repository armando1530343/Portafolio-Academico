#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#define SIZE 500
#define PI 3.141592654 
#define Retardo 10
#define radio1 50

using namespace std;

//se crea un tipo de dato que guarda los datos de un circulo
struct coords_circulos{
    int x, y, color;
    double radio;
};

std::vector<coords_circulos> circulos;

//coordenadas del circulo
int centrox = SIZE/2;
int centroy = SIZE/2;
//coordenadas del punto en movimiento
int puntoX = centrox + radio1; 
int puntoY = centroy + radio1;


int radio2 = 0;
int angulo = 90;
int vueltas = 0;
int color = 0;
int n = 0;

// Funcion encargada de controlar el cambio de tamano de la ventana
void reshape(int w, int h)
{
    glViewport (0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//grafica la curva para la ventana
void dibuja_circulo(int posx, int posy, double radio){
    glBegin(GL_LINE_STRIP);
    for(int ang = 0; ang < 361; ang++){
        int x = radio * cos(ang*PI/180) + posx;
        int y = radio * sin(ang*PI/180) + posy;
        glVertex2f(x,y);
    }
    glEnd();
}

//funcion que calcula la distancia entre dos puntos
//esta calcula la distancia entre el punto superior del circulo principal y el punto en movimiento
double euclidiana(int x1, int y1, int x2, int y2){
	return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}

// Funcion que controla los eventos de dibujo de la aplicacion.
void display(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,0,0);

    //se dibuja el primer circulo
    dibuja_circulo(250,250,radio1);
    glPointSize(8);
    //punto en movimiento
    glBegin(GL_POINTS);
    glColor3f(1,0,0);
    glVertex2f(puntoX, puntoY);
    glEnd();

    //linea roja que representa el radio del segundo circulo 
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex2f(250, 250+radio1);
    glVertex2f(puntoX, puntoY);
    glEnd();

    //se calcula la medida del radio (linea roja)
    radio2 = euclidiana(250, 250+radio1, puntoX, puntoY);

    glColor3f(0,0,0);

    //segundo circulo
    dibuja_circulo(puntoX, puntoY, radio2);

    //se dubujan los circulos rojos remarcados
    for (int i = 0; i < circulos.size(); ++i){
    	glColor3f(1,circulos.at(i).color, circulos.at(i).color);
    	dibuja_circulo(circulos.at(i).x, circulos.at(i).y, circulos.at(i).radio);
    }

    glFlush(); 
    glutSwapBuffers();
}
void TimerFunction(int value){

	coords_circulos cir;

    //se actualizan las coordenadas del segundo circulo

	puntoX = radio1 * cos(angulo*PI/180) + 250;
	puntoY = radio1 * sin(angulo*PI/180) + 250;

    //se guardan los datos en la variable de struct

	cir.x = puntoX;
	cir.y = puntoY;
	cir.radio = radio2;
	cir.color = 0;

	if(vueltas == 0)
		circulos.clear();

	if(angulo % 10 == 0 && puntoY != 300 && vueltas == 1)
		circulos.push_back(cir);

	if(vueltas == 2){
		if(angulo % 10 == 0 && angulo != 90){
			circulos.at(n).x = 2000;
			n++;
        }
    }
	else
		n = 0;

	angulo--;

	if(angulo < 0) 
        angulo = 360;

	if(angulo == 90) 
        vueltas++;

	if(vueltas > 2) {
		vueltas = 0;
		angulo = 90;
	}

    glutPostRedisplay();
    glutTimerFunc(Retardo,TimerFunction, 1);
    
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(SIZE, SIZE);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("Practica 2");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(Retardo,TimerFunction, 1);
    glutMainLoop();
    return 0;
}