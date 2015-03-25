#include <math.h>
#include <vector>
#include "Sprawl.h"
#include "Zone.h"
#include <iostream>
#include <time.h>  

namespace Generation
{

	//Set up empty world map/array. Define world size and sprawl type before here.
	Sprawl::Sprawl(int length, int width, TileInfo** map, std::vector<Zone>* zones)
	{
		
		this->length = length;
		this->width = width;

		Map = new TileInfo*[length];
	    map = Map;
		zones = &Zones;

		Generate();

	}


	void Sprawl::init()
	{
		srand(time(NULL));
		Usable.clear();
		Available.clear();
		Available.swap(Available);

		Zone world = Zone(length*width, 'L');

		for (int i = 0; i < length; ++i)
		{
			Map[i] = new TileInfo[width];
			for (int j = 0; j < width; ++j)
			{
				Map[i][j] = TileInfo();
				Map[i][j].zone_id = 0;
				Map[i][j].x = j;
				Map[i][j].y = i;
				world.addTileInfo(j + i*width, Map[i][j]);
			}
		}
		Zones.push_back(world);

		std::cout << "test: " << Zones[0].size << std::endl;
		phase = One;
	}


	TileInfo Sprawl::selectTile(std::map<int, TileInfo> &area, char query)
	{
		TileInfo tile;

		std::cout << "TEST SIZE: " << area.size() << std::endl;
		//collect all tiles of query type in map and randomly select one
		if (phase == One)
		{
			int index = rand() % (area.size());
			std::map<int, TileInfo>::iterator it;

			int temp = 0;
			for (it = area.begin(); it != area.end(); temp++)
			{
				if (temp == index)
				{
					tile = it->second;
					std::cout << index << " " << index%width << " " << index / length << std::endl;
					area.erase(it);
					break;

				}
				it++;
			}
		}
		else if (phase == Two)
		{

		}
		else if (phase == Three)
		{

		}
		return tile;
	}

	TileInfo Sprawl::selectTile(Zone &area, char query)
	{
		TileInfo tile;
		//collect all tiles of query type in map and randomly select one
		if (phase == One)
		{
			int index = rand() % (area.size);

			tile = Map[area.getTileInfo()[index]->y][area.getTileInfo()[index]->x];
			std::cout << index << " " << index%width << " " << index / length << std::endl;

		}
		else if (phase == Two)
		{

		}
		else if (phase == Three)
		{

		}
		return tile;
	}


	TileInfo Sprawl::selectTile(char query)
	{
		TileInfo tile;
		//collect all tiles of query type in map and randomly select one
		if (phase == One)
		{
			int index = rand() % (length*width);

			tile = Map[index / length][index%width];
			std::cout << index << " " << index%width << " " << index / length << std::endl;

		}
		else if (phase == Two)
		{

		}
		else if (phase == Three)
		{

		}
		return tile;
	}

	bool Sprawl::balanced_decision(char target, int &x, int &y)
	{

		int tile = rand() % Available.size();
		y = Available[tile].y;
		x = Available[tile].x;

		TileInfo parent = Map[y][x];

		int direction = rand() % 4;

		Available.erase(Available.begin() + tile);

		int temp = direction;
		for (int i = 0; i < 4; i++)
		{
			if (temp == 0 && x != 0 && Map[y][x - 1].terrain == target) //left
			{
				Available.push_back(parent);
				--x;
				return true;
			}
			else if (temp == 2 && x != width - 1 && Map[y][x + 1].terrain == target) //right
			{
				Available.push_back(parent);
				++x;
				return true;
			}
			else if (temp == 1 && y != 0 && Map[y - 1][x].terrain == target) //top
			{
				Available.push_back(parent);
				y--;
				return true;
			}
			else if (temp == 3 && y != length - 1 && Map[y + 1][x].terrain == target) //bottom
			{
				Available.push_back(parent);
				y++;
				return true;
			}
			temp = (temp + 1) % 4;
		}
		return false;
	}


