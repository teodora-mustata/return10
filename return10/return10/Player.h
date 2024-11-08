
#pragma once
#include<string>
#include"Direction.h"

#include "Gun.h"

class Player
{
public:
	Player(std::string name, int startX, int startY);
	~Player();
	void move(Direction direction);

	void shoot(Direction direction, float bulletSpeed);

	//Getters
	std::string GetName() const;
	int GetScore() const;
	int GetLives() const;
	std::pair<int, int> GetPosition() const;

	//Updates for player
	void addPoints(int acumulated_points);
	void resetPosition();
	void loseLife();

private:
	int m_score;
	int m_lives;
	int m_points;
	std::string m_name;
	std::pair<int, int> m_position;
	std::pair<int, int> m_initial_position;
	Gun m_gun;


};

