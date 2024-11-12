
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
        map.addPlayer(newPlayer);
        std::cout << "Player " << i + 1 << " spawned at (" << spawnPoint.first << ", " << spawnPoint.second << ")" << std::endl;
    }
}

void GameLogic::initializeScores()
{
    score = 0;
    std::cout << "Scores initialized. Starting score: " << score << std::endl;
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