#pragma once
#include <iostream>
#include <map>
#include <chrono>
#include <thread>
#include "Gun.h"
#include "Player.h"
#include "Map.h"

enum class GameState {
    WAITING_FOR_PLAYERS,
    ACTIVE,
    GAME_OVER
};


class GameLogic {
public:
public:
    GameLogic(Map& map);
    void checkForTraps(Player& player);
    void initializePlayers();
    void initializeScores();
    void ApplyDamage(Bomb bomb);
    void ExplodeBomb(Bomb bomb);
    void addPlayer(Player player);
    void updateBullets();
    std::vector<Player>& GetPlayers();
    void removePlayer(Player player);
    const Map& GetMap() const;
    Map& GetMap();
    bool isRunning() const;
    bool checkPlayerCollision(Player& target, Bullet& bullet);
    bool checkWallCollision(Map& map, Bullet& bullet);
    std::vector<std::string> convertMapToString() const;
    void moveBullet(Map& map, Player& target, Gun* bullets);
    void movePlayer(Player *player, Direction direction);
    bool WinCondition();

    void startGame();
    void processInput(int playerId, const std::string& command);
    void setState(GameState state);
    GameState getState() const;
private:
    Map& map;
    std::vector<Player> m_players;
    std::chrono::steady_clock::time_point startTime;
    bool gameRunning = true;
    GameState m_gameState;
    std::map<int, std::string> m_playerInput; // Store player input
    std::chrono::duration<double> m_timeSinceLastUpdate;
    
};

