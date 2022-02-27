#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include <time.h>
#include <vector>
#include <sstream>
#define WIDTH 800
#define HEIGHT 600
#define PI 3.141592654


using namespace std;

double zoom = 0.3;    //Valor del zoom de la camara
double AngleX = 0.0;      //Grados de rotacion del eje X
double AngleY = 0.0;    //Grados de rotacion del eje Y
double AngleZ = 0.0;
int Retardo = 10;

void circle(float radio, float ancho,  int lados, float *colores) {
    GLfloat X = 0, Y = 0, Z = 0, angle;
    glTranslatef(X,Y,Z);
    GLfloat Puntos[2][500][3];
    int Contador = 0;
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
        glColor3f(colores[0] - .2, colores[1] - .2, colores[2] - .2);
        Contador = 0;
        for (angle = 0.0f; angle <= (2.0f * PI); angle += (2.0f * PI) / lados) {
            Puntos[i][Contador][0] = radio * sin(angle) + X;
            Puntos[i][Contador][1] = radio * cos(angle) + Y;
            Puntos[i][Contador][2] = Z;   
            glVertex3f(Puntos[i][Contador][0], Puntos[i][Contador][1], Puntos[i][Contador][2]);
            Contador++;
        }
        glEnd();
        Z -= ancho;
    }
    float *color = colores;
    for (Contador = 0; Contador < lados; Contador++) {
        glBegin(GL_POLYGON);
        
        glColor3f(color[0], color[1], color[2]);
        int Temporal = 0;
        if (Contador == (int) (lados - 1))
            Temporal = 0;
        else
            Temporal = Contador + 1;
        glVertex3f(Puntos[0][Contador][0], Puntos[0][Contador][1], Puntos[0][Contador][2]);
        glVertex3f(Puntos[0][Temporal][0], Puntos[0][Temporal][1], Puntos[0][Temporal][2]);
        glVertex3f(Puntos[1][Temporal][0], Puntos[1][Temporal][1], Puntos[1][Temporal][2]);
        glVertex3f(Puntos[1][Contador][0], Puntos[1][Contador][1], Puntos[1][Contador][2]);
        glEnd();

        color[0] -= colores[0]/lados;
        color[1] -= colores[1]/lados;
        color[2] -= colores[2]/lados;
    }
}

void writeBitmapString(void *font, string str)
{
    int i;
    for(i = 0; i < str.size(); i++)
        glutBitmapCharacter(font, str[i]);
}

void moto(float x, float y, float z, int angle, float scale, float *color1, float *color2){
	float *color = new float[3];
	
	glPushMatrix();
	glTranslatef(x,y,z);
	glRotatef(angle,0,0,1);
	glScalef(scale, scale, scale);
		//cabeza
		glPushMatrix();
		glTranslatef(0,1,0);
		glRotatef(0,0,0,0);
		color[0] = color1[0];
		color[1] = color1[1];
		color[2] = color1[2];
		circle(.2, .05, 30, color);
		glPopMatrix();
		//cuerpo
		glPushMatrix();
		glTranslatef(0,.5,.1);
		glRotatef(0,0,0,0);
		color[0] = color2[0];
		color[1] = color2[1];
		color[2] = color2[2];
		circle(.4, .05, 4, color);
		glPopMatrix();

		//pierna izquierda
		glPushMatrix();
		glTranslatef(-.2,0.1,.1);
		glRotatef(0,0,0,0);
		color[0] = color2[0];
		color[1] = color2[1];
		color[2] = color2[2];
		circle(.3, .05, 5, color);
		glPopMatrix();

		//pierna derecha
		glPushMatrix();
		glTranslatef(.2,0.1,.1);
		glRotatef(0,0,0,0);
		color[0] = color2[0];
		color[1] = color2[1];
		color[2] = color2[2];
		circle(.3, .05, 5, color);
		glPopMatrix();

		//moto
		glPushMatrix();
		glTranslatef(.0,.15,.2);
		color[0] = color1[0];
		color[1] = color1[1];
		color[2] = color1[2];
		circle(.4, .1, 5, color);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(.0,.25,.3);
		color[0] = color2[0];
		color[1] = color2[1];
		color[2] = color2[2];
		circle(.1, .1, 8, color);
		glPopMatrix();

		//llanta
		glPushMatrix();
		glTranslatef(.1,-.15,.3);
		glRotatef(90,0,1,0);
		color[0] = .0;
		color[1] = .0;
		color[2] = .0;
		circle(.2, .2, 8, color);
		glPopMatrix();

	glPopMatrix();
}

