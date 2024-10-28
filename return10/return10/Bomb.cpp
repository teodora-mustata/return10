#include "Bomb.h"


Bomb::Bomb(int x, int y) : posX(x), posY(y), is_active(false) {} 

void Bomb::explode(Map &map)
{
    if (is_active) {
        std::cout << "Bomb exploded at (" << posX << ", " << posY << ")!" << std::endl;
        apply_damage(map);
        deactivate();
    }
    else {
        std::cout << "Bomb is not active and cannot explode." << std::endl;
    }
}

std::list<std::pair<int, int>> Bomb::calculate_effect_area()
{
    std::list<std::pair<int, int>> area_of_effect;
    for (int x = posX - radius; x <= posX + radius; ++x)
        for (int y = posY - radius; y <= posY + radius; ++y)
            area_of_effect.emplace_back(std::make_pair(x, y));
    return area_of_effect;
}

void Bomb::apply_damage(Map &map)
{
    std::list<std::pair<int, int>> area_of_effect = calculate_effect_area();
    for (auto coord : area_of_effect)
    {
        int x = coord.first;
        int y = coord.second;

        //TO DO: apply damage to players and walls

    }
}

void Bomb::deactivate()
{
	is_active = false;
	std::cout << "Bomb deactivated." << std::endl;
}

void Bomb::activate()
{
	is_active = true;
	std::cout << "Bomb activated at (" << posX << ", " << posY << ")." << std::endl;
}
