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

int main()
{
    //// Testing out Map functionality
    //std::cout << "Initial Map:" << std::endl;
    //std::cout << map;  // Print initial map state

    //for (auto sp : map.GetSpawnPoints()) {
    //    std::cout << "Spawnpoint: (" << sp.first << "," << sp.second << ")" << std::endl;
    //}
    //std::cout << "Map dimensions: height: " << map.GetDimensions().first << ", width: " << map.GetDimensions().second << std::endl;

    //std::cout << "------------------------------------------------------------------------------------------------" << std::endl;

    // Testing out GameLogic functionality
    Map map;

    GameLogic logic(map); 
    GameInterface game(logic);
    /*try {
        
        logic.initializePlayers(3);

        std::cout << "\nPlayers initialized:\n";
        for (const auto& player : map.GetPlayers()) {
            std::cout << player.GetName() << " at (" << player.GetPosition().i << ", " << player.GetPosition().j << ")\n";
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }*/
    logic.initializePlayers(1); 
    if (logic.GetPlayerCount() == 0) { 
        std::cerr << "No players available in the game!" << std::endl;
        return 1;
    }
    Gun gun;
    Player player("Player1", 5, 5);  

    
    Direction playerDirection = Direction::UP;

    // Test bullet creation
    std::cout << "Attempting to fire a bullet..." << std::endl;
    bool fired = gun.fire(player.GetPosition().i, player.GetPosition().j, playerDirection, gun.GetBulletSpeed());

 
    if (fired) {
        std::cout << "Bullet fired!" << std::endl;

        // Check if the fired bullets vector contains the bullet
        const auto& firedBullets = gun.getFiredBullets();
        if (!firedBullets.empty()) {
            const Bullet& bullet = firedBullets.back();  // Get the last fired bullet
            std::cout << "Bullet position: (" << bullet.GetX() << ", " << bullet.GetY() << ")\n";
            std::cout << "Bullet direction: " << static_cast<int>(bullet.GetDirection()) << std::endl;
            std::cout << "Bullet active status: " << (bullet.IsActive() ? "Active" : "Inactive") << std::endl;
        }
        else {
            std::cout << "No bullets fired." << std::endl;
        }
    }
    else {
        std::cout << "Gun cannot fire yet. Firing rate not met." << std::endl;
    }


    // Start the game
   // game.mainLoop();

    game.startGame();
	std::cout << "Server" << std::endl;
	GameStorage storage;
	if (!storage.Initialize())
	{
		std::cout << "Faild to initialize the database!";
		return -1;
	}

	crow::SimpleApp app;

	storage.DisplayDatabaseContents();

	Routing routing(app, storage);
	routing.Run();

	//storage.DisplayDatabaseContents();

	
}
