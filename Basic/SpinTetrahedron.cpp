#include <iostream>
#include <cmath>
#include "include/GL/freeglut.h"

int width = 600, height = 400; // Window Width and Height

void rendering(); 
void DoTimer(int value);
void reShape(int w, int h); // For Rendering Functions

int angleValue = 0;

double basePoint1[3] = { 0, 0, (sqrt(6) * 1.5) };
double basePoint2[3] = { 3, (-sqrt(3)), -(sqrt(6) * 0.5) };
double basePoint3[3] = { -3, (-sqrt(3)), -(sqrt(6) * 0.5) };
double basePoint4[3] = { 0, (2 * sqrt(3)), -(sqrt(6) * 0.5) }; // Tetrahedron Base Point Setting




int main(int args, char** argv) {
	
	glutInit(&args, argv); // Start with openGL
	glutInitWindowSize(width, height); // Window size set
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Display Mode Set with RGB and Double Buffer
	glutCreateWindow("First");
	glEnable(GL_DEPTH_TEST); // Depth Checking enable

	glutDisplayFunc(rendering); // Display Function Setting function
	glutTimerFunc(1, DoTimer, 1); // Repeat Function Setting function
	glutReshapeFunc(reShape); // Window Displaying Setting function
	glutMainLoop(); // Infitniy Loop, before closing

	return 0;
}

void rendering() {

	glClearColor(0.25f, 0.25f, 0.25f, 0.25f); // Background Color
	glClear(GL_COLOR_BUFFER_BIT); // Buffer Set

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-12, 12, -8, 8, -8, 8); // Set Displaying Space

	glMatrixMode(GL_MODELVIEW_STACK_DEPTH); // Set Modeling Coordinate System

	double angle = (angleValue * 3.141592) / 180;
	double point1[3] = { basePoint1[0] * (cos(angle)) + basePoint1[2] * (-sin(angle)), basePoint1[1], basePoint1[0] * (sin(angle)) + basePoint1[2] * (cos(angle)) };
	double point2[3] = { basePoint2[0] * (cos(angle)) + basePoint2[2] * (-sin(angle)), basePoint2[1], basePoint2[0] * (sin(angle)) + basePoint2[2] * (cos(angle)) };
	double point3[3] = { basePoint3[0] * (cos(angle)) + basePoint3[2] * (-sin(angle)), basePoint3[1], basePoint3[0] * (sin(angle)) + basePoint3[2] * (cos(angle)) };
	double point4[3] = { basePoint4[0] * (cos(angle)) + basePoint4[2] * (-sin(angle)), basePoint4[1], basePoint4[0] * (sin(angle)) + basePoint4[2] * (cos(angle)) }; // Point Rotate
	
	glMatrixMode(GL_MODELVIEW); // Set Modeling Coordinate System

	glBegin(GL_TRIANGLES); // Tetrahedron Draw
		glColor3f(1, 0, 0);
		glVertex3f(point1[0], point1[1], point1[2]);		
		glVertex3f(point4[0], point4[1], point4[2]);
		glColor3f(0.45f, 0, 0);	
		glVertex3f(point3[0], point3[1], point3[2]);

		glColor3f(0, 1, 0);
		glVertex3f(point1[0], point1[1], point1[2]);		
		glVertex3f(point4[0], point4[1], point4[2]); 
		glColor3f(0, 0.45f, 0);
		glVertex3f(point2[0], point2[1], point2[2]);

		glColor3f(0, 0, 1);
		glVertex3f(point1[0], point1[1], point1[2]);
		glColor3f(0, 0, 0.45f);
		glVertex3f(point2[0], point2[1], point2[2]);
		glVertex3f(point3[0], point3[1], point3[2]);

		glColor3f(0.3f, 0.3f, 0);
		glVertex3f(point2[0], point2[1], point2[2]);		
		glVertex3f(point3[0], point3[1], point3[2]);
		glColor3f(1, 1, 0);
		glVertex3f(point4[0], point4[1], point4[2]);

	glEnd();
	glutSwapBuffers(); // Buffer Swap
}

void DoTimer(int value) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Dept Buffer Clear(Dept space is not Drawing)
	angleValue++;
	if (angleValue == 360) angleValue = 0; // Angle Change
	glutPostRedisplay(); // Redisplaying
	glutTimerFunc(1, DoTimer, 1); // Repeat
}

void reShape(int w, int h){
	glViewport(0, 0, w, h); // Change Viewport
	width = w;
	height = h;
}