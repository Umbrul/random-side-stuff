#include "Perlin.h"


namespace Generation
{
	namespace
	{
		double* tempXMap;
		double* tempYMap;
		Random* generator;
	}

	Perlin_Sprawl::Perlin_Sprawl(Random *gen, int length, int width, int height, TileInfo** &map)
	{
		
		this->length = length; 
		this->width = width;
		this->height = height;
		generator = gen;

		Map = new TileInfo*[length];
		map = Map;
		/*
		Given height h, the max rand value must be a value such that
		when the octaves are added (if any in use) together, they 
		will, at max, equal the height. The persistence and number
		of octaves is the key factor.

			current amplitude = persistence * octave
			max >= 
		#1	height * (1/(sum(amplitudes))) +
		#2	height * (0.5/(sum(amplitudes))) +
		#3	height * (0.25/(sum(amplitudes)))

			Where, here are three octaves and the persistence is 0.5.
			1, 0.5, and 0.25 are the amplitudes

		Higher persistence gives more smooth function, though it shouldn't 
		matter a huge deal.

		So, the max used should be height * (1/(sum(amplitudes))). The resulting
		octaves are handled in the main pnoise function by multiplying the appropriate
		factors.

		Example: 
		height = 20, persistence = 0.5, octaves = 3
		A 0.57142857142857142857142857142857 <- height * (1/(sum(amplitudes)))
		B 0.28571428571428571428571428571429 <- height * (0.5/(sum(amplitudes)))
		C 0.14285714285714285714285714285714 <- height * (0.25/(sum(amplitudes)))

		A * 20 = 11.428571428571428571428571428571
		B * 20 = 5.7142857142857142857142857142858
		C * 20 = 2.8571428571428571428571428571428
		A + B + C = 20
		*/

		double sum = 0;

		double temp = 1;

		for (int i = 1; i <= octaves; i++)
		{
			sum +=  (temp);
			temp *= persist;
		}

		/* 
		the max (1-octave) is the (height  * 10 + 1) / 10). 
		A height of 10 translates to a height of 21. 
		10 (above) + 10 (below) + 1 (flat)

		Additional octaves just mean doing the 1/sum from previous comment
		*/

		double maxFactor = 1 / sum;
		amplMax = sum;
		std::cout << "amplMax: " << amplMax << std::endl;
		std::cout << "current maxFactor: " << maxFactor << std::endl;
		tempXMap = new double[width];
		srand(time(NULL));
		for (int i = 0; i < width; i++)
		{
			tempXMap[i] = double(generator->rand(i, 0, 0) % ((height * 2 * 10) / 10) + 1) * maxFactor;

			std::cout << " Rand x: " << generator->rand(i, 0, 0) << std::endl;
		}

		tempYMap = new double[length];
		srand(time(NULL));

		for (int i = 0; i < length; i++)
			tempYMap[i] = double(generator->rand(i,seed,0) % ((height * 2 * 10) / 10) + 1) * maxFactor;

		PerlinNoise2D();
	}

	Perlin_Sprawl::~Perlin_Sprawl()
	{
		delete tempXMap;
		delete tempYMap;
	}

	double Perlin_Sprawl::noise(int x, int y)
	{
		//When proceding to procedural (if using this) place a flag here
		return 
			(
			tempXMap[((x<0) ? width - 1 : x >= width) ? 0 : x] + 
			tempYMap[((y<0) ? length - 1 : y >= length) ? 0 : y]
			) / 2.0;
	}

	double Perlin_Sprawl::smoothNoise(int x, int y )
	{
		return (noise(x, y) + noise(x+1, y) + noise(x, y+1) 
			+ noise(x-1, y) + noise(x, y-1))/5.0;
	}

	void Perlin_Sprawl::PerlinNoise2D()
	{


		for (int i = 0; i < length; i++)
		{
			Map[i] = new TileInfo[width];
			for (int j = 0; j < width; j++)
			{
				Map[i][j] = TileInfo();
				Map[i][j].zone_id = 0;
				Map[i][j].x = j;
				Map[i][j].y = i;
				
				// Subtracting height so that negative (below) values exist. See Constructor 
				double tempElevation = 0;
				double ampl = 1;
				
				for (int k = 1; k <= octaves; k++)
				{

					if (k!=1)
						ampl *= persist;

					tempElevation += (smoothNoise(j, i) * (ampl));

				}
				Map[i][j].elevation = tempElevation - height;
			}
		}

	}

	void Perlin_Sprawl::Print()
	{
		
		for (int i = 0; i < length; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				std::cout << int(Map[i][j].elevation) << " ";
			}
			std::cout << std::endl;
		}
		
	}
}