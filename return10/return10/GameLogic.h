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
    GameLogic(std::shared_ptr<Map> map);

    void initializePlayers();
    void initializeScores();
    void addPlayer(Player player);
    std::vector<Player>& getPlayers();
    void removePlayer(Player player);

    void applyDamage(Bomb bomb);
    void checkForTraps(Player& player);
    void explodeBomb(Bomb& bomb);
    void updateBullets();
  
    const Map& GetMap() const;
    Map& GetMap();

    bool checkPlayerCollision(Player& target, Bullet& bullet);
    bool checkWallCollision(Bullet& bullet);
    std::vector<std::string> convertMapToString() const;

    void moveBullet(Map& map, Player& target, Gun* bullets);
    void movePlayer(Player *player, Direction direction);

    void startGame();
    bool isRunning() const;
    bool checkIfRunning();

    void processInput(int playerId, const std::string& command);
    void setState(GameState state);
    GameState getState() const;
    bool isInsideMap(const Coordinate& position);
    Coordinate getNextPosition(const Coordinate& currentPosition, Direction direction);

private:
    //Map& map;
    std::shared_ptr<Map> map;
    std::vector<Player> m_players;
    std::chrono::steady_clock::time_point startTime;
    bool gameRunning = true;
    GameState m_gameState;
    std::map<int, std::string> m_playerInput; // Store player input
    std::chrono::duration<double> m_timeSinceLastUpdate;
    
};

