#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <crow.h>
#include "BattleCityDatabase.h"
#include <regex>

class Routing
{
public:
	Routing(crow::SimpleApp& app, GameStorage& storage);
	void Run();
	void SetupLoginRoutes(crow::SimpleApp& app);
	void GetTheBestPlayersByCrowns();
	void GetTheBestPlayersByPoints();
	PlayerDAO getPlayerById(int userId);
private:
	crow::SimpleApp m_app;
	GameStorage& m_storage;
};

