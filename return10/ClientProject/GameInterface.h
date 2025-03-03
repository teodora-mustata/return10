﻿#include <iostream>
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
    void handleInput();
    void renderGame(const crow::json::rvalue& gameData, int playerId);
    void updateMap();
    bool sendCommandToServer(const std::string& command);
    void displayStatus();
    int getActivePlayers();
    bool checkWinCondition();
};
