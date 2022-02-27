#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>
#define SIZE 500

using namespace std;

// Funcion encargada de controlar el cambio de tamano de la ventana
void reshape(int w, int h)
{
    glViewport (0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

    //width = w;
    //height = h;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Funcion que controla los eventos de dibujo de la aplicacion.
void display(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);

    //ciclo for que itera 2 veces
    //en la primera dibuja la parte izquierda del coche
    //en la segunda dibuja la parte derecha del coche
    //n es la variante de la posicion en X en ambas iteraciones
    //la posicion Y nunca cambia ya que se encuentra a la misma altura

    int n = 0;
    for (int i = 0; i < 2; ++i){
        glBegin(GL_LINE_STRIP);
        glColor3f(0,0,0);
        glVertex2f(abs(400-n),150);
        glVertex2f(abs(350-n),150);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glColor3f(0,0,0);
        glVertex2f(abs(400-n),200);
        glVertex2f(abs(370-n),200);
        glVertex2f(abs(350-n),145);
        glVertex2f(abs(180-n),145);
        glVertex2f(abs(150-n),155);
        glVertex2f(abs(155-n),145);
        glVertex2f(abs(180-n),135);
        glVertex2f(abs(340-n),135);
        glVertex2f(abs(345-n),145);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glColor3f(0,0,0);
        glVertex2f(abs(150-n),155);
        glVertex2f(abs(155-n),170);
        glVertex2f(abs(180-n),160);
        glVertex2f(abs(330-n),160);
        glVertex2f(abs(350-n),210);
        glVertex2f(abs(220-n),210); 
        glVertex2f(abs(210-n),200);
        glVertex2f(abs(200-n),160);   
        glEnd();
        glBegin(GL_LINE_STRIP);
        glColor3f(0,0,0);
        glVertex2f(abs(400-n),240);
        glVertex2f(abs(370-n),240);
        glVertex2f(abs(350-n),230);
        glVertex2f(abs(200-n),230);
        glVertex2f(abs(190-n),220);
        glVertex2f(abs(180-n),160);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glColor3f(0,0,0);
        glVertex2f(abs(155-n),170);
        glVertex2f(abs(155-n),270); 
        glVertex2f(abs(170-n),320);
        glVertex2f(abs(200-n),230);
        glVertex2f(abs(170-n),320);
        glVertex2f(abs(240-n),320);
        glVertex2f(abs(260-n),290);
        glVertex2f(abs(260-n),265);
        glVertex2f(abs(320-n),265); 
        glVertex2f(abs(350-n),230);
        glVertex2f(abs(320-n),265);
        glVertex2f(abs(260-n),300);
        glVertex2f(abs(260-n),305);
        glVertex2f(abs(270-n),315);
        glVertex2f(abs(240-n),315);
        glVertex2f(abs(270-n),315);
        glVertex2f(abs(275-n),320);
        glVertex2f(abs(400-n),320);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glColor3f(0,0,0);
        glVertex2f(abs(240-n),315);
        glVertex2f(abs(270-n),370);
        glVertex2f(abs(290-n),390);
        glVertex2f(abs(400-n),390);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glColor3f(0,0,0);
        glVertex2f(abs(190-n),320);
        glVertex2f(abs(180-n),330);
        glVertex2f(abs(155-n),330);
        glVertex2f(abs(155-n),340);
        glVertex2f(abs(180-n),355);
        glVertex2f(abs(190-n),355);
        glVertex2f(abs(190-n),335);
        glVertex2f(abs(205-n),320);
        glVertex2f(abs(210-n),320);
        glVertex2f(abs(220-n),330);
        glVertex2f(abs(250-n),330);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glColor3f(0,0,0);
        glVertex2f(abs(190-n),300);
        glVertex2f(abs(210-n),250);
        glVertex2f(abs(230-n),250);
        glVertex2f(abs(230-n),295);
        glVertex2f(abs(190-n),300);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glColor3f(0,0,0);
        glVertex2f(abs(160-n),143);
        glVertex2f(abs(165-n),120);
        glVertex2f(abs(170-n),115);
        glVertex2f(abs(220-n),115);
        glVertex2f(abs(225-n),120);
        glVertex2f(abs(225-n),135);
        glEnd();
        n+=800;
    }



    glFlush(); 

    glutSwapBuffers();
}

// Funcion principal.
int main(int argc, char *argv[])
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Ferrari");
    //init(); 
    glutDisplayFunc(display);
    //glutKeyboardFunc(keyboardCallbackProc);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
