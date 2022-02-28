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

double zoom = 0.5;    //Valor del zoom de la camara
double AngleX = 0.0;      //Grados de rotacion del eje X
double AngleY = 0.0;    //Grados de rotacion del eje Y
double AngleZ = 0.0;

int angulo_manecilla1 = 35;
int angulo_manecilla2 = 145;

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
//funcion que dibuja un conjunto de figuras3D en una circunferencia para formar un ARO
void aro(int posx, int posy, int posz, double radio){
    for(int ang = 0; ang < 361; ang++){
        float x = radio * cos(ang*PI/180) + posx;
        float y = radio * sin(ang*PI/180) + posy;

        float colores[3] = {.64, .16, .16};
        float colores2[3] = {.8,.8,.8};
        glPushMatrix();
	    glTranslatef(x,y,posz);
	    glRotatef(90, 1, 0, 0);
	    glRotatef(ang, 0, 1, 0);
	    glRotatef(45, 0, 0, 1);
	    figura3D(1, 1, 4, colores, colores2, true);
	    glPopMatrix();
    }
    glEnd();
}

// Funcion que controla los eventos de dibujo de la aplicacion.
void display(void)
{
	glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, -10, -60);//Posicion de iniciado        
    glRotatef(AngleX, 1.0, 0.0, 0.0);//Controla la vista de la camara en X
    glRotatef(AngleY, 0.0, 1.0, 0.0);//Controla la vista de la camara en Y
    glRotatef(AngleZ, 0.0, 0.0, 1.0);//Controla la vista de la camara en Z
    glScalef(zoom, zoom, zoom);//Controla el Zoom

    float *colores = new float[3]{1,1,1};
    float *colores2 = new float[3]{.8,.8,.8};

    //Aros que forman el reloj
    aro(0,10,5, 30);
    aro(0,10,-5, 30);

    //circulo centro
    glPushMatrix();
    glTranslatef(0,9,1);
    figura3D(6, 2, 100, colores, colores2, true);
    glPopMatrix();

    //----------------------------------

    //soporte pequeño de la derecha
    colores = new float[3]{.8,.8,.8};
    glPushMatrix();
    glTranslatef(30,9,5);
    figura3D(.3, 10, 100, colores, colores2, true);
    glPopMatrix();

    //soporte pequeño de la izquierda
    colores = new float[3]{.8,.8,.8};
    glPushMatrix();
    glTranslatef(-30,9,5);
    figura3D(.3, 10, 100, colores, colores2, true);
    glPopMatrix();

    //soporte horizontal izquierda
    colores = new float[3]{.8,.8,.8};
    glPushMatrix();
    glTranslatef(-30,9,0);
    glRotatef(270, 0, 1, 0);
    figura3D(.3, 24, 100, colores, colores2, true);
    glPopMatrix();

    //soporte horizontal derecha
    colores = new float[3]{.8,.8,.8};
    glPushMatrix();
    glTranslatef(6,9,0);
    glRotatef(270, 0, 1, 0);
    figura3D(.3, 24, 100, colores, colores2, true);
    glPopMatrix();
    //-----------------------------------
    //soporte pequeño de abajo
    colores = new float[3]{.8,.8,.8};
    glPushMatrix();
    glTranslatef(0,-20,5);
    figura3D(.3, 10, 100, colores, colores2, true);
    glPopMatrix();

    //soporte pequeño de arriba
    colores = new float[3]{.8,.8,.8};
    glPushMatrix();
    glTranslatef(0,40,5);
    figura3D(.3, 10, 100, colores, colores2, true);
    glPopMatrix();

    //soporte vertical arriba
    colores = new float[3]{.8,.8,.8};
    glPushMatrix();
    glTranslatef(0,40,0);
    glRotatef(270, 1, 0, 0);
    figura3D(.3, 26, 100, colores, colores2, true);
    glPopMatrix();

    //soporte vertical abajo
    colores = new float[3]{.8,.8,.8};
    glPushMatrix();
    glTranslatef(0,-20,0);
    glRotatef(90, 1, 0, 0);
    figura3D(.3, 24, 100, colores, colores2, true);
    glPopMatrix();
    //--------------------------------------
    //manecilla 1
    colores = new float[3]{1,.8,0};
    colores2 = new float[3]{1,.8,0};
    glPushMatrix();
    glTranslatef(0,8,2);
    glRotatef(90, 0, 1, 0);
    glRotatef(angulo_manecilla1, 1, 0, 0);
    figura3D(1, 20, 4, colores, colores2, true);
    glPopMatrix();

    //manecilla 2
    colores = new float[3]{1,.8,0};
    colores2 = new float[3]{1,.8,0};
    glPushMatrix();
    glTranslatef(0,8,2);
    glRotatef(90, 0, 1, 0);
    glRotatef(angulo_manecilla2, 1, 0, 0);
    figura3D(1, 25, 4, colores, colores2, true);
    glPopMatrix();

    //tornillo centro de manecillas
    colores = new float[3]{1,.8,0};
    colores2 = new float[3]{1,.8,0};
    glPushMatrix();
    glTranslatef(0,9,4);
    figura3D(1.3, 1, 100, colores, colores2, true);
    glPopMatrix();
    //---------------------------------------
    colores = new float[3]{1,.8,0};
    colores2 = new float[3]{1,.8,0};
    glPushMatrix();
    glTranslatef(0,50,-2);
    figura3D(2, 3, 100, colores, colores2, true);
    glPopMatrix();

    colores = new float[3]{1,.8,0};
    colores2 = new float[3]{1,.8,0};
    glPushMatrix();
    glTranslatef(0,50,5);
    figura3D(1, 7, 100, colores, colores2, true);
    glPopMatrix();

    colores = new float[3]{1,1,1};
    colores2 = new float[3]{.8,.8,.8};
    glPushMatrix();
    glTranslatef(0,40,4);
    glRotatef(90, 1, 0, 0);
    figura3D(.3, 10, 100, colores, colores2, true);
    glPopMatrix();

    glFlush(); 

    glutSwapBuffers();
}

