#include "StunTrap.h"
#include <iostream>

StunTrap::StunTrap(int x, int y)
    : Trap(x, y) {}

void StunTrap::ActivateEffect() {
    std::cout << "Player is stunned at ("
        << m_coordinates.first << ", "
        << m_coordinates.second << ")"
        << std::endl;
    //logic for disabling player movement for x ammount of time
    SetState(false);
}
