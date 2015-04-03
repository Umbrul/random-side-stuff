#include "Random.h"


namespace Generation
{
	Random::Random()
	{
		seed = time(0) % 10; 
		srand(seed);
		setVariables();
	}

	Random::Random(int custom_seed)
	{ 
		seed = custom_seed;
		srand(seed); 
		setVariables();
	}

	void Random::setVariables()
	{
		xAC[0] = std::make_pair(1664525, 1013904223);
		yAC[0] = std::make_pair(1664525, 1013904223);

		xAC[1] = std::make_pair(22695477, 1);
		yAC[1] = std::make_pair(22695477, 1);

		xAC[2] = std::make_pair(134775813, 1);
		yAC[2] = std::make_pair(134775813, 1);
	}

	//Set specific LCG to use at any given moment. 0 Elevation 1 Moisture 2 Temperature
	void Random::setGenerator(int key)
	{
		generator = key;
	}

	int Random::rand(int value, int offset)
	{
		return ((xAC[generator].first * value + xAC[generator].second) % 2147483647);
	}

	int Random::rand(int value, int offset, int key)
	{

		return ((xAC[key].first * (value + offset) + xAC[key].second) % 2147483647);
	}

	



	

}