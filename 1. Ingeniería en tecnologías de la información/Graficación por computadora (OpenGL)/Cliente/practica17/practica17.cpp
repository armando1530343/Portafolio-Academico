#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <sstream>

#define PI 3.141592654

using namespace std;

float width, height;

//coordenadas de los vertices
float x_centro = 400;
float y_centro = 250;
float x_rojo = 250;
float y_rojo = 400;
float x_azul = 550;
float y_azul = 400;

//variables que verifican si un vertice es seleccionado
int rojo = 0;
int azul = 0;
int centro = 0;

//angulos de los vectores
float angulo_rojo;
float angulo_azul;
float angulo;

//verifica si se visualiza la circunferencia
bool circulo = false;

void writeBitmapString(void *font, string str)
{
	int i;
   	for(i = 0; i < str.size(); i++)
   		glutBitmapCharacter(font, str[i]);
}

//funcion que dibuja una circunferencia
void circunferencia(int X, int Y){
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    for(int ang = 0; ang < 361; ang++){
        int x = 100 * cos(ang*PI/180) + X;
        int y = 100 * sin(ang*PI/180) + Y;
        glVertex2f(x,y);
    }
    glEnd();
}

void display(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(5);

    //graficacion del vertice rojo
    glBegin(GL_POINTS);
    glColor3f(1,0,0);
    glVertex2f(x_rojo, y_rojo);
    glEnd();

    //graficacion del vertice azul
    glBegin(GL_POINTS);
    glColor3f(0,0,1);
    glVertex2f(x_azul, y_azul);
    glEnd();

    //graficacion de vectores
    glBegin(GL_LINES);
    //vector rojo
    glColor3f(1,0,0);
    glVertex2f(x_centro, y_centro);
    glVertex2f(x_rojo, y_rojo);
    //vector azul
    glColor3f(0,0,1);
    glVertex2f(x_centro, y_centro);
    glVertex2f(x_azul, y_azul);
    glEnd();

    //la circunferecia se grafica si la variable circulo = true

    if(circulo)
        circunferencia(x_centro, y_centro);

    //se calculan los angulos de los vectores con respecto al vertice origen
    angulo_rojo = atan2(y_rojo - y_centro, x_rojo - x_centro) * 180/PI;
    angulo_azul = atan2(y_azul - y_centro, x_azul - x_centro) * 180/PI;

    if(angulo_rojo < 0){
        angulo_rojo = angulo_rojo + 360;
    }
    if(angulo_azul < 0){
        angulo_azul = angulo_azul + 360;
    }

    //se dibuja el poligono central que representa al angulo formado entre los dos vectores
    glBegin(GL_POLYGON);
    glColor3f(.2,1,.2);
    glVertex2f(x_centro, y_centro);

    if(angulo_rojo < angulo_azul){
        for(int ang = angulo_rojo; ang < angulo_azul; ang ++){
            glVertex2f(20*cos(ang*PI/180)+x_centro, 20*sin(ang*PI/180)+y_centro);
        }
        angulo = angulo_azul - angulo_rojo;
    }
    else{
        for(int ang = angulo_azul; ang > 0; ang --){
            glVertex2f(20*cos(ang*PI/180)+x_centro, 20*sin(ang*PI/180)+y_centro);
        }
        for(int ang = 360; ang > angulo_rojo; ang --){
            glVertex2f(20*cos(ang*PI/180)+x_centro, 20*sin(ang*PI/180)+y_centro);
        }

        angulo = 360 - angulo_rojo + angulo_azul;
    }

    //cout << angulo_rojo << ", " << angulo_azul << ", " << angulo << endl;

    glEnd();

    //se dibuja el vertice origen
    glBegin(GL_POINTS);
    glColor3f(0,0,0);
    glVertex2f(x_centro, y_centro);
    glEnd();

    //graficacion de letras

    glColor3f(.0, .0, .0);
    stringstream ss; ss<<angulo<<endl;
    string newStr = ss.str();
    glRasterPos2f(300, 100);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "angulo = " + newStr);
    stringstream ss2; ss2<<cos(angulo)<<endl;
    string newStr2 = ss2.str();
    glRasterPos2f(300, 70);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "cos(angulo) = " + newStr2);
    glRasterPos2f(20, 30);
    if(circulo)
        writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Tecla c: circunferencia=true ");
    else
        writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Tecla c: circunferencia=false ");


    glFlush();


}

void mouseControl(int button, int state, int x, int y){

	//se verifica que se de clic izquierdo sobre la ventana

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        y = height - y;

        //posiciones de area de seleccion del vertice rojo
        if(x >= x_rojo-2 && x <= x_rojo+2 && y >= y_rojo-2 && y <= y_rojo+2){
            rojo = 1;//seleccionado
        }
        else{
            rojo = 0;//no seleccionado
        }
        //posiciones de area de seleccion del vertice azul
        if(x >= x_azul-2 && x <= x_azul+2 && y >= y_azul-2 && y <= y_azul+2){
            azul = 1;//seleccionado
        }
        else{
            azul = 0;//no seleccionado
        }
        //posiciones de area de seleccion del vertice origen
        if(x >= x_centro-2 && x <= x_centro+2 && y >= y_centro-2 && y <= y_centro+2){
            centro = 1;//seleccionado
        }
        else{
            centro = 0;//no seleccionado
        }
    }

    glutPostRedisplay();
}
void keyInput(unsigned char key, int x, int y)
{
   switch (key)
   {
   	//la tecla c cambia el valor booleano de la variable circulo
   	//significa que dibuja o quita la circunferencia
      case 'c':
        circulo = !circulo;
         break;
      default:
         break;
   }
   glutPostRedisplay();
}

void mouseMotion(int x, int y){

    y = height - y;

    if(rojo == 1){
        x_rojo = x;
        y_rojo = y;
    }
    if(azul == 1){
        x_azul = x;
        y_azul = y;
    }
    if(centro == 1){
        x_centro = x;
        y_centro = y;
    }

    glutPostRedisplay();
}

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

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Dot Product");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyInput);
    glutMouseFunc(mouseControl);
	glutMotionFunc(mouseMotion);
    glutMainLoop();
    return 0;
}

/*

Desarrollo experimental:

En esta practica se utilizó principalmente una funcion de trigonometria, ya que se necesita sacar las medidas de un angulo a partir
de la inclinacion de un vector con respecto a un punto central. Primero se asignaron las coordenadas de cada vertice usando dos 
variables para cada uno (X y Y). En el drawScene se graficaron tres vertices (rojo, azul, centro) con posiciones iniciales usando
GL_POINTS de tamaño 5. Usando estas mismas posiciones se dibujaron dos lineas con GL_LINES tomando como extremos el centro y el 
vertice movible(rojo y azul), asi se crean los vectores. Despues se crea un poligono central con GL_POLYGON el cual cuenta con un
radio de 20 con respecto al centro, y va dejando la forma del angulo que se forma entre los vectores tomando al vector rojo como
inicio y al azul como final. Y finalmente en drawScene se dibuja la circunferencia con radio 100 con respecto al centro, esta se
visualiza siempre que la variable circulo = true, de lo contrario no se muestra. Para asignar el cambio de valor de la variable
circulo, se debe teclear la letra 'c', para mostrar o quitar la circunferencia. Para modificar las posiciones de los vertices se
uso la funcion de mouseControl, para verificar las posiciones del area de los vertices seleccionadas, y la funcion mouseMotion, 
para una vez seleccionado un vertice, las posiciones actuales del vertice sean iguales a las del cursor del mouse en pantalla.

*/
