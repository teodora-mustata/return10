#pragma once
#include "CellType.h"
#include "Wall.h"
class Bomb;
#include <utility>
#include <vector>
#include <iostream>
#include <list>
#include <random>

class Map
{
private:
	// dimensions
	int height, width;

	// game board
	std::vector<std::vector<CellType>> board;
	//std::vector<Player*> players; //TO DO: Implement Player class
	std::vector<Bomb> bombs;
	//std::vector<Bullet> bullets; //TO DO: Implement Bullet class
	std::list<std::pair<int, int>> spawnPoints;

	// game config
	static const int max_players = 4;
	static const float destructible_wall_chance;
	static const float indestructible_wall_chance;
	static const int bombs_count = 3;
public:
	Map(int n, int m); //TO DO: finish implementing constructor
	//void generateMap();
	std::vector<std::vector<CellType>> get_board();
	std::pair<int, int> getRandomSpawnPoint();
	CellType get_cell_type(int x, int y);
	void set_cell_type(int x, int y, CellType type);
	void break_wall(int x, int y);

};

