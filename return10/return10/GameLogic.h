#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include "Player.h"
#include "Map.h"

class GameLogic {
public:
    /*void gameStart();*/
    // Getter to provide access to players from Map
    const std::vector<Player>& getPlayers() const {
        return m_players;
    }
private:
    Map* map;
    std::vector<Player> m_players;
    std::chrono::steady_clock::time_point startTime;
    bool gameRunning = true;

public:
    GameLogic(Map* map);
    void initializePlayers(int numPlayers);
    void initializeScores();
    void startTimer();
    void showStartMenu();
    void ApplyDamage(Bomb bomb);
    void ExplodeBomb(Bomb bomb);
    void addPlayer(Player player);
    void updateBullets(Map& map, Player& target, Gun& bullets);
    std::vector<Player> GetPlayers();
    void removePlayer(Player player);
    //void movePlayer(Player player, Direction direction);
    const Map& GetMap() const;

    //Bullet
    bool checkPlayerCollision(Player& target,Bullet& bullet);
    bool checkWallCollision(Map& map,Bullet& bullet);

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


