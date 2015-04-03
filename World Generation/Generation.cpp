#include "Generation.h"


namespace Generation

{
	

	void Generate::HeightToMap()
	{
		Map::map = new TileInfo**[2 * Constants::MAP_HEIGHT + 1];
		for (int i = 0; i <= 2 * Constants::MAP_HEIGHT; i++)
		{
			Map::map[i] = new TileInfo*[Constants::MAP_LENGTH];
			for (int j = 0; j < Constants::MAP_LENGTH; j++)
			{

				Map::map[i][j] = new TileInfo[Constants::MAP_WIDTH];

		
				for (int k = 0; k < Constants::MAP_WIDTH; k++)
				{
					Map::map[i][j][k] = TileInfo();
					Map::map[i][j][k].zone_id = 0;
					Map::map[i][j][k].x = k;
					Map::map[i][j][k].y = j;
					Map::map[i][j][k].elevation = i - (Constants::MAP_HEIGHT);
					Map::map[i][j][k].terrain = (HeightMap[j][k].elevation > Map::map[i][j][k].elevation) ? 'U' : ((HeightMap[j][k].elevation == Map::map[i][j][k].elevation) ? 'O' : ' ');
				
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
		HeightMap = new TileInfo*[Constants::MAP_LENGTH];
		//Step 1 Height Map
		Generation::Perlin_Sprawl func = Generation::Perlin_Sprawl(random, Constants::MAP_LENGTH, Constants::MAP_WIDTH, Constants::MAP_HEIGHT, HeightMap);
		//Step 2 Height Map -> World Map (layers)
		HeightToMap();
		//DisplayLayers();
		//Step 3 Cavern
		//Step 4 Water source + use shortest path algo to create shape. NO uphill (initially). Branching+merging river entities
		func.Print();
	}

	void Generate::terrain_picker_test()
	{
		int i;
		Biome temp = Biome(BiomeType::GRASSLAND, 0, 0);
		for (i = 0; i < 100; i++)
		{
			temp = BiomeCreation::deviatiation(temp);
		}
	}


	void Generate::DisplayLayers()
	{
		for (int i = 0; i <= 2 * Constants::MAP_HEIGHT; ++i)
		{
			std::cout << "Layer: " << i - (Constants::MAP_HEIGHT) << std::endl;
			for (int j = 0; j < Constants::MAP_LENGTH; ++j)
			{
				for (int k = 0; k < Constants::MAP_WIDTH; ++k)
				{
					std::cout << Map::map[i][j][k].terrain << " ";
				}

				std::cout << std::endl;
			}

			std::cout << std::endl;
		}
	}

	void Generate::DisplayLayer(int layer)
	{

	}

	int Generate::getElevation(int x, int y)
	{
		
		return Map::map[(int)round(y)][(int)round(x)]->elevation;
	}

	int Generate::getMoisture(int x, int y)
	{
		return Map::map[(int)round(y)][(int)round(x)]->moisture;
	}

	int Generate::getTemperature(int x, int y)
	{
		return Map::map[(int)round(y)][(int)round(x)]->temperature;
	}


}