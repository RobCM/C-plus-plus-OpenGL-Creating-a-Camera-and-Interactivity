/*
Robert Coleman  2/5/2017
Module 04 Programming Assignment - Creating a Camera and Interactivity
Program most:
*Applies a transformation to an object that varies over time, using two of the following examples:
-An object that travels back and forth along a line repeatedly
-An object that moves in a circle
-An object that continually rotates
-An object that scales up and down repeatedly
*Uses a camera class to control the display of the scene
*Allows the user to reposition the camera in the scene using the arrow keys
*/
#include <iostream>
#include <Windows.h>
#include <glew.h>
#include <freeglut.h>

// Variabales that will be used by the camara function
// Angle of rotation for the camera direction
float angle = 0.0;
// Actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;
//Variable for the movement of the sphere
static int rotation = 0;

// Variables for the 3D box
bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)  
bool movingUp = false; // Whether or not we are moving up or down  
float yLocation = 0.0f; // Keep track of our position on the y axis.  
float yRotationAngle = 0.0f; // The angle of rotation for our object 

// ------------The camera functions-------------
void renderScene(void) // Rendering
{
	// Reset transformations
	glLoadIdentity();
	// Set where the camera starts
	gluLookAt(x, 1.0f, z, x + lx, 1.0f, z + lz, 0.0f, 1.0f, 0.0f);
	glEnd();
	glutSwapBuffers();
}

void changeSize(int w, int h) // View
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(10, 10, w, h);// Edges y and x of the view!
	// Set the correct perspective.
	gluPerspective(55.0f, ratio, 0.10f, 10.0f);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}
// Keys to control the camera
void camara(int key, int xx, int yy)
{
	float fraction = 0.1f;
	// XZ position of the camera
	float x = 0.0f, z = 5.0f;
	// Switch satesment to control the camara position!
	switch (key)
	{
	case GLUT_KEY_LEFT:// <-- key
	{
		// Rotation of the camera angle
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	}
	case GLUT_KEY_RIGHT:// --> key
	{
		// Rotation of the camera angle
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	}
  }
	glFlush();  // Render now
}
//----------End of camera functions-------------

// The function that constracts the objects
void OBJECTS(void)
{
	//---------Start construction of objects----------
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);// Important!
	 
	// Box object---(object that continually goes up and down)
	glTranslatef(0.0f, yLocation, 0.0f); // Translate our object along the y axis 
	glColor3f(1.0, 0.0, 4.0);// Vortex one = pink
	glRotatef(yRotationAngle, 0.0f, 1.0f, 0.0f); // Rotate our object around the y axis  
	glutWireCube(2.0f); // Render the primitive  
	glFlush(); // Flush the OpenGL buffers to the window  
	if (movingUp) // If we are moving up  
		yLocation -= 0.050f; // Speed to move up along our yLocation  
	else  // Otherwise  
		yLocation += 0.050f; // Speed to move down along our yLocation
	if (yLocation < -0.1f) // If we have gone down too far  
		movingUp = false; // Reverse our direction so we are moving down  
	else if (yLocation > 2.0f) // Else if we have gone up too far  
		movingUp = true; // Reverse our direction so we are moving up  
	glEnd(); //End box coordinates
	
	// Sphere---(object that continually rotates)
	glPushMatrix();
	glRotatef((GLfloat)rotation, 0.0, 1.0, 10.0);
	glutWireSphere(0.2, 10, 4);  
	glPopMatrix();
	// Movement of the sphere
	rotation = (rotation + 5) % 360;
	glutPostRedisplay();
	glutSwapBuffers();
	glEnd();// End Sphere coordinates
	glFlush();  // Render the objects now	
	//-------------End Construction of objects-----------------
}

// Main function
int main(int argc, char** argv)
{
	// Initialize GLUT
	glutInit(&argc, argv);
	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// Set the window's initial width & height (this has to be call before glutCreateWindow)
	glutInitWindowSize(800, 600);
	// Set window position (this has to be call before glutCreateWindow)
	glutInitWindowPosition(200, 100);
	// Create a window with the given title
	glutCreateWindow("Camera and Interactivity");	
	// Calling the camera functions
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutSpecialFunc(camara);
	// Calling the object's function
	glutDisplayFunc(OBJECTS);
	
	//-------------------------------MAKE GLEW WORK!
	// Enter the infinitely event-processing loop
	glutMainLoop();
	// This initializes the entry points in the OpenGL driver so we can 
	// call all the functions in the API.
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Sorry! GLEW error");
		return 1;
	}
	glutMainLoop();// Go to start of program
	//----------------------------------------------
	system("pause");
	return 0;
}
