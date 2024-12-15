#pragma once
#include "Trap.h"
#include "Player.h"

class DisableGunTrap : public Trap {
public:
    DisableGunTrap(int x, int y, float duration);
    void ActivateEffect(Player& player) override;

private:
    float m_duration; 
};
