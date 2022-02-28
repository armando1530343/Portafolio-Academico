#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>

#define SIZE 650 //Ventana
#define PI 3.1416//Valor de PI
#define TotalTexturas 2


#include "imageloader.h"

double zoom = 0.5;    //Valor del zoom de la camara
double AngleX = 0.0;      //Grados de rotacion del eje X
double AngleY = 0.0;    //Grados de rotacion del eje Y
double AngleZ = 0.0;
using namespace std;

GLuint *_textureId;


// Funcion que dibuja una figura en 3d
void DibujaCilindro(int X, int Y, int Z, float rad1, float rad2, int anchura,  GLfloat LADOS, float colores[], int t) {
    GLfloat x = X, y = Y, z = Z, angle;
    glTranslatef(x, y, z);
    GLfloat radio;
    GLfloat Puntos[2][500][3];
    glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, _textureId[t]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glColor3f(1.0f, 1.0f, 1.0f);  
   
   GLfloat IncrementoLado = 1.0;
   GLfloat OffsetLado = 0.0;
   GLfloat SigLado = IncrementoLado;
    int Contador = 0;
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
        glColor3f(.05, .05, .05);
        radio = i == 0 ? rad1 : rad2;
        Contador = 0;
        for (angle = 0.0f; angle <= (2.0f * PI); angle += (2.0f * PI) / LADOS) {
            Puntos[i][Contador][0] = radio * sin(angle) + X;
            Puntos[i][Contador][1] = radio * cos(angle) + Y;
            Puntos[i][Contador][2] = Z; 
            glTexCoord2f(SigLado, 1.0f);  
            glVertex3f(Puntos[i][Contador][0], Puntos[i][Contador][1], Puntos[i][Contador][2]);
            Contador++;
            OffsetLado = SigLado;
            SigLado += IncrementoLado;
        }
        glEnd();
        Z -= anchura;
    }
    IncrementoLado = 1.0/LADOS;
       OffsetLado = 0.0;
       SigLado = IncrementoLado;
    for (Contador = 0; Contador < LADOS; Contador++) {
        glBegin(GL_POLYGON);
        
        glColor3f(colores[0], colores[1], colores[2]);
        int Temporal = 0;
        if (Contador == (int) (LADOS - 1))
            Temporal = 0;
        else
            Temporal = Contador + 1;
        glTexCoord2f(OffsetLado, 1.0f);
        glVertex3f(Puntos[0][Contador][0], Puntos[0][Contador][1], Puntos[0][Contador][2]);
        glTexCoord2f(SigLado, 1.0f);
        glVertex3f(Puntos[0][Temporal][0], Puntos[0][Temporal][1], Puntos[0][Temporal][2]);
        glTexCoord2f(SigLado, 0.0f);
        glVertex3f(Puntos[1][Temporal][0], Puntos[1][Temporal][1], Puntos[1][Temporal][2]);
        glTexCoord2f(OffsetLado, 0.0f);
        glVertex3f(Puntos[1][Contador][0], Puntos[1][Contador][1], Puntos[1][Contador][2]);
        glEnd();
        OffsetLado = SigLado;
      SigLado += IncrementoLado;
    }
}



GLuint loadTexture(Image* image, GLuint texture) {
   glBindTexture(GL_TEXTURE_2D, texture);
   glTexImage2D(GL_TEXTURE_2D,
             0,
             GL_RGB,
             image->width, image->height,
             0,
             GL_RGB,
             GL_UNSIGNED_BYTE,
             image->pixels);
   return 0;
}

static void init(void)
{
   //DefinirMisColores ();
   
   glEnable(GL_DEPTH_TEST);
   //glShadeModel(GL_FLAT);
   glClearColor(0.5, 0.5, 0.5, 0.5);
   Image* image;
   
   _textureId = new GLuint[TotalTexturas];
    glGenTextures(TotalTexturas, _textureId);

   
   //Image* image = loadBMP("vtr.bmp");
   //Image* image = loadBMP("upv.bmp");
   //TEXTURAS  
   image = loadBMP("negro.bmp");
   loadTexture(image, _textureId[0]);

   image= loadBMP("gris.bmp");
   loadTexture(image, _textureId[1]);

   


   delete image;

}


void Display(void) {

    float colores[3];

    

    int alt = 60;

    //pesas de la mancuerna
    for (int i = 0; i < 2; i++){

        if(i > 0) alt = 0;
        colores[0] = .1; colores[1] = .1;colores[2] = .1;
        glPushMatrix();
        glTranslatef(0,alt,0);
        glRotatef(90, 1, 0, 0);
        DibujaCilindro(0, 0, 0, 15, 8, 5, 6, colores,0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,alt-13,0);
        glRotatef(90, 1, 0, 0);
        DibujaCilindro(0, 0, 0, 8, 15, 5, 6, colores,0);
        glPopMatrix();

        colores[0] = .07; colores[1] = .07;colores[2] = .07;

        glPushMatrix();
        glTranslatef(0,alt-8,0);
        glRotatef(90, 1, 0, 0);
        DibujaCilindro(0, 0, 0, 15, 15, 8, 6, colores,0);
        glPopMatrix();
    }

    colores[0] = .5; colores[1] = .5;colores[2] = .5;

    //tubo de la mancuerna

    glPushMatrix();
    glTranslatef(0,44,0);
    glRotatef(90, 1, 0, 0);
    DibujaCilindro(0, 0, 0, 6, 6, 3, 6, colores, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,18, 0);
    glRotatef(90, 1, 0, 0);
    DibujaCilindro(0, 0, 0, 5, 5, 16, 6, colores, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,5,0);
    glRotatef(90, 1, 0, 0);
    DibujaCilindro(0, 0, 0, 6, 6, 3, 6, colores, 1);
    glPopMatrix();

    colores[0] = .4; colores[1] = .4;colores[2] = .4;

    glPushMatrix();
    glTranslatef(0,34,0);
    glRotatef(90, 1, 0, 0);
    DibujaCilindro(0, 0, 0, 5, 3, 10, 6, colores, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,8,0);
    glRotatef(90, 1, 0, 0);
    DibujaCilindro(0, 0, 0, 3, 5, 10, 6, colores, 1);
    glPopMatrix();
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
    gluPerspective(60.0, w / h, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

// Funcion que controla los eventos de dibujo de la aplicacion.
void displayCallbackProc(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, -10, -60);//Posicion de iniciado        
    glRotatef(AngleX, 1.0, 0.0, 0.0);//Controla la vista de la camara en X
    glRotatef(AngleY, 0.0, 1.0, 0.0);//Controla la vista de la camara en Y
    glRotatef(AngleZ, 0.0, 0.0, 1.0);//Controla la vista de la camara en Z
    glScalef(zoom, zoom, zoom);//Controla el Zoom
    Display(); 

    glutSwapBuffers();
}

// Funcion principal.
int main(int argc, char *argv[])
{
    cout<<"Teclas de Control: 'X' 'Y' 'Z' '+' '-'"<<endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SIZE, SIZE);
    glutInitWindowPosition(350, 200);
    glutCreateWindow(" Practica 05_ Mancuerna con texturas");
    init(); 
    glutDisplayFunc(displayCallbackProc);
    glutKeyboardFunc(keyboardCallbackProc);
    glutReshapeFunc(reShapeCallbackProc);
    glutMainLoop();
    return 0;
}
