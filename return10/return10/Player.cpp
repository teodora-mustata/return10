
#include "Player.h"

Player::Player(std::string name, int startX, int startY) :
	m_name(name),
	m_score(0),
	m_lives(3),
	m_crowns(0),
	m_initial_position{ startX, startY },
	m_position{ startX, startY } {}

Player::Player(int id, std::string name, int score, int crowns, Gun gun, Coordinate spawnpoint) : m_id(id), m_name(name), m_score(score), m_crowns(crowns), m_gun(gun), m_initial_position(spawnpoint), m_lives{3}
{
}

Player::Player(int id, std::string name, int score, int crowns, Gun gun): m_id(id), m_name(name), m_score(score), m_crowns(crowns), m_gun(gun), m_lives{ 3 }
{
}


Player::~Player()
{
}

void Player::move(Direction direction)
{
	if (m_isImmobilized) {
		std::cout << "Player is immobilized and cannot move.\n";
		return;
	}
	switch (direction)
	{
	case Direction::UP:
		m_position.i -= 1;
		m_facingDirection = Direction::UP;
		break;
	case Direction::DOWN:
		m_position.i += 1;
		m_facingDirection = Direction::DOWN;
		break;
	case Direction::LEFT:
		m_position.j -= 1;
		m_facingDirection = Direction::LEFT;
		break;
	case Direction::RIGHT:
		m_position.j += 1;
		m_facingDirection = Direction::RIGHT;
		break;
	}
}



void Player::printPosition() {
	std::cout << m_position.i << " " << m_position.j << "\n";
}

bool Player::operator==(const Player& other)
{
	return m_name == other.m_name;
}

void Player::shoot(Direction direction)
{
	m_gun.fire(m_position.i, m_position.j, direction);
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

Coordinate Player::GetPosition() const
{
	return m_position;
}

Gun& Player::getGun() {
	return m_gun; 
}

const Gun& Player::getGun() const {
	return m_gun;
}

int Player::GetId() const
{
	return m_id;
}

Direction Player::GetFacingDirection()
{
	return m_facingDirection;
}

Coordinate Player::getInitialPosition() const
{
	return m_initial_position;
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

void Player::setId(int id)
{
	m_id = id;
}

void Player::SetFacingDirection(const Direction& dir)
{
	m_facingDirection = dir;
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

Player& Player::operator=(const Player& other)
{
	if (this != &other) { // Protecție împotriva auto-atribuției
		m_id = other.m_id;
		m_score = other.m_score;
		m_lives = other.m_lives;
		m_crowns = other.m_crowns;
		m_name = other.m_name;
		m_position = other.m_position;
		m_initial_position = other.m_initial_position;
		m_gun = other.m_gun; // Dacă `Gun` are un operator `=` definit.
		m_isImmobilized = other.m_isImmobilized;
		m_immobilizedStartTime = other.m_immobilizedStartTime;
		m_immobilizedDuration = other.m_immobilizedDuration;
	}
	return *this;
}

void Player::setInitialPosition(Coordinate coords)
{
	m_initial_position = coords;
}
void Player::setPosition(Coordinate coords)
{
	m_position = coords;
}


void Player::Immobilize(std::chrono::steady_clock::time_point startTime, std::chrono::duration<float> duration) {
	m_isImmobilized = true;
	m_immobilizedStartTime = startTime;
	m_immobilizedDuration = duration;
}


void Player::UpdateStatus(float deltaTime) {

	if (m_isImmobilized) {
		auto now = std::chrono::steady_clock::now();
		if (now - m_immobilizedStartTime >= m_immobilizedDuration) {
			m_isImmobilized = false;
			std::cout << "Player is no longer immobilized.\n";
		}
	}

	
	m_gun.updateJammed();
}

bool Player::IsImmobilized() const {
	return m_isImmobilized;
}

bool Player::IsAlive() const
{
	if (m_lives == 0) return false;
	return true;
}
