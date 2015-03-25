#include "Biome.h"



namespace Generation
{


	short Biome::Affinity(Biome biome, short modifier = 0, bool useFactor = true, bool useBiome = true)
	{
		/* 
		Total determines the strictness of picking the biome. High values force similar biomes, low values 
		allow dissimilar biomes a chance to appear (if using a factor based approach).
		*/

		short total = modifier;

		if (useFactor)
			total += factorAffinity(biome);

		if (useBiome)
			total += biomeAffinity(biome.Type);

		return (total > 0) ? total : 0;

	}

	short Biome::factorAffinity(Biome otherBiome)
	{
		// Adjust total to determine rejection threshold. Higher values means more dissimiliar biomes (desert -> taiga).
		short total = 0;

		if (otherBiome.moisture == moisture)
			total += 5;
		else if (otherBiome.moisture > moisture)
		{
			if (otherBiome.moisture - moisture <= 1)
			{
				total += 1;
			}
			else if (otherBiome.moisture - moisture <= 3)
			{
				total += 0;
			}
			else if (otherBiome.moisture - moisture <= 5)
			{
				total -= 1;
			}
			else if (otherBiome.moisture - moisture <= 7)
			{
				total -= 5;
			}
			else if (otherBiome.moisture - moisture <= 10)
			{
				total -= 10;
			}
		}
		else if (otherBiome.moisture < moisture)
		{
			if (moisture - otherBiome.moisture <= 1)
			{
				total += 1;
			}
			else if (moisture - otherBiome.moisture <= 3)
			{
				total += 0;
			}
			else if (moisture - otherBiome.moisture <= 5)
			{
				total -= 1;
			}
			else if (moisture - otherBiome.moisture <= 7)
			{
				total -= 5;
			}
			else if (moisture - otherBiome.moisture <= 10)
			{
				total -= 10;
			}
		}

		if (otherBiome.temperature == temperature)
			total += 5;
		else if (otherBiome.temperature > temperature)
		{
			if (otherBiome.temperature - temperature <= 1)
			{
				total += 1;
			}
			else if (otherBiome.temperature - temperature <= 3)
			{
				total += 0;
			}
			else if (otherBiome.temperature - temperature <= 5)
			{
				total -= 1;
			}
			else if (otherBiome.temperature - temperature <= 7)
			{
				total -= 5;
			}
			else if (otherBiome.temperature - temperature <= 10)
			{
				total -= 10;
			}
		}
		else if (otherBiome.temperature < temperature)
		{
			if (temperature - otherBiome.temperature <= 1)
			{
				total += 1;
			}
			else if (temperature - otherBiome.temperature <= 3)
			{
				total += 0;
			}
			else if (temperature - otherBiome.temperature <= 5)
			{
				total -= 1;
			}
			else if (temperature - otherBiome.temperature <= 7)
			{
				total -= 5;
			}
			else if (temperature - otherBiome.temperature <= 10)
			{
				total -= 10;
			}
		}

		return total;

	}

	short Biome::biomeAffinity(BiomeType biome)
	{
		if (Type == FOREST)
		{
			switch (biome)
			{
			case GRASSLAND:;
			case JUNGLE:;
			case TAIGA:
				return 5;

			case WETLAND:
				return 0;


			case FOREST:;
			case OCEAN:;
			case TUNDRA:
				return -5;

			default:
				return -10;
			}
		}
		else if (Type == TAIGA)
		{
			switch (biome)
			{
			case GRASSLAND:;
			case FOREST:
				return 5;

			case TUNDRA:
			case WETLAND:
				return 0;

			case TAIGA:;
			case OCEAN:;
				return -5;

			default:
				return -10;
			}
		}
		else if (Type == JUNGLE)
		{
			switch (biome)
			{
			case GRASSLAND:;
			case FOREST:
			case WETLAND:
				return 5;

			case OCEAN:;
			case TUNDRA:;
			case JUNGLE:;
			case DESERT:
				return -5;

			default:
				return -10;
			}
		}
		else if (Type == WASTES)
		{
			switch (biome)
			{
			case DESERT:
				return 5;

			case TUNDRA:;
			case WASTES:;
			case GRASSLAND:;
				return -5;

			default:
				return -10;
			}
		}
		else if (Type == JUNGLE)
		{
			switch (biome)
			{
			case GRASSLAND:;
			case FOREST:;
			case WETLAND:
				return 5;

			case OCEAN:;
			case TUNDRA:;
			case JUNGLE:
				return -5;

			default:
				return -10;
			}
		}
		else if (Type == DESERT)
		{
			switch (biome)
			{
			case GRASSLAND:
				return 5;

			case TUNDRA:;
			case FOREST:
				return 0;

			case OCEAN:;
			case DESERT:;
			case WASTES:
				return -5;

			default:
				return -10;
			}
		}
		else if (Type == TUNDRA)
		{
			switch (biome)
			{
			case GRASSLAND:
				return 5;

			case DESERT:;
			case WETLAND:
			case FOREST:
				return 0;

			case OCEAN:;
			case TUNDRA:
				return -5;

			default:
				return -10;
			}
		}
		else if (Type == TUNDRA)
		{
			switch (biome)
			{
			case GRASSLAND:
				return 5;

			case DESERT:;
			case FOREST:
				return 0;

			case OCEAN:;
			case TUNDRA:
				return -5;

			default:
				return -10;
			}
		}
		else if (Type == GRASSLAND)
		{
			switch (biome)
			{
			
			case OCEAN:;
			case GRASSLAND:
				return -5;

			case WASTES:;
				return -10;

			default:
				return 0;
			}
		}
		else if (Type == WETLAND)
		{
			switch (biome)
			{

			case OCEAN:;
			case GRASSLAND:
				return 5;
			
			case FOREST:;
			case TAIGA:;
			case JUNGLE:;
				return 0;
			default:
				return -10;
			}
		}
		else if (Type == OCEAN)
		{
			switch (biome)
			{

			case OCEAN:
				return 5;

			case FOREST:;
			case TAIGA:;
			case JUNGLE:;
			case WETLAND:;
			case GRASSLAND:;
				return 0;
			default:
				return -10;
			}
		}
	}
}
