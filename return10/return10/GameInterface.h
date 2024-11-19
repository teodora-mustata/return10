#include <iostream>
#include <vector>
#include <memory>
#include "Map.h"
#include "Player.h"
#include "Direction.h"
#include "Login.h"
#include "Shop.h"
#include "GameLogic.h"

class GameInterface {
private:
    Map m_gameMap;
    std::vector<Player> m_players;
    Login m_loginManager; 
public:
    GameInterface();
    void startGame();
    //void initializePlayers(int numPlayers);
    void mainLoop();
    void handlePlayerMove(Player& player);
    void handlePlayerShoot(Player& player);
    void displayStatus();
    void login();
    Map GetMap() const;
};
