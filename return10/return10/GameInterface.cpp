#include "GameInterface.h"
#include "Windows.h"

//GameInterface::GameInterface(int numPlayers)
//{
//    initializePlayers(numPlayers);
//}

#include <iostream>
#include <chrono>
#include <thread>

void GameInterface::mainLoop() {
    auto lastTime = std::chrono::steady_clock::now();

    while (gameLogic.isRunning()) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();
        lastTime = currentTime;

        handleInput();

        // Debug player position
        const Player& player = gameLogic.GetPlayer(0);
        //player.printPosition();

        std::this_thread::sleep_for(std::chrono::milliseconds(80)); // ~60 FPS
    }
}


void GameInterface::handleInput() {
    if (GetKeyState('A') & 0x8000) {
        gameLogic.GetPlayer(0).move(Direction::LEFT);
    }
    if (GetKeyState('D') & 0x8000) {
        gameLogic.GetPlayer(0).move(Direction::RIGHT);
    }
    if (GetKeyState('W') & 0x8000) {
        gameLogic.GetPlayer(0).move(Direction::UP);
    }
    if (GetKeyState('S') & 0x8000) {
        gameLogic.GetPlayer(0).move(Direction::DOWN);
    }
}


GameInterface::GameInterface(GameLogic& gl) :gameLogic(gl)
{
}

void GameInterface::startGame() {
    gameLogic.initializePlayers(4);
    std::cout << "Starting login process..." << std::endl;
    //login();
    std::cout << "Game started with " << m_players.size() << " players!" << std::endl;
    mainLoop();
}

//void GameInterface::initializePlayers(int numPlayers)
//{
//    std::string name = "A"; //placeholder, playerii vor trebui sa fie initializati cu numele ales la login
//    for (int i = 0; i < numPlayers; ++i) {
//        auto spawnPoint = m_gameMap.GetRandomSpawnPoint();
//
//        Player newPlayer(name, spawnPoint.first, spawnPoint.second);
//        name[0]++;
//
//        m_players.push_back(newPlayer);
//
//        std::cout << "Player " << i << " initialized at ("
//            << spawnPoint.first << ", " << spawnPoint.second << ")\n";
//    }
//}

void GameInterface::displayStatus() {
    for (const auto& player : m_players) {
        std::cout << player.GetName() << ": Lives=" << player.GetLives()
            << ", Score=" << player.GetScore()
            << ", Position=(" << player.GetPosition().i
            << ", " << player.GetPosition().j << ")\n";
    }
}


void GameInterface::login() {
    std::string username;
    bool loginSuccessful = false;

    while (!loginSuccessful) {
        std::cout << "Enter a username to log in: ";
        std::cin >> username;
        //loginSuccessful = m_loginManager.loginUser(username);
    }
}

GameLogic& GameInterface::GetGameLogic()
{
    return gameLogic;
}

//const Map& GameInterface::GetMap() const
//{
//    return m_gameMap;
//}

void GameInterface::handlePlayerMove(Player& player) {
    char dir;
    std::cout << "Enter direction (W / A / S / D): " << std::endl;
    std::cin >> dir;

    Direction direction;
    if (dir == 'w' || dir == 'W') {
        direction = Direction::UP;
    }
    else if (dir == 's' || dir == 'S') {
        direction = Direction::DOWN;
    }
    else if (dir == 'a' || dir == 'A') {
        direction = Direction::LEFT;
    }
    else if (dir == 'd' || dir == 'D') {
        direction = Direction::RIGHT;
    }
    else {
        std::cout << "Not a valid direction." << std::endl;
        return;
    }
    player.move(direction);
}

void GameInterface::handlePlayerShoot(Player& player) {
    std::string dir;
    std::cout << "Enter shooting direction (up, down, left, right): ";
    std::cin >> dir;

    Direction direction;
    if (dir == "up") {
        direction = Direction::UP;
    }
    else if (dir == "down") {
        direction = Direction::DOWN;
    }
    else if (dir == "left") {
        direction = Direction::LEFT;
    }
    else if (dir == "right") {
        direction = Direction::RIGHT;
    }
    else {
        std::cout << "Not a valid direction." << std::endl;
        return;
    }
    player.shoot(direction, 0.25);
}

