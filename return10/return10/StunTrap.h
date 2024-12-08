#pragma once
#include "Trap.h"

class StunTrap : public Trap {
public:
    StunTrap(int x, int y);
    void ActivateEffect() override;
};
