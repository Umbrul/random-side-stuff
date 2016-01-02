#include "UIPanel.h"



//Strip several parts of this into a more basic component before implementing the next interface element


namespace Display
{
		bool UIPanel::withinPanel(double x, double y)
		{
			if ((absoluteX + width / 2.0 >= x && absoluteX - width / 2.0 <= x) && (absoluteY + height / 2.0 >= y && absoluteY - height / 2.0 <= y))
			{
				return true;
			}
			return false;
		}

		bool UIPanel::screenToPanel(double &x, double &y)
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


		void UIPanel::addChild(UIElement* child)
		{
			children.push_back(child);

			children_total++;
		}

		void UIPanel::removeChild(UIElement* child)
		{

			std::list<UIElement*>::iterator it;
			std::list<UIElement*>::iterator end;
			for (it = children.begin(), end = children.end(); it != end; ++it)
			{
				if (&child == &*it)
				{
					children.erase(it);
				}
			}
			children_total--;
		}

		void UIPanel::update()
		{
			UIElement::update();
			if (children.size() != 0)
			{
				std::list<UIElement*>::iterator it;
				std::list<UIElement*>::iterator end;
				for (it = children.begin(), end = children.end(); it != end; ++it)
				{
					if (dynamic_cast<UIPanel*>(*it) == NULL)
						(**it).refresh();
					else
						dynamic_cast<UIPanel*>(*it)->update();
				}
			}
		}

		void UIPanel::refresh()
		{
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
		}
	
}