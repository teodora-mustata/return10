#pragma once
#include <iostream>
#include <list>
#include <variant>
class Wall;
class Map;

class Bomb
{
private:
	int m_posX, m_posY;
	bool m_isActive;
	static const int m_damage = 1;
	static const int m_radius = 1;
public:
	Bomb(int x, int y);
	~Bomb() = default;
	int GetX();
	int GetY();
	bool IsActive();
	void Explode(Map &map); //TO DO: move to map class
	std::list<std::pair<int,int>> calculate_effect_area();
	void ApplyDamage(Map &map); //TO DO: move to map class
	void Deactivate();
	void Activate();
};

