#include "GameLogic.h"

GameLogic::GameLogic(std::shared_ptr<Map> map) : map{ map }, gameRunning{ true }
{
    map->setDifficulty(0);
}

Coordinate GameLogic::getNextPosition(const Coordinate& currentPosition, Direction direction) {
    Coordinate nextPosition = currentPosition;
    switch (direction) {
    case Direction::UP:
        nextPosition.i -= 1;
        break;
    case Direction::DOWN:
        nextPosition.i += 1;
        break;
    case Direction::LEFT:
        nextPosition.j -= 1;
        break;
    case Direction::RIGHT:
        nextPosition.j += 1;
        break;
    }
    return nextPosition;
}

bool GameLogic::isInsideMap(const Coordinate& position) {
    return (position.j >= 0 && position.j < map->getWidth() && position.i >= 0 && position.i < map->getHeight());
}

void GameLogic::checkForTraps(Player& player) {
    Coordinate pos = player.getPosition();
    auto& cell = map->getCellType(pos.i, pos.j);

    std::visit(
        [&player, this, &pos](auto&& cellType) {
            using T = std::decay_t<decltype(cellType)>;
            if constexpr (std::is_base_of_v<Trap, T>) {
                cellType.activateEffect(player);
                map->setCellType(pos.i, pos.j, std::monostate{}); 
            }
            
        },
        cell
    );
}

void GameLogic::initializePlayers()
{
    auto spawnPoints = map->getSpawnPoints();
    int numPlayers = m_players.size();

    for (int i = 0; i < numPlayers; ++i) {
        const auto& spawnPoint = spawnPoints[i];
        Coordinate coords(spawnPoint.first, spawnPoint.second);
        m_players[i].setInitialPosition(coords);
        m_players[i].setPosition(coords);
        std::cout << "Player " << i + 1 << " initialized at ("
            << spawnPoint.first << ", " << spawnPoint.second << ")\n";
    }
}


void GameLogic::initializeScores()
{
    for (Player& player : m_players)
    {
        player.setInitialScore();
    }
}



