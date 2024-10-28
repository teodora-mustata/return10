#pragma once
#include "Map.h"
#include <iostream>
#include <list>

class Bomb
{
private:
	int posX, posY;
	bool is_active = false;
	static const int damage = 3;
	static const int radius = 1;
public:
	Bomb(int x, int y);
	void explode(Map &map);
	std::list<std::pair<int,int>> calculate_effect_area();
	void apply_damage(Map &map);
	void deactivate();
	void activate();
};

