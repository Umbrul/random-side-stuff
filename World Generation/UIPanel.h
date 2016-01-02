#ifndef UIPANEL_H
#define UIPANEL_H

#include <iostream>
#include "UIElement.h"


//Strip several parts of this into a more basic component before implementing the next interface element


namespace Display
{
	class UIPanel: public UIElement
	{

	protected:
		std::list<UIElement*> children;
		int children_total;

	public:
		~UIPanel()
		{
			std::list<UIElement*>::iterator it;
			std::list<UIElement*>::iterator end;
			for (end = children.begin(), it = children.end(); it != end; --it)
			{
				children.remove(*it);
			}
		}

		bool withinPanel(double x, double y);
		bool screenToPanel(double &x, double &y);
		void addChild(UIElement* child);
		void removeChild(UIElement* child);
		void update();
		void refresh();
	};
}



#endif