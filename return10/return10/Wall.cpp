#include "Wall.h"

Wall::Wall(int x, int y, bool destructible) : m_posX(x), m_posY(y), m_destructible(destructible)
{
}

Wall::~Wall()
{
	delete m_containedBomb;
}

int Wall::GetX()
{
	return m_posX;
}

int Wall::GetY()
{
	return m_posY;
}

void Wall::SetContainedBomb(Bomb* bomb)
{
	this->m_containedBomb = bomb;
}

Bomb* Wall::GetContainedBomb() const
{
	return m_containedBomb;
}

bool Wall::IsDestructible() const
{
	return m_destructible;
}
