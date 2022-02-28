//****************************************************************************************/
// Desplegado de un CILINDRO
/****************************************************************************************/
	
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#define GL_PI 3.1415f

#define WIDTH 1000	
#define HEIGTH 600 
#define NEAR_Z 1.0
#define FAR_Z 100.0	

#define TAM_ESC1 3
#define TAM_ESC2 10
#define TotalTexturas 6

#include "imageloader.h"

int retardo = 100;

float anguloX = 0.0;	//angulo de la camara en x	
float anguloY = -90.0;//angulo de la camara en y
float anguloZ = 0.0;//angulo de la camara en z

int giraBase = -90;
int moverBrazo = -30;
int moverCoca;

double moverCoca2 = -3.9;


using namespace std;


GLuint *_textureId;



void writenBitmapString(void *font, char *string)
{
	char *c;
	for(c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}


double zoom = 1;
 

//Dibujar cilindro
void Cilindro (int X, int Y, int Z, GLfloat LADOS, GLfloat z1, GLfloat z2, GLfloat radio1, GLfloat radio2, int tex)
{
   GLfloat x, y, z, angle;
   GLfloat radio;
   int Contador = 0;

   GLfloat Puntos1[40][3];
   GLfloat Puntos2[40][3];


   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, _textureId[tex]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glColor3f(1.0f, 1.0f, 1.0f);  
   
   GLfloat IncrementoLado = 1.0;
   GLfloat OffsetLado = 0.0;
   GLfloat SigLado = IncrementoLado;



   glBegin(GL_POLYGON); 

   Contador = 0;
   
   for(angle = 0.0f; angle <= (2.0f*GL_PI); angle += (2.0f*GL_PI)/LADOS)
   {
      glColor3f(1.0,1.0,1.0);
      Puntos1[Contador][0] = radio1*sin(angle)+X;
      Puntos1[Contador][1] = radio1*cos(angle)+Y;
      Puntos1[Contador][2] = z1;      
      glTexCoord2f(SigLado, 1.0f);     
      glVertex3f(Puntos1[Contador][0], Puntos1[Contador][1], Puntos1[Contador][2]);          
      Contador++;
      OffsetLado = SigLado;
      SigLado += IncrementoLado;
   }
   glEnd();
   glBegin(GL_POLYGON); 


   IncrementoLado = 1.0;
   OffsetLado = 0.0;
   SigLado = IncrementoLado;
   Contador = 0;
   for(angle = 0.0f; angle <= (2.0f*GL_PI); angle += (2.0f*GL_PI)/LADOS)
   {
      glColor3f(1.0,1.0,1.0);
      Puntos2[Contador][0] = radio2*sin(angle)+X;
      Puntos2[Contador][1] = radio2*cos(angle)+Y;
      Puntos2[Contador][2] = z2;     
      glTexCoord2f(SigLado, 0.0f);     
      glVertex3f(Puntos2[Contador][0], Puntos2[Contador][1], Puntos2[Contador][2]);          
      Contador++;
      OffsetLado = SigLado;
      SigLado += IncrementoLado;
   }
   glEnd();

   IncrementoLado = 1.0/LADOS;
   OffsetLado = 0.0;
   SigLado = IncrementoLado;   
   for (Contador = 0; Contador<LADOS; Contador++)
   {
      glColor3f(1.0,1.0,1.0);
      glBegin(GL_POLYGON);
      int Temporal = 0;
      if (Contador==(int) (LADOS-1))
         Temporal = 0;
      else
         Temporal = Contador+1;
      glTexCoord2f(OffsetLado, 1.0f);
      glVertex3f(Puntos1[Contador][0], Puntos1[Contador][1], Puntos1[Contador][2]);  
      glTexCoord2f(SigLado, 1.0f); 
      glVertex3f(Puntos1[Temporal][0], Puntos1[Temporal][1], Puntos1[Temporal][2]); 
      glTexCoord2f(SigLado, 0.0f); 
      glVertex3f(Puntos2[Temporal][0], Puntos2[Temporal][1], Puntos2[Temporal][2]); 
      glTexCoord2f(OffsetLado, 0.0f); 
      glVertex3f(Puntos2[Contador][0], Puntos2[Contador][1], Puntos2[Contador][2]);       
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
   image = loadBMP("tex1.bmp");
   loadTexture(image, _textureId[0]);

   image= loadBMP("tex2.bmp");
   loadTexture(image, _textureId[1]);

   image= loadBMP("tex3.bmp");
   loadTexture(image, _textureId[2]);

   image= loadBMP("tex4.bmp");
   loadTexture(image, _textureId[3]);

   image= loadBMP("tex5.bmp");
   loadTexture(image, _textureId[4]);

   image= loadBMP("coca.bmp");
   loadTexture(image, _textureId[5]);


   delete image;

}



int movimiento1 = 0;
int movimiento2 = 0;
int movimiento3 = 0;
int movimiento4 = 0;
int movimiento5 = 0;


void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0, 0, -35);          //Posicion de iniciado        
   glRotatef(anguloX, 1.0, 0.0, 0.0);   //Controla la vista de la camara en X
   glRotatef(anguloY, 0.0, 1.0, 0.0);   //Controla la vista de la camara en Y
   glRotatef(anguloZ, 0.0, 0.0, 1.0);   //Controla la vista de la camara en Z
   glScalef(zoom, zoom, zoom);         //Controla el Zoom
   

   

   //Base
   glPushMatrix();
   glTranslatef(0,-10,0);
   glRotatef(90, 1, 0, 0);
   glRotatef(90, 0, 0, 1);
   glColor3f(.7,.5,0);
   Cilindro(0,0,0,4,0,.5,6,6,4);
   glPopMatrix();
   glEnd();

   //muro
   glPushMatrix();
   glTranslatef(4.5,-7.5,0);
   glRotatef(90, 1, 0, 0);
   glRotatef(90, 0, 0, 1);
   glColor3f(.5,.4,0);
   Cilindro(0,0,0,4,0,2.5,1,1,1);
   glPopMatrix();
   glEnd();
   //muro
   glPushMatrix();
   glTranslatef(-4.5,-7.5,0);
   glRotatef(90, 1, 0, 0);
   glRotatef(90, 0, 0, 1);
   glColor3f(.5,.4,0);
   Cilindro(0,0,0,4,0,2.5,1,1,1);
   glPopMatrix();
   glEnd();
   //muro
   glPushMatrix();
   glTranslatef(0,-7.5,4.5);
   glRotatef(90, 1, 0, 0);
   glRotatef(90, 0, 0, 1);
   glColor3f(.5,.4,0);
   Cilindro(0,0,0,4,0,2.5,1,1,1);
   glPopMatrix();
   glEnd();
   //muro
   glPushMatrix();
   glTranslatef(0,-7.5,-4.5);
   glRotatef(90, 1, 0, 0);
   glRotatef(90, 0, 0, 1);
   glColor3f(.5,.4,0);
   Cilindro(0,0,0,4,0,2.5,1,1,1);
   glPopMatrix();
   glEnd();

   //Base
   glPushMatrix();
   glTranslatef(0,-7,0);
   glRotatef(90, 1, 0, 0);
   glRotatef(90, 0, 0, 1);
   glColor3f(.7,.5,0);
   Cilindro(0,0,0,4,0,.5,6,6,4);
   glPopMatrix();
   glEnd();

   //Base que gira
   glPushMatrix();
   glTranslatef(0,-6.5,0);
   glRotatef(90, 1, 0, 0);
   glRotatef(giraBase, 0, 0, 1);
   glColor3f(.2,.2,0);
   Cilindro(0,0,0,4,0,.5,6,6,3);
   //cout<<giraBase<<endl;

      //Caja
      glPushMatrix();
      glTranslatef(0,4.5,-1.5);
      glRotatef(90, 0, 0, 1);
      glColor3f(.5,.4,0);
      Cilindro(0,0,0,4,0,1.5,1.5,1.5,2);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(0,3.2,-3.5);
      glRotatef(90, 0, 0, 1);
      glColor3f(.2,.2,0);
      Cilindro(0,0,0,4,0,2,.2,.2,1);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(0,5.8,-3.5);
      glRotatef(90, 0, 0, 1);
      glColor3f(.2,.2,0);
      Cilindro(0,0,0,4,0,2,.2,.2,1);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(1.3,4.5,-3.5);
      glRotatef(90, 0, 0, 1);
      glColor3f(.2,.2,0);
      Cilindro(0,0,0,4,0,2,.2,.2,1);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-1.3,4.5,-3.5);
      glRotatef(90, 0, 0, 1);
      glColor3f(.2,.2,0);
      Cilindro(0,0,0,4,0,2,.2,.2,1);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(0,4.5,-4);
      glRotatef(90, 0, 0, 1);
      glColor3f(.5,.4,0);
      Cilindro(0,0,0,4,0,.5,1.5,1.5,4);
      glPopMatrix();

      //paredes largas
      glPushMatrix();
      glTranslatef(0,-3,-1.5);
      glRotatef(45, 0, 0, 1);
      glRotatef(45, 0, 1, 0);
      glRotatef(90, 1, 0, 0);
      glColor3f(.5,.4,0);
      Cilindro(0,0,0,4,0,.5,2,2,4);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-2, -1,-1.5);
      glRotatef(45, 0, 0, 1);
      glRotatef(-45, 0, 1, 0);
      glRotatef(90, 1, 0, 0);
      glColor3f(.5,.4,0);
      Cilindro(0,0,0,4,0,.5,2,2,4);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(0,-3,-4.3);
      glRotatef(45, 0, 0, 1);
      glRotatef(45, 0, 1, 0);
      glRotatef(90, 1, 0, 0);
      glColor3f(.5,.4,0);
      Cilindro(0,0,0,4,0,.5,2,2,4);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-2, -1,-4.3);
      glRotatef(45, 0, 0, 1);
      glRotatef(-45, 0, 1, 0);
      glRotatef(90, 1, 0, 0);
      glColor3f(.5,.4,0);
      Cilindro(0,0,0,4,0,.5,2,2,4);
      glPopMatrix();

      //paredes cortas
      glPushMatrix();
      glTranslatef(1.8,2.8,-1.0);
      glRotatef(45, 0, 0, 1);
      glRotatef(45, 0, 1, 0);
      glRotatef(90, 1, 0, 0);
      glColor3f(.5,.4,0);
      Cilindro(0,0,0,4,0,.5,1.5,1.5,4);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(3.8, 0.8,-1.0);
      glRotatef(45, 0, 0, 1);
      glRotatef(45, 0, 1, 0);
      glRotatef(90, 1, 0, 0);
      glColor3f(.5,.4,0);
      Cilindro(0,0,0,4,0,.5,1.5,1.5,4);
      glPopMatrix();

      //rodillo
      glPushMatrix();
      glTranslatef(-2.7, -1,-4.3);
      glRotatef(45, 0, 0, 1);
      glRotatef(-moverCoca2*100, 0, 1, 0);
      glRotatef(90, 1, 0, 0);
      glColor3f(.2,.2,0);
      Cilindro(0,0,0,20,0,3.5,.8,.8,3);
         glPushMatrix();
         glTranslatef(0, .5,-1);
         glRotatef(0, 0, 0, 1);
         glRotatef(0, 0, 1, 0);
         glRotatef(0, 1, 0, 0);
         glColor3f(.2,.2,0);
         Cilindro(0,0,0,20,0,1,.2,.2,1);
         glPopMatrix(); 
      glPopMatrix(); 

      //brazo de la grua 
      glPushMatrix();
      glTranslatef(2.2,2.4,-1.5);
      glRotatef(45, 0, 0, 1);
      glRotatef(moverBrazo, 0, 1, 0);
      glRotatef(90, 1, 0, 0);
      glColor3f(.2,.2,0);
      Cilindro(0,0,0,4,0,.5,1.5,1.5,1);
         for(int i = 1.5; i <= 7; i += 1.9){
            glPushMatrix();
            glTranslatef(i,-i,0);
            glColor3f(.2,.2,0);
            Cilindro(0,0,0,4,0,.5,1.5,1.5,1);
            glPopMatrix(); 
         }
         
      glPopMatrix(); 

      moverCoca = moverBrazo;

      //Cocacola
      glPushMatrix();
      glTranslatef(8-(moverCoca*.05),7-(moverCoca*.05), moverCoca2 - (moverCoca*.1)); //-5
      glRotatef(90, 1, 0, 0);
      glRotatef(90, 0, 0, 1);
      glRotatef(90, 0, 1, 0);
      glColor3f(.7,.5,0);
      Cilindro(0,0,0,20,0,5,1,1,5); 
      glPopMatrix();
      glEnd();
      //cout<<moverCoca2<<endl;

      glPushMatrix();
      glTranslatef(2.1,2.5,-1.5);
      glRotatef(45, 0, 0, 1);
      glRotatef(moverBrazo, 0, 1, 0);
      glRotatef(90, 1, 0, 0);
      glColor3f(.5,.4,0);
      Cilindro(0,0,0,20,0,2.5,.2,.2,2);
         for(int i = 1.5; i <= 7; i += 1.9){
            glPushMatrix();
            glTranslatef(i,-i,0);
            glColor3f(.5,.4,0);
            Cilindro(0,0,0,20,0,2.5,.2,.2,2);
            glPopMatrix(); 
         }
      glPopMatrix();

      glPushMatrix();
      glTranslatef(3.4, 1.2,-1.5);
      glRotatef(45, 0, 0, 1);
      glRotatef(moverBrazo, 0, 1, 0);
      glRotatef(90, 1, 0, 0);
      glColor3f(.2,.2,0);
      Cilindro(0,0,0,4,0,.5,1.5,1.5,1);
         for(int i = 1.5; i <= 7; i += 1.1){
            glPushMatrix();
            glTranslatef(i,-i,0);
            glColor3f(.2,.2,0);
            Cilindro(0,0,0,4,0,.5,1.5,1.5,1);
            glPopMatrix(); 
         }
      glPopMatrix();

   glPopMatrix();
   glEnd();

   


   glutSwapBuffers();
}



