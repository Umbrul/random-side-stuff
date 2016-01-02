#include "Common.h"


//Extern Declarations
int seed = 0;


namespace Map
{

	TileInfo *** map = 0;

}

namespace Display

{
	Point center = Point(0, 0, 0);
	short generation_range = 0;
	short vision_range = 1;
	float zoom = 10;

	int ortho_left = -100;
	int ortho_right = 100;
	int ortho_top = 100;
	int ortho_bottom = -100;

}



