#include "Map.h"

Map::Map(int n, int m) : height(n), width(m)
{
	board.resize(height, std::vector<CellType>(width));

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			set_cell_type(i, j, std::monostate{});

	generateSpawnPoints();
	
	generateWalls();

	setBombs();
}

std::vector<std::vector<CellType>> Map::get_board()
{
	return this->board;
}

void Map::generateSpawnPoints()
{
	std::vector<std::pair<int, int>> temp = { {0, 0}, {0, width - 1}, {height - 1, 0}, {height - 1, width - 1} };
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(temp.begin(), temp.end(), gen);

	for (const auto& point : temp) {
		spawnPoints.push_back(point);
	}
}

void Map::generateWalls()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);
	for (int i = 0; i < height; ++i) 
	{
		for (int j = 0; j < width; ++j) 
		{
			if (std::find(spawnPoints.begin(), spawnPoints.end(), std::make_pair(i, j)) != spawnPoints.end()) {
				continue;
				}

			float random_value = dist(gen);
			if (random_value < destructible_wall_chance) {
				board[i][j] = Wall(i, j, true);
			}
			else if (random_value < destructible_wall_chance + indestructible_wall_chance) {
				board[i][j] = Wall(i, j, false);
			}
			
		}
	}
}

void Map::setBombs()
{
	std::vector<std::pair<int, int>> destructibleWalls;

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (auto* wall = std::get_if<Wall>(&board[i][j]); wall && wall->is_destructible()) {
				destructibleWalls.emplace_back(i, j);
			}
		}
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(destructibleWalls.begin(), destructibleWalls.end(), gen);

	int bombsToPlace = std::min(bombs_count, static_cast<int>(destructibleWalls.size()));


	for (int k = 0; k < bombsToPlace; ++k) {
		int x = destructibleWalls[k].first;
		int y = destructibleWalls[k].second;
		if (auto wallPtr = std::get_if<Wall>(&board[x][y]))
		{
			Bomb* bomb = new Bomb(x, y);
			wallPtr->set_containedBomb(bomb);
			bombs.emplace_back(x, y);
		}
	}
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

std::list<std::pair<int, int>> Map::getSpawnPoints()
{
	return spawnPoints;
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
		// if it contains a bomb -> explode it
		board[x][y] = std::monostate{};
		std::cout << "Wall destroyed at (" << x << ", " << y << ")." << std::endl;
	}
}

void Map::printMap() const {
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j) {
			if (std::find(spawnPoints.begin(), spawnPoints.end(), std::make_pair(i, j)) != spawnPoints.end()) {
				std::cout << "P "; // Spawn point
			}
			else {
				std::visit([&](auto&& arg) {
					using T = std::decay_t<decltype(arg)>;
					if constexpr (std::is_same_v<T, std::monostate>) {
						std::cout << "0 "; // Empty
					}
					else if constexpr (std::is_same_v<T, Wall>) {
						if (arg.is_destructible()) {
							if (arg.get_containedBomb() != nullptr) {
								std::cout << "DB "; // Destructible wall with bomb
							}
							else {
								std::cout << "D "; // Destructible wall
							}
						}
						else {
							std::cout << "I "; // Indestructible wall
						}
					}
					}, board[i][j]);
			}
		}
		std::cout << std::endl;
	}
}

void Map::addPlayer(Player player)
{
	m_players.emplace_back(player);
}

void Map::removePlayer(Player player)
{
	for (auto it = m_players.begin(); it!=m_players.end(); it++)
	{
		if (*it == player)
		{
			m_players.erase(it);
		}
		
	}
	
}
