/*
 * GL07BouncingBall.cpp: A ball bouncing inside the window
 */
//#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <math.h>     // Needed for sin, cos
#include <iostream>
#include <time.h>
#define PI 3.14159265f

//#define NUM_BALLS 100

using namespace std;
 
// Global variables
char title[] = "Bouncing Ball (2D)";  // Windowed mode's title
int windowWidth  = 640;     // Windowed mode's width
int windowHeight = 480;     // Windowed mode's height
int windowPosX   = 50;      // Windowed mode's top-left corner x
int windowPosY   = 50;      // Windowed mode's top-left corner y

struct Balls_Atributes{
	GLfloat ballRadius = 0.5f;   // Radius of the bouncing ball
	GLfloat ballX= 0.0f;         // Ball's center (x, y) position
	GLfloat ballY= 0.0f;
	
	GLfloat xSpeed= 0.02f;      // Ball's speed in x and y directions
	GLfloat ySpeed= 0.007f;
	GLfloat ballXMax, ballXMin, ballYMax, ballYMin; // Ball's center (x, y) bounds
	      
	 
		
}Ball[100];

int NUM_BALLS = 2;

// Projection clipping area
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;


 
int refreshMillis = 30;// Refresh period in milliseconds
 
/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
}
 
/* Callback handler for window re-paint event */
void display() {
   glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
   glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
   glLoadIdentity();              // Reset model-view matrix
 	

   for (int i = 0; i < NUM_BALLS; i++)
   {
   		//Ball[i] = Balls_Atributes();
   		glTranslatef(Ball[i].ballX, Ball[i].ballY, 0.0f);  // Translate to (xPos, yPos)
	   // Use triangular segments to form a circle

	   glBegin(GL_TRIANGLE_FAN);
	      glColor3f(rand()%2,rand()%2,rand()%2);  // Blue
	      glVertex2f(0.0f, 0.0f);       // Center of circle
	      int numSegments = 100;
	      GLfloat angle;
	      for (int j = 0; j <= numSegments; j++) { // Last vertex same as first vertex
	         angle = j * 2.0f * PI / numSegments;  // 360 deg for all segments
	         glVertex2f(cos(angle) * Ball[i].ballRadius, sin(angle) * Ball[i].ballRadius);
	      }
	   glEnd();
	   //cout<<"aqui"<<endl;
	}



	 
	glutSwapBuffers();  // Swap front and back buffers (of double buffered mode)
	
	for (int i = 0; i < NUM_BALLS; i++){ 
	   // Animation Control - compute the location for the next refresh
	   Ball[i].ballX += Ball[i].xSpeed;
	   Ball[i].ballY += Ball[i].ySpeed;
	   // Check if the ball exceeds the edges
	   if (Ball[i].ballX > Ball[i].ballXMax) {
	      Ball[i].ballX = Ball[i].ballXMax;
	      Ball[i].xSpeed = -Ball[i].xSpeed;
	   } else if (Ball[i].ballX < Ball[i].ballXMin) {
	      Ball[i].ballX = Ball[i].ballXMin;
	      Ball[i].xSpeed = -Ball[i].xSpeed;
	   }
	   if (Ball[i].ballY > Ball[i].ballYMax) {
	      Ball[i].ballY = Ball[i].ballYMax;
	      Ball[i].ySpeed = -Ball[i].ySpeed;
	   } else if (Ball[i].ballY < Ball[i].ballYMin) {
	      Ball[i].ballY = Ball[i].ballYMin;
	      Ball[i].ySpeed = -Ball[i].ySpeed;
	   }	
   }

   
}
 
/* Call back when the windows is re-sized */
void reshape(GLsizei width, GLsizei height) {
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset the projection matrix
   
	if (width >= height) {
	  clipAreaXLeft   = -1.0 * aspect;
	  clipAreaXRight  = 1.0 * aspect;
	  clipAreaYBottom = -1.0;
	  clipAreaYTop    = 1.0;
	} else {
	  clipAreaXLeft   = -1.0;
	  clipAreaXRight  = 1.0;
	  clipAreaYBottom = -1.0 / aspect;
	  clipAreaYTop    = 1.0 / aspect;
	}
	
	gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
	for (int i = 0; i < NUM_BALLS; ++i)
   {
	   Ball[i].ballXMin = clipAreaXLeft + Ball[i].ballRadius;
	   Ball[i].ballXMax = clipAreaXRight - Ball[i].ballRadius;
	   Ball[i].ballYMin = clipAreaYBottom + Ball[i].ballRadius;
	   Ball[i].ballYMax = clipAreaYTop - Ball[i].ballRadius;
   }
   
}
//acciones con el mouse
void mouseControl(int button, int state, int x, int y){
      //tocando el boton derecho del mouse
      if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
         NUM_BALLS++;

      }
      cout<<NUM_BALLS<<endl;
}
 
/* Called back when the timer expired */
void Timer(int value) {
   glutPostRedisplay();    // Post a paint request to activate display()
   glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}
 
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	srand(time(NULL));
	for (int i = 0; i < 100; ++i)
	{
		Ball[i].ballRadius = 0.3f;   // Radius of the bouncing ball
		Ball[i].ballX= 0.0f;         // Ball's center (x, y) position
		Ball[i].ballY= 0.0f;
		Ball[i].xSpeed= rand()%4 * 0.01;      // Ball's speed in x and y directions
		Ball[i].ySpeed= rand()%4 * 0.001;
	}
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
   glutInitWindowPosition(windowPosX, windowPosY); // Initial window top-left corner (x, y)
   glutCreateWindow(title);      // Create window with given title
   glutDisplayFunc(display);     // Register callback handler for window re-paintz
   glutReshapeFunc(reshape);     // Register callback handler for window re-shape
   glutMouseFunc(mouseControl);
   glutTimerFunc(0, Timer, 0);   // First timer call immediately
   initGL();                     // Our own OpenGL initialization
   glutMainLoop();               // Enter event-processing loop
   return 0;
}

