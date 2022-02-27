#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string> 
#include <sstream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

/*  Constantes   */
#define SIZE 650        //Ventana
#define NEAR_Z 1.0      //Distancia dibujado cerca del eje Z
#define FAR_Z 500.0     //Distancia dibujado lejos del eje Z
#define PI 3.1416       //Valor de PI

/*  Globales    */
double zoom = 0.5;      //Valor del zoom de la camara
double AngleX = 0;      //Grados de rotacion del eje X
double AngleY = 0;    //Grados de rotacion del eje Y
double AngleZ = 0;      //Grados de rotacion del eje Z
double rotationx = 0.0; //Contenedora de la longitud recorrida por el mouse en X
double rotationy = 0.0; //Contenedora de la longitud recorrida por el mouse en Y
int stx = 0;            //Contenedora del valor anterior de X 
int sty = 0;            //Contenedora del valor anterior de Y
bool entrada;           //Bandera detecta si mouse arrastra camara

using namespace std;


// Funcion que dibuja un cilindro en determinada posicion(X,Y,Z) con su altura
// radio y anchura y ademas la cantidad de lados que lo componen.
void DibujaCilindro(int X, int Y, int Z, float rad, int anchura, int altura, GLfloat LADOS, int colores[]) {
    GLfloat x = X, y = Y, z = Z, angle;
    glTranslatef(x, y, z);
    GLfloat radio;
    GLfloat Puntos[2][500][3];
    int Contador = 0;
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
        glColor3f(0,1,0);
        radio = rad;
        Contador = 0;
        for (angle = 0.0f; angle <= (2.0f * PI); angle += (2.0f * PI) / LADOS) {
            Puntos[i][Contador][0] = radio * sin(angle) + X;
            Puntos[i][Contador][1] = radio * cos(angle) + Y;
            Puntos[i][Contador][2] = Z;   
            glVertex3f(Puntos[i][Contador][0], Puntos[i][Contador][1], Puntos[i][Contador][2]);
            Contador++;
        }
        glEnd();
        Z -= anchura;
        //X += altura;
        //Y += altura;
    }
    for (Contador = 0; Contador < LADOS; Contador++) {
        glBegin(GL_POLYGON);
        
        glColor3f(colores[0], colores[1], colores[2]);
        int Temporal = 0;
        if (Contador == (int) (LADOS - 1))
            Temporal = 0;
        else
            Temporal = Contador + 1;
        glVertex3f(Puntos[0][Contador][0], Puntos[0][Contador][1], Puntos[0][Contador][2]);
        glVertex3f(Puntos[0][Temporal][0], Puntos[0][Temporal][1], Puntos[0][Temporal][2]);
        glVertex3f(Puntos[1][Temporal][0], Puntos[1][Temporal][1], Puntos[1][Temporal][2]);
        glVertex3f(Puntos[1][Contador][0], Puntos[1][Contador][1], Puntos[1][Contador][2]);
        glEnd();
    }
}

