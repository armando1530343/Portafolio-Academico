#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>
#define SIZE 500
#define PI 3.141592654 

using namespace std;

float width, height;

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

void writeBitmapString(void *font, string str)
{
	int i;
   	for(i = 0; i < str.size(); i++)
   		glutBitmapCharacter(font, str[i]);   
}

//-----VARIABLES

//vectores en movimiento
float centro_x = 300, centro_y = 350,
      u_x = 300, u_y = 400,
      v_x = 350, v_y = 350,
      w_x = 0, w_y = 0,
      ladoV_x = 0, ladoV_y = 0,
      ladoU_x = 0, ladoU_y = 0,

      ang_u = 0, ang_v = 0, ang_w = 90,
      long_u = 0, long_v = 0, long_w = 20;

//vectores estaticos
float centro_x2 = 600, centro_y2 = 50,
      u_x2 = 0, u_y2 = 0,
      v_x2 = 0, v_y2 = 0,
      w_x2 = 0, w_y2 = 0;

//banderas
bool select_u = false,
     select_v = false,
     select_w = false,
     select_centro1 = false,
     select_centro2 = false,
     tres_vectores = false;

void display(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    //vector u
    glColor3f(1,0,0);
    glVertex2f(centro_x, centro_y);
    glVertex2f(u_x, u_y);
    //vector v
    glColor3f(0,0,1);
    glVertex2f(centro_x, centro_y);
    glVertex2f(v_x, v_y);
    glEnd();

    glPointSize(10);
    glBegin(GL_POINTS);
    //centro 1
    glColor3f(0,0,0);
    glVertex2f(centro_x, centro_y);
    //centro 2
    glColor3f(0,0,0);
    glVertex2f(centro_x2, centro_y2);
    //punto u
    glColor3f(1,0,0);
    glVertex2f(u_x, u_y);
    //punto v
    glColor3f(0,0,1);
    glVertex2f(v_x, v_y);
    glEnd();

    ang_u = atan2(u_y - centro_y, u_x - centro_x) * 180/PI;
    ang_v = atan2(v_y - centro_y, v_x - centro_x) * 180/PI;
    //ang_w = atan2(w_y - centro_y, w_x - centro_x) * 180/PI;
    //cout << "angulo u: " << ang_u << " angulo v: " << ang_v << endl;   

    long_u = sqrt(pow(u_x - centro_x, 2) + pow(u_y - centro_y, 2));
    long_v = sqrt(pow(v_x - centro_x, 2) + pow(v_y - centro_y, 2));

    ladoU_x = long_v * cos(ang_v * PI/180) + u_x;
    ladoU_y = long_v * sin(ang_v * PI/180) + u_y;
    ladoV_x = long_u * cos(ang_u * PI/180) + v_x;
    ladoV_y = long_u * sin(ang_u * PI/180) + v_y;

    u_x2 = long_u * cos(ang_u * PI/180) + centro_x2;
    u_y2 = long_u * sin(ang_u * PI/180) + centro_y2;

    v_x2 = long_v * cos(ang_v * PI/180) + centro_x2;
    v_y2 = long_v * sin(ang_v * PI/180) + centro_y2;

    cout << "long_v: " << ladoU_y << endl;

    glBegin(GL_LINES);
    //lado u
    glColor3f(.7,.7,1);
    glVertex2f(u_x, u_y);
    glVertex2f(ladoU_x, ladoU_y);
    //lado v
    glVertex2f(v_x, v_y);
    glVertex2f(ladoV_x, ladoV_y);
    //suma vectores
    glColor3f(0,0,0);
    glVertex2f(centro_x, centro_y);
    glVertex2f(ladoV_x, ladoV_y);

    //lineas estaticas
    //vector u
    glColor3f(1,0,0);
    glVertex2f(centro_x2, centro_y2);
    glVertex2f(u_x2, u_y2);
    //vector v
    glColor3f(0,0,1);
    glVertex2f(u_x2, u_y2);
    glVertex2f(ladoU_x - u_x + u_x2, ladoU_y - u_y + u_y2);
    //diagonal suma
    glColor3f(0,0,0);
    glVertex2f(centro_x2, centro_y2);
    glVertex2f(ladoU_x - u_x + u_x2, ladoU_y - u_y + u_y2);

    glEnd();

    glFlush();

    
}

void mouseControl(int button, int state, int x, int y){
    
    y = height - y;

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(x >= centro_x-5 && x <= centro_x+5 && y >= centro_y-5 && y <= centro_y+5)
            select_centro1 = true;
        else select_centro1 = false;

        if(x >= centro_x2-5 && x <= centro_x2+5 && y >= centro_y2-5 && y <= centro_y2+5)
            select_centro2 = true;
        else select_centro2 = false;

        if(x >= u_x-5 && x <= u_x+5 && y >= u_y-5 && y <= u_y+5)
            select_u = true;
        else select_u = false;

        if(x >= v_x-5 && x <= v_x+5 && y >= v_y-5 && y <= v_y+5)
            select_v = true;
        else select_v = false;

        if(x >= w_x-5 && x <= w_x+5 && y >= w_y-5 && y <= w_y+5)
            select_w = true;
        else select_w = false;        
        
    }

    glutPostRedisplay();
}

void mouseMotion(int x, int y){

    y = height - y;

    if(select_centro1){centro_x = x; centro_y = y;}
    if(select_centro2){centro_x2 = x; centro_y2 = y;}
    if(select_u){u_x = x; u_y = y;}
    if(select_v){v_x = x; v_y = y;}
    if(select_w){w_x = x; w_y = y;}

    glutPostRedisplay();
}


void keyInput(unsigned char key, int x, int y)
{
   switch (key)
   {
      case 's':
         tres_vectores = !tres_vectores;
         break;
      default:
         break;
   }
}

// Funcion principal.
int main(int argc, char *argv[])                                                                       
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("practica1. Suma de Vectores");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyInput);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseControl);
	glutMotionFunc(mouseMotion);
    glutMainLoop();
    return 0;
}
