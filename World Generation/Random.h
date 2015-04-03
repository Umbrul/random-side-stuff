#ifndef RANDOM_H
#define RANDOM_H

#include "Point.h"
#include "Common.h"
#include <random>
#include <time.h>   
#include <utility>



namespace Generation
{
	/*
	Idea: For every coordinate (x and y), there is a max value (m) and a minimum value(n), and should be reproducible. Each x value must fall in 
	the range of n/2 to m/2. Each y value must fall in the	range of n/2 to m/2. Key integers, such as moisture, have unique n's and m's. 

	The generation of values will be carried out by PRNGS. 

	LCG (Linear Congruential Generator):

	X_{n+1} =  (a X_n + c) modm

	where X is the sequence of pseudorandom values, and:

	m,		0 < m			"modulus"
	a,		0 < a < m		"multiplier"
	c,		0 <= c < m		"increment"
	X_0,	0 <= X_0 < m	"seed" or "start value"
	
	More info online.

	To accomadate the	2 (x and y) * 3 (moisture, temperature, and elevation) = 6 different key integers, each x and y
	value will share a LCG. The y versions will be modified by the seed to differentiate it from the x values.
	*/


	class Random
	{
	public:


			Random();
			Random(int seed);
			~Random();

			void setVariables();
			float lerp(float x, float y, float r);
			void setGenerator(int key);
			int rand(int value, int offset = 0);
			int rand(int value, int offset, int key);



	private:

		/*
		Three Key Integers: temperature, moisture, elevation. At any given x/y, a key integer should be definable.

		Each Pair is:
		first -> a
		second -> c

		The m's for each chosen pair are 2^32
		*/
		std::pair <unsigned int, unsigned int> xAC[3];
		std::pair <unsigned int, unsigned int> yAC[3];
		int generator;


	};

}

# endif