#ifndef GENERATION_H
#define GENERATION_H

#include <vector>
#include <map>
#include <iostream>
#include <time.h>  
#include <math.h>
#include <vector>
#include "Random.h"
#include "Sprawl.h"
#include "Perlin.h"
#include "Constants.h"
#include "Common.h"
#include "BiomeCreation.h"
#include "Random.h"

namespace Generation
{

	//New order land/elevation -> water -> paint terrain -> landmarks -> roads


	class Generate{
		/*==Generation Variables==*/
		//General

	private:
		int layer = 0;
		enum Method { Perlin_Sprawl, Sprawl };
		Method currentMethod = Perlin_Sprawl;


	public:

		TileInfo ** HeightMap = NULL;
		TileInfo ** TemperatureMap = NULL;
		TileInfo ** MoistureMap = NULL;
		std::vector<Zone> * Zones = NULL;
		Random * random = NULL;

		Generate::Generate()
		{
			random = new Random();
		}

		int getMoisture(int x, int y);
		int getTemperature(int x, int y);
		int getElevation(int x, int y);

		void Generate::terrain_picker_test();
		void DisplayLayer(int layer);
		void DisplayLayers();
		void HeightToMap();
		void sprawl();
		void perlin_sprawl();

	};
}

#endif