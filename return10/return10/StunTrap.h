#pragma once
#include "Trap.h"
#include <chrono>


class StunTrap : public Trap {
public:
    StunTrap(int x, int y, float duration);
    void activateEffect(Player& player) override;
private:
    std::chrono::duration<float> m_duration;
};
