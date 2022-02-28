#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include <sstream>
#include <vector>
#define SIZE 500
#define PI 3.141592654

using namespace std;

float width, height;

//coordenadas del origen del plano cartesiano
static float origenX = 80;
static float origenY = 130;

int vertices = 3;//numero de vertices inicial de la figura

vector <float> coordenadas[2];//vector que guarda las coordenadas de los vertices
vector <bool> vertice;//valor booleano de cada vertice que verifica si es presionado

bool angles = false;//activador de vista de los angulos
bool side = false;//activador de vista del valor del lado de la figura
bool diagonales = false;//activador de vista de las diagonales entre vertices
bool coords = false;//activador de vista de las coordenadas de cada vertice
bool guides = false;//activador de vista de los ejes fque forman cada vertice

void reshape(int w, int h)
{
    glViewport (0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

    width = w;
    height = h;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void writeBitmapString(void *font, string str)
{
	int i;
   	for(i = 0; i < str.size(); i++)
   		glutBitmapCharacter(font, str[i]);
}

void display(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);

    //----------graficacion del plano cartesiano------------

    //--ejes
    glBegin(GL_LINES);
    //eje Y
    glColor3f(1,0,0);
    glVertex2f(origenX, 0);
    glVertex2f(origenX, 500);
    //eje X
    glColor3f(0,0,1);
    glVertex2f(0, origenY);
    glVertex2f(900, origenY);
    glEnd();


    glPointSize(5);

    //puntos del eje Y (Rojo)
    int separacion = 0;
    for(int i = 0; i < 7; i++){
    	stringstream ss; ss<<separacion<<endl;
   		string newStr = ss.str();
   		glBegin(GL_POINTS);
    	glColor3f(1,0,0);
    	glVertex2f(origenX, origenY + separacion);
    	glEnd();

    	//se dibujan los numeros del eje Y
    	glColor3f(1,0,0);
    	glRasterPos2f(origenX - 25, origenY + separacion);
   		writeBitmapString(GLUT_BITMAP_HELVETICA_12, newStr);

   		separacion += 50; //separacion entre puntos
    }

    //puntos del eje X (Azul)
    separacion = 0;
    for(int i = 0; i < 13; i++){
    	stringstream ss; ss<<separacion<<endl;
   		string newStr = ss.str();
    	glBegin(GL_POINTS);
    	glColor3f(0,0,1);
    	glVertex2f(origenX + separacion, origenY);
    	glEnd();

    	//se dibujan los numeros del exe X
    	glColor3f(0,0,1);
    	glRasterPos2f(origenX + separacion, origenY - 15);
   		writeBitmapString(GLUT_BITMAP_HELVETICA_12, newStr);

    	separacion += 50; //separacion entre puntos
    }

    //graficar vertices de la figura inicial
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(0,0,0);
    for(int i = 0; i < vertices; i++){
    	glVertex2f(coordenadas[0][i], coordenadas[1][i]);
    }
    glEnd();

    //muestra las diagonales que se forman entre todos los vertices de las figuras
    if(diagonales){
    	//se recorre cada vertice
    	for(int i = 0; i < vertices; i ++){
	    	glBegin(GL_LINES);
	    	glColor3f(.3,1,.3);
	    	//el vertice se une con los demas vertices
	    	for(int j = 0; j < vertices; j++){
	    		glVertex2f(coordenadas[0][i], coordenadas[1][i]);
	    		glVertex2f(coordenadas[0][j], coordenadas[1][j]);
	    	}
	    	glEnd();
	    }
    }

    //muestra las lineas de coordenadas de posicion del vertice
    if(guides){
    	//se recorre cada vertice
    	for(int i = 0; i < vertices; i ++){
	    	glBegin(GL_LINES);
	    	glColor3f(.8,.4,.8);
	    	//eje X vertice
	    	glVertex2f(origenX, coordenadas[1][i]);
	    	glVertex2f(coordenadas[0][i], coordenadas[1][i]);
	    	//eje Y vertice
	    	glVertex2f(coordenadas[0][i], coordenadas[1][i]);
	    	glVertex2f(coordenadas[0][i], origenY);
	    	glEnd();
	    }
    }

    //lineas (union de vertices)
    glBegin(GL_LINE_LOOP);
    glColor3f(0,0,0);
    for(int i = 0; i < vertices; i++){
    	glVertex2f(coordenadas[0][i], coordenadas[1][i]);
    }
    glEnd();

    float lado = sqrt(pow(coordenadas[0][0] - coordenadas[0][1], 2) + pow(coordenadas[1][0] - coordenadas[1][1], 2));

    //se dibujan los angulos inferiores

	for(int i = 0; i < vertices; i++){
    	float ang_inicio, ang_fin;
    	if(i == 0)
    		ang_inicio = atan2(coordenadas[1][vertices-1] - coordenadas[1][i], coordenadas[0][vertices-1] - coordenadas[0][i]) * 180/PI;
    	else
    		ang_inicio = atan2(coordenadas[1][i-1] - coordenadas[1][i], coordenadas[0][i-1] - coordenadas[0][i]) * 180/PI;

    	if(i == vertices-1)
    		ang_fin = atan2(coordenadas[1][0] - coordenadas[1][i], coordenadas[0][0] - coordenadas[0][i]) * 180/PI;
    	else
    		ang_fin = atan2(coordenadas[1][i+1] - coordenadas[1][i], coordenadas[0][i+1] - coordenadas[0][i]) * 180/PI;






    	if(ang_inicio < 0) ang_inicio += 360;
    	if(ang_fin < 0) ang_fin += 360;

    	//se dibuja el angulo de cada vertice
    	if(angles){
    		if(i == 0){
	    		//se muestra el valor del angulo inferior
	    		stringstream ss; ss<<ang_inicio-ang_fin<<endl;
	   			string newStr = ss.str();
	   			glColor3f(0,0,0);
		    	glRasterPos2f(coordenadas[0][0]-30, coordenadas[1][0]-50);
		   		writeBitmapString(GLUT_BITMAP_HELVETICA_12, "a= " + newStr);
	    	}
	    	glBegin(GL_LINE_STRIP);
	    	glColor3f(0,0,0);

	    	if(ang_fin > ang_inicio){
	    		for(int ang = ang_fin; ang < 360; ang++){
		    		float x = 20 * cos(ang * PI/180) + coordenadas[0][i];
		    		float y = 20 * sin(ang * PI/180) + coordenadas[1][i];
		    		glVertex2f(x, y);
		    	}
		    	for(int ang = 0; ang < ang_inicio; ang++){
		    		float x = 20 * cos(ang * PI/180) + coordenadas[0][i];
		    		float y = 20 * sin(ang * PI/180) + coordenadas[1][i];
		    		glVertex2f(x, y);
		    	}
	    	}
	    	else{
	    		for(int ang = ang_fin; ang < ang_inicio; ang++){
		    		float x = 20 * cos(ang * PI/180) + coordenadas[0][i];
		    		float y = 20 * sin(ang * PI/180) + coordenadas[1][i];
		    		glVertex2f(x, y);
		    	}
	    	}
	    	glEnd();
	    }

	    //muestra el valor de los lados
	    if(side){
	    	if(i == 0){
		   		//se muestra el valor del lado
	    		stringstream ss2; ss2<<lado<<endl;
	   			string newStr2 = ss2.str();
	   			glColor3f(0,0,0);
		    	glRasterPos2f(coordenadas[0][0]+60, coordenadas[1][0]-30);
		   		writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Side = " + newStr2);
	    	}
	    }

	    //muestra las coordenadas de cada vertice
	    if(coords){
	    	//se muestra el valor del lado
    		stringstream ss3, ss4;
    		ss3<<floor(coordenadas[0][i])-origenX<<endl;
    		ss4<<floor(coordenadas[1][i])-origenY<<endl;
   			string x_str = ss3.str();
   			string y_str = ss4.str();
   			glColor3f(1,0,.5);
	    	glRasterPos2f(coordenadas[0][i]+20, coordenadas[1][i]);
	   		writeBitmapString(GLUT_BITMAP_HELVETICA_12, "("+x_str+","+y_str+")");
	    }
    }

    glColor3f(0,0,0);
	glRasterPos2f(90, 80);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Tecla  ' + '  = incrementa vertices");
	glRasterPos2f(90, 70);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Tecla  ' - '  = decrementa vertices");
	glRasterPos2f(90, 60);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Tecla  ' a '  = angulos inferiores");
	glRasterPos2f(90, 50);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Tecla  ' s '  = medida del lado");
	glRasterPos2f(90, 40);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Tecla  ' d '  = diagonales");
	glRasterPos2f(90, 30);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Tecla  ' c '  = coordenadas");
	glRasterPos2f(90, 20);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Tecla  ' g '  = ejes vertices");
	glRasterPos2f(90, 90);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Tecla  ' r '  = restaurar");
	glRasterPos2f(90, 10);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Selecciona los vertices con el clic izquierdo para moverlos");



    glFlush();


}

void mouseControl(int button, int state, int x, int y){

    y = height - y;

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        //se verifica que los vertices sean seleccionados con el mouse
    	for(int i = 0; i < vertices; i++){
    		if(x >= coordenadas[0][i]-5 && x <= coordenadas[0][i]+5 && y >= coordenadas[1][i]-5 && y <= coordenadas[1][i]+5){
    			vertice[i] = true;
    		}
    		else{
    			vertice[i] = false;
    		}
    	}

    }

    glutPostRedisplay();
}

