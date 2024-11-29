#pragma once
#include <string>
#include "Direction.h"
#include "Gun.h"
#include "Coordinate.h"
#include <iostream>

class Player
{
private:
public:
	Player(std::string name, int startX, int startY);
	//Player();
	~Player();
	void move(Direction direction);
	void printPosition();

	bool operator==(const Player& other);
	void shoot(Direction direction, float bulletSpeed);

	//Getters
	std::string GetName() const;
	int GetScore() const;
	int GetCrowns() const;
	int GetLives()const;
	Coordinate GetPosition() const;
	Gun getGun() const;

	//Updates for player
	void addScore(int acumulated_points);
	void addCrowns(int acumulated_points);
	void setInitialScore();
	void setInitialCrowns();
	void resetPosition();
	void loseLife();
	bool operator==(const Player& other) const;

private:
	int m_score;
	int m_lives;
	int m_crowns;
	std::string m_name;
	Coordinate m_position;
	Coordinate m_initial_position;
	Gun m_gun;
};

