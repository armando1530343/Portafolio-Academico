#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#define SIZE 600
#define PI 3.141592654
#define TotalTexturas 5
#include "imageloader.h"


/*
Desarrollo Experimental:

*/


using namespace std;

double zoom = 0.2;
double AngleX = 20.0;
double AngleY = -40.0;
double AngleZ = 0.0;
GLuint *_textureId;

// figura en 3d
void figura3D(float radio1, float radio2, int ancho,  int lados, float *colores, float *colores2, int tex) {
    GLfloat X = 0, Y = 0, Z = 0, angle;
    glTranslatef(X,Y,Z);
    GLfloat Puntos[2][500][3];

    //TEXTURAS-------------
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId[tex]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);  
    GLfloat IncrementoLado = 1.0;
    GLfloat OffsetLado = 0.0;
    GLfloat SigLado = IncrementoLado;
    //----------------------------

    int Contador = 0;
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
        glColor3f(colores2[0], colores2[1], colores2[2]);
        Contador = 0;
        for (angle = 0.0f; angle <= (2.0f * PI); angle += (2.0f * PI) / lados) {
            Puntos[i][Contador][0] = (i == 0 ? radio1 : radio2) * sin(angle) + X;
            Puntos[i][Contador][1] = (i == 0 ? radio1 : radio2) * cos(angle) + Y;
            Puntos[i][Contador][2] = Z; 

            glTexCoord2f( Contador == 0 || Contador == 2 ? OffsetLado :  SigLado, Contador <= 1 ? 1.0f : 0.0f); 
            glVertex3f(Puntos[i][Contador][0], Puntos[i][Contador][1], Puntos[i][Contador][2]);
            Contador++;
        }
        glEnd();
        Z -= ancho;
    }

    IncrementoLado = 1.0/lados;
    OffsetLado = 0.0;
    SigLado = IncrementoLado;


    float *color = colores;
    for (Contador = 0; Contador < lados; Contador++) {
        glBegin(GL_POLYGON);
        
        glColor3f(color[0], color[1], color[2]);
        int Temporal = 0;
        if (Contador == (int) (lados - 1))
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

        if(Contador < lados/2){
            color[0] -= colores[0]/lados*2;
            color[1] -= colores[1]/lados*2;
            color[2] -= colores[2]/lados*2;
        }
        else{
            color[0] += colores[0]/lados*2;
            color[1] += colores[1]/lados*2;
            color[2] += colores[2]/lados*2;
        }
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
   image = loadBMP("pared3.bmp");
   loadTexture(image, _textureId[0]);

   image= loadBMP("piso2.bmp");
   loadTexture(image, _textureId[1]);

   image= loadBMP("oxido2.bmp");
   loadTexture(image, _textureId[2]);

   image= loadBMP("metal.bmp");
   loadTexture(image, _textureId[3]);

   image= loadBMP("oxido1.bmp");
   loadTexture(image, _textureId[4]);

   delete image;

}


