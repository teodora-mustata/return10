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

void GameManager::startNewGame()
{
    //if (m_lobbyPlayers.size() >= 2)
    //{
    //    int lobbySize;
    //    if (m_lobbyPlayers.size() >= 4) lobbySize = 4;
    //        else lobbySize = m_lobbyPlayers.size();
    //    GameLogic newGame;
    //    for (int i = 0; i < lobbySize; i++)
    //    {
    //        m_inGamePlayers.push_back(m_lobbyPlayers[i]);
    //        removePlayerFromLobby(i);
    //        Player newPlayer()
    //        newGame.addPlayer()
    //    }
    //    m_activeGames.push_back(newGame);
    //}
}
