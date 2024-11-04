#include "Wall.h"

Wall::Wall(int x, int y, bool destructible) : posX(x), posY(y), destructible(destructible)
{
}

Wall::~Wall()
{
	delete containedBomb;
}

int Wall::getX()
{
	return posX;
}

int Wall::getY()
{
	return posY;
}

void Wall::set_containedBomb(Bomb* bomb)
{
	this->containedBomb = bomb;
}

Bomb* Wall::get_containedBomb() const
{
	return containedBomb;
}

bool Wall::is_destructible() const
{
	return destructible;
}
