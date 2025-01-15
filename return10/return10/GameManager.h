#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <vector>
#include <thread>
#include "GameLogic.h"
#include "BattleCityDatabase.h"
#include <mutex>

class GameManager
{
public:
	static GameManager* getInstance(GameStorage& storage);
	void run();
	void stop();
	void sortLobbyPlayers();
	void addPlayerToLobby(int playerId);
	void removePlayerFromLobby(int playerId);
	void addPlayerToGame(int playerId);
	void removePlayerFromGame(int playerId);
	void createNewGame();
	void endGame(int gameId);
	std::shared_ptr<GameLogic> getGameByPlayerId(int playerId);
	Player getPlayerFromID(int id);
	std::vector<int> getLobbyPlayers();
	std::vector<int> getInGamePlayers();
private:
	GameManager(GameStorage& storage);
private:
	std::vector<int> m_lobbyPlayers; // players waiting to join a game
	std::vector<int> m_inGamePlayers; // players currently playing a game
	std::vector<std::shared_ptr<GameLogic>> m_activeGames;
	GameStorage& m_storage;
	static std::mutex mtx;
	std::atomic<bool> m_isRunning;
};

