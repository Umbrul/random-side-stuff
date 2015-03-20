#ifndef BIOME_H
#define BIOME_H

namespace Generation
{
	class Biome{
	public:
		
		//Info pertaining to BIOME
		enum BiomeType { PRIMARY, SECONDARY }; 
		enum BiomeName { WASTES,DESERT,TUNDRA,BARREN, GRASSLAND, JUNGLE,TAIGA,FOREST, WETLAND, OCEAN, COAST};

		BiomeType Type;
		BiomeName Name;

		Biome(BiomeType type, BiomeName name, short moisture, short temperature){ this -> moisture = moisture; this -> temperature = temperature; elevation = 0; Name = name; Type = type; }
		Biome(){ moisture = 0; temperature = 0; elevation = 0; Name = GRASSLAND; Type = PRIMARY; }
		~Biome(){}

		short Affinity(Biome biome, short modifier, bool useFactor , bool useBiome);

	protected:
		short elevation; //between -5 and 5. 0 is ground level.
		short moisture;
		short temperature;

		short biomeAffinity(BiomeName biome);
		short factorAffinity(Biome biome);



	};
}
#endif