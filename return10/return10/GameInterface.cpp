#include "GameInterface.h"


GameInterface::GameInterface(int mapWidth, int mapHeight, int numPlayers)
    : m_gameMap(mapWidth, mapHeight) {
    initializePlayers(numPlayers);
    m_gameMap.generateWalls();
    m_gameMap.generateSpawnPoints();
}
void GameInterface::mainLoop() {
    m_gameMap.printMap(); //more to do here
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

void GameInterface::login() {
    std::string username;
    bool loginSuccessful = false;

    while (!loginSuccessful) {
        std::cout << "Enter a username to log in: ";
        std::cin >> username;
        loginSuccessful = m_loginManager.loginUser(username);
    }
}

void GameInterface::handlePlayerMove(Player& player) {
    std::string dir;
    std::cout << "Enter direction (up, down, left, right): ";
    std::cin >> dir;

    Direction direction; //need to get the direction from the directionUtils here
    player.move(direction);
}

void GameInterface::handlePlayerShoot(Player& player) {
    std::string dir;
    std::cout << "Enter shooting direction (up, down, left, right): ";
    std::cin >> dir;

    Direction direction; //need to get the direction from the directionUtils here
    player.shoot(direction, 0.25);
}


