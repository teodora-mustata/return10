
#pragma once
#include "CellType.h"
#include "Wall.h"
#include "Bomb.h"
#include "Player.h";
#include "Bullet.h"
#include <utility>
#include <vector>
#include <iostream>
#include <list>
#include <random>
#include <algorithm>

class Map
{
private:
	// dimensions
	int height, width;

	// game board
	//to do move to game logic
	std::vector<std::vector<CellType>> board;
	std::vector<Player> m_players;
	std::vector<Bomb> bombs;
	std::vector<Bullet> bullets;
	std::list<std::pair<int, int>> spawnPoints;

	// game config
	static const int max_players = 4;
	const float destructible_wall_chance = 0.4f;
	const float indestructible_wall_chance = 0.2f;
	static const int bombs_count = 3;
public:
	Map(int n, int m);
	void generateSpawnPoints();
	void generateWalls();
	void setBombs();
	std::vector<std::vector<CellType>> get_board();
	std::pair<int, int> getRandomSpawnPoint();
	std::list<std::pair<int, int>> getSpawnPoints();
	CellType get_cell_type(int x, int y);
	void set_cell_type(int x, int y, CellType type);
	void break_wall(int x, int y);
	void printMap() const;


	//
	void addPlayer(Player player);
	void removePlayer(Player player);
};

