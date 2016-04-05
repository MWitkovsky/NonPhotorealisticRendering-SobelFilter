#pragma once

#include <GL/glut.h>

//variables for state management
bool grayscale;
bool depthComponent;
int displayMode;

//pixel storage
unsigned char pixels[800][600];
unsigned char outputPixels[800][600];

//All the light settings
GLfloat diffuse0[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat position0[] = { 1.0, 0.0, 0.0, 0.0 };
GLfloat direction0[] = { -1.0, 0.0, 0.0 };
GLfloat diffuse1[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat position1[] = { 0.0, 1.0, 0.0, 0.0 };
GLfloat direction1[] = { 0.0, -1.0, 0.0 };
GLfloat diffuse2[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat position2[] = { 0.0, 0.0, 1.0, 0.0 };
GLfloat direction2[] = { 0.0, 0.0, -1.0 };
GLfloat diffuse3[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat position3[] = { -1.0, 0.0, 0.0, 0.0 };
GLfloat direction3[] = { 1.0, 0.0, 0.0 };
GLfloat diffuse4[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat position4[] = { 0.0, -1.0, 0.0, 0.0 };
GLfloat direction4[] = { 0.0, 1.0, 0.0 };
GLfloat diffuse5[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat position5[] = { 0.0, 0.0, -1.0, 0.0 };
GLfloat direction5[] = { 0.0, 0.0, 1.0 };
GLfloat diffuse6[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat position6[] = { 0.0,3.0,-1.0,0.0 };

//All the methods for the project
void initGlut(int argc, char **argv);
void lightRepositioning();
void toggleGrayscale();
void toggleDepthComponent();
void display1();
void keyboard(unsigned char key, int x, int y);