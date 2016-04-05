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

	glEnable(GL_LIGHTING);
	/*glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);*/
	glEnable(GL_LIGHT6);
	glEnable(GL_DEPTH_TEST);

	GLfloat diffusereflect[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffusereflect);

	glClearColor(0.0, 0.0, 0.0, 1.0);
}

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

	//unsigned char pixels[800][600];
	//glReadPixels(0, 0, 800, 600, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, &pixels);
	//sobel_filtering(pixels);
	//glDrawPixels(800, 600, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, &pixels);
	//glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	case '1':
		displayMode = 1;
		glutDisplayFunc(display1);
		display1();
		break;
	case 'x':
		toggleGrayscale();
		break;
	}
}

int main(int argc, char** argv)
{
	initGlut(argc, argv);
	displayMode = 1;
	grayscale = true;
	
	glutDisplayFunc(display1);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
