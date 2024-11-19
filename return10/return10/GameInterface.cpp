#include "GameInterface.h"


GameInterface::GameInterface(int mapWidth, int mapHeight, int numPlayers)
    : m_gameMap(mapWidth, mapHeight) {
    initializePlayers(numPlayers);
}
void GameInterface::mainLoop() {
    m_gameMap.PrintMap(); //more to do here
}
void GameInterface::startGame() {
    std::cout << "Starting login process..." << std::endl;
    login();
    std::cout << "Game started with " << m_players.size() << " players!" << std::endl;
    mainLoop();
}
void GameInterface::displayStatus() {
    for (const auto& player : m_players) {
        std::cout << player.GetName() << ": Lives=" << player.GetLives()
            << ", Score=" << player.GetScore()
            << ", Position=(" << player.GetPosition().first
            << ", " << player.GetPosition().second << ")\n";
    }
}

//void GameInterface::login() {
//    std::string username;
//    bool loginSuccessful = false;
//
//    while (!loginSuccessful) {
//        std::cout << "Enter a username to log in: ";
//        std::cin >> username;
//        loginSuccessful = m_loginManager.loginUser(username);
//    }
//}

void GameInterface::handlePlayerMove(Player& player) {
    std::string dir;
    std::cout << "Enter direction (up, down, left, right): ";
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




