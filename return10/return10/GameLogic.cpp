#include "GameLogic.h"

GameLogic::GameLogic(Map& map) : map{ map } {}

void GameLogic::checkForTraps(Player& player) {
    Coordinate pos = player.GetPosition();
    auto& cell = map.getCellType(pos.i, pos.j);

    // Use std::visit to handle the cell type
    std::visit(
        [&player, this, &pos](auto&& cellType) {
            using T = std::decay_t<decltype(cellType)>;
            if constexpr (std::is_base_of_v<Trap, T>) {
                // If the cell is a Trap or derived from Trap, activate it
                cellType.activateEffect(player);
                map.setCellType(pos.i, pos.j, std::monostate{}); // Remove trap after activation
            }
            
        },
        cell
    );
}

void GameLogic::initializePlayers() // setez spawnpointurile pentru playeri
{
    auto spawnPoints = map.getSpawnPoints();
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
    for (Player player : getPlayers())
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
        if (winCondition() == true) gameRunning = false;
    }
}

void GameLogic::applyDamage(Bomb bomb)
{
    std::list<std::pair<int, int>> area_of_effect = bomb.calculateEffectArea();
    for (auto coord : area_of_effect)
    {
        int x = coord.first;
        int y = coord.second;

        for (Player player : getPlayers())
        {
            int playerXCoord = player.GetPosition().i;
            int playerYCoord = player.GetPosition().j;
            if (playerXCoord == x && playerYCoord == y)
            {
                //player is in bomb range -> they take damage
                player.loseLife();
            }
        }

        auto& celltype = map.getCellType(x, y); // Observă folosirea lui `auto&`!
        if (auto* wall = std::get_if<Wall>(&celltype); wall && wall->isDestructible())
        {
            map.setCellType(x, y, std::monostate{});
        }
    }
}

void GameLogic::explodeBomb(Bomb& bomb)
{
    if (bomb.isActive()) {
        std::cout << "Bomb exploded at (" << bomb.getX() << ", " << bomb.getY() << ")!" << std::endl;
        applyDamage(bomb);
        bomb.deactivate();
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

    if (bullet.getX() == targetX && bullet.getY() == targetY && target.GetLives() > 1) {
        target.resetPosition();
        bullet.deactivate();
        target.loseLife();
        return true;
    }
    else {
        return false;
    }
}

bool GameLogic::checkWallCollision(Map& map, Bullet& bullet) {

    CellType cell = map.getCellType(bullet.getX(), bullet.getY());
    if (auto* wall = std::get_if<Wall>(&cell)) {
        std::cout << "Wall detected at position (" << wall->getX() << ", "
            << wall->getY() << "). IsDestructible: "
            << (wall->isDestructible() ? "Yes" : "No") << std::endl;

        if (wall->isDestructible()) {
            if (auto* bomb = wall->getContainedBomb()) {
                std::cout << "Bomb found in wall at (" << bomb->getX() << ", "
                    << bomb->getY() << "). IsActive: "
                    << (bomb->isActive() ? "Yes" : "No") << std::endl;

                if (bomb->isActive()) {
                    std::cout << "Bomb is active and will now explode." << std::endl;
                    explodeBomb(*bomb);
                }
                else {
                    std::cout << "Bomb is inactive, no explosion." << std::endl;
                }
            }
            else {
                std::cout << "No bomb contained in this destructible wall." << std::endl;
            }

            std::cout << "Destroying wall and replacing with empty cell." << std::endl;
            map.setCellType(bullet.getX(), bullet.getY(), std::monostate{});
            bullet.deactivate();
            std::cout << "Bullet deactivated after hitting a destructible wall." << std::endl;
            return true;
        }
        else {
            std::cout << "Wall is indestructible. Bullet deactivated." << std::endl;
            bullet.deactivate();
            return true;
        }
    }
    else {
        std::cout << "No wall detected at bullet position ("
            << bullet.getX() << ", " << bullet.getY() << ")." << std::endl;
    }

    return false;
}

std::vector<std::string> GameLogic::convertMapToString() const
{
    std::vector<std::string> charMap;

    for (int rowIndex = 0; rowIndex < map.getDimensions().first; ++rowIndex) {
        std::string rowStr;

        for (int colIndex = 0; colIndex < map.getDimensions().second; ++colIndex) {
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
                        if (bullet.getX() == rowIndex && bullet.getY() == colIndex) {
                            rowStr.push_back('*');
                            cellOverridden = true;
                            break;
                        }
                    }
                }

            }

          
            if (!cellOverridden) {
                auto trapInfo = map.getTrapInfo(rowIndex, colIndex);
                
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
                const auto& cell = map.getCellType(rowIndex, colIndex);
                if (std::holds_alternative<std::monostate>(cell)) {
                    rowStr.push_back('0');
                }
                else if (std::holds_alternative<Wall>(cell)) {
                    const Wall& wall = std::get<Wall>(cell);

                    if (wall.isDestructible() == false) {
                        rowStr.push_back('I');
                    }
                    else if (wall.isDestructible() && wall.getContainedBomb() != nullptr) {
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

            if (!bullet.isActive()) continue; // Dacă glonțul nu este activ, trecem mai departe

            bullet.move(); // Mutăm glonțul pe hartă

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
                if (bullet.getX() == otherBullet.getX() && bullet.getY() == otherBullet.getY()) {
                    // Dacă două gloanțe se întâlnesc, le anulam
                    bullet.deactivate();
                    otherBullet.deactivate();
                }
            }
        }
    }
}


std::vector<Player>& GameLogic::getPlayers()
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
        currentBullet->move(); // Update the position of the current bullet

        //checkPlayerCollision(target, *currentBullet); // Check for collisions with the player
        //checkWallCollision(map, *currentBullet);      // Check for collisions with walls

        if (!currentBullet->isActive()) {
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

    auto dimensions = map.getDimensions();
    std::cout << "Attempting to move to: (" << newX << ", " << newY << ")\n";
    std::cout << "Map dimensions: (" << dimensions.first << ", " << dimensions.second << ")\n";

    if (newX < 0 || newX >= dimensions.first || newY < 0 || newY >= dimensions.second) {
        std::cout << "Out of bounds! Movement aborted.\n";
        return;
    }

    if (std::holds_alternative<Wall>(map.getBoard()[newX][newY]))
    {
        std::cout << "Hit a wall at (" << newX << ", " << newY << "). Movement aborted.\n";
        return;
    }

    player->move(direction);
    std::cout << "Player moved successfully.\n";
}


bool GameLogic::winCondition()
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
