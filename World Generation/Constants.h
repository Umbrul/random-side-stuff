#ifndef CONSTANTS_H
#define CONSTANTS_H


namespace Constants
{

	//Map
	const int ELEVATION_MIN = -5;
	const int ELEVATION_MAX = 5;

	const int MOISTURE_MIN = -3;
	const int MOISTURE_MAX = 3;

	const int TEMP_MIN = -2;
	const int TEMP_MAX = 2;


	//Do not use small numbers (obviously). Max possible length/width is signed int max.

	//Generation
	const int MAP_LENGTH = 30;
	const int MAP_WIDTH = 30;
	const int MAP_HEIGHT = 10;
	const float MID_LENGTH = MAP_LENGTH / 2.0 + 0.5;
	const float MID_WIDTH = MAP_WIDTH / 2.0 + 0.5;
	const float MID_HEIGHT = MAP_HEIGHT / 2.0 + 0.5;

	const int CHUNK_LENGTH = 10;
	const int CHUNK_WIDTH = 10;
	const int CHUNK_HEIGHT = 10;


	//Window 

	const int SCREEN_WIDTH = 700;	   // width of screen window in pixels
	const int SCREEN_HEIGHT = 900;	   // height of screen window in pixels
	const int GRID_WIDTH = 700;			// width of grid in pixels
	const int GRID_HEIGHT = 700;	   // height of grid in pixels

	

}


#endif