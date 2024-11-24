#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <crow.h>
#include "BattleCityDatabase.h"


class Routing
{
public:
	Routing(crow::SimpleApp& app, GameStorage& storage);
	void Run();
	void SetupLoginRoutes(crow::SimpleApp& app);
private:
	//crow::response AddProductToBasketRoute(ProductStorage& storage, const crow::request& req, int productId)const;

private:
	crow::SimpleApp m_app;
	GameStorage& m_storage;
};

