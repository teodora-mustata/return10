#pragma once
#include "Trap.h"
#include "Player.h"
#include <chrono>

class DisableGunTrap : public Trap {
public:
    DisableGunTrap(int x, int y, float duration);
    void ActivateEffect(Player& player) override;

private:
    std::chrono::duration<float> m_duration;
};
