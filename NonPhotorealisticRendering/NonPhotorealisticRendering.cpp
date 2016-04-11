/*
*	Non-Photorealistic Rendering project reproduced from the paper "Introduction to 3D Non-Photorealistic Rendering: Silhouettes and Outlines"
*	For CSE328 at Stony Brook University by Michael Witkovsky, Spring 2016
*	ID#: 108617627
*/

#include "stdafx.h"
#include "NonPhotorealisticRendering.h"
#include <iostream>

void initGlut(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
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

	//Black clear color
	glClearColor(0.0, 0.0, 0.0, 1.0);
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
void sobel_filtering(unsigned char pixels[600][800]){
	//filter for x component
	int Sx[3][3] = { 
	{ -1,  0,  1 },
	{ -2,  0,  2 },
	{ -1,  0,  1 }
	};

	//filter for y component
	int Sy[3][3] = {
	{ -1, -2, -1 },
	{  0,  0,  0 },
	{  1,  2,  1 }
	};

	//temp values for calculating the final value
	int tempx;
	int tempy;
	int tempVal;

	//Perform the filtering
	for (int y = 1; y < WINDOW_HEIGHT - 2; y++) {
		for (int x = 1; x < WINDOW_WIDTH - 2; x++) {
			//X convolution
			tempx =
				((Sx[0][0] * pixels[y - 1][x - 1]) + (Sx[0][1] * pixels[y - 1][x]) + (Sx[0][2] * pixels[y - 1][x + 1]) +
				 (Sx[1][0] * pixels[y][x - 1])     + (Sx[1][1] * pixels[y][x])     + (Sx[1][2] * pixels[y][x + 1]) +
				 (Sx[2][0] * pixels[y + 1][x - 1]) + (Sx[2][1] * pixels[y + 1][x]) + (Sx[2][2] * pixels[y + 1][x + 1]));
			//Y convolution
			tempy = 
				((Sy[0][0] * pixels[y - 1][x - 1]) + (Sy[0][1] * pixels[y][x]) + (Sy[0][2] * pixels[y - 1][x + 1]) +
				 (Sy[1][0] * pixels[y][x - 1])     + (Sy[1][1] * pixels[y][x]) + (Sy[1][2] * pixels[y][x + 1]) +
				 (Sy[2][0] * pixels[y + 1][x - 1]) + (Sy[2][1] * pixels[y][x]) + (Sy[2][2] * pixels[y + 1][x + 1]));

			//Normalization
			tempVal = (int)(sqrt((tempx * tempx) + (tempy * tempy)));
			//tempVal = tempx;

			//clamp to valid values
			if (tempVal > THRESHOLD) {
				tempVal = 255;
			}
			else if (tempVal < THRESHOLD){
				tempVal = 0;
			}

			if (outputPixels[y][x] == 0) {
				outputPixels[y][x] = tempVal;
			}
		}
	}
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
		//Reads in the depth values of the current image and convolves them against the sobel filter
		glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, pixels);
		sobel_filtering(pixels);

		//Convolves the RGB values and adds them to the depth map result if lights enabled
		if (!grayscale) {
			glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RED, GL_UNSIGNED_BYTE, pixels);
			sobel_filtering(pixels);
			glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_GREEN, GL_UNSIGNED_BYTE, pixels);
			sobel_filtering(pixels);
			glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_BLUE, GL_UNSIGNED_BYTE, pixels);
			sobel_filtering(pixels);
		}
		
		//Draws the result
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, outputPixels);
		//renderFilter();
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
	case 'p':
		++THRESHOLD;
		std::cout << THRESHOLD << ' ';
		display1();
		break;
	case 'o':
		--THRESHOLD;
		std::cout << THRESHOLD << ' ';
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
