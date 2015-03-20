#ifndef ZONE_H
#define ZONE_H
#include "TileInfo.h"
#include "Biome.h"

namespace Generation
{

	class Zone
	{

	public:

		enum SprawlType { FOCUSED, BALANCED, SPREAD };
		SprawlType type = FOCUSED;

		Biome myBiome;
		Zone* neighborZones;
		int size = 0;
		int zone_id = 0;
		char symbol = 'O';


		Zone(){};
		Zone(int size, char symbol){ this->size = size; this->zone_id = counter++; Area = new TileInfo*[size]; this->symbol = symbol; }

		TileInfo** getTileInfo(){ return Area; }
		void addTileInfo(int index, TileInfo &area)
		{ 
			
			Area[index] =  &area;
			Area[index]->zone_id = zone_id;
		}
	private:
		TileInfo ** Area;
		int counter = 0;

	};
}

#endif 