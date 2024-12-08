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


inline auto CreateStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Gun",
			//&UsersEntity::SetUsername, &UsersEntity::GetUsername
			sql::make_column("id", &GunDAO::SetId, &GunDAO::GetId, sql::primary_key().autoincrement()),
			sql::make_column("fireRate", &GunDAO::SetFireRate, &GunDAO::GetFireRate),
			sql::make_column("bulletSpeed", &GunDAO::SetBulletSpeed, &GunDAO::GetBulletSpeed)
		),
		sql::make_table(
			"Player",
			//&UsersEntity::SetUsername, &UsersEntity::GetUsername
			sql::make_column("id", &PlayerDAO::SetId, &PlayerDAO::GetId, sql::primary_key().autoincrement()),
			sql::make_column("name", &PlayerDAO::SetName, &PlayerDAO::GetName),
			sql::make_column("points", &PlayerDAO::SetPoints, &PlayerDAO::GetPoints),
			sql::make_column("score", &PlayerDAO::SetScore, &PlayerDAO::GetScore),
			sql::make_column("gunId", &PlayerDAO::SetGunId, &PlayerDAO::GetGunId),
			sql::make_column("password", &PlayerDAO::SetPassword, &PlayerDAO::GetPassword),
			sqlite_orm::foreign_key(&PlayerDAO::GetGunId).references(&GunDAO::GetId).on_delete.cascade()
		)
	);
}

using Storage = decltype(CreateStorage(""));

//proceseaza datele, interactioneaza cu DB
//BattleCityStorage
class GameStorage
{
public:
	bool Initialize();

	/*std::vector<Product> GetProducts();
	void AddProductToShoppingBasket(int productId, int quantity);
	std::vector<std::tuple<std::string, float, int>> GetBasket();*/
	void AddPlayer(const Player& player); // to remove (?)
	void AddPlayerDAO(const PlayerDAO& playerDAO);
	int AddGunDAO(const GunDAO& gun);
	std::vector<PlayerDAO> GetPlayersDAO();
	std::vector<GunDAO> GetGunsDAO();
	GunDAO GetGunById(int gunId);
	PlayerDAO GetPlayernByID(int playerId);
	void UpdatePlayerDAO(const PlayerDAO& player);
	void UpdateGunDAO(const GunDAO& gun);
	void DisplayDatabaseContents();
	//Map getMap()const;
private:
	const std::string kDbFile{ "BattleCity.sqlite" };

private:
	Storage m_db = CreateStorage(kDbFile);
};



