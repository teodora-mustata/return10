#include "Map.h"

Map::Map() : m_height(40), m_width(40) //default dimensions
{
	resizeMap();
	generateSpawnPoints();
	generateWalls();
	setBombs();
}

std::vector<std::vector<CellType>>& Map::getBoard() //here i put & jerry it solved the debug assertion failure for playerMove
{
	return this->m_board;
}

void Map::resizeMap()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(20,30); // map dimensions will be between 20 and 30

	m_height = dist(gen);
	m_width = dist(gen);

	// Resize m_board
	m_board.resize(m_height, std::vector<CellType>(m_width));

	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			setCellType(i, j, std::monostate{});
		}
	}
}

void Map::generateSpawnPoints()
{
	std::vector<std::pair<int, int>> temp = { {0, 0}, {0, m_width - 1}, {m_height - 1, 0}, {m_height - 1, m_width - 1} };
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(temp.begin(), temp.end(), gen);

	for (const auto& point : temp) {
		m_spawnPoints.push_back(point);
		//std::cout << point.first << " " << point.second << "\n";
	}
}

void Map::generateWalls()
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
				m_board[i][j] = Wall(i, j, true);//destructible
			}
			else if (random_value < destructible_wall_chance + indestructible_wall_chance) 
			{
				//no destructible walls on the side
				if (i == 0 || i == m_height - 1 || j == 0 || j == m_width - 1) 
				{
					m_board[i][j].emplace<Wall>(i, j, true);// destructible	
				}
				else 
				{
					m_board[i][j].emplace<Wall>(i, j, false);	//indestructible
				}
			}

		}
	}
}

