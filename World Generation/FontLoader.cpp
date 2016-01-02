#include "FontLoader.h"
#include <iostream>

namespace Display
{
	namespace Text
	{
		
		
		void FontLoader::Initiate(int size = 20)
		{
			glewInit();
			

			if (FT_Init_FreeType(&ft))
			{
				fprintf(stderr, "Could not init freetype library\n");
				
			}

			if (FT_New_Face(ft, "Marlboro.ttf", 0, &face)) {
				fprintf(stderr, "Could not open font\n");
				
			}
			FT_Set_Pixel_Sizes(face, 0, size);

			if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
				fprintf(stderr, "Could not load character 'X'\n");
				exit(1);
			}

			slot = face->glyph;

			FT_Glyph_Metrics metrics = slot->metrics;

			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				slot->bitmap.width,
				slot->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				slot->bitmap.buffer
				);
			
		}
	}
}