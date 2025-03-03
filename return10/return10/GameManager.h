#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <vector>
#include <thread>
#include "GameLogic.h"
#include "BattleCityDatabase.h"

class GameManager
{
public:
	static GameManager& getInstance(GameStorage& storage);
	void updatePlayerScore(Player player);
	void sortLobbyPlayers();
	void addPlayerToLobby(int playerId);
	void removePlayerFromLobby(int playerId);
	void addPlayerToGame(int playerId);
	void removePlayerFromGame(int playerId);
	void createNewGame();
	void endGame(int gameId);
	void endGames();
	std::shared_ptr<GameLogic> getGameByPlayerId(int playerId);
	std::unique_ptr<Player> getPlayerFromID(int id);
	std::vector<int> getLobbyPlayers();
	std::vector<int> getInGamePlayers();
	std::vector<std::shared_ptr<GameLogic>> getActiveGames();
private:
	GameManager(GameStorage& storage);
private:
	std::vector<int> m_lobbyPlayers; 
	std::vector<int> m_inGamePlayers;
	std::vector<std::shared_ptr<GameLogic>> m_activeGames;
	GameStorage& m_storage;
};

