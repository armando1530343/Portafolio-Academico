#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#define SIZE 500
#define PI 3.141592654 
#define Retardo 12
#define Retardo2 6

// tipo de dato que guarda coordenadas X y Y
struct coordenadas{
    int x, y;
};

std::vector<coordenadas> coord[13];//se crea un vector de coordenadas

int DIAMETRO = 240;//diametro del circulo
int RADIO = DIAMETRO/2;//radio del circulo

//radios de cada uno de los puntos de la recta con respecto al centro del circulo principal
int RADIOS[7] = {
    0, RADIO/6, RADIO/6*2,RADIO/6*3, RADIO/6*4, RADIO/6*5, RADIO
};
//coordenadas del centro del circulo mayor
int centroX = 325;
int centroY = 325;
//coordenadas del centro del circulo interior
int centroX2 = centroX;
int centroY2 = centroY + RADIO - DIAMETRO/6;

//angulos de rotacion de los circulos
int angulo_rotacion = 90;
int angulo_rotacion2 = 90;
int angulo_rotacion3 = 270;

//radio de rotacion del circulo interior
int RADIO_ROTACION = DIAMETRO/3;


int puntosX[13];
int puntosY[13];

int orden_puntos[13] = {6,5,4,3,2,1,0,7,8,9,10,11,12};

//double rojo = 0.0, verde = 1.0;
//double rojo2 = 0.0, verde2 = 1.0;

using namespace std;

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
void circulo(int posx, int posy, double radio){
    glBegin(GL_LINE_STRIP);
    for(int ang = 0; ang < 361; ang++){
        int x = radio * cos(ang*PI/180) + posx;
        int y = radio * sin(ang*PI/180) + posy;
        glVertex2f(x,y);
    }
    glEnd();
}

//se dibuja la recta
void recta(){
    glPointSize(5);

    //se dibujan los 13 puntos en la recta
    glBegin(GL_POINTS);
    double rojo = 0.0, verde = 1.0;
    for (int i = 0; i < 13; ++i){
        glColor3f(rojo, verde, 0);

        glVertex2f(puntosX[orden_puntos[i]], puntosY[orden_puntos[i]]);
        if(i < 6) rojo += 1.0/6;
        if(i > 6) verde -= 1.0/6;
    }
    
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 13; ++i){
        glColor3f(rojo, verde, 0);

        glVertex2f(puntosX[orden_puntos[i]], puntosY[orden_puntos[i]]);
        if(i < 6) rojo += 1.0/6;
        if(i > 6) verde -= 1.0/6;
    }
    
    glEnd();
}


// Funcion que controla los eventos de dibujo de la aplicacion.
void display(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,0,0);

    circulo(centroX, centroY, RADIO); // se dibuja el circulo mayor
    circulo(centroX2, centroY2, RADIOS[2]);//se dibuja el circulo interior

    recta();//se llama la funcion para dibujar la recta

    double rojo2 = 0.0, verde2 = 1.0;

    //se dibujan las lineas que van marcando los puntos de la recta
    for (int i = 0; i < 13; ++i){
        glBegin(GL_LINE_STRIP);

        glColor3f(rojo2, verde2, 0);
        
        for (int j = 0; j < coord[orden_puntos[i]].size(); ++j){
            glVertex2f(coord[orden_puntos[i]].at(j).x, coord[orden_puntos[i]].at(j).y);
        }
        glEnd();

        if(i < 6) rojo2 += 1.0/6;
        if(i > 6) verde2 -= 1.0/6;
    }

    glFlush(); 

    glutSwapBuffers();
}
void TimerFunction(int value){

	//nuevas coordenadas del centro del circulo interior con respecto al circulo mayor
    centroX2 = RADIO_ROTACION * cos(angulo_rotacion*PI/180) + centroX;
    centroY2 = RADIO_ROTACION * sin(angulo_rotacion*PI/180) + centroY;

    angulo_rotacion-=1;

    if(angulo_rotacion < 0)
        angulo_rotacion = 360;
    if(angulo_rotacion == 90){
        for (int i = 0; i < 13; ++i){
            coord[i].clear();
        }
        angulo_rotacion = 90;
        angulo_rotacion2 = 90;
        angulo_rotacion3 = 270;
        centroX2 = centroX;
        centroY2 = centroY + RADIO - DIAMETRO/6;
    }

    glutPostRedisplay();
    glutTimerFunc(Retardo,TimerFunction, 1);
    
}
void TimerFunction2(int value){

    coordenadas c;

    for (int i = 0; i < 7; ++i){
        puntosX[i] = RADIOS[i] * cos(angulo_rotacion2*PI/180) + centroX2;
        puntosY[i] = RADIOS[i] * sin(angulo_rotacion2*PI/180) + centroY2;
        c.x = puntosX[i];
        c.y = puntosY[i];
        coord[i].push_back(c);
    }
    int j = 1;
    for (int i = 7; i < 13; ++i){
        puntosX[i] = RADIOS[j] * cos(angulo_rotacion3*PI/180) + centroX2;
        puntosY[i] = RADIOS[j] * sin(angulo_rotacion3*PI/180) + centroY2;    
        c.x = puntosX[i];
        c.y = puntosY[i];
        coord[i].push_back(c);
        j++;
    }
    angulo_rotacion2+=1;
    angulo_rotacion3+=1;

    if(angulo_rotacion2 > 360)
        angulo_rotacion2 = 0;
    if(angulo_rotacion3 > 360)
        angulo_rotacion3 = 0;

    glutPostRedisplay();
    glutTimerFunc(Retardo2,TimerFunction2, 1);
    
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(650, 650);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("Practica 2");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(Retardo,TimerFunction, 1);
    glutTimerFunc(Retardo2,TimerFunction2, 1);
    glutMainLoop();
    return 0;
}