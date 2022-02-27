#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#define SIZE 500
#define PI 3.141592654


using namespace std;

double zoom = 0.2;
double AngleX = 0.0;
double AngleY = 0.0;
double AngleZ = 0.0;

void circle(float r1, float r2, int ancho,  int lados, float *colores) {
    GLfloat X = 0, Y = 0, Z = 0, angle;
    glTranslatef(X,Y,Z);
    GLfloat Puntos[2][500][3];
    int Contador = 0;
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
        glColor3f(colores[0]-.0, colores[1]-.0, colores[2]-.0);
        Contador = 0;
        for (angle = 0.0f; angle <= (2.0f * PI); angle += (2.0f * PI) / lados) {
            Puntos[i][Contador][0] = (i == 0 ? r1 : r2) * sin(angle) + X;
            Puntos[i][Contador][1] = (i == 0 ? r1 : r2) * cos(angle) + Y;
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

        if(Contador <= lados/2){
            color[0] -= colores[0]/(lados*2);
            color[1] -= colores[1]/(lados*2);
            color[2] -= colores[2]/(lados*2);
        }
        else{
            color[0] += colores[0]/(lados*2);
            color[1] += colores[1]/(lados*2);
            color[2] += colores[2]/(lados*2);
        }


    }
}
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


// Funcion que controla los eventos de dibujo de la aplicacion.
void display(void)
{
    float *c;
	glEnable(GL_DEPTH_TEST);
	glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, -15, -60);//Posicion de iniciado
    glRotatef(AngleX, 1.0, 0.0, 0.0);//Controla la vista de la camara en X
    glRotatef(AngleY, 0.0, 1.0, 0.0);//Controla la vista de la camara en Y
    glRotatef(AngleZ, 0.0, 0.0, 1.0);//Controla la vista de la camara en Z
    glScalef(zoom, zoom, zoom);//Controla el Zoom

    //figura3D(10, 10, 4, new float[3]{.7,.7,.7}, new float[3]{.5,.5,.5});

    //CAJON IGLESIA
    for(int i = 0; i < 2; i++){
        c = new float[3]{.9,.9,.9};
        glPushMatrix();
        glTranslatef(0,0,i == 0 ? 0 : -15);
        glRotatef(90,1,0,0);
        glRotatef(45,0,0,1);
        circle(56, 56, 40, 4, c);
        glPopMatrix();
    }

    //ventanas 1

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++){
            c = new float[3]{.5,.5,.5};
            glPushMatrix();
            glTranslatef(i == 0 ? 40 : -38,30,20 + j*(-30));
            glRotatef(90,0,1,0);
            glRotatef(45,0,0,1);
            circle(7, 7, 2, 4, c);
            glPopMatrix();
        }        
    }


    //CAJON TRIANGULO IGLESIA
    for(int i = 0; i < 2; i++){
        c = new float[3]{.9,.9,.9};
        glPushMatrix();
        glTranslatef(0,40,i == 0 ? 39 : -4);
        circle(40, 40, 50, 4, c);
        glPopMatrix();
    }

    //techo iglesia
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            c = new float[3]{.4,.4,.4};
            glPushMatrix();
            glTranslatef(i == 0 ? -20 : 21,60,j == 0 ? 12 : -27);
            
            glRotatef(90,0,1,0);
            glRotatef(i == 0 ? 45 : -45,1,0,0);
            glRotatef(45,0,0,1);

            circle(41, 41, 2, 4, c);
            glPopMatrix();
        }        
    }

    //torre piso 1
    glPushMatrix();
    glTranslatef(0,0,50);    
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    c = new float[3]{.9,.9,.9};
    circle(15, 15, 90, 4, c);
    glPopMatrix();
    //Puerta
    glPushMatrix();
    glTranslatef(0,0,55);    
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    c = new float[3]{.8,.8,.8};
    circle(8, 8, 25, 4, c);
    glPopMatrix();
    //ventana
    glPushMatrix();
    glTranslatef(0,40,55);    
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    c = new float[3]{.6,.6,.6};
    circle(8, 8, 20, 4, c);
    glPopMatrix();

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            //ventana
            glPushMatrix();
            glTranslatef(i == 0 ? 25 : -25,(j+1)*15,35);   
            glRotatef(90,1,0,0);
            glRotatef(45,0,0,1);
            c = new float[3]{.6,.6,.6};
            circle(8, 8, 10, 4, c);
            glPopMatrix();
        }
    }

    //ventana
    glPushMatrix();
    glTranslatef(0,100,55);    
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    c = new float[3]{.6,.6,.6};
    circle(5, 5, 10, 4, c);
    glPopMatrix();

    //marquiesina 1----------
    glPushMatrix();
    glTranslatef(0,90,50);    
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    c = new float[3]{.4,.4,.4};
    circle(20, 20, 1, 4, c);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,91,50);    
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    c = new float[3]{.4,.4,.4};
    circle(20, 12, 1, 4, c);
    glPopMatrix();

    //------------------------

    //torre segundo piso-----------
    glPushMatrix();
    glTranslatef(0,92,50);    
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    c = new float[3]{.9,.9,.9};
    circle(12, 12, 20, 4, c);
    glPopMatrix();

    //marquiesina 2----------
    glPushMatrix();
    glTranslatef(0,112,50);    
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    c = new float[3]{.4,.4,.4};
    circle(17, 17, 1, 4, c);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,113,50);    
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    c = new float[3]{.4,.4,.4};
    circle(17, 9, 1, 4, c);
    glPopMatrix();

    //punta-----------
    glPushMatrix();
    glTranslatef(0,114,50);    
    glRotatef(90,1,0,0);
    glRotatef(45,0,0,1);
    c = new float[3]{.6,.6,.6};
    circle(7, 0, 30, 8, c);
    glPopMatrix();




    glFlush();

    glutSwapBuffers();
}

// Funcion que controla las teclas que se presionan.
void keyInput(unsigned char key, int x, int y)
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

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SIZE, SIZE);
    glutInitWindowPosition(350, 10);
    glutCreateWindow("IGLESIA");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyInput);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
