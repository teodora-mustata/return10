#pragma once
#include<string>
#include"Direction.h"
#include "Gun.h"

class Player
{
private:
	struct Coordinate {
		int i, j;
		Coordinate(int _i, int _j):
			i{_i},
			j{_j}
		{}
	};
public:
	Player(std::string name, int startX, int startY);
	//Player();
	~Player();
	void move(Direction direction);
	bool operator==(const Player& other);
	void shoot(Direction direction, float bulletSpeed);

	//Getters
	std::string GetName() const;
	int GetScore() const;
	int GetCrowns() const;
	int GetLives()const;
	std::pair<int,int> GetPosition() const;
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

