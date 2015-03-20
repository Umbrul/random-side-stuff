#include "Biome.h"

namespace Generation
{
	class Forest : public Biome
	{


		short biomeAffinity(Biome otherBiome)
		{

			switch (otherBiome.Type)
			{
			case GRASSLAND:;
			case JUNGLE:;
			case TAIGA:
				return 5;

			case COAST:;
			case WETLAND:
				return 0;

			case OCEAN:;
			case TUNDRA:
				return -5;

			case DESERT:;
			case BARREN:;
			case WASTES:;
			default:
				return -10;
			}
		}


	};


}