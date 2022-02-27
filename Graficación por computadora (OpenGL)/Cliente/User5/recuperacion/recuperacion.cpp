#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#define WIDTH 650
#define HEIGHT 650
#define PI 3.141592654 
#define Retardo 100


using namespace std;

double zoom = 0.4;//Valor del zoom de la camara
double AngleX = 20.0;//Grados de rotacion del eje X
double AngleY = -60.0;//Grados de rotacion del eje Y
double AngleZ = 0.0;

double angulo_rotacion1 = 0.0;
double angulo_rotacion2 = 0.0;
double angulo_rotacion3 = 0.0;
double angulo_rotacion4 = 0.0;
double angulo_rotacion5 = 0.0;


// figura tridimensional con parametros definidos
void cilindro(float radio, float ancho,  GLfloat LADOS, float colores[]) {
    GLfloat X = 0, Y = 0, Z = 0, angle;
    glTranslatef(X,Y,Z);
    GLfloat Puntos[2][500][3];
    int Contador = 0;
    //se crean las dos bases del prisma y para ello se usa GL_POLYGON
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
        glColor3f(i == 1 ? colores[0] : colores[0]/2, i == 1 ? colores[1] : colores[1]/2, i == 1 ? colores[2] : colores[2]/2);
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
// se llama a dibujar las figuras
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

    float *colores;

    //estructura base
    
    //-----------------bases verticales
    for (int i = 0; i < 2; ++i){
        
        colores = new float[3]{0.44 , 0.16 , 0.};
        //--base vertical
        glPushMatrix();
        glTranslatef(i == 0 ? -35 : 35,-25,0);    
        glRotatef(90, 1, 0, 0);
        glRotatef(45, 0, 0, 1);
        cilindro(3, 35, 4, colores);
        glPopMatrix();
        colores = new float[3]{0.44 , 0.16 , 0.};
        glPushMatrix();
        glTranslatef(i == 0 ? -35 : 35,12,4);  
        glRotatef(45, 0, 0, 1);
        cilindro(3, 8, 4, colores);
        glPopMatrix();
        colores = new float[3]{0.44 , 0.16 , 0.};
        glPushMatrix();
        glTranslatef(i == 0 ? -35 : 35,16,4);  
        glRotatef(45, 0, 0, 1);
        cilindro(3, 8, 4, colores);
        glPopMatrix();

        for (int x = 0; x < 2; ++x){
            //base inclinada delantera
            glPushMatrix();
            glTranslatef(i == 0 ? -35 : 35,10,x == 0 ? 3 : -3);  
            glRotatef(x == 0 ? -30 : 30, 1, 0, 0);
                float altura = 0;
                for (int j = 0; j < 80; ++j)
                {
                    colores = new float[3]{1 , 0.7 , 0.3};
                    glPushMatrix();
                    glTranslatef(2, altura,0);    
                    glRotatef(90, 1, 0, 0);
                    glRotatef(90, 0, 1, 0);
                    glRotatef(x == 0 ? 45 : 225, 0, 0, 1);        
                    cilindro(.5, 4, 4, colores);
                    glPopMatrix();
                    altura -= .5;
                }
            glPopMatrix();
        }

        float largo = i == 0 ? -28.5 : 28.5;
        for (int x = 0; x < 6; ++x){
            colores = new float[3]{1 , 0.7 , 0.3};
            glPushMatrix();
            glTranslatef(largo, 10,0);    
            glRotatef(90, 1, 0, 0);
            glRotatef(45, 0, 0, 1);        
            cilindro(6, 8, 4, colores);
            glPopMatrix();
            largo += i == 0 ? 6 : -6;
        }
        for (int x = 0; x < 2; ++x){
            colores = new float[3]{1 , 0.7 , 0.3};
            glPushMatrix();
            glTranslatef(i == 0 ? 0 : 35, 0, x == 0 ? 2 : -2);    
            glRotatef(90, 1, 0, 0);
            glRotatef(90, 0, 1, 0);
            cilindro(1.5, 35, 100, colores);
            glPopMatrix();
        }
    }
    colores = new float[3]{.5,.5,.5};
    //--Circulo
    glPushMatrix();
    glTranslatef(0,15,1.5);  
    cilindro(33, 3, 100, colores);
    glPopMatrix();
        
    colores = new float[3]{0.44 , 0.16 , 0.};
    //--Manivela
    glPushMatrix();
    glTranslatef(0,18,15);  
    glRotatef(angulo_rotacion5, 0, 0, 1); 
    cilindro(1, 60, 100, colores);
        colores = new float[3]{0.44 , 0.16 , 0.};
        glPushMatrix();
        glTranslatef(0,-2,-2); 
        glRotatef(90, 1, 0, 0); 
        cilindro(.8, 12, 100, colores);
        glPopMatrix();
        colores = new float[3]{0.44 , 0.16 , 0.};
        glPushMatrix();
        glTranslatef(0,8,8);  
        cilindro(.8, 12, 100, colores);
        glPopMatrix();
        colores = new float[3]{0.44 , 0.16 , 0.};
        glPushMatrix();
        glTranslatef(0,0,-13);  
        cilindro(15, 5, 4, colores);
        glPopMatrix();
    glPopMatrix();

    //------------------circulo inferior horizontal giratorio----------------    

    glPushMatrix();
    glTranslatef(0,0,0);
    glRotatef(angulo_rotacion1, 0, 1, 0);
        colores = new float[3]{1 , 0.7 , 0.3};
        glPushMatrix();
        glTranslatef(0,-25,0);
        glRotatef(90, 1, 0, 0);  
        cilindro(20, 5, 100, colores);
        glPopMatrix();
        colores = new float[3]{.5,.5,.5};
        glPushMatrix();
        glTranslatef(0,-20,0);
        glRotatef(90, 1, 0, 0);  
        cilindro(17, 1, 100, colores);
        glPopMatrix();
        for(int ang = 0; ang < 361; ang++){
            float x = 25 * cos(ang*PI/180);
            float z = 25 * sin(ang*PI/180);

            colores = new float[3]{.9 , 0.5 , 0.0};
            glPushMatrix();
            glTranslatef(x,-22.5,z);
            glRotatef(90-ang, 0, 1, 0);
            //glRotatef(ang, 0, 1, 0);
            if(ang % 10 == 0)
                cilindro(1, 5, 100, colores);
            glPopMatrix();
        }
    glPopMatrix();

    //---------------------cilindro central vertical giratorio------------------------
    colores = new float[3]{1 , 0.7 , 0.3};
    glPushMatrix();
    glTranslatef(0,17,-15);
    glRotatef(angulo_rotacion2, 0, 0, 1);
    cilindro(12, 4, 100, colores);
    for(int ang = 0; ang < 361; ang++){
        float x = 10 * cos(ang*PI/180);
        float y = 10 * sin(ang*PI/180);

        colores = new float[3]{.9 , 0.5 , 0.0};
        glPushMatrix();
        glTranslatef(x,y,-4);
        if(ang % 20 == 0)
            cilindro(1, 5, 100, colores);
        glPopMatrix();
    }
    glPopMatrix();

    //---------------------------------------------
    colores = new float[3]{1 , 0.7 , 0.3};
    glPushMatrix();
    glTranslatef(0,1,-31);
    glRotatef(90, 1, 0, 0);
    glRotatef(angulo_rotacion3, 0, 0, 1);
    cilindro(8, 2, 100, colores);
        for(int ang = 0; ang < 361; ang++){
            float x = 7 * cos(ang*PI/180);
            float y = 7 * sin(ang*PI/180);

            colores = new float[3]{.9 , 0.5 , 0.0};
            glPushMatrix();
            glTranslatef(x,y,-2);
            if(ang % 40 == 0)
                cilindro(1, 8.5, 100, colores);
            glPopMatrix();
        }
        colores = new float[3]{1 , 0.7 , 0.3};
        glPushMatrix();
        glTranslatef(0,0,-8);
        //glRotatef(90, 1, 0, 0);
        cilindro(8, 2, 100, colores);
        glPopMatrix();
    glPopMatrix();
    //---------------------------------------------
    colores = new float[3]{1 , 0.7 , 0.3};
    glPushMatrix();
    glTranslatef(0,-25,-31);
    glRotatef(90, 1, 0, 0);
    glRotatef(angulo_rotacion4, 0, 0, 1);
    cilindro(8, 2, 100, colores);
        for(int ang = 0; ang < 361; ang++){
            float x = 7 * cos(ang*PI/180);
            float y = 7 * sin(ang*PI/180);

            colores = new float[3]{.9 , 0.5 , 0.0};
            glPushMatrix();
            glTranslatef(x,y,-2);
            if(ang % 40 == 0)
                cilindro(1, 16.5, 100, colores);
            glPopMatrix();
        }
        colores = new float[3]{1 , 0.7 , 0.3};
        glPushMatrix();
        glTranslatef(0,0,-16);
        cilindro(8, 2, 100, colores);
        glPopMatrix();
    glPopMatrix();
    //---------------------cilindro grande vertical giratorio------------------------
    colores = new float[3]{1 , 0.7 , 0.3};
    glPushMatrix();
    glTranslatef(0,-5,-43);
    glRotatef(angulo_rotacion2, 0, 0, 1);
    cilindro(12, 4, 100, colores);
    for(int ang = 0; ang < 361; ang++){
        float x = 10 * cos(ang*PI/180);
        float y = 10 * sin(ang*PI/180);

        colores = new float[3]{.9 , 0.5 , 0.0};
        glPushMatrix();
        glTranslatef(x,y,5);
        if(ang % 20 == 0)
            cilindro(1, 5, 100, colores);
        glPopMatrix();
    }
    glPopMatrix();

    colores = new float[3]{0.44 , 0.16 , 0.};
    glPushMatrix();
    glTranslatef(0,-5,-47);
    glRotatef(angulo_rotacion2, 0, 0, 1);
    cilindro(2, 4, 100, colores);
    glPopMatrix();

    //-----------------------base trasera------------------
    glPushMatrix();
    glTranslatef(0,-25,-52);    
    glRotatef(90, 0, 1, 0);
        colores = new float[3]{0.44 , 0.16 , 0.};
        //--base vertical
        glPushMatrix();
        glTranslatef(0,0,0);    
        glRotatef(90, 1, 0, 0);
        glRotatef(45, 0, 0, 1);
        cilindro(3, 39, 4, colores);
        glPopMatrix();
        colores = new float[3]{0.44 , 0.16 , 0.};
        glPushMatrix();
        glTranslatef(0,41,4);  
        glRotatef(45, 0, 0, 1);
        cilindro(3, 8, 4, colores);
        glPopMatrix();
        colores = new float[3]{0.44 , 0.16 , 0.};
        glPushMatrix();
        glTranslatef(0,45,4);  
        glRotatef(45, 0, 0, 1);
        cilindro(3, 8, 4, colores);
        glPopMatrix();

        float largo = -6;
        for (int x = 0; x < 3; ++x){
            colores = new float[3]{1 , 0.7 , 0.3};
            glPushMatrix();
            glTranslatef(largo, 39,0);    
            glRotatef(90, 1, 0, 0);
            glRotatef(45, 0, 0, 1);        
            cilindro(6, 8, 4, colores);
            glPopMatrix();
            largo -= 6;
        }
    glPopMatrix();
    
    glFlush(); 

    glutSwapBuffers();
}

void timer(int value){
    angulo_rotacion1 += 1;
    angulo_rotacion2 += 1;
    angulo_rotacion3 -= 2;
    angulo_rotacion4 += 2;
    angulo_rotacion5 += 1;
	glutPostRedisplay();
	glutTimerFunc(Retardo,timer, 1);
}
// Funcion que controla las teclas que se presionan.
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'x':
        	AngleX+=5; 
        	break;
        case 'y':
        	AngleY-=5; 
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
// Funcion que controla el tamaño de la ventana
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
// Funcion que inicializa el programa iniciando el modo de profundidad de OpenGL
void init(void)
{
    glEnable(GL_DEPTH_TEST); 
}
int main(int argc, char *argv[])
{
    cout<<"Teclas:\n 'x' = eje X\n 'y' = eje Y\n 'z' = eje Z\n '+,-' = zoom"<<endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 10);
    glutCreateWindow("Recuperacion");
    init(); 
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutTimerFunc(Retardo,timer, 1);
    glutMainLoop();
    return 0;
}