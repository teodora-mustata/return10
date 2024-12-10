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
	std::vector<std::vector<CellType>> GetBoard();
	//std::pair<int, int> GetRandomSpawnPoint();
	std::vector<std::pair<int, int>> GetSpawnPoints();
	CellType& GetCellType(int x, int y); // pentru a modifica celula
	const CellType& GetCellType(int x, int y) const; // read only
	void SetCellType(int x, int y, CellType type);
	void BreakWall(int x, int y);
	//void PrintMap() const; commented out because i overloaded the << operator
	std::pair<int, int> GetDimensions();

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

};

