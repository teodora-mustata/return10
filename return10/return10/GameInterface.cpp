#include "GameInterface.h"
#include "Windows.h"
#include <iostream>
#include <chrono>
#include <thread>

void GameInterface::handleInput() 
{
    char input;
    std::cout << "W/A/S/D to move, F to shoot: ";
    std::cin >> input;

    // Traducem input-ul într-o comandă pentru server
    std::string command;
    switch (input) {
        case 'W': command = "MOVE_UP"; break;
        case 'A': command = "MOVE_LEFT"; break;
        case 'S': command = "MOVE_DOWN"; break;
        case 'D': command = "MOVE_RIGHT"; break;
        case 'F': command = "SHOOT"; break;
        default: 
            std::cout << "Invalid command!" << std::endl;
            return;
    }

    // Trimitem comanda către server
    sendCommandToServer(command);
}


GameInterface::GameInterface(Player user) : m_user(user)
{}


void GameInterface::displayStatus() {
    
    std::cout << m_user.GetName() << ": Lives=" << m_user.GetLives()
        << ", Score=" << m_user.GetScore()
        << ", Position=(" << m_user.GetPosition().i
        << ", " << m_user.GetPosition().j << ")\n";
  
}






