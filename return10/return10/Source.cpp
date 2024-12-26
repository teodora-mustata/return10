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
	//crow::SimpleApp app;
	
	storage.DisplayDatabaseContents();
	Map map;
	GameLogic game(map);
	Routing routing( storage,game);
	//Player player("Test", 0, 0);
	//StunTrap stunTrap(1, 1, 3.0f);

	//
	//stunTrap.ActivateEffect(player);

	//
	//player.move(Direction::UP);

	//
	//player.UpdateStatus(1.0f);  // 1 second passed
	//player.move(Direction::UP); // Still immobilized
	//player.UpdateStatus(2.0f);  // 2 more seconds passed
	//player.move(Direction::UP); // Can move now
	routing.Run();

	//storage.DisplayDatabaseContents();

	////Testing out Map functionality
	//Map map;
	//std::cout << map;
	//for (auto sp : map.GetSpawnPoints())
	//	std::cout << "Spawnpoint: (" << sp.first << "," << sp.second << ")" << std::endl;
	//std::cout << "Map dimensions: height: " << map.GetDimensions().first << ", width: " << map.GetDimensions().second << std::endl;

	//std::cout << "------------------------------------------------------------------------------------------------" << std::endl;

	//////Testing out GameLogic functionality
	//GameLogic newGame(map);

	//newGame.initializePlayers(4);
	//for (auto player : newGame.GetPlayers())
	//{
	//	std::cout << "Player Info:" << std::endl;
	//	std::cout << "Name: " << player.GetName() << std::endl;
	//	std::cout << "Score: " << player.GetScore() << std::endl;
	//	std::cout << "Lives: " << player.GetLives() << std::endl;
	//	std::cout << "Crowns: " << player.GetCrowns() << std::endl;
	//	std::cout << "Position: (" << player.GetPosition().first << ", " << player.GetPosition().second << ")" << std::endl;
	//}

	//std::cout << "------------------------------------------------------------------------------------------------" << std::endl;

	////Testing out GameInterface functionality
	//GameLogic logic(map);
	//GameInterface game(logic);
	////game.GetGameLogic().initializePlayers(1);

	//std::vector<Player> players = game.GetGameLogic().initializePlayers(1);
	//storage.AddPlayers(players);
	//if (game.GetGameLogic().GetPlayers().empty()) {
	//	std::cerr << "No players available in the game!" << std::endl;
	//	return 1;
	//}
	//Player player = game.GetGameLogic().GetPlayers()[0];
	//game.handlePlayerMove(player);
	//std::cout << map;

	//Map map;
	//GameLogic logic(map);
	//GameInterface game(logic);
	//game.startGame();

}
