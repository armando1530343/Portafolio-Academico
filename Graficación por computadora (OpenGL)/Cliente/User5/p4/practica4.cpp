#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#define SIZE 600
#define PI 3.141592654


using namespace std;

double zoom = 0.4;    //Valor del zoom de la camara
double AngleX = 30.0;      //Grados de rotacion del eje X
double AngleY = 30.0;    //Grados de rotacion del eje Y
double AngleZ = 0.0;


//tamaño de la ventana
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
// figura en 3d
void figura3D(float radio, int anchura,  GLfloat LADOS, float colores[], float colores2[], bool sombras) {
    GLfloat X = 0, Y = 0, Z = 0, angle;
    glTranslatef(X,Y,Z);
    GLfloat Puntos[2][500][3];
    int Contador = 0;
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
        glColor3f(colores2[0], colores2[1], colores2[2]);
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
    float *color = colores;
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

        if(sombras){
	        color[0] -= colores[0]/LADOS;
	        color[1] -= colores[1]/LADOS;
	        color[2] -= colores[2]/LADOS;
	    }
    }
}

// Funcion que controla los eventos de dibujo de la aplicacion.
void display(void)
{
	glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -60);//Posicion de iniciado        
    glRotatef(AngleX, 1.0, 0.0, 0.0);//Controla la vista de la camara en X
    glRotatef(AngleY, 0.0, 1.0, 0.0);//Controla la vista de la camara en Y
    glRotatef(AngleZ, 0.0, 0.0, 1.0);//Controla la vista de la camara en Z
    glScalef(zoom, zoom, zoom);//Controla el Zoom

    float *colores = new float[3]{.6,.6,.6};
    float *colores2 = new float[3]{.8,.8,.8};


    //mesa escritorio
    for(int i = -1; i < 4; i++){
    	for(int j = 0; j < 2; j++){
    		colores = new float[3]{.6,.6,.6};
	    	colores2 = new float[3]{.8,.8,.8};
	    	glPushMatrix();
		    glTranslatef(-14 * i, 0, 14 * j);
		    glRotatef(90, 1, 0, 0);
		    glRotatef(45, 0, 0, 1);
		    figura3D(10, 1, 4, colores, colores2, true);
		    glPopMatrix();
    	}
    	
    }
    //muro amplio
    for(int i = -1; i < 1; i++){
    	for(int j = 0; j < 2; j++){
    		for(int z = 0; z < 40; z++){
    			colores = new float[3]{.7,.7,.7};
		    	colores2 = new float[3]{.9,.9,.9};
		    	glPushMatrix();
			    glTranslatef(-10 * i, -z, 12 * j);
			    glRotatef(90, 1, 0, 0);
			    glRotatef(45, 0, 0, 1);
			    figura3D(10, 1, 4, colores, colores2, true);
			    glPopMatrix();
    		}
    		
    	}
    	
    }
    //cajones
    for(int i = 0; i < 4; i++){
    	glPushMatrix();
		glTranslatef(-2, -9 * i, 20);
	    for(int j = 0; j < 4; j++){
	    	colores = new float[3]{.7,.7,.7};
	    	colores2 = new float[3]{.9,.9,.9};
	    	glPushMatrix();
		    glTranslatef( 4.8 * j, -6, 0);
		    //glRotatef(90, 1, 0, 0);
		    glRotatef(45, 0, 0, 1);
		    figura3D(6, 1, 4, colores, colores2, true);
		    glPopMatrix();
	    }
	    colores = new float[3]{.6,.6,.6};
	    colores2 = new float[3]{.8,.8,.8};
	    glPopMatrix();
	    glPushMatrix();
	    glTranslatef( 5, -9 * (.7+i), 21);
	    //glRotatef(90, 1, 0, 0);
	    //glRotatef(45, 0, 0, 1);
	    figura3D(1, 1, 100, colores, colores2, true);
	    glPopMatrix();
    }
    //pared derecha
    glPushMatrix();
    glTranslatef(17,-7,0);
    for(int i = 0; i < 3; i++){
    	for(int j = 0; j < 2; j++){
    		colores = new float[3]{.6,.6,.6};
	    	colores2 = new float[3]{.8,.8,.8};
	    	glPushMatrix();
		    glTranslatef(0, -12.4 * i, 13*j);
		    glRotatef(270, 0, 1, 0);
		    glRotatef(45, 0, 0, 1);
		    figura3D(10, 2, 4, colores, colores2, true);
		    glPopMatrix();
    	}
    }
	glPopMatrix();    	
    
    //pared trasera
    glPushMatrix();
    glTranslatef(-14,-7,-6);
    for(int i = 0; i < 3; i++){
    	for(int j = 0; j < 3; j++){
    		colores = new float[3]{.7,.7,.7};
	    	colores2 = new float[3]{.9,.9,.9};
	    	glPushMatrix();
		    glTranslatef(-13 * i, -12.5 * j, 0);
		    //glRotatef(180, 1, 0, 0);
		    glRotatef(45, 0, 0, 1);
		    figura3D(10, 1, 4, colores, colores2, true);
		    glPopMatrix();
    	}
    }
    glPopMatrix();

    //pared izquierdo
    glPushMatrix();
    glTranslatef(-48,-7,0);
    for(int i = 0; i < 3; i++){
    	for(int j = 0; j < 2; j++){
    		colores = new float[3]{.5,.5,.5};
	    	colores2 = new float[3]{.7,.7,.7};
	    	glPushMatrix();
		    glTranslatef(0, -12.4 * i, 13*j);
		    glRotatef(270, 0, 1, 0);
		    glRotatef(45, 0, 0, 1);
		    figura3D(10, 1, 4, colores, colores2, true);
		    glPopMatrix();
    	}
    }
	glPopMatrix();

	//caja1
	glPushMatrix();
    glTranslatef(-8,0,-5);
	for(int i = 0; i < 4; i++){
		colores = new float[3]{.5,.5,.5};
		colores2 = new float[3]{.7,.7,.7};
		glPushMatrix();
		glTranslatef(3*i, 4, 0);
		glRotatef(270, 0, 1, 0);
		glRotatef(45, 0, 0, 1);
		figura3D(4, 4, 4, colores, colores2, true);
		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(3, 4, 4);
	glRotatef(45, 0, 0, 1);
	figura3D(3, 1, 4, colores, colores2, true);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(9.5, 4, 4);
	glRotatef(45, 0, 0, 1);
	figura3D(3, 1, 4, colores, colores2, true);
	glPopMatrix();
	glPopMatrix();
	//caja2
	glPushMatrix();
    glTranslatef(-35,0,-5);
	for(int i = 0; i < 4; i++){
		colores = new float[3]{.5,.5,.5};
		colores2 = new float[3]{.7,.7,.7};
		glPushMatrix();
		glTranslatef(3*i, 4, 0);
		glRotatef(270, 0, 1, 0);
		glRotatef(45, 0, 0, 1);
		figura3D(4, 4, 4, colores, colores2, true);
		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(3, 4, 4);
	glRotatef(45, 0, 0, 1);
	figura3D(3, 1, 4, colores, colores2, true);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(9.5, 4, 4);
	glRotatef(45, 0, 0, 1);
	figura3D(3, 1, 4, colores, colores2, true);
	glPopMatrix();
	glPopMatrix();

	//tabla larga
	glPushMatrix();
	glTranslatef(-15, 4, -6);
	colores = new float[3]{.5,.5,.5};
	colores2 = new float[3]{.7,.7,.7};
	for(int i = 0; i < 10; i++){
		glPushMatrix();
		glTranslatef(0,5*i,0);
		glRotatef(45, 0, 0, 1);
		figura3D(4, 1, 4, colores, colores2, true);
		glPopMatrix();	
	}	
	glPopMatrix();

	//tabla larga
	glPushMatrix();
	glTranslatef(-15, 52, -4);
	colores = new float[3]{.7,.7,.7};
	colores2 = new float[3]{.9,.9,.9};
	for(int i = 0; i < 5; i++){
		glPushMatrix();
		glTranslatef(0,0,5*i);
		glRotatef(90, 1, 0, 0);
		glRotatef(45, 0, 0, 1);
		figura3D(4, 1, 4, colores, colores2, true);
		glPopMatrix();	
	}	
	glPopMatrix();

	//barra superior
	glPushMatrix();
    glTranslatef(-30,46.5,17);
	for(int i = 0; i < 15; i++){
		colores = new float[3]{.6,.6,.6};
		colores2 = new float[3]{.8,.8,.8};
		glPushMatrix();
		glTranslatef(2*i, 4, 0);
		glRotatef(270, 0, 1, 0);
		glRotatef(45, 0, 0, 1);
		figura3D(2, 2, 4, colores, colores2, true);
		glPopMatrix();
	}
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
// Funcion que inicializa el programa iniciando el modo de profundidad de OpenGL
void init(void)
{
    glEnable(GL_DEPTH_TEST); 
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SIZE, SIZE);
    glutInitWindowPosition(350, 10);
    glutCreateWindow("Escritorio 3D");
    init(); 
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}