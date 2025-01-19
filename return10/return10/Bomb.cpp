#include "Bomb.h"


Bomb::Bomb(int x, int y) : m_posX(x), m_posY(y), m_isActive(true) {}

int Bomb::getX()
{
    return m_posX;
}

int Bomb::getY()
{
    return m_posY;
}

bool Bomb::isActive()
{
    return m_isActive;
}

std::list<std::pair<int, int>> Bomb::calculateEffectArea()
{
    std::list<std::pair<int, int>> area_of_effect;
    for (int x = m_posX - m_radius; x <= m_posX + m_radius; ++x)
        for (int y = m_posY - m_radius; y <= m_posY + m_radius; ++y)
            if(x>=0 && y>=0) area_of_effect.emplace_back(std::make_pair(x, y));
    return area_of_effect;
}

void Bomb::deactivate()
{
	m_isActive = false;
}

void Bomb::activate()
{
	m_isActive = true;
}
