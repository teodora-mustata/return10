#include "TeleportTrap.h"
#include <iostream> 

TeleportTrap::TeleportTrap(int x, int y)
    : Trap(x, y) {}

void TeleportTrap::ActivateEffect() {
    std::cout << "Player is teleported from ("
        << m_coordinates.first << ", "
        << m_coordinates.second << ")"
        << std::endl;
    //repaint player at random coordinates on the map
    SetState(false); 
}