void Display(void) {

    int colores[3];

    
   
   for(int j = 0; j < 2; j++){

        colores[0] = 1;
        colores[1] = 0;
        colores[2] = 0;
        glPushMatrix();
        glTranslatef(j == 0 ? -5:5, -10, -30);
        glRotatef(110, 1, 0, 0);
        glRotatef(45, 0, 0, 1);
        DibujaCilindro(0, 0, 0, 1, 30, 6, 4, colores);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(j == 0 ? -5:5, -2, -32);
        glRotatef(110, 1, 0, 0);
        glRotatef(45, 0, 0, 1);
        DibujaCilindro(0, 0, 0, .5, 35, 6, 4, colores);
        glPopMatrix();

        for (int i = 0; i < 3; i++){
           glPushMatrix();
           glTranslatef(j == 0 ? -5:5, i == 0 ? -2 : i == 1 ? 8 : 18, i == 0 ? -32 : i == 1 ? -28 : -25);
           glRotatef(225, 1, 0, 0);
           glRotatef(45, 0, 0, 1);
           DibujaCilindro(0, 0, 0, .5, 5, 6, 4, colores);
           glPopMatrix();
        }

        for(int i = 0; i < 6; i++){

            glPushMatrix();
            if(i == 0) glTranslatef(j == 0 ? -5:5, 18, -20);
            if(i == 1) glTranslatef(j == 0 ? -4:4, 18, -20);
            if(i == 2) glTranslatef(j == 0 ? -3:3, 18, -20);
            if(i == 3) glTranslatef(j == 0 ? -2:2, 18, -20);
            if(i == 4) glTranslatef(j == 0 ? -1:1, 18, -20);
            if(i == 5) glTranslatef(0, 18, -20);
            //if(i == 3) glTranslatef(j == 0 ? -:5, 31, -20);
            glRotatef(180, 1, 0, 0);
            glRotatef(45, 0, 0, 1);
            DibujaCilindro(0, 0, 0, 1, 15, 6, 4, colores);
            glPopMatrix();
        }
        for(int i = 0; i < 4; i++){ 

            colores[0] = 0;
            colores[1] = 0;
            colores[2] = 1;

            glPushMatrix();
            if(i == 0) glTranslatef(j == 0 ? -5:5, -2, -28.0);
            if(i == 1) glTranslatef(j == 0 ? -5:5,  3, -26.0);
            if(i == 2) glTranslatef(j == 0 ? -5:5,  8, -24.0);
            if(i == 3) glTranslatef(j == 0 ? -5:5, 13, -22.0);
            glRotatef(180, 1, 0, 0);
            glRotatef(j == 0 ? -90:90, 0, 1, 0);
            DibujaCilindro(0, 0, 0, .5, 5, 6, 4, colores);
            glPopMatrix();
        }
        colores[0] = 1;
        colores[1] = 0;
        colores[2] = 0;

        glPushMatrix();
        glTranslatef(j == 0 ? -5:5, 31, -20);
        glRotatef(180, 1, 0, 0);
        glRotatef(45, 0, 0, 1);
        DibujaCilindro(0, 0, 0, .5, 15, 6, 4, colores);
        glPopMatrix();

        

        glPushMatrix();
        glTranslatef(j == 0 ? -5:5, 25, -22.5);
        glRotatef(180, 1, 0, 0);
        glRotatef(45, 0, 0, 1);
        DibujaCilindro(0, 0, 0, .5, 17.5, 6, 4, colores);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(j == 0 ? -5:5, 31, -5);
        glRotatef(270, 1, 0, 0);
        glRotatef(45, 0, 0, 1);
        DibujaCilindro(0, 0, 0, .5, 13, 6, 4, colores);
        glPopMatrix();

        for(int i = 0; i < 5; i++){ 

            glPushMatrix();
            if(i == 0) glTranslatef(j == 0 ? -5:5, 18.0, -5.0);
            if(i == 1) glTranslatef(j == 0 ? -5:5, 18.5, -4.5);
            if(i == 2) glTranslatef(j == 0 ? -5:5, 19.0, -4.0);
            if(i == 3) glTranslatef(j == 0 ? -5:5, 19.5, -3.5);
            if(i == 4) glTranslatef(j == 0 ? -5:5, 20.0, -3.0);
            glRotatef(225, 1, 0, 0);
            glRotatef(45, 0, 0, 1);
            DibujaCilindro(0, 0, 0, .5, 35, 6, 4, colores);
            glPopMatrix();
        }
        for(int i = 1; i < 6; i++){ 

            colores[0] = 0;
            colores[1] = 0;
            colores[2] = 1;

            glPushMatrix();
            if(i == 0) glTranslatef(j == 0 ? -5:5, 18.0, -5.0);
            if(i == 1) glTranslatef(j == 0 ? -4:4, 18.0, -5.0);
            if(i == 2) glTranslatef(j == 0 ? -3:3, 18.0, -5.0);
            if(i == 3) glTranslatef(j == 0 ? -2:2, 18.0, -5.0);
            if(i == 4) glTranslatef(j == 0 ? -1:1, 18.0, -5.0);
            if(i == 5) glTranslatef(0, 18.0, -5.0);
            glRotatef(225, 1, 0, 0);
            glRotatef(45, 0, 0, 1);
            DibujaCilindro(0, 0, 0, 1, 35, 6, 4, colores);
            glPopMatrix();
        }
        colores[0] = 1;
        colores[1] = 0;
        colores[2] = 0;
        for(int i = 0; i < 6; i++){ 

            glPushMatrix();
            if(i == 0) glTranslatef(j == 0 ? -5:5, -4.5, 19.5);
            if(i == 1) glTranslatef(j == 0 ? -5:5, -5.0, 19.5);
            if(i == 2) glTranslatef(j == 0 ? -5:5, -5.5, 19.5);
            if(i == 3) glTranslatef(j == 0 ? -5:5, -6.0, 19.5);
            if(i == 4) glTranslatef(j == 0 ? -5:5, -6.5, 19.5);
            if(i == 5) glTranslatef(j == 0 ? -5:5, -7.0, 19.5);
            glRotatef(180, 1, 0, 0);
            glRotatef(45, 0, 0, 1);
            DibujaCilindro(0, 0, 0, .5, 7, 6, 4, colores);
            glPopMatrix();
        }



        glPushMatrix();
        glTranslatef(j == 0 ? -5:5, -9.3, 25.0);
        glRotatef(90, 1, 0, 0);
        glRotatef(45, 0, 0, 1);
        DibujaCilindro(0, 0, 0, .5, 2, 6, 4, colores);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(j == 0 ? -5:5, 18, -5);
        glRotatef(225, 1, 0, 0);
        glRotatef(45, 1, 0, 0);
        glRotatef(j == 0 ? 45:-45, 0, 1, 0);
        DibujaCilindro(0, 0, 0, 1, 40, 6, 4, colores);
        glPopMatrix();
   }
    
}
// Funcion que inicializa el programa iniciando el modo de profundidad de OpenGL
void init(void)
{
    glEnable(GL_DEPTH_TEST); 
}



