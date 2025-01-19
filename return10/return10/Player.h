#pragma once
#include <string>
#include "Direction.h"
#include "Gun.h"
#include "Coordinate.h"
#include <iostream>

class Player
{
public:
	Player(std::string name, int startX, int startY);
	Player(int id, std::string name, int score, int crowns, Gun gun, Coordinate spawnpoint);
	Player(int id, std::string name, int score, int crowns, Gun gun);
	Player() = default;
	~Player();
	void move(Direction direction);
	void printPosition();

	bool operator==(const Player& other);
	void shoot(Direction direction);

	std::string getName() const;
	int getScore() const;
	int getCrowns() const;
	int getLives() const;
	Coordinate getPosition() const;
	Gun& getGun();
	const Gun& getGun() const;
	int getId() const;
	Direction getFacingDirection();
	Coordinate getInitialPosition() const;

	void addScore(int acumulated_points);
	void addCrowns(int acumulated_points);
	void setInitialScore();
	void setInitialCrowns();
	void setId(int id);
	void setFacingDirection(const Direction& dir);

	void resetPosition();
	void loseLife();
	bool operator==(const Player& other) const;
	Player& operator=(const Player& other);

	void setInitialPosition(Coordinate coords);
	void setPosition(Coordinate coords);

	void immobilize(std::chrono::steady_clock::time_point startTime, std::chrono::duration<float> duration);
	void updateStatus(float deltaTime);
	bool isImmobilized() const;
	bool isAlive() const;

private:
	int m_id;
	int m_score;
	int m_lives=3;
	int m_crowns;
	std::string m_name;
	Coordinate m_position;
	Coordinate m_initial_position;
	Gun m_gun;
	Direction m_facingDirection = Direction::DOWN;
	bool m_isImmobilized = false;
	std::chrono::steady_clock::time_point m_immobilizedStartTime;
	std::chrono::duration<float> m_immobilizedDuration;
};

