#ifndef BIOME_H
#define BIOME_H

namespace Generation
{
	class Biome{
	public:
		
		//Info pertaining to BIOME
		enum BiomeType { WASTES, DESERT, TUNDRA, BARREN, GRASSLAND, JUNGLE, TAIGA, FOREST, WETLAND, SCRUBLAND, OCEAN, COAST };
		BiomeType Type;
		Biome(BiomeType type, short moisture, short temperature){ this -> moisture = moisture; this -> temperature = temperature; elevation = 0;  Type = type; }
		Biome(){ moisture = 0; temperature = 0; elevation = 0; }
		~Biome(){}

		short Affinity(Biome biome, short modifier, bool useFactor , bool useBiome);
		
		
		short elevation; //between -5 and 5. 0 is ground level. Separate elevation from biome.
		short moisture;
		short temperature;

	protected:
	
		//Not sure why these, or regular affinity exist... keeping for now
		short biomeAffinity(BiomeType biome);
		short factorAffinity(Biome biome);



	};
}
#endif