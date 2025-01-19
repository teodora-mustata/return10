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
	void Run();
	void SetupLoginRoutes();
	void GetTheBestPlayersByCrowns();
	void GetTheBestPlayersByScore();
	GunDAO getGunById(int userId);
	PlayerDAO getPlayerById(int userId);
	void sendMap(crow::response& res, int playerId);
	void SetupGameRoute();
	void BuyReloadSpeedUpgrade();
	void BuyBulletSpeedUpgrade();
	void AddPlayerToLobby();
	void SetDifficulty();
	void HandlePlayerCommand();
	void CreateGame();
	void getActivePlayers();
	void updateMap();
	void checkWinCondition();
private:
	crow::SimpleApp m_app;
	GameStorage& m_storage;
	GameManager m_games;
};

