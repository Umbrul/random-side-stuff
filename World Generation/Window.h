#include "FontLoader.h"
#include "Generation.h"
#include "Grid.h"
#include "Constants.h"
#include "Common.h"
#include <iostream>
#include <glfw3.h>
#include "Vector2.h"


GLFWwindow* window;
double xPos = 0;
double yPos = 0;
bool clicked = false;


static void selectPoint(float x, float y)
{
	//Map::map[0][y + (int)Constants::MAP_LENGTH / 2][x + (int)Constants::MAP_WIDTH / 2];
	glPointSize(20);
	glColor3f(0, 1, 0);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();

	glColor3f(1, 1, 1);
}