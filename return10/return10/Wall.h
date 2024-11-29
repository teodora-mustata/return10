#pragma once
#include "Bomb.h"

class Wall
{
public:
	Wall(int x, int y, bool destructible);
	~Wall();
	int GetX();
	int GetY();
	bool IsDestructible() const;
	void SetContainedBomb(Bomb* bomb);
	Bomb* GetContainedBomb() const;
private:
	int m_posX, m_posY;
	bool m_destructible;
	Bomb* m_containedBomb = nullptr;
};

