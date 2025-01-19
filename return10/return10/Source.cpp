#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <iostream>
#include <algorithm>
#include "Map.h"
#include "CellType.h"
#include "GameInterface.h"
#include "GameLogic.h"
#include <sqlite_orm/sqlite_orm.h>
#include "BattleCityDatabase.h"
#include "routing.h"
#include "Bullet.h"
#include "Gun.h"
#include "Trap.h"
#include "StunTrap.h"

int main()
{
	std::cout << "Server" << std::endl;
	GameStorage storage;
	if (!storage.Initialize())
	{
		std::cout << "Failed to initialize the database!";
		return -1;
	}
	
	storage.DisplayDatabaseContents();
	Map map;
	GameManager& gameManager = GameManager::getInstance(storage);
	Routing routing( storage,gameManager);
	routing.Run();

}
