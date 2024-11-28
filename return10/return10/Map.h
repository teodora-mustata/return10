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
	std::vector<std::vector<CellType>> m_board;
	std::vector<Bomb> m_bombs;
	std::vector<std::pair<int, int>> m_spawnPoints;

	std::vector<Player> m_players;       // Players moved from GameLogic
	std::vector<Bullet> firedBullets;
	// game config
	static const int max_players = 4;
	const float destructible_wall_chance = 0.4f;
	const float indestructible_wall_chance = 0.1f;
	static const int bombs_count = 3;
public:
	Map();
	~Map() = default;
	friend std::ostream& operator<<(std::ostream& os, const Map& map);
	void ResizeMap();
	void GenerateSpawnPoints();
	void GenerateWalls();
	void SetBombs();
	std::vector<std::vector<CellType>> GetBoard();
	//std::pair<int, int> GetRandomSpawnPoint();
	std::vector<std::pair<int, int>> GetSpawnPoints();
	CellType& GetCellType(int x, int y); // pentru a modifica celula
	Player& GetPlayer(int index);
	const Player& GetPlayer(int index) const;
	std::vector<Player> initializePlayers(int numPlayers);
	std::vector<Player>& GetPlayers();
	void SetPlayers(const std::vector<Player>& players);
	std::vector<Bullet>& GetFiredBullets();
	void SetFiredBullets(const std::vector<Bullet>& bullets);
	const CellType& GetCellType(int x, int y) const; // read only
	void SetCellType(int x, int y, CellType type);
	void BreakWall(int x, int y);
	//void PrintMap() const; commented out because i overloaded the << operator
	std::pair<int, int> GetDimensions();

	//void addPlayer(const std::string& playerName);
	/*void removePlayer(const Player& player, std::vector<Player>& players);
	void movePlayer(const std::string& playerName, Direction direction, std::vector<Player>& players);*/
};

