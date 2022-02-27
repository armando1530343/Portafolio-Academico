
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string.h> 
#include <sstream>

#define Retardo1 1500
#define Retardo2 10
#define Retardo3 800


using namespace std;

// Globals.
static int width, height; // OpenGL window size.
static float pointSize = 15.0; // Size of point
int refreshMills = 3; // refresh interval in milliseconds

GLfloat x;
GLfloat y = 700.0f; //valor inicial en y de los triangulos que caen


bool gameOver = false;//identifica el fin del juego 
int puntos = 0;//puntos que se acumulan en el juego
int numTriangulos = 0;//numero de triangulos que se van creando
int tiempoJuego = 0;//tiempo del juego en segundos


//esta clase es para crear los vertices del triangulo principal(Triangulo verde)
class Point
{
public:
   Point(float x, float y)
   {
	  xVal = x; yVal = y; size = pointSize;
   }
   Point(){};
   void setCoords(int x, int y)
   {
	  xVal = x; yVal = y;
   }
   float getXVal()//regresa la coordenada x del punto
   {
	return xVal;
   }
   float getYVal()//regresa la coordenada y del punto
   {
	return yVal;
   }

private:
   float xVal, yVal;
   static float size;
};

float Point::size = pointSize;//tamaño de un punto


//esta clase se encarga de crear los triangulos que van cayendo
class Triangle
{
	public:
	Triangle(float x, float y, int c, int vel)
	{
		xVal = x; yVal = y;//coordenada del vertice superior del triangulo
		typeColor = c;//tipo de triangulo

		//coordenadas de los otros dos vertices
		if(typeColor == 2){
			vertice2x = xVal - 30; vertice2y = yVal - 60;
    		vertice3x = xVal + 30; vertice3y = yVal - 60;	
		}
		else{
			vertice2x = xVal - 20; vertice2y = yVal - 40;
    		vertice3x = xVal + 20; vertice3y = yVal - 40;
		}	

    	 
    	velocidad = vel;
    	
	}
	Triangle(){};
	void setCoords(int x, int y){xVal = x; yVal = y;}//actualiza las coordenadas del punto superior
	float getXVal(){return xVal;}//regresa la coord en x
	float getYVal(){return yVal;}//regresa la coord en Y
	//regresan las coordenadas de los vertices
	float getVertice2x(){return vertice2x;}
	float getVertice2y(){return vertice2y;}
	float getVertice3x(){return vertice3x;}
	float getVertice3y(){return vertice3y;}
	int getColor(){return typeColor;}
	int getVelocidad(){return velocidad;}
	void setYVal(float newY){
	    yVal = newY;
	    vertice2y = yVal - 40;
	    vertice3y = yVal-40; 
  	}
	private:
	float xVal, yVal, velocidad;
  	float vertice2x, vertice2y, vertice3x, vertice3y;
  	int rojo, verde, azul, typeColor, colisions;
};

//funcion de imprimir texto en pantalla
void writeBitmapString(void *font, string str)
{
	int i;
   	for(i = 0; i < str.size(); i++)
   		glutBitmapCharacter(font, str[i]);   
}

vector <Point> points; //vector en donded se guardas los vertices del triangulo verde
vector <Triangle> triangles; //vector en conde se guardan las coordenadas de los triangulos cayendo
vector <Point> ladosTriangulo; //lados del triangulo verde


//esta funcion sirve para detectar cuando un vertice de un triangulo que cae
//toca alguno de los lados
//es decir, calcula si un punto pertenece a la recta(algun lado del triangulo)
int ecuacionRecta(double x, double y, double x1, double y1, double x2, double y2){
    double m = (y2-y1)/(x2-x1);
    double Y = y1 + m*x - m*x1;
    return (int)Y;
}

