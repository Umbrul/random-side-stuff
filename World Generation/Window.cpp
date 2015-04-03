#include "Window.h"

using namespace Generation;

namespace
{
	Display::Grid grid;
	Generate test;
}


//static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
//{
//}


static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	

	

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		clicked = true;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		clicked = false;
	}
		
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		grid.modifyXOffset(-2);
	}
	else if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{

		grid.modifyXOffset(2);
	}

	if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		
		grid.modifyYOffset(-2);
	}
	else if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{

		grid.modifyYOffset(2);
	}
}

void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}


void _sleep(double ms)
{
	double st = clock();
	if (ms <= 0)
		ms = 10;
	while (clock() < (st + ms));
}


void update()
{

}

void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Colour to clear the scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// TODO: Draw stuff here!    

	if (clicked)
	{
		glfwGetCursorPos(window, &xPos, &yPos);
		double x = xPos;
		double y = yPos;
		grid.screenToGrid(x, y);

		std::cout << "X pos: " << x << " Y pos: " << y << std::endl;
		grid.selectPoint(x, y);
		grid.selectTileAtPoint(x, y);
	}
	grid.render();

}

//Seperate generation into generation, world, and display. World contains the generated info, display works with vision to determine what is visibles. Display should also use good and proper opengl.
int main(int argc, char** argv)
{
	
	glfwInit();


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	test = Generate();
	grid = Display::Grid();

	test.perlin_sprawl();
	
	std::cout << std::endl << std::endl << "Current Seed: " << seed << std::endl;

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_RESIZABLE, 0);
	window = glfwCreateWindow(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "Window", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	glfwMakeContextCurrent(window);
	//glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);
	glOrtho(Display::ortho_left, Display::ortho_right, Display::ortho_bottom, Display::ortho_top, 0, 1);

	while (!glfwWindowShouldClose(window))
	{

		update();
		render();
		glfwSwapBuffers(window); // Switch buffers (double buffering)
		glfwPollEvents();
		_sleep(10.0);
	}

	char* temp = (grid.isVisible(0, 0)) ? "true" : "false";
	TileInfo tileA = grid.getTileAtPoint(0, 0);
	std::cout <<"Is point 0, 0 visible? " << temp << std::endl;
	std::cout << "Tile x: " << tileA.x <<" y: "<<tileA.y<<std::endl;
	temp = (grid.isVisible(50, 50)) ? "true" : "false";
	TileInfo tileB = grid.getTileAtPoint(50, 50);
	std::cout << "Is point 50, 50 visible? " << temp << std::endl;
	std::cout << "Tile x: " << tileB.x << " y: " << tileB.y << std::endl;
	temp = (grid.isVisible(120, 50)) ? "true" : "false";
	TileInfo tileC = grid.getTileAtPoint(120, 50);
	std::cout << "Is point 120, 50 visible? " << temp << std::endl;
	std::cout << "Tile x: " << tileC.x << " y: " << tileC.y << std::endl;
	//test.terrain_picker_test();
	
	/*
	int *a = 0;
	int *b = 0;
	int c = 7;
	int d = 0;

	b = &c;
	a = &d;

	std::cout << *b << std::endl;

	*a = *b;

	*a = 2;

	std::cout << *b << std::endl;

	*b = *a;

	*a = 2;

	std::cout << *b << std::endl;

	*a = 4;

	std::cout << *b << std::endl;

	b = a;

	std::cout << *b << std::endl;

	*a = 10;

	std::cout << *b << std::endl;

	7
	7
	2
	2
	4
	10
	*/
	return 0;
}