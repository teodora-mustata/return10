#include "Map.h"

Map::Map(int n, int m) : m_height(n), m_width(m)
{
	//TO DO: Make Map generate with random height and width

	m_board.resize(m_height, std::vector<CellType>(m_width));

	for (int i = 0; i < m_height; i++)
		for (int j = 0; j < m_width; j++)
			SetCellType(i, j, std::monostate{});

	GenerateSpawnPoints();
	
	GenerateWalls();

	SetBombs();
}

std::vector<std::vector<CellType>> Map::GetBoard()
{
	return this->m_board;
}

void Map::GenerateSpawnPoints()
{
	std::vector<std::pair<int, int>> temp = { {0, 0}, {0, m_width - 1}, {m_height - 1, 0}, {m_height - 1, m_width - 1} };
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(temp.begin(), temp.end(), gen);

	for (const auto& point : temp) {
		m_spawnPoints.push_back(point);
	}
}

void Map::GenerateWalls()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);
	for (int i = 0; i < m_height; ++i) 
	{
		for (int j = 0; j < m_width; ++j) 
		{
			if (std::find(m_spawnPoints.begin(), m_spawnPoints.end(), std::make_pair(i, j)) != m_spawnPoints.end()) {
				continue;
				}

			float random_value = dist(gen);
			if (random_value < destructible_wall_chance) {
				m_board[i][j] = Wall(i, j, true);
			}
			else if (random_value < destructible_wall_chance + indestructible_wall_chance) {
				m_board[i][j] = Wall(i, j, false);
			}
			
		}
	}
}

void Map::SetBombs()
{
	std::vector<std::pair<int, int>> destructibleWalls;

	for (int i = 0; i < m_height; ++i) {
		for (int j = 0; j < m_width; ++j) {
			if (auto* wall = std::get_if<Wall>(&m_board[i][j]); wall && wall->IsDestructible()) {
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
		if (auto wallPtr = std::get_if<Wall>(&m_board[x][y]))
		{
			Bomb* bomb = new Bomb(x, y);
			wallPtr->SetContainedBomb(bomb);
			m_bombs.emplace_back(x, y);
		}
	}
}

std::pair<int, int> Map::GetRandomSpawnPoint()
{
	if (!m_spawnPoints.empty())
	{
		std::pair<int, int> spawnPoint = m_spawnPoints.back();
		m_spawnPoints.pop_back();
		return spawnPoint;
	}
	throw std::runtime_error("No more spawn points available!");
}

std::list<std::pair<int, int>> Map::GetSpawnPoints()
{
	return m_spawnPoints;
}

std::vector<Player> Map::GetPlayers()
{
	return m_players;
}

CellType Map::GetCellType(int x, int y)
{
	return m_board[x][y];
}

void Map::SetCellType(int x, int y, CellType type)
{
	m_board[x][y] = type;
}

void Map::BreakWall(int x, int y)
{
	if(std::holds_alternative<Wall>(m_board[x][y]))
	{
		// if it contains a bomb -> explode it
		m_board[x][y] = std::monostate{};
		std::cout << "Wall destroyed at (" << x << ", " << y << ")." << std::endl;
	}
}

void Map::PrintMap() const {
	for (int i = 0; i < m_board.size(); ++i) {
		for (int j = 0; j < m_board[i].size(); ++j) {
			if (std::find(m_spawnPoints.begin(), m_spawnPoints.end(), std::make_pair(i, j)) != m_spawnPoints.end()) {
				std::cout << "P "; // Spawn point
			}
			else {
				std::visit([&](auto&& arg) {
					using T = std::decay_t<decltype(arg)>;
					if constexpr (std::is_same_v<T, std::monostate>) {
						std::cout << "0 "; // Empty
					}
					else if constexpr (std::is_same_v<T, Wall>) {
						if (arg.IsDestructible()) {
							if (arg.GetContainedBomb() != nullptr) {
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
					}, m_board[i][j]);
			}
		}
		std::cout << std::endl;
	}
}

void Map::addPlayer(const std::string& playerName)
{
	std::pair<int, int> spawnPoint = GetRandomSpawnPoint();
	Player player(playerName, spawnPoint.first, spawnPoint.second);
	m_players.push_back(player);
}

void Map::removePlayer(const Player& player)
{
	for (auto it = m_players.begin(); it != m_players.end();)
	{
		if (*it == player)
		{
			it = m_players.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Map::movePlayer(const std::string& playerName, Direction direction)
{
	auto it = std::find_if(m_players.begin(), m_players.end(), [&](const Player& player) {
		return player.GetName() == playerName;
		});

	Player& player = *it;

	auto [currentX, currentY] = player.GetPosition();
	// Calculate the new position based on direction
	int newX = currentX;
	int newY = currentY;

	switch (direction) {
	case Direction::UP:    newX--; break;
	case Direction::DOWN:  newX++; break;
	case Direction::LEFT:  newY--; break;
	case Direction::RIGHT: newY++; break;
	}

	// Validate new position
	if (newX < 0 || newX >= m_height || newY < 0 || newY >= m_width) {
		return;
	}

	if (!std::holds_alternative<std::monostate>(m_board[newX][newY])) {
		return;
	}
	player.move(direction);// Update player position
}
