#include "BattleCityDatabase.h"

bool GameStorage::Initialize() {
    m_db.sync_schema();
    std::cout << "Database schema synchronized. No players or guns were added initially." << std::endl;
    return true;
}


void GameStorage::AddPlayer(const Player& player)
{
    int gunId;
    GunDAO gunDAO;
    const Gun& playerGun = player.getGun();

    gunDAO.SetFireRate(playerGun.GetFiringRate());
    gunDAO.SetBulletSpeed(playerGun.GetBulletSpeed());

    gunId = m_db.insert(gunDAO);
    PlayerDAO playerDAO;
    playerDAO.SetName(player.GetName());
    playerDAO.SetScore(player.GetScore());
    playerDAO.SetCrowns(player.GetCrowns());
    playerDAO.SetGunId(gunId); 
    m_db.insert(playerDAO);
}

void GameStorage::AddPlayerDAO(const PlayerDAO& playerDAO)
{
    m_db.insert(playerDAO);
}

int GameStorage::AddGunDAO(const GunDAO& gun)
{
    return m_db.insert(gun);
}

std::vector<PlayerDAO> GameStorage::GetPlayersDAO()
{
    return m_db.get_all<PlayerDAO>();
}
std::vector<GunDAO> GameStorage::GetGunsDAO()
{
    return m_db.get_all<GunDAO>();
}

GunDAO GameStorage::GetGunById(int gunId) {
    return m_db.get<GunDAO>(gunId);
}

PlayerDAO GameStorage::GetPlayerByID(int playerId)
{
    return m_db.get<PlayerDAO>(playerId);

}

void GameStorage::UpdatePlayerDAO(const PlayerDAO& player) {
    try {
        m_db.update(player);
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("Failed to update player: ") + e.what());
    }
}

void GameStorage::UpdateGunDAO(const GunDAO& gun) {
    try {
        m_db.update(gun);
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("Failed to update gun: ") + e.what());
    }
}


void GameStorage::DisplayDatabaseContents()
{
    auto guns = m_db.get_all<GunDAO>();
    std::cout << "Guns in the database:" << std::endl;
    for (const auto& gun : guns) {
        std::cout << "ID: " << gun.GetId() << ", Fire Rate: " << gun.GetFireRate() << ", Bullet Speed: " << gun.GetBulletSpeed() << std::endl;
    }

    std::cout << std::endl;

    auto players = m_db.get_all<PlayerDAO>();
    std::cout << "Players in the database:" << std::endl;
    for (const auto& player : players) {
        std::cout << "ID: " << player.GetId()
            << ", Name: " << player.GetName()
            << ", Password: " << player.GetPassword()
            << ", Score: " << player.GetScore()
            << ", Crowns: " << player.GetCrowns()
            << ", Gun ID: " << player.GetGunId() << std::endl;
    }
}

int GameStorage::GetPlayerScoreById(int playerId)
{
    PlayerDAO playerDAO = GetPlayerByID(playerId);
    return playerDAO.GetScore();
}

