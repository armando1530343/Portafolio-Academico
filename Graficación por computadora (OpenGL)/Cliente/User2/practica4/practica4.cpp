#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream> 
#define SIZE 650
#define PI 3.141592654 


using namespace std;

// Funcion que dibuja un prisma con determinados lados
void modelo_prisma(float radio, int anchura,  GLfloat LADOS, float colores[]) {
    GLfloat X = 0, Y = 0, Z = 0, angle;
    glTranslatef(X,Y,Z);
    GLfloat Puntos[2][500][3];
    int Contador = 0;
    //se crean las dos bases del prisma y para ello se usa GL_POLYGON
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
        glColor3f(colores[0], colores[1], colores[2]);
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
//funcion que dibuja un tubo arco
void arco(int posx, int posy, int posz){

    float color[3] = {.8, .8, .8};
    for(int ang = 0; ang < 90; ang++){
        float x = 15 * cos(ang*PI/180) + posx;
        float y = 15 * sin(ang*PI/180) + posy;

        glPushMatrix();
	    glTranslatef(x,y,posz);
	    glRotatef(90, 1, 0, 0);
	    glRotatef(ang, 0, 1, 0);
	    glRotatef(45, 0, 0, 1);
	    modelo_prisma(6, 1, 100, color);
	    glPopMatrix();
    }
    glEnd();
}

//funcion que dibuja dos circulos planos con tornillos alrededor
void estructura_tuercas(int posx, int posy, int posz, int tipo){

    //color de la estructura
    float *color = new float[3]{.6, .6, .6};

    //cantidad de circulos planos (2)
    for (int n = 1; n <= 2; ++n)
    {
        glPushMatrix();

        glTranslatef(n == 1 ? posx : tipo == 1 ? posx - 2 : posx, n == 1 ? posy : tipo == 2 ? posy + 6 : posy,posz);
        glRotatef(n ==  1 ? 90 : 270, tipo == 2 ? 1:0, tipo == 1 ? 1:0, 0);
        glRotatef(45, 0, 0, 1);
        //se crea el circulo plano de radio 10
        modelo_prisma(10, 1.5, 100, color);

            //se le asignan los tornillos al circulo plano
            //los tornillos se colocaran en la posicion segun el angulo de 0 a 360
            //siempre y cuando el valor del angulo sea multiplo de 45 (angulo % 45 == 0; 8 tornillos en total)
            for (int i = 0; i <= 360; ++i)
            {
                color = new float[3]{.8, .8, .8};
                float x = 8 * cos(i*PI/180);
                float y = 8 * sin(i*PI/180);
                if(i % 45 == 0){
                    glPushMatrix();
                    glTranslatef(x,y,1);
                    modelo_prisma(1, 1, 6, color);

                        glPushMatrix();
                        glTranslatef(0,0,1);
                        modelo_prisma(.5, tipo == 1 ? 1 : 6, 100, color);
                        glPopMatrix();

                    glPopMatrix();
                }
            }

        glPopMatrix();
        glEnd();
    }
    
}
double zoom = 0.5;//zoom camara
double AngleX = 0.0;//rotacion eje X
double AngleY = 45.0;//rotacion eje Y
double AngleZ = 0.0;
//funcion que despliega las figuras creadas
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

    //tubo arco trasero
    arco(10, 20, 0);
    //primer juego de tuercas superior
    estructura_tuercas(10, 35, 0, 1);

    //tubo horizontal superior
    float *color = new float[3]{.8, .8, .8};
    glPushMatrix();
    glTranslatef(10,35,0);
    glRotatef(90, 0, 1, 0);
    modelo_prisma(6,45,100, color);
    glPopMatrix();

    //segundo juego de tuercas superior
    estructura_tuercas(-20, 35, 0, 1);
    //tercer juego de tuercas superior
    estructura_tuercas(-35, 35, 0, 1);

    //tubo vertical
    color = new float[3]{.8, .8, .8};
    glPushMatrix();
    glTranslatef(25,20,0);
    glRotatef(270, 1, 0, 0);
    modelo_prisma(6,25,100, color);
    glPopMatrix();

    estructura_tuercas(25, 15, 0, 2);
    estructura_tuercas(25, -5, 0, 2);

    //tubo arco inferior derecho
    glPushMatrix();
    glTranslatef(25,-5,-15);
    glRotatef(180,1, 0, 0);
    glRotatef(90,0, 1, 0);
    arco(0, 0, 0);
    glPopMatrix();

    //tubo arco inferior izquierdo
    glPushMatrix();
    glTranslatef(25,-5,15);
    glRotatef(180,1, 0, 0);
    glRotatef(270,0, 1, 0);
    arco(0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(25,-20,10);
    glRotatef(90,0, 0, 1);
    glRotatef(90,1, 0, 0);
    estructura_tuercas(0, 0, 0, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(25,-20,-16);
    glRotatef(90,0, 0, 1);
    glRotatef(90,1, 0, 0);
    estructura_tuercas(0, 0, 0, 2);
    glPopMatrix();

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
    cout<<"Controles: \n\n"<<
    "[x] [X] //control de camara eje X\n"<<
    "[y] [Y] //control de camara eje Y\n"<<
    "[z] [Z] //control de camara eje Z\n"<<
    "[+] [-] //zoom\n"<<endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SIZE, SIZE);
    glutInitWindowPosition(100, 10);
    glutCreateWindow("Practica 4");
    init(); 
    glutDisplayFunc(display);    
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keys);
    glutMainLoop();
    return 0;
}