	bool Sprawl::focused_decision(char target, int &x, int &y)
	{

		int tile = 0;

		int temp = rand() % ((Available.size() * Available.size() * (Available.size() + 1)*(Available.size() + 1)) / 4);

		for (int i = 1; i <= Available.size(); i++)
		{
			temp -= i*i*i;

			if (temp <= 0)
			{
				tile = i - 1;
				break;
			}
		}
		if (temp > 0)
			return false;

		y = Available[tile].y;
		x = Available[tile].x;

		TileInfo parent = Map[y][x];

		Available.erase(Available.begin() + tile);

		int direction = rand() % 4;

		temp = direction;
		for (int i = 0; i < 4; i++)
		{
			if (temp == 0 && x != 0 && Map[y][x - 1].terrain == target) //left
			{
				Available.push_back(parent);
				--x;
				return true;
			}
			else if (temp == 2 && x != width - 1 && Map[y][x + 1].terrain == target) //right
			{
				Available.push_back(parent);
				++x;
				return true;
			}
			else if (temp == 1 && y != 0 && Map[y - 1][x].terrain == target) //top
			{
				Available.push_back(parent);
				y--;
				return true;
			}
			else if (temp == 3 && y != length - 1 && Map[y + 1][x].terrain == target) //bottom
			{
				Available.push_back(parent);
				y++;
				return true;
			}
			temp = (temp + 1) % 4;
		}
		return false;
	}

	bool Sprawl::spread_decision(char target, int &x, int &y)
	{


		int tile = 0;

		int temp = rand() % ((Available.size() * Available.size() * (Available.size() + 1)*(Available.size() + 1)) / 4);

		for (int i = 1; i <= Available.size(); i++)
		{
			temp -= i*i*i;

			if (temp <= 0)
			{
				tile = Available.size() - i;
				break;
			}
		}
		if (temp > 0)
			return false;

		y = Available[tile].y;
		x = Available[tile].x;

		TileInfo parent = Map[y][x];

		Available.erase(Available.begin() + tile);

		int direction = rand() % 4;

		temp = direction;
		for (int i = 0; i < 4; i++)
		{
			if (temp == 0 && x != 0 && Map[y][x - 1].terrain == target) //left
			{
				Available.push_back(parent);
				--x;
				return true;
			}
			else if (temp == 2 && x != width - 1 && Map[y][x + 1].terrain == target) //right
			{
				Available.push_back(parent);
				++x;
				return true;
			}
			else if (temp == 1 && y != 0 && Map[y - 1][x].terrain == target) //top
			{
				Available.push_back(parent);
				y--;
				return true;
			}
			else if (temp == 3 && y != length - 1 && Map[y + 1][x].terrain == target) //bottom
			{
				Available.push_back(parent);
				y++;
				return true;
			}
			temp = (temp + 1) % 4;
		}
		return false;
	}

	/*
	*Create a new zone comprised of given tile type within the defined zone.
	*The same approach will always be used. How the next tile is selected
	*is determined beforehand. Possibly dependant on phase/terrain.
	*/

	void Sprawl::sprawl(Zone newArea, std::map<int, TileInfo>  &targetArea)
	{
		bool success = false;
		int val = newArea.size;

		while (val > 0)
		{
			int x = 0;
			int y = 0;

			if (Available.size() == 0)
			{
				//Should only occur when there is no room.
				std::cout << "Failed Gen. Restarting..." << std::endl;
				failed = true;
				break;
			}

			if (phase == One)
			{
				if (newArea.type == Zone::BALANCED)
					success = balanced_decision('O', x, y);
				else if (newArea.type == Zone::SPREAD)
					success = spread_decision('O', x, y);
				else if (newArea.type == Zone::FOCUSED)
					success = focused_decision('O', x, y);
				if (success)
					Map[y][x].terrain = newArea.symbol;
			}

			if (success)
			{
				newArea.addTileInfo(newArea.size - 1, Map[y][x]);
				targetArea.erase(Map[y][x].reference_id);
				Available.push_back(Map[y][x]);
				val--;
			}

			success = false;
		}
	}

