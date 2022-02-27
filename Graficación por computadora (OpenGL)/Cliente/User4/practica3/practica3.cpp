#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#define SIZE 600
#define PI 3.141592654 
#define Retardo 12

using namespace std;

double centroX = SIZE/2, //coordenada X del punto central
    centroY = SIZE/2, //coordenada Y del punto central
    angulo_rotacion = 60, //angulo de rotacion que sirve para dibujar la linea angular
    puntoX_rotacion = centroX, //coordenada en X del punto que rota
    puntoY_rotacion = centroY + 30, //coordenada en Y del punto que rota
    puntoX_ordenada = 0,  //coordenada en X del punto en el eje x
    puntoY_ordenada = centroX, //coordenada en Y del punto en el eje x
    radio = 100, //distancia del centro al punto de rotacion
    radio2 = 40, //distancia del centro a la posicion de la linea angular
    hipotenusa = 150; //valor constante de la distancia entre los dos puntos en movimento

//se crea un tipo de dato que guarda los datos de un circulo
struct circunferencia{
    double x, y, angulo;
};

std::vector<circunferencia> coordenadas;

//funcion de imprimir texto en pantalla
void writeBitmapString(void *font, string str)
{
    int i;
    for(i = 0; i < str.size(); i++)
        glutBitmapCharacter(font, str[i]);   
}

// Funcion que controla los eventos de dibujo de la aplicacion.
void display(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,0,0);

    //se dibuja el plano cartesiano
    glBegin(GL_LINES);
    glVertex2f(0, SIZE/2);
    glVertex2f(SIZE, SIZE/2);
    glVertex2f(SIZE/2, 0);
    glVertex2f(SIZE/2, SIZE);
    glEnd();

    glColor3f(0,0,1);

    //punto central
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(centroX, centroY);
    glEnd();
    glRasterPos2f(centroX-10, centroY-10);    
    writeBitmapString(GLUT_BITMAP_HELVETICA_10, "A");

    //punto de rotacion
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(puntoX_rotacion, puntoY_rotacion);
    glEnd();
    glRasterPos2f(puntoX_rotacion-10, puntoY_rotacion);    
    writeBitmapString(GLUT_BITMAP_HELVETICA_10, "B");

    //punto en movimiento en el eje x
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(puntoX_ordenada, puntoY_ordenada);
    glEnd();
    glRasterPos2f(puntoX_ordenada+5, puntoY_ordenada-10);    
    writeBitmapString(GLUT_BITMAP_HELVETICA_10, "C");

    glColor3f(0,0,0);

    //lineas que unen a todos los puntos para formar un triangulo
    glBegin(GL_LINES);
    glVertex2f(centroX, centroY);
    glVertex2f(puntoX_rotacion, puntoY_rotacion);
    glVertex2f(puntoX_rotacion, puntoY_rotacion);
    glVertex2f(puntoX_ordenada, puntoY_ordenada);
    glEnd();

    //se dibuja la linea angular de acuerdo a las coordenadas guardadas en el vector
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < coordenadas.size(); ++i)
    {
        glVertex2f(coordenadas.at(i).x, coordenadas.at(i).y);
    }
    glEnd();

    
    
    glFlush(); 

    glutSwapBuffers();
}
void verificar_hipotenusa(int x1, int y1, int x2, int y2){
    cout << "Hipotenusa: "<< sqrt(pow(x2-x1, 2) + pow(y2-y1, 2)) << endl;
}
void Timer(int value){

    //se incrementa el angulo de rotacion del punto
    puntoX_rotacion = radio * cos(angulo_rotacion*PI/180) + centroX;
    puntoY_rotacion = radio * sin(angulo_rotacion*PI/180) + centroY;

    //se calcula la distancia entre los dos puntos en movimiento
    double Y = sqrt(pow(puntoY_rotacion - puntoY_ordenada, 2));
    double X = pow(hipotenusa, 2) - Y;
    puntoX_ordenada = (puntoX_rotacion - sqrt(X));
    //se modifica la posicion en X del punto en el eje de las ordenadas
    puntoX_ordenada = centroX + puntoX_ordenada;

    //se guardan las coordenadas del angulo dibujado
    circunferencia c;
    c.x = radio2 * cos(angulo_rotacion*PI/180) + centroX;
    c.y = radio2 * sin(angulo_rotacion*PI/180) + centroY;
    coordenadas.push_back(c);
    angulo_rotacion++;

    //por cada 360 grados se dibuja un nuevo angulo
    //se limpia el vector de coordenadas y se guardan las nuevas
    if(int(angulo_rotacion)%360 == 0){
        coordenadas.clear();
    }    
    //verificar_hipotenusa(puntoX_rotacion, puntoY_rotacion, puntoX_ordenada, puntoY_ordenada);


    glutPostRedisplay();
    glutTimerFunc(Retardo,Timer, 1);
}
// Funcion encargada de controlar el cambio de tamano de la ventana
void reshape(int w, int h)
{
    glViewport (0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[])
{
    //angulo_rotacion = atan2(puntoY_rotacion - centroY, puntoX_rotacion - centroX) * 180 / PI;
    circunferencia c;

    c.x = centroX+radio2;
    c.y = centroY;
    angulo_rotacion = atan2(c.y - centroY, c.x - centroY) * 180 / PI;
    coordenadas.push_back(c);
    angulo_rotacion++;
    
    for (int i = 1; i <= 90; ++i)
    {
        c.x = radio2 * cos(angulo_rotacion*PI/180) + centroX;
        c.y = radio2 * sin(angulo_rotacion*PI/180) + centroY;
        coordenadas.push_back(c);
        angulo_rotacion++;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(SIZE, SIZE);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("Practica 3");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(Retardo,Timer, 1);
    //glutTimerFunc(Retardo2,TimerFunction2, 1);
    glutMainLoop();
    return 0;
}

/*

Desarrollo Experimental:

Esta practica fue desarrollada en c++ con las librerias de opengl. Primero se dibujan los ejes X y Y sobre la pantalla con GL_LINES,
despues se definen las coordenadas del centro (x,y) en las que ira uno de los puntos, tambien se inicializan las coordenadas del punto
que rota con respecto al centro y por ultimo las coordenadas del punto que se mueve solo en el eje de las X (ordenadas).

Se define una variable llamada 'hipotenusa' la cual representa a la distancia constante que debe haber entre los dos puntos en 
movimiento, el vertice del eje X se movera de acuerdo a la posicion del vertice de rotacion para que cumpla siempre con la distancia 
de la hipotenusa, para ello se uso la formula de la distancia euclidiana pero se hizo una modificacion a la formula ya que la distancia
ya es conocida, lo que se desconce en este caso es la posicion variable en X del vertice de en el eje de las ordenadas y por eso fue que se
hizo un despeje de la formula para obtener ese valor, que es el unico que varía en este vertice ya que el valor en Y siempre permanecera a 
la altura del eje X. 

Una vez comprobando la distancia entre estos puntos, en una funcion de timer se va incrementando el valor del angulo de 
rotacion del punto. 

Por ultimo se dibujan las lineas que unen a los puntos para formar el triangulo (GL_LINES) y el marco de la linea angular
que se formando (GL_LINE_STRIP) que sera removida una vez llegue a los 360 grados.


*/