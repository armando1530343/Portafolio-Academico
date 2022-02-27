#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#define SIZE 600
#define PI 3.141592654 
#define Retardo 100


using namespace std;

double zoom = 0.3;    //Valor del zoom de la camara
double AngleX = 10.0;      //Grados de rotacion del eje X
double AngleY = -35.0;    //Grados de rotacion del eje Y
double AngleZ = 0.0;

int avanza = -30;


// Funcion que controla el tamaño de la ventana
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
// Funcion que dibuja una figura en 3d
// figura tridimensional con parametros definidos
void figura3D(float radio, float ancho,  GLfloat LADOS, float colores[]) {
    GLfloat X = 0, Y = 0, Z = 0, angle;
    glTranslatef(X,Y,Z);
    GLfloat Puntos[2][500][3];
    int Contador = 0;
    //se crean las dos bases del prisma y para ello se usa GL_POLYGON
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
        glColor3f(i == 1 ? colores[0]*.8 : colores[0]/2, i == 1 ? colores[1]*.8 : colores[1]/2, i == 1 ? colores[2]*.8 : colores[2]/2);
        Contador = 0;
        for (angle = 0.0f; angle <= (2.0f * PI); angle += (2.0f * PI) / LADOS) {
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

    //se crean las caras del prisma segun el numero de lados
    for (Contador = 0; Contador < LADOS; Contador++) {
        glBegin(GL_POLYGON);
        
        glColor3f(color[0], color[1], color[2]);
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

        if(Contador < int(LADOS/2)){
            color[0] -= colores[0]/(LADOS/2);
            color[1] -= colores[1]/(LADOS/2);
            color[2] -= colores[2]/(LADOS/2);
        }
        else{
            color[0] += colores[0]/(LADOS/2);
            color[1] += colores[1]/(LADOS/2);
            color[2] += colores[2]/(LADOS/2);
        }

        
    }
}
//funcion que dibuja un conjunto de figuras3D en una circunferencia para formar un ARO
void rueda(double radio){
    for(int ang = 0; ang < 361; ang++){
        float x = radio * cos(ang*PI/180);
        float y = radio * sin(ang*PI/180);

        float colores[3] = {.2,.2,.2};
        glPushMatrix();
	    glTranslatef(x,y,0);
	    glRotatef(90, 1, 0, 0);
	    glRotatef(ang, 0, 1, 0);
	    glRotatef(45, 0, 0, 1);
	    figura3D(radio*.6, 1, 4, colores);
	    glPopMatrix();
    }
    float *colores = new float[3]{.2,.2,.2};
    glPushMatrix();
    glTranslatef(0,-radio/2,0);
    glRotatef(90, 1, 0, 0);
    figura3D(.5, radio*1.5, 100, colores);
    glPopMatrix();

    colores = new float[3]{.2,.2,.2};
    glPushMatrix();
    glTranslatef(radio/2,0,0);
    glRotatef(90, 0, 1, 0);
    figura3D(.5, radio*1.5, 100, colores);
    glPopMatrix();

    colores = new float[3]{.2,.2,.2};
    glPushMatrix();
    glTranslatef(0,0,0);
    glRotatef(0, 1, 0, 0);
    figura3D(.5, 30, 100, colores);
    glPopMatrix();
}

// Funcion que controla los eventos de dibujo de la aplicacion.
void display(void)
{
	glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, -10, -60);//Posicion de iniciado        
    glRotatef(AngleX, 1.0, 0.0, 0.0);//Controla la vista de la camara en X
    glRotatef(AngleY, 0.0, 1.0, 0.0);//Controla la vista de la camara en Y
    glRotatef(AngleZ, 0.0, 0.0, 1.0);//Controla la vista de la camara en Z
    glScalef(zoom, zoom, zoom);//Controla el Zoom

    float *colores = new float[3]{1,1,0};
    float *colores2 = new float[3]{.8,.8,.8};

    //--------CAMION---------
    glPushMatrix();
    glTranslatef(avanza,0,0);

    	//-----------LLANTAS----------
    	for (int i = 0; i < 4; ++i){
    		glPushMatrix();
		    glTranslatef(i == 0 || i == 2 ? -40 : 40,0, i < 2 ? 19 : -19);
		    glRotatef(0,1,0,0);
		    if(i >= 2) glRotatef(180, 1,0,0);
		    glRotatef(i < 2 ? -(avanza*5) : avanza*5 , 0,0,1);
	    	rueda(8);
	    	glPopMatrix();
    	}

    	//------------------BASE---------------------
    	//rectangulo centro
    	glPushMatrix();
	    glTranslatef(0,5,0);
	    glRotatef(90,1,0,0);
	    glRotatef(45,0,0,1);
    	figura3D(35, 3, 4, colores);
    	glPopMatrix();
    	//rectangulos base 
    	int z;
    	for (int j = 0; j < 2; ++j)
    	{
    		int x1 = j == 0 ? -37 : 37;
    		int x2 = j == 0 ? -39 : 39;
    		for (int i = 0; i < 2; ++i){
	    		colores = new float[3]{1,1,0};
		    	glPushMatrix();
			    glTranslatef(i == 0 ? x1 : x2,5,0);
			    glRotatef(90,1,0,0);
			    glRotatef(45,0,0,1);
		    	figura3D(18, 3, 4, colores);
		    	glPopMatrix();
	    	}
	    	z = 18;
	    	for (int i = 0; i < 4; ++i){
	    		colores = new float[3]{1,1,0};
		    	glPushMatrix();
			    glTranslatef(j == 0 ? 58 : -58,5,z);
			    glRotatef(90,1,0,0);
			    glRotatef(45,0,0,1);
		    	figura3D(9, 3, 4, colores);
		    	glPopMatrix();
		    	z -= 12;
	    	}
    	}
    	//---------BASE DE APOYO DE TANQUES----------
    	float x;
    	for (int i = 0; i < 2; ++i)
    	{
    		colores = new float[3]{1,1,0};
	    	glPushMatrix();
		    glTranslatef(-58,8,i == 0 ? 18 : -18);
		    glRotatef(90,1,0,0);
		    glRotatef(45,0,0,1);
	    	figura3D(9, 5, 4, colores);
	    	glPopMatrix();

	    	x = -18;
	    	for (int j = 0; j < 5; ++j){
	    		colores = new float[3]{1,1,0};
	    		glPushMatrix();
			    glTranslatef(x, 8,i == 0 ? 18 : -18);
			    glRotatef(90,1,0,0);
			    glRotatef(45,0,0,1);
		    	figura3D(9, 5, 4, colores);
		    	glPopMatrix();
		    	x += 9;
	    	}
    	}      	
    	for (int i = 18; true; --i){
    		x = -58;
    		for (int j = 0; j < 11 ; ++j){
    			colores = new float[3]{1,1,0};
	    		glPushMatrix();
			    glTranslatef(x, 13,i);
			    glRotatef(90,1,0,0);
			    glRotatef(45,0,0,1);
		    	figura3D(9, 5, 4, colores);
		    	glPopMatrix();
		    	x += 11;
    		}
    		if(i <= -18) break;    		
    	}

    	
    	for (int i = 0; i < 4; ++i){
    		z = 18;
    		for (int j = 0; j < 4; ++j){
	    		colores = new float[3]{1,1,0};
		    	glPushMatrix();
			    glTranslatef(58,5 + i*3,z);
			    glRotatef(90,1,0,0);
			    glRotatef(45,0,0,1);
		    	figura3D(9, 3, 4, colores);
		    	glPopMatrix();
		    	z -= 12;
		    }
    	}
    	//----------CABINA CAMION ------------------------
    	for (int n = 0; n < 4; ++n){
    		for (int i = 0; i < 12; ++i){
	    		z = 18;
	    		for (int j = 0; j < 4; ++j){
	    			if((n == 1 && i < 11 && i > 5) || (n == 0 && j > 0 && j < 3 && i > 5 && i < 11)){
	    				z -= 12;
	    				continue;
	    			}
		    		colores = new float[3]{1,1,0};
			    	glPushMatrix();
				    glTranslatef(58 - 12*n,12 + i*3,z);
				    glRotatef(90,1,0,0);
				    glRotatef(45,0,0,1);
			    	figura3D(9, 3, 4, colores);
			    	glPopMatrix();
			    	z -= 12;
			    
			    }
	    	}
    	}
    	//---------------TANQUES--------------
    	//
    	for (int i = 0; i < 2; ++i)
    	{
    		colores = new float[3]{0,0,1};
	    	glPushMatrix();
		    glTranslatef(12,33,i == 0 ? 15:-15);
		    glRotatef(90,0,1,0);
	    	figura3D(15, 80, 100, colores);
	    	glPopMatrix();

	    	colores = new float[3]{.7,.7,.7};
	    	glPushMatrix();
		    glTranslatef(-55,20,i == 0 ? 15:-15);
		    glRotatef(90,1,0,0);
	    	figura3D(5, 30, 100, colores);
	    	glPopMatrix();
    	}
    	//---------MANGUERA----------------
    	colores = new float[3]{.7,.7,.7};
    	glPushMatrix();
	    glTranslatef(14, 15, 15);
	    glRotatef(90,1,0,0);
    	figura3D(2, 35, 100, colores);
    	glPopMatrix();
    	colores = new float[3]{.7,.7,.7};
    	glPushMatrix();
	    glTranslatef(13, 49, 15);
	    glRotatef(-90,0,1,0);
	    glRotatef(20,1,0,0);
    	figura3D(2, 60, 100, colores);
    	glPopMatrix();
    	colores = new float[3]{.7,.7,.7};
    	glPushMatrix();
	    glTranslatef(69, 69, 15);
	    glRotatef(-90,0,1,0);
	    glRotatef(0,1,0,0);
    	figura3D(2, 30, 100, colores);
    	glPopMatrix();

    	colores = new float[3]{1,1,0};
    	glPushMatrix();
	    glTranslatef(36, 23, 18);
	    glRotatef(-90,0,1,0);
	    glRotatef(0,1,0,0);
    	figura3D(2, 30, 100, colores);
    	glPopMatrix();
    	colores = new float[3]{1,1,0};
    	glPushMatrix();
	    glTranslatef(36, 23, -18);
	    glRotatef(-90,0,1,0);
	    glRotatef(0,1,0,0);
    	figura3D(2, 30, 100, colores);
    	glPopMatrix();
    	colores = new float[3]{1,1,0};
    	glPushMatrix();
	    glTranslatef(36, 18, 0);
	    glRotatef(-90,0,1,0);
	    glRotatef(45,0,0,1);
    	figura3D(13, 30, 4, colores);
    	glPopMatrix();

    glPopMatrix();

    
    glFlush(); 

    glutSwapBuffers();
}

void timer(int value){

	glutPostRedisplay();
	glutTimerFunc(Retardo,timer, 1);
}
// Funcion que controla las teclas que se presionan.
void teclado(unsigned char key, int x, int y)
{
    switch (key) {
        case 'x':
        	AngleX+=5; 
        	break;
        case 'X':
        	AngleX-=5; 
        	break;
        case 'y':
        	AngleY+=5; 
        	break;
        case 'Y':
        	AngleY-=5; 
        	break;
        case 'w':
        	avanza+=2; 
        	break;
        case 's':
        	avanza-=2; 
        	break;
        
    }
    glutPostRedisplay();
}
// Funcion que inicializa el programa iniciando el modo de profundidad de OpenGL
void init(void)
{
    glEnable(GL_DEPTH_TEST); 
}
int main(int argc, char *argv[])
{
	cout << "CONTROLES\n (W = Avanza Adelante)\n (S = Reversa)\n (x, X = camara eje X)\n (y, Y = camara eje Y)" << endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, SIZE);
    glutInitWindowPosition(20, 10);
    glutCreateWindow("Recuperacion");
    init(); 
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutReshapeFunc(reshape);
    glutTimerFunc(Retardo,timer, 1);
    glutMainLoop();
    return 0;
}