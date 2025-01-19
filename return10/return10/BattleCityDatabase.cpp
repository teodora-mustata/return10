#include "BattleCityDatabase.h"

bool GameStorage::initialize() {
    m_db.sync_schema();
    std::cout << "Database schema synchronized. No players or guns were added initially." << std::endl;
    return true;
}


void GameStorage::addPlayer(const Player& player)
{
    int gunId;
    GunDAO gunDAO;
    const Gun& playerGun = player.getGun();

    gunDAO.setFireRate(playerGun.GetFiringRate());
    gunDAO.setBulletSpeed(playerGun.getBulletSpeed());

    gunId = m_db.insert(gunDAO);
    PlayerDAO playerDAO;
    playerDAO.setName(player.getName());
    playerDAO.setScore(player.getScore());
    playerDAO.setCrowns(player.getCrowns());
    playerDAO.setGunId(gunId); 
    m_db.insert(playerDAO);
}

void GameStorage::addPlayerDAO(const PlayerDAO& playerDAO)
{
    m_db.insert(playerDAO);
}

int GameStorage::addGunDAO(const GunDAO& gun)
{
    return m_db.insert(gun);
}

std::vector<PlayerDAO> GameStorage::getPlayersDAO()
{
    return m_db.get_all<PlayerDAO>();
}
std::vector<GunDAO> GameStorage::getGunsDAO()
{
    return m_db.get_all<GunDAO>();
}

GunDAO GameStorage::getGunById(int gunId) {
    return m_db.get<GunDAO>(gunId);
}

PlayerDAO GameStorage::getPlayerByID(int playerId)
{
    return m_db.get<PlayerDAO>(playerId);

}

void GameStorage::updatePlayerDAO(const PlayerDAO& player) {
    try {
        m_db.update(player);
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("Failed to update player: ") + e.what());
    }
}

void GameStorage::updateGunDAO(const GunDAO& gun) {
    try {
        m_db.update(gun);
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("Failed to update gun: ") + e.what());
    }
}


void GameStorage::displayDatabaseContents()
{
    auto guns = m_db.get_all<GunDAO>();
    std::cout << "Guns in the database:" << std::endl;
    for (const auto& gun : guns) {
        std::cout << "ID: " << gun.getId() << ", Fire Rate: " << gun.getFireRate() << ", Bullet Speed: " << gun.getBulletSpeed() << std::endl;
    }

    std::cout << std::endl;

    auto players = m_db.get_all<PlayerDAO>();
    std::cout << "Players in the database:" << std::endl;
    for (const auto& player : players) {
        std::cout << "ID: " << player.getId()
            << ", Name: " << player.getName()
            << ", Password: " << player.getPassword()
            << ", Score: " << player.getScore()
            << ", Crowns: " << player.getCrowns()
            << ", Gun ID: " << player.getGunId() << std::endl;
    }
}

int GameStorage::getPlayerScoreById(int playerId)
{
    PlayerDAO playerDAO = getPlayerByID(playerId);
    return playerDAO.getScore();
}

