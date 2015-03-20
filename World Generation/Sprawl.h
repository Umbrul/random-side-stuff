#ifndef SPRAWL_H
#define SPRAWL_H

#include <vector>
#include <map>
#include "Zone.h"
#include "TileInfo.h"


namespace Generation
{

	class Sprawl
	{
	public:
		//Info regarding world terrain features on given tile
		TileInfo ** Map;
		int length, width;


		std::vector<Zone> Zones;
		std::vector<TileInfo> Available;
		std::map<int,TileInfo> Usable;

		/*==Generation Variables==*/
		//General

		enum Phase {Start, One, Two, Three, Complete};
		Phase phase = One;
		short Complexity; //Determines what phase it will stop at.
		
		bool failed = false;
		//Phase 1 Landmasses
		/*When revisiting, */
		short totalContinents = 3;
		short totalIslands = 0;

		float LandTotal = 40;

		// Phase 2 Biomes





		//	Misc

		TileInfo Sprawl::selectTile(char query);
		TileInfo Sprawl::selectTile(Zone &area, char query);
		TileInfo Sprawl::selectTile(std::map<int, TileInfo> &area, char query);
		Sprawl::Sprawl(int length, int width, TileInfo** map, std::vector<Zone>* zones);
		Sprawl::~Sprawl(){};
		void Sprawl::init();
		void Sprawl::Print();
		bool Sprawl::balanced_decision(char target, int &x, int &y);
		bool Sprawl::focused_decision(char target, int &x, int &y);
		bool Sprawl::spread_decision(char target, int &x, int &y);
		void Sprawl::sprawl(Zone newArea, std::map<int, TileInfo>  &targetArea);
		void Sprawl::phaseOne();
		void Sprawl::phaseTwo();
		void Sprawl::Generate();
	};
}

#endif