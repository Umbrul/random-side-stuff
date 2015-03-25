#ifndef BiomeTable_H
#define BiomeTable_H

#include <map>
#include <vector>
#include "Biome.h"
#include "Forest.h"

using namespace std;
namespace Generation
{

	//Table containing temperature and moisture range of each biome 
	static map<Biome::BiomeType, vector<int>> Reference
	{
	// moisture min | moisture max | temperature min | temperature max
		{ Biome::BiomeType::FOREST, { 2, 4, -3, 3 } },
		{ Biome::BiomeType::GRASSLAND, { -1, 1, -3, 3 } },
		{ Biome::BiomeType::JUNGLE, { 2, 4, 3, 5 } },
		{ Biome::BiomeType::DESERT, { -5, -2, -1, 5 } },
		{ Biome::BiomeType::TUNDRA, { -4, -2, -5, -2 } },
		{ Biome::BiomeType::BARREN, { -5, -5, 0, 5 } },
		{ Biome::BiomeType::WASTES, { -5, -5, -5, 0 } },
		{ Biome::BiomeType::TAIGA, { 2, 4, -5, -2 } },
		{ Biome::BiomeType::WETLAND, { 5, 5, -5, 5 } },
		{ Biome::BiomeType::SCRUBLAND, { -3, 1, -5, 5 } }


};

	static char* Reference_Names[]{"Forest", "Grassland", "Jungle","Desert","Tundra","Barren","Wastes","Taiga","Wetland","Scrubland"};



	inline char* getName(int id){ return Reference_Names[id]; };

	inline vector<Biome::BiomeType> getBiomeTypeWithTemperature(short value, bool reference = false)
	{
		vector<Biome::BiomeType> temp;
		for (map<Biome::BiomeType, vector<int>>::iterator it = Reference.begin(); it != Reference.end(); it++)
		{
			if(it->second[3] >= value && it->second[2] <= value) 
				temp.push_back(it->first);
		}
		return temp;
	}

	inline vector<Biome::BiomeType> getBiomeTypeWithMoisture(short value, bool reference = false)
	{
		vector<Biome::BiomeType> temp;
		for (map<Biome::BiomeType, vector<int>>::iterator it = Reference.begin(); it != Reference.end(); it++)
		{
			if (it->second[1] >= value && it->second[0] <= value)
				temp.push_back(it->first);
		}
		return temp;
	}

	inline vector<Biome::BiomeType> operator + (vector<Biome::BiomeType> x, vector<Biome::BiomeType> y)
	{
		vector<Biome::BiomeType> temp;
		int i, j;
		for (i = 0; i < x.size(); i++)
		{
			for (j = 0; j < y.size(); j++)
			if (x[i]==y[j])
				temp.push_back(x[i]);
		}
		return temp;
	}



}

#endif