#include "BiomeCreation.h"
#include <iostream>


using namespace Constants;
namespace Generation
{
	
	   Biome BiomeCreation::deviatiation(Biome reference)
		{
			//Define a degree of variation which will determine how much the resulting biome can differ from the reference

			Biome result = Biome();
			int y;
			result.elevation = reference.elevation;

			y = reference.temperature + rand() % 3 - 1;
			if (y >= TEMP_MAX)
				result.temperature = y - 2 - TEMP_MIN;
			else if (y < TEMP_MIN)
				result.temperature = y + 2 - TEMP_MIN;
			else
				result.temperature = y;

			y = reference.moisture + rand() % 3 - 1;
			if (y >= MOISTURE_MAX)
				result.moisture = y - 2 - MOISTURE_MIN;
			else if (y < MOISTURE_MIN)
				result.moisture = y + 2 - MOISTURE_MIN;
			else
				result.moisture = y;

			vector<BiomeType> temp = getBiomeTypeWithMoisture(result.moisture) + getBiomeTypeWithTemperature(result.temperature);


			result.Type = temp[rand() % temp.size()];

			int x = result.Type;
			std::cout << "Biome: " << getName(x) << " Moisture: " << result.moisture << " Temperature: " << result.temperature << std::endl;
			return result;
		}
		
	

}