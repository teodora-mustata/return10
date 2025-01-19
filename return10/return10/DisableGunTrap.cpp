#include "DisableGunTrap.h"
#include <iostream>



DisableGunTrap::DisableGunTrap(int x, int y, float duration)
    : Trap(x, y), m_duration(std::chrono::duration<float>(duration)) {}

void DisableGunTrap::activateEffect(Player& player) {
    auto& gun = player.getGun();
    gun.jam(m_duration);
  
}

