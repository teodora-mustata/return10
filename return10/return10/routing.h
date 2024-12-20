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
	Routing(crow::SimpleApp& app, GameStorage& storage, GameLogic& gameLogic);
	Routing( GameStorage& storage, GameLogic& gameLogic);

	void Run();
	void SetupLoginRoutes();
	void GetTheBestPlayersByCrowns();
	void GetTheBestPlayersByScore();
	GunDAO getGunById(int userId);
	PlayerDAO getPlayerById(int userId);
	void sendMap(crow::response& res);
	void SetupGameRoute();
	void BuyReloadSpeedUpgrade();
	void BuyBulletSpeedUpgrade();
	void AddPlayerToGame();
	void GetActivePlayers();
	void SetDifficulty();
	void HandlePlayerCommand();
private:
	crow::SimpleApp m_app;
	GameStorage& m_storage;
	//GameManager m_games;

	GameLogic& m_gameLogic;
	std::vector<int> m_loggedInPlayers;
};

