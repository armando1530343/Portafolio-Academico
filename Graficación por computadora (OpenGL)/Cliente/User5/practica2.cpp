#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#define SIZE 500
#define CANTIDAD_PENDULOS 10
#define PI 3.141592670
#define Retardo 30
#define Retardo2 6

using namespace std;

//coordenadas del origen
int origenX = 250;
int origenY = 450;
//longitud del pendulo menor (ira incrementando)
double longitud_menor = 20;

//estructura que guarda las caracteristicas de un pendulo
struct Estructura_pendulo{
    double x, //posicion en X del extremo del pendulo
           y, //posicion en Y del extremo del pendulo
           longitud, //longitud del pendulo
           angulo; //angulo actual del pendulo con respecto al origen
    bool direccion;
}pendulo[CANTIDAD_PENDULOS];

double separacion = 1.0; //diferencia de distancia entre cada pendulo

// Funcion que controla los eventos de dibujo de la aplicacion.
void display(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,0,0);

    //se dibujan las lineas de los pendulos
    glBegin(GL_LINES);
    for (int i = 0; i < CANTIDAD_PENDULOS ; ++i){
        glVertex2f(origenX, origenY);
        glVertex2f(pendulo[i].x, pendulo[i].y);
    }
    glEnd();

    //se dibujan los pendulos    
    for (int i = 0; i < CANTIDAD_PENDULOS ; ++i){
        glPointSize(3+(i*.5));
        glBegin(GL_POINTS);
        glVertex2f(pendulo[i].x, pendulo[i].y);
        glEnd();
    }
    
    glFlush(); 

    glutSwapBuffers();
}
void TimerFunction(int value){
    double multiplos[CANTIDAD_PENDULOS];
    double n = 1.0;

    for (int i = 0; i < CANTIDAD_PENDULOS; ++i){
        multiplos[i] = n;
        n+=.5;
    }
    int j = CANTIDAD_PENDULOS-1;

    for (int i = 0; i < CANTIDAD_PENDULOS ; ++i){

        //Se actualizan las coordenadas de los extremos de cada pendulo
        pendulo[i].x = pendulo[i].longitud * cos(pendulo[i].angulo*PI/180) + origenX;
        pendulo[i].y = pendulo[i].longitud * sin(pendulo[i].angulo*PI/180) + origenY;

        //Se verifica si los pendulos se muevan entre un rango de angulos
        if(pendulo[i].direccion){
            pendulo[i].angulo += multiplos[j];
            if(pendulo[i].angulo > -60.0)
                pendulo[i].direccion = false;
        }
        else{
            pendulo[i].angulo -= multiplos[j];
            if(pendulo[i].angulo < -120.0)
                pendulo[i].direccion = true;
        }
        j--;
    }
	
    glutPostRedisplay();
    glutTimerFunc(Retardo,TimerFunction, 1);
    
}
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
int main(int argc, char *argv[])
{
    //se inicializan los valores de cada pendulo
    for (int i = 0; i < CANTIDAD_PENDULOS ; ++i){
       
        pendulo[i].longitud = longitud_menor;//longitud del pendulo
        pendulo[i].x = origenX;//posicion X del extremo del pendulo
        pendulo[i].y = origenY - pendulo[i].longitud; //posicion Y del extremo del pendulo
        //Calculo del angulo de inclinacion con respecto al origen
        pendulo[i].angulo = atan2(pendulo[i].y - origenY, pendulo[i].x - origenX) * 180 / PI;
        pendulo[i].direccion = true;//movimiento de inicio (true = derecha, false = izquierda)
        longitud_menor += separacion;
        separacion += separacion*.9;

        
    }


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