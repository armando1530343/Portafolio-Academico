#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>
#include <time.h>
#include <string.h>

#define SIZE 650 //Ventana
#define PI 3.1416//Valor de PI

double zoom = 0.041;//0.015;//0.041;     //Valor del zoom de la camara
double AngleX = 0;      //Grados de rotacion del eje X
double AngleY = 0;    //Grados de rotacion del eje Y
double AngleZ = 0;

int avanza = 140; // recorrido de la camara hacia adelante o atras
int avanzaLado = 0; //recorrido de la camara hacia los lados
int gira = 0; //giro de la camara

using namespace std;

// Funcion que dibuja una figura en 3d
void DibujaCilindro(float rad, int anchura,  GLfloat LADOS, float colores1[], float colores2[]) {
    GLfloat X = 0, Y = 0, Z = 0, angle;
    glTranslatef(X, Y, Z);
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    GLfloat radio;
    GLfloat Puntos[2][500][3];
    int Contador = 0;
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
        glColor3f(colores2[0], colores2[1], colores2[2]);
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
    }
    for (Contador = 0; Contador < LADOS; Contador++) {
        glBegin(GL_POLYGON);
        
        glColor3f(colores1[0], colores1[1], colores1[2]);
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

float colores1[3], colores2[3], colores3[3];

void Display(void) {

    int alt = 60, i,j;

    int xInicio = -1240;
    int zInicio = 1240;
    int espacioBloque = 350;

    //se definen los colores  del plano del piso
    colores1[0] = 1; colores1[1] = 0; colores1[2] = 0;
    colores2[0] = .5; colores2[1] = .5; colores2[2] = .5;

    //se grafica el plano del suelo
    glPushMatrix();
    glTranslatef(0,0,3700);
    glRotatef(AngleY,0,1,0);
    DibujaCilindro(2000, 1, 4, colores1, colores2);    
    glRotatef(-45,0,0,1);
    glRotatef(-90,1,0,0);

    
    //ciclo qie grafica las paredes

    for(i = 1; i <= 8; i++){
	    for(j = 1; j <= 8; j++){
	    	if(i == 1 && (j == 4 || j == 6 || j == 7)) continue;
	    	if(i == 2 && (j == 2 || j == 3 || j == 4 || j == 5 || j == 7)) continue;
	    	if(i == 3 && (j == 2 || j == 4 || j == 5 || j == 6 || j == 7)) continue;
	    	if(i == 4 && (j == 1 || j == 2 || j == 3 || j == 4 || j == 7)) continue;
	    	if(i == 5 && (j == 4 || j == 6 || j == 7)) continue;
	    	if(i == 6 && (j == 2 || j == 3 || j == 4 || j == 6 || j == 7)) continue;
	    	if(i == 7 && (j == 1 || j == 2 || j == 4 || j == 6 || j == 7)) continue;
	    	
	    	glPushMatrix();
	    	//las coloca en la posicion de cada una
		    glTranslatef(xInicio+(espacioBloque*i),0,(i < 8 ? zInicio : (zInicio+espacioBloque))-(espacioBloque*j));
		    //se definen los colores de cada pared
		    colores3[0] = (rand()%10)*.1; colores3[1] = (rand()%10)*.1; colores3[2] = (rand()%10)*.1;
		    DibujaCilindro(250, 250, 4, colores3, colores2);
		    glPopMatrix();
	    }
	}
	for(j = 1; j <= 8; j++){
    	glPushMatrix();
	    glTranslatef(xInicio-espacioBloque,0,(zInicio+espacioBloque)-(espacioBloque*j));
	    DibujaCilindro(250, 250, 4, colores3, colores2);
	    glPopMatrix();
	}
	glPushMatrix();
    glTranslatef(xInicio,0,zInicio-(espacioBloque*8));
    DibujaCilindro(250, 250, 4, colores3, colores2);
    glPopMatrix();
    glPopMatrix();
}
// Funcion que inicializa el programa iniciando el modo de profundidad de OpenGL
void init(void)
{
    glEnable(GL_DEPTH_TEST); 
}


string dire = "";
// Funcion que controla las teclas que se presionan.
void keyboardCallbackProc(unsigned char key, int x, int y)
{

	
	//teclas de accion para el movimiento de la camara en el laberinto
    switch (key) {
    	//movimiento de giro
        case 'j':
        	if(gira > -500) gira-=500;  
        	if(gira == -500) dire = "Izquierda";
        	if(gira == 0) dire = "Frente";
        	cout<<"Direccion: "<<dire<<endl;
        	break;
        case 'l':
        	if(gira < 500) gira+=500;
        	if(gira == 500) dire = "Derecha";
        	if(gira == 0) dire = "Frente"; 
        	cout<<"Direccion: "<<dire<<endl; 
        	break;
        case 'a': //avanza lado izquierdo
        	if(gira == -500) avanza+=1; 
        	if(gira == 0) avanzaLado-=1; 
        	if(gira == 500) avanza-=1;
        	break;
        case 'd': //avanza lado derecho
        	if(gira == -500) avanza-=1;
        	if(gira == 0) avanzaLado+=1;
        	if(gira == 500) avanza+=1;
        	break;
        case 'w': //avanza adelante
        	if(gira == -500) avanzaLado-=1;
        	if(gira == 0) avanza-=1;
        	if(gira == 500) avanzaLado+=1;
        	break;
        case 's': //avanza atras
        	if(gira == -500) avanzaLado+=1;
        	if(gira == 0) avanza+=1;
        	if(gira == 500) avanzaLado-=1;
        	break;
        
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
    gluPerspective(60.0, w / h, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

// Funcion que controla los eventos de dibujo de la aplicacion.
void displayCallbackProc(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(avanzaLado,0,avanza,gira,0,0,0,1,0);
    glTranslatef(0, -2, -60);//Posicion de iniciado        
    glRotatef(AngleX, 1.0, 0.0, 0.0);//Controla la vista de la camara en X
    glRotatef(0, 0.0, 1.0, 0.0);//Controla la vista de la camara en Y
    glRotatef(AngleZ, 0.0, 0.0, 1.0);//Controla la vista de la camara en Z*/
    glScalef(zoom, zoom, zoom);//Controla el Zoom
    Display(); 

    glutSwapBuffers();
}

// Funcion principal.
int main(int argc, char *argv[])
{
	srand(time(NULL));
	cout<<"<< Proyecto Grupal 2 - Proyecto 5 >>"<<endl;
	cout<<"Integrantes: "<<endl;
	cout<<" -Martinez Vallejo"<<endl;
	cout<<" -Gonzalez Rendon"<<endl;
	cout<<" -Coronado Briceño"<<endl;
	cout<<" -Rodriguez Maldonado\n"<<endl;
	cout<<"Teclas:"<<endl;
	cout<<" W = avanza adelante"<<endl;
	cout<<" S = avanza atras"<<endl;
	cout<<" A = avanza izquierda"<<endl;
	cout<<" D = avanza derecha"<<endl;
	cout<<" J = gira izquierda"<<endl;
	cout<<" L = gira derecha\n"<<endl;
	cout<<" * Solo realiza un giro de 180 grados por lo que si desea retroceder se tiene que utilizar la tecla S o las de izquierda y derecha dependiendo la posicion "<<endl;
	cout<<" * No colisiona con las paredes (las traspasa)\n\n"<<endl;

    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SIZE, SIZE);
    glutInitWindowPosition(50, 20);
    glutCreateWindow(" Proyecto Grupal 2");
    init(); 
    glutReshapeFunc(reShapeCallbackProc);
    glutDisplayFunc(displayCallbackProc);
    glutKeyboardFunc(keyboardCallbackProc);
    
    glutMainLoop();
    return 0;
}
