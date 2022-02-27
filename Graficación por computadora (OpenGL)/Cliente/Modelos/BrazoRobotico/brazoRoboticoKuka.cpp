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

#define SIZE 400	
#define NEAR_Z 1.0
#define FAR_Z 100.0	// For the frustum size.

#define TAM_ESC1 3
#define TAM_ESC2 10

#define TotalTexturas 6

#include "imageloader.h"



using namespace std;

float AngleX = 20.0;     // The rotation angles about x, y and z axis.
float AngleY = 45.0;
float AngleZ = 0.0;

int refreshMills = 150;

GLuint *_textureId;



void writenBitmapString(void *font, char *string)
{
	char *c;
	for(c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

//angulos para la camara e XYZ

double anguloX = 0.0;
double anguloY = 0.0;
double anguloZ = 0.0;
double zoom = 1;
 

//Dibujar cilindro
void DibujaCilindro (int X, int Y, int Z, GLfloat LADOS, GLfloat z1, GLfloat z2, GLfloat radio1, GLfloat radio2, int IndiceTextura)
{
// int IndiceTextura=0;
   GLfloat x = X, y = Y, z = Z, angle;
   GLfloat radio;
   int Contador = 0;

   glTranslatef(X, Y, Z);

   GLfloat Puntos1[40][3];
   GLfloat Puntos2[40][3];



   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, _textureId[IndiceTextura]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glColor3f(1.0f, 1.0f, 1.0f);  
   
   GLfloat IncrementoLado = 1.0/LADOS;
   GLfloat OffsetLado = 0.0;
   GLfloat SigLado = IncrementoLado;



   glBegin(GL_POLYGON); 

   Contador = 0;
   
   for(angle = 0.0f; angle <= (2.0f*GL_PI); angle += (2.0f*GL_PI)/LADOS)
   {

      glColor3f(1.0,1.0,1.0/(Contador+1)); 


      Puntos1[Contador][0] = radio1*sin(angle)+X;
      Puntos1[Contador][1] = radio1*cos(angle)+Y;
      Puntos1[Contador][2] = z1;   
      glTexCoord2f(OffsetLado, 1.0f);       
      glVertex3f(Puntos1[Contador][0], Puntos1[Contador][1], Puntos1[Contador][2]);          
      Contador++;

      OffsetLado = SigLado;
      SigLado += IncrementoLado;
   }
   glEnd();


   IncrementoLado = 1.0/LADOS;
   OffsetLado = 0.0;
   SigLado = IncrementoLado;
   glBegin(GL_POLYGON); 
   Contador = 0;
   for(angle = 0.0f; angle <= (2.0f*GL_PI); angle += (2.0f*GL_PI)/LADOS)
   {
      glColor3f(1.0,1.0,1.0/(Contador+1));
      Puntos2[Contador][0] = radio2*sin(angle)+X;
      Puntos2[Contador][1] = radio2*cos(angle)+Y;
      Puntos2[Contador][2] = z2;          
      glTexCoord2f(OffsetLado, 1.0f);
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
      glBegin(GL_POLYGON);
      glColor3f(1.0,1.0,1.0/(Contador+1)); 
      //glColor3f(.5,.5,.5);
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

double ang1 = -120;//angulo para brazo 1
double ang2 = 113;//angulo para brazo 2
double puntaX, puntaY;

double giraBaseY = 0;//gira la base del brazo


//verificacion de movimientos del brazo

bool mov[16];
//mov[0] = true;


bool mov0 = true;
bool mov1 = false;
bool mov2 = false;
bool mov3 = false;
bool mov4 = false;
bool mov5 = false;
bool mov6 = false;
bool mov7 = false;
bool mov8 = false;
bool mov9 = false;

//veces que se hace ese movimiento
int vecesMov[16];
//vecesMov[0] = true;


int vecesMov0 = 0;
int vecesMov1 = 0;
int vecesMov2 = 0;
int vecesMov3 = 0;
int vecesMov4 = 0;
int vecesMov5 = 0;
int vecesMov6 = 0;
int vecesMov7 = 0;
int vecesMov8 = 0;
int vecesMov9 = 0;

int ocho = 0;

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */

//cargando texturas

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
   image = loadBMP("kuka3.bmp");
   loadTexture(image, _textureId[0]);

   image= loadBMP("base.bmp");
   loadTexture(image, _textureId[1]);

   image= loadBMP("kuka.bmp");
   loadTexture(image, _textureId[2]);


   delete image;

}


void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0, 0, -40);          //Posicion de iniciado        
   glRotatef(AngleX, 1.0, 0.0, 0.0);   //Controla la vista de la camara en X
   glRotatef(AngleY, 0.0, 1.0, 0.0);   //Controla la vista de la camara en Y
   glRotatef(AngleZ, 0.0, 0.0, 1.0);   //Controla la vista de la camara en Z
   glScalef(zoom, zoom, zoom);         //Controla el Zoom
   
   //DibujaCilindro (int X, int Y, GLfloat LADOS, GLfloat z1, GLfloat z2, GLfloat radio1, GLfloat radio2, int IndiceTextura)
   //
   //cout<<AngleX<<","<<AngleY<<","<<AngleZ<<endl;
   
   
   //Base
   glPushMatrix();
   glTranslatef(0,-3.1,0);
   glRotatef(90, 1, 0, 0);
   glRotatef(90, 0, 0, 1);
   glColor3f(.25,0,0);
   DibujaCilindro(0,0,0,4,.2,-.2,2,2,1);

      //dibujando el ocho en el piso
      glBegin(GL_LINE_STRIP);
      glColor3f(1,1,1);

      //double j = .1;

      //for(double i = 6.0; i >= 4.8; i-=.2){ glVertex3f(i,j,0); j += .15; }
      
      //--------------- mitad 1 infinito--------------

      glVertex3f(6,0,0);//centro
      glVertex3f(5.8,.1,0);
      glVertex3f(5.6,.25,0);
      glVertex3f(5.4,.4,0);
      glVertex3f(5.2,.55,0);
      glVertex3f(5.0,.7,0);
      glVertex3f(4.8,.85,0);
      
      glVertex3f(4.7,1,0);
      glVertex3f(4.65,1.05,0);
      glVertex3f(4.6,1.2,0);
      glVertex3f(4.55,1.35,0);
      glVertex3f(4.5,1.5,0);
      glVertex3f(4.5,1.65,0);
      glVertex3f(4.5,1.8,0);
      glVertex3f(4.5,1.95,0);
      
      glVertex3f(4.55,2.1,0);
      glVertex3f(4.6,2.25,0);
      glVertex3f(4.65,2.4,0);
      glVertex3f(4.7,2.55,0);
      glVertex3f(4.75,2.7,0);

      glVertex3f(4.8,2.8,0);
      glVertex3f(4.85,2.85,0);
      glVertex3f(4.9,2.9,0);
      glVertex3f(4.95,2.95,0);
      glVertex3f(5.0,3.0,0);
      glVertex3f(5.05,3.05,0);
      glVertex3f(5.1,3.1,0);
      glVertex3f(5.15,3.1,0);
      glVertex3f(5.3,3.15,0);
      glVertex3f(5.45,3.2,0);
      
      glVertex3f(5.6,3.25,0);
      glVertex3f(6.4,3.25,0);

      glVertex3f(6.45,3.2,0);
      glVertex3f(6.6,3.15,0);
      glVertex3f(6.85,3.1,0);
      glVertex3f(6.90,3.1,0);
      glVertex3f(6.95,3.05,0);
      glVertex3f(7.0,3.0,0);
      glVertex3f(7.05,2.95,0);
      glVertex3f(7.1,2.9,0);
      glVertex3f(7.15,2.85,0);
      glVertex3f(7.2,2.8,0);

      glVertex3f(7.25,2.7,0);
      glVertex3f(7.3,2.55,0);
      glVertex3f(7.35,2.4,0);
      glVertex3f(7.4,2.25,0);
      glVertex3f(7.45,2.1,0);
      
      glVertex3f(7.5,1.95,0);
      glVertex3f(7.5,1.8,0);
      glVertex3f(7.5,1.65,0);
      glVertex3f(7.5,1.5,0);
      glVertex3f(7.45,1.35,0);
      glVertex3f(7.4,1.2,0);
      glVertex3f(7.35,1.05,0);
      glVertex3f(7.3,1,0);

      glVertex3f(7.2,.85,0);
      glVertex3f(7.0,.7,0);
      glVertex3f(6.8,.55,0);
      glVertex3f(6.6,.4,0);
      glVertex3f(6.4,.25,0);
      glVertex3f(6.2,.1,0);
      glVertex3f(6,0,0);//centro

      //--------------- mitad 2 infinito--------------

      glVertex3f(6,0,0);//centro
      glVertex3f(5.8,-.1,0);
      glVertex3f(5.6,-.25,0);
      glVertex3f(5.4,-.4,0);
      glVertex3f(5.2,-.55,0);
      glVertex3f(5.0,-.7,0);
      glVertex3f(4.8,-.85,0);
      
      glVertex3f(4.7,-1,0);
      glVertex3f(4.65,-1.05,0);
      glVertex3f(4.6,-1.2,0);
      glVertex3f(4.55,-1.35,0);
      glVertex3f(4.5,-1.5,0);
      glVertex3f(4.5,-1.65,0);
      glVertex3f(4.5,-1.8,0);
      glVertex3f(4.5,-1.95,0);
      
      glVertex3f(4.55,-2.1,0);
      glVertex3f(4.6,-2.25,0);
      glVertex3f(4.65,-2.4,0);
      glVertex3f(4.7,-2.55,0);
      glVertex3f(4.75,-2.7,0);

      glVertex3f(4.8,-2.8,0);
      glVertex3f(4.85,-2.85,0);
      glVertex3f(4.9,-2.9,0);
      glVertex3f(4.95,-2.95,0);
      glVertex3f(5.0,-3.0,0);
      glVertex3f(5.05,-3.05,0);
      glVertex3f(5.1,-3.1,0);
      glVertex3f(5.15,-3.1,0);
      glVertex3f(5.3,-3.15,0);
      glVertex3f(5.45,-3.2,0);
      
      glVertex3f(5.6,-3.25,0);
      glVertex3f(6.4,-3.25,0);

      glVertex3f(6.45,-3.2,0);
      glVertex3f(6.6,-3.15,0);
      glVertex3f(6.85,-3.1,0);
      glVertex3f(6.90,-3.1,0);
      glVertex3f(6.95,-3.05,0);
      glVertex3f(7.0,-3.0,0);
      glVertex3f(7.05,-2.95,0);
      glVertex3f(7.1,-2.9,0);
      glVertex3f(7.15,-2.85,0);
      glVertex3f(7.2,-2.8,0);

      glVertex3f(7.25,-2.7,0);
      glVertex3f(7.3,-2.55,0);
      glVertex3f(7.35,-2.4,0);
      glVertex3f(7.4,-2.25,0);
      glVertex3f(7.45,-2.1,0);
      
      glVertex3f(7.5,-1.95,0);
      glVertex3f(7.5,-1.8,0);
      glVertex3f(7.5,-1.65,0);
      glVertex3f(7.5,-1.5,0);
      glVertex3f(7.45,-1.35,0);
      glVertex3f(7.4,-1.2,0);
      glVertex3f(7.35,-1.05,0);
      glVertex3f(7.3,-1,0);

      glVertex3f(7.2,-.85,0);
      glVertex3f(7.0,-.7,0);
      glVertex3f(6.8,-.55,0);
      glVertex3f(6.6,-.4,0);
      glVertex3f(6.4,-.25,0);
      glVertex3f(6.2,-.1,0);
      glVertex3f(6,0,0);//centro

      
      glEnd();

   glPopMatrix();
   glEnd();


   //Base Cilintro
   glPushMatrix();
   glTranslatef(0,-2.3,0);
   glColor3f(.5,0,0);
   glRotatef(90, 1, 0, 0);
   DibujaCilindro(0,0,0,20,-1.0,1.0,1.2,1.2,1);
   glPopMatrix();
   glEnd();

   //Base Gira
   glPushMatrix();
   glTranslatef(0,-2.3,0);
   glColor3f(1,0,0);
   glRotatef(90, 1, 0, 0);
   glRotatef(giraBaseY, 0, 0, 1);
   DibujaCilindro(0,0,0,20,-1.3,-1.0,1.2,1.2,1);   

         //rodillo 1 inferior
         glPushMatrix();
         glTranslatef(.7,0,-2);
         glColor3f(.25,0,0);
         glRotatef(90, 0, 1, 0);
         DibujaCilindro(0,0,0,20,-.15,.15,.8,.8,2);
         glPopMatrix();
         glEnd();

         //brazo 1
         glPushMatrix();
         glTranslatef(0,0,-2);
         glColor3f(1,0,0);
         glRotatef(-90, 1, 0, 0);
         glRotatef(ang1, 1, 0, 0);
         DibujaCilindro(0,0,0,20,0, 5,.6,.6,2);     


            //rodillo 1 superior
            glPushMatrix();
            glTranslatef(.7, 0, 5.5);
            glColor3f(.25,0,0);
            glRotatef(90, 0, 1, 0);
            glRotatef(ang1, 0, 0, 1);
            DibujaCilindro(0,0,0,20,-.15,.15,.8,.8,2);
            //DibujaCilindro(0,0,0,20,-.15,.15,.8,.8,2);
            glPopMatrix();

            //brazo 2
            glPushMatrix();
            glTranslatef(0,0,6);
            glColor3f(.5,0,0);
            glRotatef(ang2, 1, 0, 0);
            DibujaCilindro(0,0,0,20,0, 4,.6,.6,0);

            glColor3f(1,0,0);
            glTranslatef(0,0,4);
            DibujaCilindro(0,0,0,20,0, 1,.6,.3,1); 

            glColor3f(.25,0,0);
            glTranslatef(0,0,1);
            DibujaCilindro(0,0,0,20,0, 1,.2,.1,2); 

            //glPointSize(5);
            //glutDisplayFunc(rayar); 
            

            glPopMatrix(); 
        

            //rodillo 2 superior
            glPushMatrix();
            glTranslatef(-.7, 0, 5.5);
            glColor3f(.25,0,0);
            glRotatef(90, 0, 1, 0);
            glRotatef(ang1, 0, 0, 1);
            DibujaCilindro(0,0,0,20,-.15,.15,.8,.8,2);
            //DibujaCilindro(0,0,0,20,-.15,.15,.8,.8,2);
            glPopMatrix();
            
         glPopMatrix();
         glEnd();

         //rodillo 2 inferior
         glPushMatrix();
         glTranslatef(-.7,.0,-2);
         glColor3f(.25,0,0);
         glRotatef(90, 0, 1, 0);
         DibujaCilindro(0,0,0,20,-.15,.15,.8,.8,2);
         glPopMatrix();
         glEnd();

   glPopMatrix();
   glEnd();

   //cout<<"giro: "<<giraBaseY<<" brazo1: "<<ang1<<" brazo2: "<<ang2<<endl;

   /*if(ocho % 2 == 0 && vecesMov6 == 3){
      vecesMov0=0; vecesMov1=0; vecesMov2=0; vecesMov3=0; vecesMov4=0; vecesMov5=0; vecesMov6=0;
      mov1 = true; mov2 = false; mov3 = false; mov4 = false; mov5 = false; mov6 = false;
   }*/

   glutSwapBuffers();
}


int variable[5];
int vuelta = 0;

void movimiento1(int value){

   //giro : giraBaseY
   //brazo1 : ang1
   //brazo2 : ang2
   //
   //
   
   

   if(vecesMov0 < 15){
   		ang1+=6; vecesMov0++;
   }
   else if(vecesMov1 < 4){
   		if(vecesMov1 == 0) vuelta ++;
   		giraBaseY+=variable[0]; ang2+=3; vecesMov1++;
   }
   else if(vecesMov2 < 3){
   		giraBaseY+=variable[1]; ang2-=3; vecesMov2++;
   }
   else if(vecesMov3 < 3){
   		ang2-=4; vecesMov3++;
   }
   else if(vecesMov4 < 3){
   		giraBaseY-=variable[2]; ang1+=1; ang2-=3; vecesMov4++;
   }
   else if(vecesMov5 < 3){
   		giraBaseY-=variable[3]; vecesMov5++;
   }
   else if(vecesMov6 < 3){
   		giraBaseY-=variable[4]; ang1-=1; ang2+=6; vecesMov6++;
   }
   else{
   		//giraBaseY = -giraBaseY;
   		//ang1 = -120; ang2 = 113; giraBaseY = 0;
   		//vecesMov0 = 0;
   		
   		if(vuelta > 1){
   			ang1 = -120; ang2 = 113; giraBaseY = 0;
   			vecesMov0 = 0;
   			vuelta = 0;
   		}

   		vecesMov1 = 0;
   		vecesMov2 = 0;
   		vecesMov3 = 0;
   		vecesMov4 = 0;
   		vecesMov5 = 0;
   		vecesMov6 = 0;
   		for(int i = 0; i < 5; i++) variable[i] = -variable[i];

   		//vuelta = 0;
   }
   //cout<<"giro: "<<giraBaseY<<" brazo1: "<<ang1<<" brazo2: "<<ang2<<endl;
   
   glutPostRedisplay();
   glutTimerFunc(refreshMills, movimiento1, 0);
}

// Initialization routine.
void setup(void) 
{
   // Establecer el color de fondo (o borrar).
   glClearColor(1.0, 1.0, 1.0, 1.0); 
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  
   glMatrixMode(GL_PROJECTION);

   glLoadIdentity();

   glOrtho(-500, 600, -500, 600, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);

   glLoadIdentity();
}
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(30, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
//   gluLookAt(0, 0, 10, 2, 0, 2, 0, 3, 0);
   gluLookAt(0, 0, 25, 0, 0, 0, 0, 3, 0);
}
// Funcion encargada de controlar el cambio de tamano de la ventana
void reShapeCallbackProc(int w, int h)
{
    if(w<600|| h<600){
        glutReshapeWindow(600,600);   
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, w / h, NEAR_Z, FAR_Z);
    glMatrixMode(GL_MODELVIEW);
}
//****************************************************************************************
	void keyboardCallbackProc(unsigned char key, int x, int y)
							// This is the callback procedure for capturing OpenGL Keyboard events.
	{
		switch(key)
		{
		case 'x':
			AngleX+=3;//girando camara en x
			break;
		case 'X':
			AngleX-=3;//girando camara en x
			break;
		case 'y':
			AngleY+=3;//girando camara en y
			break;
		case 'Y':
			AngleY-=3;//girando camara en y
			break;
		case 'z':
			//glRotatef(1.,0.0,0.0,1.0);
			break;
		case 'Z':
			//glRotatef(-1.,0.0,0.0,1.0);
			break;
      case 'o':
         //ang2-=3;
         break;
      case 'l':
         //ang2+=3;
         break;
		case '+':
			//ang1-=3;
			break;
		case '-':
			//ang1+=3;
			break;
      case 'a':
         //giraBaseY-=3;
         break;
      case 's':
         //giraBaseY+=3;
         break;
		
		case 27 :				//ESCAPE Code for exiting program.
			//exit(0);
			return;
		}
		glutPostRedisplay();
	}


//****************************************************************************************
// Main routine: defines window properties, creates window,
// registers callback routines and begins processing.
int main(int argc, char **argv) 
{  

   cout<< "Teclas:"<<endl;
   cout<< "(y) (Y) para mover camara en Y"<<endl;
   cout<< "(x) (X) para mover camara en X"<<endl;

   variable[0] = 3;
   variable[1] = 6;
   variable[2] = 2;
   variable[3] = 5;
   variable[4] = 3;

   
   // Initialize GLUT.
   glutInit(&argc, argv);
 
   // Set display mode as single-buffered and RGB color.
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
   
   // Set OpenGL window size.
   glutInitWindowSize(800, 600);

   // Set position of OpenGL window upper-left corner.
   glutInitWindowPosition(500, 100);
   // Create OpenGL window with title.
   glutCreateWindow("Brazo_Robotico_KUKA");
   
   // Initialize.
   //setup();

   init(); 
   
   // Register display routine.
   glutDisplayFunc(display);
   //glutDisplayFunc(rayar); 
	//glutDisplayFunc(displayCallbackProc);

   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboardCallbackProc);
   glutTimerFunc(refreshMills, movimiento1,0);
   //glutTimerFunc(refreshMills, movimiento2,0);
   


   // Register keyboard routine.
   //glutKeyboardFunc(keyInput);
   
   // Begin processing.
   glutMainLoop(); 


		

   return 1;  
}

