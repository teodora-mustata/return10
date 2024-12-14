#include "BattleCityDatabase.h"

bool GameStorage::Initialize() {
    // Sincronizeaza schema bazei de date, creând tabelele necesare, dar fara a adauga date
    m_db.sync_schema();

    std::cout << "Database schema synchronized. No players or guns were added initially." << std::endl;

    // Returneaza true pentru a confirma ca tabelele au fost create cu succes
    return true;
}


void GameStorage::AddPlayer(const Player& player)
{
    int gunId;
    GunDAO gunDAO;
    const Gun& playerGun = player.getGun();

    gunDAO.SetFireRate(playerGun.GetFiringRate());
    gunDAO.SetBulletSpeed(playerGun.GetBulletSpeed());

    gunId = m_db.insert(gunDAO);  // Inseram gun-ul în baza de date
    // Cream PlayerDAO pentru a adauga player-ul în baza de date
    PlayerDAO playerDAO;
    playerDAO.SetName(player.GetName());
    playerDAO.SetScore(player.GetScore());
    playerDAO.SetCrowns(player.GetCrowns());
    playerDAO.SetGunId(gunId);  // Setam gunId-ul asociat player-ului

    // Adaugam player-ul în baza de date
    m_db.insert(playerDAO);
}

void GameStorage::AddPlayerDAO(const PlayerDAO& playerDAO)
{
    m_db.insert(playerDAO);
}

int GameStorage::AddGunDAO(const GunDAO& gun)
{
    return m_db.insert(gun);  // Inserăm obiectul GunDAO în baza de date și returnm ID-ul
}

//std::vector<PlayerDAO> GameStorage::GetPlayersDAO()
//{
//    return m_db.get_all<PlayerDAO>();
//}
std::vector<PlayerDAO> GameStorage::GetPlayersDAO()
{
    return m_db.get_all<PlayerDAO>();
}
std::vector<GunDAO> GameStorage::GetGunsDAO()
{
    return m_db.get_all<GunDAO>();
}

GunDAO GameStorage::GetGunById(int gunId) {
    return m_db.get<GunDAO>(gunId);  // Aruncă excepție dacă nu există
}

PlayerDAO GameStorage::GetPlayerByID(int playerId)
{
    return m_db.get<PlayerDAO>(playerId);

}

void GameStorage::UpdatePlayerDAO(const PlayerDAO& player) {
    try {
        
        m_db.update(player); // Actualizează jucătorul în baza de date
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("Failed to update player: ") + e.what());
    }
}

void GameStorage::UpdateGunDAO(const GunDAO& gun) {
    try {
        m_db.update(gun); // Actualizează arma în baza de date
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("Failed to update gun: ") + e.what());
    }
}


void GameStorage::DisplayDatabaseContents()
{
    // Afișează toate armele
    auto guns = m_db.get_all<GunDAO>();  // Preia toate înregistrările din tabela Gun
    std::cout << "Guns in the database:" << std::endl;
    for (const auto& gun : guns) {
        std::cout << "ID: " << gun.GetId() << ", Fire Rate: " << gun.GetFireRate() << ", Bullet Speed: " << gun.GetBulletSpeed() << std::endl;
    }

    std::cout << std::endl;

    // Afișează toți jucătorii
    auto players = m_db.get_all<PlayerDAO>();  // Preia toate înregistrările din tabela Player
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

