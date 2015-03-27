#ifndef BiomeTable_H
#define BiomeTable_H

#include <map>
#include <vector>
#include "Biome.h"
#include "Forest.h"

using namespace std;
namespace Generation

{

	const int BIOME_WIDTH = 7;
	const int BIOME_LENGTH = 5;
	//Table containing temperature and moisture range of each biome. Original approach
	static map<BiomeType, vector<int>> ReferencebyRange
	{
	// moisture min | moisture max | temperature min | temperature max
		{ BiomeType::FOREST, { 2, 4, -3, 3 } },
		{ BiomeType::GRASSLAND, { -1, 1, -3, 3 } },
		{ BiomeType::JUNGLE, { 2, 4, 3, 5 } },
		{ BiomeType::DESERT, { -5, -2, -1, 5 } },
		{ BiomeType::TUNDRA, { -4, -2, -5, -2 } },
		{ BiomeType::BARREN, { -5, -5, 0, 5 } },
		{ BiomeType::WASTES, { -5, -5, -5, 0 } },
		{ BiomeType::TAIGA, { 2, 4, -5, -2 } },
		{ BiomeType::SCRUBLAND, { -3, 1, -5, 5 } }


};

	static BiomeType Reference[5][7]
	{
		{ BiomeType::WATER, BiomeType::JUNGLE,	BiomeType::JUNGLE,	BiomeType::SCRUBLAND,	BiomeType::DESERT,		BiomeType::DESERT,	BiomeType::BARREN },
		{ BiomeType::WATER, BiomeType::JUNGLE,	BiomeType::FOREST,	BiomeType::GRASSLAND,	BiomeType::SCRUBLAND,	BiomeType::DESERT,	BiomeType::BARREN },
		{ BiomeType::WATER, BiomeType::FOREST,	BiomeType::FOREST,	BiomeType::GRASSLAND,	BiomeType::GRASSLAND,	BiomeType::DESERT,	BiomeType::DESOLATION },
		{ BiomeType::WATER, BiomeType::TAIGA,	BiomeType::FOREST,	BiomeType::GRASSLAND,	BiomeType::SCRUBLAND,	BiomeType::TUNDRA,	BiomeType::WASTES },
		{ BiomeType::WATER, BiomeType::TAIGA,	BiomeType::TAIGA,	BiomeType::SCRUBLAND,	BiomeType::TUNDRA,		BiomeType::TUNDRA,	BiomeType::WASTES }

	};

	inline char* getName(int id){ return BiomeTypeName[id]; };

	inline vector<BiomeType> getBiomeTypeWithTemperature(short value, bool reference = false)
	{
		vector<BiomeType> temp;
		int it;
		for (it = 0; it < BIOME_WIDTH; it++)
		{
				temp.push_back(Reference[value][it]);
		}
		return temp;
	}

	inline vector<BiomeType> getBiomeTypeWithMoisture(short value, bool reference = false)
	{
		vector<BiomeType> temp;

		int it;
		for (it = 0; it < BIOME_LENGTH; it++)
		{
			temp.push_back(Reference[it][value]);
		}
		return temp;
	}

	inline vector<BiomeType> operator + (vector<BiomeType> x, vector<BiomeType> y)
	{
		vector<BiomeType> temp;
		int i, j;
		for (i = 0; i < x.size(); i++)
		{
			for (j = 0; j < y.size(); j++)
			if (x[i] == y[j])
				temp.push_back(x[i]);
		}
		return temp;

	}

	/*
	static char* Reference_Names[]{"Forest", "Grassland", "Jungle","Desert","Tundra","Barren","Wastes","Taiga","Wetland","Scrubland"};

	inline char* getName(int id){ return Reference_Names[id]; };

	inline vector<BiomeType> getBiomeTypeWithTemperature(short value, bool reference = false)
	{
		vector<BiomeType> temp;
		for (map<BiomeType, vector<int>>::iterator it = Reference.begin(); it != Reference.end(); it++)
		{
			if(it->second[3] >= value && it->second[2] <= value) 
				temp.push_back(it->first);
		}
		return temp;
	}

	inline vector<BiomeType> getBiomeTypeWithMoisture(short value, bool reference = false)
	{
		vector<BiomeType> temp;
		for (map<BiomeType, vector<int>>::iterator it = Reference.begin(); it != Reference.end(); it++)
		{
			if (it->second[1] >= value && it->second[0] <= value)
				temp.push_back(it->first);
		}
		return temp;
	}

	inline vector<BiomeType> operator + (vector<BiomeType> x, vector<BiomeType> y)
	{
		vector<BiomeType> temp;
		int i, j;
		for (i = 0; i < x.size(); i++)
		{
			for (j = 0; j < y.size(); j++)
			if (x[i]==y[j])
				temp.push_back(x[i]);
		}
		return temp;
	}*/



}

#endif