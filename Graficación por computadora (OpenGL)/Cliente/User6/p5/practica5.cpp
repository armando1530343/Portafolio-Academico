#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#define SIZE 600
#define PI 3.141592654
#define T 5
#include "imageloader.h"


using namespace std;

double zoom = 0.55;    //Valor del zoom de la camara
double AngleX = 40.0;      //Grados de rotacion del eje X
double AngleY = 30.0;    //Grados de rotacion del eje Y
double AngleZ = 0.0;

GLuint *_textureId; //The id of the textura

GLUquadric *quad;

// figura en 3d
void Modelo(float radio, int ancho,  int lados, float *colores, float *colores2, int indice_textura) {
    
     GLfloat X = 0, Y = 0, Z = 0, angle;
    glTranslatef(X,Y,Z);
    GLfloat Puntos[2][500][3];

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId[indice_textura]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);  
    GLfloat IncrementoLado = 1.0;
    GLfloat OffsetLado = 0.0;
    GLfloat SigLado = IncrementoLado;

    int Contador = 0;
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
        Contador = 0;
        for (angle = 0.0f; angle <= (2.0f * PI); angle += (2.0f * PI) / lados) {
            Puntos[i][Contador][0] = radio * sin(angle) + X;
            Puntos[i][Contador][1] = radio * cos(angle) + Y;
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

void llanta(float x, float y, float z){
	glPushMatrix();
    glTranslatef(0,0,0);
    glRotatef(90, 0, 1, 0);
	for(int i = 0; i <= 360; i++){
		if(i % 5 == 0){
			for(int j = 0; j < 3; j++){
				glPushMatrix();
			    glTranslatef(7 * cos(i * PI / 180) + x,7 * sin(i * PI / 180) + y, z + (5*j));
			    glRotatef(90, 1, 0, 0);
			    glRotatef(i, 0, 1, 0);
			    glRotatef(45, 0, 0, 1);
			    Modelo(3, 3, 4, new float[3]{.2,.2,.2}, new float[3]{.2,.2,.2}, 3);
			    glPopMatrix();
			}			
		}
	}
	glPushMatrix();
    glTranslatef(x, y, z+11.5);
    Modelo(5, 13, 20, new float[3]{.7,.7,.7}, new float[3]{.9,.9,.9},4);
    glPopMatrix();

    glPopMatrix();
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
   
   _textureId = new GLuint[T];
    glGenTextures(T, _textureId);

   
   //Image* image = loadBMP("vtr.bmp");
   //Image* image = loadBMP("upv.bmp");
   //TEXTURAS  
   
   image = loadBMP("rojo3.bmp");
   loadTexture(image, _textureId[0]);
   image = loadBMP("rojo5.bmp");
   loadTexture(image, _textureId[1]);
   image = loadBMP("ferrari1.bmp");
   loadTexture(image, _textureId[2]);
   image = loadBMP("llanta1.bmp");
   loadTexture(image, _textureId[3]);
   image = loadBMP("metal.bmp");
   loadTexture(image, _textureId[4]);

   delete image;

}


// Funcion que controla los eventos de dibujo de la aplicacion.
void display(void)
{
	glEnable(GL_DEPTH_TEST); 
	glClearColor(0.1,0.1,0.1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -60);//Posicion de iniciado        
    glRotatef(AngleX, 1.0, 0.0, 0.0);//Controla la vista de la camara en X
    glRotatef(AngleY, 0.0, 1.0, 0.0);//Controla la vista de la camara en Y
    glRotatef(AngleZ, 0.0, 0.0, 1.0);//Controla la vista de la camara en Z
    glScalef(zoom, zoom, zoom);//Controla el Zoom

    //llanta(0,0,0);
    //llanta(0,0,-30);	
    int i, j, k;

    glPushMatrix();
	glTranslatef(0,0,50);
    
    //base frontal del coche
    glPushMatrix();
	glTranslatef(0,-2,0);
	glRotatef(0, 1, 0, 0);

    glPushMatrix();
	glTranslatef(0,0,0);
	glRotatef(-5, 1, 0, 0);
    for(i = 0; i < 5; i++){
    	glPushMatrix();
		glTranslatef(0,0,i*-14);
		glRotatef(90, 1, 0, 0);
		glRotatef(45, 0, 0, 1);
		Modelo(10, 6, 4, new float[3]{.6,.0,.0}, new float[3]{.8,.0,.0}, 0);
		glPopMatrix();	
    }
    glPopMatrix();
    

    //soportes frontales
    for(i = 0; i < 2; i++){
	    glPushMatrix();
		glTranslatef(i == 0 ? -5 : 6,-3,2);
		glRotatef(90, 0, 1, 0);
		glRotatef(45, 0, 0, 1);
		Modelo(5, 1, 4, new float[3]{.7,.7,.7}, new float[3]{.9,.9,.9}, 4);
		glPopMatrix();
	}

	//defensa de coche
	for(i = 0; i < 6; i++){
	    glPushMatrix();
		glTranslatef(-25 + (i*10),-7,4);
		glRotatef(90, 1, 0, 0);
		glRotatef(45, 0, 0, 1);
		Modelo(8, 1, 4, new float[3]{.6,.6,.6}, new float[3]{.8,.8,.8}, 4);
		glPopMatrix();
		if(i == 0 || i == 5){
			glPushMatrix();
			glTranslatef(-25 + (i*10),-7,-7);
			glRotatef(90, 1, 0, 0);
			glRotatef(45, 0, 0, 1);
			Modelo(8, 1, 4, new float[3]{.6,.6,.6}, new float[3]{.8,.8,.8}, 4);
			glPopMatrix();
		}
	}
	glPopMatrix();

	//Cabina
    for(i = 0; i < 2; i++){
    	for(j = 0; j < 2; j++){
		    glPushMatrix();
			glTranslatef(i == 0 ? -5 : 6,-6, j == 0 ? -84 : -110);
			glRotatef(90, 1, 0, 0);
			glRotatef(45, 0, 0, 1);
			Modelo(30, 4, 4, new float[3]{.6,.0,.0}, new float[3]{.8,.0,.0}, 4);
			glPopMatrix();
		}
	}

	for(i = 0; i < 2; i++){
	    for(j = 0; j < 5; j++){
		    glPushMatrix();
			glTranslatef(i == 0 ? -19 : 20,-2, -70 - (j*13.5));
			glRotatef(90, 1, 0, 0);
			glRotatef(45, 0, 0, 1);
			Modelo(10, 4, 4, new float[3]{.7,.0,.0}, new float[3]{.9,.0,.0}, 0);
			glPopMatrix();
		}
	}
	for(i = 0; i < 5; i++){
	    glPushMatrix();
		glTranslatef(-19 + (i*9.8),-2, -70);
		glRotatef(90, 1, 0, 0);
		glRotatef(45, 0, 0, 1);
		Modelo(10, 4, 4, new float[3]{.7,.0,.0}, new float[3]{.9,.0,.0}, 0);
		glPopMatrix();
	}
	for(i = 0; i < 5; i++){
	    glPushMatrix();
		glTranslatef(-16 + (i*8.3),-2, -112);
		glRotatef(90, 1, 0, 0);
		glRotatef(45, 0, 0, 1);
		Modelo(14, 4, 4, new float[3]{.7,.0,.0}, new float[3]{.9,.0,.0}, 0);
		glPopMatrix();
	}

	for(i = 0; i < 3; i++){
		for(j = 0; j < 2; j++){
		    glPushMatrix();
			glTranslatef(j == 0 ? -32 : 33,-6, -80 - (i*10));
			glRotatef(90, 1, 0, 0);
			glRotatef(45, 0, 0, 1);
			Modelo(8, 12, 4, new float[3]{.5,.0,.0}, new float[3]{7,.0,.0}, 2);
			glPopMatrix();
		}
	}

	//base triangulo
	for(i = 0; i < 5; i++){
	    glPushMatrix();
		glTranslatef(0,8, -100 - (i*6));
		Modelo(15, 8, 3, new float[3]{.7,.0,.0}, new float[3]{.9,.0,.0}, 2);
		glPopMatrix();
	}
	for(i = 0; i < 6; i++){
	    glPushMatrix();
		glTranslatef(-25 + (i*10),20,-138);
		glRotatef(90, 1, 0, 0);
		glRotatef(45, 0, 0, 1);
		Modelo(8, 1, 4, new float[3]{.6,.6,.6}, new float[3]{.8,.8,.8}, 4);
		glPopMatrix();
		if(i == 0 || i == 5){
			glPushMatrix();
			glTranslatef(-25 + (i*10),20,-145);
			glRotatef(90, 1, 0, 0);
			glRotatef(45, 0, 0, 1);
			Modelo(8, 1, 4, new float[3]{.6,.6,.6}, new float[3]{.8,.8,.8}, 4);
			glPopMatrix();
		}
	}

	llanta(30,-5,20);
	llanta(30,-5,-30);
	
	glPushMatrix();
	glTranslatef(20,-3,-30);
	glRotatef(90, 0, 1, 0);
	Modelo(1, 50, 20, new float[3]{.2,.2,.2}, new float[3]{.4,.4,.4}, 4);
	glPopMatrix();

	llanta(120,-2,30);
	llanta(120,-2,-40);
	

	glPopMatrix();


    

    
    glFlush();

    glutSwapBuffers();
}

// Funcion que controla las teclas que se presionan.
void teclado(unsigned char key, int x, int y)
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
    glutCreateWindow("Carro");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}