#include "GameLogic.h"

//void GameLogic::gameStart()
//{
//    showStartMenu();
//    startTimer();
//    initializeScores();
//    initializePlayers();
//}

GameLogic::GameLogic(Map& map) : map{map} {}
//
std::vector<Player> GameLogic::initializePlayers(int numPlayers)
{
    //std::cout << "Placing players..." << std::endl;
    //for (int i = 0; i < map.GetSpawnPoints().size() && i < 4; ++i) {
    //    auto spawnPoint = map.GetRandomSpawnPoint();
    //    Player newPlayer{ "Player" + std::to_string(i + 1), spawnPoint.first, spawnPoint.second };
    //    /*map.*/addPlayer(newPlayer);
    //    std::cout << "Player " << i + 1 << " spawned at (" << spawnPoint.first << ", " << spawnPoint.second << ")" << std::endl;
    //}
    std::string name = "A"; //placeholder, playerii vor trebui sa fie initializati cu numele ales la login
    auto spawnPoints = map.GetSpawnPoints();
    /*if (!map) {
        throw std::runtime_error("Map is not initialized.");
    }
    if (numPlayers > spawnPoints.size()) {
        throw std::runtime_error("Not enough spawn points");
    }*/
    /*for (const auto& spawnPoint:spawnPoints) {

        Player newPlayer(name, spawnPoint.first, spawnPoint.second);
        name[0]++;

        m_players.push_back(newPlayer);

        std::cout << "Player " << 1 << " initialized at ("
            << spawnPoint.first << ", " << spawnPoint.second << ")\n";
    }*/
    for (int i = 0; i < numPlayers; ++i) {
        const auto& spawnPoint = spawnPoints[i];
        Player newPlayer(name, spawnPoint.first, spawnPoint.second);
        name[0]++;
        m_players.push_back(newPlayer);

        std::cout << "Player " << i + 1 << " initialized at ("
            << spawnPoint.first << ", " << spawnPoint.second << ")\n";
    }
    return m_players;
}

void GameLogic::initializeScores()
{
    for (Player player : GetPlayers())
    {
        player.setInitialScore();
    }
}

void GameLogic::startTimer()
{
    startTime = std::chrono::steady_clock::now();
    std::cout << "Game timer started!" << std::endl;
}

void GameLogic::showStartMenu()
{
    std::cout << "Welcome to the game!" << std::endl;
    std::cout << "The game is starting..." << std::endl;
}

void GameLogic::ApplyDamage(Bomb bomb)
{
    std::list<std::pair<int, int>> area_of_effect = bomb.CalculateEffectArea();
    for (auto coord : area_of_effect)
    {
        int x = coord.first;
        int y = coord.second;

        for (Player player : GetPlayers())
        {
            int playerXCoord = player.GetPosition().i;
            int playerYCoord = player.GetPosition().j;
            if (playerXCoord == x && playerYCoord == y)
            {
                //player is in bomb range -> they take damage
                player.loseLife();
            }
        }

        auto& celltype = map.GetCellType(x, y); // Observă folosirea lui `auto&`!
        if (auto* wall = std::get_if<Wall>(&celltype); wall && wall->IsDestructible())
        {
            map.SetCellType(x, y, std::monostate{});
        }
    }
}

void GameLogic::ExplodeBomb(Bomb bomb)
{
    if (bomb.IsActive()) {
        std::cout << "Bomb exploded at (" << bomb.GetX() << ", " << bomb.GetY() << ")!" << std::endl;
        ApplyDamage(bomb);
        bomb.Deactivate();
    }
    else {
        std::cout << "Bomb is not active and cannot explode." << std::endl;
    }
}

void GameLogic::addPlayer(Player player)
{
    m_players.push_back(player);
}

//Bullet

bool GameLogic::checkPlayerCollision(Player& target, Bullet& bullet) {
    int targetX = target.GetPosition().i;
    int targetY = target.GetPosition().j;

    if (bullet.GetX() == targetX && bullet.GetY() == targetY && target.GetLives() > 1) {
        target.resetPosition();
        bullet.Deactivate();
        target.loseLife();
        return true;
    }
    else {
        return false;
    }
}

bool GameLogic::checkWallCollision(Map& map, Bullet& bullet) {
    CellType cell = map.GetCellType(bullet.GetX(), bullet.GetY());
    if (auto* wall = std::get_if<Wall>(&cell)) {
        if (wall->IsDestructible()) {
            map.SetCellType(bullet.GetX(), bullet.GetY(), std::monostate{});
            bullet.Deactivate();
            return true;
        }
        else {
            bullet.Deactivate();
            return true;
        }
    }
    return false;
}

//checks to see status of bullets and removes any inactive bullets that have collided from the m_firedBullets vector
//method called 
void GameLogic::updateBullets(Map& map, Player& target, Gun& bullets)
{   //needs to stay with iterator not range base because by removing from the vector it messes up the range base type for
    //need to choose where to call this and where if continous or maybe change it to once we see bullet collided somewhere else sent the message to 
    //simply erase not sure yet
    for (auto currentBullet = bullets.getFiredBullets().begin(); currentBullet != bullets.getFiredBullets().end(); ) {
        checkPlayerCollision(target, *currentBullet);
        checkWallCollision(map, *currentBullet);

        if (!currentBullet->IsActive()) {
            // if erased put iterator one place back because erase sets it further
            currentBullet = bullets.getFiredBullets().erase(currentBullet);
        }
        else {
            ++currentBullet; // only increment if we didnt erase
        }
    }

}

std::vector<Player>& GameLogic::GetPlayers()
{
    return m_players;
}

void GameLogic::removePlayer(Player player)
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

const Map& GameLogic::GetMap() const
{
    return map;
}

bool GameLogic::isRunning() const
{
    return gameRunning;
}

//void GameLogic::movePlayer(Player player, Direction direction)
//{
//    auto it = std::find_if(mplayers.begin(), players.end(), [&](const Player& player) {
//        return player.GetName() == playerName;
//        });
//
//    Player& player = *it;
//
//    auto [currentX, currentY] = player.GetPosition();
//    // Calculate the new position based on direction
//    int newX = currentX;
//    int newY = currentY;
//
//    switch (direction) {
//    case Direction::UP:    newX--; break;
//    case Direction::DOWN:  newX++; break;
//    case Direction::LEFT:  newY--; break;
//    case Direction::RIGHT: newY++; break;
//    }
//
//    // Validate new position
//    if (newX < 0 || newX >= m_height || newY < 0 || newY >= m_width) {
//        return;
//    }
//
//    if (!std::holds_alternative<std::monostate>(m_board[newX][newY])) {
//        return;
//    }
//
//    player.move(direction);// Update player position
//}
