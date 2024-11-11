
#include "GameLogic.h"

void GameLogic::gameStart()
{
    showStartMenu();
    startTimer();
    initializeScores();
    placePlayer();
}

void GameLogic::placePlayer()
{
    std::cout << "Placing players..." << std::endl;
    for (int i = 0; i < map.GetSpawnPoints().size() && i < 4; ++i) {
        auto spawnPoint = map.GetRandomSpawnPoint();
        Player newPlayer{ "Player" + std::to_string(i + 1), spawnPoint.first, spawnPoint.second };
        map.addPlayer(newPlayer);
        std::cout << "Player " << i + 1 << " spawned at (" << spawnPoint.first << ", " << spawnPoint.second << ")" << std::endl;
    }
}

void GameLogic::initializeScores()
{
    score = 0;
    std::cout << "Scores initialized. Starting score: " << score << std::endl;
}

void GameLogic::startTimer()
{
    startTime = std::chrono::steady_clock::now();
    std::cout << "Game timer started!" << std::endl;
}

void GameLogic::showStartMenu()
{
    std::cout << "Welcome to the game!" << std::endl;
    std::cout << "The game is starting..." << std::endl;
}

