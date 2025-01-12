#include "TeleportTrap.h"
#include <random>
#include <iostream>

TeleportTrap::TeleportTrap(int x, int y, const std::vector<Coordinate>& validCells)
    : Trap(x, y), m_validCells(validCells) {}

void TeleportTrap::activateEffect(Player& player) {
    if (m_validCells.empty()) {
        std::cout << "No valid cells for teleportation!\n";
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, m_validCells.size() - 1);

    Coordinate newLocation = m_validCells[dist(gen)];

    player.setPosition(newLocation);
    std::cout << "Player teleported to (" << newLocation.i << ", " << newLocation.j << ").\n";

    SetState(false);
}
