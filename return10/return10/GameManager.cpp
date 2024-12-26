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

void GameManager::createNewGame()
{
    if (m_lobbyPlayers.size() >= 2)
    {
        int lobbySize;
        if (m_lobbyPlayers.size() >= 4) lobbySize = 4;
            else lobbySize = m_lobbyPlayers.size();
        Map map;
        auto newGame = std::make_shared<GameLogic>(map);
        for (int i = 0; i < lobbySize; i++)
        {
            int id = m_lobbyPlayers[i];
            addPlayerToGame(id);
            removePlayerFromLobby(id);
            Player newPlayer = getPlayerFromID(m_lobbyPlayers[id]);
            newGame->addPlayer(newPlayer);
        }
        m_activeGames.push_back(newGame);
    }
}

void GameManager::endGame(int gameId)
{
    if (m_activeGames[gameId]->isRunning() == false) //game is over
    {
        for (auto player : m_activeGames[gameId]->GetPlayers())
        {
            int id = player.GetId();
            removePlayerFromGame(id);
            addPlayerToLobby(id);
        }
    }
}

Player GameManager::getPlayerFromID(int id)
{
    PlayerDAO player_data = m_storage.GetPlayerByID(id);
    GunDAO gun_data = m_storage.GetGunById(player_data.GetGunId());

    Gun player_gun;
    player_gun.setFiringRate(std::chrono::seconds(static_cast<int>(gun_data.GetFireRate())));
    player_gun.SetBulletSpeed(gun_data.GetBulletSpeed());

    Player new_player(player_data.GetId(), player_data.GetName(), player_data.GetScore(), player_data.GetCrowns(), player_gun);
    return new_player;
}
