
#include "Player.h"

Player::Player(std::string name, int startX, int startY) :
	m_name(name),
	m_score(0),
	m_lives(3),
	m_crowns(0),
	m_initial_position(startX, startY),
	m_position(startX, startY) {}


Player::~Player()
{
}

void Player::move(Direction direction)
{
	switch (direction)
	{
	case Direction::UP:
		m_position.i -= 1;
		break;
	case Direction::DOWN:
		m_position.i += 1;
		break;
	case Direction::LEFT:
		m_position.j -= 1;
		break;
	case Direction::RIGHT:
		m_position.j += 1;
		break;
	}
}

bool Player::operator==(const Player& other)
{
	return m_name==other.m_name;
}

void Player::shoot(Direction direction, float bulletSpeed)
{
	m_gun.fire(m_position.i, m_position.j, direction, bulletSpeed);
	//TO DO: check if the bullet collided with any player, add the points and remove the health points :)
}

std::string Player::GetName() const
{
	return m_name;
}

int Player::GetScore() const
{
	return m_score;
}

int Player::GetCrowns() const
{
	return m_crowns;
}

int Player::GetLives() const
{
	return m_lives;
}

std::pair<int, int> Player::GetPosition() const
{
	return { m_position.i,m_position.j };
}

Gun Player::getGun() const
{
	return m_gun;
}

void Player::addScore(int acumulated_points)
{
	m_score += acumulated_points;
}

void Player::addCrowns(int acumulated_points)
{
	m_crowns += acumulated_points;
}

void Player::setInitialScore()
{
	this->m_score = 0;
}

void Player::setInitialCrowns()
{
	this->m_crowns = 0;
}

void Player::resetPosition()
{
	m_position = m_initial_position;
}

void Player::loseLife()
{
	if (m_lives > 0)
	{
		m_lives -= 1;
		resetPosition();
	}
}

bool Player::operator==(const Player& other) const
{
	if (this->m_name == other.GetName()) return true;
	return false;
}
