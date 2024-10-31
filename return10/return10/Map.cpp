#include "Map.h"

Map::Map(int n, int m) : height(n), width(m)
{
	std::vector<std::pair<int,int>> temp = { {0, 0}, {0, height - 1}, {width - 1, 0}, {width - 1, height - 1}};
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(temp.begin(), temp.end(), gen);

	for (const auto& point : temp) {
		spawnPoints.push_back(point);
		}
	//TO DO: finish implementing constructor
}

std::vector<std::vector<CellType>> Map::get_board()
{
	return this->board;
}

std::pair<int, int> Map::getRandomSpawnPoint()
{
	if (!spawnPoints.empty())
	{
		std::pair<int, int> spawnPoint = spawnPoints.back();
		spawnPoints.pop_back();
		return spawnPoint;
	}
	throw std::runtime_error("No more spawn points available!");
}

CellType Map::get_cell_type(int x, int y)
{
	return board[x][y];
}

void Map::set_cell_type(int x, int y, CellType type)
{
	board[x][y] = type;
}

void Map::break_wall(int x, int y)
{
	if(std::holds_alternative<Wall>(board[x][y]))
	{
		board[x][y] = std::monostate{};
		std::cout << "Wall destroyed at (" << x << ", " << y << ")." << std::endl;
	}
}
