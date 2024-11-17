
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
private:
	// dimensions
	int m_height, m_width;

	// game board
	//to do move to game logic
	std::vector<std::vector<CellType>> m_board;
	std::vector<Bomb> m_bombs;
	std::list<std::pair<int, int>> m_spawnPoints;

	// game config
	static const int max_players = 4;
	const float destructible_wall_chance = 0.4f;
	const float indestructible_wall_chance = 0.2f;
	static const int bombs_count = 3;
public:
	Map(int n, int m);
	~Map() = default;
	void GenerateSpawnPoints();
	void GenerateWalls();
	void SetBombs();
	std::vector<std::vector<CellType>> GetBoard();
	std::pair<int, int> GetRandomSpawnPoint();
	std::list<std::pair<int, int>> GetSpawnPoints();
	std::vector<Player> GetPlayers();
	CellType GetCellType(int x, int y);
	void SetCellType(int x, int y, CellType type);
	void BreakWall(int x, int y);
	void PrintMap() const;


	//
	//void addPlayer(const std::string& playerName);
	void removePlayer(const Player& player);
	void movePlayer(const std::string& playerName, Direction direction);
};

