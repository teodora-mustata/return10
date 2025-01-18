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

	//Getters
	std::string GetName() const;
	int GetScore() const;
	int GetCrowns() const;
	int GetLives()const;
	Coordinate GetPosition() const;
	Gun& getGun();
	const Gun& getGun() const;
	int GetId() const;
	Direction GetFacingDirection();
	Coordinate getInitialPosition() const;

	//Updates for player
	void addScore(int acumulated_points);
	void addCrowns(int acumulated_points);
	void setInitialScore();
	void setInitialCrowns();
	void setId(int id);
	void SetFacingDirection(const Direction& dir);

	void resetPosition();
	void loseLife();
	bool operator==(const Player& other) const;
	Player& operator=(const Player& other);

	void setInitialPosition(Coordinate coords);
	void setPosition(Coordinate coords);

	void Immobilize(std::chrono::steady_clock::time_point startTime, std::chrono::duration<float> duration);
	void UpdateStatus(float deltaTime);
	bool IsImmobilized() const;
	bool IsAlive() const;

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

