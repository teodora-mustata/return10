#include <iostream>
#include <vector>
#include <memory>

#include "Map.h"
#include "Player.h"

class GameInterface {
public:
    GameInterface(Player user);
    void startGame();
    void mainLoop();
    void handleInput(); // se ocupa de comenzile playerului
    void renderGame(); // afiseaza mapa
    // void sendCommandToServer()
    void displayStatus();
private:
    //Map m_gameMap;
    std::vector<Player> m_enemyPlayers;
    Player m_user;
};
