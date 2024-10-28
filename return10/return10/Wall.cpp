#include "Wall.h"

Wall::Wall(int x, int y, bool destructible) : posX(x), posY(y), destructible(destructible)
{
}

Wall::~Wall()
{
	delete containedBomb;
}

void Wall::set_containedBomb(Bomb* bomb)
{
	this->containedBomb = bomb;
}

Bomb* Wall::get_containedBomb()
{
	return containedBomb;
}

bool Wall::is_destructible()
{
	return destructible;
}
