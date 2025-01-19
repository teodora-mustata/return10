#include "Trap.h"

Trap::Trap(int x, int y)
    : m_coordinates(x, y), m_isActive(true) {}

std::pair<int, int> Trap::getCoordinates() const {
    return m_coordinates;
}

bool Trap::isActive() const {
    return m_isActive;
}

void Trap::setState(bool isActive) {
    m_isActive = isActive;
}
