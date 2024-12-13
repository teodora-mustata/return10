#pragma once
#include "Trap.h"


class StunTrap : public Trap {
public:
    StunTrap(int x, int y, float duration);
    void ActivateEffect(Player& player) override;
private:
    float m_duration = 2.0f;
};
