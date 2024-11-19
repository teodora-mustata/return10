#include <iostream>
#include <algorithm>
#include "Map.h"
#include "CellType.h"
#include "GameInterface.h"
#include "GameLogic.h"

int main()
{
	//Testing out Map functionality
	Map map;
	map.PrintMap();
	//std::cout << "Map height: " << map.GetBoard().size() << std::endl;
	//std::cout << "Map width: " << map.GetBoard()[0].size() << std::endl;
	for (auto sp : map.GetSpawnPoints())
		std::cout << "Spawnpoint: (" << sp.first << "," << sp.second << ")" << std::endl;
}