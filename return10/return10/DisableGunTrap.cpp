#include "DisableGunTrap.h"
#include <iostream>
#include <thread>
#include <chrono>

DisableGunTrap::DisableGunTrap(int x, int y, float duration)
    : Trap(x, y), m_duration(duration) {}

void DisableGunTrap::ActivateEffect(Player& player) {
    auto& gun = player.getGun();
    gun.Jam(m_duration);
    std::cout << "Gun disabled at (" << m_coordinates.first << ", " << m_coordinates.second
        << ") for " << m_duration << " seconds.\n";
}

