#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#include <sstream>
#define WIDTH 800
#define HEIGHT 600
#define PI 3.141592654


using namespace std;

double zoom = 0.3;    //Valor del zoom de la camara
double AngleX = 0.0;      //Grados de rotacion del eje X
double AngleY = 0.0;    //Grados de rotacion del eje Y
double AngleZ = 0.0;
int Retardo = 10;
float giraX=0, giraY=0, giraZ=0;

// figura en 3d
void figura3D(float radio, float ancho,  int lados, float *colores) {
    GLfloat X = 0, Y = 0, Z = 0, angle;
    glTranslatef(X,Y,Z);
    GLfloat Puntos[2][500][3];
    int Contador = 0;
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
        glColor3f(colores[0] - .2, colores[1] - .2, colores[2] - .2);
        Contador = 0;
        for (angle = 0.0f; angle <= (2.0f * PI); angle += (2.0f * PI) / lados) {
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

        color[0] -= colores[0]/lados;
        color[1] -= colores[1]/lados;
        color[2] -= colores[2]/lados;
    }
}

void writeBitmapString(void *font, string str)
{
    int i;
    for(i = 0; i < str.size(); i++)
        glutBitmapCharacter(font, str[i]);
}

void fondo_espacio(){

	int n = 100;

	glPointSize(1);
	glBegin(GL_POINTS);
	glColor3f(1,1,1);
	for(int i = -n; i < n; i++ ){
		for(int j = -n; j < n; j++){
			for(int k = -n; k < n; k++){
				if(i % 20 == 0 && j % 20 == 0 && k % 20 == 0){
					glVertex3f(i, j, k);
				}
			}
		}

	}
	glEnd();
}

bool move_x = false;
bool move_y = false;

void nave(float x, float y, float z, int ang){

    //cout << -ang << endl;

    ang = -ang;

    ang = ang == 90 ? 0 : ang > 90 || ang < 90 ? ang - 90 : ang;

    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(ang,0,1,0);
        //NAVE
        glPushMatrix();
        glTranslatef(.2,2,-2.5);
        glRotatef(90,0,1,0);
        glRotatef(45,0,0,1);
        figura3D(3.5, .5, 4, new float[3]{.7,.0,.0});
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(0,4,-2.5);
        glRotatef(90,1,0,0);
        glRotatef(45,0,0,1);
        figura3D(2, .5, 4, new float[3]{.7,.0,.0});
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,0);
        glRotatef(45,0,0,1);
        figura3D(2, 1, 30, new float[3]{.7,.0,.0});
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0.5,1);
        glRotatef(45,0,0,1);
        figura3D(1, 1, 4, new float[3]{.7,.7,.7});
        glPopMatrix();

        for(int i = 0; i < 2; i++){
            glPushMatrix();
            glTranslatef(i == 0 ? -3 : 3,0,0);
            glRotatef(45,0,0,1);
            figura3D(1, 1, 8, new float[3]{.5,.0,.0});
            glPopMatrix();
        }

    glPopMatrix();
}

void bala_nave(float x, float y, float z, int ang, float *color){
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(ang,0,1,0);
    figura3D(.4, 3, 20, color);
    glPopMatrix();
}


struct Bala{
    //coordenadas de bala
    float x, y, z;
    bool visible=false;
};

struct Nave
{   
    float x, y, z;          //coordenadas de posicion de la nave
    int rotacion;           //angulo de giro de la nave (siempre mirando a la camara del jugador)
    bool derrotado=false;         //verifica si la nave es derrotada
    Bala municion;    //municion de la nave que guarda las posiciones de las balas
    int contras=0;
    bool activo;
    bool visible=true;
};

Nave *naves;
Bala municion_nave[2]; //municiones de la nave del jugador
int PUNTOS = 20;

float recorrido_bala = -5.0;
float recorrido_bala_enemigo = 100.0;

int total_naves = 3;

//misil izquierda
float misilA_x = -1;
float misilA_y = 0;
//misil derecha
float misilB_x = 1;
float misilB_y = 0;

bool disparo = false;

float mira_y = 90;

bool end_game = false;
bool juego_ganado = false;

int enemigos_vencidos = 0;
int enemigos_activos = total_naves;

float rojo = 0;
float verde = 0;

