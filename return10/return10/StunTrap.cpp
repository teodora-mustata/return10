#include "StunTrap.h"
#include <iostream>

StunTrap::StunTrap(int x, int y, float duration)
    : Trap(x, y), m_duration(std::chrono::duration<float>(duration)) {}


void StunTrap::activateEffect(Player& player) {
  
 
    if (m_isActive) {
        player.immobilize(std::chrono::steady_clock::now(), m_duration);
        setState(false);
    }
}
