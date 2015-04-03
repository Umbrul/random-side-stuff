#ifndef COMMON_H
#define COMMON_H

#include "Point.h"
#include "Constants.h";
#include "TileInfo.h"

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

#endif // !COMMON_H
