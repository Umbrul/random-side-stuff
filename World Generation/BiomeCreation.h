#ifndef BIOMECREATION_H
#define BIOMECREATION_H

#include "BiomeTable.h"
#include "Random.h"
#include <iostream>


namespace Generation
{
	inline Biome deviatiation(Biome reference)
	{
		//Define a degree of variation which will determine how much the resulting biome can differ from the reference

		Biome result = Biome();
		int y;
		result.elevation = reference.elevation;

		y = reference.temperature + rand() % 3 - 1;
		 if (y >= 5)
			 result.temperature = y - 2;
		 else if (y < 0)
			 result.temperature = y + 2;
		 else
			 result.temperature = y;

		y = reference.moisture + rand() % 3 - 1;
		if (y >= 7)
			result.moisture = y - 2;
		else if (y < 0)
			result.moisture = y + 2;
		else
			result.moisture = y;

		vector<BiomeType> temp = getBiomeTypeWithMoisture(result.moisture) + getBiomeTypeWithTemperature(result.temperature);
		
		
		result.Type = temp[rand() % temp.size()];

		int x = result.Type;
		std::cout << "Biome: " <<getName(x)<< " Moisture: " << result.moisture << " Temperature: " << result.temperature << std::endl;
		return result;
	}
}


#endif