#include "Player.h"

Player::Player(std::string name, int startX, int startY):
	m_name(name),
	m_score(0),
	m_lives(3),
	m_points(0)
{
	position = new std::pair<int, int>(startX, startY);
}

Player::~Player()
{
	delete position;
}

void Player::move(Direction direction)
{
	switch (direction)
	{
	case Direction::UP:
		position->second += 1;
		break;
	case Direction::DOWN:
		position->second -= 1;
		break;
	case Direction::LEFT:
		position->first -= 1;
		break;
	case Direction::RIGHT:
		position->first += 1;
		break;
	}
}