//carretera
void pista(float x, float y, float z, float long_pista){
	float *color = new float[3];

	glPushMatrix();
	glTranslatef(x,y,z);
	glRotatef(0,0,0,0);
	for(int i = 5; i > -long_pista; i--){
		glPushMatrix();
		glTranslatef(0,0,i*3);
		glRotatef(90,1,0,0);
		glRotatef(45,0,0,1);		
		color[0] = .4;
		color[1] = .4;
		color[2] = .4;
		circle(4, .1, 4, color);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0,0.05,i*3);
		glRotatef(90,1,0,0);
		glRotatef(45,0,0,1);
		color[0] = 1;
		color[1] = 1;
		color[2] = 1;
		circle(.5, .1, 4, color);
		glPopMatrix();

		if(i == -long_pista/2){
			glPushMatrix();
			glTranslatef(0,-2.7,i*3);
			glRotatef(180,1,0,0);
			glRotatef(45,0,0,1);
			color[0] = 1;
			color[1] = 0;
			color[2] = 0;
			circle(4, .5, 4, color);
			glPopMatrix();

		}

		
	}

	glPopMatrix();
}

//cesped
void campo(float x, float y, float z, float long_pista){
	float *color = new float[3];

	glPushMatrix();
	glTranslatef(x,y,z);
	glRotatef(0,0,0,0);
	for(int i = 5; i > -long_pista; i--){
		glPushMatrix();
		glTranslatef(0,0,i*3);
		glRotatef(90,1,0,0);
		glRotatef(45,0,0,1);		
		color[0] = .0;
		color[1] = .6;
		color[2] = .0;
		circle(4, .1, 4, color);
		glPopMatrix();		
	}

	glPopMatrix();
}

float camY = 0;			//inclinacion de moto jugador
float direccion = 0;	//direccion de moto (izq- der)

float camY_contra = 0;	//inclinacion de moto jugador contrario
float direccion_contra = 0;

//direcciones de la moto
bool ir_der = false;
bool ir_izq = false;
bool ir_del = false;

//movimiento de la carretera en Z
float pistaZ = 0;

//longitud de la carretera en eje Z
float longitud_pista = 50;

//duracion de la carrera
int vueltas = 20;


//posicion de la moto en eje Z
float motoZ = -5;

//posicion de la moto contraria en eje Z
float motoZ_contra = -5;

//posicion de la linea de meta
float metaZ = -(longitud_pista/2) * 3;

//verifica si se llego a la meta
bool meta = false;

//comprueba si se quedo en primer lugar (ganador)
bool primer_lugar = false;

//se activa la opcion de turbo
bool turbo = false;

//se activa el turbo a la moto con la tecla T
bool turbo_activo = false;


