#include "DisableGunTrap.h"
#include <iostream>



DisableGunTrap::DisableGunTrap(int x, int y, float duration)
    : Trap(x, y), m_duration(std::chrono::duration<float>(duration)) {}

void DisableGunTrap::ActivateEffect(Player& player) {
    auto& gun = player.getGun();
    gun.Jam(m_duration);
    std::cout << "Gun disabled at (" << m_coordinates.first << ", " << m_coordinates.second
        << ") for " << m_duration.count() << " seconds.\n";
}

