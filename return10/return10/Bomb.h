#pragma once
#include <iostream>
#include <list>
#include <variant>
class Wall;
class Map;

class Bomb
{
private:
	int posX, posY;
	bool is_active = false;
	static const int damage = 1;
	static const int radius = 1;
public:
	Bomb(int x, int y);
	int getX();
	int getY();
	bool isActive();
	void explode(Map &map);
	std::list<std::pair<int,int>> calculate_effect_area();
	void apply_damage(Map &map);
	void deactivate();
	void activate();
};

