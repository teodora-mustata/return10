#pragma once
#include "Trap.h"

class TeleportTrap : public Trap {
public:
    TeleportTrap(int x, int y);
    void ActivateEffect() /*override*/;
};