void mouseMotion(int x, int y){

    y = height - y;

    //se mueven los vertices de la figura de acuerdo a las posiciones del mouse
    for(int i = 0; i < vertices; i++){
    	if(vertice[i]){
    		coordenadas[0][i] = x;
    		coordenadas[1][i] = y;
    	}
    }


    glutPostRedisplay();
}


void keyInput(unsigned char key, int x, int y)
{
	float distancia_angulo;
    float angulo_inicial = 70.0;
   switch (key)
   {
      case '+':
      	vertices++;
      	coordenadas[0].clear();
      	coordenadas[1].clear();
      	distancia_angulo = 360.0 / vertices;
      	for(int i = 0; i < vertices; i++){
	    	float x = 150 * cos(angulo_inicial * PI / 180) + 300;
	    	float y = 150 * sin(angulo_inicial * PI / 180) + 280;
	    	coordenadas[0].push_back(x);
	    	coordenadas[1].push_back(y);
	    	vertice.push_back(false);
	    	angulo_inicial += distancia_angulo;
	    }
        break;
      case '-':
      	if(vertices > 3){
      		vertices--;
      		coordenadas[0].clear();
      		coordenadas[1].clear();
      		distancia_angulo = 360 / vertices;
      		for(int i = 0; i < vertices; i++){
		    	float x = 150 * cos(angulo_inicial * PI / 180) + 300;
		    	float y = 150 * sin(angulo_inicial * PI / 180) + 280;
		    	coordenadas[0].push_back(x);
		    	coordenadas[1].push_back(y);
		    	vertice.push_back(false);
		    	angulo_inicial += distancia_angulo;
		    }
      	}
        break;
      case 'r':
      	//vertices++;
      	coordenadas[0].clear();
      	coordenadas[1].clear();
      	distancia_angulo = 360.0 / vertices;
      	for(int i = 0; i < vertices; i++){
	    	float x = 150 * cos(angulo_inicial * PI / 180) + 300;
	    	float y = 150 * sin(angulo_inicial * PI / 180) + 280;
	    	coordenadas[0].push_back(x);
	    	coordenadas[1].push_back(y);
	    	vertice.push_back(false);
	    	angulo_inicial += distancia_angulo;
	    }
        break;
        break;

      case 'a':
      	angles = !angles;
      	break;
      case 's':
      	side = !side;
      	break;
      case 'd':
      	diagonales = !diagonales;
      	break;
      case 'c':
      	coords = !coords;
      	break;
      case 'g':
      	guides = !guides;
      	break;
      default:
         break;
   }
   glutPostRedisplay();
}

// Funcion principal.
int main(int argc, char *argv[])
{
	float distancia_angulo = 360 / vertices;
    float angulo_inicial = 70.0;

	for(int i = 0; i < vertices; i++){
    	float x = 150 * cos(angulo_inicial * PI / 180) + 300;
    	float y = 150 * sin(angulo_inicial * PI / 180) + 280;
    	coordenadas[0].push_back(x);
    	coordenadas[1].push_back(y);
    	vertice.push_back(false);
    	angulo_inicial += distancia_angulo;
    }
    cout << "hola" << endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(900, 500);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("practica2");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyInput);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseControl);
	glutMotionFunc(mouseMotion);
    glutMainLoop();
    return 0;
}
