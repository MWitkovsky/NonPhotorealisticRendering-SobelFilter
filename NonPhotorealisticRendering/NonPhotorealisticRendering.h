#pragma once

#include <GL/glut.h>

//Constants for window size
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

//Constant for the sobel filter
int THRESHOLD = 87;

//variables for state management
bool grayscale;
bool depthComponent;
bool sobel;
int displayMode;

//pixel storage
unsigned char pixels[600][800];
unsigned char outputPixels[600][800];

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
void toggleSobelFilter();
void sobel_filtering(unsigned char pixels[600][800]);
void clearSobel();
void display1();
void display2();
void setView();
void processSobel();
void currentDisplay();
void keyboard(unsigned char key, int x, int y);