void GameLogic::applyDamage(Bomb bomb)
{
    std::list<std::pair<int, int>> area_of_effect = bomb.calculateEffectArea();
    for (auto coord : area_of_effect)
    {
        int x = coord.first;
        int y = coord.second;

        for (Player &player : getPlayers())
        {
            int playerXCoord = player.getPosition().i;
            int playerYCoord = player.getPosition().j;
            if (playerXCoord == x && playerYCoord == y)
            {
                player.loseLife();
                player.resetPosition();
            }
        }

        auto& celltype = map->getCellType(x, y);
        if (auto* wall = std::get_if<Wall>(&celltype); wall && wall->isDestructible())
        {
            map->setCellType(x, y, std::monostate{});
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

bool GameLogic::checkPlayerCollision(Player& owner, Player& target, Bullet& bullet) {
    int targetX = target.getPosition().i;
    int targetY = target.getPosition().j;

    if (bullet.getX() == targetX && bullet.getY() == targetY && bullet.isActive() == true)
        if (target.getLives() > 1) {
            target.resetPosition();
            target.loseLife();
            owner.addScore(100);
            std::cout << "Player lives > 1, added 100 score! \n";
            bullet.deactivate();
            return true;
        }
        else if (target.getLives() == 1)
        {
            m_playersInDeathOrder.push_back(&target);
            owner.addScore(100);
            std::cout << "Player lives = 1, added 100 score! \n";
            target.loseLife();
            bullet.deactivate();
            return true;
        }
    else {
        return false;
    }
}

bool GameLogic::checkWallCollision(Bullet& bullet) {

    CellType cell = map->getCellType(bullet.getX(), bullet.getY());
    if (auto* wall = std::get_if<Wall>(&cell)) {
        std::cout << "Wall detected at position (" << wall->getX() << ", "
            << wall->getY() << "). IsDestructible: "
            << (wall->isDestructible() ? "Yes" : "No") << std::endl;

        if (wall->isDestructible()) {
            if (auto bomb = wall->getContainedBomb()) {
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
            map->setCellType(bullet.getX(), bullet.getY(), std::monostate{});
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

    for (int rowIndex = 0; rowIndex < map->getDimensions().first; ++rowIndex) {
        std::string rowStr;
        for (int colIndex = 0; colIndex < map->getDimensions().second; ++colIndex) {
            bool cellOverridden = false;


            for (const auto& player : m_players) {
                if (player.getPosition().i == rowIndex && player.getPosition().j == colIndex && player.getLives()>0) 
                {
                    std::cout << "Player " << player.getId() << " found at position: " << rowIndex << ", " << colIndex << std::endl;
                    rowStr.push_back('P');
                    cellOverridden = true;
                    break; 
                }

                if (cellOverridden==false)
                {
                    for (const auto& bullet : player.getGun().getFiredBullets())
                    {
                        if (bullet.getX() == rowIndex && bullet.getY() == colIndex && bullet.isActive()==true) {
                            rowStr.push_back('*');
                            cellOverridden = true;
                            break;
                        }
                    }
                }

            }

          
            if (cellOverridden==false) {
                auto trapInfo = map->getTrapInfo(rowIndex, colIndex);
                
                if (trapInfo.has_value() && trapInfo->second) {
                    if (trapInfo->first == 'T') {
                        rowStr.push_back('T');
                    }
                        
                    if (trapInfo->first == 'G') {
                            rowStr.push_back('G');
                    }
                        
                    if (trapInfo->first == 'S') {
                              rowStr.push_back('S');
                    }
                        
                    
                    cellOverridden = true;
                    
                }
                
                 
            }

            if (cellOverridden==false) {
                const auto& cell = map->getCellType(rowIndex, colIndex);
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
        auto& bullets = player.getGun().getFiredBullets();
        for (size_t i = 0; i < bullets.size(); ++i) {
            auto& bullet = bullets[i];

            if (!bullet.isActive()) continue; 

            bullet.move(); 

            if (checkWallCollision(bullet)) {
                break;
            }

            for (auto& enemyPlayer : m_players) {
                if (&player != &enemyPlayer && checkPlayerCollision(player, enemyPlayer, bullet)) {
                    break; 
                }
            }

            for (size_t j = i + 1; j < bullets.size(); ++j) {
                auto otherBullet = std::make_unique<Bullet>(bullets[j]);
                if (bullet.getX() == otherBullet->getX() && bullet.getY() == otherBullet->getY()) {
                    bullet.deactivate();
                    otherBullet->deactivate();
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
    return *map;
}

Map& GameLogic::GetMap()
{
    if (&map == nullptr) {
        throw std::runtime_error("Map reference is invalid!");
    }
    return *map;
}

bool GameLogic::isRunning() const
{
    return gameRunning;
}

void GameLogic::moveBullet(Map& map, Player& target, Gun* bullets)
{
    auto firedBullets = bullets->getFiredBullets();
    for (auto currentBullet = firedBullets.begin(); currentBullet != firedBullets.end(); ) {
        currentBullet->move(); 

        if (!currentBullet->isActive()) {
            currentBullet = firedBullets.erase(currentBullet);
        }
        else {
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

    player->updateStatus(0); 

    if (player->isImmobilized()) {
        std::cout << "Player is immobilized and cannot move.\n";
        return;
    }

    auto [currentX, currentY] = player->getPosition();
    std::cout << "Current position: (" << currentX << ", " << currentY << ")\n";

    int newX = currentX;
    int newY = currentY;

    switch (direction) {
    case Direction::UP:    newX--; break;
    case Direction::DOWN:  newX++; break;
    case Direction::LEFT:  newY--; break;
    case Direction::RIGHT: newY++; break;
    }

    auto dimensions = map->getDimensions();
    std::cout << "Attempting to move to: (" << newX << ", " << newY << ")\n";
    std::cout << "Map dimensions: (" << dimensions.first << ", " << dimensions.second << ")\n";

    if (newX < 0 || newX >= dimensions.first || newY < 0 || newY >= dimensions.second) {
        std::cout << "Out of bounds! Movement aborted.\n";
        player->setFacingDirection(direction);
        return;
    }

    if (std::holds_alternative<Wall>(map->getBoard()[newX][newY]))
    {
        std::cout << "Hit a wall at (" << newX << ", " << newY << "). Movement aborted.\n";
        player->setFacingDirection(direction);
        return;
    }

    for (const auto& p : m_players) {
        if (p.getPosition().i == newX && p.getPosition().j == newY) {
            std::cout << "Hit a player at (" << newX << ", " << newY << "). Movement aborted.\n";
            player->setFacingDirection(direction);
            return;
        }
    }

    player->move(direction);
    CellType cellType = map->getCellType(newX, newY);

    if (std::holds_alternative<StunTrap>(cellType)) {
        StunTrap& trap = std::get<StunTrap>(cellType);
        if (trap.isActive()) {
            trap.activateEffect(*player);
            trap.setState(false);
            std::cout << "Player has been immobilized at (" << newX << ", " << newY << ").\n";
        }
    }

    if (std::holds_alternative<DisableGunTrap>(cellType)) {
        DisableGunTrap& trap = std::get<DisableGunTrap>(cellType);
        if (trap.isActive()) {
            trap.activateEffect(*player);
            trap.setState(false);
            std::cout << "Player's gun has been disabled at (" << newX << ", " << newY << ").\n";
        }
    }

    if (std::holds_alternative<TeleportTrap>(cellType)) {
        TeleportTrap& trap = std::get<TeleportTrap>(cellType);
        if (trap.isActive()) {
            trap.activateEffect(*player);
            trap.setState(false);
           
        }
    }

    player->getGun().updateJammed();
}


bool GameLogic::checkIfRunning()
{
    int aliveCount = 0;
    Player* lastPlayer = nullptr;

    for (auto& player : m_players) {
        if (player.isAlive()) {
            aliveCount++;
            lastPlayer = &player;
        }
    }

    if (aliveCount > 1) {
        return true; 
    }

    if (aliveCount == 1 && lastPlayer != nullptr) {
        m_playersInDeathOrder.push_back(lastPlayer);
        std::cout << "Winner: " << lastPlayer->getName() << std::endl;
    }

    return false; 
}

void GameLogic::giveCrowns()
{
    if (m_playersInDeathOrder.size() == m_players.size())
    {
        m_playersInDeathOrder[m_playersInDeathOrder.size() - 1]->addCrowns(2);
        m_playersInDeathOrder[m_playersInDeathOrder.size() - 1]->addScore(200);
        if (m_playersInDeathOrder.size() >= 2)
        {
            m_playersInDeathOrder[m_playersInDeathOrder.size() - 2]->addCrowns(1);
        }
        gameRunning = false;
    }
}
