#include "Map.h"

Map::Map() : m_height(40), m_width(40) //default dimensions
{
	ResizeMap();
	GenerateSpawnPoints();
	GenerateWalls();
	SetBombs();
}

std::vector<std::vector<CellType>> Map::GetBoard()
{
	return this->m_board;
}

void Map::ResizeMap()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(40, 60); // map dimensions will be between 40 and 60

	m_height = dist(gen);
	m_width = dist(gen);

	// Resize m_board
	m_board.resize(m_height, std::vector<CellType>(m_width));

	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			SetCellType(i, j, std::monostate{});
		}
	}
}

void Map::GenerateSpawnPoints()
{
	std::vector<std::pair<int, int>> temp = { {0, 0}, {0, m_width - 1}, {m_height - 1, 0}, {m_height - 1, m_width - 1} };
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(temp.begin(), temp.end(), gen);

	for (const auto& point : temp) {
		m_spawnPoints.push_back(point);
		std::cout << point.first << " " << point.second << "\n";
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

//std::pair<int, int> Map::GetRandomSpawnPoint()
//{
//	if (!m_spawnPoints.empty())
//	{
//		std::pair<int, int> spawnPoint = m_spawnPoints.back();
//		m_spawnPoints.pop_back();
//		return spawnPoint;
//	}
//	throw std::runtime_error("No more spawn points available!");
//}

std::vector<std::pair<int, int>> Map::GetSpawnPoints()
{
	return m_spawnPoints;
}

//std::vector<Player> Map::GetPlayers()
//{
//	return m_players;
//}

CellType& Map::GetCellType(int x, int y)
{
	return m_board[x][y];
}

const CellType& Map::GetCellType(int x, int y) const
{
	return m_board[x][y];
}
std::vector<Player>& Map::GetPlayers() {
	return m_players;
}
Player& Map::GetPlayer(int index) {
	if (index < 0 || index >= m_players.size()) {
		throw std::out_of_range("Invalid player index");
	}
	return m_players[index];
}

const Player& Map::GetPlayer(int index) const {
	if (index < 0 || index >= m_players.size()) {
		throw std::out_of_range("Invalid player index");
	}
	return m_players[index];
}


std::vector<Player> Map::initializePlayers(int numPlayers) {
	m_players.clear(); // make list empty
	std::string name = "Player1"; 

	auto spawnPoints = GetSpawnPoints();
	if (numPlayers > spawnPoints.size()) {
		throw std::runtime_error("Not enough spawn points for the number of players.");
	}

	for (int i = 0; i < numPlayers; ++i) {
		const auto& spawnPoint = spawnPoints[i];
		m_players.emplace_back(name, spawnPoint.first, spawnPoint.second);
		name[6]++; // increment player number

		std::cout << "Player " << i + 1 << " initialized at ("
			<< spawnPoint.first << ", " << spawnPoint.second << ")\n";
	}

	return m_players;
}

void Map::SetPlayers(const std::vector<Player>& players) {
	m_players = players;
}

std::vector<Bullet>& Map::GetFiredBullets() {
	return firedBullets;
}

void Map::SetFiredBullets(const std::vector<Bullet>& bullets) {
	firedBullets = bullets;
}

void Map::SetCellType(int x, int y, CellType type)
{
	m_board[x][y] = type;
}

void Map::BreakWall(int x, int y)
{
	if (std::holds_alternative<Wall>(m_board[x][y]))
	{
		// if it contains a bomb -> explode it
		m_board[x][y] = std::monostate{};
		std::cout << "Wall destroyed at (" << x << ", " << y << ")." << std::endl;
	}
}

//commented out because i overloaded the << operator

//void Map::PrintMap() const {
//	for (int i = 0; i < m_board.size(); ++i) {
//		for (int j = 0; j < m_board[i].size(); ++j) {
//			if (std::find(m_spawnPoints.begin(), m_spawnPoints.end(), std::make_pair(i, j)) != m_spawnPoints.end()) {
//				std::cout << "\033[32mS \033[0m"; // Spawn point = green
//			}
//			else {
//				std::visit([&](auto&& arg) {
//					using T = std::decay_t<decltype(arg)>;
//					if constexpr (std::is_same_v<T, std::monostate>) {
//						std::cout << "0 "; // Empty
//					}
//					else if constexpr (std::is_same_v<T, Wall>) {
//						if (arg.IsDestructible()) {
//							if (arg.GetContainedBomb() != nullptr) {
//								std::cout << "\033[31mDB \033[0m"; // Destructible wall with bomb = red
//							}
//							else {
//								std::cout << "\033[36mD \033[0m"; // Destructible wall = cyan
//							}
//						}
//						else {
//							std::cout << "\033[34mI \033[0m"; // Indestructible wall = blue
//						}
//					}
//					}, m_board[i][j]);
//			}
//		}
//		std::cout << std::endl;
//	}
//}

std::pair<int, int> Map::GetDimensions()
{
	std::pair<int, int> dim(m_height, m_width);
	return dim;
}

std::ostream& operator<<(std::ostream& os, const Map& map) {
	const auto& board = map.m_board;
	const auto& spawnPoints = map.m_spawnPoints;

	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j) {
			if (std::find(spawnPoints.begin(), spawnPoints.end(), std::make_pair(i, j)) != spawnPoints.end()) {
				os << "\033[32mS \033[0m"; // Spawn point = green
			}
			else {
				std::visit([&](auto&& arg) {
					using T = std::decay_t<decltype(arg)>;
					if constexpr (std::is_same_v<T, std::monostate>) {
						os << "0 "; // Empty
					}
					else if constexpr (std::is_same_v<T, Wall>) {
						if (arg.IsDestructible()) {
							if (arg.GetContainedBomb() != nullptr) {
								os << "\033[31mDB \033[0m"; // Destructible wall with bomb = red
							}
							else {
								os << "\033[36mD \033[0m"; // Destructible wall = cyan
							}
						}
						else {
							os << "\033[34mI \033[0m"; // Indestructible wall = blue
						}
					}
					}, board[i][j]);
			}
		}
		os << '\n';
	}

	return os;
}
