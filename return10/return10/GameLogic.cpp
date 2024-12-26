#include "GameLogic.h"

GameLogic::GameLogic(Map& map) : map{ map } {}

void GameLogic::checkForTraps(Player& player) {
    Coordinate pos = player.GetPosition();
    auto& cell = map.GetCellType(pos.i, pos.j);

    // Use std::visit to handle the cell type
    std::visit(
        [&player, this, &pos](auto&& cellType) {
            using T = std::decay_t<decltype(cellType)>;
            if constexpr (std::is_base_of_v<Trap, T>) {
                // If the cell is a Trap or derived from Trap, activate it
                cellType.ActivateEffect(player);
                map.SetCellType(pos.i, pos.j, std::monostate{}); // Remove trap after activation
            }
            
        },
        cell
    );
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

void GameLogic::startGame()
{
    startTime = std::chrono::steady_clock::now();
    while (gameRunning)
    {
        updateBullets();
        if (WinCondition() == true) gameRunning = false;
    }
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
            if (auto* bomb = wall->GetContainedBomb()) {
                if (bomb->IsActive()) {
                    ExplodeBomb(*bomb);
                }
            }
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


            for (const auto& player : m_players) {
                if (player.GetPosition().i == rowIndex && player.GetPosition().j == colIndex) 
                {
                    rowStr.push_back('P');
                    cellOverridden = true;
                    break; 
                }

                if (!cellOverridden)
                {
                    for (const auto& bullet : player.getGun().getFiredBullets()) {
                        if (bullet.GetX() == rowIndex && bullet.GetY() == colIndex) {
                            rowStr.push_back('*');
                            cellOverridden = true;
                            break;
                        }
                    }
                }

            }

          
            if (!cellOverridden) {
                auto trapInfo = map.GetTrapInfo(rowIndex, colIndex);
                
                if (trapInfo.has_value() && trapInfo->second) { // Trap exists and is active
                    //std::cout << trapInfo->first << ' ' << trapInfo->second;
                    if (trapInfo->first == 'T') {
                        rowStr.push_back('T');
                        //if(rowStr[rowStr.size() - 1] == 'T')
                        //     std::cout << "successfully sent the character T " << "\n ";
                    }
                        
                    if (trapInfo->first == 'G') {
                            rowStr.push_back('G');
                            /*if (rowStr[rowStr.size() - 1] == 'G')
                            std::cout << "successfully sent the character G " <<  "\n ";*/
                    }
                        
                    if (trapInfo->first == 'S') {
                              rowStr.push_back('S');
                              //if (rowStr[rowStr.size() - 1] == 'S')
                              //       std::cout << "successfully sent the character S "  << "\n ";
                    }
                        
                    
                    cellOverridden = true;
                    
                }
                
                 
            }

            if (!cellOverridden) {
                const auto& cell = map.GetCellType(rowIndex, colIndex);
                if (std::holds_alternative<std::monostate>(cell)) {
                    rowStr.push_back('0');
                }
                else if (std::holds_alternative<Wall>(cell)) {
                    const Wall& wall = std::get<Wall>(cell);

                    if (wall.IsDestructible() == false) {
                        rowStr.push_back('I');
                    }
                    else if (wall.IsDestructible() && wall.GetContainedBomb() != nullptr) {
                        rowStr.push_back('B');
                    }
                    else {
                        rowStr.push_back('D');
                    }
                }
               

            }
        }

        charMap.push_back(rowStr);
    }

    return charMap;
}


void GameLogic::updateBullets() {
    for (auto& player : m_players) {
        // Parcurgem fiecare glonț tras de jucătorul curent
        auto& bullets = player.getGun().getFiredBullets(); // Accesăm vectorul de gloanțe al jucătorului
        for (size_t i = 0; i < bullets.size(); ++i) {
            auto& bullet = bullets[i];

            if (!bullet.IsActive()) continue; // Dacă glonțul nu este activ, trecem mai departe

            bullet.Move(); // Mutăm glonțul pe hartă

            // Verificăm coliziunea cu zidurile
            if (checkWallCollision(map, bullet)) {
                continue; // Dacă glonțul lovește un zid, îl distrugem
            }

            // Verificăm coliziunea cu alți jucători
            for (auto& enemyPlayer : m_players) {
                if (&player != &enemyPlayer && checkPlayerCollision(enemyPlayer, bullet)) {
                    break; // Dacă glonțul lovește un alt jucător, pierde o viata
                }
            }

            // Verificăm coliziunea între gloanțele diferitelor jucători
            for (size_t j = i + 1; j < bullets.size(); ++j) {
                auto& otherBullet = bullets[j];
                if (bullet.GetX() == otherBullet.GetX() && bullet.GetY() == otherBullet.GetY()) {
                    // Dacă două gloanțe se întâlnesc, le anulam
                    bullet.Deactivate();
                    otherBullet.Deactivate();
                }
            }
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

Map& GameLogic::GetMap()
{
    return map;
}

bool GameLogic::isRunning() const
{
    return gameRunning;
}

void GameLogic::moveBullet(Map& map, Player& target, Gun* bullets)
{
    auto firedBullets = bullets->getFiredBullets(); // Reference to the vector of bullets
    for (auto currentBullet = firedBullets.begin(); currentBullet != firedBullets.end(); ) {
        currentBullet->Move(); // Update the position of the current bullet

        //checkPlayerCollision(target, *currentBullet); // Check for collisions with the player
        //checkWallCollision(map, *currentBullet);      // Check for collisions with walls

        if (!currentBullet->IsActive()) {
            // Remove inactive bullets and update iterator
            currentBullet = firedBullets.erase(currentBullet);
        }
        else {
            // Move to the next bullet if no erase
            ++currentBullet;
        }
    }
}

void GameLogic::movePlayer(Player* player, Direction direction)
{
    if (player == nullptr)
    {
        std::cout << "Player is null in movePlayer\n";
        return;
    }

    auto [currentX, currentY] = player->GetPosition();
    std::cout << "Current position: (" << currentX << ", " << currentY << ")\n";

    int newX = currentX;
    int newY = currentY;

    switch (direction) {
    case Direction::UP:    newX--; break;
    case Direction::DOWN:  newX++; break;
    case Direction::LEFT:  newY--; break;
    case Direction::RIGHT: newY++; break;
    }

    auto dimensions = map.GetDimensions();
    std::cout << "Attempting to move to: (" << newX << ", " << newY << ")\n";
    std::cout << "Map dimensions: (" << dimensions.first << ", " << dimensions.second << ")\n";

    if (newX < 0 || newX >= dimensions.first || newY < 0 || newY >= dimensions.second) {
        std::cout << "Out of bounds! Movement aborted.\n";
        return;
    }

    if (std::holds_alternative<Wall>(map.GetBoard()[newX][newY]))
    {
        std::cout << "Hit a wall at (" << newX << ", " << newY << "). Movement aborted.\n";
        return;
    }

    player->move(direction);
    std::cout << "Player moved successfully.\n";
}


bool GameLogic::WinCondition()
{
    int aliveCount = 0;

    for (const auto& player : m_players) {
        if (player.IsAlive()) {
            aliveCount++;
        }

        if (aliveCount > 1) {
            return false;
        }
    }

    return (aliveCount <= 1);
}
