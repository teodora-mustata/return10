#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <crow.h>
#include "BattleCityDatabase.h"
#include <regex>
#include "GameLogic.h"

class Routing
{
public:
	Routing(crow::SimpleApp& app, GameStorage& storage, GameLogic& gameLogic);
	Routing( GameStorage& storage, GameLogic& gameLogic);

	void Run();
	void SetupLoginRoutes(crow::SimpleApp& app);
	void GetTheBestPlayersByCrowns();
	void GetTheBestPlayersByPoints();
	GunDAO getGunById(int userId);
	PlayerDAO getPlayerById(int userId);
	void sendMap(crow::response& res);
	void SetupGameRoute();
	void BuyReloadSpeedUpgrade();//intreaba daca ar trebui sa facem tabelele separat(GunDAO PlayerDAO)
	void BuyBulletSpeedUpgrade();
	void AddPlayerToGame(const crow::request& req, crow::response& res);
	void GetActivePlayers();
private:
	crow::SimpleApp m_app;
	GameStorage& m_storage;
	GameLogic& m_gameLogic;
};

