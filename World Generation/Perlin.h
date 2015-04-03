#ifndef PERLIN_H
#define PERLIN_H

#include "TileInfo.h"
#include "Random.h"
#include "Zone.h"
#include <time.h>
#include <stdlib.h>     /* srand, rand */
#include <iostream>


namespace Generation
{
	class Perlin_Sprawl
	{
		
	public:
		Perlin_Sprawl(Random* rand, int length, int width, int height, TileInfo** &map);
		~Perlin_Sprawl();
		void Print();

	private:

		TileInfo ** Map;
		int length, width, height;
		int octaves = 5; // At min should be 1
		double persist = 0.75; // persist >= 1
		double amplMax;

		double noise(int x, int y);
		double smoothNoise(int x, int y);
		void PerlinNoise2D();
	};
}
#endif // !PERLIN_H
