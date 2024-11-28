#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include "Player.h"
#include "Map.h"

class GameLogic {
public:
    /*void gameStart();*/
private:
    Map& map;
    std::chrono::steady_clock::time_point startTime;
    bool gameRunning = true;

public:
    GameLogic(Map& map);
    Player& GetPlayer(int index);               
    const Player& GetPlayer(int index) const;
    void initializePlayers(int numPlayers);
    void initializeScores();
    int GetPlayerCount() const;
    void MovePlayer(int index, Direction direction);
    void startTimer();
    void showStartMenu();
    void ApplyDamage(Bomb bomb);
    void ExplodeBomb(Bomb bomb);
    void addPlayer(Player player);
    void updateBullets(Map& map, Player& target, Gun& bullets);
    void removePlayer(Player player);
    //void movePlayer(Player player, Direction direction);
    const Map& GetMap() const;
    bool isRunning() const;
    //Bullet
    bool checkPlayerCollision(Player& target, Bullet& bullet);
    bool checkWallCollision(Map& map, Bullet& bullet);

    //void gameLoop() {
    //    while (gameRunning) {
    //        std::this_thread::sleep_for(std::chrono::seconds(1));
    //        std::cout << "Game is running..." << std::endl;

    //        if (score >= 100) {
    //            gameRunning = false;
    //            std::cout << "Game Over! You won!" << std::endl;
    //        }
    //    }
    //}
};

