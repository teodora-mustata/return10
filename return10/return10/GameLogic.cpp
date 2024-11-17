
#include "GameLogic.h"

void GameLogic::gameStart()
{
    showStartMenu();
    startTimer();
    initializeScores();
    placePlayer();
}

void GameLogic::placePlayer()
{
    std::cout << "Placing players..." << std::endl;
    for (int i = 0; i < map.GetSpawnPoints().size() && i < 4; ++i) {
        auto spawnPoint = map.GetRandomSpawnPoint();
        Player newPlayer{ "Player" + std::to_string(i + 1), spawnPoint.first, spawnPoint.second };
        /*map.*/addPlayer(newPlayer);
        std::cout << "Player " << i + 1 << " spawned at (" << spawnPoint.first << ", " << spawnPoint.second << ")" << std::endl;
    }
}

void GameLogic::initializeScores()
{
    for (Player player : map.GetPlayers())
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

        for (int i = 0; i < map.GetPlayers().size(); ++i)
        {
            Player player = map.GetPlayers()[i];
            int playerXCoord = player.GetPosition().first;
            int playerYCoord = player.GetPosition().second;
            if (playerXCoord == x && playerYCoord == y)
            {
                //player is in bomb range -> they take damage
                player.loseLife();
            }
        }
 
        if (auto* wall = std::get_if<Wall>(&map.GetCellType(x, y)); wall && wall->IsDestructible())
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

bool GameLogic::checkPlayerCollision(Player& target,Bullet& bullet) {
    int targetX = target.GetPosition().first;
    int targetY = target.GetPosition().second;

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
    CellType cell = map.GetCellType(bullet.getX(),bullet.getY());
    if (auto* wall = std::get_if<Wall>(&cell)) {
        if (wall->IsDestructible()) {
            map.SetCellType(bullet.getX(), bullet.getY(), std::monostate{});
            bullet.deactivate();
            return true;
        }
        else {
            bullet.deactivate();
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
    for (auto currentBullet = bullets.getBullets().begin(); currentBullet != bullets.getBullets().end(); ) {
        checkPlayerCollision(target, *currentBullet);
        checkWallCollision(map, *currentBullet);

        if (!currentBullet->isActive()) {
            // if erased put iterator one place back because erase sets it further
            currentBullet = bullets.getBullets().erase(currentBullet);
        }
        else {
            ++currentBullet; // only increment if we didnt erase
        }
    }

}