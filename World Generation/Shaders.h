#ifndef SHADERS_H
#define SHADERS_H

#include <GL\glew.h>


namespace Display
{

	//This approach, for color, uses uniforms. Basically, uniforms -> globals and you can modify them each cycle
	//const GLchar* vertexSource =
	//	"#version 150 core\n"
	//	"in vec2 position;"
	//	"void main() {"
	//	"   gl_Position = vec4(position, 0.0, 1.0);"
	//	"}";
	//const GLchar* fragmentSource =
	//	"#version 150 core\n"
	//	"uniform vec3 triangleColor;"
	//	"out vec4 outColor;"
	//	"void main() {"
	//	"   outColor = vec4(triangleColor, 1.0);"
	//	"}";

	//This approach specifies color from the start, associating a color with each vertex.
	const GLchar* vertexSource =
		"#version 150 core\n"
		"in vec2 position;"
		"in vec3 color;"
		"out vec3 Color;"
		"uniform mat4 MVP;"
		"void main() {"
		"	Color = color;"
		"   gl_Position = MVP * vec4(position, 0.0, 1.0);"
		//"   gl_Position = vec4(position[0],position[1]*-1, 0.0, 1.0);" flips across x-axis
		"}";
	const GLchar* fragmentSource =
		"#version 150 core\n"
		"in vec3 Color;"
		"out vec4 outColor;"
		"void main() {"

		//"   outColor = vec4(1 - Color, 1.0);"
		"   outColor = vec4(Color, 1.0);"
		"}";


	const GLchar* vertexSourceBasic =
		"#version 150 core\n"
		"in vec2 position;"
		"uniform mat4 MVP;"
		"void main() {"
		"   gl_Position = MVP * vec4(position, 0.0, 1.0);"
		//"   gl_Position = vec4(position[0],position[1]*-1, 0.0, 1.0);" flips across x-axis
		"}";
	const GLchar* fragmentSourceBasic =
		"#version 150 core\n"
		"out vec4 outColor;"
		"void main() {"

		//"   outColor = vec4(1 - Color, 1.0);"
		"    outColor = vec4(1.0, 1.0, 1.0, 1.0);"
		"}";
}


#endif