//funcion que dibuja el escenario
void drawScene(void)
{
   
   glClear(GL_COLOR_BUFFER_BIT);
   
   int i;
   
   //se dibuja el triangulo verde
    glPointSize(pointSize);
	glBegin(GL_POLYGON);
    glColor3f(0,1,0);
    glVertex2f(points.at(0).getXVal(), points.at(0).getYVal());
	glVertex2f(points.at(1).getXVal(), points.at(1).getYVal());
	glVertex2f(points.at(2).getXVal(), points.at(2).getYVal());
	glEnd();


	//se dibujan los triangulos que caen
	glBegin(GL_TRIANGLES);
	
   for(i = 0; i < triangles.size(); i++){
   		//color rojo
   		if(triangles.at(i).getColor() == 0) glColor3f(1.0, 0.0, 0.0);
   		//azul
   		else if(triangles.at(i).getColor() == 1) glColor3f(0.0, 0.0, 1.0);
   		
   		//multicolor
   		if(triangles.at(i).getColor() == 2) glColor3f(1.0, 0.0, 0.0);
        glVertex3f(triangles.at(i).getXVal(), triangles.at(i).getYVal(),0.0);
        if(triangles.at(i).getColor() == 2) glColor3f(0.0, 1.0, 0.0);
        glVertex3f(triangles.at(i).getVertice2x(), triangles.at(i).getVertice2y(),0.0);
        if(triangles.at(i).getColor() == 2) glColor3f(0.0, 0.0, 1.0);
        glVertex3f(triangles.at(i).getVertice3x(), triangles.at(i).getVertice3y(),0.0);
   }

   glEnd();

   //se imprime la puntuacion del juego
   glColor3f(1.0, 1.0, 1.0);
   stringstream ss; ss<<puntos<<endl;
   string newStr = ss.str();   
   glRasterPos2f(5, 550);
   writeBitmapString(GLUT_BITMAP_HELVETICA_18, newStr);

   //esto se imprimirá una ves que el juego se termine
   if (gameOver == true){
	   	glRasterPos2f(200, 350);   	
	   	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "HAS PERDIDO");
	   	glRasterPos2f(200, 300);   	
	   	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Puntos: " + newStr);
   }
   glColor3f(1.0,0.0,0.0);
    glRasterPos3f(10,600, 0.0);

    glFlush();
}

//este timer es lo que tarda en dibujarse un nuevo triangulo en la pantalla (1500 milisegundos)
void TimerFunction1(int value){

	if(gameOver == false){
		int color = 0;
		int vel = 3 + rand()%10;

		//por cada cinco triangulos rojos que se dibujen
		//cambiara a un nuevo color
		if(tiempoJuego % 5 == 0) color = rand()%2;
		//por cada once triangulos que se dibujen cambiara a multicolor
		if(tiempoJuego % 11 == 0) color = 2;

		//se crea un nuevo triangulo
		Triangle t = Triangle(rand()%500, y, color, vel);
		triangles.push_back(t);


		glutPostRedisplay();
		glutTimerFunc(Retardo1,TimerFunction1, 1);
		tiempoJuego++;
	}
	
}

int colisiones;
bool colision = false;
bool dentro = false;

//acciones del triangulo azul
void funcionAzul(int i){
	
	if (triangles.at(i).getColor() == 1){
		colisiones++;
	
		
		if (colisiones == 3){
			dentro = !dentro;

			colisiones = 0;
		}
	}
	
}

