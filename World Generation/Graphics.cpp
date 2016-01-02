#include "Graphics.h"


namespace Display 
{
	namespace
	{
		void error_callback(int error, const char* description)
		{
			fputs(description, stderr);
		}
	}

	void Graphics::sleep(double ms)
	{
		double st = clock();
		if (ms <= 0)
			ms = 10;
		while (clock() < (st + ms));
	}

	void Graphics::initCore()
	{
		glfwInit();
		glfwSetErrorCallback(error_callback);

		glfwWindowHint(GLFW_RESIZABLE, 0);
		window = glfwCreateWindow(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "Window", NULL, NULL);

		if (!window)
		{
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glfwMakeContextCurrent(window);

		glOrtho(Display::ortho_left, Display::ortho_right, Display::ortho_bottom, Display::ortho_top, 0, 1);

		glewExperimental = GL_TRUE;
		glewInit();

	}

	void Graphics::initShaders()
	{
		//Basic shader

		// Create and compile the vertex shader
		vertexShaderBasic = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderBasic, 1, &vertexSourceBasic, NULL);
		glCompileShader(vertexShaderBasic);

		// Create and compile the fragment shader
		fragmentShaderBasic = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderBasic, 1, &fragmentSourceBasic, NULL);
		glCompileShader(fragmentShaderBasic);

		shaderProgramBasic = glCreateProgram();
		glAttachShader(shaderProgramBasic, vertexShaderBasic);
		glAttachShader(shaderProgramBasic, fragmentShaderBasic);
		glBindFragDataLocation(shaderProgramBasic, 0, "outColor");
		glLinkProgram(shaderProgramBasic);
		glUseProgram(shaderProgramBasic);

		MatrixID = glGetUniformLocation(shaderProgramBasic, "MVP");

	}

	void Graphics::startDrawing(GLenum mode)
	{
		if (DRAWING)
			std::cout << "Drawing already in progress. " << std::endl;
		else
		{
			DRAWING = true;
			temp = VertexOb(mode);
		}
	}

	void Graphics::finishDrawing()
	{
		if (!DRAWING)
			std::cout << "Drawing was not in progress. " << std::endl;
		else
		{
			DRAWING = false;

			if (temp.primitive == GL_LINES)
			{
				for each (float flo in temp.vertices)
					lines.push_back(flo);

				std::cout << " " << GL_LINES << " " << temp.primitive << " " << temp.vertices.size() << std::endl;
			}
		}
	}

	void Graphics::drawLine(float x1, float y1, float x2, float y2)
	{
		if (DRAWING && temp.primitive == (GL_LINE || GL_LINES))
		{
			if (temp.primitive == GL_LINE && temp.vertices.size() > 1)
				temp.primitive = GL_LINES;

			temp.vertices.push_back(x1);
			temp.vertices.push_back(y1);
			temp.vertices.push_back(x2);
			temp.vertices.push_back(y2);
		}
	}

	void Graphics::initDrawingVBOs()
	{

		if (lines.size() > 0)
		{
			glGenBuffers(1, &DRAWING_LINES);
			glBindBuffer(GL_ARRAY_BUFFER, DRAWING_LINES);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)* lines.size(), &lines[0], GL_STATIC_DRAW);
			GLint posAttrib = glGetAttribLocation(shaderProgramBasic, "position");
			glEnableVertexAttribArray(posAttrib);
			glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}
	}

	void Graphics::render()
	{
		glLineWidth(10);

		startDrawing(GL_LINES);
			drawLine(35.0f, 30.5f, 30.5f, -35.5f);
			drawLine(-30.0f, -30.5f, -30.5f, 30.5f);
		finishDrawing();

		initDrawingVBOs();

		modelMatrix = glm::mat4(1.0f);
		cameraMatrix = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		orthoMatrix = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f);

		glm::mat4 MVPmatrix;

		while (!glfwWindowShouldClose(window))
		{
			//MVP Stuff

			MVPmatrix = orthoMatrix * cameraMatrix * modelMatrix;
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVPmatrix[0][0]);

			// Clear the screen to black
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Draw pre-defined static(mostly) primitives
			if (lines.size() != 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, DRAWING_LINES);
				glDrawArrays(GL_LINES, 0, 4);
			}

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glDrawArrays(GL_LINES,0, 4);

			// Swap buffers
			glfwPollEvents();
			glfwSwapBuffers(window); // Switch buffers (double buffering)
			sleep(1.0);
		}
	}

	Graphics::Graphics()
	{
		initCore();

		glGenVertexArrays(1, &vao2);
		glBindVertexArray(vao2);

		initShaders();

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Display::hardcode3), Display::hardcode3, GL_STATIC_DRAW);

		GLint posAttrib = glGetAttribLocation(shaderProgramBasic, "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

		render();
	}

	Graphics::~Graphics()
	{
		//Update after integration

		glDeleteProgram(shaderProgram);
		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteProgram(shaderProgramBasic);
		glDeleteShader(fragmentShaderBasic);
		glDeleteShader(vertexShaderBasic);

		glDeleteVertexArrays(1, &vao);
		glDeleteVertexArrays(1, &vao2);
	}
}

/*
On VAO's and VBO's:

A VAO keeps track of the VBO's associated with it, and how to interpret vertex data passed into
the pipeline. A VAO may simply take in positional data (only x and y coordinates at
that), and nothing more. Another might take in positional data (x, y, z), UV values, color
values, etc. IN ADDITION, two similar VAO's might specify different approaches in regards
to processing vertex data. There may be multiple arrays, one for each data group (positional vs
UV's), varying placement order for the data groups (position/UV/color vs position/color/UV), etc.

Use multiple when vertex data semantics vary.

The VBO(s) maintain the actual vertex data. The data can stored in several ways. One approach is 
to seperate each data group into its own array. Another is to interleave the attributes.
	Ex:
		data groups: position, color
		
		interleaved -> xyzrgba xyzrgba xyzrgba xyzrgba
		arrays -> xyzxyzxyzxyz rgbargbargbargba
A VBO can be distinguished from another by its redraw frequency and purpose. Generally, objects that
are displayed on a scene together should be grouped into the same VBO.

It is possible/acceptable to have one VAO/VBO per object drawn. There is no heavy penalty for having
multiple afterall. However, the increased function calls and the process of (re)binding is not so simple,
triggering opengl to complete extra consistency/misc calls each time. For simple applications, the increased
overhead is of no issue. For a more complicated application, the increased overhead adds up quickly.

Final note, need to rebind respective vbo/ebo's when switching to another VAO

*/

int main(int argc, char** argv)
{
	Display::Graphics a = Display::Graphics();
}