// Funcion que controla los eventos de dibujo de la aplicacion.
void display(void)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(rojo,verde,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //gluLookAt(0,0,-10,giraX, giraY, giraZ, 0,1,0);

    float posZ = 0;

    glTranslatef(0, 0, posZ);//Posicion de iniciado
    glRotatef(giraY, 0.0, 1.0, 0.0);//Controla la vista de la camara en Y
    glScalef(zoom, zoom, zoom);//Controla el Zoom

    fondo_espacio();

    float n = .1;


    float x_mira = -4 * cos((180-mira_y) * 3.1415/180);
    float z_mira = -4 * sin((180-mira_y) * 3.1415/180);

    

    //cout << mira_y << endl;
    //APUNTADOR DE DISPARO
    glPushMatrix();
    glTranslatef(x_mira, 0, z_mira);

    glRotatef(-giraY,0,1,0);

    stringstream s;
    s << PUNTOS;
    string _puntos = s.str();

    stringstream ss;
    ss << enemigos_activos;
    string _activos = ss.str();

    
    glColor3f(1,0,0);
    glRasterPos3f(2, 2, 0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, _puntos);
    glRasterPos3f(1.5, 2, 0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Puntos: ");
    glRasterPos3f(2, 1.5, 0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, _activos);
    glRasterPos3f(1.5, 1.5, 0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Naves: ");
    glRasterPos3f(-2., -1.8, 0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "a = gira izquierda ");
    glRasterPos3f(-2., -2., 0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "d = gira derecha ");
    glRasterPos3f(-2., -2.2, 0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "m = dispara ");

    glColor3f(1,0,0);

    if(end_game && juego_ganado){
        glRasterPos3f(-.5, 1, 0);
        writeBitmapString(GLUT_BITMAP_HELVETICA_18, "SUPERADO!!!");
    }
    if(end_game && !juego_ganado){
        glRasterPos3f(-.4, 1, 0);
        writeBitmapString(GLUT_BITMAP_HELVETICA_18, "HAZ MUERTO");
    }

    

    glRotatef(45,0,0,1);

    glBegin(GL_LINE_LOOP);
    glColor3f(0,1,0);
    glVertex3f(-n, n, 0);
    glVertex3f(n,n,0);
    glVertex3f(n,-n,0);
    glVertex3f(-n,-n,0);
    glEnd();
    
    n*=20;
    glBegin(GL_LINES);
    glColor3f(0,.3,0);
    glVertex3f(-n, n, 0);
    glVertex3f(n,-n,0);
    glVertex3f(n,n,0);
    glVertex3f(-n,-n,0);    
    glEnd();
    

    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(1,0,0);
    glVertex3f(0,0,0.1);
    glEnd();

    


    glPopMatrix();

    
    

    //balas izquierda    
    bala_nave(municion_nave[0].x, municion_nave[0].y, municion_nave[0].z, -giraY, new float[3]{1,1,1});
    //balas derecha
    bala_nave(municion_nave[1].x, municion_nave[1].y, municion_nave[1].z, -giraY, new float[3]{1,1,1});
    


    for(int i = 0; i < total_naves*2; i++){
        if(naves[i].visible && !naves[i].derrotado){
            naves[i].rotacion = atan2(naves[i].z - posZ, naves[i].x) * 180/3.1415;
            nave(naves[i].x, naves[i].y, naves[i].z, naves[i].rotacion);        
            bala_nave(naves[i].municion.x, naves[i].municion.y, naves[i].municion.z, -naves[i].rotacion-90, new float[3]{1,1,0});
        }
        

    }

    

    glFlush();

    glutSwapBuffers();
}

void timer(int value){

    if (!end_game){
        int ataques = 0;

        for(int i = 0; i < total_naves*2; i++){

            if(naves[i].activo){
                naves[i].municion.x = recorrido_bala_enemigo * cos(naves[i].rotacion * 3.1415 / 180 );
                naves[i].municion.z = recorrido_bala_enemigo * sin(naves[i].rotacion * 3.1415 / 180 );  

                ataques++;  
            }
        }

        //cout << naves[0].contras << "," << naves[1].contras << "," << naves[2].contras << endl;
        
        recorrido_bala_enemigo -= 5;
        if(recorrido_bala_enemigo < 0){
            PUNTOS -= ataques;

            if(PUNTOS <= 0){
                PUNTOS = 0;
                end_game = true;
                rojo = .4;
                //glutPostRedisplay();
                //return;
            }

            recorrido_bala_enemigo = 100.0;
        }

        
        municion_nave[0].x = recorrido_bala * cos(mira_y * 3.1415 / 180 ) - 2;
        municion_nave[0].z = -recorrido_bala * sin(mira_y * 3.1415 / 180 );

        municion_nave[1].x = recorrido_bala * cos(mira_y * 3.1415 / 180 ) + 2;
        municion_nave[1].z = -recorrido_bala * sin(mira_y * 3.1415 / 180 );

        if(disparo == true){
            //cout << "z: " << municion_nave[0].z << endl;
            recorrido_bala += 10;
            if(recorrido_bala > 100){
                recorrido_bala = -5;


                for(int i = 0; i < total_naves*2; i++){

                    if(naves[i].activo){
                        naves[i].municion.x = naves[i].x;
                        naves[i].municion.y = naves[i].y-2;
                        naves[i].municion.z = naves[i].z;

                        if(mira_y >= -naves[i].rotacion - 5 && mira_y <= -naves[i].rotacion + 5){
                            
                            naves[i].contras++;
                            PUNTOS += 2;
                            
                            if(naves[i].contras >= 3){
                                naves[i].derrotado = true;
                                naves[i].activo = false;
                                enemigos_vencidos++;
                            }
                        }
                    }
                }

                disparo = false;

            }
                
        }

        for(int i = 0; i < total_naves; i++){
            if(naves[i].derrotado && naves[i].visible){
                if(naves[i+total_naves].y > 0){
                    naves[i+total_naves].y -= 1;
                    naves[i+total_naves].visible = true;
                }
                else{
                    naves[i+total_naves].activo = true;
                    naves[i].visible = false;
                }

                
            }
        }

        enemigos_activos=0;
        for(int i = 0; i < total_naves*2; i++){
            if(naves[i].activo)
                enemigos_activos++;
        }

        //cout << enemigos_vencidos << endl;

        if(enemigos_vencidos >= total_naves*2){
            juego_ganado = true;
            end_game = true;
            verde = .3;
        }

    }

    
    glutPostRedisplay();
    glutTimerFunc(Retardo,timer, 1);
}

// Funcion que controla las teclas que se presionan.
void keyInput(unsigned char key, int x, int y)
{
    if(!end_game){
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
            case 'd':
                giraY+= giraY < 90 ? 2 : 0;
                mira_y-= mira_y > 0 ? 2 : 0;
                
                move_y = true;
                break;
            case 'a':
                giraY-= giraY > - 90 ? 2 : 0;
                mira_y+= mira_y < 180 ? 2 : 0;
                
                move_y = true;
                break;

            case 'm':
                disparo = true;
                break;

        }
    }
    
    //cout << giraY << endl;
    glutPostRedisplay();
}

//ventana
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
int main(int argc, char *argv[])
{
    naves = new Nave[total_naves*2];

    naves[0].x = 0; naves[0].y = 0; naves[0].z = -50; naves[0].activo = true;
    naves[1].x = -30; naves[1].y = 0; naves[1].z = -50; naves[1].activo = true;
    naves[2].x = 30; naves[2].y = 0; naves[2].z = -50; naves[2].activo = true;

    for(int i = 0; i < total_naves; i++){
        naves[i].municion.x = naves[i].x;
        naves[i].municion.y = naves[i].y-2;
        naves[i].municion.z = naves[i].z;

        naves[i+total_naves] = naves[i];
        naves[i+total_naves].y = 50;
        naves[i+total_naves].activo = false;
        naves[i+total_naves].visible = false;
    }

    

    municion_nave[0].x = -2;
    municion_nave[0].y = -2;
    municion_nave[0].z = 5;

    municion_nave[1].x =  2;
    municion_nave[1].y = -2;
    municion_nave[1].z = 5;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(350, 10);
    glutCreateWindow("Battlesphere Gold - Atari Jaguar");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyInput);
    glutReshapeFunc(reshape);
    glutTimerFunc(Retardo,timer, 1);
    glutMainLoop();
    return 0;
}
