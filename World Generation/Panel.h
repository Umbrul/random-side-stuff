#ifndef PANEL_H
#define PANEL_H

#include <GLFW\glfw3.h>
#include <list>
#include "Common.h"
#include <iostream>



namespace Display
{
	class Panel
	{

	protected:
		std::list<Panel> children;
		int children_total;

		bool border = true;
		int border_thickness = 1; //Seperate into seperate function later, when revisiting gui stuffs

		float absoluteX, absoluteY; //Central point of panel. Used in draw function
		float xOrthoFactor, yOrthoFactor; 
		int height, width;
		bool initiated = true;

		void glVertex2Panel(float x, float y) //Displays vertex in appropriate in the panel area
		{
			float posX = (x < 0) ? x*-1 : x;
			float posY = (y < 0) ? y*-1 : y;
			if (posX <= width / 2 && posY <= height / 2)
				glVertex2f((x + absoluteX)* xOrthoFactor, (y + absoluteY) * yOrthoFactor);
		}

		virtual void refresh()//Recalculate key values when key settings (zoom, etc) are modified.
		{

		}
		virtual void draw()
		{

		}





	public:
		
		void update()
		{
			if (children.size() != 0)
			{
				std::list<Panel>::iterator it;
				std::list<Panel>::iterator end;
				for (it = children.begin(), end = children.end(); it != end; ++it)
				{
					it->update();
				}
			}

			/*
			Maps window coords -> ortho coords, and then restricts the range n,
			where n is the portion of space that the window takes up (relative to the entire window).
			*/

			int orthoHeight = ortho_top + ((ortho_bottom > 0) ? ortho_bottom : -1 * ortho_bottom);
			int orthoWidth = ortho_right + ((ortho_left > 0) ? ortho_left : -1 * ortho_left);
			
			/*
			xOrthoFactor = (orthoWidth / (float)width)   * ((width) / (float)Constants::SCREEN_WIDTH);
			yOrthoFactor = (orthoHeight / (float)height)  * ((height) / (float)Constants::SCREEN_HEIGHT);
			*/

			xOrthoFactor = (orthoWidth / (float)Constants::SCREEN_WIDTH);
			yOrthoFactor = (orthoHeight / (float)Constants::SCREEN_HEIGHT);
			refresh();
		}

		bool withinPanel(double x, double y)
		{
			if ((absoluteX + width / 2.0 >= x && absoluteX - width / 2.0 <= x) && (absoluteY + height / 2.0 >= y && absoluteY - height / 2.0 <= y))
			{
				return true;
			}
			return false;
		}

		bool screenToPanel(double &x, double &y)
		{
			x = (x - Constants::SCREEN_WIDTH / 2);
			//x *= -1;
			y = (y - Constants::SCREEN_HEIGHT / 2);
			y *= -1;

			if (withinPanel(x, y))
			{
				x -= absoluteX;
				y -= absoluteY;
				std::cout << "uf x: " << x << " y: " << y << std::endl;
			
				return true;
			}
			return false;
		}

		void enableBorder()
		{
			border = true;
		}

		void disableBorder()
		{
			border = false;
		}

		void setHeight(int newHeight)
		{
			height = newHeight;
		}

		void setWidth(int newWidth)
		{
			width = newWidth;
		}

		void render()
		{
			if (initiated)
			{
				if (border)
				{
					
					glLineWidth(border_thickness);
					glBegin(GL_LINES);
						glVertex2Panel(height / 2, -width / 2);
						glVertex2Panel(height / 2, width / 2);
						
						glVertex2Panel(height / 2, -width / 2);
						glVertex2Panel(-height / 2, -width / 2);

						glVertex2Panel(-height / 2, -width / 2);
						glVertex2Panel(-height / 2, width / 2);

						glVertex2Panel(-height / 2, width / 2);
						glVertex2Panel(height / 2, width / 2);
					glEnd();
					glLineWidth(1);// Set line size and point size defaults later, or just reset to 1 each time, or ALWAYS set size prior to use
				}
				draw();
			}
		}
		void initiate(int height, int width, float x, float y)
		{
			this->height = height;
			this->width = width;
			this->absoluteX = x;
			this->absoluteY = y;
			initiated = true;
			update();
		}

		void addChild(Panel child)
		{
			children.push_back(child);

			children_total++;
		}

		void removeChild(Panel child)
		{

			std::list<Panel>::iterator it;
			std::list<Panel>::iterator end;
			for (it = children.begin(), end = children.end(); it != end; ++it)
			{
				if (&child == &*it)
				{
					children.erase(it);
				}
			}
			children_total--;
		}


	};
}



#endif