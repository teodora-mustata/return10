#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <crow.h>
#include "BattleCityDatabase.h"


class Routing
{
public:
	void Run();

private:
	//crow::response AddProductToBasketRoute(ProductStorage& storage, const crow::request& req, int productId)const;

private:
	crow::SimpleApp m_app;
};

