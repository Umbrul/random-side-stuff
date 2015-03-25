#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <time.h>   

namespace Generation
{
	static int seed = 0;
	class Random
	{
		public:
			Random(){ seed = time(0)%10; srand(seed); }
			Random(int seed){ Generation::seed = seed; srand(seed); }
		~Random();

	};

}

# endif