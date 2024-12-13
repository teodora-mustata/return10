#pragma once
#include "Trap.h"

class DisableGunTrap : public Trap {
public:
    DisableGunTrap(int x, int y);
    void ActivateEffect() /*override*/;
};
