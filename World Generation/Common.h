#ifndef COMMON_H
#define COMMON_H

#include "Point.h"
#include "Constants.h";
#include "TileInfo.h"
#include <chrono>

//General
extern int seed;



//Map

namespace Map
{
	extern TileInfo *** map;


}

//Window
namespace Display
{

	extern Point center;
	extern short generation_range; // Range of in which tiles/zones/etc are generated/loaded
	extern short vision_range; //Range of visible tiles/.../...
	extern float zoom; // Determines what portion of the map the camera will fit in the window


	extern int ortho_left;	   
	extern int ortho_right;
	extern int ortho_top;
	extern int ortho_bottom;



}



//Utility Functions (make seperate file if this becomes to bulky)

namespace Util
{
	
	static float lerp(float x, float y, float r)
	{
		return (x * (1 - r) + y * (r));
	}

	static void screenToOrtho(double &x, double &y)
	{


		double x2 = x;
		double y2 = y;

		int orthoHeight = Display::ortho_top + ((Display::ortho_bottom > 0) ? Display::ortho_bottom : -1 * Display::ortho_bottom);
		int orthoWidth = Display::ortho_right + ((Display::ortho_left > 0) ? Display::ortho_left : -1 * Display::ortho_left);

		double widthRatio = Constants::SCREEN_WIDTH / (double)(orthoWidth);
		double heightRatio = Constants::SCREEN_HEIGHT / (double)(orthoHeight);

		x = (x - Constants::SCREEN_WIDTH / 2) / widthRatio;
		//x *= -1;
		y = (y - Constants::SCREEN_HEIGHT / 2) / heightRatio;
		y *= -1;
	}

	static void orthoToScreen(double &x, double &y)
	{


		double x2 = x;
		double y2 = y;

		int orthoHeight = Display::ortho_top + ((Display::ortho_bottom > 0) ? Display::ortho_bottom : -1 * Display::ortho_bottom);
		int orthoWidth = Display::ortho_right + ((Display::ortho_left > 0) ? Display::ortho_left : -1 * Display::ortho_left);

		double widthRatio = Constants::SCREEN_WIDTH / (double)(orthoWidth);
		double heightRatio = Constants::SCREEN_HEIGHT / (double)(orthoHeight);

		x = x * widthRatio + Constants::SCREEN_WIDTH / 2;
		//x *= -1;
		y = y * heightRatio + Constants::SCREEN_HEIGHT / 2;
		y *= -1;
	}
}

#endif // !COMMON_H
