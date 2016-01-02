#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "FontLoader.h"
#include "Constants.h"
#include "Common.h"
#include <iostream>
#include <time.h> 
#include <vector>

#include "Shaders.h"
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Display{


	float hardcode[]{
		//triangles
		0, 0, 1.5f, 0.0f, 0.0f,
			1.5, 1.5, 0.0f, 1.0f, 0.0f,
			0, 1.5, 0.0f, 0.0f, 1.0f,
			0, -1.5, 0.0f, 1.0f, 1.0f,
			1.5, -1.5, 1.0f, 1.0f, 1.0f
	};
	float hardcode3[]{
		10.0f, 10.5f,
		10.5f, -10.5f,
		-10.5f, -10.5f,
		-10.5f, 20.5f
	};
	GLuint elementsOne[]{
		0, 3, 4
	};
	GLuint elementsTwo[]{
		0, 1, 2
	};

	class Graphics
	{
		private:
			GLFWwindow* window;

			GLuint vertexShader;
			GLuint fragmentShader;
			GLuint shaderProgram;

			GLuint vertexShaderBasic;
			GLuint fragmentShaderBasic;
			GLuint shaderProgramBasic;

			GLuint MatrixID;

			glm::mat4 modelMatrix;
			glm::mat4 cameraMatrix;
			glm::mat4 orthoMatrix;

			GLuint eboOne, eboTwo;

			void initCore();
			void initShaders();
			void initDrawingVBOs();

			void render();

			void sleep(double ms);

		public:

			Graphics();
			~Graphics();
			GLuint DRAWING_LINES;
			GLuint DRAWING_TRIANGLES;

			/*
				Call startDrawing before calling any of the custom draw functions. It will make it so that all changes
				made will be stored in a single VertexOb. After calling the draw functions, complete the process by calling
				finishDrawing. It will send the VertexOb data to structure which maintains all VertexOb.

				The vector map will iterate through stored references and bind/draw each buffer defined.

				Process can be refined in the future, by seperating maps based off of redraw frequency. Some models/objects
				are modified more than others.

				Another refinement would be merging VertexOb's who share key details (primitive, redraw frequency, etc.). Can
				be done after set-up.
				*/
			bool DRAWING = false;

			//Draw structures
			struct VertexOb
			{
				VertexOb(std::vector<float> vertices, GLenum primitive){ this->vertices = vertices; this->primitive = primitive; }
				VertexOb(GLenum primitive){ this->primitive = primitive; }
				VertexOb(){}

				std::vector<float> vertices = std::vector<float>();
				GLenum primitive;

			};
			VertexOb temp;

			std::vector<float> lines = std::vector<float>();
			std::vector<float> triangles = std::vector<float>();

			//Draw Functions
			void startDrawing(GLenum mode);
			void finishDrawing();

			void drawLine(float x1, float y1, float x2, float y2);
			void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
	};
}


GLuint vbo, vbo2, test;
GLuint vao, vao2;

#endif