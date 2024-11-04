#pragma once

class Bomb;

class Wall
{
private:
	int posX, posY;
	bool destructible;
	Bomb* containedBomb=nullptr;
public:
	Wall(int x, int y, bool destructible);
	~Wall();
	int getX();
	int getY();
	bool is_destructible() const;
	void set_containedBomb(Bomb* bomb);
	Bomb* get_containedBomb() const;
};