void display(void)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(.5,.5,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0, 0, 0);//Posicion de iniciado
    glRotatef(0, 0.0, 1.0, 0.0);//Controla la vista de la camara en Y
    glScalef(zoom, zoom, zoom);//Controla el Zoom

    glColor3f(1,0,0);

    if(meta && primer_lugar){
    	
	    glRasterPos3f(-.5, 2, -5);
	    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "!! GANADOR !!");
    }
    if(meta && !primer_lugar){
    	glRasterPos3f(-.5, 2, -5);
	    writeBitmapString(GLUT_BITMAP_HELVETICA_18, " PERDEDOR :'v");
    }

    string lugar = "1er LUGAR";

    if(motoZ > motoZ_contra)
    	lugar = "2do LUGAR";

    glRasterPos3f(2, 2, -5);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, lugar);

    glRasterPos3f(-2.5, 2, -5);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "z: izquierda");
    glRasterPos3f(-2.5, 1.7, -5);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "x: frente");
    glRasterPos3f(-2.5, 1.4, -5);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "c: derecha");

    if(turbo){
    	glRasterPos3f(-2.5, 1.1, -5);
    	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Turbo Activo (Presiona T)");
    }
    

    


    pista(0,-1.4, pistaZ, longitud_pista);
    campo(-6,-1.4, pistaZ, longitud_pista);
    campo(6,-1.4, pistaZ, longitud_pista);

    float *color1 = new float[3];
    float *color2 = new float[3];

    color1[0] = .5;
    color1[1] = .0;
    color1[2] = .0;

    color2[0] = .5;
    color2[1] = .5;
    color2[2] = .0;

    //motocicleta principal

    moto(direccion,-1, motoZ, camY, .8, color1, color2);

    color1[0] = .5;
    color1[1] = .2;
    color1[2] = .5;

    color2[0] = .5;
    color2[1] = .5;
    color2[2] = .0;

    //motocicleta  de competidor

    moto(direccion_contra,-1, motoZ_contra, camY_contra, .8, color1, color2);

    glFlush();

    glutSwapBuffers();
}

int dir = 0;
int revasa = 0;
int _turbo = 0;

void timer(int value){


	if(!meta){		

		if(pistaZ >= longitud_pista/2 && vueltas > 0){
			vueltas--;
			pistaZ = 0;
			metaZ = -(longitud_pista/2) * 3;

			dir = rand()%3;

			revasa = rand()%3;

			if(vueltas == 2)
				_turbo = 1;

		}

		//se verifica si la posicion de la moto principal llega a la posicion de la linea de meta

		if(metaZ >= motoZ){
			cout << "META !!" << endl;
			meta = true;

			//se decide quien queda en primer lugar
			if(motoZ < motoZ_contra)
				primer_lugar = true;
		}

		pistaZ += 1;
		metaZ += 1;
		
		if(ir_izq && direccion > -1.5)
	        direccion -= .05;

	    if(ir_der && direccion < 1.5)
	        direccion += .05;

	    //jugador contrario

	    camY_contra = 0;

	    if(dir == 1 && direccion_contra > -1.5){
	    	direccion_contra -= .05;
	    	camY_contra = 45;
	    }
	    if(dir == 2 && direccion_contra < 1.5){
	    	direccion_contra += .05;
	    	camY_contra = -45;
	    }

	    if(revasa == 1)
	    	motoZ_contra-=.1;

	    if(revasa == 2)
	    	motoZ_contra+=.1;

	    if(_turbo == 1)
	    	turbo = true;

	    if(turbo_activo)
	    	motoZ -= .2;
	}

	
    
    glutPostRedisplay();
    glutTimerFunc(Retardo,timer, 1);
}

void keyInput(unsigned char key, int x, int y)
{
    if(!meta){
        switch (key){
            
            case 'z':
                camY=45;
                ir_der = false;
                ir_del = false;
                ir_izq = true;
                
                break;
            case 'c':
                camY=-45;
                ir_izq = false;
                ir_del = false;
                ir_der = true;
                
                break;
            case 'x':
                camY=0;
                ir_del = true;
                ir_der = false;
                ir_izq = false;
                break;

            case 't':
            	if(turbo)
            		turbo_activo = true;
                break;

        }
    }
    glutPostRedisplay();
}

//ventana
void reshape(int w, int h)
{
    if(w<WIDTH|| h<HEIGHT){
        glutReshapeWindow(WIDTH,HEIGHT);
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, w / h, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char *argv[])
{

	srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(350, 10);
    glutCreateWindow("Super Burnout - Atari Jaguar");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyInput);
    glutReshapeFunc(reshape);
    glutTimerFunc(Retardo,timer, 1);
    glutMainLoop();
    return 0;
}
