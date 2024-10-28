#pragma once

class Bomb;

class Wall
{
private:
	int posX, posY;
	bool destructible;
	Bomb* containedBomb;
public:
	Wall(int x, int y, bool destructible);
	~Wall();
	bool is_destructible();
	void set_containedBomb(Bomb* bomb);
	Bomb* get_containedBomb();
};

