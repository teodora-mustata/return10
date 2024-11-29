#pragma once
#include <iostream>
#include <list>
#include <variant>

class Bomb
{
public:
	Bomb(int x, int y);
	~Bomb() = default;
	int GetX();
	int GetY();
	bool IsActive();
	std::list<std::pair<int,int>> CalculateEffectArea();
	void Deactivate();
	void Activate();
private:
	int m_posX, m_posY;
	bool m_isActive;
	static const int m_damage = 1;
	static const int m_radius = 1;
};

