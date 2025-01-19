#pragma once
#include <iostream>
#include <list>
#include <variant>

class Bomb
{
public:
	Bomb(int x, int y);
	~Bomb() = default;
	int getX();
	int getY();
	bool isActive();
	std::list<std::pair<int,int>> calculateEffectArea();
	void deactivate();
	void activate();
private:
	int m_posX, m_posY;
	bool m_isActive = true;
	static const int m_damage = 1;
	static const int m_radius = 1;
};

