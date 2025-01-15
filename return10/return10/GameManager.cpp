#include "GameManager.h"

GameManager& GameManager::getInstance(GameStorage& storage)
{
    static GameManager instance(storage); 
    return instance;
}

GameManager::GameManager(GameStorage& storage) : m_storage(storage) {}

void GameManager::sortLobbyPlayers()
{
    std::sort(m_lobbyPlayers.begin(), m_lobbyPlayers.end(),
        [this](int id1, int id2) {
            return m_storage.GetPlayerScoreById(id1) > m_storage.GetPlayerScoreById(id2);
        });
}

void GameManager::addPlayerToLobby(int playerId)
{
    m_lobbyPlayers.push_back(playerId);
    sortLobbyPlayers();
}

void GameManager::removePlayerFromLobby(int playerId)
{
    auto it = std::find(m_lobbyPlayers.begin(), m_lobbyPlayers.end(), playerId);

    if (it != m_lobbyPlayers.end())
    {
        m_lobbyPlayers.erase(it);
    }
}

void GameManager::addPlayerToGame(int playerId)
{
    m_inGamePlayers.push_back(playerId);
}

void GameManager::removePlayerFromGame(int playerId)
{
    auto it = std::find(m_inGamePlayers.begin(), m_inGamePlayers.end(), playerId);

    if (it != m_inGamePlayers.end())
    {
        m_inGamePlayers.erase(it);
    }
}

//void GameManager::createNewGame()
//{
//    if (m_lobbyPlayers.size() >= 2)
//    {
//        int lobbySize;
//        if (m_lobbyPlayers.size() >= 4) lobbySize = 4;
//            else lobbySize = m_lobbyPlayers.size();
//        Map map;
//        auto newGame = std::make_shared<GameLogic>(map);
//        for (int i = 0; i < lobbySize; i++)
//        {
//            int id = m_lobbyPlayers[i];
//            addPlayerToGame(id);
//            removePlayerFromLobby(id);
//            Player newPlayer = getPlayerFromID(id);
//            newGame->addPlayer(newPlayer);
//        }
//        newGame->startGame();
//        m_activeGames.push_back(newGame);
//    }
//}

void GameManager::createNewGame()
{
    if (m_lobbyPlayers.size() < 2)
        return;
    if (m_lobbyPlayers.size() >= 2)
    {
        int lobbySize = (m_lobbyPlayers.size() >= 4) ? 4 : m_lobbyPlayers.size();
        if (lobbySize > m_lobbyPlayers.size()) {
            std::cerr << "Error: Trying to create game with more players than in lobby!" << std::endl;
            return;
        }

        auto map = std::make_shared<Map>();
        auto newGame = std::make_shared<GameLogic>(map);

        for (int i = lobbySize - 1; i >= 0; i--)
        {
            int id = m_lobbyPlayers[i];
            addPlayerToGame(id);
            removePlayerFromLobby(id); 
            Player newPlayer = getPlayerFromID(id);
            newGame->addPlayer(newPlayer);
        }

        newGame->startGame();
        m_activeGames.push_back(newGame);
        std::cout << "Created a new game! "<< std::endl;
    }
}

void GameManager::endGame(int gameId)
{
    if (m_activeGames[gameId]->isRunning() == false) //game is over
    {
        for (auto player : m_activeGames[gameId]->getPlayers())
        {
            int id = player.GetId();
            removePlayerFromGame(id);
            addPlayerToLobby(id);
        }
    }
}

void GameManager::endGames()
{
    for (size_t i = 0; i < m_activeGames.size(); ++i)
    {
        auto& game = m_activeGames[i];
        if (!game->isRunning())
        {
            std::cout << "Ended game with id: " << i << std::endl;
            endGame(i);
        }
    }
}

Player GameManager::getPlayerFromID(int id)
{
    PlayerDAO player_data = m_storage.GetPlayerByID(id);
    GunDAO gun_data = m_storage.GetGunById(player_data.GetGunId());

    Gun player_gun;
    player_gun.setFiringRate(std::chrono::seconds(static_cast<int>(gun_data.GetFireRate())));
    player_gun.setBulletSpeed(gun_data.GetBulletSpeed());

    Player new_player(player_data.GetId(), player_data.GetName(), player_data.GetScore(), player_data.GetCrowns(), player_gun);
    return new_player;
}

std::vector<int> GameManager::getLobbyPlayers()
{
    return m_lobbyPlayers;
}

std::vector<int> GameManager::getInGamePlayers()
{
    return m_inGamePlayers;
}

std::vector<std::shared_ptr<GameLogic>> GameManager::getActiveGames()
{
    return m_activeGames;
}

void GameManager::startGame(int gameId)
{
    m_activeGames[gameId]->startGame();
}


std::shared_ptr<GameLogic> GameManager::getGameByPlayerId(int playerId)
{
    for (auto& game : m_activeGames) {
        for (const auto& player : game->getPlayers()) {
            if (player.GetId() == playerId) {
                return game;
            }
        }
    }
    return nullptr;
}