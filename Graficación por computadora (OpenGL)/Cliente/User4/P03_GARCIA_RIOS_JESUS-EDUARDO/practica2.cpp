#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#define PI 3.141592654 

using namespace std;


int Retardo = 10;

float width, height;
//coordenadas del centro del plano
float centroX = 250;
float centroY = 250;
//coordenadas del punto rojo
float puntoX = centroX + 125;
float puntoY = centroY;
//coordenadas del origen de rotacion de la recta
float rectaX = puntoX;
float rectaY = puntoY;
//angulo de giro de la recta
float angulo = 90;
//esquinas del rombo en que rota la recta
bool esquinas[4] = {true, false, false, false};
//coordenadas almacenadas de la trayectoria del punto rojo
vector <float> punto[2];

void writeBitmapString(void *font, string str)
{
	int i;
   	for(i = 0; i < str.size(); i++)
   		glutBitmapCharacter(font, str[i]);   
}

void reshape(int w, int h)
{
    glViewport (0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

    width = w;
    height = h;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

bool pausar = false;
bool menu = false;

int color_boton[4] = {0,0,0,0};

void display(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,0,0);
    glBegin(GL_LINES);
    //eje X
    glVertex2f(0, centroY);
    glVertex2f(500, centroY);
    //eje Y
    glVertex2f(centroX, 0);
    glVertex2f(centroX, 500);
    glEnd();

    //rombo
    glBegin(GL_LINE_LOOP);
    glVertex2f(centroX, centroY + 125);
    glVertex2f(centroX - 125, centroY);
    glVertex2f(centroX, centroY - 125);
    glVertex2f(centroX + 125, centroY);
    glEnd();

    //punto rojo
    glColor3f(1,0,0);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2f(puntoX, puntoY);
    glEnd();

    //recorrido punto rojo
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i < punto[0].size(); i++){
        glVertex2f(punto[0][i], punto[1][i]);
    }
    glEnd();

    //recta
    glBegin(GL_LINES);

    //primer extremo de la recta con radio de 500 con respecto al centro
    float x1 = 500 * cos(angulo * PI / 180) + rectaX;
    float y1 = 500 * sin(angulo * PI / 180) + rectaY;
    //segundo extremo de la recta con radio de 500 con respecto al centro
    float x2 = 500 * cos((angulo+180) * PI / 180) + rectaX;
    float y2 = 500 * sin((angulo+180) * PI / 180) + rectaY;

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();

    //letras
    glColor3f(.0, .0, .0);
    glRasterPos2f(centroX-15, 480);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "y");
    glColor3f(1, .0, .0);
    glRasterPos2f(centroX+5, 480);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "b");
    glColor3f(.0, .0, .0);
    glRasterPos2f(480, centroY-15);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "x");
    glColor3f(1, .0, .0);
    glRasterPos2f(480, centroY+5);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "a");
    //ecuacion
    glColor3f(1, .0, .0);
    glRasterPos2f(centroX+150, 430);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "a");
    glColor3f(0, .0, .0);
    glRasterPos2f(centroX+158, 430);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "x + ");
    glColor3f(1, .0, .0);
    glRasterPos2f(centroX+190, 430);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "b");
    glColor3f(0, .0, .0);
    glRasterPos2f(centroX+199, 430);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "y = 1");

    if(menu){

    	// -- boton pausar / reanudar
        glColor3f(color_boton[0],0,1);
        glBegin(GL_POLYGON);
        glVertex2f(200, 400);
        glVertex2f(300, 400);
        glVertex2f(300, 360);
        glVertex2f(200, 360);
        glEnd();
        glColor3f(1, 1, 1);
        if(!pausar){
            glRasterPos2f(220, 375);
            writeBitmapString(GLUT_BITMAP_HELVETICA_12, "PAUSAR");    
        }
        else{
            glRasterPos2f(220, 375);
            writeBitmapString(GLUT_BITMAP_HELVETICA_12, "REANUDAR");    
        }
        
        
        //velocidad giro +
        glColor3f(color_boton[1],0,1);
        glBegin(GL_POLYGON);
        glVertex2f(200, 350);
        glVertex2f(300, 350);
        glVertex2f(300, 310);
        glVertex2f(200, 310);
        glEnd();
        glColor3f(1, 1, 1);
        glRasterPos2f(215, 325);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "+ VEL. GIRO");

        glColor3f(color_boton[2],0,1);
        glBegin(GL_POLYGON);
        glVertex2f(200, 300);
        glVertex2f(300, 300);
        glVertex2f(300, 260);
        glVertex2f(200, 260);
        glEnd();
        glColor3f(1, 1, 1);
        glRasterPos2f(210, 275);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "- VEL. GIRO");

        glColor3f(color_boton[3],0,1);
        glBegin(GL_POLYGON);
        glVertex2f(200, 250);
        glVertex2f(300, 250);
        glVertex2f(300, 210);
        glVertex2f(200, 210);
        glEnd();
        glColor3f(1, 1, 1);
        glRasterPos2f(210, 225);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "CERRAR");
    }    

    glFlush();    
}
void TimerFunction(int value){

    if(!pausar){
        //esquina arriba
        if(esquinas[0]){
            if(puntoY < centroY + 125)
                puntoY++;
            else{
                esquinas[0] = false;
                esquinas[1] = true;
            }

            rectaX = centroX + 125;
            rectaY = centroY;

            if(puntoY == centroY){
                punto[0].clear();
                punto[1].clear();
                angulo = 90.0;
            }
        }
        //esquina izquierda
        if(esquinas[1]){
            if(puntoX > centroX - 125)
                puntoX--;
            else{
                esquinas[1] = false;
                esquinas[2] = true;
            }
            rectaX = centroX;
            rectaY = centroY + 125;
        }
        //esquina abajo
        if(esquinas[2]){
            if(puntoY > centroY - 125)
                puntoY--;
            else{
                esquinas[2] = false;
                esquinas[3] = true;
            }
            rectaX = centroX - 125;
            rectaY = centroY;
        }
        //esquina derecha
        if(esquinas[3]){
            if(puntoX < centroX + 125)
                puntoX++;
            else{
                esquinas[3] = false;
                esquinas[0] = true;            
            }
            rectaX = centroX;
            rectaY = centroY - 125;
        }

        //se ingrementa el angulo de rotacion del
        angulo+=(45.0/125);

        punto[0].push_back(puntoX);
        punto[1].push_back(puntoY);
    }

    

    glutPostRedisplay();
    glutTimerFunc(Retardo,TimerFunction, 1);
    
}

