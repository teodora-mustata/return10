#include <iostream>
#include <vector>
#include <cpr/cpr.h>
#include <crow/json.h>
#include <string>
#include "UserSession.h"

class GameInterface {
public:
    GameInterface() = default;
    void addPlayerToGame(int playerID);
    void startGame();
    void handleInput(); // se ocupa de comenzile playerului
    void renderGame(const crow::json::rvalue& gameData, int playerId); // afiseaza mapa
    bool sendCommandToServer(const std::string& command);
    void displayStatus();
private:
    std::vector<int> m_players;
};
