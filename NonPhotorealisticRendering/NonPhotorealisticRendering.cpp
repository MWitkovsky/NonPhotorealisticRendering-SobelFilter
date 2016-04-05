// NonPhotorealisticRendering.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NonPhotorealisticRendering.h"
#include <iostream>

void initGlut(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Nonphotorealistic Rendering");

	glLightfv(GL_LIGHT6, GL_DIFFUSE, diffuse6);
	glLightfv(GL_LIGHT6, GL_POSITION, position6);

	//Turn lighting on
	glEnable(GL_LIGHTING);
	//Start with just the normal white light above the cube
	glEnable(GL_LIGHT6);
	//Enable depth test for proper 3d rendering
	glEnable(GL_DEPTH_TEST);

	//Diffuse property for the cube
	GLfloat diffusereflect[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffusereflect);

	//White clear color
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

//Makes sure the lights rotate with the current matrix
void lightRepositioning() {
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
	glLightfv(GL_LIGHT2, GL_POSITION, position2);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction2);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse3);
	glLightfv(GL_LIGHT3, GL_POSITION, position3);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, direction3);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse4);
	glLightfv(GL_LIGHT4, GL_POSITION, position4);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, direction4);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuse5);
	glLightfv(GL_LIGHT5, GL_POSITION, position5);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, direction5);
}

//Switches between single overhead light and the colored+positioned normal extracting lights
void toggleGrayscale() {
	if (grayscale) {
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		glEnable(GL_LIGHT4);
		glEnable(GL_LIGHT5);
		glDisable(GL_LIGHT6);
	}
	else {
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);
		glDisable(GL_LIGHT5);
		glEnable(GL_LIGHT6);
	}
	grayscale = !grayscale;
	display1();
}

//Toggles rendering of the depth component data
void toggleDepthComponent() {
	depthComponent = !depthComponent;
}

//Sobel filter convolving, where the pixels are interpreted into outlines
void sobel_filtering(unsigned char pixels[800][600]){
	int Sx[3][3] = { 
	{ -1,  0,  1 },
	{ -2,  0,  2 },
	{ -1,  0,  1 }
	};

	int Sy[3][3] = {
	{ -1, -2, -1 },
	{  0,  0,  0 },
	{  1,  2,  1 }
	};
}

void display1() {
	//Clear previous frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//make the cube
	glutSolidCube(1.0);

	//rotate the view and set up the lighting
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glRotatef(45.0, 1.0, 1.0, 1.0);
	glPushMatrix();
	lightRepositioning();
	glPopMatrix();
	
	glFlush();

	//Does the depth component if triggered
	if (depthComponent) {
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Reads in the depth values of the current image
		glReadPixels(0, 0, 800, 600, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, &pixels);
		//sobel_filtering(pixels);

		//Draws the result
		glDrawPixels(800, 600, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, &pixels);
		glFlush();
	}
}

//Handles all the keyboard controls involved with this project
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	//If escape is pressed, the program exits
	case 27:
		exit(0);
		break;
	//If 1 is pressed, switches to display mode 1
	case '1':
		displayMode = 1;
		glutDisplayFunc(display1);
		display1();
		break;
	//If x is pressed, switches between overhead and colored lights
	case 'x':
		toggleGrayscale();
		break;
	//If d is pressed, toggles depth component convolution
	case 'd':
		toggleDepthComponent();
		display1();
		break;
	}
}

int main(int argc, char** argv)
{
	initGlut(argc, argv);
	displayMode = 1;
	grayscale = true;
	depthComponent = false;
	
	glutDisplayFunc(display1);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
