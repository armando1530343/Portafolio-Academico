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

int radio_pentagono = 10;
int ancho = 10;

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

void pentagono(){
    GLfloat Puntos[500][2], angle;
    int Contador = 0;

    float x1, y1, x2, y2;
    
    glBegin(GL_POLYGON);
    glColor3f(1,0,0);
    Contador = 0;
    for (angle = 0.0f; angle <= (2.0f * PI); angle += (2.0f * PI) / 5) {
        Puntos[Contador][0] = radio_pentagono * sin(angle);
        Puntos[Contador][1] = radio_pentagono * cos(angle);   
        glVertex2f(Puntos[Contador][0], Puntos[Contador][1]);
        Contador++;
    }
    glEnd();

    for (int i = 0; i < 2; ++i){
        glBegin(GL_LINE_LOOP);
        glColor3f(0,0,1);
        Contador = 0;
        for (angle = 0.0f; angle <= (2.0f * PI); angle += (2.0f * PI) / 5) {
            Puntos[Contador][0] = radio_pentagono * sin(angle);
            Puntos[Contador][1] = radio_pentagono * cos(angle);   
            glVertex3f(Puntos[Contador][0], Puntos[Contador][1], i == 0 ? .1 : -.1);
            Contador++;
        }
        glEnd();
    }


}
void rectangulo(){
    glBegin(GL_POLYGON);
    glColor3f(color,0,0);
    glVertex2f(0, 0);
    glVertex2f(lado, 0);
    glVertex2f(lado, ancho);
    glVertex2f(0, ancho);
    glEnd();
    for(int i = 0; i < 2; i++){
        glBegin(GL_LINE_LOOP);
        glColor3f(1,1,1);
        glVertex3f(0, 0, i == 0 ? .1 : -.1);
        glVertex3f(lado, 0, i == 0 ? .1 : -.1);
        glVertex3f(lado, ancho, i == 0 ? .1 : -.1);
        glVertex3f(0, ancho, i == 0 ? .1 : -.1);
        glEnd();
    }
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

    pentagono();
    rectangulo();

    

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
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SIZE, SIZE);
    glutInitWindowPosition(350, 10);
    glutCreateWindow("Prisma Pentagono");
    init(); 
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutReshapeFunc(reshape);
    glutTimerFunc(Retardo,timer, 1);
    glutMainLoop();
    return 0;
}