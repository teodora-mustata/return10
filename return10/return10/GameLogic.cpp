#include "GameLogic.h"

GameLogic::GameLogic(Map& map) : map{ map } {}


void GameLogic::checkForTraps(Player& player) {
    Coordinate pos = player.GetPosition();
    auto& cell = map.GetCellType(pos.i, pos.j);

    if (auto trap = std::get_if<TeleportTrap>(&cell)) {
        std::cout << "Player " << player.GetName() << " stepped on a Teleport Trap!\n";
        trap->ActivateEffect(); // Implement teleportation logic in the trap class
        map.SetCellType(pos.i, pos.j, std::monostate{}); // Remove the trap after activation
    }
    else if (auto trap = std::get_if<DisableGunTrap>(&cell)) {
        std::cout << "Player " << player.GetName() << "'s gun is disabled!\n";
        trap->ActivateEffect(player);
        map.SetCellType(pos.i, pos.j, std::monostate{}); // Remove the trap
    }
    else if (auto trap = std::get_if<StunTrap>(&cell)) {
        std::cout << "Player " << player.GetName() << " is stunned!\n";
        trap->ActivateEffect(player);
        map.SetCellType(pos.i, pos.j, std::monostate{}); // Remove the trap
    }
}

//must be updated in the game

void GameLogic::generateTaps()
{
    static std::chrono::steady_clock::time_point lastTrap = std::chrono::steady_clock::now();
    auto currentTime=std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastTrap);
    if (elapsed.count() >= 50)
    {
        map.GenerateRandomTrap();
        lastTrap = currentTime;
    }
}

void GameLogic::initializePlayers() // setez spawnpointurile pentru playeri
{
    auto spawnPoints = map.GetSpawnPoints();
    int numPlayers = m_players.size();

    for (int i = 0; i < numPlayers; ++i) {
        const auto& spawnPoint = spawnPoints[i];
        Coordinate coords;
        coords.i= spawnPoint.first;
        coords.j = spawnPoint.second;
        m_players[i].setInitialPosition(coords);
        std::cout << "Player " << i + 1 << " initialized at ("
            << spawnPoint.first << ", " << spawnPoint.second << ")\n";
    }
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

std::vector<std::string> GameLogic::convertMapToString() const
{
    std::vector<std::string> charMap;

    for (int rowIndex = 0; rowIndex < map.GetDimensions().first; ++rowIndex) {
        std::string rowStr;

        for (int colIndex = 0; colIndex < map.GetDimensions().second; ++colIndex) {
            bool cellOverridden = false;

            // Adăugăm jucătorii
            for (const auto& player : m_players) {
                if (player.GetPosition().i == rowIndex && player.GetPosition().j == colIndex) 
                {
                    rowStr.push_back('P');  // Jucător
                    cellOverridden = true;
                    break; 
                }

                // Adăugăm gloanțele
                if (!cellOverridden)
                {
                    for (const auto& bullet : player.getGun().getFiredBullets()) {
                        if (bullet.GetX() == rowIndex && bullet.GetY() == colIndex) {
                            rowStr.push_back('*');  // Glonț
                            cellOverridden = true;
                            break;
                        }
                    }
                }

            }

            // Dacă celula nu a fost suprascrisă de un jucător sau glonț
            if (!cellOverridden) {
                const auto& cell = map.GetCellType(rowIndex, colIndex);
                if (std::holds_alternative<std::monostate>(cell)) {
                    rowStr.push_back('0');  // Celulă goală
                }
                else if (std::holds_alternative<Wall>(cell)) {
                    const Wall& wall = std::get<Wall>(cell);

                    if (wall.IsDestructible() == false) {
                        rowStr.push_back('I');  // Zid indestructibil
                    }
                    else if (wall.IsDestructible() && wall.GetContainedBomb() != nullptr) {
                        rowStr.push_back('B');  // Zid destructibil cu bombă
                    }
                    else {
                        rowStr.push_back('D');  // Zid destructibil
                    }
                }
            }
        }

        charMap.push_back(rowStr);  // Adăugăm rândul la hartă
    }

    return charMap;
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
