#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#define SIZE 500
#define PI 3.141592654 
#define Retardo 12

using namespace std;

//grafica la curva para la ventana
void circulo(int posx, int posy, double radio){
    glBegin(GL_LINE_STRIP);
    for(int ang = 0; ang < 361; ang++){
        int x = radio * cos(ang*PI/180) + posx;
        int y = radio * sin(ang*PI/180) + posy;
        glVertex2f(x,y);
    }
    glEnd();
}

// Funcion que controla los eventos de dibujo de la aplicacion.
void display(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,0,0);

    glBegin(GL_LINES);
    glVertex2f(0, SIZE/2);
    glVertex2f(SIZE, SIZE/2);
    glVertex2f(SIZE/2, 0);
    glVertex2f(SIZE/2, SIZE);
    glEnd();
    
    glFlush(); 

    glutSwapBuffers();
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
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(650, 650);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("Practica 3");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //glutTimerFunc(Retardo,TimerFunction, 1);
    //glutTimerFunc(Retardo2,TimerFunction2, 1);
    glutMainLoop();
    return 0;
}