	//Given an empty world (all 0), place land and maybe water;
	void Sprawl::phaseOne()
	{
		/*Start by storing all of tiles that can be used. This makes no difference if just once
		*landmass. However, with multiple, each successive landmass will have a smaller pool of tiles use.*/

		std::cout << "test: " << Zones[0].size << std::endl;
		for (int i = 0; i < Zones[0].size; i++)
		{

			Zones[0].getTileInfo()[i]->reference_id = i;
			Usable.insert(std::pair<int, TileInfo>(i, *Zones[0].getTileInfo()[i]));
		}


		//Array of landmass zones. Generate the size of each one first
		Zone * land = new Zone[totalContinents];

		int size = int((LandTotal / 100.0)*Zones[0].size);
		int temp = size;

		std::cout << "land size: " << size << std::endl;


		// Define/Create each new zone given newly defined siezes. Assign associated terrain symbol for the zone.
		for (int continent = 0; continent < totalContinents; continent++)
		{
			int landSize = (rand() % 10) + ((temp / totalContinents) - 5); //make variables for this later.
			if (continent + 1 == totalContinents)
			{
				land[continent] = Zone(size, 'L');
				std::cout << "0 landmass " << continent << ": " << size << std::endl;
			}
			else if (landSize > size)
			{
				land[continent] = Zone(size, 'L');
				std::cout << "1 landmass " << continent << ": " << size << std::endl;
				size -= size;
			}
			else
			{
				land[continent] = Zone(landSize, 'L');
				std::cout << "2 landmass " << continent << ": " << landSize << std::endl;
				size -= landSize;
			}

		}

		// Given the parameters in place, generate each landmass
		for (int continent = 0; continent < totalContinents && !failed; continent++)
		{
			TileInfo startingTile;

			startingTile = selectTile(Usable, 'O');

			if (startingTile.terrain == 'S')
				continent--;
			else
			{
				Map[startingTile.y][startingTile.x].terrain = 'L';
				Available.push_back(Map[startingTile.y][startingTile.x]);

				sprawl(land[continent], Usable);
				land[continent].addTileInfo(0, Map[startingTile.y][startingTile.x]);


				//Generate Shore around new land
				for (int i = 0; i < Available.size(); i++)
				{
					//Make a method for this border placement later (after it is used for mroe than just land. obv make improve it when that happens.
					if (Available[i].x != 0 && Map[Available[i].y][Available[i].x - 1].terrain == 'O') //left
					{
						Map[Available[i].y][Available[i].x - 1].terrain = 'S';
					}
					if (Available[i].x != width - 1 && Map[Available[i].y][Available[i].x + 1].terrain == 'O') //right
					{
						Map[Available[i].y][Available[i].x + 1].terrain = 'S';
					}
					if (Available[i].y != 0 && Map[Available[i].y - 1][Available[i].x].terrain == 'O') //top
					{
						Map[Available[i].y - 1][Available[i].x].terrain = 'S';
					}
					if (Available[i].y != length - 1 && Map[Available[i].y + 1][Available[i].x].terrain == 'O') //bottom
					{
						Map[Available[i].y + 1][Available[i].x].terrain = 'S';
					}
				}

				//Clear it for next land placement, or completion of phase one.
				Available.clear();
			}
		}

		phase = Complete;

		Usable.clear();

		delete land;
	}


	void Sprawl::phaseTwo()
	{


	}


	void Sprawl::Print()
	{
		for (int i = 0; i < length; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				std::cout << Map[i][j].terrain << " ";
			}
			std::cout << std::endl;
		}
	}

	void Sprawl::Generate()
	{

		phase = Start;
		while (phase != Complete)
		{

			std::cout << "Start Generation..." << std::endl;
			if (phase == Start)
				Sprawl::init();
			Print();
			if (phase == One)
				phaseOne();
			else if (phase == Two)
			{
				phaseTwo();
			}
			Print();


			//If failure at any given point, restart
			if (failed)
			{
				// Clear/Delete all relevant data MAKE SURE TO FILL THIS IN LATER
				failed = false;
				phase = Start;
			}
		}
	}



}