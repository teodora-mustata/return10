#pragma once
#include<string>
#include"Direction.h"
class Player
{
public:
	Player(std::string name, int startX, int startY);
	~Player();
	void move(Direction direction);

private:
	int m_score;
	int m_lives;
	int m_points;
	std::string m_name;
	std::pair<int, int>* position;


};

