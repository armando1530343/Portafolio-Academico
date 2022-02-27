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



using namespace std;

float AngleX = 90.0;     // The rotation angles about x, y and z axis.
float AngleY = 0.0;
float AngleZ = 0.0;

int refreshMills = 150;

void writenBitmapString(void *font, char *string)
{
	char *c;
	for(c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

double anguloX = 0.0;
double anguloY = 0.0;
double anguloZ = 0.0;
double zoom = 1;
 

//Dibujar cilindro
void DibujaCilindro (int X, int Y, int Z, GLfloat LADOS, GLfloat z1, GLfloat z2, GLfloat radio1, GLfloat radio2)
{
// int IndiceTextura=0;
   GLfloat x = X, y = Y, z = Z, angle;
   GLfloat radio;
   int Contador = 0;

   glTranslatef(X, Y, Z);

   GLfloat Puntos1[40][3];
   GLfloat Puntos2[40][3];

   glBegin(GL_POLYGON); 

   Contador = 0;
   
   for(angle = 0.0f; angle <= (2.0f*GL_PI); angle += (2.0f*GL_PI)/LADOS)
   {
      Puntos1[Contador][0] = radio1*sin(angle)+X;
      Puntos1[Contador][1] = radio1*cos(angle)+Y;
      Puntos1[Contador][2] = z1;          
      glVertex3f(Puntos1[Contador][0], Puntos1[Contador][1], Puntos1[Contador][2]);          
      Contador++;
   }
   glEnd();
   glBegin(GL_POLYGON); 
   Contador = 0;
   for(angle = 0.0f; angle <= (2.0f*GL_PI); angle += (2.0f*GL_PI)/LADOS)
   {
      Puntos2[Contador][0] = radio2*sin(angle)+X;
      Puntos2[Contador][1] = radio2*cos(angle)+Y;
      Puntos2[Contador][2] = z2;          
      glVertex3f(Puntos2[Contador][0], Puntos2[Contador][1], Puntos2[Contador][2]);          
      Contador++;
   }
   glEnd();
   
   for (Contador = 0; Contador<LADOS; Contador++)
   {
      glBegin(GL_POLYGON); 
      //glColor3f(1,0,0);
      int Temporal = 0;
      if (Contador==(int) (LADOS-1))
         Temporal = 0;
      else
         Temporal = Contador+1;
      //glTexCoord2f(OffsetLado, 1.0f);
      glVertex3f(Puntos1[Contador][0], Puntos1[Contador][1], Puntos1[Contador][2]);    
      //glTexCoord2f(SigLado, 1.0f);     
      glVertex3f(Puntos1[Temporal][0], Puntos1[Temporal][1], Puntos1[Temporal][2]);       
      //glTexCoord2f(SigLado, 0.0f);  
      glVertex3f(Puntos2[Temporal][0], Puntos2[Temporal][1], Puntos2[Temporal][2]);    
      //glTexCoord2f(OffsetLado, 0.0f);        
      glVertex3f(Puntos2[Contador][0], Puntos2[Contador][1], Puntos2[Contador][2]);       
      glEnd();
      //OffsetLado = SigLado;
      //SigLado += IncrementoLado;
   }

}

double ang1 = -120;
double ang2 = 110;
double puntaX, puntaY;

double giraBaseY = 0;

bool mov0 = true;
bool mov1 = false;
bool mov2 = false;
bool mov3 = false;
bool mov4 = false;
bool mov5 = false;
bool mov6 = false;
bool mov7 = false;

int vecesMov0 = 0;
int vecesMov1 = 0;
int vecesMov2 = 0;
int vecesMov3 = 0;
int vecesMov4 = 0;
int vecesMov5 = 0;
int vecesMov6 = 0;
int vecesMov7 = 0;
int ocho = 0;

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */



void rayar(void){
	glBegin(GL_LINE_STRIP);
    glColor3f(1,1,0);
    glVertex3f(0,0,1);
    glVertex3f(0,0,2);
    glEnd();
    //glFlush();
    glutSwapBuffers();
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
   





   //Base
   glPushMatrix();
   glTranslatef(0,-3.1,0);
   glRotatef(90, 1, 0, 0);
   glRotatef(45, 0, 0, 1);
   glColor3f(.25,0,0);
   DibujaCilindro(0,0,0,4,.2,-.2,2,2);

      glBegin(GL_LINE_STRIP);
      glColor3f(1,1,1);
      glVertex3f(3,0,0);
      glVertex3f(4,0,0);
      glEnd();

   glPopMatrix();
   glEnd();


   //Base Cilintro
   glPushMatrix();
   glTranslatef(0,-2.3,0);
   glColor3f(.5,0,0);
   glRotatef(90, 1, 0, 0);
   DibujaCilindro(0,0,0,20,-1.0,1.0,1.2,1.2);
   glPopMatrix();
   glEnd();

   //Base Gira
   glPushMatrix();
   glTranslatef(0,-2.3,0);
   glColor3f(1,0,0);
   glRotatef(90, 1, 0, 0);
   glRotatef(45, 0, 0, 0);
   glRotatef(giraBaseY, 0, 0, 1);
   DibujaCilindro(0,0,0,20,-1.3,-1.0,1.2,1.2);   

         //rodillo 1 inferior
         glPushMatrix();
         glTranslatef(.7,0,-2);
         glColor3f(.25,0,0);
         glRotatef(90, 0, 1, 0);
         DibujaCilindro(0,0,0,20,-.15,.15,.8,.8);
         glPopMatrix();
         glEnd();

         //brazo 1
         glPushMatrix();
         glTranslatef(0,0,-2);
         glColor3f(1,0,0);
         glRotatef(-90, 1, 0, 0);
         glRotatef(ang1, 1, 0, 0);
         DibujaCilindro(0,0,0,20,0, 5,.6,.6);     


            //rodillo 1 superior
            glPushMatrix();
            glTranslatef(.7, 0, 5.5);
            glColor3f(.25,0,0);
            glRotatef(90, 0, 1, 0);
            glRotatef(ang1, 0, 0, 1);
            DibujaCilindro(0,0,0,20,-.15,.15,.8,.8);
            DibujaCilindro(0,0,0,20,-.15,.15,.8,.8);
            glPopMatrix();

            //brazo 2
            glPushMatrix();
            glTranslatef(0,0,6);
            glColor3f(.5,0,0);
            glRotatef(ang2, 1, 0, 0);
            DibujaCilindro(0,0,0,20,0, 4,.6,.6);

            glColor3f(1,0,0);
            glTranslatef(0,0,4);
            DibujaCilindro(0,0,0,20,0, 1,.6,.3); 

            glColor3f(.25,0,0);
            glTranslatef(0,0,1);
            DibujaCilindro(0,0,0,20,0, 1,.2,.1); 

            //glPointSize(5);
            //glutDisplayFunc(rayar); 
            

            glPopMatrix(); 
        

            //rodillo 2 superior
            glPushMatrix();
            glTranslatef(-.7, 0, 5.5);
            glColor3f(.25,0,0);
            glRotatef(90, 0, 1, 0);
            glRotatef(ang1, 0, 0, 1);
            DibujaCilindro(0,0,0,20,-.15,.15,.8,.8);
            DibujaCilindro(0,0,0,20,-.15,.15,.8,.8);
            glPopMatrix();
            
         glPopMatrix();
         glEnd();

         //rodillo 2 inferior
         glPushMatrix();
         glTranslatef(-.7,.0,-2);
         glColor3f(.25,0,0);
         glRotatef(90, 0, 1, 0);
         DibujaCilindro(0,0,0,20,-.15,.15,.8,.8);
         glPopMatrix();
         glEnd();

   glPopMatrix();
   glEnd();

   cout<<"giro: "<<giraBaseY<<" brazo1: "<<ang1<<" brazo2: "<<ang2<<endl;

   if(ocho % 2 == 0 && vecesMov6 == 3){
      vecesMov0=0; vecesMov1=0; vecesMov2=0; vecesMov3=0; vecesMov4=0; vecesMov5=0; vecesMov6=0;
      mov1 = true; mov2 = false; mov3 = false; mov4 = false; mov5 = false; mov6 = false;
   }

   glutSwapBuffers();
}



void movimiento1(int value){

   //giro : giraBaseY
   //brazo1 : ang1
   //brazo2 : ang2
   
   
   if(vecesMov0 <= 29 && ang1 < -30 && mov1 == false){
      vecesMov0++;
      cout<<"mov0 "<<vecesMov0<<endl;
      ang1+=6; mov1=false;
   } else {mov1 = true;}

   //primer rueda

   if(mov1 == true && vecesMov1 <= 8  && giraBaseY < 27 && ang2 < 137){
      vecesMov1++;
      cout<<"mov1 "<<vecesMov1<<endl;
      giraBaseY+=3; ang1=-30; ang2+=3; 
   } else {mov2 = true;}

   if(mov2 == true && vecesMov2 <= 5 && vecesMov1 == 9 && giraBaseY > 21 && ang1 < -27 && ang2 > 95){
      vecesMov2++;
      cout<<"mov2 "<<vecesMov2<<endl;
      giraBaseY-=1; ang1+=0.5 ;ang2-=7;
   } else {mov3 = true;}

   if(mov3 == true && vecesMov2 == 6 && giraBaseY > 0 && ang1 > -30 && ang2 < 110){
      vecesMov3++;
      cout<<"mov3 "<<vecesMov3<<endl;
      giraBaseY-=7; ang1-=1 ;ang2+=5;
   } else {mov4 = true;}

   //if(vecesMov3==3 && vecesMov4==0)ocho++;

   //segunda rueda

   /*if(mov4 == true && vecesMov3 == 3  && giraBaseY > -27 && ang2 < 137){
      vecesMov4++;
      cout<<"mov4 "<<vecesMov4<<endl;
      giraBaseY-=3; ang1=-30; ang2+=3; 
   } else {mov5 = true;}

   if(mov5 == true && vecesMov2 <= 5 && vecesMov1 == 9 && giraBaseY < -21 && ang1 < -27 && ang2 > 95){
      vecesMov5++;
      cout<<"mov5 "<<vecesMov2<<endl;
      giraBaseY+=1; ang1+=0.5 ;ang2-=7;
   } else {mov6 = true;}

   if(mov6 == true && vecesMov2 == 6 && giraBaseY < 0 && ang1 > -30 && ang2 < 110){
      vecesMov3++;
      cout<<"mov6 "<<vecesMov3<<endl;
      giraBaseY+=7; ang1-=1 ;ang2+=5;
   } else {
      vecesMov0=0; vecesMov1=0; vecesMov2=0; vecesMov3=0; vecesMov4=0; vecesMov5=0; vecesMov6=0;
      mov1 = true; mov2 = false; mov3 = false; mov4 = false; mov5 = false; mov6 = false;
   }*/

   //if(mov2 == true && giraBaseY >= 21 && /*ang1 <= -27 &&*/ ang2 >= 95){giraBaseY-=1; /*ang1+=0.5*/ ;ang2-=7;} else {mov3 = true;}

   //if(mov3 == true && giraBaseY > 0 && ang1 > -120 && ang2 < 110){giraBaseY-=7; ang1-=31 ;ang2+=5;} else mov4 = true;
   
   cout<<"giro: "<<giraBaseY<<" brazo1: "<<ang1<<" brazo2: "<<ang2<<endl;
   
   glutPostRedisplay();
   glutTimerFunc(refreshMills, movimiento1, 0);
}
void movimiento2(int value){

   //giro : giraBaseY
   //brazo1 : ang1
   //brazo2 : ang2
   
   //segunda rueda

   if(mov4 == true && vecesMov4 <= 8 && vecesMov3 == 3  && giraBaseY > -27 && ang2 < 137){
      vecesMov4++;
      cout<<"mov4 "<<vecesMov4<<endl;
      giraBaseY-=3; ang1=-30; ang2+=3; 
   } else {mov5 = true;}

   if(mov5 == true && vecesMov5 <=5 && vecesMov4 == 9 && giraBaseY < -21 && ang1 < -27 && ang2 > 95){
      vecesMov5++;
      cout<<"mov5 "<<vecesMov2<<endl;
      giraBaseY+=1; ang1+=0.5 ;ang2-=7;
   } else {mov6 = true;}

   if(mov6 == true && vecesMov5 == 6 && giraBaseY < 0 && ang1 > -30 && ang2 < 110){
      vecesMov6++;
      cout<<"mov6 "<<vecesMov3<<endl;
      giraBaseY+=7; ang1-=1 ;ang2+=5;
   } else {

      //if(vecesMov6 == 3)ocho++;
      //vecesMov0=0; vecesMov1=0; vecesMov2=0; vecesMov3=0; vecesMov4=0; vecesMov5=0; vecesMov6=0;
      //mov1 = true; mov2 = false; mov3 = false; mov4 = false; mov5 = false; mov6 = false;
   }

   if(vecesMov6 == 3){ocho++;}

   //if(mov2 == true && giraBaseY >= 21 && /*ang1 <= -27 &&*/ ang2 >= 95){giraBaseY-=1; /*ang1+=0.5*/ ;ang2-=7;} else {mov3 = true;}

   //if(mov3 == true && giraBaseY > 0 && ang1 > -120 && ang2 < 110){giraBaseY-=7; ang1-=31 ;ang2+=5;} else mov4 = true;
   
   cout<<"giro: "<<giraBaseY<<" brazo1: "<<ang1<<" brazo2: "<<ang2<<endl;
   
   glutPostRedisplay();
   glutTimerFunc(refreshMills, movimiento2, 0);
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
			AngleX+=3;
			break;
		case 'X':
			AngleX-=3;
			break;
		case 'y':
			AngleY+=3;
			break;
		case 'Y':
			AngleY-=3;
			break;
		case 'z':
			//glRotatef(1.,0.0,0.0,1.0);
			break;
		case 'Z':
			//glRotatef(-1.,0.0,0.0,1.0);
			break;
      case 'o':
         ang2-=3;
         break;
      case 'l':
         ang2+=3;
         break;
		case '+':
			ang1-=3;
			break;
		case '-':
			ang1+=3;
			break;
      case 'a':
         giraBaseY-=3;
         break;
      case 's':
         giraBaseY+=3;
         break;
		
		case 27 :				//ESCAPE Code for exiting program.
			//exit(0);
			return;
		}
		glutPostRedisplay();
	}


void init(void)
{
    glEnable(GL_DEPTH_TEST); 
    //showMenu();
}


//****************************************************************************************
// Main routine: defines window properties, creates window,
// registers callback routines and begins processing.
int main(int argc, char **argv) 
{  

   cout<< "Teclas:"<<endl;
   cout<< "(+) (-) para mover el brazo inferior"<<endl;
   cout<< "(o) (l) para mover el brazo superior"<<endl;
   cout<< "(y) (Y) para rotar el brazo"<<endl;
   // Initialize GLUT.
   glutInit(&argc, argv);
 
   // Set display mode as single-buffered and RGB color.
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
   
   // Set OpenGL window size.
   glutInitWindowSize(800, 600);

   // Set position of OpenGL window upper-left corner.
   glutInitWindowPosition(500, 100);
   // Create OpenGL window with title.
   glutCreateWindow("Brazo_Robotico_KUKA Avance No.1");
   
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
   glutTimerFunc(refreshMills, movimiento2,0);
   


   // Register keyboard routine.
   //glutKeyboardFunc(keyInput);
   
   // Begin processing.
   glutMainLoop(); 


		

   return 1;  
}

