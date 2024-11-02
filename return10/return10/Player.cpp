#include "Player.h"

Player::Player(std::string name, int startX, int startY):
	m_name(name),
	m_score(0),
	m_lives(3),
	m_points(0),
	m_initial_position(startX, startY)
{
	m_position = new std::pair<int, int>(startX, startY);
}

Player::~Player()
{
	delete m_position;
}

void Player::move(Direction direction)
{
	switch (direction)
	{
	case Direction::UP:
		m_position->second += 1;
		break;
	case Direction::DOWN:
		m_position->second -= 1;
		break;
	case Direction::LEFT:
		m_position->first -= 1;
		break;
	case Direction::RIGHT:
		m_position->first += 1;
		break;
	}
}

std::string Player::GetName() const
{
	return m_name;
}

int Player::GetScore() const
{
	return m_score;
}

int Player::GetLives() const
{
	return m_lives;
}

std::pair<int, int> Player::GetPosition() const
{
	return *m_position;
}

void Player::addPoints(int acumulated_points)
{
	m_points += acumulated_points;
}

void Player::resetPosition()
{
	*m_position = m_initial_position;
}

void Player::loseLife()
{
	if (m_lives > 0)
	{
		m_lives -= 1;
		resetPosition();
	}
}
