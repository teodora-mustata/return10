#pragma once
#include "CellType.h"
class Bomb;
#include <utility>
#include <vector>

class Map
{
private:
	// dimensions
	int width, height;

	// game board
	std::vector<std::vector<CellType>> board;
	//std::vector<Player*> players; //TO DO: Implement Player class
	std::vector<Bomb> bombs;
	//std::vector<Bullet> bullets; //TO DO: implement Bullet class

	// game config
	static const int max_players = 4;
	static const float destructible_wall_chance;
	static const float indestructible_wall_chance;
	static const int bombs_count = 3;
public:
	std::pair<int, int> getRandomSpawnPoint();
	void generateMap();
	CellType get_cell_type(int x, int y);

};

