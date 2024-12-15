#include "StunTrap.h"
#include <iostream>

StunTrap::StunTrap(int x, int y, float duration)
    : Trap(x, y), m_duration(std::chrono::duration<float>(duration)) {}


void StunTrap::ActivateEffect(Player& player) {
  
 
    if (m_isActive) {
        player.Immobilize(std::chrono::steady_clock::now(), m_duration);
        std::cout << "Player has been immobilized for " << m_duration.count() << " seconds.\n";
        SetState(false);
    }
}