void animacion(int value){

   if(movimiento1 == 0){
      if(moverBrazo >= -30 && moverBrazo <= 20){
         moverBrazo+=3;
         if(moverBrazo == 21)movimiento1 = 1;
      }
   }
   else if(movimiento2 == 0){
      if(moverCoca2 >= -7 && moverCoca2 <= -3.9){
         moverCoca2-=.2;
         if(moverCoca2 <= -7)movimiento2 = 1;
      }
   }
   else if(movimiento3 == 0){
      if(giraBase >= -90 && giraBase <= 0){
         giraBase += 3;
         if(giraBase > 0)movimiento3 = 1;
      }
   }
   else if(movimiento4 == 0){
      if(moverBrazo >= -30 && moverBrazo <= 21){
         moverBrazo-=3;
         if(moverBrazo < -30)movimiento4 = 1;
      }
   }
   else if(movimiento5 == 0){
      if(moverCoca2 >= -7.2 && moverCoca2 <= -3.9){
         moverCoca2+=.2;
         if(moverCoca2 > -3.9){
            movimiento1 = 0;
            movimiento2 = 0;
            movimiento3 = 0;
            movimiento4 = 0;
            moverBrazo = -30;
            moverCoca2 = -3.9;
            giraBase = -90;
         }

      }
   }

   glutPostRedisplay();
   glutTimerFunc(retardo, animacion, 0);
}





