#include "Trap.h"

Trap::Trap(int x, int y)
    : m_coordinates(x, y), m_isActive(true) {}

std::pair<int, int> Trap::GetCoordinates() const {
    return m_coordinates;
}

bool Trap::IsActive() const {
    return m_isActive;
}

void Trap::SetState(bool isActive) {
    m_isActive = isActive;
}
