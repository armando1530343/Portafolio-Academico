
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string.h> 
#include <sstream>

#define PI 3.141592654 // valor de PI

using namespace std;


int circuloMes[12][2]; //guarda las posiciones X y Y de los circulos que grafican el mes 


int anio = 2018; //identifica el anio

int radio = 350; //radio del circulo mayor

int diaMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};//cantidad de dias que tiene cada mes desde enero hasta diciembre
string mes[] = {"Ene","Feb","Mar","Abr","May","Jun","Jul","Ago","Sep","Oct","Nov","Dic"}; // arreglo que guarda el nombre del mes


void writeBitmapString(void *font, string str)
{
	int i;
   	for(i = 0; i < str.size(); i++)
   		glutBitmapCharacter(font, str[i]);   
}

void drawScene(){
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);


	int x, y; //variables de posiciones
	
	//variables para transformar de numero a cadena
	stringstream ss;
   	string newStr;

   	//se dibuja el circulo principal
	glBegin(GL_POLYGON);
	glColor3f(0,.1,1);

	//se dibuja la circunferencia
	for (int ang = 0; ang <=360; ang++){
		x = radio * cos((ang)*PI/180) + 350;
		y = radio * sin((ang)*PI/180) + 350;
		glVertex2f(x,y);
	}

	glEnd();

	ss<<anio<<endl;
    newStr = ss.str();

	glColor3f(0,0,0);
	glRasterPos2f(350, 350);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, newStr);

	int i = 0;

	// se grafican los puntos en donde se posicionan los circulos de los meses
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(0,1,0);
	for (int ang = 0; ang <=360; ang++){
		if(ang%30 == 0 && ang != 0){			
			x = (radio * cos((ang)*PI/180)*.75 + 350);
			y = (radio * sin((ang)*PI/180)*.75 + 350);
			glVertex2f(x,y);
			circuloMes[i][0] = x; //se guarda la posicion en x
			circuloMes[i][1] = y; //se guarda la posicion en y
			i = i + 1;
		}
	}

	glEnd();

	int radio2 = 68; //radio de los circulos menores


	//en este ciclo se dibujan los circulos de los meses
	for (i = 0; i < 12; i++){
		glBegin(GL_POLYGON);

		//se selecciona el color dependiendo el numero de mes
		if (i < 3) glColor3f(1,0,0);
		else if (i < 6) glColor3f(0,1,0);
		else if (i < 9) glColor3f(1,0,1);
		else if (i < 12) glColor3f(1,1,0);

		//se grafican los vertices del poligono del circulo menor

		for (int ang = 0; ang <=360; ang++){

			x = radio2 * cos((ang)*PI/180) + circuloMes[i][0];
			y = radio2 * sin((ang)*PI/180) + circuloMes[i][1];
			glVertex2f(x,y);
		}

		glEnd();

		//se escribe el nombre del mes dentro del circulo

		glColor3f(0,0,0);
		glRasterPos2f(circuloMes[i][0], circuloMes[i][1]);
		writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, mes[i]);

	}

	//en este ciclo se grafica el numero de dias de cada mes
	for (i = 0; i < 12; i++){
		int ang=1;
		int dia = 1;
		while(ang <= 360){
			if (ang % 11 == 0){	
				//posiciones en las que se coloca cada numero del dia
				x = ((radio2-10) * cos((ang)*PI/180) + circuloMes[i][0]);
				y = ((radio2-10) * sin((ang)*PI/180) + circuloMes[i][1]);
				
				
				if (dia < diaMes[i]+1){
					stringstream s;
					s<<dia<<endl;
    				newStr = s.str();
					glColor3f(0,0,0);
					glRasterPos2f(x, y);
					writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, newStr);
				}
					
				dia = dia + 1;
			}
			ang = ang + 1;
		}
	}
	

	glFlush();
}

void resize(int w, int h){

   glViewport (0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

   int width = w;
   int height = h;

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main(int argc, char **argv)
{
    srand(time(NULL));

	
   	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 10);
	glutCreateWindow("Practica 01");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutMainLoop();
	return 0;
}