// Funcion encargada de controlar el cambio de tamano de la ventana
void reShapeCallbackProc(int w, int h)
{
    if(w<WIDTH|| h<HEIGTH){
        glutReshapeWindow(WIDTH,HEIGTH);   
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, w / h, NEAR_Z, FAR_Z);
    glMatrixMode(GL_MODELVIEW);
}

void keyboardCallbackProc(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'x':
		anguloX+=3;
		break;
	case 'X':
		anguloX-=3;
		break;
	case 'y':
		anguloY+=3;
		break;
	case 'Y':
		anguloY-=3;
		break;
	case 'n':
		//giraBase-=3;
		break;
	case 'm':
		//giraBase+=3;
		break;
   case 'k':
      /*if(moverBrazo > -30)
         moverBrazo-=3;*/
      break;
   case 'l':
      //if(moverBrazo < 20)
        // moverBrazo+=3;
      break;
   case 'h':
      //if(moverCoca2 > -7)
         //moverCoca2-=.2;
      break;
   case 'j':
      //if(moverCoca2 < -3.95)
         //moverCoca2+=.2;
      break;
	case 27 :				
		//exit(0);
		return;
	}
	glutPostRedisplay();
}


int main(int argc, char **argv) 
{  
   
   cout<< "*******Irlanda Isamar Torres Moreno********"<<endl;
   cout<< "*******Teclas:  <x, X> para girar camara en X ********"<<endl;
   cout<< "*******Teclas:  <y, Y> para girar camara en Y ********"<<endl;
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
   glutInitWindowSize(WIDTH, HEIGTH);
   glutInitWindowPosition(50, 50);
   glutCreateWindow("modelo 3D Grua");
   init(); 
   glutDisplayFunc(display); 
	glutReshapeFunc(reShapeCallbackProc);
	glutKeyboardFunc(keyboardCallbackProc);
   glutTimerFunc(retardo, animacion, 0);
   glutMainLoop(); 
   return 1;  
}

