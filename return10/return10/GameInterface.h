
#include <iostream>
#include <vector>
#include <memory>
#include "Map.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <memory>
#include "Map.h"
#include "Player.h"
#include "Direction.h"
#include "Login.h"

class GameInterface {
private:
    Map m_gameMap;
    std::vector<std::unique_ptr<Player>> m_players;
    Login m_loginManager;


public:
    GameInterface(int mapWidth, int mapHeight, int numPlayers);
    void startGame();
    void initializePlayers(int numPlayers);
    void mainLoop();
    void handlePlayerMove(Player& player);
    void handlePlayerShoot(Player& player);
    void displayStatus();
    void checkWallCollision(Bullet& bullet);


    void login();
};