void Map::setBombs()
{
	std::vector<std::pair<int, int>> destructibleWalls;

	for (int i = 0; i < m_height; ++i) {
		for (int j = 0; j < m_width; ++j) {
			if (auto* wall = std::get_if<Wall>(&m_board[i][j]); wall && wall->isDestructible()) {
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
		if (auto wallPtr = std::get_if<Wall>(&m_board[x][y])) {
			auto bomb = std::make_unique<Bomb>(x, y); 
			wallPtr->setContainedBomb(std::move(bomb)); // Transfer ownership
			m_bombs.emplace_back(x, y);
		}
	}
}

std::optional<std::pair<char, bool>> Map::getTrapInfo(int row, int col) const {
	if (row < 0 || row >= m_height || col < 0 || col >= m_width) {
		//std::cout << "Invalid indices (" << row << ", " << col << ")\n";
		return std::nullopt;
	}

	const auto& cell = m_board[row][col];
	//std::cout << "Checking cell at (" << row << ", " << col << ")\n";

	if (std::holds_alternative<TeleportTrap>(cell)) {
		const TeleportTrap& trap = std::get<TeleportTrap>(cell);
		//std::cout << "Found TeleportTrap, active: " << trap.IsActive() << '\n';
		return std::make_pair('T', trap.IsActive());
	}
	else if (std::holds_alternative<DisableGunTrap>(cell)) {
		const DisableGunTrap& trap = std::get<DisableGunTrap>(cell);
		//std::cout << "Found DisableGunTrap, active: " << trap.IsActive() << '\n';
		return std::make_pair('G', trap.IsActive());
	}
	else if (std::holds_alternative<StunTrap>(cell)) {
		const StunTrap& trap = std::get<StunTrap>(cell);
		//std::cout << "Found StunTrap, active: " << trap.IsActive() << '\n';
		return std::make_pair('S', trap.IsActive());
	}

	//std::cout << "No trap found at (" << row << ", " << col << ")\n";
	return std::nullopt;
}



void Map::generateRandomTrap() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::vector<Coordinate> validCells;
	for (int i = 0; i < m_height; ++i) {
		for (int j = 0; j < m_width; ++j) {
			if (std::holds_alternative<std::monostate>(m_board[i][j])) {
				validCells.emplace_back(i, j);
			}
		}
	}
	if (validCells.empty())
		return;

	std::shuffle(validCells.begin(), validCells.end(), gen);

	int cellsWithTraps = validCells.size()/6; // 1/6 din toate celulele libere vor avea trape

	int teleportTraps = 0, disableGunTraps = 0, stunTraps = 0;

	switch (m_difficulty)
	{
	case (1):
		return;
	case(2):
		disableGunTraps = cellsWithTraps / 2; stunTraps = cellsWithTraps - disableGunTraps;
		break;
	case(3): 
		disableGunTraps = cellsWithTraps / 3; stunTraps = cellsWithTraps / 3; teleportTraps = cellsWithTraps - teleportTraps - disableGunTraps;
		break;
	}

	auto placeTrap = [&](int& count, auto trapCreator) {
		for (int i = 0; i < count && !validCells.empty(); ++i) {
			auto coord = validCells.back();
			validCells.pop_back();
			m_board[coord.i][coord.j] = CellType(trapCreator(coord));
		}
		};

	placeTrap(teleportTraps, [&](const Coordinate& coord) {
		return TeleportTrap(coord.i, coord.j, validCells);
		});

	placeTrap(disableGunTraps, [&](const Coordinate& coord) {
		return DisableGunTrap(coord.i, coord.j, 3.0f);
		});

	placeTrap(stunTraps, [&](const Coordinate& coord) {
		return StunTrap(coord.i, coord.j, 3.0f);
		});

}
void Map::initialize()
{
	if (m_difficulty != 0) generateRandomTrap();
	else std::cout << "Difficulty is 0! \n";
}

std::vector<std::pair<int, int>> Map::getSpawnPoints()
{
	return m_spawnPoints;
}

int Map::getHeight()
{
	return m_height;
}
int Map::getWidth()
{
	return m_width;
}

CellType& Map::getCellType(int x, int y)
{
	return m_board[x][y];
}

const CellType& Map::getCellType(int x, int y) const
{
	return m_board[x][y];
}

void Map::setCellType(int x, int y, CellType type)
{
	m_board[x][y] = type;
}

void Map::setDifficulty(int difficulty)
{
	m_difficulty = difficulty;
}


void Map::breakWall(int x, int y)
{
	if (std::holds_alternative<Wall>(m_board[x][y]))
	{
		// if it contains a bomb -> explode it
		m_board[x][y] = std::monostate{};
		std::cout << "Wall destroyed at (" << x << ", " << y << ")." << std::endl;
	}
}

std::pair<int, int> Map::getDimensions()
{
	std::pair<int, int> dim(m_height, m_width);
	return dim;
}

int Map::getDifficulty()
{
	return m_difficulty;
}

std::pair<int, int> Map::getRandomSpawnPoint()
{
	std::cout << "Available spawn points: " << m_spawnPoints.size() << "\n";
	if (m_spawnPoints.empty()) {
		std::cout << "No available spawnpoints!\n";
		return { 0, 0 };
	}

	std::pair<int, int> selectedSpawnPoint = m_spawnPoints.back();
	std::cout << "Selected spawn point: " << selectedSpawnPoint.first << " " << selectedSpawnPoint.second << "\n";
	m_spawnPoints.pop_back();
	return selectedSpawnPoint;
}

//std::ostream& operator<<(std::ostream& os, const Map& map) {
//	const auto& board = map.m_board;
//	const auto& spawnPoints = map.m_spawnPoints;
//
//	for (int i = 0; i < board.size(); ++i) {
//		for (int j = 0; j < board[i].size(); ++j) {
//			if (std::find(spawnPoints.begin(), spawnPoints.end(), std::make_pair(i, j)) != spawnPoints.end()) {
//				os << "\033[32mS \033[0m"; // Spawn point = green
//			}
//			else {
//				std::visit([&](auto&& arg) {
//					using T = std::decay_t<decltype(arg)>;
//					if constexpr (std::is_same_v<T, std::monostate>) {
//						os << "0 "; // Empty
//					}
//					else if constexpr (std::is_same_v<T, Wall>) {
//						if (arg.IsDestructible()) {
//							if (arg.GetContainedBomb() != nullptr) {
//								os << "\033[31mDB \033[0m"; // Destructible wall with bomb = red
//							}
//							else {
//								os << "\033[36mD \033[0m"; // Destructible wall = cyan
//							}
//						}
//						else {
//							os << "\033[34mI \033[0m"; // Indestructible wall = blue
//						}
//					}
//					}, board[i][j]);
//			}
//		}
//		os << '\n';
//	}
//
//	return os;
//}

std::ostream& operator<<(std::ostream& os, const Map& map) {
	const auto& board = map.m_board;
	const auto& spawnPoints = map.m_spawnPoints;

	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j) {
			// Check if the current cell is a spawn point
			if (std::find(spawnPoints.begin(), spawnPoints.end(), std::make_pair(i, j)) != spawnPoints.end()) {
				os << "\033[32mS \033[0m"; // Spawn point = green
			}
			else {
				// Process the cell type
				std::visit([&](auto&& arg) {
					using T = std::decay_t<decltype(arg)>;
					if constexpr (std::is_same_v<T, std::monostate>) {
						os << "0 "; // Empty cell
					}
					else if constexpr (std::is_same_v<T, Wall>) {
						if (arg.isDestructible()) {
							if (arg.getContainedBomb() != nullptr) {
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
					else if constexpr (std::is_same_v<T, TeleportTrap>) {
						os << "\033[35mR \033[0m"; // Teleport trap = magenta
					}
					else if constexpr (std::is_same_v<T, DisableGunTrap>) {
						os << "\033[33mG \033[0m"; // Disable gun trap = yellow
					}
					else if constexpr (std::is_same_v<T, StunTrap>) {
						os << "\033[31mS \033[0m"; // Stun trap = red
					}
					}, board[i][j]);
			}
		}
		os << '\n';
	}

	return os;
}
