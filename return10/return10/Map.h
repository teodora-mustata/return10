#pragma once
#include "CellType.h"
#include "Wall.h"
#include "Player.h"
#include <utility>
#include <vector>
#include <iostream>
#include <list>
#include <random>
#include <algorithm>

class Map
{
public:
	Map();
	~Map() = default;
	friend std::ostream& operator<<(std::ostream& os, const Map& map);
	void ResizeMap();
	void GenerateSpawnPoints();
	void GenerateWalls();
	void SetBombs();
	void GenerateRandomTrap();

	std::vector<std::vector<CellType>>& GetBoard(); // here put & jerry it solved the debug assertion failre for playerMove
	std::vector<std::pair<int, int>> GetSpawnPoints();
	CellType& GetCellType(int x, int y); // pentru a modifica celula
	const CellType& GetCellType(int x, int y) const; // read only
	std::pair<int, int> GetDimensions();
	int GetDifficulty();

	void SetCellType(int x, int y, CellType type);
	void SetDifficulty(int difficulty);

	void BreakWall(int x, int y);


private:
	// dimensions
	int m_height, m_width;

	// game board
	std::vector<std::vector<CellType>> m_board;
	std::vector<Bomb> m_bombs;
	std::vector<std::pair<int, int>> m_spawnPoints;

	// game config
	static const int max_players = 4;
	const float destructible_wall_chance = 0.4f;
	const float indestructible_wall_chance = 0.1f;
	static const int bombs_count = 3;
	int m_difficulty=0;
};