//este timer muestra el tiempo en que un triangulo que cae recorre el eje y
//que decrementa 1 unidad
void TimerFunction2(int value){
    float auxY, vel;
    int i, j;
 	double v1x, v1y, v2x, v2y, v3x, v3y, p1x, p1y, p2x, p2y, p3x, p3y;
 	
 	if(gameOver == false){
    
		for (i = 0; i < triangles.size(); i++){

	        auxY = triangles.at(i).getYVal();
	        vel = triangles.at(i).getVelocidad();
	        triangles.at(i).setYVal(auxY - 1);

	        //se obtienen los vertices de los triangulos
	        v1x = triangles.at(i).getXVal();
	        v1y = triangles.at(i).getYVal();
	        v2x = triangles.at(i).getVertice2x();
	        v2y = triangles.at(i).getVertice2y();
	        v3x = triangles.at(i).getVertice3x();
	        v3y = triangles.at(i).getVertice3y();
	        //se otienen los vertices del triangulo verde
	        p1x = points.at(0).getXVal();
	        p1y = points.at(0).getYVal();
	        p2x = points.at(1).getXVal();
	        p2y = points.at(1).getYVal();
	        p3x = points.at(2).getXVal();
	        p3y = points.at(2).getYVal();


	       // estas son las condiciones para detectar cuando uno de los triangulos
	       // colisiona con alguno de los lados del triangulo verde
	       // de acuerdo a la funcion de cada uno 
	        
	        if(v1x > p2x && v1x < p1x || v1x < p2x && v1x > p1x){
	    		if(v2y == ecuacionRecta(v1x, v1y, p1x, p1y, p2x, p2y) ){
	    				    			
	    			if(triangles.at(i).getColor() == 0)gameOver = true;
	    			funcionAzul(i);
					colision = true;
	    			
	    		} 
	    		else colision = false;   		
	    		
	    	}        
	    	if(v2x > p2x && v2x < p1x || v2x < p2x && v2x > p1x){
	    		if(v2y == ecuacionRecta(v2x, v2y, p1x, p1y, p2x, p2y)){
	    			
	    			if(triangles.at(i).getColor() == 0)gameOver = true;
	    			funcionAzul(i);
					colision = true;
	    			
	    		}
	    		else colision = false;  
	    	}
	    	if(v3x > p2x && v3x < p1x || v3x < p2x && v3x > p1x){
	    		if(v3y == ecuacionRecta(v3x, v3y, p1x, p1y, p2x, p2y)){
	    			
	    			if(triangles.at(i).getColor() == 0)gameOver = true;
	    			funcionAzul(i);
					colision = true;
	    		} 
	    		else colision = false; 
	    	}    

	        if(v1x > p3x && v1x < p2x || v1x < p3x && v1x > p2x){
	    		if(v1y == ecuacionRecta(v1x, v1y, p2x, p2y, p3x, p3y)){
	    			
	    			if(triangles.at(i).getColor() == 0)gameOver = true;
	    			funcionAzul(i);
					colision = true;
	    		} 
	    		else colision = false;  
	    	} 
	    	if(v2x > p3x && v2x < p2x || v2x < p3x && v2x > p2x){
	    		if(v2y == ecuacionRecta(v2x, v2y, p2x, p2y, p3x, p3y)){
	    			
	    			if(triangles.at(i).getColor() == 0)gameOver = true;
	    			funcionAzul(i);
					colision = true;
	    		}
	    		else colision = false;   
	    	}  
	    	if(v3x > p3x && v3x < p2x || v3x < p3x && v3x > p2x){
	    		if(v3y == ecuacionRecta(v3x, v3y, p2x, p2y, p3x, p3y)){
	    			
	    			if(triangles.at(i).getColor() == 0)gameOver = true;
	    			funcionAzul(i);
					colision = true;
	    		}
	    		else colision = false;   
	    	} 

	        if(v1x > p1x && v1x < p3x || v1x < p3x && v1x > p1x){
	    		if(v1y == ecuacionRecta(v1x, v1y, p1x, p1y, p3x, p3y)){
	    			
	    			if(triangles.at(i).getColor() == 0)gameOver = true;
	    			funcionAzul(i);
					colision = true;
	    		} 
	    		else colision = false;  
	    	}  
	    	if(v2x > p1x && v2x < p3x || v2x < p3x && v2x > p1x){
	    		if(v2y == ecuacionRecta(v2x, v2y, p1x, p1y, p3x, p3y)){
	    			
	    			if(triangles.at(i).getColor() == 0)gameOver = true;
	    			funcionAzul(i);
					colision = true;
	    		} 
	    		else colision = false;  
	    	}    
	    	if(v3x > p1x && v3x < p3x || v3x < p3x && v3x > p1x){
	    		if(v3y == ecuacionRecta(v3x, v3y, p1x, p1y, p3x, p3y)){
	    			
	    			if(triangles.at(i).getColor() == 0)gameOver = true;
	    			funcionAzul(i);
					colision = true;
	    		} 
	    		else colision = false;  
	    	}       

		}
		 if(dentro == true) puntos+=1;
		glutPostRedisplay();
		glutTimerFunc(Retardo2,TimerFunction2, 1);
	}
	
	
}




int flag = 0;

//funcion que calcula la distancia entre las coordenadas del mouse y los vertices 
//del triangulo verde
double distanciaPuntos(double x1, double y1, double x2, double y2){
  double distancia = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
  
  return distancia;
}

//acciones con el mouse
void mouseControl(int button, int state, int x, int y){

  	double d1, d2, d3;
  	bool multicolor = false;

  	if(gameOver == false){

  		//tocando el boton derecho del mouse
		if (button == GLUT_LEFT_BUTTON){
			  d1 = distanciaPuntos(points.at(0).getXVal(),points.at(0).getYVal(),x,height-y);
		      d2 = distanciaPuntos(points.at(1).getXVal(),points.at(1).getYVal(),x,height-y);
		      d3 = distanciaPuntos(points.at(2).getXVal(),points.at(2).getYVal(),x,height-y);

		      //se detecta si se da clic en un triangulo multicolor(typecolor 2)
		      for(int i = 0; i < triangles.size(); i++){
		      		if(triangles.at(i).getColor()==2){
		      			if(triangles.at(i).getYVal()+30 > height-y &&
		      			   triangles.at(i).getVertice2y()-30 < height-y &&
		      			   triangles.at(i).getVertice2x()-30 < x &&
		      			   triangles.at(i).getVertice3y()-30 < height-y &&
		      			   triangles.at(i).getVertice3x()+30 > x){
		      				multicolor = true;
		      				puntos += 20;
		      			}
		      		}
		      }
		      if(multicolor == false){
		      	if(d1<d2 && d1<d3){points.at(0).setCoords(x, height-y); flag = 1;}
			    else if(d2<d1 && d2<d3){points.at(1).setCoords(x, height-y); flag =2;} 
			    else if(d3<d1 && d3<d2){points.at(2).setCoords(x, height-y); flag = 3;}  	
		      }

		      

		}
	}
}

