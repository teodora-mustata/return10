#include "GameInterface.h"


//GameInterface::GameInterface(int numPlayers)
//{
//    initializePlayers(numPlayers);
//}

void GameInterface::mainLoop() {
    m_gameMap.PrintMap(); //more to do here
}

GameInterface::GameInterface()
{
    /*m_gameMap = new Map();*/
}

void GameInterface::startGame() {
    std::cout << "Starting login process..." << std::endl;
    login();
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
        //loginSuccessful = m_loginManager.loginUser(username);
    }
}

Map GameInterface::GetMap() const
{
    return m_gameMap;
}

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