// Funcion que controla los eventos de dibujo de la aplicacion.
void display(void)
{
	glEnable(GL_DEPTH_TEST); 
	glClearColor(0.0,0.0,0.0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -60);//Posicion de iniciado        
    glRotatef(AngleX, 1.0, 0.0, 0.0);//Controla la vista de la camara en X
    glRotatef(AngleY, 0.0, 1.0, 0.0);//Controla la vista de la camara en Y
    glRotatef(AngleZ, 0.0, 0.0, 1.0);//Controla la vista de la camara en Z
    glScalef(zoom, zoom, zoom);//Controla el Zoom

    float colores1[3], colores2[3];

    /*glPushMatrix();
    glTranslatef(0,.0,0);
    //glScalef(.59,.59,.59);
    glRotatef(90.0,1,0,0);
    glutSolidTorus(.1,1.0,20,20);
    glPopMatrix();*/

    //PARED TEXTURA LADRILLO
    glPushMatrix();
    glTranslatef(0,-50,-60);
    //glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(150, 150, 50, 4, colores1, colores2,0);
    glPopMatrix();

    //PISO TEXTURA LADRILLO
    glPushMatrix();
    glTranslatef(0,-153,-60);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(150, 150, 3, 4, colores1, colores2,1);
    glPopMatrix();
    
    //BASE POSTE
    glPushMatrix();
    glTranslatef(0,-150,0);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(14, 14, 3, 6, colores1, colores2, 2);
    glPopMatrix();

    for(int i = 0; i < 2; i++){
        glPushMatrix();
        glTranslatef(0,i == 0 ? -148 : -144,0);
        glRotatef(90,1,0,0);
        glRotatef(45,0,0,1);
        colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    	colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
        figura3D(8, 10, 2, 100, colores1, colores2, 2);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,i == 0 ? -146 : -142,0);
        glRotatef(90,1,0,0);
        glRotatef(45,0,0,1);
        colores1[0] = .9; colores1[1] = .9; colores1[2] = .9;
    	colores2[0] = .7; colores2[1] = .7; colores2[2] = .7;
        figura3D(10, 8, 2, 100, colores1, colores2, 2);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(0,-140,0);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(8, 6, 40, 100, colores1, colores2, 4);
    glPopMatrix();

    for(int i = 0; i < 2; i++){
        glPushMatrix();
        glTranslatef(0,i == 0 ? -110 : -104,0);
        glRotatef(90,1,0,0);
        glRotatef(45,0,0,1);
        colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    	colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
        figura3D(6, 8, 2, 100, colores1, colores2, 2);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,i == 0 ? -108 : -102,0);
        glRotatef(90,1,0,0);
        glRotatef(45,0,0,1);
        colores1[0] = .9; colores1[1] = .9; colores1[2] = .9;
    	colores2[0] = .7; colores2[1] = .7; colores2[2] = .7;
        figura3D(8, 6, 2, 100, colores1, colores2, 2);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(0,-100,0);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(5, 2.5, 55, 100, colores1, colores2, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-45,0);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(2.5, 4.5, 2, 100, colores1, colores2, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-43,0);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .9; colores1[1] = .9; colores1[2] = .9;
    colores2[0] = .7; colores2[1] = .7; colores2[2] = .7;
    figura3D(4.5, 2.5, 2, 100, colores1, colores2, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-41,0);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(2.5, 2.5, 55, 100, colores1, colores2, 3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,14,0);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(4, 6, 5, 100, colores1, colores2, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,19,0);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(8, 12, 4, 6, colores1, colores2, 3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,23,0);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(8, 8, 4, 6, colores1, colores2, 3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,23,0);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(1.5, 1.5, 18, 100, colores1, colores2, 3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,41,0);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(2.5, .2, 5, 100, colores1, colores2, 3);
    glPopMatrix();

    //LAMPARA

    glPushMatrix();
    glTranslatef(3,23,10);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(1, 1, 30, 4, colores1, colores2, 3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,23,3);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(1, 1, 30, 4, colores1, colores2, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8,23,-7);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(1, 1, 30, 4, colores1, colores2, 3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3,23,-10);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(1, 1, 30, 4, colores1, colores2, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10,23,-3);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(1, 1, 30, 4, colores1, colores2, 3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8,23,7);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(1, 1, 30, 4, colores1, colores2, 4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,53,0);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(13, 8, 4, 6, colores1, colores2, 3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,57,0);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(8, 5, 4, 100, colores1, colores2, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,61,0);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    colores1[0] = .7; colores1[1] = .7; colores1[2] = .7;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;
    figura3D(4, 2, 4, 100, colores1, colores2, 4);
    glPopMatrix();
    
    
    glFlush();

    glutSwapBuffers();
}

// Funcion que controla las teclas que se presionan.
void keyInput(unsigned char key, int x, int y)
{
    switch (key) {
        case 'x':
        	AngleX+=5; 
        	break;
        case 'y':
        	AngleY+=5; 
        	break;
        case 'z':
        	AngleZ+=5; 
        	break;
        case '+':
        	zoom+=.05; 
        	break;
        case '-':
        	zoom-=.05; 
        	break;
        
    }
    glutPostRedisplay();
}

//ventana
void reshape(int w, int h)
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
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SIZE, SIZE);
    glutInitWindowPosition(350, 10);
    glutCreateWindow("base");
    init(); 
    glutDisplayFunc(display);
    glutKeyboardFunc(keyInput);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}