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

void Bomb::Explode(Map &map)
{
    if (m_isActive) {
        std::cout << "Bomb exploded at (" << m_posX << ", " << m_posY << ")!" << std::endl;
        ApplyDamage(map);
        Deactivate();
    }
    else {
        std::cout << "Bomb is not active and cannot explode." << std::endl;
    }
}

std::list<std::pair<int, int>> Bomb::calculate_effect_area()
{
    std::list<std::pair<int, int>> area_of_effect;
    for (int x = m_posX - m_radius; x <= m_posX + m_radius; ++x)
        for (int y = m_posY - m_radius; y <= m_posY + m_radius; ++y)
            area_of_effect.emplace_back(std::make_pair(x, y));
    return area_of_effect;
}

//void Bomb::apply_damage(Map &map)
//{
//    std::list<std::pair<int, int>> area_of_effect = calculate_effect_area();
//    for (auto coord : area_of_effect)
//    {
//        int x = coord.first;
//        int y = coord.second;
//
//        //TO DO: apply damage to players
//
//        if (auto* wall = std::get_if<Wall>(&map.get_cell_type(x, y)); wall && wall->is_destructible())
//        {
//            map.set_cell_type(x, y, std::monostate{});
//        }
//    }
//}

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
