#include "Bomb.h"


Bomb::Bomb(int x, int y) : m_posX(x), m_posY(y), m_isActive(false) {}

int Bomb::GetX()
{
    return m_posX;
}

int Bomb::GetY()
{
    return m_posY;
}

bool Bomb::IsActive()
{
    return m_isActive;
}

std::list<std::pair<int, int>> Bomb::CalculateEffectArea()
{
    std::list<std::pair<int, int>> area_of_effect;
    for (int x = m_posX - m_radius; x <= m_posX + m_radius; ++x)
        for (int y = m_posY - m_radius; y <= m_posY + m_radius; ++y)
            if(x>=0 && y>=0) area_of_effect.emplace_back(std::make_pair(x, y)); // TO DO: x < map.height; y < map.width
    return area_of_effect;
}

void Bomb::Deactivate()
{
	m_isActive = false;
	std::cout << "Bomb deactivated." << std::endl;
}

void Bomb::Activate()
{
	m_isActive = true;
	std::cout << "Bomb activated at (" << m_posX << ", " << m_posY << ")." << std::endl;
}
