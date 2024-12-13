#include "StunTrap.h"
#include <iostream>

StunTrap::StunTrap(int x, int y, float duration)
    : Trap(x, y) {
    m_duration = duration;
}

void StunTrap::ActivateEffect(Player& player) {
  
 
    if (m_isActive) {
        player.Immobilize(m_duration);
        std::cout << "Player has been immobilized for " << m_duration << " seconds.\n";
        SetState(false);
    }
}
