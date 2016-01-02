#ifndef FONTLOADER_H	
#define FONTLOADER_H	


#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include <map>
#include "Vector2.h"
#include "Constants.h"

#include <ft2build.h>
#include FT_FREETYPE_H





namespace Display
{
	namespace Text
	{
	

		class FontLoader
		{

		private:
			FT_Library ft;
			FT_Face face;

			FT_GlyphSlot  slot;
			FT_Matrix     matrix;                 /* transformation matrix */
			FT_Vector     pen;                    /* untransformed origin  */
			FT_Error      error;

			char*         text;

			double        angle;
			int           target_height;
			int           n, num_chars;

			GLint attribute_coord;
			GLint uniform_tex;
			GLint uniform_color;

			void createPixels8(GLuint imgWidth, GLuint imgHeight);
			unsigned char image[Constants::MAP_LENGTH][Constants::MAP_WIDTH];
		public:
			void Initiate(int size);
			void draw_bitmap(FT_Bitmap*  bitmap, FT_Int  x, FT_Int      y);
			void show_image(void);


		};

	}
}
#endif