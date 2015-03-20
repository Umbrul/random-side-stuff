#ifndef TERRAIN_H
#define TERRAIN_H

namespace Generation
{
	class TileInfo{
	public:
		//Reference id | Used to simplify other processes. NOT CONSTANT
		int reference_id;

		//Info pertaining to tile
		bool land;
		int x, y;
		short elevation; //between -5 and 5. 0 is ground level.
		char terrain;
		short zone_id;
		TileInfo(){ terrain = 'O'; zone_id = -1; elevation = 0; }
		~TileInfo(){}

	};
}
#endif