void timer(int value){

	angulo_manecilla1++;
	angulo_manecilla2+= 5;
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
    cout<<"Teclas de Control:"<<endl;
    cout<<" x : rotacion eje x"<<endl;
    cout<<" y : rotacion eje y"<<endl;
    cout<<" z : rotacion eje z"<<endl;
    cout<<" + : Acercamiento"<<endl;
    cout<<" - : Alejamiento"<<endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SIZE, SIZE);
    glutInitWindowPosition(350, 10);
    glutCreateWindow("Reloj 3D");
    init(); 
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutReshapeFunc(reshape);
    glutTimerFunc(Retardo,timer, 1);
    glutMainLoop();
    return 0;
}

/*

Desarrollo Experimental:

En el desarrollo de la practica fue utilizado el lenguaje de programacion de c++ y tambien implementando las funciones de openGl
y el objetivo es dibujar un reloj en 3D, que para dibujarlo, comprende de dos aros y las varillas del soporte mas las manecillas.
Primetamente se construyo una una funcion llamada "figura3D()" la cual dibuja un conjunto de poligonos para formar un prisma, y 
las caracteristicas dependem de los parametros los cuales son el radio del prisma, la anchura, el numero de lados segun la figura
que se quiera y los colores.
Despues, para dibujar los aros se hizo una funcion diferente llamada "aro()", y dentro de esta se llama la funcion de figura3D()
en un ciclo "for" dandole las caracteristicas de un prisma cuadrangular la cual dibujara 360 iguales pero de forma de circunferencia
dando las coordenadas especificas, y asi al final se crea un aro, que en pocas palabras es un conjunto de 360 figuras 3D en forma circular.
Por ultimo, para los soportes de los aros (varillas), se llama tantas veces a figura3D() como varillas existan de forma de cilindro
pero con un radio muy delgado y se posicionan segun corresponda calculando sus posiciones, esto igual para las manecillas.
Para las manecillas, cada una contiene una funcion rotate(), y aqui solo se creo una variable diferente para cada manecilla la cual 
ira incrementando el angulo de rotacion en una funcion Timer(), y al final simula que las manecillas giran con diferente velocidad.

*/