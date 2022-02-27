#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>
#define SIZE 500
#define PI 3.141592654 

using namespace std;

// Funcion encargada de controlar el cambio de tamano de la ventana
void reshape(int w, int h)
{
    glViewport (0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

    //width = w;
    //height = h;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//grafica la curva para la ventana
void curva(int posx, int posy, int radio){
    glBegin(GL_LINES);
    for(int ang = 0; ang < 181; ang++){
        int x = radio * cos(ang*PI/180) + posx;
        int y = radio * sin(ang*PI/180) + posy;
        glVertex2f(x,y);
    }
    glEnd();
    glBegin(GL_LINES);
    for(int ang = 0; ang < 181; ang++){
        int x = radio-2 * cos(ang*PI/180) + posx;
        int y = radio-2 * sin(ang*PI/180) + posy;
        glVertex2f(x,y);
    }

    glEnd();
}
//diseño de ventana circular
void ventana(int posx, int posy){
	int radio = 17, radio2 = 34;
    curva(posx, posy, radio);
    curva(posx, posy, radio-3);
    curva(posx, posy, radio2);
    curva(posx, posy, radio2-3);

    glBegin(GL_LINE_STRIP);
    glVertex2f(posx-radio, posy);
    glVertex2f(posx-radio, posy-90);
    glVertex2f(posx+radio, posy-90);
    glVertex2f(posx+radio, posy);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(posx-radio+3, posy);
    glVertex2f(posx-radio+3, posy-30);
    glVertex2f(posx+radio-3, posy-30);
    glVertex2f(posx+radio-3, posy);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(posx-radio+3, posy-33);
    glVertex2f(posx-radio+3, posy-87);
    glVertex2f(posx+radio-3, posy-87);
    glVertex2f(posx+radio-3, posy-33);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(posx-radio-3, posy-90);
    glVertex2f(posx-radio-3, posy-100);
    glVertex2f(posx+radio+3, posy-100);
    glVertex2f(posx+radio+3, posy-90);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(posx-radio2-2, posy);
    glVertex2f(posx-radio2-2, posy-4);
    glVertex2f(posx-radio2+5, posy-4);
    glVertex2f(posx-radio2+5, posy);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(posx+radio2-5, posy);
    glVertex2f(posx+radio2-5, posy-4);
    glVertex2f(posx+radio2+2, posy-4);
    glVertex2f(posx+radio2+2, posy);
    glEnd();
}
//diseño de las tres ventanas mas altas de la casa
void ventana2(int posx, int posy){
	glBegin(GL_LINE_LOOP);
    glVertex2f(posx-22, posy);
    glVertex2f(posx-22, posy+10);
    glVertex2f(posx+22, posy+10);
    glVertex2f(posx+22, posy);
    glEnd();
	glBegin(GL_LINE_LOOP);
    glVertex2f(posx-18, posy);
    glVertex2f(posx-18, posy-60);
    glVertex2f(posx+18, posy-60);
    glVertex2f(posx+18, posy);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(posx-15, posy-5);
    glVertex2f(posx-15, posy-29);
    glVertex2f(posx+15, posy-29);
    glVertex2f(posx+15, posy-5);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(posx-15, posy-31);
    glVertex2f(posx-15, posy-57);
    glVertex2f(posx+15, posy-57);
    glVertex2f(posx+15, posy-31);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(posx-22, posy-70);
    glVertex2f(posx-22, posy-60);
    glVertex2f(posx+22, posy-60);
    glVertex2f(posx+22, posy-70);
    glEnd();
}

// Funcion que controla los eventos de dibujo de la aplicacion.
void display(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,0,0);

    //Puerta---------------------------------
    glBegin(GL_LINE_LOOP);
    glVertex2f(380, 20);
    glVertex2f(280, 20);
    glVertex2f(280, 70);
    glVertex2f(380, 70);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(380, 20);
    glVertex2f(370, 20);
    glVertex2f(370, 70);
    glVertex2f(380, 70);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(280, 20);
    glVertex2f(290, 20);
    glVertex2f(290, 70);
    glVertex2f(280, 70);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(376, 120);
    glVertex2f(374, 120);
    glVertex2f(374, 70);
    glVertex2f(376, 70);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(284, 120);
    glVertex2f(286, 120);
    glVertex2f(286, 70);
    glVertex2f(284, 70);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(290, 65);
    glVertex2f(290, 62);
    glVertex2f(370, 62);
    glVertex2f(370, 65);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(290, 50);
    glVertex2f(290, 47);
    glVertex2f(370, 47);
    glVertex2f(370, 50);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(290, 35);
    glVertex2f(290, 32);
    glVertex2f(370, 32);
    glVertex2f(370, 35);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(290, 70);
    glVertex2f(290, 210);
    glVertex2f(330, 217);
    glVertex2f(370, 210);
    glVertex2f(370, 70);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(295, 70);
    glVertex2f(295, 205);
    glVertex2f(330, 212);
    glVertex2f(365, 205);
    glVertex2f(365, 70);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(295, 73);
    glVertex2f(295, 202);
    glVertex2f(365, 202);
    glVertex2f(365, 73);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(298, 76);
    glVertex2f(298, 199);
    glVertex2f(362, 199);
    glVertex2f(362, 76);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(298, 175);
    glVertex2f(298, 199);
    glVertex2f(362, 199);
    glVertex2f(362, 175);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(301, 178);
    glVertex2f(301, 196);
    glVertex2f(359, 196);
    glVertex2f(359, 178);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(298, 76);
    glVertex2f(298, 175);
    glVertex2f(310, 175);
    glVertex2f(310, 76);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(350, 76);
    glVertex2f(350, 175);
    glVertex2f(362, 175);
    glVertex2f(362, 76);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(300, 79);
    glVertex2f(300, 175);
    glVertex2f(306, 175);
    glVertex2f(306, 79);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(354, 79);
    glVertex2f(354, 175);
    glVertex2f(360, 175);
    glVertex2f(360, 79);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(310, 79);
    glVertex2f(310, 110);
    glVertex2f(350, 110);
    glVertex2f(350, 79);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(313, 84);
    glVertex2f(313, 105);
    glVertex2f(347, 105);
    glVertex2f(347, 84);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(316, 87);
    glVertex2f(316, 102);
    glVertex2f(328, 102);
    glVertex2f(328, 87);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(332, 87);
    glVertex2f(332, 102);
    glVertex2f(344, 102);
    glVertex2f(344, 87);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(310, 115);
    glVertex2f(310, 110);
    glVertex2f(350, 110);
    glVertex2f(350, 115);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(313, 171);
    glVertex2f(313, 115);
    glVertex2f(347, 115);
    glVertex2f(347, 171);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(313, 171);
    glVertex2f(313, 155);
    glVertex2f(347, 155);
    glVertex2f(347, 171);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(316, 168);
    glVertex2f(316, 158);
    glVertex2f(321, 158);
    glVertex2f(321, 168);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(339, 168);
    glVertex2f(339, 158);
    glVertex2f(344, 158);
    glVertex2f(344, 168);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(324, 168);
    glVertex2f(324, 158);
    glVertex2f(336, 158);
    glVertex2f(336, 168);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(313, 145);
    glVertex2f(330, 155);
    glVertex2f(347, 145);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(280, 20);
    glVertex2f(170, 20);
    glVertex2f(170, 240);
    glVertex2f(395, 240);
    glVertex2f(395, 30);
    glVertex2f(380, 30);
    glEnd();
    int n = 0;
    for (int i = 0; i < 7; ++i){
        glBegin(GL_LINE_STRIP);
        glVertex2f(170, 240+n);
        glVertex2f(170, 240+(n+3));
        glVertex2f(395, 240+(n+3));
        glVertex2f(395, 240+n);
        glEnd();
        n+=3;
    }

    ventana(225,185);
    ventana(225,385);
    ventana(340,385);

    glBegin(GL_POLYGON);
    glVertex2f(256, 385);
    glVertex2f(256, 381);
    glVertex2f(309, 381);
    glVertex2f(309, 385);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(395, 20);
    glVertex2f(395, 400);
    glVertex2f(398, 400);
    glVertex2f(398, 20);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(398, 25);
    glVertex2f(405, 25);
    glVertex2f(465, 20);
    glVertex2f(465, 80);
    glVertex2f(405, 85);
    glVertex2f(405, 25);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(402, 93);
    glVertex2f(465, 88);
    glVertex2f(465, 80);
    glVertex2f(402, 85);
    glEnd();    
    glBegin(GL_LINE_LOOP);
    glVertex2f(465, 88);
    glVertex2f(465, 80);
    glVertex2f(555, 80);
    glVertex2f(555, 88);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(465, 80);
    glVertex2f(465, 20);
    glVertex2f(480, 20);
    glVertex2f(480, 45);
    glVertex2f(540, 45);
    glVertex2f(540, 20);
    glVertex2f(540, 22);
    glVertex2f(480, 22);
    glVertex2f(540, 22);
    glVertex2f(540, 20);
    glVertex2f(555, 20);
    glVertex2f(555, 80);
    glEnd();
    //ventana
    glBegin(GL_LINE_LOOP);
    glVertex2f(405, 93);
    glVertex2f(405, 240);
    glVertex2f(465, 245);
    glVertex2f(465, 88);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(415, 93);
    glVertex2f(415, 230);
    glVertex2f(455, 233);
    glVertex2f(455, 88);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(418, 93);
    glVertex2f(418, 227);
    glVertex2f(455, 230);
    glVertex2f(455, 88);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(418, 160);
    glVertex2f(418, 157);
    glVertex2f(455, 157);
    glVertex2f(455, 160);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(418, 93);
    glVertex2f(418, 103);
    glVertex2f(455, 98);
    glVertex2f(455, 88);
    glEnd();
    //--------------------
    //ventana
    glBegin(GL_LINE_LOOP);
    glVertex2f(465, 88);
    glVertex2f(465, 245);
    glVertex2f(555, 245);
    glVertex2f(555, 88);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(475, 88);
    glVertex2f(475, 235);
    glVertex2f(545, 235);
    glVertex2f(545, 88);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(478, 98);
    glVertex2f(478, 230);
    glVertex2f(542, 230);
    glVertex2f(542, 98);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(478, 160);
    glVertex2f(478, 157);
    glVertex2f(542, 157);
    glVertex2f(542, 160);
    glEnd();
    //-------------------
    //ventana
    glBegin(GL_LINE_LOOP);
    glVertex2f(555, 88);
    glVertex2f(555, 245);
    glVertex2f(615, 240);
    glVertex2f(615, 93);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(565, 88);
    glVertex2f(565, 233);
    glVertex2f(605, 230);
    glVertex2f(605, 93);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(565, 88);
    glVertex2f(565, 230);
    glVertex2f(602, 227);
    glVertex2f(602, 93);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(565, 160);
    glVertex2f(565, 157);
    glVertex2f(602, 157);
    glVertex2f(602, 160);
    glEnd();    
    glBegin(GL_LINE_LOOP);
    glVertex2f(565, 88);
    glVertex2f(565, 98);
    glVertex2f(602, 103);
    glVertex2f(602, 93);
    glEnd();
    //-------------------
    glBegin(GL_LINE_LOOP);
    glVertex2f(555, 80);
    glVertex2f(555, 88);
    glVertex2f(618, 93);
    glVertex2f(618, 85);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(555, 80);
    glVertex2f(555, 20);
    glVertex2f(615, 25);
    glVertex2f(615, 85);
    glEnd();
    n=0;
    for (int i = 0; i < 7; ++i){
    	glBegin(GL_LINE_LOOP);
	    glVertex2f(405, 240+n);
	    glVertex2f(405, 243+n);
	    glVertex2f(465, 243+n+5);
	    glVertex2f(465, 240+n+5);
	    glEnd();
	    n+=3;	
    }
    n=0;
    for (int i = 0; i < 7; ++i){
    	glBegin(GL_LINE_LOOP);
	    glVertex2f(465, 245+n);
	    glVertex2f(465, 248+n);
	    glVertex2f(555, 248+n);
	    glVertex2f(555, 245+n);
	    glEnd();
	    n+=3;	
    }
    n=0;
    for (int i = 0; i < 7; ++i){
    	glBegin(GL_LINE_LOOP);
	    glVertex2f(555, 248+n);
	    glVertex2f(555, 245+n);
	    glVertex2f(615, 245+n-5);
	    glVertex2f(615, 248+n-5);
	    glEnd();
	    n+=3;	
    }
    //ventana
    glBegin(GL_LINE_LOOP);
    glVertex2f(405, 93+168);
    glVertex2f(405, 240+168);
    glVertex2f(465, 245+168);
    glVertex2f(465, 98+168);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(415, 93+168);
    glVertex2f(415, 230+168);
    glVertex2f(455, 233+168);
    glVertex2f(455, 98+168);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(418, 93+168);
    glVertex2f(418, 227+168);
    glVertex2f(455, 230+168);
    glVertex2f(455, 98+168);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(418, 160+168);
    glVertex2f(418, 157+168);
    glVertex2f(455, 162+168);
    glVertex2f(455, 165+168);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(418, 93+168);
    glVertex2f(418, 103+168);
    glVertex2f(455, 108+168);
    glVertex2f(455, 98+168);
    glEnd();
    //--------------------
    //ventana
    glBegin(GL_LINE_LOOP);
    glVertex2f(465, 98+168);
    glVertex2f(465, 245+168);
    glVertex2f(555, 245+168);
    glVertex2f(555, 98+168);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(475, 98+168);
    glVertex2f(475, 235+168);
    glVertex2f(545, 235+168);
    glVertex2f(545, 98+168);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(478, 106+168);
    glVertex2f(478, 230+168);
    glVertex2f(542, 230+168);
    glVertex2f(542, 106+168);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(478, 165+168);
    glVertex2f(478, 162+168);
    glVertex2f(542, 162+168);
    glVertex2f(542, 165+168);
    glEnd();
    //-------------------
    //ventana
    glBegin(GL_LINE_LOOP);
    glVertex2f(555, 98+168);
    glVertex2f(555, 245+168);
    glVertex2f(615, 240+168);
    glVertex2f(615, 93+168);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(565, 98+168);
    glVertex2f(565, 233+168);
    glVertex2f(605, 230+168);
    glVertex2f(605, 93+168);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(565, 98+168);
    glVertex2f(565, 230+168);
    glVertex2f(602, 227+168);
    glVertex2f(602, 93+168);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(565, 163+168);
    glVertex2f(565, 160+168);
    glVertex2f(602, 157+168);
    glVertex2f(602, 160+168);
    glEnd();    
    glBegin(GL_LINE_LOOP);
    glVertex2f(565, 98+168);
    glVertex2f(565, 108+168);
    glVertex2f(602, 103+168);
    glVertex2f(602, 93+168);
    glEnd();
    //-------------------
    glBegin(GL_LINE_STRIP);
    glVertex2f(395, 407);
    glVertex2f(465, 413);
    glVertex2f(555, 413);
    glVertex2f(625, 407);
    glVertex2f(625, 400);
    glVertex2f(615, 400);
    glVertex2f(625, 400);
    glVertex2f(630, 413);
    glVertex2f(555, 420);
    glVertex2f(465, 420);
    glVertex2f(390, 413);
    glVertex2f(395, 407);
    glVertex2f(390, 413);
    glVertex2f(455, 440);
    glVertex2f(475, 445);
    glVertex2f(545, 445);
    glVertex2f(565, 440);
    glVertex2f(630, 413);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(465, 420);
    glVertex2f(475, 445);
    glVertex2f(545, 445);
    glVertex2f(555, 420);
    glEnd();
    n = 0;
    for (int i = 0; i < 8; ++i){
        glBegin(GL_LINE_STRIP);
        glVertex2f(615, 237+n);
        glVertex2f(615, 237+(n+3));
        glVertex2f(650, 237+(n+3));
        glVertex2f(650, 237+n);
        glEnd();
        n+=3;
    }
    glBegin(GL_LINE_STRIP);
    glVertex2f(170, 261);
    glVertex2f(170, 440);
    glVertex2f(290, 545);
    glVertex2f(285, 550);
    glVertex2f(410, 650);
    glVertex2f(535, 550);
    glVertex2f(530, 545);
    glVertex2f(650, 440);
    glVertex2f(650, 25);
    glVertex2f(615, 25);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(170, 440);
    glVertex2f(163, 433);
    glVertex2f(143, 453);
    glVertex2f(410, 680);
    glVertex2f(677, 453);
    glVertex2f(657, 433);
    glVertex2f(650, 440);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(170, 440);
    glVertex2f(650, 440);
    glVertex2f(175, 445);
    glVertex2f(645, 445);
    glVertex2f(185, 455);
    glVertex2f(635, 455);
    glVertex2f(190, 460);
    glVertex2f(630, 460);
    glEnd();

    ventana2(360, 530);
    ventana2(410, 530);
    ventana2(460, 530);

    glBegin(GL_LINE_STRIP);
    glVertex2f(650, 25);
    glVertex2f(695, 25);
    glVertex2f(695, 450);
    glVertex2f(675, 450);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(695, 25);
    glVertex2f(715, 25);
    glVertex2f(715, 450);
    glVertex2f(695, 450);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(715, 450);
    glVertex2f(715, 580);
    glVertex2f(530, 580);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(712, 580);
    glVertex2f(692, 580);
    glVertex2f(692, 585);
    glVertex2f(712, 585);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(715, 585);
    glVertex2f(689, 585);
    glVertex2f(689, 590);
    glVertex2f(715, 590);
    glEnd();

    glFlush(); 

    glutSwapBuffers();
}

// Funcion principal.
int main(int argc, char *argv[])
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Casa");
    //init(); 
    glutDisplayFunc(display);
    //glutKeyboardFunc(keyboardCallbackProc);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
