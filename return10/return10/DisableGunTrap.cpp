#include "DisableGunTrap.h"
#include <iostream>

DisableGunTrap::DisableGunTrap(int x, int y)
    : Trap(x, y) {}

void DisableGunTrap::ActivateEffect() {
    std::cout << "Player's gun is disabled at ("
        << m_coordinates.first << ", "
        << m_coordinates.second << ")"
        << std::endl;
    //implementation of Player at this coordinate to not be able to shoot for x ammount of time
    SetState(false); 
}
