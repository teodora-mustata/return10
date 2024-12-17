#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include "Player.h"
#include "Map.h"

class GameLogic {
public:
public:
    GameLogic() = default;
    GameLogic(Map& map);
    void checkForTraps(Player& player);
    void generateTaps();
    void initializePlayers();
    void initializeScores();
    void startTimer();
    void ApplyDamage(Bomb bomb);
    void ExplodeBomb(Bomb bomb);
    void addPlayer(Player player);
    void updateBullets(Map& map, Player& target, Gun& bullets);
    std::vector<Player>& GetPlayers();
    void removePlayer(Player player);
    const Map& GetMap() const;
    Map& GetMap();
    bool isRunning() const;
    bool checkPlayerCollision(Player& target, Bullet& bullet);
    bool checkWallCollision(Map& map, Bullet& bullet);
    std::vector<std::string> convertMapToString() const;
    void movePlayer(Player *player, Direction direction);
    bool WinCondition();
private:
    Map& map;
    std::vector<Player> m_players;
    std::chrono::steady_clock::time_point startTime;
    bool gameRunning = true;
};

