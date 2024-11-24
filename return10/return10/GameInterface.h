#include <iostream>
#include <vector>
#include <memory>

#include "Map.h"
#include "Player.h"
#include "Direction.h"
#include "Login.h"
#include "Shop.h"
#include "GameLogic.h"
#include "Coordinate.h"

class GameInterface {
private:
    //Map m_gameMap;
    std::vector<Player> m_players;
    Login m_loginManager; 
    GameLogic& gameLogic; // referință la GameLogic pentru a interacționa cu jocul
public:
    GameInterface(GameLogic& gl); // jerry added ref here for debug assertion error 
    void startGame();
    void mainLoop();
    void handleInput();
    void handlePlayerMove(Player& player);
    void handlePlayerShoot(Player& player);
    void displayStatus();
    void login();
    //const Map& GetMap() const;
    GameLogic& GetGameLogic(); //put reference here to solve the debug assertion failure error
};