void mouseControl(int button, int state, int x, int y){

    y = height - y;

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)        
        menu = !menu;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(x > 200 && x < 300 && y > 360 && y < 400){
            color_boton[0] = 1;
            pausar = !pausar;
        }
        if(x > 200 && x < 300 && y > 310 && y < 350){
            color_boton[1] = 1;
            if(Retardo > 0) 
                Retardo--;
        }
        if(x > 200 && x < 300 && y > 260 && y < 300){
            color_boton[2] = 1;
            if(Retardo < 20)
                Retardo++;
        }
        if(x > 200 && x < 300 && y > 210 && y < 250){
            color_boton[3] = 1;
            exit(0);
        }
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        color_boton[0] = 0;
        color_boton[1] = 0;
        color_boton[2] = 0;
        color_boton[3] = 0;
    }

    glutPostRedisplay();
} 

int main(int argc, char *argv[])                                                                       
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseControl);
    glutTimerFunc(Retardo,TimerFunction, 1);
    glutMainLoop();
    return 0;
}

/*

Desarrollo experimental:

Primero se grafico el plano con una linea vertical y horizontal sobre el centro de la ventana con GL_LINES representando los ejes X y Y.
Despues se dibujo el rombo, para esto se definieron en variables las coordenadas del centro del plano, y con ayuda de éstas se graficaron los vertices del rombo y se unieron con la funcion de GL_LINE_LOOP. Para graficar el punto rojo se uso GL_POINTS y se le dio color rojo.
Para definir el movimiento del punto, se uso una funcion de TimerFunc para modificar las coordenadas del punto. Dentro de esta funcion se verifica que dependiendo de la esquina hacia la que se dirija el punto se movera hacia arriba, abajo, izquierda o derecha.
Finalmente se grafica la recta que gira en base al centro, esta va siguiendo la rotacion del angulo definido y va cambiando la posicion del centro de la recta segun la esquina del rombo a la que se dirige el punto.

Para la creación del menu se crearon cuatro rectangulos con la ayuda de GL_POLYGON, uno para Reanudar/Pausar, en el cual se una la variable 'pausar' que se iguala a True o False cuando se hace clic en el boton, cuando pausar = True, el movimiento se detiene.
Para los botones velocidad solo se aumenta o decrementa la variable de 'retardo' de la funcion de Timer.
Y por ultimo se programo el boton de Cerrar usando la intruccion 'exit(0)' una vez dando en el boton.
*/
