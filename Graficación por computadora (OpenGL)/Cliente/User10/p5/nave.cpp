#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#define SIZE 600
#define PI 3.141592654


#include "imageloader.h"


using namespace std;

double zoom = 0.2;    //Valor del zoom de la camara
double AngleX = 40.0;      //Grados de rotacion del eje X
double AngleY = 30.0;    //Grados de rotacion del eje Y
double AngleZ = 0.0;
GLuint *_textureId;

int Texturas = 3;
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
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5, 0.5, 0.5, 0.5);
    Image* image;
    _textureId = new GLuint[Texturas];
    glGenTextures(Texturas, _textureId);
    image = loadBMP("rojo2.bmp");
    loadTexture(image, _textureId[0]);

    image= loadBMP("gris2.bmp");
    loadTexture(image, _textureId[1]);

    image= loadBMP("verde1.bmp");
    loadTexture(image, _textureId[2]);

    delete image;

}

// figura en 3d
void figura3D(float radio, float radio2, int ancho,  int lados, int textura) {
    GLfloat X = 0, Y = 0, Z = 0, angle;
    glTranslatef(X,Y,Z);
    GLfloat Puntos[2][500][3];
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId[textura]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);  
    GLfloat IncrementoLado = 1.0;
    GLfloat OffsetLado = 0.0;
    GLfloat SigLado = IncrementoLado;
    int Contador = 0;
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
        glColor3f(1,1,1);
        Contador = 0;
        for (angle = 0.0f; angle <= (2.0f * PI); angle += (2.0f * PI) / lados) {
            Puntos[i][Contador][0] = (i == 0 ? radio : radio2) * sin(angle) + X;
            Puntos[i][Contador][1] = (i == 0 ? radio : radio2) * cos(angle) + Y;
            Puntos[i][Contador][2] = Z;   
            glTexCoord2f( Contador == 0 || Contador == 2 ? OffsetLado :  SigLado, Contador <= 1 ? 1.0f : 0.0f); 
            glVertex3f(Puntos[i][Contador][0], Puntos[i][Contador][1], Puntos[i][Contador][2]);
            Contador++;
        }
        glEnd();
        Z -= ancho;
    }
    for (Contador = 0; Contador < lados; Contador++) {
        glBegin(GL_POLYGON);
        
        glColor3f(1,1,1);
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

        OffsetLado = SigLado;
        SigLado += IncrementoLado;
    }
}


// Funcion que controla los eventos de dibujo de la aplicacion.
void display(void)
{
	glEnable(GL_DEPTH_TEST); 
	glClearColor(.3,.3,.3,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -60);//Posicion de iniciado        
    glRotatef(AngleX, 1.0, 0.0, 0.0);//Controla la vista de la camara en X
    glRotatef(AngleY, 0.0, 1.0, 0.0);//Controla la vista de la camara en Y
    glRotatef(AngleZ, 0.0, 0.0, 1.0);//Controla la vista de la camara en Z
    glScalef(zoom, zoom, zoom);//Controla el Zoom

    //ALAS
    for(int i = 0; i < 2; i++){
	    for(int j = 0; j < 100; j++){
	    	glPushMatrix();
		    glTranslatef(i == 0 ? -100 : 100,-50,j*.8);
		    glRotatef(90,1,0,0);
		    glRotatef(45,0,0,1);
		    figura3D(25.0-(j*.25), 20.0-(j*.2), 5, 4, 0);
		    glPopMatrix();
	    }
	    for(int j = 0; j < 100; j++){
		    glPushMatrix();
		    glTranslatef(i == 0 ? -100 : 100,-50,-j*.5);
		    glRotatef(90,1,0,0);
		    glRotatef(45,0,0,1);
		    figura3D(25.0-(j*.25), 20.0-(j*.2), 5, 4, 0);
		    glPopMatrix();
	    }
	}

    for(int i = 0; i < 2; i++){
    	for(int j = 0; j < 10; j++){
    		glPushMatrix();
			glTranslatef((i == 0 ? -j : j) *10,-49,0);
			glRotatef(90,1,0,0);
			glRotatef(45,0,0,1);
			figura3D(20, 20, 3, 4, 0);
			glPopMatrix();
    	}
    }

    //CUERPO DE LA NAVE
    for(int i = 0; i < 100; i++){
    	glPushMatrix();
		glTranslatef(0,-50,i*.5);
		glRotatef(90,1,0,0);
		glRotatef(45,0,0,1);
		figura3D(60.0-(i*.5), 55.0-(i*.45), 5, 4, 1);
		glPopMatrix();
    }
    //CUERPO VERDE
    for(int j = 0; j < 2; j++){
    	for(int i = 0; i < 100; i++){
	    	glPushMatrix();
			glTranslatef(0,j == 0 ? -45: -52,-11 + i*.7);
			glRotatef(90,1,0,0);
			glRotatef(45,0,0,1);
			figura3D((j == 0 ? 40.0-(i*.4) : 35-(i*.35)), (j == 0 ? 35.0-(i*.35) : 40-(i*.4)), 5, 4, 2);
			glPopMatrix();
	    }
    }
    for(int j = 0; j < 100; j++){
    	glPushMatrix();
		glTranslatef(0, -45, -j*1.4);
		glRotatef(90,1,0,0);
		glRotatef(45,0,0,1);
		figura3D(25-(j*.25), 25-(j*.25), 5, 4, 2);
		glPopMatrix();
    }

    for(int i = 0; i < 2; i++){
    	for(int j = 0; j < 100; j++){
	    	glPushMatrix();
			glTranslatef(i == 0 ?-32 : 32, -45, -j);
			glRotatef(90,1,0,0);
			glRotatef(45,0,0,1);
			figura3D(10-(j*.1), 10-(j*.1), 5, 4, 2);
			glPopMatrix();
	    }
    }

    for(int i = 0; i < 2; i++){
    	for(int j = 0; j < 100; j++){
	    	glPushMatrix();
			glTranslatef(i == 0 ?-15 : 15, -40, -40-(j*.4));
			glRotatef(90,1,0,0);
			glRotatef(45,0,0,1);
			figura3D(8-(j*.08), 8-(j*.08), 5, 4, 0);
			glPopMatrix();
	    }
    }
	//--------------------------------

    glPushMatrix();
	glTranslatef(0,-48,55);
	figura3D(20, 20, 30, 4, 1);
	glPopMatrix();

    glPushMatrix();
	glTranslatef(0,-48,60);
	figura3D(10, 10, 5, 20, 0);
	glPopMatrix();

	for(int i = 0; i < 2; i++){
    	for(int j = 0; j < 100; j++){
    		glPushMatrix();
			glTranslatef(i == 0 ? -37 : 37,-49,j*.8);
			glRotatef(90,1,0,0);
			glRotatef(45,0,0,1);
			figura3D(7 - (j*.07), 7 - (j*.07), 3, 4, 0);
			glPopMatrix();
    	}
    }



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
    glutInitWindowPosition(700, 10);
    glutCreateWindow("NAVE");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyInput);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}