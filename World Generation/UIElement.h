#ifndef UIELEMENT_H	
#define UIELEMENT_H	

#include <GLFW\glfw3.h>
#include <list>
#include "Common.h"

namespace Display
{
	class UIElement
	{

	protected:
		bool initiated = true;

		bool border = true;
		int border_thickness = 1; //Seperate into seperate function later, when revisiting gui stuffs

		float absoluteX, absoluteY; //Central point of panel. Used in draw function
		float xOrthoFactor, yOrthoFactor;
		int height, width;


		void render()
		{
			if (initiated)
			{
				if (border)
				{
					glLineWidth(border_thickness);
					glBegin(GL_LINES);
					glVertex2UI(height / 2, -width / 2);
					glVertex2UI(height / 2, width / 2);

					glVertex2UI(height / 2, -width / 2);
					glVertex2UI(-height / 2, -width / 2);

					glVertex2UI(-height / 2, -width / 2);
					glVertex2UI(-height / 2, width / 2);

					glVertex2UI(-height / 2, width / 2);
					glVertex2UI(height / 2, width / 2);
					glEnd();
					glLineWidth(1);// Set line size and point size defaults later, or just reset to 1 each time, or ALWAYS set size prior to use
				}

				draw();
			}
		}
		virtual void draw() = 0;

	public:

		void setPosition(float x, float y)
		{
			this->absoluteX = x;
			this->absoluteY = y;
		}

		void setHeight(int newHeight)
		{
			height = newHeight;
		}

		void setWidth(int newWidth)
		{
			width = newWidth;
		}

		void enableBorder()
		{
			border = true;
		}

		void disableBorder()
		{
			border = false;
		}

		void update()
		{
			refresh();
			render();

		}

		void glVertex2UI(float x, float y) //Displays vertex in appropriate in the panel area
		{
			float posX = (x < 0) ? x*-1 : x;
			float posY = (y < 0) ? y*-1 : y;
			if (posX <= width / 2 && posY <= height / 2)
				glVertex2f((x * xOrthoFactor) + absoluteX, (y * yOrthoFactor) + absoluteY);
		}

		void Initiate(int height, int width, float x, float y)
		{
			this->height = height;
			this->width = width;
			this->absoluteX = x;
			this->absoluteY = y;
			initiated = true;
			refresh();
		}

		virtual void refresh() = 0;//Recalculate key values when key settings (zoom, etc) are modified.
	};
}

#endif