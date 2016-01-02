#ifndef VERTEXCONTAINER_H
#define VERTEXCONTAINER_H

#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Common.h"

namespace Display
{


	class VertexContainer
	{
		/*
		Each Vertex Container should be used to define an important vertex
		group in a scene. For a 3D environment, each container may correspond to
		characters within the environment. The environment, itself, would also
		be defined using one. 

		ATM, defining the general structure prior to runtime is the proper practice.
		The # of containers, and vertex groups within each container, should remain static.

		Note: Vertex containers without internally defined VBO's will not have a unique
		VBO created.

		Another Note: Define the buffer data after defining the Vertex Container.
		
		*/
		private:
			int vertexOb_total = 0;
			int subcontainer_total = 0;
			GLenum type;
			GLuint vbo;

			VertexObject **vertexObs;
			VertexContainer** subcontainers;
			std::vector<float> internalVertices;


			void generateBufferObject()
			{
				glGenBuffers(1, &vbo);
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glBufferData(GL_ARRAY_BUFFER, sizeof(internalVertices), &internalVertices.front(), GL_STATIC_DRAW);
			}


		public:
			VertexContainer(GLenum type, int children, int vertices, std::vector<float> externalVertices)
			{
				internalVertices = externalVertices;
				subcontainer_total = children;
				vertexOb_total = vertices;

				subcontainers = new VertexContainer*[children];
				vertexObs = new VertexObject*[vertices];

				generateBufferObject();
			}

			VertexContainer(GLenum type, int children, int vertices)
			{
				internalVertices = std::vector<float>();
				subcontainer_total = children;
				vertexOb_total = vertices;

				subcontainers = new VertexContainer*[children];
				vertexObs = new VertexObject*[vertices];

				generateBufferObject();
			}

			VertexContainer(GLenum type, int vertices)
			{
				internalVertices = std::vector<float>();
				subcontainer_total = 0;
				vertexOb_total = vertices;

				vertexObs = new VertexObject*[vertices];

				generateBufferObject();
			}

			~VertexContainer(){}

			void createVertexObject(int id, int index, int amount)
			{
				std::vector<float*> ref = std::vector<float*>();
				for (int i = 0; i < amount; i++)
				{
					ref.push_back(&internalVertices[index + i]);
				}

				vertexObs[id] = new VertexObject(ref);
			}

	};


	class VertexObject
	{
		/*
			Contains vertices referencing a specific sub-zone of the associated vertex
			container. In the environment example, a container corresponds to 
			each character/actor. The vertex objects of an actor container might represent
			regions on a character (torso, arms, etc).
		*/

		std::vector<float*> vertexRef;
		public:
			VertexObject(std::vector<float*> ref)
			{
				vertexRef = ref;
			}
			~VertexObject(){}
	};
}



#endif