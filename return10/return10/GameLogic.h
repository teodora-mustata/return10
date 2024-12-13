#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include "Player.h"
#include "Map.h"

class GameLogic {
public:
    /*void gameStart();*/
public:
    GameLogic(Map& map);

    void generateTaps();
    void initializePlayers();
    void initializeScores();
    void startTimer();
    void showStartMenu();
    void ApplyDamage(Bomb bomb);
    void ExplodeBomb(Bomb bomb);
    void addPlayer(Player player);
    void updateBullets(Map& map, Player& target, Gun& bullets);
    std::vector<Player>& GetPlayers();
    void removePlayer(Player player);
    //void movePlayer(Player player, Direction direction);
    const Map& GetMap() const;
    bool isRunning() const;
    //Bullet
    bool checkPlayerCollision(Player& target, Bullet& bullet);
    bool checkWallCollision(Map& map, Bullet& bullet);
    std::vector<std::string> convertMapToString() const;
private:
    Map& map;
    std::vector<Player> m_players;
    std::chrono::steady_clock::time_point startTime;
    bool gameRunning = true;
};

