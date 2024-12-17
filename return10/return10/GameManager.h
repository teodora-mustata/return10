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
	void sortLobbyPlayers();
	void addPlayerToLobby(int playerId);
	void removePlayerFromLobby(int playerId);
	void startNewGame();
	void endGame(int gameId);
private:
	GameManager(GameStorage& storage);
private:
	std::vector<int> m_lobbyPlayers; // players waiting to join a game
	std::vector<int> m_inGamePlayers; // players currently playing a game
	std::vector<std::shared_ptr<GameLogic>> m_activeGames;
	GameStorage& m_storage;
};