//timer de los puntos que se acumulan
void Puntos(int value) {
	double d1 = distanciaPuntos(points.at(0).getXVal(),points.at(0).getYVal(),points.at(1).getXVal(),points.at(1).getYVal());
	double d2 = distanciaPuntos(points.at(1).getXVal(),points.at(1).getYVal(),points.at(2).getXVal(),points.at(2).getYVal());
   	double d3 = distanciaPuntos(points.at(2).getXVal(),points.at(2).getYVal(),points.at(0).getXVal(),points.at(0).getYVal());
	
	//acumulacion de puntos de acuerdo al tamaño de los lados del triangulo verde
	if(gameOver == false){
		puntos += d1*.02;
		puntos += d2*.02;
		puntos += d3*.02;
	}

	

   glutPostRedisplay();      
   glutTimerFunc(Retardo3, Puntos, 0); 
}


//funcion que mueve los vertices del triangulo verde cada que se selecciona uno
void mouseMotion(int x, int y)
{

    if(flag == 1)
    {
		points.at(0).setCoords(x, height-y);
	}

	if(flag == 2)
	{
		points.at(1).setCoords(x, height-y);
	}

	if(flag == 3)
	{
		points.at(2).setCoords(x, height-y);
	}

	if (gameOver == false){
		glutPostRedisplay();
	}  

}

void resize(int w, int h)
{
   glViewport(0, 0, w, h);

   glMatrixMode(GL_PROJECTION);

   glLoadIdentity();

   glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

   glMatrixMode(GL_MODELVIEW);

   width = w;
   height = h;

   glLoadIdentity();
}


void keyInput(unsigned char key, int x, int y)
{
   switch (key)
   {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}
void SetupRC (void)
{
	glClearColor (0.0f,0.0f,0.0f,1.0f);
}



int main(int argc, char **argv)
{
    srand(time(NULL));

	cout<<endl<<"================================================================================"<<endl;
	cout<<endl<<"--------------------------PROYECTO GRUPAL 1 Tri-morph---------------------------"<<endl;
	cout<<endl<<"Integrantes:"<<endl;
	cout<<endl<<"Armando Issac Hernandez Muniz"<<endl;
	cout<<endl<<"Mariana Magdalena Hinojosa Tijerina"<<endl;
	cout<<endl<<"Yuridia Guadalupe Montelongo Padilla"<<endl;
	cout<<endl<<"-------------------------------------------------------------------------------"<<endl;
	cout<<endl<<"Interaccion:"<<endl;
	cout<<endl<<"1. Mueve los vertices del triangulo verde con el mouse"<<endl;
	cout<<endl<<"2. Esquiva los triangulos de color rojo, si tocan el triangulo verde pierdes y se acaba el juego"<<endl;
	cout<<endl<<"3. Haz que el triangulo de color azul quede completamente dentro del verde y obtendras puntos extras"<<endl;
	cout<<endl<<"4. Cada que te salga un triangulo de colores haz clic sobre el para obtener puntos extras"<<endl;
	cout<<endl<<"5. Puedes ver tu score en el lado superior izquierdo"<<endl;
	cout<<endl<<"DIVIERTETE JUGANDO!!!!!!!!!!!!"<<endl;
	cout<<endl<<"================================================================================="<<endl;

    //se crean las coordenadas de los vertices del triangulo verde
    Point p1 = Point(250,250); //0
	Point p2 = Point(100, 100);
	Point p3 = Point(300, 100);

	//se agregan los vertices al vector de puntos
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);

   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(500, 650);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Proyecto Grupal -- Tri-morph --");
   glutDisplayFunc(drawScene);
   glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);   
	glutMouseFunc(mouseControl);
	glutMotionFunc(mouseMotion);

   glutTimerFunc(Retardo1,TimerFunction1, 1);
   glutTimerFunc(Retardo2,TimerFunction2, 1);
   glutTimerFunc(Retardo3,Puntos, 1);
 
   SetupRC ();
   glutMainLoop();
   return 0;
}
