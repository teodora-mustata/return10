#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <crow.h>
#include "BattleCityDatabase.h"
#include <regex>
#include "GameLogic.h"
#include "GameManager.h"

class Routing
{
public:
	Routing( GameStorage& storage, GameManager& gameLogic);
	void run();
	void setupLoginRoutes();
	void getTheBestPlayersByCrowns();
	void getTheBestPlayersByScore();
	GunDAO getGunById(int userId);
	PlayerDAO getPlayerById(int userId);
	void sendMap(crow::response& res, int playerId);
	void setupGameRoute();
	void buyReloadSpeedUpgrade();
	void buyBulletSpeedUpgrade();
	void addPlayerToLobby();
	void setDifficulty();
	void handlePlayerCommand();
	void createGame();
	void getActivePlayers();
	void updateMap();
	void checkWinCondition();
private:
	crow::SimpleApp m_app;
	GameStorage& m_storage;
	GameManager m_games;
};

