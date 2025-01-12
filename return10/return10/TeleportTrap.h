#pragma once

#include "Trap.h"
#include <vector>
#include "Coordinate.h"

class TeleportTrap : public Trap {
public:
    TeleportTrap(int x, int y, const std::vector<Coordinate>& validCells);

    void activateEffect(Player& player) override;

private:
    std::vector<Coordinate> m_validCells;
};