// Funcion que controla las teclas que se presionan.
void keyboardCallbackProc(unsigned char key, int x, int y)
{
    switch (key) {
        case 'x':AngleX+=5; break;
        case 'y':AngleY+=5; break;
        case 'z':AngleZ+=5; break;
        case '+':zoom+=.05; break;
        case '-':zoom-=.05; break;
        
    }
    glutPostRedisplay();
}

// Funcion encargada de controlar el cambio de tamano de la ventana
void reShapeCallbackProc(int w, int h)
{
    if(w<SIZE|| h<SIZE){
        glutReshapeWindow(SIZE,SIZE);   
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, w / h, NEAR_Z, FAR_Z);
    glMatrixMode(GL_MODELVIEW);
}

// Funcion que controla los eventos de dibujo de la aplicacion.
void displayCallbackProc(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, -10, -60);          //Posicion de iniciado        
    glRotatef(AngleX, 1.0, 0.0, 0.0);   //Controla la vista de la camara en X
    glRotatef(AngleY, 0.0, 1.0, 0.0);   //Controla la vista de la camara en Y
    glRotatef(AngleZ, 0.0, 0.0, 1.0);   //Controla la vista de la camara en Z
    glScalef(zoom, zoom, zoom);         //Controla el Zoom
    Display(); 

    glutSwapBuffers();
}

// Funcion principal.
int main(int argc, char *argv[])
{
    cout<<"Instrucciones\n\
    tecla + = aumenta el zoom\n\
    tecla - = disminuye el zoom\n\
    tecla x = angulo X\n\
    tecla y = angulo Y\n\
    tecla z = angulo Z\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SIZE, SIZE);
    glutInitWindowPosition(350, 200);
    glutCreateWindow(" Practica 04 - Escalera");
    init(); 
    glutDisplayFunc(displayCallbackProc);
    glutKeyboardFunc(keyboardCallbackProc);
    glutReshapeFunc(reShapeCallbackProc);
    glutMainLoop();
    return 0;
}
