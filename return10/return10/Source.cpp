#include <iostream>
#include <algorithm>
#include "Map.h"
#include "CellType.h"
#include "GameInterface.h"
#include "GameLogic.h"

int main()
{
	////Testing out Map functionality
	Map map;
	map.PrintMap();
	for (auto sp : map.GetSpawnPoints())
		std::cout << "Spawnpoint: (" << sp.first << "," << sp.second << ")" << std::endl;
	std::cout << "Map dimensions: height: " << map.GetDimensions().first << ", width: " << map.GetDimensions().second << std::endl;

	std::cout << "------------------------------------------------------------------------------------------------" << std::endl;

	////Testing out GameLogic functionality
	GameLogic newGame;

	newGame.initializePlayers(4);
	for (auto player : newGame.GetPlayers())
	{
		std::cout << "Player Info:" << std::endl;
		std::cout << "Name: " << player.GetName() << std::endl;
		std::cout << "Score: " << player.GetScore() << std::endl;
		std::cout << "Lives: " << player.GetLives() << std::endl;
		std::cout << "Crowns: " << player.GetCrowns() << std::endl;
		std::cout << "Position: (" << player.GetPosition().first << ", " << player.GetPosition().second << ")" << std::endl;
	}

	std::cout << "------------------------------------------------------------------------------------------------" << std::endl;

	//Testing out GameInterface functionality
	GameLogic logic;
	GameInterface game(logic);
	game.GetGameLogic().initializePlayers(1);
	Player player = game.GetGameLogic().GetPlayers()[0];
	game.handlePlayerMove(player);

}