#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <string>
#include <vector>
#include "PlayerDAO.h"
#include "GunDAO.h"
#include "Player.h"
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;


inline auto createStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Gun",
			sql::make_column("id", &GunDAO::setId, &GunDAO::getId, sql::primary_key().autoincrement()),
			sql::make_column("fireRate", &GunDAO::setFireRate, &GunDAO::getFireRate),
			sql::make_column("bulletSpeed", &GunDAO::setBulletSpeed, &GunDAO::getBulletSpeed)
		),
		sql::make_table(
			"Player",
			sql::make_column("id", &PlayerDAO::setId, &PlayerDAO::getId, sql::primary_key().autoincrement()),
			sql::make_column("name", &PlayerDAO::setName, &PlayerDAO::getName),
			sql::make_column("score", &PlayerDAO::setScore, &PlayerDAO::getScore),
			sql::make_column("crowns", &PlayerDAO::setCrowns, &PlayerDAO::getCrowns),
			sql::make_column("gunId", &PlayerDAO::setGunId, &PlayerDAO::getGunId),
			sql::make_column("password", &PlayerDAO::setPassword, &PlayerDAO::getPassword),
			sqlite_orm::foreign_key(&PlayerDAO::getGunId).references(&GunDAO::getId).on_delete.cascade()
		)
	);
}

using Storage = decltype(createStorage(""));

class GameStorage
{
public:
	bool initialize();
	void addPlayer(const Player& player);
	void addPlayerDAO(const PlayerDAO& playerDAO);
	int addGunDAO(const GunDAO& gun);
	std::vector<PlayerDAO> getPlayersDAO();
	std::vector<GunDAO> getGunsDAO();
	GunDAO getGunById(int gunId);
	PlayerDAO getPlayerByID(int playerId);
	void updatePlayerDAO(const PlayerDAO& player);
	void updateGunDAO(const GunDAO& gun);
	void displayDatabaseContents();
	int getPlayerScoreById(int playerId);
private:
	const std::string kDbFile{ "BattleCity.sqlite" };

private:
	Storage m_db = createStorage(kDbFile);
};



