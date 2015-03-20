#include <math.h>
#include <vector>
#include "Generation.h"
#include <iostream>
#include <time.h>  

namespace Generation

{

	void Generate::HeightToMap()
	{
		Map = new TileInfo**[2 * chunk_height + 1];
		for (int i = 0; i <= 2 *chunk_height; i++)
		{
			Map[i] = new TileInfo*[chunk_length];
			for (int j = 0; j < chunk_length; j++)
			{

				Map[i][j] = new TileInfo[chunk_width];

		
				for (int k = 0; k < chunk_width; k++)
				{
					Map[i][j][k] = TileInfo();
					Map[i][j][k].zone_id = 0;
					Map[i][j][k].x = k;
					Map[i][j][k].y = j;
					Map[i][j][k].elevation = i-(chunk_height);
					Map[i][j][k].terrain = (HeightMap[j][k].elevation > Map[i][j][k].elevation) ? 'U' : ((HeightMap[j][k].elevation == Map[i][j][k].elevation) ? 'O': ' ') ;
				
				}

			}
		}
	}

	void Generate::sprawl()
	{

		Generation::Sprawl func = Generation::Sprawl(50, 50, HeightMap, Zones);

	}

	void Generate::perlin_sprawl()
	{
		HeightMap = new TileInfo*[chunk_length];
		//Step 1 Height Map
		Generation::Perlin_Sprawl func = Generation::Perlin_Sprawl(chunk_length, chunk_width, chunk_height, HeightMap);
		//Step 2 Height Map -> World Map (layers)
		HeightToMap();
		DisplayLayers();
		//Step 3 Cavern
		//Step 4 Water source + use shortest path algo to create shape. NO uphill (initially). Branching+merging river entities
		func.Print();
	}


	void Generate::DisplayLayers()
	{
		for (int i = 0; i <= 2* chunk_height; ++i)
		{
			std::cout <<"Layer: "<<i-(chunk_height) << std::endl;
			for (int j = 0; j < chunk_length; ++j)
			{
				for (int k = 0; k < chunk_width; ++k)
				{
					std::cout << Map[i][j][k].terrain << " ";
				}

				std::cout << std::endl;
			}

			std::cout << std::endl;
		}
	}

	void Generate::DisplayLayer(int layer)
	{

	}
}