#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream> 
#define SIZE 650
#define PI 3.141592654 


using namespace std;

//creacion de modelo en 3D
/*void construir_figura(float radio, float altura,  GLfloat LADOS, double colores[], int n, bool sombra) {
    GLfloat X = 0, Y = 0, Z = 0.0, angle;
    glTranslatef(X,Y,Z);
    GLfloat Puntos[2][500][3];
    int Contador = 0;
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
        glColor3f(colores[0], colores[1], colores[2]);
        if(n == 2)
        	glColor3f(colores[0]*.5, colores[1]*.5, colores[2]*.5);
        Contador = 0;
        for (angle = 0.0f; angle <= (2.0f * PI); angle += (2.0f * PI) / LADOS) {
        	if (n == 1){
	        	Puntos[i][Contador][0] = radio * sin(angle) + X;
	            Puntos[i][Contador][1] = radio * cos(angle) + Y;
	            Puntos[i][Contador][2] = Z;
            }
            else{
            	Puntos[i][Contador][0] = radio * sin(angle) + X;
	            Puntos[i][Contador][1] = Z;
	            Puntos[i][Contador][2] = radio * cos(angle) + Y;
            }
            glVertex3f(Puntos[i][Contador][0], Puntos[i][Contador][1], Puntos[i][Contador][2]);
            Contador++;
        	
        }
        glEnd();
        Z -= altura;
    }
    double *color = colores;

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

        if(sombra){
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
}*/

double lado_pentagono;
float x1, y1, x2, y2;


//funcion que dibuja la madera del barril (Cilindro)
void pentagono(float radio){

    double color[3];

    int lados = 0;


    glBegin(GL_POLYGON);

    for(int ang = 0; ang < 361; ang++){
        float x = radio * cos(ang*PI/180);
        float y = radio * sin(ang*PI/180);

        color[0] = .9; color[1] = .6; color[2] = .0;


        if( ang % 72 == 0){

        	glVertex2f(x, y);

            if(lados < 2){
                if(lados == 0){
                    x1 =(x);
                    y1 =(y);
                }
                else{
                    x2 =(x);
                    y2 =(y);
                }
            }
            else{
                lado_pentagono = sqrt(((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1)));
            }

            lados ++;
        }
        
    }
    glEnd();
}

double zoom = 0.5;//zoom camara
double AngleX = 0.0;//rotacion eje X
double AngleY = 0.0;//rotacion eje Y
double AngleZ = 0.0;//rotacion eje z

//funcion que despliega las figuras creadas
void display(void)
{
	glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -100);//Posicion de iniciado        
    glRotatef(AngleX, 1.0, 0.0, 0.0);//Controla la vista de la camara en X
    glRotatef(AngleY, 0.0, 1.0, 0.0);//Controla la vista de la camara en Y
    glRotatef(AngleZ, 0.0, 0.0, 1.0);//Controla la vista de la camara en Z
    
    glScalef(zoom, zoom, zoom);//Controla el Zoom

    //double color[3];
    

 

    //color[0] = 1.0; color[1] = .6; color[2] = .0;
    glPushMatrix();
    glTranslatef(-15, 40, 0);
    glRotatef(0, 0, 0, 0);
    glRotatef(0, 0, 0, 0);
    glRotatef(18, 0, 0, 1);
    pentagono(20);
    glPopMatrix();

    cout << "Lado del pentagono: " << lado_pentagono << endl;
	
	glFlush(); 

    glutSwapBuffers();
}
// Funcion que controla las teclas que se presionan.
void keys(unsigned char key, int x, int y)
{
    switch (key) {
        case 'X':
        	AngleX+=5; 
        	break;
        case 'x':
            AngleX-=5; 
            break;
        case 'Y':
        	AngleY+=5; 
        	break;
        case 'y':
            AngleY-=5; 
            break;
        case 'Z':
        	AngleZ+=5; 
        	break;
        case 'z':
            AngleZ-=5; 
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
int main(int argc, char *argv[])
{
    cout<<"\nTeclas: x, X, y, Y, z, Z, +, -"<<endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SIZE, SIZE);
    glutInitWindowPosition(150, 20);
    glutCreateWindow("Barril 3D");
    init(); 
    glutDisplayFunc(display);    
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keys);
    glutMainLoop();
    return 0;
}