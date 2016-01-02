#ifndef UITEXT_H	
#define UITEXT_H	

#include <ft2build.h>
#include <string>
#include "UIElement.h"


namespace Display
{
	namespace Text
	{
		class UIText : public UIElement
		{

		public:
			void renderText(std::string text, int x, int y);
		private:
			int size = 12;

		};

	}
}
#endif